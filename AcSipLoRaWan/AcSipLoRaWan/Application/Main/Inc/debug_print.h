//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : debug_print.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 21/2/2018
//; [Revision and Description]
//; Rev1.0 - 21/2/2018: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _DEBUG_PRINT_H
#define _DEBUG_PRINT_H

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
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#include <stdarg.h>


        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

#define UART1_LOG 			0
#define UART2_LOG 			1
#define UART5_LOG 			0
#if UART1_LOG
	#define log_output(a)	os_puts_uart1(a)
#elif UART5_LOG
	#define log_output(a)	os_puts_uart5(a)
#else
	#define log_output(a)	os_puts_uart3(a)
#endif


#define LOG_DEBUG(a...)  		log_format(LEVEL_DEBUG, __FILE__, __LINE__, a)
#define LOG_ERROR(a...) 		log_format(LEVEL_ERROR, __FILE__, __LINE__, a)
#define LOG_WARN(a...)  		log_format(LEVEL_WARN, __FILE__, __LINE__, a)
#define LOG_INFO(a...)  		log_format(LEVEL_INFO, NULL, 0,  a)


/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
 	     
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
		
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
typedef enum {
	LEVEL_DEBUG= 0,	/* Prints most of the messages, adds a "DEBUG" at the beginning of the message*/
	LEVEL_INFO, 	/* print the message only, without any additional info */
	LEVEL_WARN,   /* like VERB, but adds a "WARNING" at the beginning of the message. */
	LEVEL_ERROR,  /* like VERB, but adds an "ERROR" at the beginning of the message */
	LEVEL_NONE    /* Do not print anything */
} LOG_LEVEL;

/* 3.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.3. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.4. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # # */  

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 4. Public Variable Definition
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */



		
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
void set_log_level(LOG_LEVEL level);
LOG_LEVEL get_log_level(void);
void log_format (LOG_LEVEL level, const char* file, int line, const char *fmt, ... );





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

#endif	//_DEBUG_PRINT_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
