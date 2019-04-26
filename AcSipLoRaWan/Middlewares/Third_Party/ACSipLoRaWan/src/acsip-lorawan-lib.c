//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : acsip-lorawan-lib.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : npr.ninsamran@gmail.com
//; Objective	 : ACSIP LoRaWan Library Implementation
//; Create(dd/mm/yy) : 07/02/2019
//; [Revision and Description]
//; Rev1.0 - 07/02/2019: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "acsip-lorawan-lib.h"
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */


/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
static char modem_buf[512];
uint8_t debug = 1;
acsip_ret_t return_code =  ACSIP_OK_RET;

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */


/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */


//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */


/* 5.3. Helper function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */


//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
//@
//@ Section 6. Interrupt Service Routine
//@
//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 7. Public Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 7.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

int16_t read_ack_uart2_blocked (int16_t fd, char* buf_pt, int32_t max_buf, int32_t tmout) {
int16_t len_cnt = 0;
uint32_t tick_byt_timeout = 0;
uint32_t prev_tick_byt_timeout = 0;
char* tmp_buf_pt;
uint8_t tmp_buf;
acsip_rx_state_t acsip_rx_state;

    tmp_buf_pt = buf_pt;

    prev_tick_byt_timeout = tick_byt_timeout = tick_sys;

    acsip_rx_state = ACSIP_RX_SOF1_STA;

    while (1) {
        // get timebase
        tick_byt_timeout = tick_sys;

        if ((tick_byt_timeout - prev_tick_byt_timeout) >= tmout) {
            *buf_pt = '\0';
            return -2;
        }

        // read data form uart2 queue
        if (os_getc_uart2(&tmp_buf, 5) == pdTRUE) {



            prev_tick_byt_timeout = tick_byt_timeout;
			switch (acsip_rx_state) {
				  case ACSIP_RX_SOF1_STA:
					  if (tmp_buf == (uint8_t)'>') {
						  len_cnt = 0;
						  *buf_pt = '\0';
						  acsip_rx_state = ACSIP_RX_SOF2_STA;
						//  LOG_INFO("ACSIP_RX_SOF1_STA-->OK");
					  }
					  break;

				  case ACSIP_RX_SOF2_STA:
					  if (tmp_buf == (uint8_t)'>') {
						  acsip_rx_state = ACSIP_RX_SOF3_STA;
						//  LOG_INFO("ACSIP_RX_SOF2_STA-->OK");
					  }
					  else {
						  acsip_rx_state = ACSIP_RX_SOF1_STA;
					  }
					  break;

				  case ACSIP_RX_SOF3_STA:
					  if (tmp_buf == (uint8_t)' ') {
						  acsip_rx_state = ACSIP_RX_DATA_STA;
						//  LOG_INFO("ACSIP_RX_SOF3_STA-->OK");
					  }
					  else {
						  acsip_rx_state = ACSIP_RX_SOF1_STA;
					  }
					  break;

				  case ACSIP_RX_DATA_STA:
					  if (len_cnt >= max_buf) {
						  len_cnt = 0;
						  buf_pt[0] = '\0';
						  return -1;
					  }

					  if (tmp_buf == (uint8_t)'\n') {
						  *tmp_buf_pt = '\0';
						 // LOG_INFO("ACSIP_RX_DATA_STA-->OK");
						  return len_cnt;
					  }

					  *tmp_buf_pt = (uint8_t) tmp_buf;
					  tmp_buf_pt++;
					  len_cnt++;

					  break;

				  default:
					  acsip_rx_state = ACSIP_RX_SOF1_STA;
					  break;
			}
        }
    }

    return len_cnt;
}


acsip_ret_t get_return_code(void) {
	return return_code;
}

void set_return_code(acsip_ret_t ret) {
	return_code = ret;
}

