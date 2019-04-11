//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : template.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : template.c example Implementation
//; Create(dd/mm/yy) : 5/7/2016
//; [Revision and Description]
//; Rev1.0 - 5/7/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#include "app_trns-task.h"



// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
QueueHandle_t xQueueTransH = 0;
TaskHandle_t xTranRcvH = NULL;
TaskHandle_t xTranXmitH = NULL;
SemaphoreHandle_t xTransSem;
/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

//SemaphoreHandle_t xSendTransSem = NULL;
/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
enum {
    TRNS_XMIT_IDLE = 0,
    TRNS_XMIT_TRANSPARENT_UART1,
	TRNS_XMIT_TRANSPARENT_UART2,
	TRNS_XMIT_TRANSPARENT_UART3,
    TRNS_XMIT_TRANSPARENT_UART4,
    TRNS_XMIT_TRANSPARENT_UART5,
    TRNS_XMIT_TRANSTACK_UART1,
	TRNS_XMIT_TRANSTACK_UART2,
    TRNS_XMIT_TRANSTACK_UART4, 
    TRNS_XMIT_TRANSTACK_UART5
} proc_trns_xmit_state; 

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */
static void os_transtack_xmit_task (void *pvParameters);
static void os_transtack_rcv_task  (void *pvParameters);

_SRAM2 conf_trns_t config_trns_uart1;
//conf_trns_t config_trns_uart2;
_SRAM2 conf_trns_t config_trns_uart4;
//conf_trns_t config_trns_uart5;

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
void os_transtack_task_create (void) {

int ret;
//    ret =  init_trns_dl (&config_trns_uart1, MODE_SLAVE, SELF_ADDRESS,
//                         snd_cnf_cbk_uart1, rcv_ind_cbk_uart1, tmout_ind_cbk_uart1,
//                         0, os_write_uart1, os_read_uart1);

    ret =  init_trns_dl (&config_trns_uart1, MODE_SLAVE, SELF_ADDRESS,
                         snd_cnf_cbk_uart5, rcv_ind_cbk_uart5, tmout_ind_cbk_uart5,
                         0, os_write_uart5, os_read_uart5);

//    ret =  init_trns_dl (&config_trns_uart2, SELF_ADDRESS,
//                         snd_cnf_cbk_uart2, rcv_ind_cbk_uart2, tmout_ind_cbk_uart2,
//                         0, xputn_uart2, xgetn_uart2);

    ret =  init_trns_dl (&config_trns_uart4, MODE_MASTER, SELF_ADDRESS,
                         snd_cnf_cbk_uart4, rcv_ind_cbk_uart4, tmout_ind_cbk_uart4,
                         0, os_write_uart4, os_read_uart4);

//    ret =  init_trns_dl (&config_trns_uart5, SELF_ADDRESS,
//                         snd_cnf_cbk_uart5, rcv_ind_cbk_uart5, tmout_ind_cbk_uart5,
//                         0, xputn_uart5, xgetn_uart5);

//    ret =  init_trns_dl (&config_trns_uart5, MODE_SLAVE, SELF_ADDRESS,
//                         snd_cnf_cbk_uart5, rcv_ind_cbk_uart5, tmout_ind_cbk_uart5,
//                         0, os_write_uart5, os_read_uart5);

//   snd_trns_dl (&config_trns_uart4,
//                0,      //Destination Address
//                0,     //Self Address or Source Address
//                CTRL_NORMAL_PKT,
//                HDR_TYP_REQ_PKT,  //HEADER TYPE
//                NULL, 0);
//
   

BaseType_t  xReturned;

  /* Create the task, storing the handle. */
  xReturned = xTaskCreate(os_transtack_xmit_task,       /* Function that implements the task. */
                          "TRANS1",          /* Text name for the task. */
						  1024,      /* Stack size in words, not bytes. */
                          ( void * ) NULL,    /* Parameter passed into the task. */
                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
                          &xTranXmitH );      /* Used to pass out the created task's handle. */

  /* Create the task, storing the handle. */
  xReturned = xTaskCreate(os_transtack_rcv_task,       /* Function that implements the task. */
                          "TRANS2",          /* Text name for the task. */
						  1024,      /* Stack size in words, not bytes. */
                          ( void * ) NULL,    /* Parameter passed into the task. */
                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
                          &xTranRcvH );      /* Used to pass out the created task's handle. */

    /* Create a queue capable of containing 10 unsigned long values. */
   
    xQueueTransH = xQueueCreate(4, sizeof(queue_trns_t));

    if(xQueueTransH == NULL )
    {
    	LOG_ERROR ("[SYSTEM]: Transtack Task Cannot Create Queue!!...\r\n");
      for( ;; );
        /* Queue was not created and must not be used. */
    }  



   // xSendTransSem = xSemaphoreCreateBinary();
	//xSemaphoreGive( xSendTransSem );
}


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */



