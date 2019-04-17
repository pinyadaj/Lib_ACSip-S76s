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

acsip_ret_t sip_get_hw_model_acsip(char *rep_buf, uint16_t len_max);

acsip_ret_t sip_set_echo_acsip(int8_t on);

acsip_ret_t sip_set_log_info_acsip(void);

acsip_ret_t sip_sleep_acsip (int16_t time, uint8_t uart_on);

acsip_ret_t sip_set_baudrate_acsip(uint32_t baudrate, char *password);

acsip_ret_t sip_get_hw_model_ver_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t sip_set_gpio_mode_acsip(char *gpio_group, uint8_t gpio_pin_num, uint8_t gpio_mode);

acsip_ret_t sip_set_gpio_acsip(char *gpio_group, uint8_t gpio_pin_num, uint8_t gpio_val);

acsip_ret_t sip_get_gpio_acsip (char *gpio_group, uint8_t gpio_pin_num, char *rep_buf, uint16_t len_max);

acsip_ret_t sip_get_uuid_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t sip_set_storage_acsip(char *eeprom_encrypted);

acsip_ret_t sip_get_storage_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t sip_set_iap_acsip(uint8_t on);

acsip_ret_t sip_set_iap_mode_acsip(uint8_t mode);


// * * * * * MAC * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t mac_tx_acsip(char *type, int8_t port_num, uint8_t *data, uint32_t len);

acsip_ret_t mac_join_acsip(char *mode, char *rep_buf, uint16_t len_max);

acsip_ret_t mac_save_acsip(void);

