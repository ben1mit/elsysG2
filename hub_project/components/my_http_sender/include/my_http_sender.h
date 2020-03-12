/* 
AN EXAMPLE FILE FOR SENDING DATA TO "https://www.vibecheck.no/esptest.php",
data is sent in json format with hhtp-post and formatted into a table at the webpage. 
This is based on the esp_http_client example from esp_idf
*/

#ifndef COMPONENTS_MY_HTTP_SENDER_H_
#define COMPONENTS_MY_HTTP_SENDER_H_

void http_sender_main(void); // this is just for testing.

void my_http_sender_init(); // call this function first. (unless you call http_sender_main)
void my_http_sender_send_turbine(int turbin_id, int data[], size_t data_len); // function for sending in our specific format. can only send one int as data.
void fill_my_http_buffer(int new_measurement);
void print_array(int arr[], int len);

#endif /* COMPONENTS_MY_HTTP_SENDER_H_ */