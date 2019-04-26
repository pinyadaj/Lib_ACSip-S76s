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
//can_msg_t       CAN_TxMsg[2];                      /* CAN message for sending */
//can_msg_t       CAN_RxMsg[2];                      /* CAN message for receiving */
//
//uint32_t CAN_TxRdy[2] = {0,0};              /* CAN HW ready to transmit a message */
//uint32_t CAN_RxRdy[2] = {0,0};              /* CAN HW received a message */

//static uint32_t CAN_filterIdx[2] = {0,0};        /* static variable for the filter index */
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
QueueHandle_t xRxCan1QueueH;
QueueHandle_t xTxCan1QueueH;

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
void OS_CAN1_TX_ISR_HANDLER (void) {
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
can_msg_t msg;


	if (CAN1->TSR & CAN_TSR_RQCP0) {          /* request completed mbx 0        */
		CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */

		if (xQueueReceiveFromISR( xTxCan1QueueH, &msg, &xHigherPriorityTaskWoken ) == pdTRUE ) {
			write_ff0_can1 (&msg);
		}
		else {
			CAN1->IER &= ~CAN_IER_TMEIE;            /* disable  TME interrupt         */
		}
		//CAN_TxRdy[0] = 1;
	}

	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );

}



void OS_CAN1_RX0_ISR_HANDLER (void) {
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
can_msg_t msg;

	if (CAN1->RF0R & CAN_RF0R_FMP0) {			/* message pending ?              */
		read_ff0_can1 (&msg);           		/* read the message               */
		xQueueSendFromISR ( xRxCan1QueueH, &msg, &xHigherPriorityTaskWoken );
		//xQueueOverwriteFromISR ( xRxCan1QueueH, &msg, &xHigherPriorityTaskWoken );
	}

	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );

}
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
int16_t os_init_can1 (uint32_t TQ, uint32_t SJW, uint32_t TSEG1, uint32_t TSEG2 ,unsigned portBASE_TYPE baud, unsigned portBASE_TYPE queue_length) {
int16_t xReturn = 1;

	/* Create the queues used to hold Rx/Tx characters. */
	xRxCan1QueueH = xQueueCreate( queue_length, sizeof( can_msg_t) );
	xTxCan1QueueH = xQueueCreate( queue_length + 1, sizeof( can_msg_t) );
	
	/* If the queue/semaphore was created correctly then setup the serial port
	hardware. */
	if( ( xRxCan1QueueH != INVALID_QUEUE ) && ( xTxCan1QueueH != INVALID_QUEUE ) )
	{
	  	uint32_t BAUDRATE_PRESCALER;

	  	/*----------------------------------------------------------------------------
	  	  setup CAN I/O interface
	  	 *----------------------------------------------------------------------------*/

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

		/*----------------------------------------------------------------------------
		  CAN start initial
		 *----------------------------------------------------------------------------*/
	//	pCAN->MCR = (CAN_MCR_INRQ   |           /* initialisation request           */
	//			   CAN_MCR_NART    );         /* no automatic retransmission      */

		CAN1->MCR = (CAN_MCR_INRQ);           /* initialisation request           */
				                			/*  automatic retransmission      */
											  /* only FIFO 0, tx mailbox 0 used!  */
		while (!(CAN1->MSR & CAN_MCR_INRQ));

		/*----------------------------------------------------------------------------
		  CAN baudrate setup
		 *----------------------------------------------------------------------------*/
//		TQ = 16;
		/* Note: this calculations fit for CAN (APB1) clock = 80MHz */
		BAUDRATE_PRESCALER  = (SystemCoreClock / TQ) / baud;         /* baudrate is set to 500k bit/s    */

		/* set BTR register so that sample point is at about 71% bit time from bit start */
		/* TSEG1 = 13, TSEG2 = 2, SJW = 1  => 1 CAN bit = 16 TQ, sample at 87.5%      */
//		TSEG1 = 13;
//		TSEG2 = 2;
//		SJW = 1;

//		TSEG1 = 8;
//		TSEG2 = 7;
//		SJW = 1;

		CAN1->BTR &= 0xC0000000;
		CAN1->BTR |=  ((((SJW-1) & 0x03) << 24) | (((TSEG2-1) & 0x07) << 20) | (((TSEG1-1) & 0x0F) << 16) | ((BAUDRATE_PRESCALER-1) & 0x3FF));

		/*----------------------------------------------------------------------------
		  check if transmit mailbox is empty
		 *----------------------------------------------------------------------------*/
		while ((CAN1->TSR & CAN_TSR_TME0) == 0);  /* Transmit mailbox 0 is empty    */
		//CAN_TxRdy[0] = 1;

		/*----------------------------------------------------------------------------
		  Enable Interrupt
		 *----------------------------------------------------------------------------*/
		NVIC_SetPriority(CAN1_RX0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(CAN1_RX0_IRQn);
		NVIC_SetPriority(CAN1_TX_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
		NVIC_EnableIRQ(CAN1_TX_IRQn);

		CAN1->IER = (CAN_IER_FMPIE0 |           /* enable FIFO 0 msg pending IRQ    */
				     CAN_IER_TMEIE    );        /* enable Transmit mbx empty IRQ    */


		/*----------------------------------------------------------------------------
		  setup acceptance filter
		 *----------------------------------------------------------------------------*/
		//init_filter_ff0_can1 (0, FILTER_LIST_MODE, STANDARD_FORMAT, 0x2FF);          /* Enable reception of msgs id = 0x2FF*/
		//init_filter_ff0_can1 (1, FILTER_LIST_MODE, STANDARD_FORMAT, 0x3F2);          /* Enable reception of msgs id = 0x3F2*/
		init_filter_ff0_can1 (2, FILTER_LIST_MODE, STANDARD_FORMAT, 0x7E8);            /* Enable reception of msgs id = 0x7E8 , ODB2 ADDRESS*/
		//init_filter_ff0_can1 (0, FILTER_MASK_MODE, STANDARD_FORMAT, 0x000);            /* Enable reception all msgs id */

		/*----------------------------------------------------------------------------
		  leave initialisation mode
		*----------------------------------------------------------------------------*/
		CAN1->MCR &= ~CAN_MCR_INRQ;             /* normal operating mode, reset INRQ*/


	}
	else
	{
		xReturn =  0;
	}

	/* This demo file only supports a single port but we have to return
	something to comply with the standard demo header file. */
	return xReturn;
}

int16_t os_read_ff0_can1 (can_msg_t *msg_ptr, TickType_t xBlockTime ) {

	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxCan1QueueH, msg_ptr, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

/*-----------------------------------------------------------*/
int16_t os_write_ff0_can1 (can_msg_t *msg_ptr, TickType_t xBlockTime ) {
int16_t xReturn = pdPASS;

	if ((CAN1->sTxMailBox[0].TIR & CAN_TI0R_TXRQ) == 0) {  /* check empty transmit*/
		write_ff0_can1 (msg_ptr);
		CAN1->IER |= CAN_IER_TMEIE;                 /* enable  TME interrupt        */
	}
	else if( xQueueSend( xTxCan1QueueH, msg_ptr, xBlockTime ) == pdPASS ) {
		xReturn = pdPASS;
	}
	else {
		xReturn = pdFAIL;
	}

	return xReturn;
}


/*-----------------------------------------------------------*/

void vclose_can1(void)
{
	/* Not supported as not required by the demo application. */
}
/*-----------------------------------------------------------*/


/*----------------------------------------------------------------------------
  wite a message to CAN peripheral and transmit it
 *----------------------------------------------------------------------------*/
void write_ff0_can1 (can_msg_t *msg)  {
  CAN1->TSR |= CAN_TSR_RQCP0;             /* reset request complete mbx 0   */

  CAN1->sTxMailBox[0].TIR  = (uint32_t)0; /* reset TXRQ bit */
                                          /* Setup identifier information */
  if (msg->format == STANDARD_FORMAT) {   /*    Standard ID                   */
	  CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id << 21) | CAN_ID_STD;
  } else {                                /* Extended ID                      */
	  CAN1->sTxMailBox[0].TIR |= (uint32_t)(msg->id <<  3) | CAN_ID_EXT;
  }

                                          /* Setup type information           */
  if (msg->type == DATA_FRAME)  {         /* DATA FRAME                       */
	  CAN1->sTxMailBox[0].TIR |= CAN_RTR_DATA;
  } else {                                /* REMOTE FRAME                     */
	  CAN1->sTxMailBox[0].TIR |= CAN_RTR_REMOTE;
  }
                                          /* Setup data bytes                 */
  CAN1->sTxMailBox[0].TDLR = (((uint32_t)msg->data[3] << 24) |
                              ((uint32_t)msg->data[2] << 16) |
                              ((uint32_t)msg->data[1] <<  8) |
                              ((uint32_t)msg->data[0]));
  CAN1->sTxMailBox[0].TDHR = (((uint32_t)msg->data[7] << 24) |
                              ((uint32_t)msg->data[6] << 16) |
                              ((uint32_t)msg->data[5] <<  8) |
                              ((uint32_t)msg->data[4])        );
                                          /* Setup length                     */
  CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
  CAN1->sTxMailBox[0].TDTR |=  (msg->len & CAN_TDT0R_DLC);

 // CAN1->IER |= CAN_IER_TMEIE;                 /* enable  TME interrupt        */
  CAN1->sTxMailBox[0].TIR |=  CAN_TI0R_TXRQ;  /* transmit message             */
}

/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it
 *----------------------------------------------------------------------------*/
void read_ff0_can1 (can_msg_t *msg)  {
                                              /* Read identifier information  */
  if ((CAN1->sFIFOMailBox[0].RIR & CAN_ID_EXT) == 0) {
    msg->format = STANDARD_FORMAT;
    msg->id     = 0x000007FF & (CAN1->sFIFOMailBox[0].RIR >> 21);
  } else {
    msg->format = EXTENDED_FORMAT;
    msg->id     = 0x1FFFFFFF & (CAN1->sFIFOMailBox[0].RIR >> 3);
  }
                                              /* Read type information        */
  if ((CAN1->sFIFOMailBox[0].RIR & CAN_RTR_REMOTE) == 0) {
    msg->type =   DATA_FRAME;
  } else {
    msg->type = REMOTE_FRAME;
  }
                                              /* Read number of rec. bytes    */
  msg->len     = (CAN1->sFIFOMailBox[0].RDTR      ) & 0x0F;
                                              /* Read data bytes              */
  msg->data[0] = (CAN1->sFIFOMailBox[0].RDLR      ) & 0xFF;
  msg->data[1] = (CAN1->sFIFOMailBox[0].RDLR >>  8) & 0xFF;
  msg->data[2] = (CAN1->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
  msg->data[3] = (CAN1->sFIFOMailBox[0].RDLR >> 24) & 0xFF;

  msg->data[4] = (CAN1->sFIFOMailBox[0].RDHR      ) & 0xFF;
  msg->data[5] = (CAN1->sFIFOMailBox[0].RDHR >>  8) & 0xFF;
  msg->data[6] = (CAN1->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
  msg->data[7] = (CAN1->sFIFOMailBox[0].RDHR >> 24) & 0xFF;

  CAN1->RF0R |= CAN_RF0R_RFOM0;             /* Release FIFO 0 output mailbox */
}


/*----------------------------------------------------------------------------
  setup acceptance filter
 *----------------------------------------------------------------------------*/
void init_filter_ff0_can1 (uint32_t CAN_filterIdx, uint32_t filer_mode, uint8_t format,  uint32_t id){
//   static unsigned short CAN_filterIdx = 0;
   uint32_t      CAN_msgId     = 0;

  if (CAN_filterIdx > 13) {                 /* check if Filter Memory is full*/
	  CAN_filterIdx = 13;
  }


                                            /* Setup identifier information  */
  if (format == STANDARD_FORMAT)  {         /*   Standard ID                 */
      CAN_msgId |= (uint32_t)(id << 21) | CAN_ID_STD;
  }  else  {                                /*   Extended ID                 */
      CAN_msgId |= (uint32_t)(id <<  3) | CAN_ID_EXT;
  }

  CAN1->FMR  |=   CAN_FMR_FINIT;            /* set initMode for filter banks */
  CAN1->FA1R &=  ~(1UL << CAN_filterIdx);   /* deactivate filter             */

                                            /* initialize filter             */
  CAN1->FS1R |= (uint32_t)(1 << CAN_filterIdx);     /* set 32-bit scale configuration    */

	/*! !* To disable the CAN Filters: Swap the comment on the next two lines and the two lines after the next line. */
  if (filer_mode == FILTER_LIST_MODE) {
	  CAN1->FM1R |= (uint32_t)(1 << CAN_filterIdx);   /* set to 32-bit Identifier List mode */

  }
  else {
	  CAN1->FM1R &= (uint32_t)~(1 << CAN_filterIdx);     							/* DISABLES FILTERS  set to 32-bit Identifier Mask mode */

  }
  CAN1->sFilterRegister[CAN_filterIdx].FR1 = CAN_msgId; //CAN_msgId; /*  32-bit identifier   */

	/* !!*  To disable the CAN Filters: Swap the comment on the next two lines.    */
  CAN1->sFilterRegister[CAN_filterIdx].FR2 = CAN_msgId; 	/*  32-bit identifier (33) for identifier mode  */
	//pCAN->sFilterRegister[CAN_filterIdx].FR2 = 0; 	/*  DISABLES FILTERS  32-bit MASK for mask mode */


  CAN1->FFA1R &= ~(uint32_t)(1 << CAN_filterIdx);   /* assign filter to FIFO 0  */
  CAN1->FA1R  |=  (uint32_t)(1 << CAN_filterIdx);   /* activate filter          */

  CAN1->FMR &= ~CAN_FMR_FINIT;              /* reset initMode for filterBanks*/

	//CAN_filterIdx++;                       /* increase filter index  */

}

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
