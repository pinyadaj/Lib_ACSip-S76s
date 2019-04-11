//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_sdcard_task.c
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
TaskHandle_t xSDCardH = NULL;
QueueHandle_t os_queue_sdcard_handle = 0;
SemaphoreHandle_t xSDCardSem;

//Fatfs object
FATFS FatFs;
//File object
FIL fil;
//Free and total space
//FRESULT fr;          /* FatFs function common result code */
//UINT br, bw;         /* File read/write count */
//uint32_t sz;
uint8_t file_open_sts = 0;



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

/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
enum {
    SDC_IDLE = 0,
    SDC_FIL_CREATE,
    SDC_FIL_WRITE,
    SDC_FIL_READ,
    SDC_FIL_CLOSE
} proc_sdcard_state; 
/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */
void UIntToChar(unsigned int num, char *buf);
/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */

static void os_sdcard_task ( void *pvParameters );

int16_t open_file (char *abs_path, uint8_t flag);

int16_t sdc_write_cmd (char *data_pt, int16_t data_len) ;

int16_t sdc_read_cmd (char type, char *data_pt, int16_t data_len);

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
int16_t os_sdcard_task_create (void) {
BaseType_t  xReturned;


  /* Create the task, storing the handle. */
  xReturned = xTaskCreate(os_sdcard_task,       /* Function that implements the task. */
                          "SDCARD",          /* Text name for the task. */
                          2048,      /* Stack size in words, not bytes. */
                          ( void * ) NULL,    /* Parameter passed into the task. */
                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
                          &xSDCardH );      /* Used to pass out the created task's handle. */

  if (xReturned == pdPASS) {

     // LL_GPIO_ResetOutputPin (LED2_GPIO_PORT, LED2_PIN);
      os_queue_sdcard_handle = xQueueCreate(2 ,sizeof( queue_trns_t ));

      if(os_queue_sdcard_handle == NULL )
      {
      	LOG_ERROR  ("[SYSTEM]: A queues of SDCard cannot create!!...\r\n");
        for( ;; );
          /* Queue was not created and must not be used. */
      }

      Init_spi1();
      LL_GPIO_SetPinMode(SS_SDCARD_PORT, SS_SDCARD_PIN, LL_GPIO_MODE_OUTPUT);
      CS_HIGH();			/* Set CS# high */

  	//Mount drive
      if (f_mount(&FatFs, "", 1) == FR_OK) {

         xSDCardSem = xSemaphoreCreateBinary();

        if ( xSDCardSem == NULL ) {
            /* There was insufficient FreeRTOS heap available for the semaphore to
            be created successfully. */
        }
        else {
          xSemaphoreGive( xSDCardSem );
        }
        LOG_INFO ("[SDCARD]:  Disk is mounted....\r\n");
      }
      else {
      	LOG_WARN ("[SDCARD]: SD-Card is not install....\r\n");
      }

      return 1;
  }
  else {
	  LOG_ERROR  ("[SYSTEM]: The SDCard task cannot create!!...\r\n");
  }
  return -1;
}

//char cmd[128] = {"W,a+,/gps_info/sub1/sub2/test.txt,B,Transocde\r\n"};
//char sdcard_cmd1[512] = {"W,a+,/gps_info/gps.tmp,CC,>>10,0222222222222222;G00:2017-11-23T10:08:02.000Z,A,13.806930N,100.573972E,0,294.86,A,3,1.20,0.91,0.79;M00:490.81;E00:0000000000000004;S0F:00;S11:03;S12:0000,0000,0000,0000;S04:00;S07:03;S08:054D,02A6;\r\n\0x17\r\n"};
//char sdcard_cmd2[512] = {"W,a+,/gps_info/test.txt,A,1234567890;\0x17\r\n"};

//char cmd2[128] = {"R,l,/gps_info/sub1/sub2/test.txt;\r\n"};
//char cmd3[128] = {"D,s,/gps_info/sub1/sub2/test.txt;\r\n"};

//char sdcard_cmd3[128] = {"R,l,/gps_info/test.txt;\r\n"};

