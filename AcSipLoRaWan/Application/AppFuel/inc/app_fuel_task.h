//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : app_obd2_task.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 25/10/2016
//; [Revision and Description]
//; Rev1.0 - 25/10/2016: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _APP_FUEL_TASK_H
#define _APP_FUEL_TASK_H

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

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//ADC PARAMETER
#define VREF                    (5.0F)         // 5.0Volt
#define RESOLATION              (4096.0F)      //2^n, n = 12bits
#define VOLTAGE_PER_LSB         (VREF / RESOLATION)    // 5.0/2^n


//OIL SENSOR PARAMETER
#define OIL_LEVEL               (10U)
#define OIL_MIN_ANL             (0.5F)        // 0.5Volt
#define OIL_MAX_ANL             (4.5F)       // 4.25Volt
#define OIL_MIN_DIGT            (OIL_MIN_ANL / VOLTAGE_PER_LSB)
#define OIL_MAX_DIGT            (OIL_MAX_ANL / VOLTAGE_PER_LSB)
#define OIL_SLOPE               ((100.0F - 0) / (OIL_MAX_DIGT - OIL_MIN_DIGT))

//GAS SENSOR PARAMETER
#define GAS_LEVEL               (10U)
#define GAS_MIN_ANL             (0.45F)        // 0.5Volt
//#define GAS_MAX_ANL             (4.5F)        // 4.5Volt 400bar
#define GAS_MAX_ANL             (2.4F)        // 2.75Volt  200bar
#define GAS_MIN_DIGT            (GAS_MIN_ANL / VOLTAGE_PER_LSB)
#define GAS_MAX_DIGT            (GAS_MAX_ANL / VOLTAGE_PER_LSB)
#define GAS_SLOPE               ((100.0F - 0) / (GAS_MAX_DIGT - GAS_MIN_DIGT))

#define AVG_N                   (16U)
#define MEA_GAS_TRY_MAX         (20)
#define MEA_OIL_TRY_MAX         (20)

#define GAS_BUF_MAX             (64)       //2^n Only!!!!
#define OIL_BUF_MAX             (64)       //2^n Only!!!!

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
TaskHandle_t xFuelH;
QueueHandle_t xQueueANALOGH;
SemaphoreHandle_t xOilSem;

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */
typedef union {
	uint8_t fuel_byt[4];
	struct {
		uint8_t level_gas;
		uint8_t level_oil;
		uint8_t percent_gas;
		uint8_t percent_oil;
	} type;
} __attribute__ ((packed)) fuel_t;

typedef union {
	uint8_t adc_byt[8];
	struct {
		uint16_t adc1_raw;
		uint16_t adc2_raw;
		uint16_t adc3_raw;
		uint16_t adc4_raw;
	} ch;
} __attribute__ ((packed)) adc_t;

typedef union {
	uint8_t batt_byt[4];
	struct {
		uint16_t batt3v7;
		uint16_t batt12;
	} ch;
} __attribute__ ((packed)) batt_t;

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
void os_fuel_task_create (void);

void fuel_trigger_cbk (void);
void Configure_EXTI (void);
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

#endif	//_APP_FUEL_TASK_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
