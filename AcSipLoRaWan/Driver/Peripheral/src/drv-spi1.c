//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : drv-uart5.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : uart5 module Implementation
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
#include "drv-spi1.h"
#include "diskio.h"

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
static QueueHandle_t xRxSPI1QueueH;
static QueueHandle_t xTxSPI1QueueH;

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
void Init_spi1 (void){
  /* (1) Enables GPIO clock and configures the SPI1 pins ********************/
		  /* Enable the peripheral clock of GPIOB */
		  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

		  /* Configure SCK Pin connected to pin 31 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_3, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_DOWN);

		  /* Configure MISO Pin connected to pin 27 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_4, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_4, LL_GPIO_PULL_UP);

		  /* Configure MOSI Pin connected to pin 29 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_5, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_5, LL_GPIO_PULL_DOWN);

		  /* (2) Configure NVIC for SPI1 transfer complete/error interrupts **********/
		  /* Set priority for SPI1_IRQn */
		  NVIC_SetPriority(SPI1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		  /* Enable SPI1_IRQn           */
		  NVIC_EnableIRQ(SPI1_IRQn);

		  /* (3) Configure SPI1 functional parameters ********************************/

		  /* Enable the peripheral clock of GPIOB */
		  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

		  /* Configure SPI1 communication */
		  LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV64);
		  LL_SPI_SetTransferDirection(SPI1,LL_SPI_FULL_DUPLEX);
		  LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);
		  LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);
		  /* Reset value is LL_SPI_MSB_FIRST */
		  //LL_SPI_SetTransferBitOrder(SPI1, LL_SPI_MSB_FIRST);
		  LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
		  LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
		  LL_SPI_SetRxFIFOThreshold(SPI1, LL_SPI_RX_FIFO_TH_QUARTER);
		  
		  LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

		  /* Configure SPI1 transfer interrupts */
		  /* Enable RXNE  Interrupt             */
		  //LL_SPI_EnableIT_RXNE(SPI1);
		  /* Enable TXE   Interrupt             */
		 // LL_SPI_EnableIT_TXE(SPI1);
		  /* Enable Error Interrupt             */
		 // LL_SPI_EnableIT_ERR(SPI1);      
          
          /* Enable SPI1 */
          LL_SPI_Enable(SPI1);
}

int16_t xInit_spi1 (unsigned portBASE_TYPE queue_length) {
int16_t xReturn;


	/* Create the queues used to hold Rx/Tx characters. */
	xRxSPI1QueueH = xQueueCreate( queue_length, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xTxSPI1QueueH = xQueueCreate( queue_length + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	
	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxSPI1QueueH != serINVALID_QUEUE ) && ( xTxSPI1QueueH != serINVALID_QUEUE ) )
	{
		/* (1) Enables GPIO clock and configures the SPI1 pins ********************/
		  /* Enable the peripheral clock of GPIOB */
		  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

		  /* Configure SCK Pin connected to pin 31 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_3, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_DOWN);

		  /* Configure MISO Pin connected to pin 27 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_4, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_4, LL_GPIO_PULL_DOWN);

		  /* Configure MOSI Pin connected to pin 29 of CN10 connector */
		  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_ALTERNATE);
		  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_5, LL_GPIO_AF_5);
		  LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_5, LL_GPIO_SPEED_FREQ_VERY_HIGH);
		  LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);

		  /* (2) Configure NVIC for SPI1 transfer complete/error interrupts **********/
		  /* Set priority for SPI1_IRQn */
		//  NVIC_SetPriority(SPI1_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		  /* Enable SPI1_IRQn           */
		//  NVIC_EnableIRQ(SPI1_IRQn);

		  /* (3) Configure SPI1 functional parameters ********************************/

		  /* Enable the peripheral clock of GPIOB */
		  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

		  /* Configure SPI1 communication */
		  LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV64);
		  LL_SPI_SetTransferDirection(SPI1,LL_SPI_FULL_DUPLEX);
		  LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);
		  LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);
		  /* Reset value is LL_SPI_MSB_FIRST */
		  //LL_SPI_SetTransferBitOrder(SPI1, LL_SPI_MSB_FIRST);
		  LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
		  LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
		  LL_SPI_SetRxFIFOThreshold(SPI1, LL_SPI_RX_FIFO_TH_QUARTER);
		  
		  LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

		  /* Configure SPI1 transfer interrupts */
		  /* Enable RXNE  Interrupt             */
		  //LL_SPI_EnableIT_RXNE(SPI1);
		  /* Enable TXE   Interrupt             */
		 // LL_SPI_EnableIT_TXE(SPI1);
		  /* Enable Error Interrupt             */
		 // LL_SPI_EnableIT_ERR(SPI1);      
          
          /* Enable SPI1 */
          LL_SPI_Enable(SPI1);
	}
	else
	{
		xReturn =  0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;        
}

