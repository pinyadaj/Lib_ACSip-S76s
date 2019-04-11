//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_obd2_task.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : template.c example Implementation
//; Create(dd/mm/yy) : 19/10/2016
//; [Revision and Description]
//; Rev1.0 - 19/10/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/


/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "main.h"
#include "common.h"

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */


/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
TaskHandle_t xGPSH = NULL;
QueueHandle_t xQueueGPSH = 0;
SemaphoreHandle_t xGPSSem = NULL;
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
char read_buf[256];
uint16_t len_read_buf = 0;

int16_t len_gnrmc_packet = 0;
int16_t len_gnrmc_buf = 0;
char gnrmc_buf[256];
conf_gps_t gps_gnrmc_conf;


char gpgsv_buf[256];
int16_t len_gpgsv_packet = 0;
int16_t len_gpgsv_buf = 0;
conf_gps_t gps_gpgsv_conf;

char gpgsa_buf[256];
int16_t len_gpgsa_packet = 0;
int16_t len_gpgsa_buf = 0;
conf_gps_t gps_gpgsa_conf;

pktGPS_t pkt_gps;

/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
enum {
    GPS_XMIT_IDLE = 0,
    GPS_XMIT_TRANSPARENT_UART1,
	GPS_XMIT_TRANSPARENT_UART2,
    GPS_XMIT_TRANSPARENT_UART4,
    GPS_XMIT_TRANSPARENT_UART5,
    GPS_XMIT_TRANSTACK_UART1,
	GPS_XMIT_TRANSTACK_UART2,
    GPS_XMIT_TRANSTACK_UART4,
    GPS_XMIT_TRANSTACK_UART5,
	GPS_XMIT_GPS
} proc_gps_xmit_state;

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */

static void vGPSRcvTask ( void *pvParameters );
static void vGPSXmitTask ( void *pvParameters );

//void print_gps_gnrmc_info (void);


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
int16_t xGPSTaskCreate (void) {

BaseType_t  xReturned;

/* Create the task, storing the handle. */
xReturned = xTaskCreate (vGPSRcvTask,       /* Function that implements the task. */
					   	 "GPSRx",          /* Text name for the task. */
						 512,      /* Stack size in words, not bytes. */
					     (void *) NULL,    /* Parameter passed into the task. */
					     tskIDLE_PRIORITY,/* Priority at which the task is created. */
					     &xGPSH );      /* Used to pass out the created task's handle. */

xReturned = xTaskCreate (vGPSXmitTask,       /* Function that implements the task. */
					   	 "GPSTx",          /* Text name for the task. */
						 512,      /* Stack size in words, not bytes. */
					     (void *) NULL,    /* Parameter passed into the task. */
					     tskIDLE_PRIORITY,/* Priority at which the task is created. */
					     &xGPSH );      /* Used to pass out the created task's handle. */

init_gps (&gps_gnrmc_conf, GNRMC_TYPE, &gnrmc_buf[0], 256);
init_gps (&gps_gpgsv_conf, GPGSV_TYPE, &gpgsv_buf[0], 256);
init_gps (&gps_gpgsa_conf, GPGSA_TYPE, &gpgsa_buf[0], 256);

xGPSSem = xSemaphoreCreateBinary();
xSemaphoreGive( xGPSSem );

xQueueGPSH = xQueueCreate(4 ,sizeof( queue_trns_t ));

if(xQueueGPSH == NULL )
{
	os_puts_uart2 ("[SYSTEM]: GPS Task Cannot Create Queue!!...\r\n");
  for( ;; );
    /* Queue was not created and must not be used. */
}

return 1;
}


