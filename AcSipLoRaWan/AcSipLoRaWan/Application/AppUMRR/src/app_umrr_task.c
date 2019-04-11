//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : umrr.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : umrr.c Implementation
//; Create(dd/mm/yy) : 26/2/2018
//; [Revision and Description]
//; Rev1.0 - 26/2/2018: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "main.h"


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




//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
umrr_pdu_s2c_state_t  umrr_pdu_s2c_sta;
umrr_pdu_sen_resp_state_t umrr_pdu_sen_resp_sta;
umrr_pl_state_t   umrr_pl_sta;

umrr_obj_t umrr_obj;

umrr_statistic_feature_msg1_t umrr_statistic_feature_msg1;
umrr_statistic_feature_msg2_t umrr_statistic_feature_msg2;
umrr_statistic_time_msg_t     umrr_statistic_time_msg;

umrr_pvr_hdr_t     umrr_pvr_hdr;
umrr_pvr_obj_msg_t umrr_pvr_msg;

umrr_sensor_ctrl_msg_t umrr_sensor_ctrl_msg;

/* 3.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 3.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */


///////////////////////////////////////////////////////////////////////////////
//
// Section 4. Private Variable Declare
//
///////////////////////////////////////////////////////////////////////////////
/* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
TaskHandle_t os_task_umrr_handle;

uint8_t umrr_pl_buf [1024];
uint16_t umrr_pl_len;

/* 4.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */
static void os_umrr_task(void *pvParameters);
int16_t umrr_rs485_sensor_to_controller_decoder(uint8_t *umrr_pdu_buf_pt, int16_t umrr_len);
int16_t umrr_rs485_sensor_cmd_resp_decoder (uint8_t *umrr_pdu_buf_pt, int16_t umrr_len);
int16_t umrr_can_decoder(uint8_t *umrr_pl_buf_pt, int16_t umrr_len);
static void dummy_umrr_ind_rx_cb (uint16_t can_id, uint8_t can_len, uint8_t *data_pt);
uint32_t umrr_decode(uint8_t *buf_pt, int8_t len, int16_t bit_offset_low, int16_t bit_offset_hi);

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
void os_umrr_task_create(void) {
BaseType_t  xReturned;

	  /* Create the task, storing the handle. */
	  xReturned = xTaskCreate( os_umrr_task,       /* Function that implements the task. */
	                          "UMRR",          /* Text name for the task. */
	                          2048,      /* Stack size in words, not bytes. */
	                          ( void * ) NULL,    /* Parameter passed into the task. */
	                          tskIDLE_PRIORITY,/* Priority at which the task is created. */
	                          &os_task_umrr_handle );      /* Used to pass out the created task's handle. */

	umrr_pdu_s2c_sta = START_CA_STA;
	umrr_pdu_sen_resp_sta = START_BA_STA;

	GPIOA_CLK_ENABLE();
	GPIOB_CLK_ENABLE();
	GPIOC_CLK_ENABLE();

	LL_GPIO_SetPinMode(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);

	LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);

	LL_GPIO_SetPinMode(USR_SW_GPIO_PORT, USR_SW_PIN, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(USR_SW_GPIO_PORT, USR_SW_PIN, LL_GPIO_PULL_UP);
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
uint8_t uart3_buf[1024];
int32_t uart3_len;

uint8_t uart4_buf[1024];
int32_t uart4_len;

uint8_t uart5_buf[512];
int32_t uart5_len;

static void os_umrr_task(void *pvParameters) {

//can_msg_t CAN_TxMsg[16];

	LOG_INFO ("[SYSTEM]: UMRR Task Started...\r\n");

	for (;;) {


		uart4_len = os_read_uart4 (0, &uart4_buf[0], 1024);

		if (uart4_len > 0) {
			LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
			// forward data from PC to UMRR
			uart3_len = os_read_uart3 (0, &uart3_buf[0], 1024);
			if (uart3_len > 0) {
				LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);

				os_write_uart4 (0, &uart3_buf[0], uart3_len);

				 LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);
			}

			// forward data from UMRR to PC
			os_write_uart3 (0, &uart4_buf[0], uart4_len);

			// decode data's UMRR
			if (umrr_rs485_sensor_to_controller_decoder (&uart4_buf[0], uart4_len) > 0) {

				//LOG_INFO("[UMRR]: Connected...^^\r\n");
			}
			else if (umrr_rs485_sensor_cmd_resp_decoder (&uart4_buf[0], uart4_len) > 0) {
				//LOG_INFO("[UMRR]: SETUP SENSOR...^^\r\n");
			}
			else {
				//LOG_INFO("[UMRR]: PACKET ERROR...!!!\r\n");
			}
			LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
		}


		uart5_len = os_read_uart5 (0, &uart5_buf[0], 1023);

		if (uart5_len > 0) {
			uart5_buf[uart5_len] = '\0';
			if (strstr (uart5_buf, "CHECK") != NULL) {
				LOG_INFO ("\"DEVICE\":{\"UMRR\":%02X", 0x0A);
				LOG_INFO ("}\r\n");

			}
		}




	}//for(;;)

}