static void os_sdcard_task( void *pvParameters ) {

queue_trns_t queue_sdcard;
char *data_pt;
uint16_t  data_len;
uint8_t cmd_ret;

//uint16_t  data_len_ret;
//char* tmp1_cmd_pt;
//char* tmp2_cmd_pt;
//char sdcard_buf[1024];
//char tmp_dips[512];
//int16_t rx_len;
//int16_t fr = 0;

	LOG_INFO ("[SDCARD]: SDCARD Task Stared......\r\n");

	//queue_trns_t queue_trns_tst;

//	queue_trns_tst.dst_addr   = 0;
//	queue_trns_tst.src_addr   = 0xFFFF;
//
//	queue_trns_tst.buf_pt= sdcard_cmd2;
//	queue_trns_tst.len = strlen((char *)sdcard_cmd2);
//	//xQueueSend (os_queue_sdcard_handle, &queue_trns_tst, portMAX_DELAY);
//
//
//	queue_trns_tst.buf_pt = sdcard_cmd3;
//	queue_trns_tst.len = strlen((char *)sdcard_cmd3);
//	//xQueueSend (os_queue_sdcard_handle, &queue_trns_tst, portMAX_DELAY);

	for( ;; ) {
//		vTaskDelay(100);
	  // Wait receive Queue

		  if( xQueueReceive( os_queue_sdcard_handle, &queue_sdcard, portMAX_DELAY)) {
			  data_pt = (char *) &queue_sdcard.buf_pt[0];
			  data_len = queue_sdcard.len;

				if (data_pt[0] == 'W') {
					if (assert_pdu(5, data_pt, data_len)) {

						cmd_ret = sdc_write_cmd (data_pt, data_len);

						snd_trns_dl (&config_trns_uart1,   //Change to uart1
									 queue_sdcard.src_addr, //Destination Address (Reply Address)
									 queue_sdcard.dst_addr, //Self Address or Source Address
									 CTRL_NORMAL_PKT, HDR_TYP_REP_PKT,  //HEADER TYPE
									 (uint8_t *) &cmd_ret, 1);
						cmd_ret = 0;

					} else {
						LOG_ERROR("[SDCARD] : WRITE { }\r\n\r\n");
					}
				}

			  //Read File.
			  else if (data_pt[0] == 'R') {
					if (assert_pdu(3, data_pt, data_len)) {
						cmd_ret = sdc_read_cmd (data_pt[2] , data_pt, data_len);
					} else {
						LOG_ERROR("[SDCARD] : READ { }\r\n\r\n");
					}


//				  os_puts_uart2 ("\r\n[SDCARD] : Read Command = { \r\n");
//				  os_puts_uart2 (queue_sdcard.buffer_pt);
//				  os_puts_uart2 ("\r\n}\r\n");
//				  if (queue_sdcard.buffer_pt[2] == 'o') {
//					  tmp1_cmd_pt = queue_sdcard.buffer_pt + 4;
//			          tmp2_cmd_pt = strchr(tmp1_cmd_pt + 1, ',');
//			          *tmp2_cmd_pt = '\0';
//					  if (open_file (tmp1_cmd_pt + 1, FA_READ)) {
//						  file_open_sts = 1;
//					  }
//					  else {
//						  file_open_sts = 0;
//					  }
//
//					  snd_trns_dl (&config_trns_uart1,   //Change to uart1
//									queue_sdcard.src_addr,      //Destination Address (Reply Address)
//									queue_sdcard.dst_addr,     //Self Address or Source Address
//									CTRL_NORMAL_PKT,
//									HDR_TYP_REP_PKT,  //HEADER TYPE
//									&file_open_sts, 1);
//				  }
//				  //Read All
//				  else if (queue_sdcard.buffer_pt[2] == 'n') {
//			          tmp1_cmd_pt = queue_sdcard.buffer_pt + 4;
//			          tmp2_cmd_pt = strchr(tmp1_cmd_pt + 1, ',');
//			          *tmp2_cmd_pt = '\0';
//
//					  os_puts_uart2 ("\r\n[SDCARD] : Read n byte in file \"");
//					  os_puts_uart2 (tmp1_cmd_pt + 1);
//					  os_puts_uart2 ("\"\r\n");
//
//					  if (open_file (tmp1_cmd_pt + 1, FA_READ)) {
//						  file_open_sts = 1;
//					  }
//					  else {
//						  file_open_sts = 0;
//					  }
//
//					  snd_trns_dl (&config_trns_uart1,   //Change to uart1
//									queue_sdcard.src_addr,      //Destination Address (Reply Address)
//									queue_sdcard.dst_addr,     //Self Address or Source Address
//									CTRL_NORMAL_PKT,
//									HDR_TYP_REP_PKT,  //HEADER TYPE
//									&file_open_sts, 1);
//
//			          if (file_open_sts == 1) {
//
//			  			//f_lseek(&fil, 0);
//
//			  			do {
//
//							fr = f_read(&fil, sdcard_buf, 1024, &rx_len);
//
//							if ((fr || rx_len) == 0) break; /* error or eof */
//
//							if (rx_len > 0) {
//
//							  sprintf(tmp_dips, "\r\n[SDCARD] : Size = %d\r\n", rx_len);
//							  os_puts_uart2 (tmp_dips);
//
//							  os_puts_uart2 ("\r\n[SDCARD] : Read = { \r\n");
//							  os_write_uart2 (0, sdcard_buf, rx_len);
//							  os_write_uart1 (0, sdcard_buf, rx_len);
//							  os_puts_uart2 ("\r\n}\r\n");
//
//							  //xputn_uart1 (0, &rx_buf[0], rx_len);
//
//							  /*snd_trns_dl (&config_trns_uart1,   //Change to uart1
//											queue_sdcard.src_addr,      //Destination Address (Reply Address)
//											queue_sdcard.dst_addr,     //Self Address or Source Address
//											CTRL_NORMAL_PKT,
//											HDR_TYP_REP_PKT,  //HEADER TYPE
//											rx_buf, rx_len);*/
//
//							}
//							vTaskDelay(2);
//
//			  			} while(1);
//			  		}
//					  vTaskDelay(10);
//					f_close(&fil);           //Close file, don't forget this!
//					file_open_sts = 0;
//
//			  	 }
//				  //Read Line
//			  	 else if (queue_sdcard.buffer_pt[2] == 'l') {
//			  		 tmp1_cmd_pt = queue_sdcard.buffer_pt + 4;
//					tmp2_cmd_pt = strchr(tmp1_cmd_pt + 1, ',');
//					*tmp2_cmd_pt = '\0';
//					  xputs_uart2 ("\r\n[SDCARD] : Read line in file \"");
//					  xputs_uart2 (tmp1_cmd_pt + 1);
//					  xputs_uart2 ("\"\r\n");
//			  	      if (file_open_sts == 1)  {
//			  				rx_len = 0;
//			  				//f_lseek(&fil, 0);
//			  				do {
//
//			  					if (f_gets (sdcard_buf, 512, &fil) != NULL) {
//			  						xputs_uart2 ("\r\n[SDCARD] : Read = { \r\n");
//			  						xputs_uart2 (sdcard_buf);
//			  						xputs_uart2 ("\r\n}\r\n");
//
//			  						snd_trns_dl (&config_trns_uart1,   //Change to uart1
//												queue_sdcard.src_addr,      //Destination Address (Reply Address)
//												queue_sdcard.dst_addr,     //Self Address or Source Address
//												CTRL_NORMAL_PKT,
//												HDR_TYP_REP_PKT,  //HEADER TYPE
//												&sdcard_buf, strlen(sdcard_buf));
//			  						//xputs_uart2 ("[SDCARD] : LastPtr = ");
//			  					//	data_len_ret = f_tell (&fil);
//			  						//sprintf(tmp_dips,"%lu\r\n", data_len_ret);
//			  						//xputs_uart2(tmp_dips);
//			  					 }
//
//			  					vTaskDelay(2);
//
//			  				} while(f_eof(&fil)==0);
//
//			  			}
//			  		 }
			  	 //if (((tmp1_cmd_pt = strstr (queue_sdcard.buf, "e")) != NULL))
//			  	 else {
//			  		  f_close(&fil);           //Close file, don't forget this!
//			  		  file_open_sts = 1;
//						snd_trns_dl (&config_trns_uart1,   //Change to uart1
//									queue_sdcard.src_addr,      //Destination Address (Reply Address)
//									queue_sdcard.dst_addr,     //Self Address or Source Address
//									CTRL_NORMAL_PKT,
//									HDR_TYP_REP_PKT,  //HEADER TYPE
//									&file_open_sts, 1);
//						file_open_sts = 0;
//
//			  	 }
			  }

			  //Delete file
//			  if (queue_sdcard.buffer_pt[0] == 'D') {
//			  	 if (((tmp1_cmd_pt = strstr (queue_sdcard.buffer_pt, "s")) != NULL)) {
//			  		 tmp1_cmd_pt = queue_sdcard.buffer_pt + 4;
//			          tmp2_cmd_pt = strchr(tmp1_cmd_pt + 1, ',');
//			          *tmp2_cmd_pt = '\0';
//			      	//xputs_uart2 ("\r\n[SDCARD] : delete the file  \"");
//			  		//xputs_uart2 (tmp1_cmd_pt + 1);
//			  		//xputs_uart2 ("\" has been delete\r\n");
//
//			  		if (f_unlink (tmp1_cmd_pt + 1) == FR_OK) {
//			  			 file_open_sts = 1;
//						snd_trns_dl (&config_trns_uart1,   //Change to uart1
//									queue_sdcard.src_addr,      //Destination Address (Reply Address)
//									queue_sdcard.dst_addr,     //Self Address or Source Address
//									CTRL_NORMAL_PKT,
//									HDR_TYP_REP_PKT,  //HEADER TYPE
//									&file_open_sts, 1);
//						 file_open_sts = 0;
//			  			os_puts_uart2 ("\r\n[SDCARD] : The file \"");
//			  			os_puts_uart2 (tmp1_cmd_pt + 1);
//			  			os_puts_uart2 ("\" has been delete\r\n");
//			  		}
//			  	 }
//			  }
		  }
	}//for( ;; )
}




