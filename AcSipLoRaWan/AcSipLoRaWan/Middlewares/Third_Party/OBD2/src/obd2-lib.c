//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : obd2-lib.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : OBD2 Library Implementation
//; Create(dd/mm/yy) : 25/10/2016
//; [Revision and Description]
//; Rev1.0 - 25/10/2016: Create Library by n.noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "obd2-lib.h"
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
//obd2_pid_t pid_map [2] =  {
//		{PID_0_20, PID_0_20_FN, PID_0_20_DESC},
//		{STATUS_DTC, STATUS_DTC_FN, STATUS_DTC_DESC}
//};



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
static int32_t PID0_20_FN (uint8_t *msg);
static int32_t PID1_STATUS_DTC_FN (uint8_t *msg);
static int32_t PID2_FREEZE_DTC_FN (uint8_t *msg);
static int32_t PID3_FUEL_SYS_STATUS_FN (uint8_t *msg);
static int32_t PID4_ENGINE_LOAD_FN (uint8_t *msg);
static int32_t PID5_ENGINE_COOLANT_TEMP_FN (uint8_t *msg);

const obd2_pid_t pid_map[] = {
	{PID0_20_NUM      	  	  , PID0_20_FN			  	    , PID0_20_DESC			  		},
	{PID1_STATUS_DTC_NUM	  , PID1_STATUS_DTC_FN		    , PID1_STATUS_DTC_DESC		    },
	{PID2_FREEZE_DTC_NUM	  , PID2_FREEZE_DTC_FN	        , PID2_FREEZE_DTC_DESC		    },
	{PID3_FUEL_SYS_STATUS_NUM , PID3_FUEL_SYS_STATUS_FN	    , PID3_FUEL_SYS_STATUS_DESC	    },
	{PID4_ENGINE_LOAD_NUM	  , PID4_ENGINE_LOAD_FN		    , PID4_ENGINE_LOAD_DESC		    },
	{PID5_ENGINE_COOLANT_TEMP_NUM , PID5_ENGINE_COOLANT_TEMP_FN , PID5_ENGINE_COOLANT_TEMP_DESC }
};

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
#define TIMEOUT 200

/*uint8_t request_obd2 (uint8_t pid) {

    int8_t can_msg[8];
    float engine_data;
    can_msg[0] = 0x02;
    can_msg[1] = 0x01;
    can_msg[2] = pid;
    can_msg[3] = 0;
    can_msg[4] = 0;
    can_msg[5] = 0;
    can_msg[6] = 0;
    can_msg[7] = 0;

    return 0;
}*/

uint8_t query_obd2 (uint8_t pid) {



}




//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
static int32_t PID0_20_FN (uint8_t *msg) {

	return ((((int32_t)msg[0] << 24) | ((int32_t)msg[1] << 16) | ((int32_t)msg[2] << 8) | ((int32_t)msg[3])));
}

static int32_t PID1_STATUS_DTC_FN (uint8_t *msg) {

	return ( ((int32_t)msg[0] << 8) | ((int32_t)msg[1]) );
}

static int32_t PID2_FREEZE_DTC_FN (uint8_t *msg) {

	return ( (int32_t)0 );
}

static int32_t PID3_FUEL_SYS_STATUS_FN (uint8_t *msg) {

	return ( (int32_t)msg[0] );
}

static int32_t PID4_ENGINE_LOAD_FN (uint8_t *msg) {

	return ( ((int32_t)msg[0] * 100) / 255 );
}

static int32_t PID5_ENGINE_COOLANT_TEMP_FN (uint8_t *msg) {

	return ( (int32_t)msg[0] - 40 );
}

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
