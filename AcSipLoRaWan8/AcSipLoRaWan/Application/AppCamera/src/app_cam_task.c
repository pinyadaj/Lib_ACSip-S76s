//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_cam_task.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : Camera Aplication Implementation
//; Create(dd/mm/yy) : 15/10/2016
//; [Revision and Description]
//; Rev1.0 - 15/10/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "app_cam_task.h"
#include "app_trns-task.h"
#include "app_sdcard_task.h"

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */


/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
TaskHandle_t xCameraH = NULL;

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
queue_trns_t queue_trns;
queue_trns_t* queue_trns_ptr;
uint8_t EndFlag = 0;
uint8_t cam_buf [138];
cam_data_t cam_data;
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

static void vCameraTask( void *pvParameters );



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
void xCamTaskCreate (void) {

BaseType_t  xReturned;

  /* Create the task, storing the handle. */
  xReturned = xTaskCreate(vCameraTask,       /* Function that implements the task. */
                          "CAM",          /* Text name for the task. */
                          2048,      /* Stack size in words, not bytes. */
                          ( void * ) NULL,    /* Parameter passed into the task. */
                          tskIDLE_PRIORITY+1,/* Priority at which the task is created. */
                          &xCameraH );      /* Used to pass out the created task's handle. */

}


static void vCameraTask( void *pvParameters ) {
/*portTickType xLastExecutionTime;
xLastExecutionTime = xTaskGetTickCount();


cam_data.cam_buf_ptr = &cam_buf[0];
cam_data.cam_len = 138;
cam_data.cam_addr = 0;
cam_data_t *cam_data_ptr;
uint16_t tmp_cnt = 0;
uint16_t cam_try = 0;
static queue_sdcard_t queue_sdcard;
queue_sdcard_t* queue_sdcard_ptr;

queue_trns_ptr = &queue_trns;

  LL_USART_SetBaudRate(AUX_USART_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 38400); 
  reset_camera_ls_y201();
  baudrate_camera_ls_y201 (115200);
  vTaskDelay (100);
  LL_USART_SetBaudRate(AUX_USART_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 115200);  
  */
	printf ("[SYSTEM]: CAM(RS485) Task Started...\r\n");

	portTickType xLastExecutionTime;

	// Initialise the xLastWakeTime variable with the current time.
	xLastExecutionTime = xTaskGetTickCount();

	for( ;; ){

	  //vTaskDelay (10);
	  vTaskDelayUntil( &xLastExecutionTime,50);

//	  if (config_trns_uart4.mode == 1) {
//			len_uart4_buf = (int32_t)os_read_uart4 (0, &uart4_buf[0], 2048);
//
//			if (len_uart4_buf > 0 ) {
//				 os_write_uart1 (0, &uart4_buf[0], len_uart4_buf);
//			}
//      }

       /*stop_take_photo_camera_ls_y201();
       vTaskDelay (20);
       take_photo_camera_ls_y201();
       cam_data.cam_addr = 0; 
        while(1) {
            cam_data_ptr = read_data_camera_ls_y201 (&cam_data);
           
            if (cam_data_ptr != NULL) {

                if( xSemaphoreTake( xSDCardSem, portMAX_DELAY ) == pdTRUE )
                {
                     We were able to obtain the semaphore and can now access the
                    shared resource.

					queue_sdcard_ptr = &queue_sdcard;
					queue_sdcard.dst_addr = LOGI_SDCARD_ADDR;
					queue_sdcard.src_addr = LOGI_CAMERA_LS_Y201;
					memcpy (&queue_sdcard.buf[0],cam_data_ptr->cam_buf_ptr, cam_data_ptr->cam_len);
					queue_sdcard.buf_len = cam_data_ptr->cam_len;
					xQueueSend ( xQueueSDCardH, &queue_sdcard_ptr, portMAX_DELAY );

					 We have finished accessing the shared resource.  Release the
					semaphore.
					xSemaphoreGive( xSDCardSem );
                }
                else
                {
                     We could not obtain the semaphore and can therefore not access
                    the shared resource safely.
                }
               

                cam_data.cam_addr += 128; 
                cam_data.cam_buf_ptr = &cam_buf[0];
                cam_data.cam_len = 138;
                
                if (cam_data_ptr->cam_status == JPEG_LAST){
                    stop_take_photo_camera_ls_y201();
                    break;
                }
            
            }
            else {
                cam_try++;
                if (cam_try == 5) {
                    cam_try = 0;
                    baudrate_camera_ls_y201 (38400);
                    LL_USART_SetBaudRate(AUX_USART_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 38400); 
                    reset_camera_ls_y201();
                    baudrate_camera_ls_y201 (115200);
                    LL_USART_SetBaudRate(AUX_USART_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 115200);  
 
                    break;
                }
            }
        }
       */
      // vTaskDelay (5000);
  }
}

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
