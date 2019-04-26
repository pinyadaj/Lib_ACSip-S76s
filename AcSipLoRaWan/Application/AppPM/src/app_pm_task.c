//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_pm_task.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : POWER MANAGEMENT Implementation
//; Create(dd/mm/yy) : 23/12/2016
//; [Revision and Description]
//; Rev1.0 - 23/12/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */
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
TaskHandle_t xTaskPM_H = NULL;
QueueHandle_t xQueuePM_H = NULL;

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
	PWR_WAITING_ON_STS = 0,
	PWR_WAITING_OFF_STS,
	PWR_CTRL_ON_STS,
	PWR_CTRL_OFF_STS
} pwr_ctrl_state;

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */


/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */
static void os_pm_task (void *pvParameters);
void app_pwr_ctrl(void);
void pwr_ctrl_conf(void);

void Configure_IWDG(void);

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
void os_pm_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_pm_task,       /* Function that implements the task. */
	                          "PM",          /* Text name for the task. */
	                          128,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xTaskPM_H );      /* Used to pass out the created task's handle. */


	xQueuePM_H = xQueueCreate(1 ,sizeof( queue_trns_t ));

	if(xQueuePM_H == NULL)
	{
		LOG_ERROR ("[SYSTEM]: PWR_M Task Cannot Create Queue!!...\r\n");
	  for( ;; );
	    /* Queue was not created and must not be used. */
	}


	/* Configure GPIO in analog mode to be used as ADC input */
	// BATT12V SENSOR
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	// BATT3V7 SENSOR
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
	LL_GPIO_EnablePinAnalogControl(GPIOB, LL_GPIO_PIN_0 | LL_GPIO_PIN_1);

	// ACC PIN
	//LL_GPIO_SetPinMode (DIN1_GPIO_PORT, DIN1_PIN, LL_GPIO_MODE_INPUT);
	//LL_GPIO_SetPinPull (DIN1_GPIO_PORT, DIN1_PIN, LL_GPIO_PULL_UP);
	//LL_GPIO_SetPinInputType(DIN1_GPIO_PORT, DIN1_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	pwr_ctrl_state = PWR_WAITING_ON_STS;
//	Configure_IWDG();

}

char temp_buf[128];

static void os_pm_task ( void *pvParameters ) {
queue_trns_t queue_trns;
uint16_t led_tick =0 ;
uint8_t read_acc;
//xCameraH
//xDIOH
//xFuelH
//xGPSH
//xOBD2H
//xQueueSDCardH
//xTmBaseH
//xTranRcvH;
//xTranXmitH;
portTickType xLastExecutionTime;


// Initialise the xLastWakeTime variable with the current time.
//	xLastExecutionTime = xTaskGetTickCount();

//LOG_INFO ("[SYSTEM]: PM Task Started...\r\n");

	  for ( ;; ){
			//	vTaskDelayUntil( &xLastExecutionTime,100);

		vTaskDelay(100);

		if (++led_tick == 10) {
			//LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			led_tick = 0;
		}


		/* Refresh IWDG down-counter to default value */
		//LL_IWDG_ReloadCounter(IWDG);

		app_pwr_ctrl();


//			for (uint8_t i_cnt = 0; i_cnt < AVG_N; i_cnt++) {
//				xSemaphoreTake (xADCSem, portMAX_DELAY);
//				raw_gas  +=  xread_adc (ADC_CH1);
//				xSemaphoreGive( xADCSem );
//			}


           // Wait receive Queue
           if (xQueuePM_H != NULL) {
				if (xQueueReceive( xQueuePM_H, &queue_trns, 10)) {
//
//					if (queue_trns.dst_addr == (LOGI_USR_SW_ADDR | SELF_ADDRESS)) {
//						queue_trns.buffer_ptr_ptr[0] = (uint8_t)LL_GPIO_IsInputPinSet(USR_SW_GPIO_PORT, USR_SW_PIN);
//						queue_trns.len = 1;
//					}
//					else
//					{
//						queue_trns.len = 0;
//						queue_trns.buffer_ptr_ptr = NULL;
//					}
//
//					snd_trns_dl (&config_trns_uart1,   //Change to uart1
//							  	  queue_trns.src_addr,      //Destination Address (Reply Address)
//								  (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
//								  CTRL_NORMAL_PKT,
//								  HDR_TYP_REP_PKT,  //HEADER TYPE
//								  queue_trns.buffer_ptr, queue_trns.len);
				}
          }

	  }
}


void app_pwr_ctrl(void) {
static uint8_t tick_led;

	switch (pwr_ctrl_state) {
		case PWR_WAITING_ON_STS :
//			  if (LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN) == 0) {
//				  vTaskDelay(5000);
//				  if (LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN) == 0) {
//					  pwr_ctrl_state = PWR_CTRL_ON_STS;
//				  }
//			  }
			 pwr_ctrl_state = PWR_CTRL_ON_STS;
			break;

		case PWR_WAITING_OFF_STS :
//			  if (LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN) == 1) {
//				  vTaskDelay(5000);
//				  if (LL_GPIO_IsInputPinSet(DIN1_GPIO_PORT, DIN1_PIN) == 1) {
//					  pwr_ctrl_state = PWR_CTRL_OFF_STS;
//				  }
//			  }


			break;

		case PWR_CTRL_ON_STS :


			//LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);

			//3g HwShutdown Button Inactive
		    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_6);

			// DIGITAL LDO ENABLE
			LL_GPIO_SetOutputPin(GPIOC , LL_GPIO_PIN_13);

			// TELIT 3G MODULE LDO ENABLE
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);

			pwr_ctrl_conf();

			//3g PowerON Button Active
			LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
			vTaskDelay(1000);
		    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
		    vTaskDelay(5000);
		    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);

		    pwr_ctrl_state = PWR_WAITING_OFF_STS;
			break;

		case PWR_CTRL_OFF_STS :


			LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);

			// TELIT 3G MODULE LDO ENABLE
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7);

			// TELIT 3G MODULE POWER ON Inactive
			LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);

			//3g HwShutdown Button Active
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_6);

			// DIGITAL LDO Inactive
			LL_GPIO_ResetOutputPin(GPIOC , LL_GPIO_PIN_13);

			pwr_ctrl_conf();

		    pwr_ctrl_state = PWR_WAITING_ON_STS;
			break;

		default :
			pwr_ctrl_state = PWR_WAITING_ON_STS;
			break;
	}

}

