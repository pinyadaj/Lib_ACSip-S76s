//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : trnstack-llc.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat1122@gmail.com
//; Objective	 : Library TranStack Implementation
//; Create(dd/mm/yy) : 11/7/2016
//; [Revision and Description]
//; Rev1.0 - 11/7/2016: Create Library by N.Nin
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
#include "trns-mac.h"

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Private declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. enum declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
   
/* 2.2. struct declare # # # # # # # # # # # # # # # # # # # # # # # # # # */



/* 2.3. function pointer declare # # # # # # # # # # # # # # # # # # # # # */

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 3. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 4. Private Variable Declare
//
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

/* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//*
//* Section 5. Private Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 5.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */


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

int16_t init_trns_dl( conf_trns_t*        create_conf_pt,
		   	   	   	   int8_t mode,
                       uint16_t           self_addr,
					   snd_cnf_cb_t   sent_ind_cb,
					   rcv_ind_cb_t   received_ind_cb,
					   tmout_ind_cb_t tmout_ind_cb,
					   int32_t  file_desc,
					   rw_cb_t*       xmit_cb,
					   rw_cb_t*       rcv_cb)
{
    
	init_trns_mac ( create_conf_pt,
			            mode,
			            self_addr,
                        sent_ind_cb,
                        received_ind_cb,
                        tmout_ind_cb,
                        file_desc,
                        xmit_cb,
                        rcv_cb);
    return 1;
    
}

void process_trns_dl(conf_trns_t* conf_pt) {
	process_trns_mac (conf_pt);
}

void exec_trns_dl (trns_state_t state) {    

	exec_trns_mac (state);
}

int16_t snd_trns_dl( conf_trns_t* conf_pt,
                      uint16_t    dst_addr,  
                      uint16_t    src_addr,  
                      ctrl_t      ctrl,
                      hdr_typ_t       hdr_type,
                      int8_t*    xmit_pyl_buf_pt,
                      int16_t    len_pyl_buf)
{
    snd_trns_mac ( conf_pt,
                   dst_addr,  
                   src_addr,  
                   ctrl,    
                   hdr_type,
                   xmit_pyl_buf_pt,
                   len_pyl_buf);
    return 1;
}

void wait_receive_trns_dl (conf_trns_t* conf_pt){
	
	wait_receive_trns_mac (conf_pt);
	
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
