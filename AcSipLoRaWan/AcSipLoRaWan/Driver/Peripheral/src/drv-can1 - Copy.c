//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : drv-can1.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : can1 module Implementation
//; Create(dd/mm/yy) : 21/10/2016
//; [Revision and Description]
//; Rev1.0 - 21/10/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "drv-can1.h"

/* CAN identifier type */
#define CAN_ID_STD            ((uint32_t)0x00000000)  /* Standard Id          */
#define CAN_ID_EXT            ((uint32_t)0x00000004)  /* Extended Id          */

/* CAN remote transmission request */
#define CAN_RTR_DATA          ((uint32_t)0x00000000)  /* Data frame           */
#define CAN_RTR_REMOTE        ((uint32_t)0x00000002)  /* Remote frame         */

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
/*CAN_HandleTypeDef    CanHandle;
CAN_FilterConfTypeDef  sFilterConfig;
static CanTxMsgTypeDef        TxMessage;
static CanRxMsgTypeDef        RxMessage;
*/
/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
CAN_msg       CAN_TxMsg[2];                      /* CAN message for sending */
CAN_msg       CAN_RxMsg[2];                      /* CAN message for receiving */

uint32_t CAN_TxRdy[2] = {0,0};              /* CAN HW ready to transmit a message */
uint32_t CAN_RxRdy[2] = {0,0};              /* CAN HW received a message */

