#include <stdio.h>
#include "my_mpu_wrapper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdcard.h"


void app_main(void)
{

	sdcard_mount();


	/*
	printf("printing from my_main\n");
	knock_init();
	while(true){
   		check_dunk();
		printf("test\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);

	}
*/
}