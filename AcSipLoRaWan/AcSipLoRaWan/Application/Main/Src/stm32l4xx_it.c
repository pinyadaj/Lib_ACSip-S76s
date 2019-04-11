/**
  ******************************************************************************
  * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Src/stm32l4xx_it.c
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    29-April-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "stm32l4xx_it.h"
#include "main.h"

/** @addtogroup STM32L4xx_LL_Examples
  * @{
  */

/** @addtogroup USART_Communication_TxRx_DMA
  * @{
  */
/* External variables --------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
//NVIC_SystemReset();
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
	 blink_led(LED_BLINK_FAST);
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
 //NVIC_SystemReset();
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
	  blink_led(LED_BLINK_FAST);
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
 // NVIC_SystemReset();
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
	  blink_led(LED_BLINK_FAST);
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
//NVIC_SystemReset();
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void DebugMon_Handler(void)
{
}



/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s), for the        */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles DMA1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler(void)
{

}

/**
  * @brief  This function handles DMA1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler(void)
{

}

/**
  * Brief   This function handles TELIT UART Instance interrupt request.
  * Param   None
  * Retval  None
  */
void USART1_IRQHandler(void) {
  OS_UART1_ISR_HANDLER ();
}

/**
  * Brief   This function handles BLE UART Instance interrupt request.
  * Param   None
  * Retval  None
  */
void USART2_IRQHandler(void) {
  OS_UART2_ISR_HANDLER ();
}
/**
  * Brief   This function handles RFID UART Instance interrupt request.
  * Param   None
  * Retval  None
  */
void USART3_IRQHandler(void) {
  OS_UART3_ISR_HANDLER ();
}

/**
  * Brief   This function handles RS485 UART Instance interrupt request.
  * Param   None
  * Retval  None
  */
void UART4_IRQHandler(void) {
  OS_UART4_ISR_HANDLER ();
}

/**
  * Brief   This function handles AUX UART Instance interrupt request.
  * Param   None
  * Retval  None
  */
void UART5_IRQHandler(void) {
  
  OS_UART5_ISR_HANDLER ();
}

/**
  * @brief  This function handles SPI1 interrupt request.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
  vSPI1_ISR_HANDLER ();
}

void CAN1_TX_IRQHandler(void) {
	OS_CAN1_TX_ISR_HANDLER();
}

/*----------------------------------------------------------------------------
  CAN receive interrupt handler
 *----------------------------------------------------------------------------*/
void CAN1_RX0_IRQHandler (void) {
	OS_CAN1_RX0_ISR_HANDLER();
}

void ADC3_IRQHandler(void) {

	  /* Check whether ADC group regular overrun caused the ADC interruption */
	  if(LL_ADC_IsActiveFlag_OVR(ADC3) != 0)
	  {
	    /* Clear flag ADC group regular overrun */
	    LL_ADC_ClearFlag_OVR(ADC3);

	    /* Disable ADC group regular overrun interruption */
	    LL_ADC_DisableIT_OVR(ADC3);

	  }

}

void ADC1_2_IRQHandler(void)
{
  /* Check whether ADC group regular overrun caused the ADC interruption */
  if(LL_ADC_IsActiveFlag_OVR(ADC1) != 0)
  {
    /* Clear flag ADC group regular overrun */
    LL_ADC_ClearFlag_OVR(ADC1);

    /* Call interruption treatment function */
    //AdcGrpRegularOverrunError_Callback();
  }
}

void EXTI15_10_IRQHandler(void)
{



  /* Manage Flags */
  if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_15) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
   // LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
    /* Manage code in app_fuel_task.c.*/
    fuel_trigger_cbk();
  }

  /* Manage Flags */
//  if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_13) != RESET)
//  {
//    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_13);
//    LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//    /* Manage code in app_fuel_task.c.*/
//    //fuel_trigger_cbk();
//  }


}

/**
* @brief  This function handles TIM1 update interrupt.
* @param  None
* @retval None
*/
void TIM1_UP_TIM16_IRQHandler(void)
{
static signed long xHigherPriorityTaskWoken;


  /* Check whether update interrupt is pending */
  if(LL_TIM_IsActiveFlag_UPDATE(TIM1) == 1)
  {
    /* Clear the update interrupt flag*/
    LL_TIM_ClearFlag_UPDATE(TIM1);
    /* TIM1 update interrupt processing */
    //LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
    /* Disable counter */
    LL_TIM_DisableCounter (TIM1);

	xHigherPriorityTaskWoken = pdFALSE;

    /* Unblock the task by releasing the semaphore. */
	xSemaphoreGiveFromISR( xOilSem, &xHigherPriorityTaskWoken );
	/* If xHigherPriorityTaskWoken was set to true you
	we should yield.  The actual macro used here is
	port specific. */
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  }


}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
