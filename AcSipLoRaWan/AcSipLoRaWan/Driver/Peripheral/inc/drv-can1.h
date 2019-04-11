//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : uart1_init.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 5/7/2016
//; [Revision and Description]
//; Rev1.0 - 5/7/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef CAN1_INIT_H
#define CAN1_INIT_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
//#include "stm32l4xx_hal.h"
//#include "stm32l4xx_hal_can.h"

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
      
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "transcode_bsp.h"

        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

#define FILTER_MASK_MODE      0
#define FILTER_LIST_MODE      1

typedef struct  {
  uint32_t   id;                    /* 29 bit identifier */
  uint8_t  data[8];               /* Data field */
  uint8_t  len;                   /* Length of data field in bytes */
  uint8_t  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
  uint8_t  type;                  /* 0 - DATA FRAME, 1 - REMOTE FRAME */
} __attribute__ ((packed)) can_msg_t;

/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
    
/* Misc defines. */
#define INVALID_QUEUE				((QueueHandle_t) 0)
#define NON_BLOCK					((TickType_t) 0)
#define BLOCKED						(portMAX_DELAY)
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
			
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 3. Public Variable Definition
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
extern QueueHandle_t xRxCan1QueueH;
extern QueueHandle_t xTxCan1QueueH;

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
/* Functions defined in module CAN.c */
//extern can_msg_t  CAN_TxMsg[2];      /* CAN messge for sending */
//extern can_msg_t  CAN_RxMsg[2];      /* CAN message for receiving */
//extern uint32_t CAN_TxRdy[2];      /* CAN HW ready to transmit a message */
//extern uint32_t CAN_RxRdy[2];      /* CAN HW received a message */
//
		
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
void OS_CAN1_TX_ISR_HANDLER (void);
void OS_CAN1_RX0_ISR_HANDLER (void);

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 6. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

int16_t os_init_can1 (uint32_t TQ, uint32_t SJW, uint32_t TSEG1, uint32_t TSEG2 ,unsigned portBASE_TYPE baud, unsigned portBASE_TYPE queue_length);
int16_t os_read_ff0_can1  (can_msg_t *msg_ptr, TickType_t xBlockTime);
int16_t os_write_ff0_can1 (can_msg_t *msg_ptr, TickType_t xBlockTime );

void write_ff0_can1       (can_msg_t *msg);
void read_ff0_can1        (can_msg_t *msg);
void init_filter_ff0_can1 (uint32_t CAN_filterIdx, uint32_t filer_mode, uint8_t format,  uint32_t id);;


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

#endif	//CAN1_INIT_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