//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void UIntToChar(unsigned int num, char *buf){

	if(num>=10000)*buf++ = (num/10000)+0x30;
	if(num>=1000)*buf++ = (num%10000)/1000+0x30;
	if(num>=100)*buf++ = (num%1000)/100+0x30;
	if(num>=10)*buf++ = (num%100)/10+0x30;
	*buf++ = (num%10)+0x30;
	*buf = 0;

}
/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
int16_t open_file(char *abs_path, uint8_t flag) {
	char *tmp_pt;

	if (f_open(&fil, abs_path, flag) == FR_OK) {
		file_open_sts = 1;
		LOG_INFO ("\r\n[SDCARD]: The file \"%s\" open successfully", abs_path);
		return 1;

	} else {
		file_open_sts = 0;
		LOG_INFO ("\r\n[SDCARD]: Can't open the file \"%s\"\r\n", abs_path);
	}

	tmp_pt = *abs_path == '/' ? abs_path + 1 : abs_path;

	while (1) {
		if ((tmp_pt = strchr(tmp_pt, '/')) != NULL) {

			*tmp_pt = '\0';

			if (f_mkdir(abs_path) == FR_OK) {
				LOG_INFO ("[SDCARD]: A path \"%s\" has been created.\r\n", abs_path);
			} else {
				LOG_INFO ("[SDCARD]: Directory can not be created.\r\n");
			}

			*tmp_pt = '/';

			tmp_pt++;
		} else {
			break;
		}
	}

	if (f_open(&fil, abs_path, flag) == FR_OK) {
		file_open_sts = 1;
		LOG_INFO ("\r\n[SDCARD]: The file \"%s\" open successfully", abs_path);
	} else {
		file_open_sts = 0;
		LOG_INFO ("\r\n[SDCARD]: Can't open the file \"%s\"\r\n", abs_path);
	}

	return file_open_sts;
}

