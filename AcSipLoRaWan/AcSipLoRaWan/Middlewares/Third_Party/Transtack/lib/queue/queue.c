//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : queue.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat1122@gmail.com
//; Objective	 : queue.c  Implementation
//; Create(dd/mm/yy) : 28/7/2016
//; [Revision and Description]
//; Rev1.0 - 28/7/2016: Create Library by n.noparat
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



// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 2.4. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private Declare
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
int16_t init_queue (conf_queue_t* create_conf_ptr, 
                    uint8_t*      buf_ptr, 
                    uint16_t      len_buf) 
{
    create_conf_ptr->tail = -1;
    create_conf_ptr->head = -1;
    
    if ((buf_ptr != NULL) && (len_buf != 0)) {
        create_conf_ptr->buf_ptr = buf_ptr;
        create_conf_ptr->max = len_buf;
    }    
    else return EXT_FAILURE;
    
    return EXT_SUCCESS;
}

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
int16_t enqueue_blocked (conf_queue_t* conf_ptr, 
                         uint8_t       data) 
{
    int16_t tmp_head;
    
    tmp_head  = (conf_ptr->head + 1) & (conf_ptr->max - 1);

    while ( tmp_head == conf_ptr->tail){
        ;/* wait for free space in buffer */
    }
    
   // if (conf_ptr->tail == -1) conf_ptr->tail = 0;
    
    conf_ptr->buf_ptr[tmp_head] =  data;
    conf_ptr->head = tmp_head;
    return EXT_SUCCESS;
}

int16_t enqueue_nblocked (conf_queue_t* conf_ptr, 
                          uint8_t       data) 
{
    int16_t tmp_head;
    
    tmp_head  = (conf_ptr->head + 1) & (conf_ptr->max - 1);

    if ( tmp_head == conf_ptr->tail) return EXT_FAILURE;
    
   // if (conf_ptr->tail == -1) conf_ptr->tail = 0;
    
    conf_ptr->buf_ptr[tmp_head] =  data;
    conf_ptr->head = tmp_head;
    return EXT_SUCCESS;
}

int16_t dequeue_blocked (conf_queue_t* conf_ptr) 
{
    int16_t tmp_tail; 
        
    while ( conf_ptr->head == conf_ptr->tail){
        ;/* wait for data in buffer */
    }

    /* calculate and store new buffer index */
    tmp_tail = (conf_ptr->tail + 1) & (conf_ptr->max - 1);
    conf_ptr->tail = tmp_tail;
    /* get one byte from buffer and return */
    return conf_ptr->buf_ptr[tmp_tail] & 0x00FF;  /* start transmission */
}

int16_t dequeue_nblocked (conf_queue_t* conf_ptr) 
{
    int16_t tmp_tail; 
        
    
    if (conf_ptr->head != conf_ptr->tail) {
        /* calculate and store new buffer index */
        tmp_tail = (conf_ptr->tail + 1) & (conf_ptr->max - 1);
        conf_ptr->tail = tmp_tail;
        /* get one byte from buffer and return */
        return conf_ptr->buf_ptr[tmp_tail] & 0x00FF;  /* start transmission */
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

/* 7.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
