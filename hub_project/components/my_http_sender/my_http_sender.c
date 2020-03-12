/* 
AN EXAMPLE FILE FOR SENDING DATA TO "https://www.vibecheck.no/esptest.php",
data is sent in json format with hhtp-post and formatted into a table at the webpage. 
It sends only once, when the function http_rest_with_url(void) is called. 
This is based on the esp_http_client example from esp_idf
*/

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"

#include "esp_http_client.h"

#include "my_http_sender.h"

#define TURBIN_ID 1

#define MAX_HTTP_RECV_BUFFER 512
static const char *TAG = "HTTP_CLIENT";

//comment from original esp-idf document. 
/* Root cert for howsmyssl.com, taken from howsmyssl_com_root_cert.pem

   The PEM file was extracted from the output of this command:
   openssl s_client -showcerts -connect www.howsmyssl.com:443 </dev/null

   The CA root cert is the last cert given in the chain of certs.

   To embed it in the app binary, the PEM file is named
   in the component.mk COMPONENT_EMBED_TXTFILES variable.
*/

extern const char howsmyssl_com_root_cert_pem_start[] asm("_binary_howsmyssl_com_root_cert_pem_start");
extern const char howsmyssl_com_root_cert_pem_end[]   asm("_binary_howsmyssl_com_root_cert_pem_end");

//used in fill_my_http_buffer
int my_send_buffer[4];// todo: calculate size
int buffer_index=0; 
//int char_count=0; 
const int json_padding_size = 30;

const int max_digits_in_data_element = 10;
const int max_digits_in_turb_num = 3;

int buf_num=0; //the number to put in the buffer, has to be global due to parsing-reasons

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Write out data
                // printf("%.*s", evt->data_len, (char*)evt->data);
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error(evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            break;
    }
    return ESP_OK;
}


static void http_rest_with_url(void)
{
    esp_http_client_config_t config = {
        .url = /*"http://vibecheck.no/arg",*/ "http://httpbin.org/get",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // POST
    const char *post_data = "{\"turbin\":11,\"verdier\":\"2\"}"; 
    char *read_data = malloc(MAX_HTTP_RECV_BUFFER + 1); 

    esp_http_client_set_url(client, "https://www.vibecheck.no/esptest.php");
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
        
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    printf("read_data unfilled size: %d\n", sizeof(read_data));
    int read_len = esp_http_client_read(client, read_data, esp_http_client_get_content_length(client));
    if(read_len>=0){printf(read_data);}
    else{printf("esp_http_client_read failed \n");}

    free(read_data);
    esp_http_client_cleanup(client);
}


int count_digits(int n) 
{ 
    int count = 0; 
    while (n != 0) { 
        n = n / 10; 
        ++count; 
    } 
    return count; 
} 

void my_http_sender_send_turbine(int turbin_id, int data[], size_t data_len){ 
    //todo: make better error handling in this function
    
    

    //todo: find out whether this should be placed outside of function. 
    esp_http_client_config_t config = {
        .url =  "http://httpbin.org/get",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

//concatenate string to send------------------------------------

    // the strings that will be concatenated:
    const char *turb = "{\"turbin\":"; 
    char turb_num[max_digits_in_turb_num]; 
    const char *verd = ",\"verdier\":\"";
    char* verd_num=malloc((data_len*2*max_digits_in_data_element+1)*sizeof(char)); // *2 pga mellomrommene
    const char *closing = "\"}"; //nb, assumes last value of the json is string. 

    //fill turb_num
    itoa(turbin_id, turb_num, 10); // ten is because we want decimal format not binary

    //fill verd_num
    char temp_verd_num[max_digits_in_data_element]; 
    strcpy(verd_num, itoa(data[0], temp_verd_num, 10) );

    for (int i = 1; i <data_len; i++)
    {
        strcat(verd_num, " ");
        itoa(data[i], temp_verd_num, 10); 
        strcat(verd_num, temp_verd_num);
    }
/*
    if((strlen(turb)+strlen(verd)+strlen(verd_num)+strlen(turb_num)+strlen(closing)+1) > 255){
        printf("error: cannot send more than 255 characters to database\n");
        return;
    }
*/
    
    char* post_data = malloc( (strlen(turb)+strlen(verd)+strlen(verd_num)+strlen(turb_num)+strlen(closing)+1)*sizeof(char) ); // the string to send. //+1 because of nul-character.
    
    strcpy(post_data, turb);
    strcat(post_data, turb_num); 
    strcat(post_data, verd); 
    strcat(post_data, verd_num); 
    strcat(post_data, closing);

//finished concatenating------------------------------------

    //post_data example value: "{\"turbin\": 11,\"verdier\":\"2\"}"
    //printf(post_data); // // todo: change to ESP_LOGI 
    

    // POST
    char *read_data = malloc(MAX_HTTP_RECV_BUFFER + 1); //the string recieved back to us from our post

    esp_http_client_set_url(client, "https://www.vibecheck.no/esptest.php");
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data)); // post data is only used here. 
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
        
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    //uncomment to print read-data
    //printf("read_data unfilled size: %d\n", sizeof(read_data)); // todo: change to ESP_LOGI
    //int read_len = esp_http_client_read(client, read_data, esp_http_client_get_content_length(client));
    //if(read_len>=0){printf(read_data);}// todo: change to ESP_LOGI
    //else{printf("esp_http_client_read failed \n");}// todo: change to ESP_LOGI

    //free everything allocated with malloc.
    free(read_data);
    free(post_data); 
    free(verd_num);

    esp_http_client_cleanup(client);

}


