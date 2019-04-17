/**
  ******************************************************************************
  * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Inc/main.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    29-April-2016
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/* Includes ------------------------------------------------------------------*/
#include <limits.h>     /* CHAR_BIT */

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_iwdg.h"
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Kernel includes. */
#include "FreeRTOSConfig.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "transcode_bsp.h"
#include "drv-uart1.h"
#include "drv-uart2.h"
#include "drv-uart3.h"
#include "drv-uart4.h"
#include "drv-uart5.h"
#include "drv-spi1.h"
#include "drv-can1.h"
#include "adc.h"
#include "tm_stm32f4_swo.h"


#include "gps.h"
#include "app_gps_task.h"
#include "obd2-lib.h"
#include "app_trns-task.h"
//#include "app_cam_task.h"
#include "app_tmbase_task.h"
#include "app_sdcard_task.h"
#include "app_fuel_task.h"
#include "app_dio_task.h"
#include "app_pm_task.h"
#include "app_buzzer_task.h"
#include "app_rfid_task.h"
#include "app_obd2_task.h"
#include "app_umrr_task.h"

#include "service_peripheral.h"

#include "acsip-lorawan-lib.h"



#include "debug_print.h"

#define BIT_MASK(__TYPE__, __ONE_COUNT__) \
    ((__TYPE__) (-((__ONE_COUNT__) != 0))) \
    & (((__TYPE__) -1) >> ((sizeof(__TYPE__) * CHAR_BIT) - (__ONE_COUNT__)))

#define _SRAM2	__attribute__((section (".sram2"), used))

/* Exported types ------------------------------------------------------------*/
extern volatile uint32_t tick_sys;
/* Exported constants --------------------------------------------------------*/

/* Virtual Com Port use is enabled 
       USART2 instance is used. (TX on PA.02, RX on PA.03)
       (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled 
       on HW board in order to support Virtual Com Port)
*/

void USART_CharReception_Callback(void);

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment functions */

/*-----------------------------------------------------------*/

void vApplicationTickHook( void );
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName );


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
