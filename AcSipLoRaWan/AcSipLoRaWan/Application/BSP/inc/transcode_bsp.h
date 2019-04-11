//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : transcode_bsp.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : TranscodeGPS Board Support
//; Create(dd/mm/yy) : 15/10/2016
//; [Revision and Description]
//; Rev1.0 - 15/10/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _TRANSCODE_BSP_H
#define _TRANSCODE_BSP_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_usart.h"
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/


        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
#define GPIOA_CLK_ENABLE()             		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)
#define GPIOB_CLK_ENABLE()             	 	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)
#define GPIOC_CLK_ENABLE()              	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)
#define GPIOD_CLK_ENABLE()              	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD)
#define GPIOE_CLK_ENABLE()              	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE)

#define LED1_PIN                           	LL_GPIO_PIN_13
#define LED1_GPIO_PORT                     	GPIOA

#define LED2_PIN                           	LL_GPIO_PIN_14
#define LED2_GPIO_PORT                     	GPIOA

//#define LED1_PIN                           	LL_GPIO_PIN_8
//#define LED1_GPIO_PORT                     	GPIOE
//
//#define LED2_PIN                           	LL_GPIO_PIN_2
//#define LED2_GPIO_PORT                     	GPIOB

#define BUZZER_PIN                          LL_GPIO_PIN_7
#define BUZZER_GPIO_PORT                    GPIOA

#define DOUT1_PIN                           LL_GPIO_PIN_14
#define DOUT1_GPIO_PORT                     GPIOB

#define DOUT2_PIN                           LL_GPIO_PIN_15
#define DOUT2_GPIO_PORT                     GPIOB

#define DIN1_PIN                            LL_GPIO_PIN_12
#define DIN1_GPIO_PORT                     	GPIOB

#define DIN2_PIN                           	LL_GPIO_PIN_13
#define DIN2_GPIO_PORT                     	GPIOB

#define DIN3_TG1_PIN                        LL_GPIO_PIN_9
#define DIN3_TG1_GPIO_PORT                  GPIOC

#define DIN4_TG2_PIN                        LL_GPIO_PIN_15
#define DIN4_TG2_GPIO_PORT                  GPIOC

#define DIN5_DAC1_PIN                        LL_GPIO_PIN_4
#define DIN5_DAC1_GPIO_PORT                  GPIOA

#define DIN6_DAC2_PIN                        LL_GPIO_PIN_5
#define DIN6_DAC2_GPIO_PORT                  GPIOA



#define USR_SW_PIN                          LL_GPIO_PIN_6
#define USR_SW_GPIO_PORT                    GPIOA
#define USR_SW_GPIO_CLK_ENABLE()            LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)


/**
  * @brief LED2 
  */
#define LED_PIN                           LED2_PIN
#define LED_GPIO_PORT                     LED2_GPIO_PORT
//#define LED_GPIO_CLK_ENABLE()             LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)
#define LED_GPIO_CLK_ENABLE()             LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)

/**
  * @brief Toggle periods for various blinking modes
  */
#define LED_BLINK_FAST  70
#define LED_BLINK_SLOW  500
#define LED_BLINK_ERROR 1000


/**
  * @brief Key push-button
  */
    /*
#define USER_BUTTON_PIN                       LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                   GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)   
#define USER_BUTTON_EXTI_IRQn                   EXTI15_10_IRQn
#define USER_BUTTON_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13)   
#define USER_BUTTON_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_13)   
#define USER_BUTTON_SYSCFG_SET_EXTI()           do {                                                                     \
                                                  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                  \
                                                  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);  \
                                                } while(0)
*/
/* User can use this section to tailor CANx instance used and associated
resources */
/* Definition for CANx clock resources */
//#define CANx                            CAN
//#define CANx_CLK_ENABLE()               __HAL_RCC_CAN1_CLK_ENABLE()
//#define CANx_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

//#define CANx_FORCE_RESET()              __HAL_RCC_CAN1_FORCE_RESET()
//#define CANx_RELEASE_RESET()            __HAL_RCC_CAN1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define CANx_TX_PIN                    LL_GPIO_PIN_12
#define CANx_TX_GPIO_PORT              GPIOA
#define CANx_TX_AF                     GPIO_AF9_CAN1
#define CANx_RX_PIN                    LL_GPIO_PIN_11
#define CANx_RX_GPIO_PORT              GPIOA
#define CANx_RX_AF                     GPIO_AF9_CAN1

/* Definition for USARTx's NVIC */
#define CANx_RX_IRQn                   CAN1_RX0_IRQn
//#define CANx_RX_IRQHandler             CAN1_RX0_IRQHandler
#define CANx_TX_IRQn                   CAN1_TX_IRQn
//#define CANx_TX_IRQHandler             CAN1_TX_IRQHandler

/* SPI1 instance is used. (SCK on PB.03, MISO on PB.04, MOSI on PB.05)*/
                                                
                                                  
                                                  
                                                  
                                                  
                                                  
/* USART1 instance is used. (TX on PA.09, RX on PA.10) */
#define TELIT_USART_INSTANCE               USART1
#define TELIT_USART_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define TELIT_USART_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2)
#define TELIT_USART_IRQn                   USART1_IRQn
#define TELIT_USART_IRQHandler             USART1_IRQHandler

