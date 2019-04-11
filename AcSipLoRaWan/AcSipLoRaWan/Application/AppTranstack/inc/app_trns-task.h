//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : template.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 5/7/2016
//; [Revision and Description]
//; Rev1.0 - 5/7/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _TRNS_TASK_H
#define _TRNS_TASK_H

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
#include "task.h"
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "transcode_bsp.h"
#include "main.h"
#include "common.h"
#include "app_trns-transceiver.h"
#include "app_trns-callback.h"
        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */



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
/*typedef enum {
    LOGI_CTRL_ADDR              = 0x0000,
    LOGI_UART2_TRNSPRNT_ADDR    = 0x0100,
    LOGI_DACx_ADDR              = 0x0200,     
    LOGI_USR_SW_ADDR            = 0x0300,
    LOGI_BUZZER_ADDR            = 0x0400,
    LOGI_UART1_TRNSPRNT_ADDR    = 0x0500,   
    LOGI_CAN1_ADDR              = 0x0600,   
    LOGI_LED_ADDR               = 0x0700,
    LOGI_BATT12V_ADDR           = 0x0800,
    LOGI_BATT3V7_ADDR           = 0x0900,
    LOGI_SPI1_EXT1_ADDR         = 0x0A00,   
    LOGI_SPI1_EXT2_ADDR         = 0x0B00,
    LOGI_SDCARD_ADDR            = 0x0C00,   
    LOGI_I2C_ADDR               = 0x0D00,   
    LOGI_LPUART1_TRNSPRNT_ADDR  = 0x0E00,   
    LOGI_DINx_ADDR              = 0x0F00,   
    LOGI_DOUTx_ADDR             = 0x1100,   
    LOGI_ADCx_ADDR              = 0x1200,
    LOGI_UART3_TRNSPRNT_ADDR    = 0x1300,
    LOGI_UART4_TRNSPRNT_ADDR    = 0x1400,
    LOGI_UART5_TRNSPRNT_ADDR    = 0x1500,
    
    LOGI_UART1_TRNSTCK_ADDR     = 0x1600,
    LOGI_UART2_TRNSTCK_ADDR     = 0x1700,
    LOGI_UART3_TRNSTCK_ADDR     = 0x1800,
    LOGI_UART4_TRNSTCK_ADDR     = 0x1900,
    LOGI_UART5_TRNSTCK_ADDR     = 0x1A00,
    LOGI_LPUART1_TRNSTCK_ADDR   = 0x1B00,
    
    LOGI_CAMERA_LS_Y201         = 0x1C00
    
} logical_addr_t;*/


/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
extern SemaphoreHandle_t xSendTransSem;
extern TaskHandle_t xTranRcvH;
extern TaskHandle_t xTranXmitH;

extern conf_trns_t config_trns_uart1;
extern conf_trns_t config_trns_uart2;
extern conf_trns_t config_trns_uart4;
extern conf_trns_t config_trns_uart5;


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
void os_transtack_task_create (void);

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

#endif	//_TRNS_TASK_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------

