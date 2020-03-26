/**
 * @file 
 * @brief library for sending data over bluetooth low energy
 * @note this might be very suboptimal for fast connection.
 * this file is largely based on the example found at esp-idf/examples/bluetooth/bluedroid/ble/ble_spp_client
 */

#ifndef COMPONENTS_SPP_CLIENT_DEMO_H_
#define COMPONENTS_SPP_CLIENT_DEMO_H_

/**
 * @brief initialization function for BLE sending. Must be called before anything else in this library works.
 */ 
void ble_client_app_main(); //TODO: change name

/**
 * @brief a function for sending a number with multiple digits over BLE in special format.
 * it sends one digit at a time, and at the end of the number sends a comma. 
 */ 
void my_client_send_multiple_digits(int num_to_send); //todo: change to more elegant format using bitshifting. 

/**
 * @brief a function that sends a single digit over BLE.
 */ 
void my_client_send_single_digit(int num_to_send);

#endif /* COMPONENTS_SPP_CLIENT_DEMO_H_ */