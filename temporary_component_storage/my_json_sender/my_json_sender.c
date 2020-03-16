#include "my_json_sender.h"
#include "esp_wifi.h"
#include <stdio.h>

const char* my_json_string = "{
'turbine':12,
'data':'32'    
}";

void init(){
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    //ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL));
    //ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_connect();
}

