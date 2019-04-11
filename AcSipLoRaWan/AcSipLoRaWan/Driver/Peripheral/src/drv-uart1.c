//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : drv-uart1.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : uart1 module Implementation
//; Create(dd/mm/yy) : 14/10/2016
//; [Revision and Description]
//; Rev1.0 - 14/10/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "drv-uart1.h"

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
static QueueHandle_t xRxUart1QueueH;
static QueueHandle_t xTxUart1QueueH;

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


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
int16_t os_init_uart1 ( unsigned portBASE_TYPE baud, unsigned portBASE_TYPE queue_length) {
int16_t xReturn;


	/* Create the queues used to hold Rx/Tx characters. */
	xRxUart1QueueH = xQueueCreate( queue_length, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xTxUart1QueueH = xQueueCreate( queue_length + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	
	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxUart1QueueH != serINVALID_QUEUE ) && ( xTxUart1QueueH != serINVALID_QUEUE ) )
	{
      
        /* (1) Enable GPIO clock and configures the USART pins *********************/

        /* Enable the peripheral clock of GPIO Port */
        TELIT_USART_GPIO_CLK_ENABLE();

        /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
        LL_GPIO_SetPinMode(TELIT_USART_TX_GPIO_PORT, TELIT_USART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
        TELIT_USART_SET_TX_GPIO_AF();
        LL_GPIO_SetPinSpeed(TELIT_USART_TX_GPIO_PORT, TELIT_USART_TX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
        LL_GPIO_SetPinOutputType(TELIT_USART_TX_GPIO_PORT, TELIT_USART_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
        LL_GPIO_SetPinPull(TELIT_USART_TX_GPIO_PORT, TELIT_USART_TX_PIN, LL_GPIO_PULL_UP);

        /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
        LL_GPIO_SetPinMode(TELIT_USART_RX_GPIO_PORT, TELIT_USART_RX_PIN, LL_GPIO_MODE_ALTERNATE);
        TELIT_USART_SET_RX_GPIO_AF();
        LL_GPIO_SetPinSpeed(TELIT_USART_RX_GPIO_PORT, TELIT_USART_RX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
        LL_GPIO_SetPinOutputType(TELIT_USART_RX_GPIO_PORT, TELIT_USART_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
        LL_GPIO_SetPinPull(TELIT_USART_RX_GPIO_PORT, TELIT_USART_RX_PIN, LL_GPIO_PULL_UP);

        /* (2) NVIC Configuration for USART interrupts */
        /*  - Set priority for TELIT_USART_IRQn */
        /*  - Enable TELIT_USART_IRQn */
        NVIC_SetPriority(TELIT_USART_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);  
        NVIC_EnableIRQ(TELIT_USART_IRQn);

        /* (3) Enable USART peripheral clock and clock source ***********************/
        TELIT_USART_CLK_ENABLE();

        /* Set clock source */
        TELIT_USART_CLK_SOURCE();

        /* (4) Configure USART functional parameters ********************************/
        
        /* Disable USART prior modifying configuration registers */
        /* Note: Commented as corresponding to Reset value */
        // LL_USART_Disable(TELIT_USART_INSTANCE);

        /* TX/RX direction */
        LL_USART_SetTransferDirection(TELIT_USART_INSTANCE, LL_USART_DIRECTION_TX_RX);

        /* 8 data bit, 1 start bit, 1 stop bit, no parity */
        LL_USART_ConfigCharacter(TELIT_USART_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

        /* No Hardware Flow control */
        /* Reset value is LL_USART_HWCONTROL_NONE */
        // LL_USART_SetHWFlowCtrl(TELIT_USART_INSTANCE, LL_USART_HWCONTROL_NONE);

        /* Oversampling by 16 */
        /* Reset value is LL_USART_OVERSAMPLING_16 */
        //LL_USART_SetOverSampling(TELIT_USART_INSTANCE, LL_USART_OVERSAMPLING_16);

        /* Set Baudrate to 115200 using APB frequency set to 80000000 Hz */
        /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
        /* Ex :
            Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance
        
            In this example, Peripheral Clock is expected to be equal to 80000000 Hz => equal to SystemCoreClock
        */
        LL_USART_SetBaudRate(TELIT_USART_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, baud); 

        /* (5) Enable USART *********************************************************/
        LL_USART_Enable(TELIT_USART_INSTANCE);
        
        /* Polling USART initialisation */
        while((!(LL_USART_IsActiveFlag_TEACK(TELIT_USART_INSTANCE))) || (!(LL_USART_IsActiveFlag_REACK(TELIT_USART_INSTANCE))))
        { 
        }

        /* Enable RXNE and Error interrupts */
        LL_USART_EnableIT_RXNE(TELIT_USART_INSTANCE);
       // LL_USART_EnableIT_ERROR(TELIT_USART_INSTANCE);  
        
	}
	else
	{
		xReturn =  0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;        
}

int16_t os_getc_uart1(signed char *pcRxedChar, TickType_t xBlockTime ) {

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxUart1QueueH, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

void os_puts_uart1( const signed char * const pcString ) {
signed char *pxNext;

	/* NOTE: This implementation does not handle the queue being full as no
	block time is used! */

	/* Send each character in the string, one at a time. */
	pxNext = ( signed char * ) pcString;
	while( *pxNext )
	{
		os_putc_uart1(*pxNext, serNO_BLOCK );
		pxNext++;
	}
}

/*-----------------------------------------------------------*/

int16_t os_putc_uart1( signed char cOutChar, TickType_t xBlockTime ) {
int16_t xReturn;

	if( xQueueSend( xTxUart1QueueH, &cOutChar, xBlockTime ) == pdPASS )
	{
		xReturn = pdPASS;
        
        /* Enable TXE interrupt */
        LL_USART_EnableIT_TXE(TELIT_USART_INSTANCE); 
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}

int16_t os_write_uart1 (int16_t file_desc, uint8_t *buf_ptr, int16_t buf_len) {
int16_t i_cnt;

	/* Send each character in the string, one at a time. */
    for (i_cnt = 0; i_cnt < buf_len; i_cnt++){
        os_putc_uart1 (buf_ptr[i_cnt], serNO_BLOCK );      
    }
    
    return (i_cnt);
}

int16_t os_read_uart1 (int16_t file_desc, uint8_t *buf_ptr, int16_t buf_len) {
int16_t i_cnt;
int16_t ret;

    for (i_cnt = 0; i_cnt < buf_len; i_cnt++)  {  
          ret = os_getc_uart1((signed char *) buf_ptr++, 1);
          if (ret == pdFALSE) break;
    }

    return (i_cnt);
}

/*-----------------------------------------------------------*/

void os_close_uart1(void)
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/

void OS_UART1_ISR_HANDLER ( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
char cChar;

  /* Check RXNE flag value in ISR register */
  if (LL_USART_IsActiveFlag_RXNE(TELIT_USART_INSTANCE) && LL_USART_IsEnabledIT_RXNE(TELIT_USART_INSTANCE))
  {
    /* RXNE flag will be cleared by reading of RDR register (done in call) */
    /* Call function in charge of handling Character reception */
      cChar = LL_USART_ReceiveData8(TELIT_USART_INSTANCE);
      xQueueSendFromISR( xRxUart1QueueH, &cChar, &xHigherPriorityTaskWoken );
  }
  
  
  if (LL_USART_IsEnabledIT_TXE(TELIT_USART_INSTANCE) && LL_USART_IsActiveFlag_TXE(TELIT_USART_INSTANCE))
  {
    /* TXE flag will be automatically cleared when writing new data in TDR register */

    /* Call function in charge of handling empty DR => will lead to transmission of next character */
    /* The interrupt was caused by the THR becoming empty.  Are there any
    more characters to transmit? */
      if( xQueueReceiveFromISR( xTxUart1QueueH, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
      {
        /* A character was retrieved from the queue so can be sent to the
        THR now. */
        /* Fill TDR with a new char */
        LL_USART_TransmitData8(TELIT_USART_INSTANCE, cChar);
      }
      else
      {
          /* Disable TXE interrupt */
          LL_USART_DisableIT_TXE(TELIT_USART_INSTANCE);
	
      }
  }
  
  LL_USART_ClearFlag_PE(TELIT_USART_INSTANCE);
  LL_USART_ClearFlag_FE(TELIT_USART_INSTANCE);
  LL_USART_ClearFlag_NE(TELIT_USART_INSTANCE);
  LL_USART_ClearFlag_ORE(TELIT_USART_INSTANCE);
  
  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}



/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------