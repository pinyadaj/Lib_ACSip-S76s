//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : debug_print.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : debug_print.c  Implementation
//; Create(dd/mm/yy) : 21/2/2018
//; [Revision and Description]
//; Rev1.0 - 21/2/2018: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include <stdarg.h>

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

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */




//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */

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

LOG_LEVEL GLOBAL_LOG_LEVEL = LEVEL_DEBUG; //default value

/* 4.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


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
//int LOG_INFO (const char *fmt, ...)
//{
//    char debug_buf[2048];
//    va_list args;
//
//    va_start(args, fmt);
//    int len = vsnprintf (debug_buf,2048, fmt, args);
//    va_end(args);
//
//    os_puts_uart2 (debug_buf);
//
//    return(len);
// }
void set_log_level(LOG_LEVEL level){
	GLOBAL_LOG_LEVEL = level;
}

LOG_LEVEL get_log_level(void){
	return GLOBAL_LOG_LEVEL;
}

static int  bufSize = 1*1024;//1024;

_SRAM2 char buf[1024];

void log_format (LOG_LEVEL level, const char* file, int line, const char *fmt, ... ) {
	va_list arg;
	int32_t offset = 0;
	memset(buf,0,bufSize);
	/* If the selected log level is high enough create the message and print it */
	if (level >= get_log_level()) {
		switch(level)
		{
			case LEVEL_DEBUG:
				offset = sprintf(buf, "\x1B[1;35m[DEBUG]: ");
				break;

			case LEVEL_INFO:
				//offset = sprintf(buf, "\x1B[1;32m");  //Color is green.
				//offset = sprintf(buf, "\x1B[0m");		//Color is white.

				break;

			case LEVEL_WARN:
				offset = sprintf(buf, "\x1B[1;33m[WARN]: ");
				break;

			case LEVEL_ERROR:
				offset = sprintf(buf, "\x1B[1;31m[ERROR]: ");
				break;

			default:
				break;
		}

		va_start(arg, fmt);
		vsnprintf(buf + offset, bufSize-offset, fmt, arg);
		va_end(arg);

		/* Print the message on the selected output stream */
		log_output(buf);
	}
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
// END of File.
//------------------------------------------------------------------------------
