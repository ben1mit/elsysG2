#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "ble_spp_server_demo.h"
#include "spp_client_demo.h"

void app_main(void)
{
	ble_client_app_main();
	//printf("printing from my_main\n");
	//ble_main();
	//http_sender_main();



/*
	my_http_sender_init();
	printf("past init in main");
	my_http_sender_send_turbine(3,40);
	my_http_sender_send_turbine(9,16);
	my_http_sender_send_turbine(4,32);
*/
	//todo: set up task for sending. remember to delete task. 
}