char* transfer_acsip (char* reqStr, char* ackStr, uint16_t tmout, int8_t crlf) {
char* ret_pt = NULL;
uint16_t ret_num = 0;

	for (int try_cnt = 0; try_cnt < SEND_AT_TRY_MAX; try_cnt++) {

		if (reqStr != NULL) {
			if (crlf) {SEND_AT_CMD_TO_MODEM(reqStr);}
			else {SEND_STRING_TO_MODEM(reqStr);}

			if (debug) {
				LOG_INFO("\r\n\r\n[DEBUG]: SND={ %s }\r\n",reqStr);
			}
		}
		else {
			if (debug) {
				LOG_INFO("\r\n\r\n[DEBUG]: SND.=\r\n");
			}
		}

		if (tmout == 0) {
			set_return_code(ACSIP_TIMEOUT_RET);
			break;
		}

		memset (modem_buf, 0, sizeof(modem_buf));

		ret_num = read_ack_uart2_blocked (0, modem_buf, sizeof(modem_buf), tmout);

		if (ret_num > 0) {
			set_return_code(ACSIP_OK_RET);

			ret_pt = modem_buf;

			if (ackStr != NULL) {
				ret_pt = strstr(modem_buf, ackStr);
				if(ret_pt == NULL) {
					set_return_code(ACSIP_TIMEOUT_RET);
					ret_pt = NULL;
					if (debug) LOG_INFO("[DEBUG]: RCV_FILTER = {\r\n%s\r\n}\r\n", modem_buf);
				}
				else {
					if (debug) LOG_INFO("[DEBUG]: RCV_FILTER = {\r\n%s\r\n}\r\n", ret_pt);
					return ret_pt;
				}
			}
			else {
				if (debug){
					LOG_INFO("[DEBUG]: RCV={\r\n%s\r\n}\r\n", modem_buf);
				}
				return ret_pt;
			}
		}
		else if (ret_num == -1) {
			set_return_code(ACSIP_BUFFER_OVERFLOW_RET);

			if (debug) {
				LOG_INFO("\r\n\r\n[DEBUG]: RCV: Buffer Overflow..(T_T)\r\n");
			}
		}
		else if (ret_num == -2) {
			set_return_code(ACSIP_TIMEOUT_RET);

			if (debug) {
				LOG_INFO("\r\n\r\n[DEBUG]: RCV: Timeout Occur..(T_T)\r\n");
			}
		}
	}

	 return ret_pt;
}

acsip_ret_t get_acsip (char* reqStr, char* filterStr, char *rep_buf, uint16_t rep_len_max, uint32_t tmout){
	*rep_buf = '\0';

	char* ret_str = transfer_acsip(reqStr, filterStr, tmout, 0);

	if (ret_str != NULL) {
		if ((rep_buf == NULL) || (rep_len_max <= strlen(ret_str))){
			set_return_code(ACSIP_BUFFER_OVERFLOW_RET);
		}else {
			strcpy(rep_buf, ret_str);
		}
	}

	return get_return_code();
}

// ************ SIP commands ************

acsip_ret_t sip_factory_reset_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("sip factory_reset", NULL, rep_buf, len_max, 5000);
}

