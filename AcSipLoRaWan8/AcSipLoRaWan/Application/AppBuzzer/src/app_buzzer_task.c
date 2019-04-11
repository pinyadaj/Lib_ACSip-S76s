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
TaskHandle_t xBuzzerH = NULL;
TaskHandle_t xBuzzer2H = NULL;
QueueHandle_t xQueueBuzzerH = 0;

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
enum {
    BUZZER_IDLE = 0,
	BUZZER_STEP1_ON,
	BUZZER_STEP1_OFF,
	BUZZER_STEP2_ON,
	BUZZER_STEP2_OFF,
	BUZZER_STEP3_ON,
	BUZZER_STEP3_OFF,
	BUZZER_STEP4_ON,
	BUZZER_STEP4_OFF,
	BUZZER_STEP5_ON,
	BUZZER_STEP5_OFF
} buzzer_proc_state;
/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */


/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */
static void os_buzzer_task (void *pvParameters);
static void os_buzzer2_task (void *pvParameters);
void buzzer_type1_proc(void);

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
void os_buzzer_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_buzzer_task,       /* Function that implements the task. */
	                          "BUZZER",          /* Text name for the task. */
	                          128,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xBuzzerH );      /* Used to pass out the created task's handle. */

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_buzzer2_task,       /* Function that implements the task. */
	                          "BUZZER2",          /* Text name for the task. */
	                          128,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xBuzzer2H );      /* Used to pass out the created task's handle. */


	xQueueBuzzerH = xQueueCreate(2 ,sizeof( queue_trns_t ));

	if(xQueueBuzzerH == NULL)
	{
		LOG_ERROR ("[SYSTEM]: Buzzer Task Cannot Create Queue!!...\r\n");
		for( ;; );
	    /* Queue was not created and must not be used. */
	}


	GPIOA_CLK_ENABLE();
	LL_GPIO_SetPinMode(BUZZER_GPIO_PORT, BUZZER_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(BUZZER_GPIO_PORT, BUZZER_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	//Start System Beep
//	LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//	LL_mDelay(100);
//	LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
}

char temp_buf[128];
uint32_t t_delay[10];
char buzzer_sound_type = 0;
char buzzer_on = 0;
uint8_t buzzer_repeat = 255;

uint8_t buzzer_reset = 0;
uint8_t buzzer_break = 0;

static void os_buzzer_task ( void *pvParameters ) {
queue_trns_t queue_trns;
//LOG_INFO ("[SYSTEM]: Buzzer1Task Started...\r\n");

	  for( ;; ){

          // Wait receive Queue
          if (xQueueBuzzerH != NULL) {
				if (xQueueReceive( xQueueBuzzerH, &queue_trns, 10)) {

					if (queue_trns.dst_addr == (LOGI_BUZZER_ADDR | SELF_ADDRESS)) {

						if (queue_trns.len) {
							if (queue_trns.buf_pt[0] > 0) buzzer_on = 1;
							else buzzer_on = 0;

							buzzer_sound_type = queue_trns.buf_pt[1];
							buzzer_repeat     = queue_trns.buf_pt[2];



							if (buzzer_sound_type == 0) {
								t_delay[0] = 6000;
								t_delay[1] = 1000;
							}
							else if (buzzer_sound_type == 1) {
								t_delay[0] = 500;
								t_delay[1] = 100;
								t_delay[2] = 500;
								t_delay[3] = 100;
								t_delay[4] = 500;
								t_delay[5] = 100;
								t_delay[6] = 500;
								t_delay[7] = 100;
								t_delay[8] = 500;
								t_delay[9] = 3000;
							}
							else if (buzzer_sound_type == 2) {
								t_delay[0] = 200;
								t_delay[1] = 40;
								t_delay[2] = 200;
								t_delay[3] = 40;
								t_delay[4] = 200;
								t_delay[5] = 40;
								t_delay[6] = 200;
								t_delay[7] = 40;
								t_delay[8] = 200;
								t_delay[9] = 1500;
							}
							else if (buzzer_sound_type == 3) {
								t_delay[0] = 60;
								t_delay[1] = 60;
								t_delay[2] = 60;
								t_delay[3] = 60;
								t_delay[4] = 60;
								t_delay[5] = 60;
								t_delay[6] = 60;
								t_delay[7] = 60;
								t_delay[8] = 60;
								t_delay[9] = 60;
							}
							else if (buzzer_sound_type == 4) {
								t_delay[0] = 100;
								t_delay[1] = 1000;
								t_delay[2] = 100;
								t_delay[3] = 1000;
								t_delay[4] = 100;
								t_delay[5] = 1000;
								t_delay[6] = 100;
								t_delay[7] = 1000;
								t_delay[8] = 100;
								t_delay[9] = 1000;
							}
							else if (buzzer_sound_type == 5) {
								t_delay[0] = 60;
								t_delay[1] = 100;
								t_delay[2] = 60;
								t_delay[3] = 100;
								t_delay[4] = 60;
								t_delay[5] = 200;
								t_delay[6] = 400;
								t_delay[7] = 100;
								t_delay[8] = 60;
								t_delay[9] = 2000;
							}
							else if (buzzer_sound_type == 6) {
								t_delay[0] = 100;
								t_delay[1] = 1000;
							}
							// reset counter
							buzzer_reset = 1;
						}
						queue_trns.buf_pt[0] = buzzer_on;
						queue_trns.len = 1;
					}
					else {
						queue_trns.len = 0;
						//queue_trns.buf_pt = NULL;
					}

					//xSemaphoreTake (xSendTransSem, portMAX_DELAY);

					snd_trns_dl (&config_trns_uart1,   //Change to uart1
							  	  queue_trns.src_addr,      //Destination Address (Reply Address)
								  (LOGI_BUZZER_ADDR | SELF_ADDRESS),     //Self Address or Source Address
								  CTRL_NORMAL_PKT,
								  HDR_TYP_REP_PKT,  //HEADER TYPE
								  queue_trns.buf_pt, queue_trns.len);

					//xSemaphoreGive (xSendTransSem);

					//LOG_INFO ("[BUZZER]: [%d, %d, %d]\r\n\r\n", buzzer_on, buzzer_sound_type, buzzer_repeat);

				}
          }

	  }
}
static void os_buzzer2_task ( void *pvParameters ) {
	uint8_t buzzer_cnt = 0;

//	LOG_INFO ("[SYSTEM]: Buzzer2Task Started...\r\n");

	  for( ;; ){
		  vTaskDelay(10);

          if (buzzer_on) {
        	  for (buzzer_cnt = 0; (buzzer_cnt < buzzer_repeat) || (buzzer_repeat == 255); buzzer_cnt++){

        		  if (buzzer_reset == 1) {
        			  break;
        		  }

				  if ((buzzer_sound_type == 0) || (buzzer_sound_type == 6)) {
					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
					  vTaskDelay(t_delay[0]);
					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
					  vTaskDelay(t_delay[1]);

				  }
				  else if ((buzzer_sound_type > 0) &&(buzzer_sound_type < 10) )
				  {
					  int i_cnt;
					  for (i_cnt = 0; i_cnt < 10; i_cnt = i_cnt + 2){
						  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
						  vTaskDelay(t_delay[i_cnt]);
						  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
						  vTaskDelay(t_delay[i_cnt + 1]);
						  if (buzzer_reset == 1)  break;

					  }

//					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[0]);
//					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[1]);
//					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[2]);
//					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[3]);
//					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[4]);
//					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[5]);
//					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[6]);
//					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[7]);
//					  LL_GPIO_SetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[8]);
//					  LL_GPIO_ResetOutputPin(BUZZER_GPIO_PORT, BUZZER_PIN);
//					  vTaskDelay(t_delay[9]);
				  }

    		  } //if (buzzer_repeat == 255)
        	  vTaskDelay(500);
    		  if (buzzer_reset == 0) {
    			  buzzer_on = 0;
    		  }
    		  buzzer_reset = 0;

          }//if (buzzer_on)





	  }
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void buzzer_type1_proc (void) {
	switch (buzzer_proc_state) {

	case BUZZER_IDLE :
		break;

	case BUZZER_STEP1_ON :

		break;

	case BUZZER_STEP1_OFF:
		break;

	case BUZZER_STEP2_ON :
		break;

	case BUZZER_STEP2_OFF:
		break;

	case BUZZER_STEP3_ON :
		break;

	case BUZZER_STEP3_OFF:
		break;

	case BUZZER_STEP4_ON :
		break;

	case BUZZER_STEP4_OFF:
		break;

	case BUZZER_STEP5_ON :
		break;

	case BUZZER_STEP5_OFF:
		break;


	default:
		break;
	}
}
/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
