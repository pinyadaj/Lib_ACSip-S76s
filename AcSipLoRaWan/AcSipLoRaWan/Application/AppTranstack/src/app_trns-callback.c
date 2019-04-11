//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_trns_callback.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : template.c example Implementation
//; Create(dd/mm/yy) : 15/10/2016
//; [Revision and Description]
//; Rev1.0 - 15/10/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "trns-typedef.h"

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "common.h"
#include "transcode_bsp.h"
#include "app_trns-callback.h"


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


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
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
int16_t snd_cnf_cbk_uart1 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_xmit_state_t result_xmit)
{
    int16_t ret=1;
    if (FIND_LOGICAL_ADDR(src_addr) == LOGI_UART1_TRNSTCK_ADDR) {
	//	sprintf(temp_buf, "ADC SND CNF\n\r");
	//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
    }
    return ret;
}



int16_t rcv_ind_cbk_uart1 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv,
                             uint8_t* data_pt,
                             uint16_t data_len)
{
    uint8_t temp_buf[64];
	int16_t ret = 0;
	queue_trns_t queue_trns;


	queue_trns.dst_addr   = dst_addr;
	queue_trns.src_addr   = src_addr;
	queue_trns.buf_pt= data_pt;
	queue_trns.len = data_len;

//	if (data_len <= TRAN_PAYLOAD_BUFFER_MAX) {
//		memcpy(queue_trns.buf_pt, data_pt, data_len) ;
//		queue_trns.len = data_len;
//	}
//	else {
//		memcpy(queue_trns.buf_pt, data_pt, TRAN_PAYLOAD_BUFFER_MAX) ;
//		queue_trns.len = TRAN_PAYLOAD_BUFFER_MAX;
//	}


//	sprintf(temp_buf, "DEST ADDR: 0x%X\r\n", queue_trns.dst_addr);
//	sprintf(temp_buf, "SRC ADDR: 0x%X\r\n", queue_trns.src_addr);
//	os_puts_uart2(temp_buf);
//
//	sprintf(temp_buf, "rcv-ind\r\n");
//	os_puts_uart2(temp_buf);

	if (FIND_SELF_ADDR(dst_addr) == SELF_ADDRESS) {   //SELF_ADDRESS define in common.h, LOGICAL_XXXXX_ADDR define in service_peripheral.h

//		if      (reqIndPERIPH_GPS_OS    (&queue_trns))   ret = 1;
		if (reqIndPERIPH_UARTx_OS  (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_FUEL_OS   (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_ADCx_OS   (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_USR_SW_OS (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_BUZZER_OS (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_LED_OS    (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_DINx_OS   (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_DOUTx_OS  (&queue_trns))   ret = 1;
		else if (reqIndPERIPH_RFID_OS   (&queue_trns))   ret = 1;
		else if (reqPERIPH_BATT_OS  	(&queue_trns))   ret = 1;
		else if (reqPERIPH_SDCARD_OS  	(&queue_trns))   ret = 1;
		else if (reqIndPERIPH_CAN1_OS  	(&queue_trns))   ret = 1;

	}


/*
    for (i_cnt = 0; i_cnt < len; i_cnt++) {
        helper_hex2ascii (&buf_pt_disp[0], data_pt[i_cnt]);
        write_n_uart2(0, &buf_pt_disp[0], 5);
    }

    puts_uart2 ("\n\r");
    */



    return ret;
}

int16_t tmout_ind_cbk_uart1 (uint16_t dst_addr,
                               uint16_t src_addr,
                               result_rcv_state_t result_rcv)
{
    int16_t ret = 1;
    //static uint8_t buf_pt_disp[11] = "Timeout\n\r";
    uint8_t temp_buf[32];

	sprintf(temp_buf, "Timeout_uart1\n\r");
//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

    return ret;
}


/********************** UART2 Call Back Function*******************************/
int16_t snd_cnf_cbk_uart2 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_xmit_state_t result_xmit)
{
    int16_t ret = 1;

    return ret;
}

int16_t rcv_ind_cbk_uart2 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_rcv_state_t result_rcv,
                           uint8_t* data_pt,
                           uint16_t data_len)
{
int16_t ret = 0;
queue_trns_t queue_trns;
uint8_t temp_buf[32];

queue_trns.dst_addr   = dst_addr;
queue_trns.src_addr   = src_addr;
queue_trns.buf_pt= data_pt;
queue_trns.len = data_len;

//if (data_len <= TRAN_PAYLOAD_BUFFER_MAX) {
//	memcpy(queue_trns.buf_pt, data_pt, data_len) ;
//	queue_trns.len = data_len;
//}
//else {
//	memcpy(queue_trns.buf_pt, data_pt, TRAN_PAYLOAD_BUFFER_MAX) ;
//	queue_trns.len = TRAN_PAYLOAD_BUFFER_MAX;
//}
//

//queue_trns.buf_pt= data_pt;
//queue_trns.len = data_len;



//	sprintf(temp_buf, "DEST ADDR: 0x%X", queue_trns.dst_addr);
//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
//	xputs_uart2("\n\r");

	if (FIND_SELF_ADDR(dst_addr) == SELF_ADDRESS) {   //SELF_ADDRESS define in common.h, LOGICAL_XXXXX_ADDR define in service_peripheral.h
	//	if      (reqIndPERIPH_GPS_OS (&queue_trns))   ret = 1;
		//else if (reqIndPERIPH_UARTx_OS (&queue_trns)) ret = 1;
	}

    return ret;
}

int16_t tmout_ind_cbk_uart2 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv)
{
    int16_t ret = 1;
    uint8_t temp_buf[32];

	sprintf(temp_buf, "Timeout_uart2\n\r");
//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));

    return ret;
}

/********************** UART4 Call Back Function*******************************/
int16_t snd_cnf_cbk_uart4 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_xmit_state_t result_xmit)
{
    int16_t ret = 1;

    return ret;
}

int16_t rcv_ind_cbk_uart4 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_rcv_state_t result_rcv,
                           uint8_t* data_pt,
                           uint16_t data_len)
{
int16_t ret = 0;


    return ret;
}

int16_t tmout_ind_cbk_uart4 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv)
{
    int16_t ret = 1;
    uint8_t temp_buf[32];
	sprintf(temp_buf, "Timeout_uart4\n\r");
//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
    return ret;
}

/********************** UART5 Call Back Function*******************************/
int16_t snd_cnf_cbk_uart5 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_xmit_state_t result_xmit)
{
    int16_t ret = 1;

    return ret;
}

