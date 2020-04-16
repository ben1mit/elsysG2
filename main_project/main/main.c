/**
 * @mainpage
 * This is a project made for the subject "electronic system design, project II" at NTNU. \n
 * The project consists of two units: \n
 * One which detects bird-collisions at the blade of the windmill, 
 * based on vibration patterns detected with an accelerometer, and sends a signal via Blluetooth Low Energy \n
 * And a second, called the hub, which relays a signal recieved via BLE to our database via WIFI. \n \n
 * 
 * The documentation for the unit on the wing is found in main_project, and the code for the hub is found in hub_project \n
 * To understand the project, look at the documentation of the header-files (of the components) and main-files in these projects first \n \n
 * 
 * To run this project a few things must be done: \n
 * download ESP-IDF, this can be done from here: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/.
 * (Building and flashing the project is also decribed there) \n \n
 * 
 * You must also edit the file at esp-idf/components/partition_table/partitions_singleapp.csv, here "factory, app" size should be  0x180000 not 1M. \n \n
 * 
 * Menuconfig (opened by writing idf.py menuconfig in the terminal) must be set up correctly: \n
 *
 * -menuconfig on hub_project: \n
 * menuconfig -> example connection configuration, write name and password of the wifi network, 
 * also check that connect using wifi is set here, and not connect using ethernet \n
 * menuconfig -> component config -> bluetooth -> check the box (otherwise the project wont compile) \n
 * menuconfig -> component config -> ESP32-specific -> main XTAL frequency -> select autodetect \n \n
 * 
 * -menuconfig on main_project: \n
 * menuconfig -> component config -> bluetooth -> check the box (otherwise the project wont compile) \n
 * menuconfig -> component config -> ESP32-specific -> main XTAL frequency -> select autodetect \n \n
 * 
 * The source code for this project can be found here: 
 * https://github.com/ben1mit/elsysG2 \n
 * 
 *  
*/

/**
 * @file
 * @brief this is the main file for the unit on the wing.
 */ 



#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#include "ble_spp_server_demo.h"
#include "spp_client_demo.h"

/*
	//this section is the functional code inside main for the project (without sleep). 
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
*/

void app_main(void)
{
	knock_init();
	while(true){
		printf("%d\n", read_accel_byte());
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	//start_sleep_detection();
	//printf("f\n");

/*
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
	
*/


	/*
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
