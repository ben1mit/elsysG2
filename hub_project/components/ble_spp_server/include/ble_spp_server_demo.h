/**
 * @file
 * @brief ble_spp_server_demo, a library for recieving data to be relayed on the hub 
 * largely based on the example from espressif found at esp-idf/examples/bluetooth/bluedroid/ble/ble_spp_server 
 */ 

/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * DEFINES
 ****************************************************************************************
 */
//#define SUPPORT_HEARTBEAT
//#define SPP_DEBUG_MODE

#define spp_sprintf(s,...)         sprintf((char*)(s), ##__VA_ARGS__)
#define SPP_DATA_MAX_LEN           (512)
#define SPP_CMD_MAX_LEN            (20)
#define SPP_STATUS_MAX_LEN         (20)
#define SPP_DATA_BUFF_MAX_LEN      (2*1024)
///Attributes State Machine
enum{
    SPP_IDX_SVC,

    SPP_IDX_SPP_DATA_RECV_CHAR,
    SPP_IDX_SPP_DATA_RECV_VAL,

    SPP_IDX_SPP_DATA_NOTIFY_CHAR,
    SPP_IDX_SPP_DATA_NTY_VAL,
    SPP_IDX_SPP_DATA_NTF_CFG,

    SPP_IDX_SPP_COMMAND_CHAR,
    SPP_IDX_SPP_COMMAND_VAL,

    SPP_IDX_SPP_STATUS_CHAR,
    SPP_IDX_SPP_STATUS_VAL,
    SPP_IDX_SPP_STATUS_CFG,

#ifdef SUPPORT_HEARTBEAT
    SPP_IDX_SPP_HEARTBEAT_CHAR,
    SPP_IDX_SPP_HEARTBEAT_VAL,
    SPP_IDX_SPP_HEARTBEAT_CFG,
#endif

    SPP_IDX_NB,
};


#define SEND_IMMEDIATELY true //if this is the case we assume only a single digit is recieved, and no parsing needed
                            // this controls what kind of sending-function is used.
                            //it should be true if we immediately want to send that digit.

/**
 * @brief this is the function that handles all bluetooth-related activities on the hub
 * @note when it recieves data it calls @c my_http_sender_send_turbine if @c SEND_IMMEDIATELY is true and @c fill_my_http_buffer_digit 
 * with the single digit recieved over BLE as a parameter if @c SEND_IMMEDIATELY is false.
 * @warning does not initialize nvs, since that is done in @c my_http_sender_init , and thus it is important to call that function first.
 */ 
void ble_main(void);