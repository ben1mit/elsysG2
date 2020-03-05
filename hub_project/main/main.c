#include <stdio.h>
//#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_http_sender.h"
#include "ble_spp_server_demo.h"



void app_main(void)
{
	my_http_sender_init(); // denne må gjøres på en måte som gir høyere båndbredde. Evt kan ble-main cache dataen. 
	ble_main();
	//todo: set up task for sending. remember to delete task. 
}

