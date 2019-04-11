//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : acsip-lorawan-lib.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : npr.ninsamran@gmail.com
//; Objective	 : ACSIP LoRaWan Library Definition
//; Create(dd/mm/yy) : 07/02/2019
//; [Revision and Description]
//; Rev1.0 - 07/02/2019: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _ACSIP_LORAWAN_LIB_H
#define _ACSIP_LORAWAN_LIB_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "stm32l4xx.h"
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
#include "main.h"
#include "common.h"

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
#define SEND_AT_TRY_MAX             (3)

#define SEND_CRLF_TO_MODEM()        os_puts_uart2("\r\n")

#define SEND_STRING_TO_MODEM(D)     os_puts_uart2(D)

#define SEND_AT_CMD_TO_MODEM(D)     os_puts_uart2(D);\
                                    SEND_CRLF_TO_MODEM()

#define ACSIP_VER		"v1.6.5-g9"
#define HW_DEVEUI		"9c65f9fffe0a8262"
#define UCNF_TYPE		"ucnf"
#define CNF_TYPE		"cnf"
#define ABP_MODE		"abp"
#define OTAA_MODE		"otaa"

#define GPS_UPLINK_RAW	"raw"
#define GPS_UPLINK_IPSO	"ipso"
#define GPS_UPLINK_KIWI	"kiwi"
#define GPS_AUTO_MODE	"auto"
#define GPS_MANUAL_MODE "manual"
#define GPS_IDLE_MODE 	"idle"
#define GPS_RAW_DATA	"raw"
#define GPS_DD_DATA		"dd"
#define GPS_DMS_DATA	"dms"
#define BAUDRATE_9600   	9600
#define BAUDRATE_19200   	19200
#define BAUDRATE_57600	 	57600
#define BAUDRATE_115200		115200

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 3. Public Variable Definition
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
typedef enum {
	ACSIP_RX_SOF1_STA = 0,
	ACSIP_RX_SOF2_STA,
	ACSIP_RX_SOF3_STA,
	ACSIP_RX_DATA_STA
} acsip_rx_state_t;

typedef enum {
    ACSIP_OK_RET  = 0x00,
	ACSIP_BUFFER_OVERFLOW_RET  = -1,
	ACSIP_TIMEOUT_RET  = -2,
	ACSIP_FRAME_ERROR_RET = -3
} acsip_ret_t;  //type of return code

/* 4.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 4.4. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # # */  


//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
//@
//@ Section 5. Interrupt Service Routine
//@
//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 6. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

char* transfer_acsip (char* reqStr, char* ackStr, uint16_t tmout, int8_t crlf);

acsip_ret_t get_acsip (char* reqStr, char* filterStr, char *rep_buf, uint16_t rep_len_max, uint32_t tmout);


// * * * * * SIP * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t sip_factory_reset_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t sip_get_ver_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t sip_get_hw_deveui_acsip(char *rep_buf, uint16_t len_max);

acsip_ret_t sip_reset_acsip(void);

acsip_ret_t sip_set_echo_acsip(int8_t on);


// * * * * * MAC * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t mac_tx_acsip(char *type, int8_t port_num, uint8_t *data, uint32_t len);

acsip_ret_t mac_join_acsip(char *mode, char *rep_buf, uint16_t len_max);

acsip_ret_t mac_save_acsip(void);

acsip_ret_t mac_get_join_status_acsip(char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_deveui_acsip(char *deveui);

acsip_ret_t mac_set_appeui_acsip(char *appeui);

acsip_ret_t mac_set_appkey_acsip(char *appkey);

acsip_ret_t mac_set_devaddr_acsip(char *devaddr);

acsip_ret_t mac_set_nwkskey_acsip(char *nwkskey);

acsip_ret_t mac_set_appskey_acsip(char *appskey);

acsip_ret_t mac_set_freq_acsip(int8_t ch, uint32_t freq);

acsip_ret_t mac_get_deveui_acsip (char *rep_buf, uint16_t len_max);


// * * * * * GPS * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t gps_set_level_shift_acsip(int8_t on);

acsip_ret_t gps_set_nmea_rmc_acsip(void);

acsip_ret_t gps_set_port_uplink_acsip(char *port);

acsip_ret_t gps_set_format_uplink_acsip(char *format);

acsip_ret_t gps_set_positioning_cycle_acsip(uint32_t time);

acsip_ret_t gps_set_mode_acsip(char *mode);

acsip_ret_t gps_get_mode_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t gps_get_data_acsip (char *req_buf, char *rep_buf, uint16_t len_max);


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 7. Private Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 7.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int16_t bytesToHexStr(uint8_t *buf_in, int32_t len_in, uint8_t *buf_out, int32_t len_out);



/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */


/* 7.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif

#endif	//_ACSIP_LORAWAN_LIB_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