acsip_ret_t sip_get_ver_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("sip get_ver", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_get_hw_deveui_acsip(char *rep_buf, uint16_t len_max) {
	return get_acsip("sip get_hw_deveui", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_reset_acsip(void) {
	transfer_acsip("sip reset", NULL, 5000, 0);
	return get_return_code();
}

acsip_ret_t sip_get_hw_model_acsip(char *rep_buf, uint16_t len_max){
	return get_acsip("sip get_hw_model", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_set_echo_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "sip set_echo %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_set_log_info_acsip(void) {
	transfer_acsip(" sip set_log info", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_sleep_acsip (int16_t time, uint8_t uart_on) {
	char snd_buf[128];
	sprintf(snd_buf, "sip sleep %lu %s", time, uart_on ? "uart_on": "uart_off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_set_baudrate_acsip(uint32_t baudrate, char *password) {
	char tmp_buf[128];
	sprintf(tmp_buf, "sip set_baudrate %lu %s", baudrate, password);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_get_hw_model_ver_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("sip get_hw_model_ver", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_set_gpio_mode_acsip(char *gpio_group, uint8_t gpio_pin_num, uint8_t gpio_mode) {
	char tmp_buf[128];
	sprintf(tmp_buf, "sip set_gpio_mode %s %u %u", gpio_group, gpio_pin_num, gpio_mode);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_set_gpio_acsip(char *gpio_group, uint8_t gpio_pin_num, uint8_t gpio_val) {
	char tmp_buf[128];
	sprintf(tmp_buf, "sip set_gpio %s %u %u", gpio_group, gpio_pin_num, gpio_val);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_get_gpio_acsip (char *gpio_group, uint8_t gpio_pin_num, char *rep_buf, uint16_t len_max){
	char tmp_buf[128];
	sprintf(tmp_buf, "sip get_gpio %s %u", gpio_group, gpio_pin_num);
	return get_acsip(tmp_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_get_uuid_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("sip get_uuid", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_set_storage_acsip(char *eeprom_encrypted) {
	char tmp_buf[1024];
	sprintf(tmp_buf, "sip set_storage %s", eeprom_encrypted);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_get_storage_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("sip get_storage", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t sip_set_iap_acsip(uint8_t on) {
	char snd_buf[128];
	sprintf(snd_buf, "sip set_iap %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t sip_set_iap_mode_acsip(uint8_t mode) {
	char snd_buf[128];
	sprintf(snd_buf, "sip set_iap_mode %s", mode ? "normal": "silent");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}


// ************ MAC commands ************

acsip_ret_t mac_tx_acsip(char *type, int8_t port_num, uint8_t *data, uint32_t len) {
 char tmp_buf[255];
 uint8_t data_out[255] = {0};

	 if (bytesToHexStr(data, len, data_out, sizeof(data_out)) < 0) {
		 set_return_code(ACSIP_BUFFER_OVERFLOW_RET);
	 }
	 else {
		 //LOG_INFO("convert:: %s\n\r", data_out);
		 sprintf(tmp_buf, "mac tx %s %d %s", type, port_num, data_out);

		  transfer_acsip(tmp_buf, "Ok", 5000, 0);

		  if (get_return_code() == ACSIP_OK_RET) {
		   transfer_acsip(NULL, "tx_ok", 30000, 0);
		  }
	 }

	 return get_return_code();
}

acsip_ret_t mac_join_acsip(char *mode, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];

	for (int try_cnt = 0; try_cnt < SEND_AT_TRY_MAX; try_cnt++) {
		sprintf(tmp_buf, "mac join %s", mode);
		char* ret_str = transfer_acsip(tmp_buf, "Ok", 1000, 0);

		if (ret_str != NULL) {
			set_return_code(get_acsip(NULL, "accepted", rep_buf, len_max, 10000));
			break;
		}
	}
	return get_return_code();
}

acsip_ret_t mac_save_acsip(void) {
	transfer_acsip("mac save", "Ok", 3000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_join_status_acsip(char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_join_status", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_linkchk_acsip(void) {
	transfer_acsip(" mac set_linkchk", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_deveui_acsip(char *deveui) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_deveui %s", deveui);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_appeui_acsip(char *appeui) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_appeui %s", appeui);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_appkey_acsip(char *appkey) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_appkey %s", appkey);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_devaddr_acsip(char *devaddr) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_devaddr %s", devaddr);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_nwkskey_acsip(char *nwkskey) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_nwkskey %s", nwkskey);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_appskey_acsip(char *appskey) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_appskey %s", appskey);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_power_acsip(char *power) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_power %s", power);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_dr_acsip(char *datarate) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_dr %s", datarate);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_adr_acsip(uint8_t on) {
	char snd_buf[128];
	sprintf(snd_buf, "mac set_adr %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_txretry_acsip(uint8_t retrycount) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_txretry %u", retrycount);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_rxdelay1_acsip(uint16_t delay) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_rxdelay1 %lu", delay);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_rx2_acsip(uint8_t dataRate, uint32_t freq) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_rx2 %u %lu", dataRate, freq);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_sync_acsip (uint8_t syncWord){
char tmp_buf[128];
	sprintf(tmp_buf, "mac set_sync %u", syncWord);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_ch_freq_acsip(int8_t ch, uint32_t freq) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_ch_freq %u %lu", ch, freq);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_ch_dr_range(int8_t channelid, int8_t mindr, int8_t maxdr){
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_ch_dr_range %u %u %u", channelid, mindr, maxdr);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_ch_status_acsip(uint8_t channelid, uint8_t status){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_ch_status %u %s", channelid, status ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_dc_ctl_acsip(uint8_t status){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_dc_ctl %s", status ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_dc_band_acsip(int8_t bandid, int16_t dutycycle){
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_dc_band %u %lu", bandid, bandid);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_join_ch_acsip(uint8_t channelid, uint8_t status){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_join_ch %u %s", channelid, status ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_upcnt_acsip(int32_t uplinkcounter) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_upcnt %lu", uplinkcounter);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_downcnt_acsip(int32_t downlinkcounter) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_downcnt %lu", downlinkcounter);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_class_acsip(uint8_t class){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_class %s", class ? "A": "C");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_devaddr_acsip(char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_devaddr", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_deveui_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_deveui", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_appeui_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_appeui", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_nwkskey_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_nwkskey", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_appskey_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_appskey", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_appkey_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_appkey", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_dr_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_dr", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_band_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_band", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_power_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_power", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_adr_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_adr", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_txretry_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_txretry", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_rxdelay_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_rxdelay", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_rx2_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_rx2", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_sync_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_sync", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_ch_para_acsip (uint8_t channelid, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac get_ch_para %u", channelid);
	return get_acsip(tmp_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_ch_status_acsip (uint8_t channelid, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac get_ch_status %u", channelid);
	return get_acsip(tmp_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_dc_ctl_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_dc_ctl", NULL, rep_buf, len_max, 2000);
}

acsip_ret_t mac_get_dc_band_acsip (uint8_t bandid, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac get_dc_band %u", bandid);
	return get_acsip(tmp_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_join_ch_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_join_ch", NULL, rep_buf, len_max, 1000);
}


acsip_ret_t mac_get_upcnt_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_upcnt", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_downcnt_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_downcnt", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_get_class_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_class", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_tx_mode_acsip(uint8_t cycle){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_tx_mode %s", cycle ? "cycle": "no_cycle");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_tx_mode_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_tx_mode", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_batt_acsip(char *battery) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_batt %s", battery);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_batt_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_batt", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_tx_confirm_acsip(uint8_t confirm){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_tx_confirm  %s", confirm ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_tx_confirm_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_tx_confirm", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_claa_acsip(char *claamode) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_claa %s", claamode);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_claa_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_claa", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_getchinfo_acsip(void) {
	transfer_acsip(" mac set_getchinfo", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_gettimeinfo_acsip(void) {
	transfer_acsip(" mac set_gettimeinfo", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_jumboframe_acsip(void) {
	transfer_acsip(" mac set_jumboframe", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_lbt_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_lbt %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_lbt_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_lbt", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_uplink_dwell_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_uplink_dwell %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_uplink_dwell_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_uplink_dwell", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_downlink_dwell_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_downlink_dwell %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_downlink_dwell_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_downlink_dwell", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_max_eirp_acsip(int8_t maxeirp) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_max_eirp %u", maxeirp);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_max_eirp_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_max_eirp", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_ch_count_acsip(uint8_t channelscount, uint16_t bw){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_ch_count %u %u",channelscount, bw);
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_ch_count_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_ch_count", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_keys_acsip(char *devaddr, char *deveui, char *appeui, char *appkey, char *appskey, char *nwkskey) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_keys %s %s %s %s %s %s", devaddr, deveui, appeui, appkey, appskey, nwkskey);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_tx_interval_acsip(int32_t interval) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_tx_interval %lu", interval);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_tx_interval_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_tx_interval", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_rx1_freq_acsip(int32_t rx1_freq_begin, int32_t rx1_step, int32_t rx1_count) {
	char tmp_buf[128];
	sprintf(tmp_buf, "mac set_rx1_freq %lu %lu %lu", rx1_freq_begin, rx1_step, rx1_count);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_rx1_freq_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_rx1_freq", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t mac_set_auto_join_otaa_acsip(uint8_t on, uint16_t join_count){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_auto_join %s otaa %lu", on ? "on": "off", join_count);
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_auto_join_abp_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "mac set_auto_join %s abp", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_set_auto_join_off_acsip(void){
	transfer_acsip("mac set_auto_join off", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t mac_get_auto_join_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("mac get_auto_join", NULL, rep_buf, len_max, 1000);
}


// ************ RF commands ************

acsip_ret_t rf_tx_acsip(uint8_t *data, uint32_t len) {
 char tmp_buf[255];
 uint8_t data_out[255] = {0};

	 if (bytesToHexStr(data, len, data_out, sizeof(data_out)) < 0) {
		 set_return_code(ACSIP_BUFFER_OVERFLOW_RET);
	 }
	 else {
		 //LOG_INFO("convert:: %s\n\r", data_out);
		 sprintf(tmp_buf, "rf tx %s", data_out);

		  transfer_acsip(tmp_buf, "Ok", 5000, 0);

		  if (get_return_code() == ACSIP_OK_RET) {
		   transfer_acsip(NULL, "radio_tx_ok", 30000, 0);
		  }
	 }

	 return get_return_code();
}

acsip_ret_t rf_rx_acsip(uint16_t window_time, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];

	for (int try_cnt = 0; try_cnt < SEND_AT_TRY_MAX; try_cnt++) {
		sprintf(tmp_buf, "rf rx %lu", window_time);
		char* ret_str = transfer_acsip(tmp_buf, "Ok", 1000, 0);

		if (ret_str != NULL) {
			set_return_code(get_acsip(NULL, "radio_rx ", rep_buf, len_max, 10000));
			break;
		}
	}
	return get_return_code();
}

acsip_ret_t rf_set_freq_acsip(int32_t frequency) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_freq %lu", frequency);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_pwr_acsip(int8_t power) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_pwr %u", power);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_sf_acsip(int8_t spreadingfactor) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_sf %u", spreadingfactor);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_bw_acsip(int16_t spreadingfactor) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_bw %u", spreadingfactor);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_cr_acsip(char *codingRate) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_cr %s", codingRate);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_prlen_acsip(int16_t PreambleLength) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_prlen %lu", PreambleLength);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_crc_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rf set_crc %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_iqi_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rf set_iqi %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_sync_acsip(int8_t syncword) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_sync %u", syncword);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_save_acsip(void) {
	transfer_acsip("rf save", "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_get_freq_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_freq", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_pwr_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_pwr", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_sf_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_sf", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_bw_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_bw", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_prlen_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_prlen", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_crc_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_crc", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_iqi_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_iqi", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_cr_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_cr", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_get_sync_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_sync", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_rx_con_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rf rx_con %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_fsk_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rf fsk %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_lora_tx_start_acsip(int32_t times, int32_t interval, char *data) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf lora_tx_start %lu %lu %s", times, interval, data);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_lora_tx_stop_acsip(void) {
	transfer_acsip("rf lora_tx_stop", "Ok", 5000, 0);
	return get_return_code();
}

acsip_ret_t rf_lora_rx_start_acsip(char *data, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];

	for (int try_cnt = 0; try_cnt < SEND_AT_TRY_MAX; try_cnt++) {
		sprintf(tmp_buf, "rf lora_rx_start %s", data);
		char* ret_str = transfer_acsip(tmp_buf, "Ok", 1000, 0);

		if (ret_str != NULL) {
			set_return_code(get_acsip(NULL, "rf lora_rx", rep_buf, len_max, 10000));
			break;
		}
	}
	return get_return_code();
}

acsip_ret_t rf_lora_rx_stop_acsip(void) {
	transfer_acsip("rf lora_rx_stop", "Ok", 5000, 0);
	return get_return_code();
}

acsip_ret_t rf_set_fdev_acsip(int16_t freqdeviation) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf set_fdev %lu", freqdeviation);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_get_fdev_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_fdev", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_set_cad_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rf set_cad %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rf_get_cad_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rf get_cad", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rf_cad_acsip(int32_t frequency, uint8_t sf, uint16_t bw, uint8_t syncword, uint8_t skiprx) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rf cad %lu %u %lu %u %u", frequency, sf, bw, syncword, skiprx);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}



// ************ RM commands ************

acsip_ret_t rm_set_gpio_acsip(char *dir, uint8_t serial_num, char *pin_group, uint8_t pin_name) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rm set_gpio %s %u %s %u", dir, serial_num, pin_group, pin_name);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_gpio_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_gpio", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_gpio_swtich_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rm set_gpio_swtich %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_gpio_swtich_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_gpio_swtich", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_adc_acsip(uint8_t serial_num, uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rm set_adc %u %s", serial_num, on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_adc_acsip (uint8_t serial_num, char *rep_buf, uint16_t len_max) {
	char snd_buf[128];
	sprintf(snd_buf, "rm get_adc %u", serial_num);
	return get_acsip(snd_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_adc_switch_acsip(uint8_t on){
	char snd_buf[128];
	sprintf(snd_buf, "rm set_adc_switch %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_adc_switch_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_adc_switch", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_port_uplink_acsip(uint8_t port) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rm set_port_uplink %u", port);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_set_port_downlink_acsip(uint8_t port) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rm set_port_downlink %u", port);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_port_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_port", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_mode_acsip(char *mode) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rm set_mode %s", mode);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_mode_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_mode", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t rm_set_trigger_acsip(char *pin_group, uint8_t pin_num, char *trig_type) {
	char tmp_buf[128];
	sprintf(tmp_buf, "rm set_trigger %s %u %s", pin_group, pin_num, trig_type);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t rm_get_trigger_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("rm get_trigger", NULL, rep_buf, len_max, 1000);
}


// ************ GPS commands ************

acsip_ret_t gps_set_level_shift_acsip(int8_t on) {
	char snd_buf[128];
	sprintf(snd_buf, "gps set_level_shift %s", on ? "on": "off");
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_set_nmea_rmc_acsip(void) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps set_nmea rmc");
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}


acsip_ret_t gps_set_port_uplink_acsip(uint8_t port) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps set_port_uplink %u", port);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_set_format_uplink_acsip(char *format) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps set_format_uplink %s", format);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_set_positioning_cycle_acsip (uint32_t time) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps set_positioning_cycle %lu", time);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_set_mode_acsip(char *mode) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps set_mode %s", mode);
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_get_mode_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("gps get_mode", NULL, rep_buf, len_max, 1000);
}

acsip_ret_t gps_get_data_acsip (char *req_buf, char *rep_buf, uint16_t len_max) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps get_data %s", req_buf);
	return get_acsip(tmp_buf, NULL, rep_buf, len_max, 1000);
}

acsip_ret_t gps_sleep_on_acsip(int8_t sleep_lev) {
	char snd_buf[128];
	sprintf(snd_buf, "gps sleep on %u", sleep_lev);
	transfer_acsip(snd_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_sleep_off_acsip(void) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps sleep off");
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}

acsip_ret_t gps_get_ttff_acsip (char *rep_buf, uint16_t len_max) {
	return get_acsip("gps get_ttff", NULL, rep_buf, len_max, 1000);
}


acsip_ret_t gps_reset_acsip(void) {
	char tmp_buf[128];
	sprintf(tmp_buf, "gps reset");
	transfer_acsip(tmp_buf, "Ok", 1000, 0);
	return get_return_code();
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */
const char hexArray[] = {'0', '1', '2', '3', '4', '5','6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int16_t bytesToHexStr(uint8_t *buf_in, int32_t len_in, uint8_t *buf_out, int32_t len_out) {
int j = 0;
 	if(len_out < (len_in<<1)) return -1;

    for (j = 0; j < len_in; j++ ) {
        int v = buf_in[j] & 0xFF;
        buf_out[j * 2] = hexArray[v >> 4];
        buf_out[j * 2 + 1] = hexArray[v & 0x0F];
    }

    buf_out[len_in * 2] = 0;

    return 1;
}

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
