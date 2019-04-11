
#ifndef _TRNS_H
#define _TRNS_H

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "../../common.h"



#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #       

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.2. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 3.4. struct and union definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.5. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */  

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 4. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
/* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 5. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 5.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
int16_t init_trns_mac (conf_trns_t*       conf_pt,
					   int8_t mode,
                       uint16_t           self_addr,
					   snd_cnf_cb_t   sent_ind_cb,
					   rcv_ind_cb_t   received_ind_cb,
					   tmout_ind_cb_t tmout_ind_cb,
					   int32_t file_desc,
					   rw_cb_t*       transmitter_cb,
					   rw_cb_t*       rcv_cb);

int16_t snd_trns_mac ( conf_trns_t* conf_pt,
                        uint16_t    dst_addr,  
                        uint16_t    src_addr,  
                        ctrl_t      ctrl,    
                        hdr_typ_t   hdr_type,    
                        int8_t*    xmit_pyl_buf_pt,
                        int16_t    len_pyl_buf);

void process_trns_mac (conf_trns_t* conf_pt);

void wait_receive_trns_mac (conf_trns_t* conf_pt);

int16_t receive_pkt_trns_mac (conf_trns_t* conf_pt);

void exec_trns_mac (trns_state_t state);

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//*
//* Section 6. Private Function Prototype (helper function for debug)
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */


#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif

#endif	//_TRNS_H
    
    
//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