_SRAM2 char uart_buf[2048];
_SRAM2 int32_t len_uart_buf;

static void os_transtack_rcv_task( void *pvParameters ) {

    portTickType xLastExecutionTime;
    xLastExecutionTime = xTaskGetTickCount();

//    LOG_INFO ("[SYSTEM]: Transtack Task Started...\r\n");

    for( ;; ){


        if (config_trns_uart1.mode == 0) {
        	process_trns_dl (&config_trns_uart1);
        }else {
        	len_uart_buf = os_read_uart1 (0, &uart_buf[0], 2048);

    		if (len_uart_buf > 0 ) {
    		//	 xSemaphoreTake (xSendTransSem, portMAX_DELAY);
    			 os_write_uart1 (0, &uart_buf[0], len_uart_buf);
    		//	 xSemaphoreGive (xSendTransSem);
    		}
        }


//        if (config_trns_uart2.mode == 0) {
//        	process_trns_dl (&config_trns_uart2);
//        }else
//
//        {
//        	len_uart_buf = xgetn_uart2 (0, &uart_buf[0], 2048);
//
//    		if (len_uart_buf > 0 ) {
//    		//	xSemaphoreTake (xSendTransSem, portMAX_DELAY);
//    			 xputn_uart1 (0, &uart_buf[0], len_uart_buf);
//    		//	 xSemaphoreGive (xSendTransSem);
//    		}
//        }


        if (config_trns_uart4.mode == 0) {
        	process_trns_dl (&config_trns_uart4);
        }else
        {
        	len_uart_buf = os_read_uart4 (0, &uart_buf[0], 2048);

    		if (len_uart_buf > 0 ) {
    			// xSemaphoreTake (xSendTransSem, portMAX_DELAY);
    		//	os_write_uart1 (0, &uart_buf[0], len_uart_buf);
    			os_write_uart5 (0, &uart_buf[0], len_uart_buf);
    			// xSemaphoreGive (xSendTransSem);
    		}
        }


//        if (config_trns_uart5.mode == 0) {
//        	process_trns_dl (&config_trns_uart5);
//        }else{
//        	len_uart_buf = xgetn_uart5 (0, &uart_buf[0], 2048);
//
//    		if (len_uart_buf > 0 ) {
//    		//	 xSemaphoreTake (xSendTransSem, portMAX_DELAY);
//    			 xputn_uart1 (0, &uart_buf[0], len_uart_buf);
//    		//	 xSemaphoreGive (xSendTransSem);
//    		}
//        }




    }
}


