//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : service_peripheral.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : service_peripheral.c example Implementation
//; Create(dd/mm/yy) : 15/11/2016
//; [Revision and Description]
//; Rev1.0 - 25/11/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "main.h"
#include "common.h"



// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
int8_t flag_rx = 0;

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
char* get_pt_field (char *buf_pt, uint16_t n_field, char delimiter) {
char* packet_pt;
uint16_t i_cnt;

	packet_pt = buf_pt;
	n_field--;
	for (i_cnt = 0; i_cnt < n_field; i_cnt++) {

		packet_pt = strchr (packet_pt, delimiter);

		if (packet_pt == NULL) {
			return NULL;
		}
		else if ((*(packet_pt + 1)) == delimiter){
			return NULL;
		}

		packet_pt++;
	}

	return packet_pt;
}
//"F,D,1,0,3F2";
int8_t assert_pdu (uint16_t n_field, char *buf_pt, uint16_t len) {
	LOG_DEBUG ("[PDU]: CHECK LAST FIELD ADDRESS = 0x%LX\r\n", get_pt_field (buf_pt, n_field, ','));
	LOG_DEBUG ("[PDU]: CHECK LAST FIELD LENGTH  = %d\r\n\r\n", ((buf_pt + len) - get_pt_field (buf_pt, n_field, ',')));
	if (get_pt_field (buf_pt, n_field, ',')  != NULL) {
		if (((buf_pt + len) - get_pt_field (buf_pt, n_field, ',')) > 0) {
				return 1;
		}
	}
	return 0;
}

//int16_t servicePERIPH(conf_trns_t* conf_pt, uint16_t req_addr, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//int flag_timeout = 0;
//
//UINT32 tick_rx = 0;
//UINT32 prev_tick_rx = 0;
//
//	*reply_len_tpr = 0;
//
//	// Send Request to Peripheral
//	snd_trns_dl (conf_pt,
//				 req_addr,      //Destination Address
//				 SELF_ADDRESS,     //Self Address or Source Address
//				 CTRL_NORMAL_PKT,
//				 HDR_TYP_REQ_PKT,  //HEADER TYPE
//				 req_msg_pt, req_len);
//
//	// Wait Reply form Peripheral
//	m2m_hw_req_ms_count(&tick_rx);
//	prev_tick_rx = tick_rx;
//	while (1) {
//
//		process_trns_dl (conf_pt);
//
//		m2m_hw_req_ms_count(&tick_rx);
//
//		if ((tick_rx - prev_tick_rx) >= RX_TIMEOUT) {
//			//write_uart0 (global_fd, "  UUUtimeout\n\r", strlen( "  UUUtimeout\n\r") );
//			return -1;
//		}
//
//		if (flag_rx == 1) {
//			flag_rx = 0;
//			//write_uart0 (global_fd,  "  UUUSuccess\n\r", strlen( "  UUUSuccess\n\r") );
//			*reply_len_tpr = conf_pt->pyl_now_len_rx;
//			memcpy (reply_msg_pt, conf_pt->rcv_pkt_trns.pyl_buf_pt, conf_pt->pyl_now_len_rx);
//			return 1;
//		}
//
//
//	}
//
//return ret;
//}
//
//int16_t reqPERIPH_UART2_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART2_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_DACx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_DACx_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_USR_SW (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_USR_SW_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_BUZZER (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_BUZZER_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART1_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART1_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_CAN1 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_CAN1_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_LED (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_LED_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_BATT12V (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_BATT12V_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_BATT3V7 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_BATT3V7_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_SPI1_EXT1 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_SPI1_EXT1_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_SPI1_EXT2 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_SPI1_EXT2_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_SDCARD (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_SDCARD_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_I2C (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_I2C_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_LPUART1_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_LPUART1_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_DINx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_DINx_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_DOUTx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_DOUTx_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_ADCx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_ADCx_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART3_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART3_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART4_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART4_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART5_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART5_TRNSPRNT_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART1_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART1_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART2_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART2_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART3_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART3_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART4_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART4_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_UART5_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_UART5_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_LPUART1_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_LPUART1_TRNSTCK_ADDR, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//
//int16_t reqPERIPH_CAMERA_LS_Y201 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_CAMERA_LS_Y201, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}
//int16_t reqPERIPH_GPS (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int ret = -1;
//
//	ret = servicePERIPH (conf_pt, LOGI_CAMERA_LS_Y201, req_msg_pt, req_len, reply_msg_pt, reply_len_tpr);
//
//	return ret;
//}

int16_t reqPERIPH_SDCARD_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_SDCARD_ADDR) {
		if (os_queue_sdcard_handle != NULL) xReturn = (int16_t) xQueueSend (os_queue_sdcard_handle, queue_trns_pt, portMAX_DELAY);
	}

return xReturn;
}

int16_t reqPERIPH_BATT_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_BATTx_ADDR) {
		if (xQueueANALOGH != NULL) xReturn = (int16_t) xQueueSend (xQueueANALOGH, queue_trns_pt, portMAX_DELAY);
	}

return xReturn;
}

//int16_t reqPERIPH_BATT3V7_OS (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr) {
//int16_t xReturn = 0;
//
//	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_BATT3V7_ADDR) {
//		if (xQueueANALOGH != NULL) xReturn = (int16_t) xQueueSend (xQueueANALOGH, queue_trns_pt, portMAX_DELAY);
//	}
//
//return xReturn;
//}

