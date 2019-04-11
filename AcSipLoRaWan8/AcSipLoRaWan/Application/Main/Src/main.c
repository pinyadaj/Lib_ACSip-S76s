/**
 ******************************************************************************
 * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Src/main.c
 * @author  MCD Application Team
 * @version V1.5.0
 * @date    29-April-2016
 * @brief   This example describes how to send/receive bytes over USART IP using
 *          the STM32L4xx USART LL API in DMA mode.
 *          Peripheral initialization done using LL unitary services functions.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
/* Kernel includes. */
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
static void prvSetupHardware(void);
static void osTestTask(void *pvParameters);

int main(void) {

	prvSetupHardware();

	//os_dio_task_create();

	//os_buzzer_task_create();

	os_tmbase_task_create();

	//os_pm_task_create();

	//os_transtack_task_create();

	//os_rfid_task_create();

	//os_fuel_task_create();

	//os_sdcard_task_create();

	//os_can_task_create();

	//os_umrr_task_create();

	/* Application Task Create */
	xTaskCreate(osTestTask, "TEST", 4095, (void *) NULL, tskIDLE_PRIORITY,
			NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Infinite loop */
	while (1)
		continue;
}

uint8_t uart2_buf[2048];
int32_t uart2_len;

uint8_t uart3_buf[2048];
int32_t uart3_len;

#define UART3_CONN_UART2 		1

struct {
	uint32_t lat;
	uint32_t lon;
}__attribute__ ((packed)) gps_loc;


static void osTestTask(void *pvParameters) {
	portTickType xLastExecutionTime;
	uint32_t tick_snd_now = 0;
	uint32_t tick_snd_prev = 0;
	char reply_buf[128];
	uint8_t data[32];
	acsip_ret_t ret;

	uint32_t lat = 0;
	uint32_t lon = 0;

	// Initialise the xLastWakeTime variable with the current time.
	//xLastExecutionTime = xTaskGetTickCount();

	vTaskDelay(1000);

	tick_snd_prev = tick_snd_now = tick_sys;

	sip_reset_acsip();
	sip_set_echo_acsip(0);


	gps_set_level_shift_acsip(1);

	gps_set_positioning_cycle_acsip(15000);

	gps_set_mode_acsip (GPS_MANUAL_MODE);

	mac_join_acsip(ABP_MODE, reply_buf, sizeof(reply_buf));

	for (int i=0; i<sizeof(data); i++){
		data[i] = i;
	}

	for (;;) {
		vTaskDelay(10);

		tick_snd_now = tick_sys;

		if ((tick_snd_now - tick_snd_prev) >= 30000) {
			tick_snd_prev = tick_snd_now;

//			ret = sip_get_ver_acsip(reply_buf, sizeof(reply_buf));

			ret = gps_get_data_acsip(GPS_DD_DATA, reply_buf, sizeof(reply_buf));

			if (ret == ACSIP_OK_RET) {
				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n reply_buf : %s\r\n", reply_buf);
				gps_loc.lat = (uint32_t) (strtod (strstr(reply_buf, "LAT( ") + 5, NULL) * 1000000.0);
				gps_loc.lon = (uint32_t) (strtod (strstr(reply_buf, "LONG( ") + 6, NULL) * 1000000.0);

				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n LAT : %s\r\n LON : %s\r\n}\r\n\r\n", strstr(reply_buf, "LAT( ") , strstr(reply_buf, "LONG( ") );

				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n LAT : %lu\r\nLON : %lu\r\SIZE : %lu}\r\n\r\n",gps_loc.lat, gps_loc.lon, sizeof(gps_loc));



				ret = mac_tx_acsip(UCNF_TYPE, 5, &gps_loc, sizeof(gps_loc));

				if (ret == ACSIP_OK_RET) {
					LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
					vTaskDelay(100);
					LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
				}else {
					LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
					vTaskDelay(100);
					LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				}

			} else {
				//os_puts_uart2("\n\r:error:\n\r");
				LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				vTaskDelay(100);
				LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			}
		}


		if (UART3_CONN_UART2) {
			uart3_len = os_read_uart3(0, &uart3_buf[0], sizeof(uart3_buf));

			if (uart3_len > 0) {
				LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
				// forward data from PC to ACSIP module
				os_write_uart2(0, &uart3_buf[0], uart3_len);

				vTaskDelay(100);
				LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);
			}

			uart2_len = os_read_uart2(0, &uart2_buf[0], sizeof(uart2_buf));

			if (uart2_len > 0) {
				LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
				// forward data from PC to ACSIP module
				os_write_uart3(0, &uart2_buf[0], uart2_len);

				vTaskDelay(100);
				LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
			}
		}

	}
}

