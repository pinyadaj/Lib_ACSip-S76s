//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_rfid_task.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : app_rfid_task.c  Implementation
//; Create(dd/mm/yy) : 12/08/2016
//; [Revision and Description]
//; Rev1.0 - 12/08/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/


/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

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
TaskHandle_t xRFIDH = NULL;
QueueHandle_t xQueueRFIDH = 0;

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
static void os_rfid_task (void *pvParameters);

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
void os_rfid_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_rfid_task,       /* Function that implements the task. */
	                          "RFID",          /* Text name for the task. */
	                          1024,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xRFIDH );      /* Used to pass out the created task's handle. */


	xQueueRFIDH = xQueueCreate(2 ,sizeof( queue_trns_t ));

	if(xQueueRFIDH == NULL)
	{
		LOG_ERROR ("[SYSTEM]: length   RFID Task Cannot Create Queue!!...\r\n");
		for( ;; );
	    /* Queue was not created and must not be used. */
	}

}

_SRAM2 uint8_t uart3_buf[256];	//magnetic card reader
int16_t len_uart3_buf;

_SRAM2 uint8_t rfid_buf[256];
int16_t len_rfid_buf = 0;

static void os_rfid_task ( void *pvParameters ) {
queue_trns_t queue_trns;


//LOG_INFO ("[SYSTEM]: RFID Task Started...\r\n");

	  for( ;; ){

          // Wait receive Queue
          if (xQueueRFIDH != 0) {
				if (xQueueReceive( xQueueRFIDH, &queue_trns, 10)) {

					if (queue_trns.dst_addr == (LOGI_RFID_ADDR | SELF_ADDRESS)) {
						if (queue_trns.len) {

							os_write_uart3 (0, queue_trns.buf_pt, queue_trns.len);

//							int i_cnt;

//							LOG_DEBUG ("[RFID]: WRITE = ");
//							for (i_cnt = 0; i_cnt < queue_trns.len; i_cnt++){
//								LOG_DEBUG ("%c", queue_trns.buf_pt[i_cnt]);
//							}
//							LOG_DEBUG ("\r\n");

							// xSemaphoreTake (xSendTransSem, portMAX_DELAY);
							snd_trns_dl (&config_trns_uart1,   //Change to uart1
									  	  queue_trns.src_addr,      //Destination Address (Reply Address)
										  queue_trns.dst_addr,     //Self Address or Source Address
										  CTRL_NORMAL_PKT,
										  HDR_TYP_REP_PKT,  //HEADER TYPE
										  NULL, 0);
							// xSemaphoreGive (xSendTransSem);
						}else {
							// xSemaphoreTake (xSendTransSem, portMAX_DELAY);
							snd_trns_dl (&config_trns_uart1,   //Change to uart1
									  	  queue_trns.src_addr,      //Destination Address (Reply Address)
										  queue_trns.dst_addr,     //Self Address or Source Address
										  CTRL_NORMAL_PKT,
										  HDR_TYP_REP_PKT,  //HEADER TYPE
										  rfid_buf, len_rfid_buf);
							// xSemaphoreGive (xSendTransSem);
							LOG_INFO ("[RFID]: READ %d Bytes...\r\n", len_rfid_buf);
							len_rfid_buf = 0;
						}
					}
					else {
						queue_trns.len = 0;
					//	queue_trns.buf_pt = NULL;
					}

				}
          }


  		//  type 21 ----> pass
  		//  type 13 ----> not pass
        len_uart3_buf = os_read_uart3 (0, &uart3_buf[0], 256);

		if (len_uart3_buf > 0 ) {

			memcpy (&rfid_buf[0], &uart3_buf[0], len_uart3_buf);
			len_rfid_buf = len_uart3_buf;

//			int i_cnt;
//			LOG_DEBUG ("[RFID]: READ = ");
//			for (i_cnt = 0; i_cnt < len_rfid_buf; i_cnt++){
//				LOG_DEBUG ("%c", rfid_buf[i_cnt]);
//			}
//			LOG_DEBUG ("\r\n");

		}



	  }//for
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