int16_t umrr_rs485_sensor_to_controller_decoder (uint8_t *umrr_pdu_buf_pt, int16_t umrr_len) {
uint16_t i_cnt = 0;
uint16_t j_cnt = 0;
uint8_t tmp_chksum = 0;


for (i_cnt = 0; i_cnt < umrr_len; i_cnt++) {
	switch (umrr_pdu_s2c_sta) {
		case START_CA_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xCA) {
			//	LOG_INFO("[UMRR]: 0xCA...\r\n");
				umrr_pdu_s2c_sta = START_CB_STA;
			}
			break;

		case START_CB_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xCB) {
			//	LOG_INFO("[UMRR]: 0xCB...\r\n");
				umrr_pdu_s2c_sta = START_CC_STA;
			}

			else {umrr_pdu_buf_pt = START_CA_STA;}
			break;

		case START_CC_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xCC) {
				//LOG_INFO("[UMRR]: 0xCC...\r\n");
				umrr_pdu_s2c_sta = START_CD_STA;
			}
			else {umrr_pdu_s2c_sta = START_CA_STA;}
			break;

		case START_CD_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xCD) {
				//LOG_INFO("[UMRR]: 0xCD...\r\n");
				umrr_pl_len = 0;
				tmp_chksum  = 0;
				memset(umrr_pl_buf,0,1024);
				umrr_pdu_s2c_sta = PAYLOAD_S2C_STA;
			}
			else {umrr_pdu_s2c_sta = START_CA_STA;}
			break;

		case PAYLOAD_S2C_STA:

				umrr_pl_buf[umrr_pl_len++] = umrr_pdu_buf_pt[i_cnt];

				if (umrr_pl_len > 1024) {
					umrr_pdu_s2c_sta = START_CA_STA;
				}
				else if ((umrr_pl_buf[umrr_pl_len - 4] == 0xEA) &&
					(umrr_pl_buf[umrr_pl_len - 3] == 0xEB) &&
					(umrr_pl_buf[umrr_pl_len - 2] == 0xEC) &&
					(umrr_pl_buf[umrr_pl_len - 1] == 0xED) && (umrr_pl_len > 4)
				) {

					for (j_cnt = 0; j_cnt < umrr_pl_len - 5; j_cnt++) {
						tmp_chksum ^= umrr_pl_buf[j_cnt];
					}
					umrr_pdu_s2c_sta = START_CA_STA;

					//LOG_INFO("\r\n\r\n[UMRR]: CHK_RCV = 0x%X == CHK_CALC = 0x%X...\r\n", umrr_pl_buf[umrr_pl_len - 5], tmp_chksum );
					//LOG_INFO("[UMRR]: PL_LEN  = %d\r\n", umrr_pl_len - 6);

					if (tmp_chksum == umrr_pl_buf[umrr_pl_len - 5]) {

//						for (j_cnt = 0; j_cnt < (umrr_pl_len - 6); j_cnt++) {
//							LOG_INFO ("%02X", umrr_pl_buf[j_cnt]);
//							if (((j_cnt % 8) == 0) && (j_cnt > 0)) LOG_INFO ("\r\n");
//						}
//						LOG_INFO ("\r\n");
						if (umrr_can_decoder(&umrr_pl_buf[0], umrr_pl_len - 5) > 0)
						{

							return 1;
						}
					}
					return 0;
				}

			break;

		default:
			umrr_pdu_buf_pt = START_CA_STA;
			break;
	}
}
	return 0;
}

