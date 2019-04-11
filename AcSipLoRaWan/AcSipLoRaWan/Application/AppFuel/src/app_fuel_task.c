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
#include "app_fuel_task.h"
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
TaskHandle_t xFuelH = NULL;
TaskHandle_t xOilH = NULL;
QueueHandle_t xQueueANALOGH = 0;
//SemaphoreHandle_t xOilSem = NULL;

volatile fuel_t fuel;
uint32_t prev_tick_measure = 0;
uint32_t tick_measure = 0;
volatile uint16_t gas_meas_try = 0;
volatile uint16_t oil_meas_try = 0;
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
volatile uint16_t gas_buf [GAS_BUF_MAX];
volatile uint16_t oil_buf [OIL_BUF_MAX];
volatile uint16_t raw_gas_ma;
volatile uint16_t raw_oil_ma;

/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */
conf_ma_t ma_gas_config;
conf_ma_t ma_oil_config;

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */
void Configure_EXTI (void);
void Configure_TIMTimeBase(void);
static void os_fuel_task (void *pvParameters);

static void  vOilTask (void *pvParameters);
/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */
void app_measure_percent_gas (fuel_t* ptr_fuel);
void app_measure_percent_oil (fuel_t* ptr_fuel);
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
void os_fuel_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate(os_fuel_task,       /* Function that implements the task. */
	                          "FUEL",          /* Text name for the task. */
	                          256,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &xFuelH );      /* Used to pass out the created task's handle. */

//	  /* Create the task, storing the handle. */
//	  xReturned = xTaskCreate(vOilTask,       /* Function that implements the task. */
//	                          "FUEL",          /* Text name for the task. */
//	                          1024,      /* Stack size in words, not bytes. */
//	                          ( void * ) NULL,    /* Parameter passed into the task. */
//							  1,/* Priority at which the task is created. */
//	                          &xOilH );      /* Used to pass out the created task's handle. */

	init_ma (&ma_oil_config,
			 &oil_buf[0],
			  OIL_BUF_MAX);

	init_ma (&ma_gas_config,
			 &gas_buf[0],
			  GAS_BUF_MAX);

	//Configure_EXTI();
	//Configure_TIMTimeBase();


	//xOilSem = xSemaphoreCreateBinary();
	//xSemaphoreGive( xOilSem );

	xQueueANALOGH = xQueueCreate(2 ,sizeof( queue_trns_t ));

	if(xQueueANALOGH == NULL)
	{
		LOG_ERROR ("[SYSTEM]: ANALOG Task Cannot Create Queue!!...\r\n");
		for( ;; );
	    /* Queue was not created and must not be used. */
	}

}

uint8_t tick;

uint32_t tick_disp = 50;
uint32_t tick_tx = 0;
uint32_t prev_tick_tx = 0;


uint32_t prev_tick_oil_tmout = 0;
volatile uint32_t tick_oil_tmout = 0;   //call in INT0_ISR(void)
uint16_t adc_value[4] = {0, 0, 0, 0};
double voltage[4] = {0.0, 0.0, 0.0, 0.0};

