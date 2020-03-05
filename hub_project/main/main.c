#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_http_sender.h"
#include "ble_spp_server_demo.h"



void app_main(void)
{
	printf("printing from my_main\n");
	//http_sender_main();

	my_http_sender_init();
/*	my_http_sender_send_turbine(3,40);
	my_http_sender_send_turbine(9,16);
	my_http_sender_send_turbine(4,32);
*/
	ble_main();

	//todo: set up task for sending. remember to delete task. 
}