static void http_test_task(void *pvParameters)
{
    http_rest_with_url();
    ESP_LOGI(TAG, "Finish http example");
    vTaskDelete(NULL);
}

void http_sender_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    ESP_LOGI(TAG, "Connected to AP, begin http example");

    xTaskCreate(&http_test_task, "http_test_task", 8192, NULL, 5, NULL);
}

void my_http_sender_init(){
    esp_err_t ret = nvs_flash_init(); // to store key-value pairs in flash. (im not entirely sure where this is necessary)

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init()); // thread-safe api for TCP/IP 
    ESP_ERROR_CHECK(esp_event_loop_create_default()); //special loop for handling system events (like wifi)

    // this is determined by menuconfig. See readme. (not yet created.)
    ESP_ERROR_CHECK(example_connect()); //NB: TODO: this is an oversimplified connection-function, replace. It doesnt handle errors well.
    ESP_LOGI(TAG, "Init, Connected to AP, begin http example");

}

void print_array(int arr[], int len){
    for(int i=0; i<len; i++){
        printf("%d",arr[i]);
        printf(" ");
    }
    printf("\n");
}


//this function accepts only a digit at a time, and parses numbers splitted by commas.
void fill_my_http_buffer(int new_measurement){ // todo: vurdere om denne skal flyttes. //husk at vi max kan sende 255 characters. 
    //as it seems I can send one char at the time over bluetooth i should parse the chars here.
    //todo: parse chars here. 
    //the int new measurement is the ascii-code for the char sent.

    if (new_measurement==44) // the ascii-code for "," 
    {
        my_send_buffer[buffer_index]=buf_num;
        buffer_index++;
        //char_count+= count_digits(buf_num); char count probably not necessary. could be used if there is a char limit for how much we can send with http.
        printf("added %d to buffer \n",buf_num );
        buf_num=0;
        printf("got comma\n"); //for testing, todo: remove
    }
    else{
        printf("partial num: %d \n", new_measurement);
        buf_num=buf_num*10+(new_measurement); 
    }

    if(buffer_index  >= sizeof(my_send_buffer)/sizeof(my_send_buffer[0])){ //char_count>=255-json_padding_size-max_digits_in_data_element-10){//10 is just to overkill //
        //todo: make if-statement more dynamic and elegant
        my_http_sender_send_turbine(TURBIN_ID, my_send_buffer, sizeof(my_send_buffer)/sizeof(my_send_buffer[0]));
        buffer_index=0;
        //char_count=0;
    }


}



