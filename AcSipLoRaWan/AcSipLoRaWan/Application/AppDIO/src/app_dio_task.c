//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_obd2_task.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : template.c example Implementation
//; Create(dd/mm/yy) : 19/10/2016
//; [Revision and Description]
//; Rev1.0 - 19/10/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
#include "adc.h"

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
TaskHandle_t xDIOH = NULL;
QueueHandle_t xQueueDIOH = 0;

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
static void os_dio_task (void *pvParameters);

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
void os_dio_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_dio_task,       /* Function that implements the task. */
	                          "DIO",          /* Text name for the task. */
	                          256,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xDIOH );      /* Used to pass out the created task's handle. */



	xQueueDIOH = xQueueCreate(2 ,sizeof(queue_trns_t));

	if(xQueueDIOH == NULL)
	{

		LOG_ERROR ("[SYSTEM]: Digital I/O Task Cannot Create Queue!!...\r\n");
		for( ;; );
	    /* Queue was not created and must not be used. */
	}

	GPIOA_CLK_ENABLE();
	GPIOB_CLK_ENABLE();
	GPIOC_CLK_ENABLE();

	LL_GPIO_SetPinMode(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);

	LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);

	LL_GPIO_SetPinMode(USR_SW_GPIO_PORT, USR_SW_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(USR_SW_GPIO_PORT, USR_SW_PIN, LL_GPIO_PULL_UP);



	LL_GPIO_SetPinMode(DOUT1_GPIO_PORT, DOUT1_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(DOUT1_GPIO_PORT, DOUT1_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	LL_GPIO_SetPinMode(DOUT2_GPIO_PORT, DOUT2_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(DOUT2_GPIO_PORT, DOUT2_PIN, LL_GPIO_OUTPUT_PUSHPULL);





	LL_GPIO_SetPinMode(DIN1_GPIO_PORT, DIN1_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(DIN1_GPIO_PORT, DIN1_PIN, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(DIN2_GPIO_PORT, DIN2_PIN, LL_GPIO_MODE_INPUT);
	//LL_GPIO_SetPinPull(DIN2_GPIO_PORT, DIN2_PIN, LL_GPIO_PULL_DOWN);
	LL_GPIO_SetPinPull(DIN2_GPIO_PORT, DIN2_PIN, LL_GPIO_PULL_UP);





	LL_GPIO_SetPinMode(DIN3_TG1_GPIO_PORT, DIN3_TG1_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(DIN3_TG1_GPIO_PORT, DIN3_TG1_PIN, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(DIN4_TG2_GPIO_PORT, DIN4_TG2_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(DIN4_TG2_GPIO_PORT, DIN4_TG2_PIN, LL_GPIO_PULL_DOWN);



	LL_GPIO_SetPinMode(DIN5_DAC1_GPIO_PORT, DIN5_DAC1_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(DIN5_DAC1_GPIO_PORT, DIN5_DAC1_PIN, LL_GPIO_PULL_DOWN);

	LL_GPIO_SetPinMode(DIN6_DAC2_GPIO_PORT, DIN6_DAC2_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(DIN6_DAC2_GPIO_PORT, DIN6_DAC2_PIN, LL_GPIO_PULL_DOWN);

}


static void os_dio_task ( void *pvParameters ) {
queue_trns_t queue_trns;

//	LOG_INFO ("[SYSTEM]: Digital I/O Task Started...\r\n");

	  for( ;; ){

          // Wait receive Queue
          if (xQueueDIOH != NULL) {
				if (xQueueReceive( xQueueDIOH, &queue_trns, 10)) {

					if (queue_trns.dst_addr == (LOGI_USR_SW_ADDR | SELF_ADDRESS)) {
						queue_trns.buf_pt[0] = (uint8_t)LL_GPIO_IsInputPinSet(USR_SW_GPIO_PORT, USR_SW_PIN) ? 1 : 0;
						queue_trns.len = 1;

					//	LOG_INFO ("[USR_SW]: 0x%02X\r\n",queue_trns.buf_pt[0] );


					}
					else if (queue_trns.dst_addr == (LOGI_LED_ADDR | SELF_ADDRESS)) {
						if (queue_trns.len) {
							if ((queue_trns.buf_pt[0] & 0x03) == 1) LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
							else if ((queue_trns.buf_pt[0] & 0x03) == 0) LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);

							if ((queue_trns.buf_pt[1] & 0x03) == 1) LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
							else if ((queue_trns.buf_pt[1] & 0x03) == 0)  LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
						}
						queue_trns.buf_pt[0] = (uint8_t)((LL_GPIO_IsOutputPinSet(LED2_GPIO_PORT, LED2_PIN) ? 2 : 0) | (LL_GPIO_IsOutputPinSet(LED1_GPIO_PORT, LED1_PIN) ? 1 : 0));
						queue_trns.len = 1;

					//	LOG_INFO ("[LEDx]  : 0x%02X\r\n",queue_trns.buf_pt[0] );
					}
					else if (queue_trns.dst_addr == (LOGI_DINx_ADDR | SELF_ADDRESS)) {
//						queue_trns.buf_pt[0] = (uint8_t)(!LL_GPIO_IsInputPinSet(DIN2_GPIO_PORT, DIN2_PIN) ? 2 : 0) | ((!LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN)? 1 : 0));

//						queue_trns.buf_pt[0] = (uint8_t)((LL_GPIO_IsInputPinSet(DIN6_DAC2_GPIO_PORT, DIN6_DAC2_PIN) ? 0x20 : 0) | (LL_GPIO_IsInputPinSet(DIN5_DAC1_GPIO_PORT, DIN5_DAC1_PIN)? 0x10 : 0) |
//																  (LL_GPIO_IsInputPinSet(DIN4_TG2_GPIO_PORT, DIN4_TG2_PIN) ? 0x08 : 0) | (!LL_GPIO_IsInputPinSet(DIN3_TG1_GPIO_PORT, DIN3_TG1_PIN)? 4 : 0) |
//																  (!LL_GPIO_IsInputPinSet(DIN2_GPIO_PORT, DIN2_PIN) ? 0x02 : 0) | (!LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN)?0x01 : 0));

						queue_trns.buf_pt[0] = (uint8_t)((LL_GPIO_IsInputPinSet(DIN6_DAC2_GPIO_PORT, DIN6_DAC2_PIN) << 5) | (LL_GPIO_IsInputPinSet(DIN5_DAC1_GPIO_PORT, DIN5_DAC1_PIN) << 4) |
																  (LL_GPIO_IsInputPinSet(DIN4_TG2_GPIO_PORT, DIN4_TG2_PIN) << 3) | (!LL_GPIO_IsInputPinSet(DIN3_TG1_GPIO_PORT, DIN3_TG1_PIN) << 2)|
																  (!LL_GPIO_IsInputPinSet(DIN2_GPIO_PORT, DIN2_PIN) << 1) | (!LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN)));

						queue_trns.len = 1;

						//LOG_INFO ("[DINx]  : 0x%02X\r\n",queue_trns.buf_pt[0] );
					}
					else if (queue_trns.dst_addr == (LOGI_DOUTx_ADDR | SELF_ADDRESS)) {
						if (queue_trns.len) {
							if ((queue_trns.buf_pt[0] & 0x03) == 1) LL_GPIO_SetOutputPin(DOUT1_GPIO_PORT, DOUT1_PIN);
							else if ((queue_trns.buf_pt[0] & 0x03) == 0) LL_GPIO_ResetOutputPin(DOUT1_GPIO_PORT, DOUT1_PIN);

							if ((queue_trns.buf_pt[1] & 0x03) == 1) LL_GPIO_SetOutputPin(DOUT2_GPIO_PORT, DOUT2_PIN);
							else if ((queue_trns.buf_pt[1] & 0x03) == 0) LL_GPIO_ResetOutputPin(DOUT2_GPIO_PORT, DOUT2_PIN);
						}
						queue_trns.buf_pt[0] = (uint8_t)((LL_GPIO_IsOutputPinSet(DOUT2_GPIO_PORT, DOUT2_PIN) ? 2 : 0) | (LL_GPIO_IsOutputPinSet(DOUT1_GPIO_PORT, DOUT1_PIN) ? 1 : 0));

					//	LOG_INFO ("[DOUTx] : 0x%02X\r\n",queue_trns.buf_pt[0]);

						queue_trns.len = 1;
					}
					else {
						queue_trns.len = 0;
						//queue_trns.buf_pt = NULL;
					}

					//xSemaphoreTake (xSendTransSem, portMAX_DELAY);
					snd_trns_dl (&config_trns_uart1,   //Change to uart1
							  	  queue_trns.src_addr,      //Destination Address (Reply Address)
								  queue_trns.dst_addr,     //Self Address or Source Address
								  CTRL_NORMAL_PKT,
								  HDR_TYP_REP_PKT,  //HEADER TYPE
								  queue_trns.buf_pt, queue_trns.len);
					//xSemaphoreGive (xSendTransSem);
				}
          }



	  }
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
