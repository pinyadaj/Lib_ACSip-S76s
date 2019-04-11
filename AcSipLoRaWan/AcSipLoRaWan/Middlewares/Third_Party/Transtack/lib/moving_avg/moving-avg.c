//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : moving-avg.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : Moving Average example Implementation
//; Create(dd/mm/yy) : 25/8/2016
//; [Revision and Description]
//; Rev1.0 - 25/8/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "../../common.h"
#include "moving-avg.h"




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
uint32_t calc_avg    (uint16_t*  buf_ptr,
                     uint16_t   len_buf);

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */
int16_t remove_last (conf_ma_t* conf_ptr);

int16_t add_new     (conf_ma_t* conf_ptr, 
                     uint16_t     data);


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
uint32_t calc_avg (uint16_t*  buf_ptr,
                  uint16_t  len_buf)
{
    uint32_t sum;

    sum = 0;
    
    for (uint16_t i_cnt = 0; i_cnt < len_buf; i_cnt++) {
         sum += buf_ptr [i_cnt];
    }
    
    return (uint32_t)(sum / len_buf);
}

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
int16_t init_ma (conf_ma_t* create_conf_ptr, 
                 uint16_t*    buf_ptr, 
                 uint16_t     len_buf) {
    if ((buf_ptr != NULL) && (len_buf != 0)) {
        create_conf_ptr->buf_ptr = buf_ptr;
        create_conf_ptr->max     = len_buf;
        create_conf_ptr->tail = 0;
        create_conf_ptr->head = create_conf_ptr->max - 1;
        memset (buf_ptr, 0x00, len_buf);
    }    
    else return EXT_FAILURE;
    
    return EXT_SUCCESS;
    
}

uint32_t read_ma (conf_ma_t* conf_ptr,
                 uint16_t     new_data)
{

    remove_last (conf_ptr);
    
    add_new (conf_ptr, new_data);
    
    return calc_avg(conf_ptr->buf_ptr, conf_ptr->max); 
}



int16_t add_new (conf_ma_t* conf_ptr, 
                 uint16_t     data) 
{
    int16_t tmp_head;
    
    tmp_head  = (conf_ptr->head + 1) & (conf_ptr->max - 1);

    if ( tmp_head == conf_ptr->tail) return EXT_FAILURE;    
    
    conf_ptr->buf_ptr[tmp_head] =  data;
    conf_ptr->head = tmp_head;
    return EXT_SUCCESS;
}

int16_t remove_last (conf_ma_t* conf_ptr) 
{
    if (conf_ptr->head != conf_ptr->tail) {
        /* calculate and store new buffer index */
        conf_ptr->tail = (conf_ptr->tail + 1) & (conf_ptr->max - 1);
        /* get one byte from buffer and return */
        return conf_ptr->buf_ptr[conf_ptr->tail] & 0x00FF;  /* start transmission */
    }
    return 0xFFFF;   //0xFFxx indicate no data in queue
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