int16_t umrr_rs485_sensor_cmd_resp_decoder (uint8_t *umrr_pdu_buf_pt, int16_t umrr_len) {
uint16_t i_cnt = 0;
uint16_t j_cnt = 0;
uint8_t tmp_chksum = 0;


for (i_cnt = 0; i_cnt < umrr_len; i_cnt++) {
	switch (umrr_pdu_sen_resp_sta) {
		case START_BA_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xBA) {
			//	LOG_INFO("[UMRR]: 0xBA...\r\n");
				umrr_pdu_sen_resp_sta = START_BB_STA;
			}
			break;

		case START_BB_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xBB) {
			//	LOG_INFO("[UMRR]: 0xBB...\r\n");
				umrr_pdu_sen_resp_sta = START_BC_STA;
			}

			else {umrr_pdu_sen_resp_sta = START_BA_STA;}
			break;

		case START_BC_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xBC) {
				//LOG_INFO("[UMRR]: 0xBC...\r\n");
				umrr_pdu_sen_resp_sta = START_BD_STA;
			}
			else {umrr_pdu_sen_resp_sta = START_BA_STA;}
			break;

		case START_BD_STA:
			if (umrr_pdu_buf_pt[i_cnt] == 0xBD) {
				//LOG_INFO("[UMRR]: 0xBD...\r\n");
				return 1;
			}
			else {umrr_pdu_sen_resp_sta = START_BA_STA;}
			break;


		case PAYLOAD_SEN_CMD_RESP_STA:

//				umrr_pl_buf[umrr_pl_len++] = umrr_pdu_buf_pt[i_cnt];
//
//
//
//				if (umrr_pl_len > 1024) {
//					umrr_pdu_sen_resp_sta = START_BA_STA;
//				}
//				else if ((umrr_pl_buf[umrr_pl_len - 4] == 0xEA) &&
//					(umrr_pl_buf[umrr_pl_len - 3] == 0xEB) &&
//					(umrr_pl_buf[umrr_pl_len - 2] == 0xEC) &&
//					(umrr_pl_buf[umrr_pl_len - 1] == 0xED) && (umrr_pl_len > 4)
//				) {
//
//					for (j_cnt = 0; j_cnt < umrr_pl_len - 5; j_cnt++) {
//						tmp_chksum ^= umrr_pl_buf[j_cnt];
//					}
//					umrr_pdu_sen_resp_sta = START_BA_STA;
//
//					//LOG_INFO("\r\n\r\n[UMRR]: CHK_RCV = 0x%X == CHK_CALC = 0x%X...\r\n", umrr_pl_buf[umrr_pl_len - 5], tmp_chksum );
//					//LOG_INFO("[UMRR]: PL_LEN  = %d\r\n", umrr_pl_len - 6);
//
//					if (tmp_chksum == umrr_pl_buf[umrr_pl_len - 5]) {
//
////						for (j_cnt = 0; j_cnt < (umrr_pl_len - 6); j_cnt++) {
////							LOG_INFO ("%02X", umrr_pl_buf[j_cnt]);
////							if (((j_cnt % 8) == 0) && (j_cnt > 0)) LOG_INFO ("\r\n");
////						}
////						LOG_INFO ("\r\n");
//						if (umrr_can_decoder(&umrr_pl_buf[0], umrr_pl_len - 5) > 0) {
//							return 1;
//						}
//					}
//					return 0;
//
//				}

			break;

		default:
			umrr_pdu_buf_pt = START_BA_STA;
			break;
	}
}
	return 0;
}
int16_t umrr_can_decoder (uint8_t *umrr_pl_buf_pt, int16_t umrr_len) {
	int16_t ret = 0;
	uint16_t i_cnt = 0;
	uint16_t j_cnt = 0;

	uint16_t can_id = 0;
	int16_t can_len = 0;
	uint8_t can_msg[8];


	while (1) {

		can_id = MAKE16(umrr_pl_buf_pt[i_cnt], umrr_pl_buf_pt[i_cnt + 1]);
		i_cnt += 2;
		can_len = umrr_pl_buf_pt[i_cnt++];

		for (j_cnt = 0; j_cnt < can_len; j_cnt++) {
			can_msg[j_cnt] = umrr_pl_buf_pt[i_cnt++];
		}

		dummy_umrr_ind_rx_cb (can_id, can_len, &can_msg[0]);

		if (i_cnt == umrr_len ) {
			return 1;
		}
		else if (i_cnt > umrr_len ) {
			LOG_INFO("[UMRR]: ERROR --> umrr_len  = %d, i_cnt = %d\r\n",umrr_len,i_cnt);
			return 0;
		}

	}
	return ret;
}


