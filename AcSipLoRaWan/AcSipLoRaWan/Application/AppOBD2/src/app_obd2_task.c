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
TaskHandle_t os_task_can_handle = NULL;
QueueHandle_t os_queue_can_handle = NULL;
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

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */

static void os_can_task(void *pvParameters);
void can_filter_cmd (char *data_pt, int16_t data_len);
void can_write_cmd  (char *data_pt, int16_t data_len);
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
int16_t os_can_task_create(void) {

	BaseType_t xReturned;

	/* Create the task, storing the handle. */
	xReturned = xTaskCreate(os_can_task, /* Function that implements the task. */
	"CAN1", /* Text name for the task. */
	128, /* Stack size in words, not bytes. */
	(void *) NULL, /* Parameter passed into the task. */
	tskIDLE_PRIORITY,/* Priority at which the task is created. */
	&os_task_can_handle); /* Used to pass out the created task's handle. */

	/* SJW = 1  => 1 CAN bit = 16 TQ, TSEG1 = 13, TSEG2 = 2, sample at 87.5%      */
	if (os_init_can1(16, 1, 13, 2, 500000, 8) == 0) {
		LOG_ERROR ("[SYSTEM]: CAN BUS Initial Error!!...\r\n");
		for (;;)
			;

	}

	os_queue_can_handle = xQueueCreate(2, sizeof(queue_trns_t));

	if (os_queue_can_handle == NULL) {
		LOG_ERROR ("[SYSTEM]: CAN1 Task Cannot Create Queue!!...\r\n");
		for (;;)
			;
		/* Queue was not created and must not be used. */
	}

}