int16_t rcv_ind_cbk_uart5 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_rcv_state_t result_rcv,
                           uint8_t* data_pt,
                           uint16_t data_len)
{
int16_t ret = 1;
queue_trns_t queue_trns;

queue_trns.dst_addr   = dst_addr;
queue_trns.src_addr   = src_addr;
queue_trns.buf_pt= data_pt;
queue_trns.len = data_len;

if (FIND_SELF_ADDR(dst_addr) == SELF_ADDRESS) {   //SELF_ADDRESS define in common.h, LOGICAL_XXXXX_ADDR define in service_peripheral.h

//		if      (reqIndPERIPH_GPS_OS    (&queue_trns))   ret = 1;
	if (reqIndPERIPH_UARTx_OS  (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_FUEL_OS   (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_ADCx_OS   (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_USR_SW_OS (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_BUZZER_OS (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_LED_OS    (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_DINx_OS   (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_DOUTx_OS  (&queue_trns))   ret = 1;
	else if (reqIndPERIPH_RFID_OS   (&queue_trns))   ret = 1;
	else if (reqPERIPH_BATT_OS  	(&queue_trns))   ret = 1;
	else if (reqPERIPH_SDCARD_OS  	(&queue_trns))   ret = 1;
	else if (reqIndPERIPH_CAN1_OS  	(&queue_trns))   ret = 1;
	else if (reqIndPERIPH_UART3_OS  (&queue_trns))   ret = 1;

}
    return ret;
}

int16_t tmout_ind_cbk_uart5 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv)
{
    int16_t ret = 1;
    uint8_t temp_buf[32];
	sprintf(temp_buf, "Timeout_uart5\n\r");
//	xputn_uart2(0, &temp_buf[0], strlen(&temp_buf[0]));
    return ret;
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
