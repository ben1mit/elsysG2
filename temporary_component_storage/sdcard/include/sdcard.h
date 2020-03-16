/*
 * sdcard.h
 *
 *  Created on: Nov 7, 2019
 *      Author: gusta
 */

#ifndef MAIN_SDCARD_H_
#define MAIN_SDCARD_H_

#define PIN_NUM_MISO 2
#define PIN_NUM_MOSI 15
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   13

#include "esp_err.h"

esp_err_t sdcard_mount();
void sdcard_unmount();

#endif /* MAIN_SDCARD_H_ */