#define TELIT_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)   /* Enable the peripheral clock of GPIOA */
#define TELIT_USART_TX_PIN                 LL_GPIO_PIN_9
#define TELIT_USART_TX_GPIO_PORT           GPIOA
#define TELIT_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define TELIT_USART_RX_PIN                 LL_GPIO_PIN_10
#define TELIT_USART_RX_GPIO_PORT           GPIOA
#define TELIT_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)

/* USART2 instance is used. (TX on PA.02, RX on PA.03)
   (please ensure that USART communication between the target MCU and ST-LINK MCU is properly enabled 
    on HW board in order to support Virtual Com Port) */
#define BLE_USART_INSTANCE               USART2
#define BLE_USART_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)
#define BLE_USART_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1)
#define BLE_USART_IRQn                   USART2_IRQn
#define BLE_USART_IRQHandler             USART2_IRQHandler

#define BLE_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)   /* Enable the peripheral clock of GPIOA */
#define BLE_USART_TX_PIN                 LL_GPIO_PIN_2
#define BLE_USART_TX_GPIO_PORT           GPIOA
#define BLE_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_7)
#define BLE_USART_RX_PIN                 LL_GPIO_PIN_3
#define BLE_USART_RX_GPIO_PORT           GPIOA
#define BLE_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_3, LL_GPIO_AF_7)


/* USART3 - instance is used. (TX on PC.04, RX on PC.05)*/
#define RFID_USART_INSTANCE               USART3
#define RFID_USART_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)
#define RFID_USART_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1)
#define RFID_USART_IRQn                   USART3_IRQn
#define RFID_USART_IRQHandler             USART3_IRQHandler

#define RFID_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)   /* Enable the peripheral clock of GPIOC */
#define RFID_USART_TX_PIN                 LL_GPIO_PIN_4
#define RFID_USART_TX_GPIO_PORT           GPIOC
#define RFID_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_4, LL_GPIO_AF_7)
#define RFID_USART_RX_PIN                 LL_GPIO_PIN_5
#define RFID_USART_RX_GPIO_PORT           GPIOC
#define RFID_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_5, LL_GPIO_AF_7)


/* USART4 instance is used. (TX on PC.10, RX on PC.11 DE on PA.15)*/
#define RS485_USART_INSTANCE               UART4
#define RS485_USART_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4)
#define RS485_USART_CLK_SOURCE()           LL_RCC_SetUARTClockSource(LL_RCC_UART4_CLKSOURCE_PCLK1)
#define RS485_USART_IRQn                   UART4_IRQn
#define RS485_USART_IRQHandler             UART4_IRQHandler

#define RS485_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);\
                                           LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)      
                                             
#define RS485_USART_TX_PIN                 LL_GPIO_PIN_10
#define RS485_USART_TX_GPIO_PORT           GPIOC
#define RS485_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_10, LL_GPIO_AF_8)
#define RS485_USART_RX_PIN                 LL_GPIO_PIN_11
#define RS485_USART_RX_GPIO_PORT           GPIOC
#define RS485_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_11, LL_GPIO_AF_8)
#define RS485_USART_DE_PIN                 LL_GPIO_PIN_15
#define RS485_USART_DE_GPIO_PORT           GPIOA
#define RS485_USART_SET_DE_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_15, LL_GPIO_AF_8)
                                                   
/* USART5 instance is used. (TX on PC.12, RX on PD.02)*/
#define CAM_USART_INSTANCE               UART5
#define CAM_USART_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5)
#define CAM_USART_CLK_SOURCE()           LL_RCC_SetUARTClockSource(LL_RCC_UART5_CLKSOURCE_PCLK1)
#define CAM_USART_IRQn                   UART5_IRQn
#define CAM_USART_IRQHandler             UART5_IRQHandler

#define CAM_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);\
                                         LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD)  
                                           
#define CAM_USART_TX_PIN                 LL_GPIO_PIN_12
#define CAM_USART_TX_GPIO_PORT           GPIOC
#define CAM_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_12, LL_GPIO_AF_8)
#define CAM_USART_RX_PIN                 LL_GPIO_PIN_2
#define CAM_USART_RX_GPIO_PORT           GPIOD
#define CAM_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOD, LL_GPIO_PIN_2, LL_GPIO_AF_8)

#define AUX_USART_INSTANCE               UART5
#define AUX_USART_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5)
#define AUX_USART_CLK_SOURCE()           LL_RCC_SetUARTClockSource(LL_RCC_UART5_CLKSOURCE_PCLK1)
#define AUX_USART_IRQn                   UART5_IRQn
#define AUX_USART_IRQHandler             UART5_IRQHandler

#define AUX_USART_GPIO_CLK_ENABLE()      LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);\
                                         LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD) 
                                           
#define AUX_USART_TX_PIN                 LL_GPIO_PIN_12
#define AUX_USART_TX_GPIO_PORT           GPIOC
#define AUX_USART_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOC, LL_GPIO_PIN_12, LL_GPIO_AF_8)
#define AUX_USART_RX_PIN                 LL_GPIO_PIN_2
#define AUX_USART_RX_GPIO_PORT           GPIOD
#define AUX_USART_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOD, LL_GPIO_PIN_2, LL_GPIO_AF_8)
                                                  
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
			
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 3. Public Variable Definition
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
		
		
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
void SystemClock_Config(void);
void init_led(void);
void on_led (void);
void blink_led(uint32_t Period);
void off_led (void);

void init_usr_btn(void);
void usr_btn_cbk_fn(void);

void Error_Callback(void);
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

#endif	//_TRANSCODE_BSP_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
