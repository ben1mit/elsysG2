/**
 * @file 
 * @brief a wrapper library for the mpu, necessary since the MPU-driver is written in c++
 * here we also implement helper functions for detecting hits.
 * documentation for the MPU-driver can be found here: https://esp32-mpu-driver.readthedocs.io/en/latest/ 
 * (the MPU-driver is a component in the project, but excluded from documentation as it has its own documentation)
 */ 

#ifndef COMPONENTS_MY_MPU_WRAPPER_H_
#define COMPONENTS_MY_MPU_WRAPPER_H_

//#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDA GPIO_NUM_22
#define SCL GPIO_NUM_19
#define CLOCK 100000

#define CONFIG_MY_MPU_KNOCK_LIMIT 2000

/**
 * @brief initialization function for MPU. 
 */
void knock_init(); 

/**
 * @brief checks if the difference of two consequtive 
 * measurements (in z-direction) passes the threshold set in @c CONFIG_MY_MPU_KNOCK_LIMIT 
 */ 
int check_dunk(); 

/**
 * @brief returns raw data of z-acceleration.
 */ 
int get_dunk_z();

#ifdef __cplusplus
}
#endif

#endif /* COMPONENTS_MY_MPU_WRAPPER_H_ */