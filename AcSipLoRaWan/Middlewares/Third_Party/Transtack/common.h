#ifndef __COMMON_H__
#define __COMMON_H__

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
//#include <xc.h>
#define _XTAL_FREQ  80000000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>< */
//Driver
//#include "driver/inc/uart1.h"
//#include "driver/inc/uart2.h"
//#include "driver/inc/adc10.h"
//#include "driver/inc/timer.h"
//#include "driver/inc/ecan.h"
//#include "driver/inc/int0.h"

//Library and Stack
#include "service_peripheral.h"
#include "lib/transtack/trns-typedef.h"
#include "lib/transtack/trns-llc.h"
#include "lib/crc/crc.h"
//#include "lib/queue/queue.h"
#include "lib/moving_avg/moving-avg.h"

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
#define SELF_ADDRESS        0x0001
#define DST_ADDRESS         0xFFFF

#define TRUE    1
#define FALSE   0

#define HIGH    1
#define LOW     0

#define EXT_SUCCESS    0
#define EXT_FAILURE   -1

//#define MAKE16(HI, LOW)     ((uint16_t)HI<<8 | LOW)

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 3.2. struct definition # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 3.3. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.3. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # # */
extern QueueHandle_t xQueueTransH;
extern QueueHandle_t xQueueGPSH;

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 5. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 5.1. general function * * * * * * * * * * * * * * * * * * * * * * * * * *  */
uint8_t helper_hex2ascii (uint8_t* buf, uint8_t c);
/* 5.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 6. Private Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

#endif

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
