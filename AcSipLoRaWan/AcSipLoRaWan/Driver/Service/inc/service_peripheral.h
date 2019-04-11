//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : service_peripheral.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 25/11/2016
//; [Revision and Description]
//; Rev1.0 - 25/11/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _SERVICE_PERIPH_H
#define _SERVICE_PERIPH_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#include "trns-typedef.h"
#include "trns-llc.h"
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/


        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

#define RX_TIMEOUT		(200)   //200mS

#define LOGI_CTRL_ADDR               0x0000
#define LOGI_UART2_TRNSPRNT_ADDR     0x0100
#define LOGI_DACx_ADDR               0x0200
#define LOGI_USR_SW_ADDR             0x0300
#define LOGI_BUZZER_ADDR             0x0400
#define LOGI_UART1_TRNSPRNT_ADDR     0x0500
#define LOGI_CAN1_ADDR               0x0600
#define LOGI_LED_ADDR                0x0700
#define LOGI_BATTx_ADDR            	0x0800
//#define LOGI_BATT3V7_ADDR            0x0900
#define LOGI_SPI1_EXT1_ADDR          0x0A00
#define LOGI_SPI1_EXT2_ADDR          0x0B00
#define LOGI_SDCARD_ADDR             0x0C00
#define LOGI_I2C_ADDR                0x0D00
#define LOGI_LPUART1_TRNSPRNT_ADDR   0x0E00
#define LOGI_DINx_ADDR               0x0F00
#define LOGI_DOUTx_ADDR              0x1100
#define LOGI_ADCx_ADDR               0x1200
#define LOGI_UART3_TRNSPRNT_ADDR     0x1300
#define LOGI_UART4_TRNSPRNT_ADDR     0x1400
#define LOGI_UART5_TRNSPRNT_ADDR     0x1500

#define LOGI_UART1_TRNSTCK_ADDR      0x1600
#define LOGI_UART2_TRNSTCK_ADDR      0x1700
#define LOGI_UART3_TRNSTCK_ADDR      0x1800
#define LOGI_UART4_TRNSTCK_ADDR      0x1900
#define LOGI_UART5_TRNSTCK_ADDR      0x1A00
#define LOGI_LPUART1_TRNSTCK_ADDR    0x1B00

#define LOGI_CAMERA_LS_Y201          0x1C00
#define LOGI_GPS_ADDR	             0x1D00
#define LOGI_FUEL_ADDR               0x1E00

#define LOGI_RFID_ADDR               0x1F00

#define FIND_LOGICAL_ADDR(a) 		(a & 0xFF00)
#define FIND_SELF_ADDR(a) 			(a & 0x00FF)
/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
 	     
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
		
      
		
		
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
char* get_pt_field (char *buf_pt, uint16_t n_field, char delimiter) ;
int8_t assert_pdu (uint16_t n_field, char *buf_pt, uint16_t len);

       /***************** Service for Seriver Side ******************/
//int16_t servicePERIPH(conf_trns_t* conf_pt, uint16_t req_addr, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//
//int16_t reqPERIPH_UART2_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_DACx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_USR_SW (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_BUZZER (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART1_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_CAN1 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_LED (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_BATT12V (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_BATT3V7 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_SPI1_EXT1 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_SPI1_EXT2 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_SDCARD (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_I2C (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_LPUART1_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_DINx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_DOUTx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_ADCx (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART3_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART4_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART5_TRNSPRNT (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART1_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART2_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART3_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART4_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_UART5_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_LPUART1_TRNSTCK (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_CAMERA_LS_Y201 (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);
//int16_t reqPERIPH_GPS (conf_trns_t* conf_pt, uint8_t *req_msg_pt, uint16_t req_len, uint8_t *reply_msg_pt, uint16_t *reply_len_tpr);

/***************************************** Service for Server Side ***********************************************/
int16_t reqIndPERIPH_OS (QueueHandle_t xQueue, int16_t logic_addr, queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_GPS_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_UARTx_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_ADCx_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_FUEL_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_USR_SW_OS (queue_trns_t *queue_trns_pt);
int16_t reqIndPERIPH_BUZZER_OS (queue_trns_t *queue_trns_pt);
int16_t reqIndPERIPH_LED_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_DINx_OS (queue_trns_t *queue_trns_pt);
int16_t reqIndPERIPH_DOUTx_OS (queue_trns_t *queue_trns_pt);

int16_t reqIndPERIPH_UARTx_OS (queue_trns_t *queue_trns_pt);
int16_t reqIndPERIPH_RFID_OS (queue_trns_t *queue_trns_pt);

int16_t reqPERIPH_SDCARD_OS (queue_trns_t *queue_trns_pt);
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 7. Private Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 7.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif

#endif	//_TEMPLATE_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