static void os_fuel_task ( void *pvParameters ) {

queue_trns_t queue_trns;


	LOG_INFO ("[SYSTEM]: Fuel and ADC Task Started...\r\n");
	  for( ;; ){
	        /* toggle LED2*/
	      // LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);

          // Wait receive Queue
          if (xQueueANALOGH != NULL) {
				if (xQueueReceive( xQueueANALOGH, &queue_trns, 10)) {
					LOG_INFO ("[ADC]: Q RCV...\r\n");
					if (queue_trns.dst_addr == (LOGI_FUEL_ADDR | SELF_ADDRESS)) {
						memcpy(queue_trns.buf_pt, &fuel, 4);
						queue_trns.len = sizeof(fuel_t);
					}
					else if (queue_trns.dst_addr == (LOGI_ADCx_ADDR | SELF_ADDRESS)) {
					//	xSemaphoreTake (xADCSem, portMAX_DELAY);
						((adc_t*)queue_trns.buf_pt)->ch.adc1_raw = xread_adc (ADC_CH1);
						((adc_t*)queue_trns.buf_pt)->ch.adc2_raw = xread_adc (ADC_CH2);
						((adc_t*)queue_trns.buf_pt)->ch.adc3_raw = xread_adc (ADC_CH3);
						((adc_t*)queue_trns.buf_pt)->ch.adc4_raw = xread_adc (ADC_CH4);
					//	xSemaphoreGive (xADCSem);
						queue_trns.len = 8;

					}
					else if (queue_trns.dst_addr == (LOGI_BATTx_ADDR | SELF_ADDRESS)) {
					//	xSemaphoreTake (xADCSem, portMAX_DELAY);
						((batt_t*)queue_trns.buf_pt)->ch.batt3v7 = xread_adc (ADC_CH16_BATT3V7_SEN);
						((batt_t*)queue_trns.buf_pt)->ch.batt12  = xread_adc (ADC_CH15_BATT12V_SEN);
					//	xSemaphoreGive (xADCSem);
						queue_trns.len = 4;

					}
					else {
						queue_trns.len = 0;
					//	queue_trns.buf_pt = NULL;
					}


				//	xSemaphoreTake (xSendTransSem, portMAX_DELAY);
					snd_trns_dl (&config_trns_uart1,   //Change to uart1
							  	  queue_trns.src_addr,      //Destination Address (Reply Address)
								  queue_trns.dst_addr,     //Self Address or Source Address
								  CTRL_NORMAL_PKT,
								  HDR_TYP_REP_PKT,  //HEADER TYPE
								  queue_trns.buf_pt, queue_trns.len);
					//xSemaphoreGive (xSendTransSem);

					if (queue_trns.dst_addr == (LOGI_FUEL_ADDR | SELF_ADDRESS)) {

					}
					else if (queue_trns.dst_addr == (LOGI_ADCx_ADDR | SELF_ADDRESS)) {

//						LOG_INFO ("[ADCx]  : [%d, %d, %d, %d]\r\n",((adc_t*)queue_trns.buf_pt)->ch.adc1_raw,
//															   ((adc_t*)queue_trns.buf_pt)->ch.adc2_raw,
//															   ((adc_t*)queue_trns.buf_pt)->ch.adc3_raw,
//															   ((adc_t*)queue_trns.buf_pt)->ch.adc4_raw);

					}
					else if (queue_trns.dst_addr == (LOGI_BATTx_ADDR | SELF_ADDRESS)) {

						LOG_INFO ("[BATTx] : [%d, %d]\r\n",((batt_t*)queue_trns.buf_pt)->ch.batt12,
													     ((batt_t*)queue_trns.buf_pt)->ch.batt3v7);
					}

					queue_trns.len = 0;
				}
          }


        //	app_measure_percent_gas (&fuel);

	        tick_oil_tmout = tick_sys;

	        //RR Task 1sec. period
	        if ((tick_oil_tmout - prev_tick_oil_tmout) >= 50) {
	            prev_tick_oil_tmout = tick_oil_tmout;
	            fuel.type.percent_oil = 0xFF;
	            fuel.type.level_oil   = 0xFF;
	        }

//			if (--tick_disp == 0) {
//
//				tick_disp = 5;
//				sprintf(temp_buf, "\fGAS%%      : %u \n\r", fuel.type.percent_gas);
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "GAS Level  : %u \n\r", fuel.type.level_gas);
//				xputs_uart2(temp_buf);
//
//
//				voltage[0] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, raw_gas_ma, LL_ADC_RESOLUTION_12B);
//				sprintf(temp_buf, "VoltMA1 : %5.2f V \n\r", voltage[0]/1000.0);
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "MA1     : %u \n\r", raw_gas_ma);
//				xputs_uart2(temp_buf);
//
//				adc_value[0] = xread_adc (ADC_CH1);
//				voltage[0] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[0], LL_ADC_RESOLUTION_12B);
//				sprintf(temp_buf, "RAW1     : %u \n\r", adc_value[0]);
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "VoltRAW1 : %5.2f V \n\r\n\r", voltage[0]/1000.0);
//
//
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "Oil%%      : %u \n\r", fuel.type.percent_oil);
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "Oil Level  : %u \n\r", fuel.type.level_oil);
//				xputs_uart2(temp_buf);
//
//				voltage[1] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, raw_oil_ma, LL_ADC_RESOLUTION_12B);
//				sprintf(temp_buf, "VoltMA2 : %5.2f V \n\r", voltage[1]/1000.0);
//				xputs_uart2(temp_buf);
//				sprintf(temp_buf, "MA2     : %u \n\r", raw_oil_ma);
//				xputs_uart2(temp_buf);
//
//
//				voltage[1] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[1], LL_ADC_RESOLUTION_12B);
//
//				sprintf(temp_buf, "VoltRAW2 : %5.2f V \n\r", voltage[1]/1000.0);
//				xputs_uart2(temp_buf);
//
//				sprintf(temp_buf, "RAW2     : %u \n\r\n\r", adc_value[1]);
//				xputs_uart2(temp_buf);
//			}

	  }
}