int16_t xgetc_spi1(signed char *pcRxedChar, TickType_t xBlockTime ) {

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxSPI1QueueH, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

void xputs_spi1( const signed char * const pcString ) {
signed char *pxNext;

	/* NOTE: This implementation does not handle the queue being full as no
	block time is used! */

	/* Send each character in the string, one at a time. */
	pxNext = ( signed char * ) pcString;
	while( *pxNext )
	{
		xputc_spi1(*pxNext, serNO_BLOCK );
		pxNext++;
	}
}
/*-----------------------------------------------------------*/

int16_t xputc_spi1( signed char cOutChar, TickType_t xBlockTime ) {
int16_t xReturn;

	if( xQueueSend( xTxSPI1QueueH, &cOutChar, xBlockTime ) == pdPASS )
	{
		xReturn = pdPASS;
      //  LL_SPI_TransmitData8(SPI1, cOutChar);
        /* Enable TXE interrupt */
		LL_SPI_EnableIT_TXE(SPI1);
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}
int16_t xputn_spi1 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len) {
uint8_t i_cnt;

	/* Send each character in the string, one at a time. */
    for (i_cnt = 0; i_cnt < buf_len; i_cnt++){
        xputc_spi1 (buf_ptr[i_cnt], serNO_BLOCK );      
    }
    
    return (i_cnt);
}

int16_t xgetn_spi1 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len) {
uint8_t i_cnt;
int16_t ret;

    for (i_cnt = 0; i_cnt < buf_len; i_cnt++)  {  
          ret = xgetc_spi1((signed char *) buf_ptr++, 10);
          if (ret == pdFALSE) break;
    }

    return (i_cnt);
}
/*-----------------------------------------------------------*/

void vclose_spi1(void)
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/

void vSPI1_ISR_HANDLER ( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
char cChar;

  /* Check RXNE flag value in ISR register */
  if (LL_SPI_IsActiveFlag_RXNE(SPI1))
  {
    /* RXNE flag will be cleared by reading of RDR register (done in call) */
    /* Call function in charge of handling Character reception */
      cChar = LL_SPI_ReceiveData8(SPI1);
   //   LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
      xQueueSendFromISR( xRxSPI1QueueH, &cChar, &xHigherPriorityTaskWoken );
  }
  
  
  if (LL_SPI_IsActiveFlag_TXE(SPI1))
  {
    /* TXE flag will be automatically cleared when writing new data in TDR register */

    /* Call function in charge of handling empty DR => will lead to transmission of next character */
    /* The interrupt was caused by the THR becoming empty.  Are there any
    more characters to transmit? */
      if( xQueueReceiveFromISR( xTxSPI1QueueH, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
      {
        /* A character was retrieved from the queue so can be sent to the
        THR now. */
        /* Fill TDR with a new char */
		LL_SPI_TransmitData8(SPI1, cChar);
        cChar = LL_SPI_ReceiveData8(SPI1);
        xQueueSendFromISR( xRxSPI1QueueH, &cChar, &xHigherPriorityTaskWoken );
      }
      else
      {
          /* Disable TXE interrupt */
		LL_SPI_DisableIT_TXE(SPI1);
	   
      }
  }
//LL_SPI_ClearFlag_OVR(SPI1);
//LL_SPI_ClearFlag_CRCERR(SPI1);
//LL_SPI_ClearFlag_MODF(SPI1);
//LL_SPI_ClearFlag_OVR(SPI1);
//LL_SPI_ClearFlag_FRE(SPI1);

  portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}



/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
