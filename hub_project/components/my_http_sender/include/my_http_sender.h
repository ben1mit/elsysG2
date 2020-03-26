/**
 * @file
 * @brief a file for sending data to "https://www.vibecheck.no/esptest.php"
 * @note data is sent in json format with hhtp-post and formatted into a table at the webpage. 
* This is based on the esp_http_client example from sepressif found at esp-idf/examples/protocols/esp_http_client
*/

#ifndef COMPONENTS_MY_HTTP_SENDER_H_
#define COMPONENTS_MY_HTTP_SENDER_H_

#define TURBIN_ID 1 //used in ble and fill_my_http_buffer_digit

//todo: add define for adress to send data to.

/**
 * @brief function solely used for testing 
 */ 
void http_sender_main(void); // this is just for testing.

/**
 * @brief initialization function for initializing wifi
 */ 
void my_http_sender_init(); // call this function first. (unless you call http_sender_main)

/**
 * @brief function for sending data in json format to the database (https://www.vibecheck.no/esptest.php)
 * 
 * example of json string sent with turbin_id=1 and data=[34,2,6]: 
 * {"turbin": 1 , "verdier": "34 2 6"}
 *  
 * @param[in] turbin_id a unique identifier for which windmill is sent from.
 * @param[in] data an array of ints to send
 * @param[in] data_len the number of elements in data 
 */ 
void my_http_sender_send_turbine(int turbin_id, int data[], size_t data_len); // function for sending in our specific format.

/**
 * @brief a function for adding digits recieved in the format described in my_client_send_multiple_digits in main_project to an http-buffer
 * this does not add "new_measurement" to the buffer. 
 * Instead it treats it as a single digit in a larger number, where all the numbers are seperated with commas.
 * When the buffer is full it sends all its content using @c my_http_sender_send_turbine
 * @warning this does not add "new_measurement" to the buffer!
 */ 
void fill_my_http_buffer_digit(int new_measurement);

/**
 * @brief a function for printing an array (with printf), only for debugging
 * @param[in] arr the array to be printed
 * @param[in] len the number of elements in the array 
 */
void print_array(int arr[], int len);

#endif /* COMPONENTS_MY_HTTP_SENDER_H_ */