static void dummy_umrr_ind_rx_cb (uint16_t can_id, uint8_t can_len, uint8_t *data_pt) {
	uint16_t j_cnt = 0;

	if ((can_id == 0x500) || (can_id == 0x580) || (can_id == 0x600) || (can_id == 0x680)) {
		umrr_sensor_ctrl_msg.type.sensor_sta =   data_pt[0];
		umrr_sensor_ctrl_msg.type.spare1 = data_pt[1];
		umrr_sensor_ctrl_msg.type.src_device =  data_pt[2];
		umrr_sensor_ctrl_msg.type.spare2 =  data_pt[3];
		umrr_sensor_ctrl_msg.type.time_stamp =  ((uint32_t)data_pt[7]<<24) |  ((uint32_t)data_pt[6]<<16) |  ((uint32_t)data_pt[4]<<8) | data_pt[3] ;

		if (umrr_sensor_ctrl_msg.type.sensor_sta & 0x80) {
			LOG_INFO ("\"STA\":{\"RAIN_STA\":%d",  (int32_t)1);
			LOG_INFO ("}\r\n");
		}


	}

	if ((can_id >= 0x590) && (can_id <= 0x5CF)) {

//		LOG_INFO ("::0x%lX, ", can_id);
//		LOG_INFO ("%u, ", can_len);
//
//		for (j_cnt = 0; j_cnt < can_len; j_cnt++) {
//			LOG_INFO ("0x%02X ", data_pt[j_cnt]);
//		//	umrr_pvr_msg.buf[j_cnt] =  data_pt[j_cnt];
//		}
//		LOG_INFO ("\r\n");

		umrr_obj.type.id =  umrr_decode (data_pt, can_len, 58, 63);
		umrr_obj.type.len = umrr_decode (data_pt, can_len, 50, 57);
		umrr_obj.type.y_veloc =  umrr_decode (data_pt, can_len, 39, 49);
		umrr_obj.type.x_veloc =  umrr_decode (data_pt, can_len, 28, 38);
		umrr_obj.type.y_coord =  umrr_decode (data_pt, can_len, 14, 27);
		umrr_obj.type.x_coord =  umrr_decode (data_pt, can_len, 0, 13);

		//check less than 5km/h
		if (abs(((double)umrr_obj.type.x_veloc - 1024.0) * 0.36) < 5) {

			LOG_INFO ("\"OBJ_ZERO_SPD\":{\"ID\":%d,", umrr_obj.type.id);
			LOG_INFO ("\"LENGTH\":%.1f,", (double)umrr_obj.type.len * 0.2);
			LOG_INFO ("\"Y_VELOC\":%.2f,", ((double)umrr_obj.type.y_veloc - 1024.0) * 0.36);
			LOG_INFO ("\"X_VELOC\":%.2f,", ((double)umrr_obj.type.x_veloc - 1024.0) * 0.36);
			LOG_INFO ("\"Y_COOR\":%.2f,", ((double)umrr_obj.type.y_coord - 8192.0) * 0.064);
			LOG_INFO ("\"X_COOR\":%.2f", ((double)umrr_obj.type.x_coord- 8192.0) * 0.064);
			LOG_INFO ("}\r\n");
		}


//		LOG_INFO ("[UMRR]: OBJECT { \r\n"
//				  " ID     = %d\r\n", umrr_obj.type.id);
//		LOG_INFO (" LENGTH = %.1f m\r\n", (double)umrr_obj.type.len * 0.2);
//
//		LOG_INFO (" Y_VELOCITY = %.2f km/h\r\n", ((double)umrr_obj.type.y_veloc - 1024.0) * 0.36);
//		LOG_INFO (" X_VELOCITY = %.2f km/h\r\n", ((double)umrr_obj.type.x_veloc - 1024.0) * 0.36);
//
//		LOG_INFO (" Y_COORDINATE = %.2f m\r\n", ((double)umrr_obj.type.y_coord - 8192.0) * 0.064);
//		LOG_INFO (" X_COORDINATE = %.2f m\r\n", ((double)umrr_obj.type.x_coord- 8192.0) * 0.064);
//
//		LOG_INFO ("\r\n}\r\n\r\n");


	}

	if (can_id == 0x78D) {
		umrr_pvr_hdr.type.part      = umrr_decode (data_pt, can_len, 0, 1);
		if (umrr_pvr_hdr.type.part == 0) {
			umrr_pvr_hdr.type.part       = umrr_decode (data_pt, can_len, 0, 1);
			umrr_pvr_hdr.type.obj_cnt    = umrr_decode (data_pt, can_len, 2, 7);
			umrr_pvr_hdr.type.unix_tm    = umrr_decode (data_pt, can_len, 8, 39);
			umrr_pvr_hdr.type.ms_tm  	 = umrr_decode (data_pt, can_len, 40, 49);
			umrr_pvr_hdr.type.sen_nwk_id = umrr_decode (data_pt, can_len, 50, 51);

//			LOG_INFO ("\"PVR_HDR\":{"
//					  "\"OBJ_CNT\":%d,", umrr_pvr_hdr.type.obj_cnt);
//			LOG_INFO ("\"UNIX_TIME\":%d,", umrr_pvr_hdr.type.unix_tm);
//			LOG_INFO ("\"Millis\":%d,", umrr_pvr_hdr.type.ms_tm);
//			LOG_INFO ("\"SEN_NWK_ID\":%d", umrr_pvr_hdr.type.sen_nwk_id);
//			LOG_INFO ("}\r\n");

//			LOG_INFO ("\r\n[UMRR]: PVR HEADER { \r\n"
//					  " OBJECT_CNT    = %d\r\n", umrr_pvr_hdr.type.obj_cnt);
//			LOG_INFO (" UNIX_TIME     = %d s\r\n", umrr_pvr_hdr.type.unix_tm);
//			LOG_INFO (" Milliseconds  = %d ms\r\n", umrr_pvr_hdr.type.ms_tm);
//			LOG_INFO (" SENSOR_NWK_ID = %d \r\n", umrr_pvr_hdr.type.sen_nwk_id);
//			LOG_INFO ("\r\n}\r\n");
		}
		else if (umrr_pvr_hdr.type.part == 1) {
//				LOG_INFO ("::0x%lX, ", can_id);
//				LOG_INFO ("%u, ", can_len);
//
//				for (j_cnt = 0; j_cnt < can_len; j_cnt++) {
//					LOG_INFO ("0x%02X ", data_pt[j_cnt]);
//				//	umrr_pvr_msg.buf[j_cnt] =  data_pt[j_cnt];
//				}
//				LOG_INFO ("\r\n");

				umrr_pvr_msg.type.part      = umrr_decode (data_pt, can_len, 0, 1);
				umrr_pvr_msg.type.obj_num   = umrr_decode (data_pt, can_len, 2, 6);
				umrr_pvr_msg.type.obj_id    = umrr_decode (data_pt, can_len, 7, 12);
				umrr_pvr_msg.type.lane_num  = umrr_decode (data_pt, can_len, 13, 15);
				umrr_pvr_msg.type.mline_num = umrr_decode (data_pt, can_len, 16, 17);
				umrr_pvr_msg.type.class     = umrr_decode (data_pt, can_len, 18, 20);
				umrr_pvr_msg.type.speed     = umrr_decode (data_pt, can_len, 21, 31);

				LOG_INFO ("\"PVR_MSG\":{\"OBJ_NUM\":%d,",umrr_pvr_msg.type.obj_num);
				LOG_INFO ("\"OBJ_ID\":%d,",umrr_pvr_msg.type.obj_id);
				LOG_INFO ("\"LANE\":%d,",   umrr_pvr_msg.type.lane_num);
				LOG_INFO ("\"MLINE\":%d,",  umrr_pvr_msg.type.mline_num);
				LOG_INFO ("\"CLASS\":%d,",  umrr_pvr_msg.type.class);
				LOG_INFO ("\"SPD\":%0.2f", ((double)umrr_pvr_msg.type.speed - 1024) * 0.36);
				LOG_INFO ("}\r\n");

//				LOG_INFO ("[UMRR]: PVR MESSAGE SIZE(%d) { \r\n"
//						  " OBJECT_NUM = %d\r\n",sizeof(umrr_pvr_obj_msg_t), umrr_pvr_msg.type.obj_num);
//				LOG_INFO (" OBJECT_ID  = %d \r\n", umrr_pvr_msg.type.obj_id);
//				LOG_INFO (" LANE_NUM   = %d \r\n", umrr_pvr_msg.type.lane_num);
//				LOG_INFO (" MLINE_NUM  = %d \r\n", umrr_pvr_msg.type.mline_num);
//				LOG_INFO (" CLASS = %d\r\n", umrr_pvr_msg.type.class);
//				LOG_INFO (" SPEED_RAW  = %d\r\n", umrr_pvr_msg.type.speed);
//				LOG_INFO (" SPEED = %0.2f km/h\r\n", ((double)umrr_pvr_msg.type.speed - 1024) * 0.36);
//
//				LOG_INFO ("\r\n}\r\n\r\n");
			}
	}

	if ((can_id == 0x780) || (can_id == 0x788) || (can_id == 0x790) || (can_id == 0x798)) {

	}

	if ((can_id == 0x781) || (can_id == 0x789) || (can_id == 0x791) || (can_id == 0x799)) {

//		LOG_INFO ("::0x%lX, ", can_id);
//		LOG_INFO ("%u, ", can_len);
//
//		for (j_cnt = 0; j_cnt < can_len; j_cnt++) {
//			LOG_INFO ("0x%02X ", data_pt[j_cnt]);
//		//	umrr_pvr_msg.buf[j_cnt] =  data_pt[j_cnt];
//		}
//		LOG_INFO ("\r\n");


		umrr_statistic_feature_msg1.type.feature_part_id  = umrr_decode (data_pt, can_len, 9, 9);

		if (umrr_statistic_feature_msg1.type.feature_part_id == 0) {

			umrr_statistic_feature_msg1.type.msg_num          = umrr_decode (data_pt, can_len, 0, 8);
			umrr_statistic_feature_msg1.type.feature_part_id  = umrr_decode (data_pt, can_len, 9, 9);
			umrr_statistic_feature_msg1.type.mline 			  = umrr_decode (data_pt, can_len, 10, 11);
			umrr_statistic_feature_msg1.type.lane  			  = umrr_decode (data_pt, can_len, 12, 14);
			umrr_statistic_feature_msg1.type.headway    	  = umrr_decode (data_pt, can_len, 15, 31);
			umrr_statistic_feature_msg1.type.class   		  = umrr_decode (data_pt, can_len, 32, 37);
			umrr_statistic_feature_msg1.type.percent_85_speed = umrr_decode (data_pt, can_len, 38, 47);
			umrr_statistic_feature_msg1.type.avg_speed        = umrr_decode (data_pt, can_len, 48, 63);

			LOG_INFO ("\"FEATURE_MSG1\":{\"MSG_NUM\":%d,", umrr_statistic_feature_msg1.type.msg_num);
			LOG_INFO ("\"FEATURE_PART_ID\":%d,", umrr_statistic_feature_msg1.type.feature_part_id);
			LOG_INFO ("\"MLINE\":%d,", umrr_statistic_feature_msg1.type.mline);
			LOG_INFO ("\"LANE\":%d,", umrr_statistic_feature_msg1.type.headway);
			LOG_INFO ("\"HEADWAY\":%d,", umrr_statistic_feature_msg1.type.class);
			LOG_INFO ("\"SPD85\":%d,", umrr_statistic_feature_msg1.type.percent_85_speed - 300);
			LOG_INFO ("\"AVG_SPD\":%0.2f", ((double)umrr_statistic_feature_msg1.type.avg_speed - 32768.0) * 0.01);
			LOG_INFO ("}\r\n");

//			LOG_INFO ("[UMRR]: FEATURE MESSAGE1 SIZE(%d) { \r\n"
//					  " MSG_NUM = %d\r\n",sizeof(umrr_statistic_feature_msg1), umrr_statistic_feature_msg1.type.msg_num);
//			LOG_INFO (" FEATURE_PART_ID  = %d \r\n", umrr_statistic_feature_msg1.type.feature_part_id);
//			LOG_INFO (" MEA_LINE  = %d \r\n", umrr_statistic_feature_msg1.type.mline);
//			LOG_INFO (" LANE      = %d \r\n", umrr_statistic_feature_msg1.type.headway);
//			LOG_INFO (" HEADWAY   = %d\r\n", umrr_statistic_feature_msg1.type.class);
//			LOG_INFO (" 85%_SPEED = %d km/h\r\n", umrr_statistic_feature_msg1.type.percent_85_speed - 300);
//			LOG_INFO (" AVG_SPEED = %0.2f km/h\r\n", ((double)umrr_statistic_feature_msg1.type.avg_speed - 32768.0) * 0.01);
//
//			LOG_INFO ("\r\n}\r\n\r\n");

		}
		else {
			umrr_statistic_feature_msg2.type.msg_num          = umrr_decode (data_pt, can_len, 0, 8);
			umrr_statistic_feature_msg2.type.feature_part_id  = umrr_decode (data_pt, can_len, 9, 9);
			umrr_statistic_feature_msg2.type.mline 			  = umrr_decode (data_pt, can_len, 10, 11);
			umrr_statistic_feature_msg2.type.lane  			  = umrr_decode (data_pt, can_len, 12, 14);
			umrr_statistic_feature_msg2.type.gap    	      = umrr_decode (data_pt, can_len, 15, 31);
			umrr_statistic_feature_msg2.type.class   		  = umrr_decode (data_pt, can_len, 32, 35);
			umrr_statistic_feature_msg2.type.volume 		  = umrr_decode (data_pt, can_len, 36, 49);
			umrr_statistic_feature_msg2.type.occupancy        = umrr_decode (data_pt, can_len, 50, 63);
			LOG_INFO ("\"FEATURE_MSG2\":{\"MSG_NUM\":%d,",umrr_statistic_feature_msg2.type.msg_num);
			LOG_INFO ("\"FEATURE_PART_ID\":%d,", umrr_statistic_feature_msg2.type.feature_part_id);
			LOG_INFO ("\"MLINE\":%d,", umrr_statistic_feature_msg2.type.mline);
			LOG_INFO ("\"LANE\":%d,", umrr_statistic_feature_msg2.type.lane);
			LOG_INFO ("\"GAP\":%0.2f,", (double)umrr_statistic_feature_msg2.type.gap * 0.028);
			LOG_INFO ("\"CLASS\":%d,", umrr_statistic_feature_msg2.type.class);
			LOG_INFO ("\"VOLUME\":%d,", umrr_statistic_feature_msg2.type.volume);
			LOG_INFO ("\"OCCUPANCY\":%0.2f", (double)umrr_statistic_feature_msg2.type.occupancy * 0.01);
			LOG_INFO ("}\r\n");

//			LOG_INFO ("[UMRR]: FEATURE MESSAGE2 SIZE(%d) { \r\n"
//					  " MSG_NUM = %d\r\n",sizeof(umrr_statistic_feature_msg2), umrr_statistic_feature_msg2.type.msg_num);
//			LOG_INFO (" FEATURE_PART_ID  = %d\r\n", umrr_statistic_feature_msg2.type.feature_part_id);
//			LOG_INFO (" MEA_LINE  = %d\r\n", umrr_statistic_feature_msg2.type.mline);
//			LOG_INFO (" LANE      = %d\r\n", umrr_statistic_feature_msg2.type.lane);
//			LOG_INFO (" GAP       = %0.2f s\r\n", (double)umrr_statistic_feature_msg2.type.gap * 0.028);
//			LOG_INFO (" CLASS     = %d\r\n", umrr_statistic_feature_msg2.type.class);
//			LOG_INFO (" VOLUME    = %d\r\n", umrr_statistic_feature_msg2.type.volume);
//			LOG_INFO (" OCCUPANCY = %0.2f %%\r\n", (double)umrr_statistic_feature_msg2.type.occupancy * 0.01);
//
//			LOG_INFO ("\r\n}\r\n\r\n");
		}
	}

//	if ((can_id == 0x782) || (can_id == 0x78A) || (can_id == 0x792) || (can_id == 0x79A)) {
//		LOG_INFO ("::0x%lX, ", can_id);
//		LOG_INFO ("%u, ", can_len);
//
//		for (j_cnt = 0; j_cnt < can_len; j_cnt++) {
//			LOG_INFO ("0x%02X ", data_pt[j_cnt]);
//		//	umrr_pvr_msg.buf[j_cnt] =  data_pt[j_cnt];
//		}
//		LOG_INFO ("\r\n");
//
//		umrr_statistic_time_msg.type.sensor_id         = umrr_decode (data_pt, can_len, 0, 3);
//		umrr_statistic_time_msg.type.interval_cnt_down = umrr_decode (data_pt, can_len, 4, 15);
//		umrr_statistic_time_msg.type.num_lane 		   = umrr_decode (data_pt, can_len, 16, 31);
//		umrr_statistic_time_msg.type.serial_num 	   = umrr_decode (data_pt, can_len, 32, 63);
//
//		LOG_INFO ("[UMRR]: TIME MESSAGE SIZE(%d) { \r\n"
//				  " SENSOR_ID = %d\r\n",sizeof(umrr_statistic_time_msg), umrr_statistic_time_msg.type.sensor_id);
//		LOG_INFO (" INTERVAL_CNT_DOWN  = %d\r\n", umrr_statistic_time_msg.type.interval_cnt_down);
//		LOG_INFO (" NUM_OF_LANES = %d\r\n", umrr_statistic_time_msg.type.num_lane);
//		LOG_INFO (" SERIAL_NUM   = %s\r\n", umrr_statistic_time_msg.type.serial_num);
//	LOG_INFO ("\r\n}\r\n\r\n");
//	}


}