static void vGPSRcvTask ( void *pvParameters ) {
portTickType xLastExecutionTime;
xLastExecutionTime = xTaskGetTickCount();

  for( ;; ){
        /* toggle LED2*/
      // LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);

	//  	vTaskDelay (10);
		len_read_buf = os_read_uart5 (0, &read_buf[0], 256);

		if (len_read_buf > 0 ) {
			//xputn_uart2(0, &read_buf[0], len_read_buf);
			len_gnrmc_buf = len_gpgsv_buf = len_gpgsa_buf = len_read_buf;

			while ((len_gnrmc_buf > 0) || (len_gpgsa_buf > 0)) {
				if (len_gnrmc_buf > 0) len_gnrmc_packet = split_pkt_gps (&gps_gnrmc_conf, &read_buf[len_read_buf - len_gnrmc_buf], &len_gnrmc_buf);
				if (len_gpgsv_buf > 0) len_gpgsv_packet = split_pkt_gps (&gps_gpgsv_conf, &read_buf[len_read_buf - len_gpgsv_buf], &len_gpgsv_buf);
				if (len_gpgsa_buf > 0) len_gpgsa_packet = split_pkt_gps (&gps_gpgsa_conf, &read_buf[len_read_buf - len_gpgsa_buf], &len_gpgsa_buf);

				if (len_gnrmc_packet > 0) {
					//xputs_uart2("\f\n\r");
					//xputn_uart2(0, &gnrmc_buf[0], len_gnrmc_packet);
					//xputs_uart2("\n\r");

					//sprintf(temp_buf, "sizeof(double) : %u byte\n\r", sizeof(double));
					//xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

					//sprintf(temp_buf, "sizeof(float) : %u byte\n\r", sizeof(float));
					//xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
					xSemaphoreTake (xGPSSem, portMAX_DELAY);
					split_gprmc(&gps_gnrmc_conf, &pkt_gps.pkt_gprmc);
					xSemaphoreGive (xGPSSem);
				}

				if (len_gpgsv_packet > 0) {
					//xputn_uart2(0, &gpgsv_buf[0], len_gpgsv_packet);
					//xputs_uart2("\n\r");
				}

				if (len_gpgsa_packet > 0) {
					//xputs_uart2("\n\r");
					//xputn_uart2(0, &gpgsa_buf[0], len_gpgsa_packet);
					//xputs_uart2("\n\r");
					xSemaphoreTake (xGPSSem, portMAX_DELAY);
					split_gpgsa(&gps_gpgsa_conf, &pkt_gps.pkt_gpgsa);
					xSemaphoreGive (xGPSSem);
				}
			}

			print_gps_gnrmc_info ();


		}
  }
}