static void vOilTask ( void *pvParameters ) {



	  for( ;; ){
	        /* toggle LED2*/
	      // LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);

			if (xSemaphoreTake (xOilSem, portMAX_DELAY) == pdTRUE)
			{
				/* We were able to obtain the semaphore and can now access the
				shared resource. */

		//	  LL_GPIO_SetOutputPin (LED_GPIO_PORT, LED_PIN);

			  tick_oil_tmout = tick_sys;   // clear timeout timer

	          app_measure_percent_oil (&fuel);


		//	  LL_GPIO_ResetOutputPin (LED_GPIO_PORT, LED_PIN);
				/* We have finished accessing the shared resource.  Release the
				semaphore. */
				//xSemaphoreGive( xOilSem );
			  //xSemaphoreTake (xOilSem, portMAX_DELAY);
			}
			else
			{
			  /* We could not obtain the semaphore and can therefore not access
			  the shared resource safely. */
			}


			vTaskDelay (10);

	  }
}
void app_measure_percent_gas (fuel_t* ptr_fuel) {
uint32_t raw_gas;

	//if (xSemaphoreTake (xADCSem, portMAX_DELAY) == pdTRUE)
	{
		raw_gas = 0;
		for (uint8_t i_cnt = 0; i_cnt < AVG_N; i_cnt++) {
			xSemaphoreTake (xADCSem, portMAX_DELAY);
			raw_gas  +=  xread_adc (ADC_CH1);
			xSemaphoreGive( xADCSem );
		}
		//xSemaphoreGive( xADCSem );
	}



    raw_gas  /= AVG_N;

    raw_gas = read_ma (&ma_gas_config, raw_gas);
    raw_gas_ma = raw_gas;

    if ((raw_gas >= GAS_MIN_DIGT) && (raw_gas <= GAS_MAX_DIGT)) {

     //   LATBbits.LATB5 ^= 1;     // Blue LED
        raw_gas = raw_gas - GAS_MIN_DIGT;
        ptr_fuel->type.percent_gas = (uint8_t) (((float)raw_gas * GAS_SLOPE) + 0.5F);
        ptr_fuel->type.level_gas   = (uint8_t) (((float)ptr_fuel->type.percent_gas / GAS_LEVEL) + 0.5F);
        gas_meas_try = 0;
    }
    else {
     //  LATBbits.LATB5 = 0;     // Blue LED
        gas_meas_try++;
        if (gas_meas_try == MEA_GAS_TRY_MAX) {
            gas_meas_try = 0;
            ptr_fuel->type.percent_gas = 0xFF;
            ptr_fuel->type.level_gas   = 0xFF;
        }
    }

}