uint32_t umrr_decode (uint8_t *buf_pt, int8_t len, int16_t bit_offset_low, int16_t bit_offset_hi) {
uint32_t value = 0;
int8_t indx_hi;
int8_t indx_low;
int8_t indx_delta;
uint8_t tmp_buf[8];
int8_t i_byte=0;
int8_t i_bit=0;

    indx_low = ((len * 8) - (bit_offset_low + 1)) / 8;
    indx_hi = ((len * 8) - (bit_offset_hi + 1)) / 8;
    indx_delta = indx_low - indx_hi;

  //  printf("\r\nindex_low = %d\r\n", indx_low);
   // printf("index_high = %d\r\n", indx_hi);
    //printf("delta = %d\r\n", indx_low - indx_hi);

    if (indx_delta == 0) {
    	value = buf_pt[indx_low] >> (bit_offset_low % 8);
    }
    else if (indx_delta == 1) {
    	value = buf_pt[indx_low] >> (bit_offset_low % 8);
    	value |= buf_pt[indx_low - 1] << (8 - (bit_offset_low % 8));
    }
    else if (indx_delta >= 2) {
        memcpy(tmp_buf,buf_pt, 8);
        for(i_bit=0; i_bit < bit_offset_low; i_bit++){

            for(i_byte = len-1; i_byte > 0; i_byte--){
                tmp_buf[i_byte] >>= 1;
                tmp_buf[i_byte] |= tmp_buf[i_byte - 1] & 1 ? 0x80: 0;
            }

            tmp_buf[i_byte] >>= 1;
        }
        value =  tmp_buf[len-4];
        value <<=  8;
        value |=  tmp_buf[len-3];
        value <<=  8;
        value |=  tmp_buf[len-2];
        value <<=  8;
        value |=  tmp_buf[len-1];
    }

    return value & BIT_MASK(uint32_t, bit_offset_hi - bit_offset_low + 1);
}
/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
////Start sequence
//sen_buf[sen_len++] = 0xAA;
//sen_buf[sen_len++] = 0xAB;
//sen_buf[sen_len++] = 0xAC;
//sen_buf[sen_len++] = 0xAD;
//
////CAN MESSAGE
////CAN ID
//sen_buf[sen_len++] = 0x03;
//sen_buf[sen_len++] = 0xA1;
//
////CAN LENGTH
//sen_buf[sen_len++] = 0x8;
//
////
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//
////CAN ID
//sen_buf[sen_len++] = 0x03;
//sen_buf[sen_len++] = 0xA1;
//
////CAN LENGTH
//sen_buf[sen_len++] = 0x8;
////
//sen_buf[sen_len++] = 0x10;
//sen_buf[sen_len++] = 0x8B;
//sen_buf[sen_len++] = 0x74;
//sen_buf[sen_len++] = 0x8A;
//sen_buf[sen_len++] = 0x48;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x01;
//sen_buf[sen_len++] = 0xF4;
//
//
////CAN ID
//sen_buf[sen_len++] = 0x03;
//sen_buf[sen_len++] = 0xA1;
//
////CAN LENGTH
//sen_buf[sen_len++] = 0x8;
////
//sen_buf[sen_len++] = 0x20;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0xFF;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//sen_buf[sen_len++] = 0x00;
//
//
//// XOR Checksum
//sen_buf[sen_len] = 0;
//for (i_cnt = 0; i_cnt < sen_len-4; i_cnt++) {
//	sen_buf[sen_len] ^= sen_buf[4 + sen_len];
//}
//
//sen_len++;
//
////End sequence
//sen_buf[sen_len++] = 0xDA;
//sen_buf[sen_len++] = 0xDB;
//sen_buf[sen_len++] = 0xDC;
//sen_buf[sen_len++] = 0xDD;
