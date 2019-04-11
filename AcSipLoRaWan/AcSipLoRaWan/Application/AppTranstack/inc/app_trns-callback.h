//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_trns_callback.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 15/10/2016
//; [Revision and Description]
//; Rev1.0 - 15/10/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _APP_TRNS_CBK_H
#define _APP_TRNS_CBK_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
#include "queue.h"
#include "app_trns-task.h"
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "common.h"
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 3. Public Variable Definition
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */
		
		
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */



/* 4.3. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 4.4. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # # */  


//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
//@
//@ Section 5. Interrupt Service Routine
//@
//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 6. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
/***************** UART1 Call Back FunctionPrototypes ***********************/
int16_t snd_cnf_cbk_uart1 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_xmit_state_t result_xmit);

int16_t rcv_ind_cbk_uart1 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv,
                             uint8_t* data_ptr,
                             uint16_t data_len);

int16_t tmout_ind_cbk_uart1 (uint16_t dst_addr,
                               uint16_t src_addr,
                               result_rcv_state_t result_rcv);

/***************** UART2 Call Back FunctionPrototypes ***********************/
int16_t snd_cnf_cbk_uart2 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_xmit_state_t result_xmit);

int16_t rcv_ind_cbk_uart2 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv,
                             uint8_t* data_ptr,
                             uint16_t data_len);

int16_t tmout_ind_cbk_uart2 (uint16_t dst_addr,
                               uint16_t src_addr,
                               result_rcv_state_t result_rcv);

/******************* UART4 Call Back FunctionPrototypes ***********************/
int16_t snd_cnf_cbk_uart4 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_xmit_state_t result_xmit);

int16_t rcv_ind_cbk_uart4 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_rcv_state_t result_rcv,
                           uint8_t* data_ptr,
                           uint16_t data_len);

int16_t tmout_ind_cbk_uart4 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv);

/****************** UART5 Call Back FunctionPrototypes ***********************/
int16_t snd_cnf_cbk_uart5 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_xmit_state_t result_xmit);

int16_t rcv_ind_cbk_uart5 (uint16_t dst_addr,
                           uint16_t src_addr,
                           result_rcv_state_t result_rcv,
                           uint8_t* data_ptr,
                           uint16_t data_len);

int16_t tmout_ind_cbk_uart5 (uint16_t dst_addr,
                             uint16_t src_addr,
                             result_rcv_state_t result_rcv);


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 7. Private Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 7.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif

#endif	//_APP_TRNS_CBK_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