static void os_can_task(void *pvParameters) {
//	portTickType xLastExecutionTime;
	queue_trns_t queue_trns;

	char *data_pt;
	int16_t data_len;

	can_msg_t CAN_RxMsg;

	uint32_t rx_cnt = 0;
	uint32_t tx_cnt = 0;
	uint16_t tick_can_tx = 0;

	uint8_t comm_mode = 0;

	uint8_t can_tst_filter[] = "F,D,1,0,3F2";
	uint8_t can_tst_write[] = "W,3F2,0,0,8,12345678";




//	xLastExecutionTime = xTaskGetTickCount();


	queue_trns_t queue_trns_tst;

	queue_trns_tst.dst_addr   = 0;
	queue_trns_tst.src_addr   = 0xFFFF;

	queue_trns_tst.buf_pt = can_tst_filter;
	queue_trns_tst.len = strlen((char *)can_tst_filter);
	//xQueueSend (os_queue_can_handle, &queue_trns_tst, portMAX_DELAY);

	queue_trns_tst.buf_pt= can_tst_write;
	queue_trns_tst.len = strlen((char *)can_tst_write);
	//xQueueSend (os_queue_can_handle, &queue_trns_tst, portMAX_DELAY);

//	LOG_INFO ("[SYSTEM]: CAN1 Task Started!!...\r\n");

	for (;;) {
		/* toggle LED2*/
		// LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
		//vTaskDelay(10);

		if (xQueueReceive(os_queue_can_handle, &queue_trns, 10) == pdTRUE) {
			data_pt = (char *) &queue_trns.buf_pt[0];
			data_len = queue_trns.len;

			if (queue_trns.buf_pt[0] == 'F') {
				if (assert_pdu (5, data_pt, data_len)) {
					can_filter_cmd (data_pt, data_len);
				}
				else {
					LOG_ERROR ( "[CAN1] : SET_FILTER { }\r\n\r\n");
				}
			}
			else if (queue_trns.buf_pt[0] == 'W') {

				if (assert_pdu (6, data_pt, data_len)) {
					can_write_cmd (data_pt, data_len);
				}
				else {
					LOG_ERROR ( "[CAN1] : WRITE { }\r\n\r\n");
				}
			}
			else if (queue_trns.buf_pt[0] == 'C') {
				LOG_INFO ("[CAN1] : SET_COMMUNICATION_MODE\r\n");

			}
		}



		// READ
		if (comm_mode == 0) {
			if (os_read_ff0_can1 (&CAN_RxMsg, 100) == pdTRUE) {
				LOG_INFO ("[CAN1] : READ {\r\n"
					      "  SEQ_RX   = %lu\r\n", rx_cnt++);
				LOG_INFO ("  FREAM_ID = 0x%lX\r\n", CAN_RxMsg.id);
				LOG_INFO ("  LENGTH   = %u\r\n", CAN_RxMsg.len);
				LOG_INFO ("  DATA     = 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n}\r\n", CAN_RxMsg.data[0]
																										  , CAN_RxMsg.data[1]
																										  , CAN_RxMsg.data[2]
																										  , CAN_RxMsg.data[3]
																										  , CAN_RxMsg.data[4]
																										  , CAN_RxMsg.data[5]
																										  , CAN_RxMsg.data[6]
																										  , CAN_RxMsg.data[7]);
				LOG_INFO("}\r\n");

			}
			else {
				//DEBUG_PRINT ("[CAN1]: Waiting Data.....\n\r");

			}
		}

		// TEST WRITE
//       if (++tick_can_tx == 100) {
//			tick_can_tx = 0;
//			int i;
//			uint8_t offset = 0;
//
//			for (i = 0; i < 8; i++){
//				CAN_TxMsg.data[i] = i+offset;
//			}
//			offset += 8;
//
//			CAN_TxMsg.id  = 0x3F2;
//			CAN_TxMsg.len = 8;
//			CAN_TxMsg.format = STANDARD_FORMAT;
//			CAN_TxMsg.type = DATA_FRAME;
//
//			// write can bus
//			os_write_ff0_can1 (&CAN_TxMsg, NON_BLOCK);
//       }

	}
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

void can_filter_cmd (char *data_pt, int16_t data_len) {

	uint32_t tmp_data[4];

	 //RCV_FILTER_NUMBER
	tmp_data[0] = strtol(get_pt_field (data_pt, 2, ','), NULL, 16);

	 //RCV_FILTER_MODE
	tmp_data[1] = strtol(get_pt_field (data_pt, 3, ','), NULL, 16) ? FILTER_LIST_MODE : FILTER_MASK_MODE;

	 //RCV_FILTER_FORMAT
	tmp_data[2] = strtol(get_pt_field (data_pt, 4, ','), NULL, 16) ? EXTENDED_FORMAT : STANDARD_FORMAT;

	//RCV_FILTER_ID
	tmp_data[3] = strtol(get_pt_field (data_pt, 5, ','), NULL, 16);

	init_filter_ff0_can1 (tmp_data[0], tmp_data[1], (uint8_t)tmp_data[2], tmp_data[3]);

	LOG_INFO ( "[CAN1] : SET_FILTER {\r\n"
					  "  FILTER_INDEX  = 0x%X\r\n"
					  "  FILTER_MODE   = %s\r\n"
					  "  FILTER_FORMAT = %s\r\n"
					  "  FILTER_ID     = 0x%X\r\n}\r\n"
					  , (uint16_t)tmp_data[0]
					  ,tmp_data[1] ? "LIST_MODE" :  "MASK_MODE"
					  ,tmp_data[2] ? "EXTENDED_FORMAT" : "STANDARD_FORMAT"
					  ,(uint16_t)tmp_data[3]);
}

void can_write_cmd (char *data_pt, int16_t data_len) {
can_msg_t CAN_TxMsg;
static uint32_t tx_cnt;

	//FRAME_ID
	CAN_TxMsg.id = strtol(get_pt_field (data_pt, 2, ','), NULL, 16);

	//FORMAT
	CAN_TxMsg.format = strtol(get_pt_field (data_pt, 3, ','), NULL, 16) ? EXTENDED_FORMAT : STANDARD_FORMAT;

	//TYPE
	CAN_TxMsg.type = strtol(get_pt_field (data_pt, 4, ','), NULL, 16) ? REMOTE_FRAME : DATA_FRAME;

	 //LENGTH
	CAN_TxMsg.len = strtol(get_pt_field (data_pt, 5, ','), NULL, 16);

	//DATA
	if (CAN_TxMsg.len > 8) CAN_TxMsg.len = 8;
	if (get_pt_field (data_pt, 6, ',') != NULL && CAN_TxMsg.len) {
		memcpy (&CAN_TxMsg.data[0], get_pt_field (data_pt, 6, ','), CAN_TxMsg.len);
	}
	else {
		CAN_TxMsg.len = 0;
	}


	os_write_ff0_can1 (&CAN_TxMsg, 100);

	LOG_INFO ("[CAN1] : WRITE {\r\n"
					  "  SEQ_TX   = %lu\r\n"
					  "  FREAM_ID = 0x%lX\r\n"
					  "  LENGTH   = %u\r\n"
					  "  DATA     = 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n}\r\n"
					  , tx_cnt++
					  , CAN_TxMsg.id
					  , CAN_TxMsg.len
					  , CAN_TxMsg.data[0]
					  , CAN_TxMsg.data[1]
					  , CAN_TxMsg.data[2]
					  , CAN_TxMsg.data[3]
					  , CAN_TxMsg.data[4]
					  , CAN_TxMsg.data[5]
					  , CAN_TxMsg.data[6]
					  , CAN_TxMsg.data[7]);
}
/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
