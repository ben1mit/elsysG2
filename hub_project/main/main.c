/**
 * @file 
 * @brief main file for the unit on the wing 
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_http_sender.h"
#include "ble_spp_server_demo.h"

// it might be relevant to change the defines in ble_spp_server.h for different kinds of testing and purpouses.
//av en eller annen grunn relayer den bare 1 når send immediately er aktivert. 


void app_main(void)
{
	//int my_values[] = {1,2,3,4,5,6,7,8,9,2};
	//print_array(my_values);
	my_http_sender_init(); // denne må gjøres på en måte som gir høyere båndbredde. Evt kan ble-main cache dataen. 
	/*for(int i=0; i<2450; i++){
		fill_my_http_buffer(i);
	}
	*/

	//http_sender_main(); // to test rest_with_url
	//my_http_sender_send_turbine(5, my_values, 10);
	ble_main();
	//todo: set up task for sending. remember to delete task. 
}