acsip_ret_t mac_get_join_status_acsip(char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_linkchk_acsip(void);

acsip_ret_t mac_set_deveui_acsip(char *deveui);

acsip_ret_t mac_set_appeui_acsip(char *appeui);

acsip_ret_t mac_set_appkey_acsip(char *appkey);

acsip_ret_t mac_set_devaddr_acsip(char *devaddr);

acsip_ret_t mac_set_nwkskey_acsip(char *nwkskey);

acsip_ret_t mac_set_appskey_acsip(char *appskey);

acsip_ret_t mac_set_power_acsip(char *power);

acsip_ret_t mac_set_dr_acsip(char *datarate);

acsip_ret_t mac_set_adr_acsip(uint8_t on);

acsip_ret_t mac_set_txretry_acsip(uint8_t retrycount);

acsip_ret_t mac_set_rxdelay1_acsip(uint16_t delay);

acsip_ret_t mac_set_rx2_acsip(uint8_t dataRate, uint32_t freq);

acsip_ret_t mac_set_sync_acsip (uint8_t syncWord);

acsip_ret_t mac_set_ch_freq_acsip(int8_t ch, uint32_t freq);

acsip_ret_t mac_set_ch_dr_range(int8_t channelid, int8_t mindr, int8_t maxdr);

acsip_ret_t mac_set_ch_status_acsip(uint8_t channelid, uint8_t status);

acsip_ret_t mac_set_dc_ctl_acsip(uint8_t status);

acsip_ret_t mac_set_join_ch_acsip(uint8_t channelid, uint8_t status);

acsip_ret_t mac_set_upcnt_acsip(int32_t uplinkcounter);

acsip_ret_t mac_set_downcnt_acsip(int32_t downlinkcounter);

acsip_ret_t mac_set_class_acsip(uint8_t class);

acsip_ret_t mac_get_devaddr_acsip(char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_deveui_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_appeuii_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_nwkskey_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_appskey_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_appkey_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_dr_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_band_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_power_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_adr_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_txretry_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_rxdelay_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_rx2_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_sync_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_ch_para_acsip (uint8_t channelid, char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_ch_status_acsip (uint8_t channelid, char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_dc_ctl_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_dc_band_acsip (uint8_t bandid, char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_join_ch_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_upcnt_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_downcnt_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_get_class_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_tx_mode_acsip(uint8_t cycle);

acsip_ret_t mac_get_tx_mode_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_batt_acsip(int8_t battery);

acsip_ret_t mac_get_batt_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_tx_confirm_acsip(uint8_t confirm);

acsip_ret_t mac_get_tx_confirm_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_claa_acsip(int8_t claamode);

acsip_ret_t mac_get_claa_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_getchinfo_acsip(void);

acsip_ret_t mac_set_gettimeinfo_acsip(void);

acsip_ret_t mac_set_jumboframe_acsip(void);

acsip_ret_t mac_set_lbt_acsip(uint8_t on);

acsip_ret_t mac_get_lbt_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_uplink_dwell_acsip(uint8_t on);

acsip_ret_t mac_get_uplink_dwell_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_downlink_dwell_acsip(uint8_t on);

acsip_ret_t mac_get_downlink_dwell_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_max_eirp_acsip(int8_t maxeirp);

acsip_ret_t mac_get_max_eirp_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_ch_count_acsip(uint8_t channelscount, uint8_t bw);

acsip_ret_t mac_get_ch_count_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_keys_acsip(char *devaddr, char *deveui, char *appeui, char *appkey, char *appskey, char *nwkskey);

acsip_ret_t mac_set_tx_interval_acsip(int32_t interval);

acsip_ret_t mac_get_tx_interval_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_rx1_freq_acsip(int32_t rx1_freq_begin, int32_t rx1_step, int32_t rx1_count);

acsip_ret_t mac_get_rx1_freq_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t mac_set_auto_join_acsip(uint8_t on, uint8_t join_type, uint16_t join_count);

acsip_ret_t mac_get_auto_join_acsip (char *rep_buf, uint16_t len_max);


// * * * * * RF * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t rf tx_acsip(uint8_t *data, uint32_t len);

acsip_ret_t rf_set_freq_acsip(int32_t frequency);

acsip_ret_t rf_set_pwr_acsip(int8_t power);

acsip_ret_t rf_set_sf_acsip(int8_t spreadingfactor);

acsip_ret_t rf_set_bw_acsip(int16_t spreadingfactor);

acsip_ret_t rf_set_cr_acsip(int8_t *codingRate);

acsip_ret_t rf_set_prlen_acsip(int16_t PreambleLength);

acsip_ret_t rf_set_crc_acsip(uint8_t on);

acsip_ret_t rf_set_iqi_acsip(uint8_t on);

acsip_ret_t rf_set_sync_acsip(int8_t syncword);

acsip_ret_t rf_save_acsip(void);

acsip_ret_t rf_get_freq_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_pwr_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_sf_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_bw_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_prlen_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_crc_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_iqi_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_cr_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_get_sync_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_rx_con_acsip(uint8_t on);

acsip_ret_t rf_fsk_acsip(uint8_t on);

acsip_ret_t rf_lora_tx_start_acsip(int32_t times, int32_t interval, char *data);

acsip_ret_t rf_lora_tx_stop_acsip(void);

acsip_ret_t rf_lora_rx_stop_acsip(void);

acsip_ret_t rf_set_fdev_acsip(int16_t freqdeviation);

acsip_ret_t rf_get_fdev_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_set_cad_acsip(uint8_t on);

acsip_ret_t rf_get_cad_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rf_cad_acsip(int32_t frequency, uint8_t sf, uint16_t bw, uint8_t syncword, uint8_t skiprx);


// * * * * * RM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t rm_set_gpio_acsip(char *dir, uint8_t serial_num, char *pin_group, uint8_t pin_name);

acsip_ret_t rm_get_gpio_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_gpio_swtich_acsip(uint8_t on);

acsip_ret_t rm_get_gpio_swtich_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_adc_acsip(uint8_t serial_num, uint8_t on);

acsip_ret_t rm_get_adc_acsip (uint8_t serial_num, char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_adc_switch_acsip(uint8_t on);

acsip_ret_t rm_get_adc_switch_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_port_uplink_acsip(uint8_t port);

acsip_ret_t rm_set_port_downlink_acsip(uint8_t port);

acsip_ret_t rm_get_port_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_mode_acsip(char *mode);

acsip_ret_t rm_get_mode_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t rm_set_trigger_acsip(char *pin_group, uint8_t pin_num, char *trig_type);

acsip_ret_t rm_get_trigger_acsip (char *rep_buf, uint16_t len_max);


// * * * * * GPS * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

acsip_ret_t gps_set_level_shift_acsip(int8_t on);

acsip_ret_t gps_set_nmea_rmc_acsip(void);

acsip_ret_t gps_set_port_uplink_acsip(char *port);

acsip_ret_t gps_set_format_uplink_acsip(char *format);

acsip_ret_t gps_set_positioning_cycle_acsip(uint32_t time);

acsip_ret_t gps_set_mode_acsip(char *mode);

acsip_ret_t gps_get_mode_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t gps_get_data_acsip (char *req_buf, char *rep_buf, uint16_t len_max);

acsip_ret_t gps_sleep_acsip(int8_t on, int8_t sleep_lev);

acsip_ret_t gps_get_ttff_acsip (char *rep_buf, uint16_t len_max);

acsip_ret_t gps_reset_acsip(void);

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