void app_measure_percent_oil (fuel_t* ptr_fuel) {
uint32_t raw_oil ;

	//if (xSemaphoreTake (xADCSem, portMAX_DELAY) == pdTRUE)
	{
		raw_oil = 0;
		for (uint8_t i_cnt = 0; i_cnt < 4; i_cnt++) {
			xSemaphoreTake (xADCSem, portMAX_DELAY);
			raw_oil  +=  xread_adc (ADC_CH2);
			xSemaphoreGive( xADCSem );
		}
		//xSemaphoreGive( xADCSem );
	}


	raw_oil  /= 4;

	raw_oil = read_ma (&ma_oil_config, raw_oil);
	raw_oil_ma = raw_oil;

	if ((raw_oil >= OIL_MIN_DIGT) && (raw_oil <= OIL_MAX_DIGT)) {
		raw_oil = raw_oil - OIL_MIN_DIGT;
		fuel.type.percent_oil = (uint8_t)(((float)raw_oil * OIL_SLOPE) + 0.5F);
		fuel.type.level_oil   = (uint8_t)(((float)fuel.type.percent_oil / OIL_LEVEL) + 0.5F);
		oil_meas_try = 0;
	}else {
		//LATBbits.LATB4 = 0;     // White LED
		oil_meas_try++;
		if (oil_meas_try == MEA_OIL_TRY_MAX) {
		   oil_meas_try = 0;
		   fuel.type.percent_oil = 0xFF;
		   fuel.type.level_oil   = 0xFF;
		}
	}


}
void Configure_EXTI (void) {


  /* -1- GPIO Config */
  /* Enable GPIO Clock (to be able to program the configuration registers) */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  /* Configure IO */
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_15, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_15, LL_GPIO_PULL_NO);
//configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE15);

  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_15);
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_15);

  LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
  /*-2- Configure NVIC for EXTI15_10_IRQn */
  NVIC_EnableIRQ(EXTI15_10_IRQn);
  NVIC_SetPriority(EXTI15_10_IRQn, 10);

  /* -3- Connect External Line to the GPIO*/


  /*-4- Enable a falling trigger EXTI line 13 Interrupt */
  /* Set fields of initialization structure */
 // exti_initstruct.Line_0_31   = LL_EXTI_LINE_15;
 // exti_initstruct.Line_32_63  = LL_EXTI_LINE_NONE;
 // exti_initstruct.LineCommand = ENABLE;
 // exti_initstruct.Mode        = LL_EXTI_MODE_IT;  exti_initstruct.Trigger     = LL_EXTI_TRIGGER_RISING;

  /* Initialize DAC instance according to parameters defined in initialization structure. */
 // LL_EXTI_Init(&exti_initstruct);

}

void  Configure_TIMTimeBase(void)
{
  /* Enable the timer peripheral clock */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

  /* Set counter mode */
  /* Reset value is LL_TIM_COUNTERMODE_UP */
  //LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_UP);

  /* Set the pre-scaler value to have TIM1 counter clock equal to 10 kHz      */
  /*
   In this example TIM1 input clock TIM1CLK is set to APB2 clock (PCLK2),
   since APB2 pre-scaler is equal to 1.
      TIM1CLK = PCLK2
      PCLK2 = HCLK
      => TIM1CLK = SystemCoreClock (80 MHz)
  */
 // LL_TIM_SetPrescaler(TIM1, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));
  LL_TIM_SetPrescaler(TIM1, (uint32_t)8000);
  /* Set the auto-reload value to have an initial update event frequency of 10 Hz */
  //LL_TIM_SetAutoReload(TIM1, (uint32_t)__LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM1), 330));  // ~3m
  LL_TIM_SetAutoReload(TIM1, (uint32_t) 29);  // ~3ms
  /* Enable the update interrupt */
  LL_TIM_EnableIT_UPDATE(TIM1);

  /* Configure the NVIC to handle TIM1 update interrupt */
  NVIC_SetPriority(TIM1_UP_TIM16_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);


  /* Enable counter */
 // LL_TIM_EnableCounter(TIM1);

  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM1);
}

void fuel_trigger_cbk (void) {

	//LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
	LL_TIM_EnableCounter(TIM1);

}

//		adc_value[0] = xread_adc (ADC_CH1);
//		adc_value[1] = xread_adc (ADC_CH2);
//		adc_value[2] = xread_adc (ADC_CH3);
//		adc_value[3] = xread_adc (ADC_CH4);
//
//
//		voltage[0] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[0], LL_ADC_RESOLUTION_12B);
//		voltage[1] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[1], LL_ADC_RESOLUTION_12B);
//		voltage[2] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[2], LL_ADC_RESOLUTION_12B);
//		voltage[3] = __LL_ADC_CALC_DATA_TO_VOLTAGE((uint32_t)3300, adc_value[3], LL_ADC_RESOLUTION_12B);
//
//		sprintf(temp_buf, "\fRAW1  : %u \n\r", adc_value[0]);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "RAW2  : %u \n\r", adc_value[1]);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "RAW3  : %u \n\r", adc_value[2]);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "RAW4  : %u \n\r", adc_value[3]);
//		xputs_uart2(temp_buf);
//
//		sprintf(temp_buf, "Volt1 : %5.2f V \n\r", voltage[0]/1000.0);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "Volt2 : %5.2f V \n\r", voltage[1]/1000.0);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "Volt3 : %5.2f V \n\r", voltage[2]/1000.0);
//		xputs_uart2(temp_buf);
//		sprintf(temp_buf, "Volt4: %5.2f V \n\r", voltage[3]/1000.0);
//		xputs_uart2(temp_buf);
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
