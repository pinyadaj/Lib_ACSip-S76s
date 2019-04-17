//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : gps.h
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : GPS Definition
//; Create(dd/mm/yy) : 26/11/2016
//; [Revision and Description]
//; Rev1.0 - 26/11/2016: Create Library by N.Nin
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO


#ifndef _GPS_H
#define _GPS_H

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif
        
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/


        
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
#define GPAAM_TYPE	"GPAAM"
#define GPALM_TYPE	"GPALM"
#define GPAPA_TYPE	"GPAPA"
#define GPAPB_TYPE	"GPAPB"
#define GPBOD_TYPE	"GPBOD"
#define GPBWC_TYPE	"GPBWC"
#define GPDTM_TYPE	"GPDTM"
#define GPGGA_TYPE	"GPGGA"
#define GPGLL_TYPE	"GPGLL"
#define GPGRS_TYPE	"GPGRS"
#define GPGSA_TYPE	"GPGSA"
#define GPGST_TYPE	"GPGST"
#define GPGSV_TYPE	"GPGSV"
#define GPMSK_TYPE	"GPMSK"
#define GPMSS_TYPE	"GPMSS"
#define GPRMA_TYPE	"GPRMA"
#define GPRMB_TYPE	"GPRMB"
#define GPRMC_TYPE	"GPRMC"
#define GPRTE_TYPE	"GPRTE"
#define GPTRF_TYPE	"GPTRF"
#define GPSTN_TYPE	"GPSTN"
#define GPVBW_TYPE	"GPVBW"
#define GPVTG_TYPE	"GPVTG"
#define GPWCV_TYPE	"GPWCV"
#define GPWPL_TYPE	"GPWPL"
#define GPXTC_TYPE	"GPXTC"
#define GPXTE_TYPE	"GPXTE"
#define GPZTG_TYPE	"GPZTG"
#define GPZDA_TYPE	"GPZDA"
#define HCHDG_TYPE	"HCHDG"
#define PSLIB_TYPE	"PSLIB"

#define GNRMC_TYPE	"GNRMC"

#define GET_GNRMC_TIME_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 1)
#define GET_GNRMC_STATUS_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 2)
#define GET_GNRMC_LAT_PTR(conf_ptr)				get_gps_pkt_field (conf_ptr, 3)
#define GET_GNRMC_NS_PTR(conf_ptr)				get_gps_pkt_field (conf_ptr, 4)
#define GET_GNRMC_LON_PTR(conf_ptr)				get_gps_pkt_field (conf_ptr, 5)
#define GET_GNRMC_EW_PTR(conf_ptr)				get_gps_pkt_field (conf_ptr, 6)
#define GET_GNRMC_SPEED_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 7)
#define GET_GNRMC_COURSE_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 8)
#define GET_GNRMC_DATE_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 9)
#define GET_GNRMC_MAG_DEG_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 10)
#define GET_GNRMC_MAG_EW_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 11)

#define GET_GPGSA_OPER_MODE_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 1)
#define GET_GPGSA_FIX_MODE_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 2)
#define GET_GPGSA_SAT_USE_CH1_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 3)
#define GET_GPGSA_SAT_USE_CH2_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 4)
#define GET_GPGSA_SAT_USE_CH3_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 5)
#define GET_GPGSA_SAT_USE_CH4_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 6)
#define GET_GPGSA_SAT_USE_CH5_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 7)
#define GET_GPGSA_SAT_USE_CH6_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 8)
#define GET_GPGSA_SAT_USE_CH7_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 9)
#define GET_GPGSA_SAT_USE_CH8_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 10)
#define GET_GPGSA_SAT_USE_CH9_PTR(conf_ptr)		get_gps_pkt_field (conf_ptr, 11)
#define GET_GPGSA_SAT_USE_CH10_PTR(conf_ptr)	get_gps_pkt_field (conf_ptr, 12)
#define GET_GPGSA_SAT_USE_CH11_PTR(conf_ptr)	get_gps_pkt_field (conf_ptr, 13)
#define GET_GPGSA_SAT_USE_CH12_PTR(conf_ptr)	get_gps_pkt_field (conf_ptr, 14)
#define GET_GPGSA_PDOP_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 15)
#define GET_GPGSA_HDOP_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 16)
#define GET_GPGSA_VDOP_PTR(conf_ptr)			get_gps_pkt_field (conf_ptr, 17)

/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
 	     
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
		
      
		
		
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
typedef enum {
	SPLIT_GPS_SOF_STS = 0,
	SPLIT_GPS_TPYE_STS,
	SPLIT_GPS_PAYLOAD_STS,
	SPLIT_GPS_CHKSUM_STS
} split_gps_state_t;

/* 4.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */
typedef   struct {
   char gps_filter_type[10];


   char *pyl_buf_ptr;
   split_gps_state_t   split_state;

   int32_t file_desc;
   //rw_fn_ptr_t* xmit_fn_ptr;
  // rw_fn_ptr_t* rcv_fn_ptr;

  // rcv_ind_fn_ptr_t* rcv_ind_fn_ptr;
  // tmout_ind_fn_ptr_t* tmout_ind_fn_ptr;

   uint16_t pyl_max_len_rx;
   uint16_t pyl_now_len_rx;
   uint16_t pyl_tmp_len_rx;

   uint8_t  rcv_try;
   uint32_t  rcv_tmout;
   uint32_t tick_tmout;
   uint32_t tick_tmout_prev;
}  __attribute__ ((packed)) conf_gps_t;

typedef struct {
	char 	utc_time[16];
	char 	status;
	double 	lat;
	char 	ns_ind;
	double 	lon;
	char 	we_ind;
	double 	speed_gnd;
	double 	course_gnd;
	char 	utc_date[16];
 	double 	mag_varnt_deg;
	double 	mag_varnt_ew;
	uint8_t chk_sum;
} __attribute__ ((packed)) pktGPRMC_t;  //99byte

typedef struct {
	char 	 oper_mode;
	char 	 fix_mode;
 	uint16_t sat_used_ch [12];
	double pdop;
	double hdop;
	double vdop;
	uint8_t chk_sum;
} __attribute__ ((packed)) pktGPGSA_t;

typedef struct {
	pktGPRMC_t pkt_gprmc;
	pktGPGSA_t pkt_gpgsa;
} __attribute__ ((packed)) pktGPS_t;


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
uint16_t init_gps (conf_gps_t* create_conf_ptr,
				   const char* filter_type_ptr,
				   char*       buf_rx_ptr, 
				   uint16_t    len_buf_rx);

int16_t split_pkt_gps (conf_gps_t* conf_ptr, char* read_buf_ptr, int16_t* len_read_buf);

int16_t date_time_conv_utc (char* date, char* time, char* utc_buf);

char* get_gps_pkt_field (conf_gps_t *conf_ptr, uint16_t field_index);

int16_t split_gprmc (conf_gps_t* conf_ptr, pktGPRMC_t* pkt_gprmc);

int16_t split_gpgsa (conf_gps_t* conf_ptr, pktGPGSA_t* pkt_gpgsa);

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

#endif	//_GPS_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