void pwr_ctrl_conf(void) {


	// TELIT 3G MODULE POWER ON
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_OPENDRAIN);

	// TELIT 3G MODULE HW SHUTDOWN
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_OPENDRAIN);


	// TELIT 3G MODULE LDO
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_OPENDRAIN);


	// ANALOG LDO
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_14, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_14, LL_GPIO_OUTPUT_PUSHPULL);

	// DIGITAL LDO
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_13, LL_GPIO_OUTPUT_PUSHPULL);

}

int16_t app_measure_batt (batt_t* batt_ptr) {
uint32_t raw_batt;

//	raw_batt = 0;
//
//	for (uint8_t i_cnt = 0; i_cnt < AVG_N; i_cnt++) {
//		xSemaphoreTake (xADCSem, portMAX_DELAY);
//		raw_batt  +=  xread_adc (ADC_CH15_BATT12V_SEN);
//		xSemaphoreGive (xADCSem);
//	}
//
//	raw_batt /= AVG_N;
//
//	batt_ptr->type.voltage_batt12v = (uint8_t)__LL_ADC_CALC_DATA_TO_VOLTAGE ((uint32_t)200, raw_batt, LL_ADC_RESOLUTION_12B);
//	batt_ptr->type.percent_batt12v = (uint8_t)((double)batt_ptr->type.voltage_batt12v / 200.0 * 100.0);
//
//
//	raw_batt = 0;
//	for (uint8_t i_cnt = 0; i_cnt < AVG_N; i_cnt++) {
//		xSemaphoreTake (xADCSem, portMAX_DELAY);
//		raw_batt  +=  xread_adc (ADC_CH16_BATT3V7_SEN);
//		xSemaphoreGive (xADCSem);
//	}
//
//	raw_batt /= AVG_N;
//
//	batt_ptr->type.percent_batt3v7 = (uint8_t)__LL_ADC_CALC_DATA_TO_VOLTAGE ((uint32_t)50, raw_batt, LL_ADC_RESOLUTION_12B);
//	batt_ptr->type.percent_batt3v7 = (uint8_t)((double)batt_ptr->type.voltage_batt12v / 50.0 * 100.0);
//
//	sprintf(temp_buf, "\fRAW12V  : %u \n\r", raw_batt);
//	xputs_uart2(temp_buf);
//	sprintf(temp_buf, "Volt12V : %5.2f V \n\r", batt_ptr->type.voltage_batt12v / 10.0);
//	xputs_uart2(temp_buf);
//
//	sprintf(temp_buf, "\fRAW3V7  : %u \n\r", raw_batt);
//	xputs_uart2(temp_buf);
//	sprintf(temp_buf, "Volt3V7 : %5.2f V \n\r", batt_ptr->type.percent_batt3v7 / 10.0);
//	xputs_uart2(temp_buf);

	return 1;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
  * @brief  This function configures IWDG
  * @param  None
  * @retval None
  */
void Configure_IWDG(void)
{
  /* Enable the peripheral clock of DBG register (uncomment for debug purpose) */
  /* ------------------------------------------------------------------------- */
  /*  LL_DBGMCU_ABP1_GRP1_FreezePeriph(LL_DBGMCU_ABP1_GRP1_IWDG_STOP); */

  /* Enable the peripheral clock IWDG */
  /* -------------------------------- */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
	  blink_led(LED_BLINK_FAST);
  }

  /* Configure the IWDG with window option disabled */
  /* ------------------------------------------------------- */
  /* (1) Enable the IWDG by writing 0x0000 CCCC in the IWDG_KR register */
  /* (2) Enable register access by writing 0x0000 5555 in the IWDG_KR register */
  /* (3) Write the IWDG prescaler by programming IWDG_PR from 0 to 7 - LL_IWDG_PRESCALER_4 (0) is lowest divider*/
  /* (4) Write the reload register (IWDG_RLR) */
  /* (5) Wait for the registers to be updated (IWDG_SR = 0x0000 0000) */
  /* (6) Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA) */
  LL_IWDG_Enable(IWDG);                             /* (1) */
  LL_IWDG_EnableWriteAccess(IWDG);                  /* (2) */
  LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_32);  /* (3) */    //timebase 1ms
  LL_IWDG_SetReloadCounter(IWDG, 0xFEE);            /* (4) */
  while (LL_IWDG_IsReady(IWDG) != 1)                /* (5) */
  {
	  blink_led(LED_BLINK_FAST);
  }
  LL_IWDG_ReloadCounter(IWDG);                      /* (6) */
}

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