#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
static void prvSetupHardware(void) {
	/* Configure the system clock to 80 MHz */
	SystemClock_Config();

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	NVIC_SetPriority(MemoryManagement_IRQn, 0);
	/* BusFault_IRQn interrupt configuration */
	NVIC_SetPriority(BusFault_IRQn, 0);
	/* UsageFault_IRQn interrupt configuration */
	NVIC_SetPriority(UsageFault_IRQn, 0);
	/* SVCall_IRQn interrupt configuration */
	NVIC_SetPriority(SVCall_IRQn, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	NVIC_SetPriority(DebugMonitor_IRQn, 0);
	/* PendSV_IRQn interrupt configuration */
	NVIC_SetPriority(PendSV_IRQn, 15);
	/* SysTick_IRQn interrupt configuration */
	NVIC_SetPriority(SysTick_IRQn, 15);

	/* Initialize LED2 */
	init_led();

	/* Initialize button in EXTI mode */
	//init_usr_btn();
	os_init_uart1(115200UL, 4096UL);

	os_init_uart2(115200UL, 2048UL);

	os_init_uart3(115200UL, 2048UL);

	//os_init_uart3(115200UL, 4096UL);

	os_init_uart4(115200UL, 4096UL);

	os_init_uart5(115200UL, 2048UL);   //GPS Module Interface

	xInit_adc();

	LOG_INFO("\r\n[SYSTEM]: RESET STATUS {\r\n");

	if (LL_RCC_IsActiveFlag_FWRST())
		LOG_INFO("  >>>>>> Reset from the firewall occurred");

	if (LL_RCC_IsActiveFlag_IWDGRST())
		LOG_INFO("  >>>>>> Independent watchdog reset occurred");

	if (LL_RCC_IsActiveFlag_LPWRRST())
		LOG_INFO("  >>>>>> Illegal mode reset occurred");

	if (LL_RCC_IsActiveFlag_OBLRST())
		LOG_INFO("  >>>>>> Reset from Option Byte loading occurred");

	if (LL_RCC_IsActiveFlag_PINRST())
		LOG_INFO("  >>>>>> Reset from NRST pin occurred");

	if (LL_RCC_IsActiveFlag_SFTRST())
		LOG_INFO("  >>>>>> Software reset occurred");

	if (LL_RCC_IsActiveFlag_WWDGRST())
		LOG_INFO("  >>>>>> Window watchdog reset occurred");

	if (LL_RCC_IsActiveFlag_BORRST())
		LOG_INFO("  >>>>>> BOR occurred");

	LL_RCC_ClearResetFlags();
	LOG_INFO("\r\n}\r\n\r\n");

}
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler */
}
#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d", file, line) */

	/* Infinite loop */
	while (1) {
	}
}
#endif

/*-----------------------------------------------------------*/
void vApplicationTickHook(void) {

}

/*-----------------------------------------------------------*/
void vApplicationMallocFailedHook(void) {
	/* vApplicationMallocFailedHook() will only be called if
	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	 function that will get called if a call to pvPortMalloc() fails.
	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
	 timer or semaphore is created.  It is also called by various parts of the
	 demo application.  If heap_1.c or heap_2.c are used, then the size of the
	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	 to query the size of free heap space that remains (although it does not

	 provide information on how the remaining heap might be fragmented). */
	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	 task.  It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()).  If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
	(void) pcTaskName;
	(void) pxTask;

	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	 function is called if a stack overflow is detected. */
	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

