#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "ble_spp_server_demo.h"
#include "spp_client_demo.h"

void app_main(void)
{
	ble_client_app_main();

	vTaskDelay(5000 / portTICK_PERIOD_MS); //necessary for initialization to settle.

    my_client_send_single_digit(1);

	vTaskDelay(10000 / portTICK_PERIOD_MS); //necessary for initialization to settle.
   
    my_client_send_single_digit(2);
	
	vTaskDelay(10000 / portTICK_PERIOD_MS); //necessary for initialization to settle.

	my_client_send_single_digit(3);

	//printf("printing from my_main\n");
	//ble_main();
	//http_sender_main();

	//todo: set up task for sending. remember to delete task. 
}