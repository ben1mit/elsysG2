/**
 * @file
 * @brief this is the main file for the unit on the wing.
 * @attention 
 * some settings must be changed in makefiles and some other changes must be done. Elaborate on this later. 
 */ 

#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#include "ble_spp_server_demo.h"
#include "spp_client_demo.h"

void app_main(void)
{
	knock_init();

	int i=0;

	int previous=0;
	int present=0;
	while (true)
	{
		present=get_dunk_z();
		printf("%d,", present);
		previous=get_dunk_z();
		vTaskDelay(20 / portTICK_PERIOD_MS);

		if(i>100){i=0; printf("\n");}
	}
	

	/*
	ble_client_app_main();

	vTaskDelay(5000 / portTICK_PERIOD_MS); //necessary for initialization to settle.

	knock_init();
	int knock_counter=0;
	while (true)
	{
		if(check_dunk()){
			printf("dunk detected\n");
    		my_client_send_single_digit(knock_counter%10);
			vTaskDelay(2000 / portTICK_PERIOD_MS); //cooldown before checking next knock
			knock_counter++;
		}
		vTaskDelay(50 / portTICK_PERIOD_MS);

	}

	check_dunk();


    my_client_send_single_digit(1);

	vTaskDelay(10000 / portTICK_PERIOD_MS); //necessary for initialization to settle.

    my_client_send_single_digit(2);

	vTaskDelay(10000 / portTICK_PERIOD_MS); //necessary for initialization to settle.

	my_client_send_single_digit(3);
	*/


	//printf("printing from my_main\n");
	//ble_main();
	//http_sender_main();

	//todo: set up task for sending. remember to delete task.
}