///**
// ******************************************************************************
// * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Src/main.c
// * @author  MCD Application Team
// * @version V1.5.0
// * @date    29-April-2016
// * @brief   This example describes how to send/receive bytes over USART IP using
// *          the STM32L4xx USART LL API in DMA mode.
// *          Peripheral initialization done using LL unitary services functions.
// ******************************************************************************
// * @attention
// *
// * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
// *
// * Redistribution and use in source and binary forms, with or without modification,
// * are permitted provided that the following conditions are met:
// *   1. Redistributions of source code must retain the above copyright notice,
// *      this list of conditions and the following disclaimer.
// *   2. Redistributions in binary form must reproduce the above copyright notice,
// *      this list of conditions and the following disclaimer in the documentation
// *      and/or other materials provided with the distribution.
// *   3. Neither the name of STMicroelectronics nor the names of its contributors
// *      may be used to endorse or promote products derived from this software
// *      without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// ******************************************************************************
// */
//
///* Includes ------------------------------------------------------------------*/
///* Kernel includes. */
//#include "main.h"
//
///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
///* Private function prototypes -----------------------------------------------*/
///* Private functions ---------------------------------------------------------*/
//
///**
// * @brief  Main program
// * @param  None
// * @retval None
// */
//static void prvSetupHardware(void);
//static void osTestTask(void *pvParameters);
//
//int main(void) {
//
//	prvSetupHardware();
//
//	//os_dio_task_create();
//
//	//os_buzzer_task_create();
//
//	os_tmbase_task_create();
//
//	//os_pm_task_create();
//
//	//os_transtack_task_create();
//
//	//os_rfid_task_create();
//
//	//os_fuel_task_create();
//
//	//os_sdcard_task_create();
//
//	//os_can_task_create();
//
//
//	//os_umrr_task_create();
//
//	/* Application Task Create */
//	xTaskCreate(osTestTask, "TEST", 2048, (void *) NULL, tskIDLE_PRIORITY, NULL);
//
//	/* Start the scheduler. */
//	vTaskStartScheduler();
//
//	/* Infinite loop */
//	while (1)
//		continue;
//}
//
//
//static void osTestTask(void *pvParameters) {
//	portTickType xLastExecutionTime;
//	uint32_t tick_led=0;
//	char* res;
//	// Initialise the xLastWakeTime variable with the current time.
//	xLastExecutionTime = xTaskGetTickCount();
//
//	sip_reset_acsip();
//	sip_set_echo_acsip(0);
//
//
//	res = mac_join_abp_acsip();
//
//	if (strstr (res, "Ok") != NULL ) {
//		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//		vTaskDelay(100);
//		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//	}
//	else {
//		//os_puts_uart2("\n\r:error:\n\r");
//		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//		vTaskDelay(100);
//		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//	}
//
//
//	for (;;) {
//
//		vTaskDelayUntil(&xLastExecutionTime, 1000);
//
//        if (++tick_led == 10) {
//        	tick_led = 0;
//
//        	//res = sip_get_ver_acsip();
//        	//res = sip_get_hw_deveui_acsip();
//
//
//        	res = mac_tx_acsip(CNF_TYPE, 5, "1234");
//
//        	if (strstr (res, "Ok") != NULL ) {
//        		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//        		vTaskDelay(100);
//        		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//        	}
//        	else {
//        		//os_puts_uart2("\n\r:error:\n\r");
//        		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//        		vTaskDelay(100);
//        		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//        	}
//        }
//
//
//	}
//}
//
//#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
//                                                                 0 bit  for subpriority */
//static void prvSetupHardware(void) {
//	/* Configure the system clock to 80 MHz */
//	SystemClock_Config();
//
//	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
//
//	/* System interrupt init*/
//	/* MemoryManagement_IRQn interrupt configuration */
//	NVIC_SetPriority(MemoryManagement_IRQn, 0);
//	/* BusFault_IRQn interrupt configuration */
//	NVIC_SetPriority(BusFault_IRQn, 0);
//	/* UsageFault_IRQn interrupt configuration */
//	NVIC_SetPriority(UsageFault_IRQn, 0);
//	/* SVCall_IRQn interrupt configuration */
//	NVIC_SetPriority(SVCall_IRQn, 0);
//	/* DebugMonitor_IRQn interrupt configuration */
//	NVIC_SetPriority(DebugMonitor_IRQn, 0);
//	/* PendSV_IRQn interrupt configuration */
//	NVIC_SetPriority(PendSV_IRQn, 15);
//	/* SysTick_IRQn interrupt configuration */
//	NVIC_SetPriority(SysTick_IRQn, 15);
//
//	/* Initialize LED2 */
//	init_led();
//
//	/* Initialize button in EXTI mode */
//	//init_usr_btn();
//	os_init_uart1(115200UL, 4096UL);
//
//	os_init_uart2(115200UL, 4096UL);
//
//	os_init_uart3(9600UL, 2048UL);
//
//	//os_init_uart3(115200UL, 4096UL);
//
//	os_init_uart4(115200UL, 4096UL);
//
//	os_init_uart5(115200UL, 2048UL);   //GPS Module Interface
//
//	xInit_adc();
//
//
//
//	/*	LOG_INFO("\r\n[SYSTEM]: RESET STATUS {\r\n");
//
//	if (LL_RCC_IsActiveFlag_FWRST())
//		LOG_INFO ("  >>>>>> Reset from the firewall occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_IWDGRST())
//		LOG_INFO("  >>>>>> Independent watchdog reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_LPWRRST())
//		LOG_INFO("  >>>>>> Illegal mode reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_OBLRST())
//		LOG_INFO("  >>>>>> Reset from Option Byte loading occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_PINRST())
//		LOG_INFO("  >>>>>> Reset from NRST pin occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_SFTRST())
//		LOG_INFO("  >>>>>> Software reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_WWDGRST())
//		LOG_INFO("  >>>>>> Window watchdog reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_BORRST())
//		LOG_INFO("  >>>>>> BOR occurred\r\n");
//
//	LL_RCC_ClearResetFlags();
//	LOG_INFO("}\r\n\r\n");*/
//
//}
//void Error_Handler(void)
//{
//  /* USER CODE BEGIN Error_Handler */
//  /* User can add his own implementation to report the HAL error return state */
//  while(1)
//  {
//  }
//  /* USER CODE END Error_Handler */
//}
//#ifdef  USE_FULL_ASSERT
//
///**
// * @brief  Reports the name of the source file and the source line number
// *         where the assert_param error has occurred.
// * @param  file: pointer to the source file name
// * @param  line: assert_param error line source number
// * @retval None
// */
//void assert_failed(uint8_t *file, uint32_t line) {
//	/* User can add his own implementation to report the file name and line number,
//	 ex: printf("Wrong parameters value: file %s on line %d", file, line) */
//
//	/* Infinite loop */
//	while (1) {
//	}
//}
//#endif
//
///*-----------------------------------------------------------*/
//void vApplicationTickHook(void) {
//
//}
//
///*-----------------------------------------------------------*/
//void vApplicationMallocFailedHook(void) {
//	/* vApplicationMallocFailedHook() will only be called if
//	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
//	 function that will get called if a call to pvPortMalloc() fails.
//	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
//	 timer or semaphore is created.  It is also called by various parts of the
//	 demo application.  If heap_1.c or heap_2.c are used, then the size of the
//	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
//	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
//	 to query the size of free heap space that remains (although it does not
//
//	 provide information on how the remaining heap might be fragmented). */
//	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
//	taskDISABLE_INTERRUPTS();
//	for (;;)
//		;
//}
///*-----------------------------------------------------------*/
//
//void vApplicationIdleHook(void) {
//	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
//	 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
//	 task.  It is essential that code added to this hook function never attempts
//	 to block in any way (for example, call xQueueReceive() with a block time
//	 specified, or call vTaskDelay()).  If the application makes use of the
//	 vTaskDelete() API function (as this demo application does) then it is also
//	 important that vApplicationIdleHook() is permitted to return to its calling
//	 function, because it is the responsibility of the idle task to clean up
//	 memory allocated by the kernel to any task that has since been deleted. */
//}
///*-----------------------------------------------------------*/
//
//void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
//	(void) pcTaskName;
//	(void) pxTask;
//
//	/* Run time stack overflow checking is performed if
//	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
//	 function is called if a stack overflow is detected. */
//	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
//	taskDISABLE_INTERRUPTS();
//	for (;;)
//		;
//}
///*-----------------------------------------------------------*/
//
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