static void os_transtack_xmit_task( void *pvParameters ) {
    queue_trns_t queue_trns;
    
    proc_trns_xmit_state = TRNS_XMIT_IDLE;

    for( ;; ){
       // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

        switch (proc_trns_xmit_state) {
          case TRNS_XMIT_IDLE:
        
            // Wait receive Queue 
            if (xQueueTransH != NULL) {
              // Receive a message on the created queue.  Block for 1 ticks if a
              // message is not immediately available.
                if( xQueueReceive( xQueueTransH, &queue_trns, ( TickType_t )10))
                {
                  if (queue_trns.dst_addr == (LOGI_UART1_TRNSPRNT_ADDR | SELF_ADDRESS))      proc_trns_xmit_state = TRNS_XMIT_TRANSPARENT_UART1;
                  else if (queue_trns.dst_addr == (LOGI_UART2_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_trns_xmit_state = TRNS_XMIT_TRANSPARENT_UART2;

                  else if (queue_trns.dst_addr == (LOGI_UART4_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_trns_xmit_state = TRNS_XMIT_TRANSPARENT_UART4;
                  else if (queue_trns.dst_addr == (LOGI_UART5_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_trns_xmit_state = TRNS_XMIT_TRANSPARENT_UART5;
                  else if (queue_trns.dst_addr == (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS))  proc_trns_xmit_state = TRNS_XMIT_TRANSTACK_UART1;
                  else if (queue_trns.dst_addr == (LOGI_UART2_TRNSTCK_ADDR | SELF_ADDRESS))  proc_trns_xmit_state = TRNS_XMIT_TRANSTACK_UART2;
            //      else if (queue_trns.dst_addr == (LOGI_UART3_TRNSTCK_ADDR | SELF_ADDRESS))  proc_trns_xmit_state = TRNS_XMIT_TRANSTACK_UART3;
                  else if (queue_trns.dst_addr == (LOGI_UART4_TRNSTCK_ADDR | SELF_ADDRESS))  proc_trns_xmit_state = TRNS_XMIT_TRANSTACK_UART4;
                  else if (queue_trns.dst_addr == (LOGI_UART5_TRNSTCK_ADDR | SELF_ADDRESS))  proc_trns_xmit_state = TRNS_XMIT_TRANSTACK_UART5;
                  //else proc_trns_xmit_state = TRNS_XMIT_TRANSPARENT_UART2;
                }
            }
            
            break;
            
          case TRNS_XMIT_TRANSTACK_UART1:
        	  config_trns_uart1.mode = 0;
        	 // xSemaphoreTake (xSendTransSem, portMAX_DELAY);
              snd_trns_dl (&config_trns_uart1,
            		  	    queue_trns.src_addr,      //Destination Address
                            (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
                            HDR_TYP_REP_PKT,  //HEADER TYPE
                           &queue_trns.buf_pt[0], queue_trns.len);
              //xSemaphoreGive (xSendTransSem);
              proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;
            
          case TRNS_XMIT_TRANSTACK_UART2:
//        	  config_trns_uart2.mode = 0;
//        	//  xSemaphoreTake (xSendTransSem, portMAX_DELAY);
//              snd_trns_dl (&config_trns_uart2,
//            		  	  	queue_trns.src_addr,      //Destination Address
//                            (LOGI_UART2_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
//                            CTRL_NORMAL_PKT,
//							HDR_TYP_REP_PKT,  //HEADER TYPE
//                           &queue_trns.buf_pt[0], queue_trns.len);
//            //  xSemaphoreGive (xSendTransSem);
              proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;

          case TRNS_XMIT_TRANSTACK_UART4:
        	  config_trns_uart4.mode = 0;
        	//  xSemaphoreTake (xSendTransSem, portMAX_DELAY);
              snd_trns_dl (&config_trns_uart4,
            		  	  	queue_trns.src_addr,      //Destination Address
                            (LOGI_UART4_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
							HDR_TYP_REP_PKT,  //HEADER TYPE
                           &queue_trns.buf_pt[0], queue_trns.len);
           //   xSemaphoreGive (xSendTransSem);
              proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;
            
          case TRNS_XMIT_TRANSTACK_UART5:
  //      	  config_trns_uart5.mode = 0;
//        	//  xSemaphoreTake (xSendTransSem, portMAX_DELAY);
//              snd_trns_dl (&config_trns_uart5,
//            		  	  	queue_trns.src_addr,      //Destination Address
//                            (LOGI_UART5_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
//                            CTRL_NORMAL_PKT,
//							HDR_TYP_REP_PKT,  //HEADER TYPE
//                            &queue_trns.buf_pt[0], queue_trns.len);
//            //  xSemaphoreGive (xSendTransSem);
              proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;    
            
          case TRNS_XMIT_TRANSPARENT_UART1:
        	config_trns_uart1.mode = 1;

        	//xSemaphoreTake (xSendTransSem, portMAX_DELAY);
            os_write_uart1 (0, &queue_trns.buf_pt[0], queue_trns.len);
            //xSemaphoreGive (xSendTransSem);
            proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;
            
          case TRNS_XMIT_TRANSPARENT_UART2:
        	//config_trns_uart2.mode = 1;
        //	xSemaphoreTake (xSendTransSem, portMAX_DELAY);
            //os_write_uart2 (0, &queue_trns.buf_pt[0], queue_trns.len);
//            snd_trns_dl (&config_trns_uart1,
//          		  	    queue_trns.src_addr,      //Destination Address
//                          (LOGI_UART2_TRNSPRNT_ADDR | SELF_ADDRESS),     //Self Address or Source Address
//                          CTRL_NORMAL_PKT,
//                          HDR_TYP_REP_PKT,  //HEADER TYPE
//                         NULL, 0);
         //   xSemaphoreGive (xSendTransSem);
            proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;

          case TRNS_XMIT_TRANSPARENT_UART3:
            proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;            
          

          case TRNS_XMIT_TRANSPARENT_UART4:
        	config_trns_uart4.mode = 1;
//        //	xSemaphoreTake (xSendTransSem, portMAX_DELAY);
            os_write_uart4 (0, &queue_trns.buf_pt[0], queue_trns.len);
//       //     xSemaphoreGive (xSendTransSem);
            proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;
            
          case TRNS_XMIT_TRANSPARENT_UART5:
        	//config_trns_uart5.mode = 1;
        //	xSemaphoreTake (xSendTransSem, portMAX_DELAY);
            //os_write_uart5 (0, &queue_trns.buf_pt[0], queue_trns.len);
         //   xSemaphoreGive (xSendTransSem);
            break;
          default :
            proc_trns_xmit_state = TRNS_XMIT_IDLE;
            break;
        }

    }
}

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