static void vGPSXmitTask( void *pvParameters ) {
    queue_trns_t queue_trns;
    proc_gps_xmit_state = GPS_XMIT_IDLE;

    for( ;; )
    {
       // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

        switch (proc_gps_xmit_state) {
          case GPS_XMIT_IDLE:

            // Wait receive Queue
            if (xQueueGPSH != 0) {
              // Receive a message on the created queue.  Block for 1 ticks if a
              // message is not immediately available.
                if( xQueueReceive( xQueueGPSH, &queue_trns, 10))
                {
                  if (queue_trns.dst_addr == (LOGI_UART1_TRNSPRNT_ADDR | SELF_ADDRESS))      proc_gps_xmit_state  = GPS_XMIT_TRANSPARENT_UART1;
                  else if (queue_trns.dst_addr == (LOGI_UART2_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_gps_xmit_state = GPS_XMIT_TRANSPARENT_UART2;
                  else if (queue_trns.dst_addr == (LOGI_UART4_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_gps_xmit_state = GPS_XMIT_TRANSPARENT_UART4;
                  else if (queue_trns.dst_addr == (LOGI_UART5_TRNSPRNT_ADDR | SELF_ADDRESS)) proc_gps_xmit_state = GPS_XMIT_TRANSPARENT_UART5;
                  else if (queue_trns.dst_addr == (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS))  proc_gps_xmit_state = GPS_XMIT_TRANSTACK_UART1;
                  else if (queue_trns.dst_addr == (LOGI_UART2_TRNSTCK_ADDR | SELF_ADDRESS))  proc_gps_xmit_state = GPS_XMIT_TRANSTACK_UART2;
                  else if (queue_trns.dst_addr == (LOGI_UART4_TRNSTCK_ADDR | SELF_ADDRESS))  proc_gps_xmit_state = GPS_XMIT_TRANSTACK_UART4;
                  else if (queue_trns.dst_addr == (LOGI_UART5_TRNSTCK_ADDR | SELF_ADDRESS))  proc_gps_xmit_state = GPS_XMIT_TRANSTACK_UART5;
                  else if (queue_trns.dst_addr == (LOGI_GPS_ADDR | SELF_ADDRESS))  		  proc_gps_xmit_state = GPS_XMIT_GPS;
                  else proc_gps_xmit_state = GPS_XMIT_GPS;
                }
            }

            break;

          case GPS_XMIT_TRANSTACK_UART1:
              snd_trns_dl (&config_trns_uart1,
            		  	  	queue_trns.src_addr,      //Destination Address (Reply to Request Address)
                            (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
                            HDR_TYP_REQ_PKT,  //HEADER TYPE
                           &queue_trns.buf_pt[0], queue_trns.len);

              proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSTACK_UART2:
              snd_trns_dl (&config_trns_uart2,
            		  queue_trns.src_addr,     //Destination Address (Reply to Request Address)
                            (LOGI_UART2_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
                            HDR_TYP_REQ_PKT,  //HEADER TYPE
                           &queue_trns.buf_pt[0], queue_trns.len);

              proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSTACK_UART4:
              snd_trns_dl (&config_trns_uart4,
            		  queue_trns.src_addr,      //Destination Address (Reply to Request Address)
                            (LOGI_UART4_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
                            HDR_TYP_REQ_PKT,  //HEADER TYPE
                           &queue_trns.buf_pt[0], queue_trns.len);
              proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSTACK_UART5:
              snd_trns_dl (&config_trns_uart5,
            		  	  	queue_trns.src_addr,      //Destination Address (Reply to Request Address)
                            (LOGI_UART5_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
                            CTRL_NORMAL_PKT,
                            HDR_TYP_REQ_PKT,  //HEADER TYPE
                            &queue_trns.buf_pt[0], queue_trns.len);
              proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSPARENT_UART1:
            os_write_uart1 (0, &queue_trns.buf_pt[0], queue_trns.len);
            proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSPARENT_UART2:
            os_write_uart2 (0, &queue_trns.buf_pt[0], queue_trns.len);
            proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSPARENT_UART4:
            os_write_uart4 (0, &queue_trns.buf_pt[0], queue_trns.len);
            proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case GPS_XMIT_TRANSPARENT_UART5:
            os_write_uart5 (0, &queue_trns.buf_pt[0], queue_trns.len);
            proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;

          case  GPS_XMIT_GPS:

			//memcpy(&queue_trns.buf_pt[0], &pkt_gps, sizeof(pktGPS_t));

			//queue_trns.len = sizeof(pktGPS_t);

		    snd_trns_dl (&config_trns_uart1,   //Change to uart1
		    			  queue_trns.src_addr,      //Destination Address (Reply to Request Address)
						 (LOGI_UART1_TRNSTCK_ADDR | SELF_ADDRESS),     //Self Address or Source Address
						  CTRL_NORMAL_PKT,
						  HDR_TYP_REP_PKT,  //HEADER TYPE
						  &pkt_gps, sizeof(pktGPS_t));

        	  proc_gps_xmit_state = GPS_XMIT_IDLE;
        	  break;
          default :
            proc_gps_xmit_state = GPS_XMIT_IDLE;
            break;
        }

    }
}
/*
void print_gps_gnrmc_info (void) {
char temp_buf[128];
char *date_ptr;
char *time_ptr;
uint8_t i_cnt;

	//if (len_gnrmc_packet > 0)
	{
		os_puts_uart2("\f\n\r");
		os_write_uart2(0, &gnrmc_buf[0], len_gnrmc_packet);
		os_puts_uart2("\n\r");

		split_gprmc(&gps_gnrmc_conf, &pkt_gps.pkt_gprmc);

		os_puts_uart2("Time   : ");
		date_time_conv_utc(pkt_gps.pkt_gprmc.utc_date, pkt_gps.pkt_gprmc.utc_time,
				&temp_buf[0]);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");

		sprintf(temp_buf, "Status : %s",
				pkt_gps.pkt_gprmc.status == 'A' ? "Valid" : "Invalid");
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");

		sprintf(temp_buf, "Lat    : %f%c", pkt_gps.pkt_gprmc.lat, pkt_gps.pkt_gprmc.ns_ind);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");

		sprintf(temp_buf, "Long   : %f%c", pkt_gps.pkt_gprmc.lon, pkt_gps.pkt_gprmc.we_ind);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");

		sprintf(temp_buf, "Speed  : %u km/h",
				(uint8_t) (pkt_gps.pkt_gprmc.speed_gnd * 1.852));
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");

		sprintf(temp_buf, "Course : %f", pkt_gps.pkt_gprmc.course_gnd);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		os_puts_uart2("\n\r");
		//				}
		//
		//				//				if (len_gpgsv_packet > 0) {
		//				//					xputn_uart2(0, &gpgsv_buf[0], len_gpgsv_packet);
		//				//					xputs_uart2("\n\r");
		//				//				}
		//
		//				if (len_gpgsa_packet > 0)
		//				{
		os_puts_uart2("\n\r");
		os_write_uart2(0, &gpgsa_buf[0], len_gpgsa_packet);
		os_puts_uart2("\n\r");

		split_gpgsa(&gps_gpgsa_conf, &pkt_gps.pkt_gpgsa);

		sprintf(temp_buf, "Operating Mode : %s\n\r",
				pkt_gps.pkt_gpgsa.oper_mode == 'A' ? "Auto" : "Manual");
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

		sprintf(temp_buf, "Fix Mode : %c\n\r", pkt_gps.pkt_gpgsa.fix_mode);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

		for (i_cnt = 0; i_cnt < 12; i_cnt++) {
			sprintf(temp_buf, "Sat ch[%u]: %u\n\r", i_cnt,
					pkt_gps.pkt_gpgsa.sat_used_ch[i_cnt]);
			os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
		}

		sprintf(temp_buf, "PDOP : %f\n\r", pkt_gps.pkt_gpgsa.pdop);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

		sprintf(temp_buf, "HDOP : %f\n\r", pkt_gps.pkt_gpgsa.hdop);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

		sprintf(temp_buf, "VDOP : %f\n\r", pkt_gps.pkt_gpgsa.vdop);
		os_write_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

	}

}
*/
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
