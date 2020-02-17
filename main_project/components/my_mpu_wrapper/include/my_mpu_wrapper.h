#ifndef COMPONENTS_MY_MPU_WRAPPER_H_
#define COMPONENTS_MY_MPU_WRAPPER_H_

//#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SDA GPIO_NUM_22
#define SCL GPIO_NUM_19
#define CLOCK 100000

void knock_init(); 
int check_dunk(); 

int get_dunk_y();

#ifdef __cplusplus
}
#endif

#endif /* COMPONENTS_MY_MPU_WRAPPER_H_ */