int16_t reqIndPERIPH_RFID_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_RFID_ADDR) {
		if (xQueueRFIDH != NULL) xReturn = (int16_t) xQueueSend (xQueueRFIDH, queue_trns_pt, portMAX_DELAY);
	}

	return xReturn;
}


int16_t reqIndPERIPH_GPS_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_GPS_ADDR) {
		if (xQueueGPSH != NULL) xReturn = (int16_t) xQueueSend (xQueueGPSH, queue_trns_pt, portMAX_DELAY);
	}

	return xReturn;
}

int16_t reqIndPERIPH_UARTx_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;
uint16_t logical_address = FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr);

	if (logical_address == LOGI_UART1_TRNSPRNT_ADDR ||
		logical_address == LOGI_UART2_TRNSPRNT_ADDR ||

		logical_address == LOGI_UART4_TRNSPRNT_ADDR ||
		logical_address == LOGI_UART5_TRNSPRNT_ADDR ||
		logical_address == LOGI_LPUART1_TRNSPRNT_ADDR ||
		logical_address == LOGI_UART1_TRNSTCK_ADDR ||
		logical_address == LOGI_UART2_TRNSTCK_ADDR ||

		logical_address == LOGI_UART4_TRNSTCK_ADDR ||
		logical_address == LOGI_UART5_TRNSTCK_ADDR ||
		logical_address == LOGI_LPUART1_TRNSTCK_ADDR)
	{

		if (xQueueTransH != NULL) xReturn = (int16_t) xQueueSend (xQueueTransH, queue_trns_pt, portMAX_DELAY);

	}

	return xReturn;
}
int16_t reqIndPERIPH_UART3_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;
uint16_t logical_address = FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr);

	if (logical_address == LOGI_UART3_TRNSPRNT_ADDR)
	{

		if (xQueueRFIDH != NULL) xReturn = (int16_t) xQueueSend (xQueueRFIDH, queue_trns_pt, portMAX_DELAY);

	}

	if (logical_address == LOGI_UART3_TRNSTCK_ADDR)
	{

		if (xQueueTransH != NULL) xReturn = (int16_t) xQueueSend (xQueueTransH, queue_trns_pt, portMAX_DELAY);

	}
	return xReturn;
}
int16_t reqIndPERIPH_ADCx_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_ADCx_ADDR) {
		if (xQueueANALOGH != NULL) xReturn = (int16_t) xQueueSend (xQueueANALOGH, queue_trns_pt, portMAX_DELAY);
	}

	return xReturn;
}

int16_t reqIndPERIPH_FUEL_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_FUEL_ADDR) {
		if (xQueueANALOGH != NULL) xReturn = (int16_t) xQueueSend (xQueueANALOGH, queue_trns_pt, portMAX_DELAY);
	}

	return xReturn;
}

int16_t reqIndPERIPH_USR_SW_OS (queue_trns_t *queue_trns_pt) {
	int16_t xReturn = 0;

		if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_USR_SW_ADDR) {
			if (xQueueDIOH != NULL) xReturn = (int16_t) xQueueSend (xQueueDIOH, queue_trns_pt, portMAX_DELAY);
		}

		return xReturn;
}

int16_t reqIndPERIPH_BUZZER_OS (queue_trns_t *queue_trns_pt) {
	int16_t xReturn = 0;

		if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_BUZZER_ADDR) {
			if (xQueueBuzzerH != NULL) xReturn = (int16_t) xQueueSend (xQueueBuzzerH, queue_trns_pt, portMAX_DELAY);
		}

		return xReturn;
}

int16_t reqIndPERIPH_LED_OS (queue_trns_t *queue_trns_pt) {
	int16_t xReturn = 0;

		if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_LED_ADDR) {
			if (xQueueDIOH != NULL) xReturn = (int16_t) xQueueSend (xQueueDIOH, queue_trns_pt, portMAX_DELAY);
		}

		return xReturn;
}

int16_t reqIndPERIPH_DINx_OS (queue_trns_t *queue_trns_pt) {
	int16_t xReturn = 0;

		if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_DINx_ADDR) {
			if (xQueueDIOH != NULL) xReturn = (int16_t) xQueueSend (xQueueDIOH, queue_trns_pt, portMAX_DELAY);
		}

		return xReturn;
}

int16_t reqIndPERIPH_DOUTx_OS (queue_trns_t *queue_trns_pt) {
	int16_t xReturn = 0;

		if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_DOUTx_ADDR) {
			if (xQueueDIOH != NULL) xReturn = (int16_t) xQueueSend (xQueueDIOH, queue_trns_pt, portMAX_DELAY);
		}

		return xReturn;
}
int16_t reqIndPERIPH_CAN1_OS (queue_trns_t *queue_trns_pt) {
int16_t xReturn = 0;

	if (FIND_LOGICAL_ADDR(queue_trns_pt->dst_addr) == LOGI_CAN1_ADDR) {
		if (os_queue_can_handle != NULL) xReturn = (int16_t) xQueueSend (os_queue_can_handle, queue_trns_pt, portMAX_DELAY);
	}

	return xReturn;
}



//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