int16_t sdc_open_cmd (char *data_pt, int16_t data_len) {

}

int16_t sdc_write_cmd (char *data_pt, int16_t data_len) {
char *path_pt;
char *len_pt;
char *info_pt;
int16_t info_len_ret = 0;
int16_t info_len_wr = 0;
int16_t ret = 0;

	if ((strstr(data_pt, "a+") != NULL)) {

		path_pt = get_pt_field (data_pt, 3, ','); //start path string
		len_pt  = get_pt_field (data_pt, 4, ',');
		info_pt = get_pt_field (data_pt, 5, ',');

		*(len_pt - 1) = '\0';   //path close string

		info_len_wr = strtol(len_pt, NULL, 16);
		LOG_INFO("\r\n[SDCARD]: The file \"%s\" open for writes\r\n\r\n",path_pt);

		if (open_file(path_pt, FA_OPEN_APPEND | FA_READ | FA_WRITE)) {

			f_write(&fil, info_pt, info_len_wr, (UINT *) &info_len_ret);

			vTaskDelay(10);

			if (info_len_wr == info_len_ret) {
				LOG_DEBUG ("\r\n[SDCARD] : WRITE {\r\n");
				LOG_DEBUG (" LENGTH = %d\r\n", info_len_ret);
				LOG_DEBUG (" DATA = \"%s\"\r\n", info_pt);
				//os_write_uart2(0, data_pt, data_len);
				LOG_DEBUG ("}\r\n");
				ret = 1;
				LOG_INFO("\r\n[SDCARD]: The file \"%s\" was successfully written.\r\n",path_pt);
			}

			f_sync(&fil);
			f_close(&fil);           //Close file, don't forget this!

		}
	}

return ret;

}