static uint32_t CAN_filterIdx[2] = {0,0};        /* static variable for the filter index */
/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
static QueueHandle_t xRxCan1QueueH;
static QueueHandle_t xTxCan1QueueH;

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
int16_t xInit_can1 ( unsigned portBASE_TYPE baud, unsigned portBASE_TYPE queue_length) {
int16_t xReturn;


	/* Create the queues used to hold Rx/Tx characters. */
	xRxCan1QueueH = xQueueCreate( queue_length, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xTxCan1QueueH = xQueueCreate( queue_length + 1, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	
	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxCan1QueueH != serINVALID_QUEUE ) && ( xTxCan1QueueH != serINVALID_QUEUE ) )
	{
		CAN_setup (1);                                  /* setup CAN Controller #1  */
		CAN_wrFilter (1, 0x7E8, STANDARD_FORMAT);          /* Enable reception of msgs */
		CAN_start (1);                                  /* start CAN Controller #1  */

	}
	else
	{
		xReturn =  0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;
}

int16_t xgetc_can1(signed char *pcRxedChar, TickType_t xBlockTime ) {

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxCan1QueueH, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

void xputs_can1( const signed char * const pcString ) {
signed char *pxNext;

	/* NOTE: This implementation does not handle the queue being full as no
	block time is used! */

	/* Send each character in the string, one at a time. */
	pxNext = ( signed char * ) pcString;
	while( *pxNext )
	{
		xputc_can1(*pxNext, serNO_BLOCK );
		pxNext++;
	}
}

/*-----------------------------------------------------------*/

int16_t xputc_can1( signed char cOutChar, TickType_t xBlockTime ) {
int16_t xReturn;

	if( xQueueSend( xTxCan1QueueH, &cOutChar, xBlockTime ) == pdPASS )
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

int16_t xputn_can1 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len) {
int16_t i_cnt;

	/* Send each character in the string, one at a time. */
    for (i_cnt = 0; i_cnt < buf_len; i_cnt++){
        xputc_can1 (buf_ptr[i_cnt], serNO_BLOCK );      
    }
    
    return (i_cnt);
}

int16_t xgetn_can1 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len) {
int16_t i_cnt;
int16_t ret;

    for (i_cnt = 0; i_cnt < buf_len; i_cnt++)  {  
          ret = xgetc_can1((signed char *) buf_ptr++, 1);
          if (ret == pdFALSE) break;
    }

    return (i_cnt);
}

/*-----------------------------------------------------------*/

void vclose_can1(void)
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/

void vCAN1_ISR_HANDLER ( void )
{
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
char cChar;

  /* Check RXNE flag value in ISR register */
  if (LL_USART_IsActiveFlag_RXNE(TELIT_USART_INSTANCE) && LL_USART_IsEnabledIT_RXNE(TELIT_USART_INSTANCE))
  {
    /* RXNE flag will be cleared by reading of RDR register (done in call) */
    /* Call function in charge of handling Character reception */
      cChar = LL_USART_ReceiveData8(TELIT_USART_INSTANCE);
      xQueueSendFromISR( xRxCan1QueueH, &cChar, &xHigherPriorityTaskWoken );
  }
  
  
  if (LL_USART_IsEnabledIT_TXE(TELIT_USART_INSTANCE) && LL_USART_IsActiveFlag_TXE(TELIT_USART_INSTANCE))
  {
    /* TXE flag will be automatically cleared when writing new data in TDR register */

    /* Call function in charge of handling empty DR => will lead to transmission of next character */
    /* The interrupt was caused by the THR becoming empty.  Are there any
    more characters to transmit? */
      if( xQueueReceiveFromISR( xTxCan1QueueH, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
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

/*----------------------------------------------------------------------------
  setup CAN interface
 *----------------------------------------------------------------------------*/
void CAN_setup (uint32_t ctrl)  {
	CAN_TypeDef *pCAN = CAN1;
  	uint32_t BAUDRATE_PRESCALER;
  	uint32_t SJW;
  	uint32_t TSEG1;
  	uint32_t TSEG2;
  	uint32_t TQ;

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_CAN1);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinMode(CANx_TX_GPIO_PORT, CANx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(CANx_RX_GPIO_PORT, CANx_RX_PIN, LL_GPIO_MODE_ALTERNATE);

	LL_GPIO_SetAFPin_8_15(CANx_TX_GPIO_PORT, CANx_TX_PIN, LL_GPIO_AF_9);
	LL_GPIO_SetAFPin_8_15(CANx_RX_GPIO_PORT, CANx_RX_PIN, LL_GPIO_AF_9);

	LL_GPIO_SetPinSpeed(CANx_TX_GPIO_PORT, CANx_TX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);
	LL_GPIO_SetPinSpeed(CANx_RX_GPIO_PORT, CANx_RX_PIN, LL_GPIO_SPEED_FREQ_VERY_HIGH);

	LL_GPIO_SetPinOutputType(CANx_TX_GPIO_PORT, CANx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinOutputType(CANx_RX_GPIO_PORT, CANx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);

	LL_GPIO_SetPinPull(CANx_TX_GPIO_PORT, CANx_TX_PIN, LL_GPIO_PULL_UP);
	LL_GPIO_SetPinPull(CANx_RX_GPIO_PORT, CANx_RX_PIN, LL_GPIO_PULL_UP);





//	pCAN->MCR = (CAN_MCR_INRQ   |           /* initialisation request           */
//			   CAN_MCR_NART    );         /* no automatic retransmission      */

	pCAN->MCR = (CAN_MCR_INRQ);           /* initialisation request           */
			                			/*  automatic retransmission      */
										  /* only FIFO 0, tx mailbox 0 used!  */
	while (!(pCAN->MSR & CAN_MCR_INRQ));



	pCAN->IER = (CAN_IER_FMPIE0 |           /* enable FIFO 0 msg pending IRQ    */
			     CAN_IER_TMEIE    );        /* enable Transmit mbx empty IRQ    */


	TQ = 16;

	/* Note: this calculations fit for CAN (APB1) clock = 42MHz */
	BAUDRATE_PRESCALER  = (80000000 / TQ) / 500000;         /* baudrate is set to 500k bit/s    */



	/* set BTR register so that sample point is at about 71% bit time from bit start */
	/* TSEG1 = 13, TSEG2 = 2, SJW = 1  => 1 CAN bit = 16 TQ, sample at 87.5%      */
	TSEG1 = 13;
	TSEG2 = 2;
	SJW = 1;

	pCAN->BTR &= 0xC0000000;
	pCAN->BTR |=  ((((SJW-1) & 0x03) << 24) | (((TSEG2-1) & 0x07) << 20) | (((TSEG1-1) & 0x0F) << 16) | ((BAUDRATE_PRESCALER-1) & 0x3FF));
	//pCAN->BTR =  0x001c0009;


	CAN_waitReady (1);                              /* wait til tx mbx is empty */

	NVIC_SetPriority(CAN1_RX0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
	NVIC_EnableIRQ(CAN1_RX0_IRQn);

	NVIC_SetPriority(CAN1_TX_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
	NVIC_EnableIRQ(CAN1_TX_IRQn);

}


/*----------------------------------------------------------------------------
  leave initialisation mode
 *----------------------------------------------------------------------------*/
void CAN_start (uint32_t ctrl)  {
  CAN_TypeDef *pCAN = CAN1;

  pCAN->MCR &= ~CAN_MCR_INRQ;             /* normal operating mode, reset INRQ*/
#ifndef __TEST
  while (pCAN->MSR & CAN_MCR_INRQ);
#endif
}

/*----------------------------------------------------------------------------
  set the testmode
 *----------------------------------------------------------------------------*/
void CAN_testmode (uint32_t ctrl, uint32_t testmode) {
  CAN_TypeDef *pCAN = CAN1;

  pCAN->BTR &= ~(CAN_BTR_SILM | CAN_BTR_LBKM);     /* set testmode            */
  pCAN->BTR |=  (testmode & (CAN_BTR_SILM | CAN_BTR_LBKM));
}

/*----------------------------------------------------------------------------
  check if transmit mailbox is empty
 *----------------------------------------------------------------------------*/
void CAN_waitReady (uint32_t ctrl)  {
  CAN_TypeDef *pCAN = CAN1;

  while ((pCAN->TSR & CAN_TSR_TME0) == 0);  /* Transmit mailbox 0 is empty    */
  CAN_TxRdy[ctrl-1] = 1;
}

/*----------------------------------------------------------------------------
  wite a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (uint32_t ctrl, CAN_msg *msg)  {
  CAN_TypeDef *pCAN = CAN1;

  CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */

  pCAN->sTxMailBox[0].TIR  = (uint32_t)0; /* reset TXRQ bit */
                                          /* Setup identifier information */
  if (msg->format == STANDARD_FORMAT) {   /*    Standard ID                   */
    pCAN->sTxMailBox[0].TIR |= (uint32_t)(msg->id << 21) | CAN_ID_STD;
  } else {                                /* Extended ID                      */
    pCAN->sTxMailBox[0].TIR |= (uint32_t)(msg->id <<  3) | CAN_ID_EXT;
  }

                                          /* Setup type information           */
  if (msg->type == DATA_FRAME)  {         /* DATA FRAME                       */
    pCAN->sTxMailBox[0].TIR |= CAN_RTR_DATA;
  } else {                                /* REMOTE FRAME                     */
    pCAN->sTxMailBox[0].TIR |= CAN_RTR_REMOTE;
  }
                                          /* Setup data bytes                 */
  pCAN->sTxMailBox[0].TDLR = (((uint32_t)msg->data[3] << 24) |
                              ((uint32_t)msg->data[2] << 16) |
                              ((uint32_t)msg->data[1] <<  8) |
                              ((uint32_t)msg->data[0]));
  pCAN->sTxMailBox[0].TDHR = (((uint32_t)msg->data[7] << 24) |
                              ((uint32_t)msg->data[6] << 16) |
                              ((uint32_t)msg->data[5] <<  8) |
                              ((uint32_t)msg->data[4])        );
                                          /* Setup length                     */
  pCAN->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
  pCAN->sTxMailBox[0].TDTR |=  (msg->len & CAN_TDT0R_DLC);

  pCAN->IER |= CAN_IER_TMEIE;                 /* enable  TME interrupt        */
  pCAN->sTxMailBox[0].TIR |=  CAN_TI0R_TXRQ;  /* transmit message             */
}

/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg)  {
  CAN_TypeDef *pCAN = CAN1;

                                              /* Read identifier information  */
  if ((pCAN->sFIFOMailBox[0].RIR & CAN_ID_EXT) == 0) {
    msg->format = STANDARD_FORMAT;
    msg->id     = 0x000007FF & (pCAN->sFIFOMailBox[0].RIR >> 21);
  } else {
    msg->format = EXTENDED_FORMAT;
    msg->id     = 0x1FFFFFFF & (pCAN->sFIFOMailBox[0].RIR >> 3);
  }
                                              /* Read type information        */
  if ((pCAN->sFIFOMailBox[0].RIR & CAN_RTR_REMOTE) == 0) {
    msg->type =   DATA_FRAME;
  } else {
    msg->type = REMOTE_FRAME;
  }
                                              /* Read number of rec. bytes    */
  msg->len     = (pCAN->sFIFOMailBox[0].RDTR      ) & 0x0F;
                                              /* Read data bytes              */
  msg->data[0] = (pCAN->sFIFOMailBox[0].RDLR      ) & 0xFF;
  msg->data[1] = (pCAN->sFIFOMailBox[0].RDLR >>  8) & 0xFF;
  msg->data[2] = (pCAN->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
  msg->data[3] = (pCAN->sFIFOMailBox[0].RDLR >> 24) & 0xFF;

  msg->data[4] = (pCAN->sFIFOMailBox[0].RDHR      ) & 0xFF;
  msg->data[5] = (pCAN->sFIFOMailBox[0].RDHR >>  8) & 0xFF;
  msg->data[6] = (pCAN->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
  msg->data[7] = (pCAN->sFIFOMailBox[0].RDHR >> 24) & 0xFF;

  pCAN->RF0R |= CAN_RF0R_RFOM0;             /* Release FIFO 0 output mailbox */
}


/*----------------------------------------------------------------------------
  setup acceptance filter
 *----------------------------------------------------------------------------*/
void CAN_wrFilter (uint32_t ctrl, uint32_t id, uint8_t format)  {
   CAN_TypeDef *pCAN = CAN1;
   uint32_t      CAN_msgId     = 0;

  if (CAN_filterIdx[ctrl-1] > 13) {                 /* check if Filter Memory is full*/
    return;
  }
                                            /* Setup identifier information  */
  if (format == STANDARD_FORMAT)  {         /*   Standard ID                 */
      CAN_msgId |= (uint32_t)(id << 21) | CAN_ID_STD;
  }  else  {                                /*   Extended ID                 */
      CAN_msgId |= (uint32_t)(id <<  3) | CAN_ID_EXT;
  }

  pCAN->FMR  |=   CAN_FMR_FINIT;            /* set initMode for filter banks */
  pCAN->FA1R &=  ~(1UL << CAN_filterIdx[ctrl-1]);   /* deactivate filter             */

                                            /* initialize filter             */
  pCAN->FS1R |= (uint32_t)(1 << CAN_filterIdx[ctrl-1]);     /* set 32-bit scale configuration    */

	/*! !* To disable the CAN Filters: Swap the comment on the next two lines and the two lines after the next line. */
	pCAN->FM1R |= (uint32_t)(1 << CAN_filterIdx[ctrl-1]);   /* set to 32-bit Identifier List mode */
	//pCAN->FM1R |= 0x0;    							/* DISABLES FILTERS  set to 32-bit Identifier Mask mode */

  pCAN->sFilterRegister[CAN_filterIdx[ctrl-1]].FR1 = 0; //CAN_msgId; /*  32-bit identifier   */

	/* !!*  To disable the CAN Filters: Swap the comment on the next two lines.    */
  pCAN->sFilterRegister[CAN_filterIdx[ctrl-1]].FR2 = CAN_msgId; 	/*  32-bit identifier (33) for identifier mode  */
	//pCAN->sFilterRegister[CAN_filterIdx[ctrl-1]].FR2 = 0; 	/*  DISABLES FILTERS  32-bit MASK for mask mode */


  pCAN->FFA1R &= ~(uint32_t)(1 << CAN_filterIdx[ctrl-1]);   /* assign filter to FIFO 0  */
  pCAN->FA1R  |=  (uint32_t)(1 << CAN_filterIdx[ctrl-1]);   /* activate filter          */

  pCAN->FMR &= ~CAN_FMR_FINIT;              /* reset initMode for filterBanks*/

	CAN_filterIdx[ctrl-1]++;                       /* increase filter index  */
}

/*----------------------------------------------------------------------------
  CAN transmit interrupt handler
 *----------------------------------------------------------------------------*/
//void CAN1_TX_IRQHandler (void) {
//
//  if (CAN1->TSR & CAN_TSR_RQCP0) {          /* request completed mbx 0        */
//    CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */
//    CAN1->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
//
//	  CAN_TxRdy[0] = 1;
//  }
//}

/*----------------------------------------------------------------------------
  CAN receive interrupt handler
 *----------------------------------------------------------------------------*/
//void CAN1_RX0_IRQHandler (void) {
//
//  if (CAN1->RF0R & CAN_RF0R_FMP0) {			    /* message pending ?              */
//	  CAN_rdMsg (1, &CAN_RxMsg[0]);           /* read the message               */
//
//    CAN_RxRdy[0] = 1;                       /*  set receive flag              */
//  }
//}
//


/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
