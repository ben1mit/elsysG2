// code for elsysg2 deep-sleep

/*
kconfig settings-------------------------------------
should probably not be like this in final version:
CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP selected (one must be careful with this. Not to be used in conjunction with OTA)
CONFIG_SECURE_BOOT_ENABLED disabled

kconfig settings-------------------------------------
*/

//todo: remove unecessary includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp32/ulp.h"
#include "esp_sleep.h"

#include "esp32/rom/ets_sys.h" //for ets_printf


//uncomment these includes when they become necessary. They likely will be. 
/*#include "freertos/FreeRTOS.h"
#include <time.h>
#include <sys/time.h>
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/touch_pad.h"
#include "driver/adc.h"
#include "driver/rtc_io.h"
#include "soc/sens_periph.h"
#include "soc/rtc.h"*/

//#include "esp_deepsleep.h" //has been renamed esp_sleep. is already included.


void app_main(void)
{
    static const int mega= 1000000;
    printf("entering sleep\n");
    esp_sleep_enable_timer_wakeup(5*mega);//time in microseconds.
    esp_deep_sleep_start(); // when it wakes it will reboot. should this be placed inside ESP_ERROR_CHECK()?
}


RTC_DATA_ATTR int wake_count; // loaded into rtc mem. 

// a wake stub is loaded into rtc-fast memory. Can only access data from RTC fast mem.
void RTC_IRAM_ATTR esp_wake_deep_sleep(void) { 
    esp_default_wake_deep_sleep();
    static RTC_RODATA_ATTR const char fmt_str[] = "Wake count %d\n";
    ets_printf(fmt_str, wake_count++);
}

/*
static void start_ulp_program(void){
    printf("starting ULP program\n");
    const ulp_insn_t program[]={
        // here the assembly code that the ULP will run will be placed.
    };
}
*/