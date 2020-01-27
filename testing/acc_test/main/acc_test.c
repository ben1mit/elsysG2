#include <stdio.h>
//#include <math.h>
//#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{
	while (1)
	{
		printf("acc test \n");
		vTaskDelay(500/portTICK_RATE_MS);
	}
}