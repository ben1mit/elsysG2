#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//#include "esp_system.h"
//#include "sdkconfig.h"
//#include "esp_spi_flash.h"
#include <math.h>

#include "I2Cbus.hpp"
#include "MPU.hpp"        // main file, provides the class itself
#include "mpu/math.hpp"   // math helper for dealing with MPU data
#include "mpu/types.hpp"  // MPU data types and definitions

#include "my_mpu_wrapper.h"

#define CONFIG_MY_MPU_KNOCK_LIMIT 700

MPU_t MPU_dunk;         // create an object

mpud::raw_axes_t accelRaw_dunk;     // holds x, y, z axes as int16
mpud::raw_axes_t gyroRaw_dunk;      // holds x, y, z axes as int16

int previous_acc=0;

void knock_init(){
	i2c0.begin(SDA, SCL, CLOCK);

	MPU_dunk.setBus(i2c0);  // set communication bus, for SPI -> pass 'hspi'
	MPU_dunk.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address or handle, for SPI -> pass 'mpu_spi_handle'
	esp_err_t err = MPU_dunk.testConnection();  // test connection with the chip, return is a error code. Returns ESP_OK if everything is right.
	if (err != ESP_OK)
	{
		printf("failed to initialize in dunking with code: %s\n", esp_err_to_name(err));
		//return false;
	}
	
	MPU_dunk.initialize();  // this will initialize the chip and set default configurations
	MPU_dunk.setSampleRate(250);  // in (Hz)
	MPU_dunk.setAccelFullScale(mpud::ACCEL_FS_4G);
	MPU_dunk.setGyroFullScale(mpud::GYRO_FS_500DPS);
	MPU_dunk.setDigitalLowPassFilter(mpud::DLPF_42HZ);  // smoother data
	MPU_dunk.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY);  // enable INT pin

	//return true;
}

int check_dunk(){

	MPU_dunk.acceleration(&accelRaw_dunk);  // fetch raw data from the registers
	MPU_dunk.rotation(&gyroRaw_dunk);       // fetch raw data from the registers
  
    if( abs(accelRaw_dunk.z-previous_acc) > CONFIG_MY_MPU_KNOCK_LIMIT){ // a single knock is detected
		previous_acc=accelRaw_dunk.z;
		return 1;
    }
	previous_acc=accelRaw_dunk.z;
	return 0;
}

int get_dunk_y(){
	MPU_dunk.acceleration(&accelRaw_dunk);  // fetch raw data from the registers
    return accelRaw_dunk.z;
}

//annen info:

//strengt tatt er det ikke lenger nødvedig å kompensere for jordakselerasjonen lenger, men jeg har valgt å beholde det.

//ting man kan printe om man vil teste litt:
//printf("angle : %+.2f ", 90* (2/3.1415)* gravity_angle_rad);
//printf("delta acceleration : %+.2f \n",  delta_acc);
//printf("accel: %+d %+d %+d\n", accelRaw_dunk.x, accelRaw_dunk.y, accelRaw_dunk.z);
//printf("gyro: %+d %+d %+d\n", gyroRaw_dunk[0], gyroRaw_dunk[1], gyroRaw_dunk[2]);

/*printf("dunk dunk ");
printf("%d", dunk_count);
printf("\n");

printf("time ");
printf("%f", time_count);
printf("\n");

printf("time since check ");
printf("%f", time_since_last_check);
printf("\n");
*/
//printf("delta_acc; %f , angle: %f , compensation %f \n", delta_acc, gravity_angle_rad, ANGLE_COMPENSATION * cos(gravity_angle_rad) );


/*
printf(" compensation ");
printf("%f", ANGLE_COMPENSATION * cos(gravity_angle_rad) );
printf("\n");
printf("\n");
*/