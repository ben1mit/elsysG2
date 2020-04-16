/**
 * @file
 * @brief implementation file for mpu-wrapper
 */ 

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

//for configuring the sleep of the mpu. 
#define WAKEUP_RATE mpud::LP_ACCEL_RATE_40HZ
#define WAKEUP_THRESHOLD 255 // in LSB.  1LSB = 32mg, 255LSB = 8160mg
#define WAKEUP_TIME_LIMIT 10 // in ms how long must acceleration exceed limit before it triggers wakeup.


MPU_t MPU_dunk;         // create an object

mpud::raw_axes_t accelRaw_dunk;     // holds x, y, z axes as int16
mpud::raw_axes_t gyroRaw_dunk;      // holds x, y, z axes as int16

int previous_acc=0;

void knock_init(){
	i2c0.begin(SDA, SCL, CLOCK);
 
	MPU_dunk.setBus(i2c0);  // set communication bus, for SPI -> pass 'hspi'
	MPU_dunk.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address or handle, for SPI -> pass 'mpu_spi_handle'
	esp_err_t err = MPU_dunk.testConnection();  // test connection with the chip, return is a error code. Returns ESP_OK if everything is right.
	if (err != ESP_OK) //todo: make this return an error code.
	{
		printf("failed to initialize in dunking with code: %s\n", esp_err_to_name(err));
		//return false;
	}
	
	MPU_dunk.initialize();  // this will initialize the chip and set default configurations
	MPU_dunk.setSampleRate(250);  // in (Hz)
	MPU_dunk.setAccelFullScale(mpud::ACCEL_FS_4G); //todo: check if more convienient to have it be 2g.
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

int get_dunk_z(){
	MPU_dunk.acceleration(&accelRaw_dunk);  // fetch raw data from the registers
    return accelRaw_dunk.z;
}

mpud::types::mot_config_t my_motion_conf = {WAKEUP_THRESHOLD, WAKEUP_TIME_LIMIT};


void start_sleep_detection(){
	//printf("a\n");
	MPU_dunk.setLowPowerAccelMode(true); //Enter Low Power Accelerometer mode
	//printf("b\n");
	MPU_dunk.setLowPowerAccelRate(WAKEUP_RATE); //Select the wake-up rate 
	//printf("c\n");
	MPU_dunk.setMotionDetectConfig(my_motion_conf);//Configure motion-detect interrupt. 
	//printf("d\n");
 	MPU_dunk.setMotionFeatureEnabled(true);//Enable the motion detection module 
	//printf("e\n");
}


uint8_t read_accel_byte(){
	//uint8_t data_buffer = 0;
	//const uint8_t reg_addr = 63; // 0x3f, z-out øvre åtte bits.

	// this works for reading from the register 
	//MPU_dunk.readByte(reg_addr, &data_buffer);  //contents of mpu.read_byte : return err = bus->readByte(addr, regAddr, data);

	//this also works for reading the register
	//i2c0.readByte(mpud::MPU_I2CADDRESS_AD0_LOW, reg_addr, &data_buffer);

//basert på readBytes (fungerer) ----------------------------------------------------

	//deklarering av argumenter som ville ha blitt satt inn i readBytes:
	const uint8_t devAddr = mpud::MPU_I2CADDRESS_AD0_LOW;
	const uint8_t regAddr = 63; // 0x3f, z-out øvre åtte bits.
	const size_t length = 1; //vi leser bare én byte
	uint8_t data_content=0; //in order to properly declare data.
	uint8_t *data = &data_content; 
	const int32_t timeout = -1; //default argument

	const bool ack_en = true; //replaces I2C_MASTER_ACK_EN, which is defined in i2cbus.cpp

	//const mpu_bus_t port = i2c0; // ganske sikker på at porten er port 0. //i mpuTtypes.hpp har vi typedef I2C_t mpu_bus_t; 
	const uint32_t ticksToWait = pdMS_TO_TICKS(1000); //default er 1000ms.
	//bytter ut port med MPU_DEFAULT_BUS med i2c0
	int port=0;//prøver å sette port til 0

/*
	//kopiert fra I2C::readBytes(uint8_t devAddr, uint8_t regAddr, size_t length, uint8_t *data, int32_t timeout)
	//link create og delete kan by på problemer i ULP-kode. 
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, ack_en);
    i2c_master_write_byte(cmd, regAddr, ack_en);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_READ, ack_en);
    i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(port, cmd, (timeout < 0 ? ticksToWait : pdMS_TO_TICKS(timeout))); //timeouten kan by på problemer
    i2c_cmd_link_delete(cmd);
*/

//basert på readBytes ----------------------------------------------------


//forsøk på ren direkte lesing--------------------------------------------

//jeg burde ta utgangspunkt i i2c ulp eksempel.

//forsøk på re direkte lesing--------------------------------------------
	return *data; //data_buffer;

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