int16_t sdc_read_cmd (char type, char *data_pt, int16_t data_len) {
char *path_pt;
int16_t ret = 0;
char sdcard_buf[SDC_LEN];
int16_t sdcard_len;
FRESULT fr;

	path_pt = get_pt_field (data_pt, 3, ','); //start path string

	*(data_pt + data_len - 3) = '\0';   //path close the string

	LOG_INFO ("\r\n[SDCARD]: The file \"%s\" open for read\r\n\r\n",path_pt);

	if ((file_open_sts = f_open(&fil, path_pt, FA_READ)) == FR_OK) {
		// read line
		if (type == 'l') {
			//f_lseek(&fil, 0);
			do {
				if (f_gets(sdcard_buf, SDC_LEN, &fil) != NULL) {

					LOG_DEBUG ("[SDCARD] : READ LINE = \"%s\"\r\n", sdcard_buf);
					//xputs_uart2 ("[SDCARD] : LastPtr = ");
					//	data_len_ret = f_tell (&fil);
					//sprintf(tmp_dips,"%lu\r\n", data_len_ret);
					//xputs_uart2(tmp_dips);
				}
			} while (f_eof(&fil) == 0);

			ret = 1;

		}

		//read hex n byte
		else if (type == 'n') {
			do {

				fr = f_read(&fil, sdcard_buf, 1024, &sdcard_len);

				if ((fr || sdcard_len) == 0) break; /* error or eof */

				if (sdcard_len > 0) {
				  LOG_DEBUG ("\r\n[SDCARD] : READ HEX = \"%s\"\r\n", sdcard_buf);

				  os_write_uart1 (0, sdcard_buf, sdcard_len);

				  /*snd_trns_dl (&config_trns_uart1,   //Change to uart1
								queue_sdcard.src_addr,      //Destination Address (Reply Address)
								queue_sdcard.dst_addr,     //Self Address or Source Address
								CTRL_NORMAL_PKT,
								HDR_TYP_REP_PKT,  //HEADER TYPE
								rx_buf, rx_len);*/

				}
				vTaskDelay(2);

			} while(1);

			ret = 1;
		}

		vTaskDelay(10);
		f_close(&fil);           //Close file, don't forget this!
		file_open_sts = 0;

		if (ret) LOG_INFO("\r\n[SDCARD]: The file \"%s\" has been successfully read.\r\n",path_pt);
		else LOG_INFO("\r\n[SDCARD]: Can't read the file \"%s\".\r\n",path_pt);
	}

	return ret;

}

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
