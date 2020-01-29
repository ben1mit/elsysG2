#include "bird_mpu.h"

#include "I2Cbus.hpp"
#include "MPU.hpp"        // main file, provides the class itself
#include "mpu/math.hpp"   // math helper for dealing with MPU data
#include "mpu/types.hpp"  // MPU data types and definitions


MPU_t MPU;         // create an object

mpud::raw_axes_t bird_accel_raw;     // holds x, y, z axes as int16
mpud::raw_axes_t previous_accel;


esp_err_t bird_mpu_init(){ // esp_err_t er typen til feilkoden akselerometeret gir.
    i2c0.begin(SDA, SCL, CLOCK);

	MPU.setBus(i2c0);  // set communication bus, for SPI -> pass 'hspi'
	MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address or handle, for SPI -> pass 'mpu_spi_handle'
	esp_err_t err = MPU.testConnection();  // test connection with the chip, return is a error code. Returns ESP_OK if everything is right.
	if (err != ESP_OK){
		printf("failed to initialize in dunking with code: %s\n", esp_err_to_name(err));
		return err;
	}
	
	MPU.initialize();  // this will initialize the chip and set default configurations
	MPU.setSampleRate(250);  // in (Hz)
	MPU.setAccelFullScale(mpud::ACCEL_FS_4G);
	MPU.setDigitalLowPassFilter(mpud::DLPF_42HZ);  // smoother data

	return err;
    //perhaps useful later:
	// MPU.setGyroFullScale(mpud::GYRO_FS_500DPS);
	// MPU.setInterruptEnabled(mpud::INT_EN_RAWDATA_READY);  // enable INT pin
}



bool check_collision(){ //should be called frequently
    bool hit=false;

	MPU_dunk.acceleration(&bird_accel_raw);  // fetch raw data from the registers
	if( abs(bird_accel_raw.z-previous_accel.z) > BIRD_IMPACT_LIMIT){ // a single hit is detected
		hit=true;
	}
	previous_accel =bird_accel_raw; 
	return hit;
}
