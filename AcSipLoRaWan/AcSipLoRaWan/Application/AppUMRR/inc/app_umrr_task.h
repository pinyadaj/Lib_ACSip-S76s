//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : umrr.h
//; Programmer   : Nopparat Ninsumran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : 
//; Create(dd/mm/yy) : 26/2/2018
//; [Revision and Description]
//; Rev1.0 - 26/2/2018: Create Library by N.Noparat
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

#ifndef _UMRR_H
#define _UMRR_H

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
/* 2.1. Constant definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 2.2. Hardware definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
 	     
/* 2.3. TABLE definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
		
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 3. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 3.1. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
typedef enum {
	START_CA_STA = 0,
	START_CB_STA,
	START_CC_STA,
	START_CD_STA,
	PAYLOAD_S2C_STA,
} umrr_pdu_s2c_state_t;

typedef enum {
	START_BA_STA = 0,
	START_BB_STA,
	START_BC_STA,
	START_BD_STA,
	PAYLOAD_SEN_CMD_RESP_STA,
} umrr_pdu_sen_resp_state_t;

typedef enum {
	CAN_ID_STA = 0,
	CAN_LEN_STA,
	CAN_DATA_STA
} umrr_pl_state_t;

typedef enum {
	MCU_TO_SENSOR_REQ = 0,
	SENSOR_TO_MCU,
	SENSOR_TO_MCU_RESP
} umrr_pdu_dir_t;


/* 3.2. struct and union definition # # # # # # # # # # # # # # # # # # # # # */
typedef union {
   uint8_t buf[8];
   struct {
	  unsigned id : 6;
	  unsigned len : 8;
	  unsigned y_veloc : 11;
	  unsigned x_veloc : 11;
	  unsigned y_coord : 14;
	  unsigned x_coord : 14;
   } type;
} __attribute__ ((packed)) umrr_obj_t;

/*********************************************************************
7 Tracked Object Output Specification
There are two categories of messages to be transmitted:
a) Status messages of the sensor
b) Data of detected objects
**********************************************************************/
/*********************************************************************
7.1 Status messages
Part a) is used to transmit information on:
sensor_control
 Sensor ID in the network
 Field of view
 Timestamp
The sensor control message is transmitted every cycle.
Message-Specification sensor_control:
Message Type: sensor_control
Identifier: ID0 0x500 / ID1 0x580 / ID2 0x600 / ID3 0x680
Format: Intel (little endian)*/
/**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned sensor_sta : 8;
	   unsigned spare1 : 8;
	   unsigned src_device : 8;
	   unsigned spare2 : 8;
	   unsigned time_stamp : 32;
   } type;
} __attribute__ ((packed)) umrr_sensor_ctrl_msg_t;





/*********************************************************************
5.1 Data output bound to Report Interval
**********************************************************************/

/*********************************************************************
* 5.1.1 Statistic Output – Info Message 1
* Message Type: sensor_control
* Identifier: 0x780 (ID0), 0x788 (ID1), 0x790 (ID2), 0x798 (ID3)
* DLC : 8
* Source : UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned info_part_id : 1;
	   unsigned num_mline : 3;
	   unsigned num_lanes : 4;
	   unsigned num_class : 4;
	   unsigned status : 4;
	   unsigned lane_dir : 8;
	   unsigned active_feature : 8;
	   unsigned report_interval : 20;
	   unsigned sensor_id : 4;
	   unsigned stuff_bits : 8;
   } type;
} __attribute__ ((packed)) umrr_statistic_info_msg1_t;


/*********************************************************************
* 5.1.2 Cyclical Statistic Output – Info Message 2
* Message Type: sensor_control
* Identifier: 0x780 (ID0), 0x788 (ID1), 0x790 (ID2), 0x798 (ID3)
* DLC: 8
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned info_part_id : 1;
	   unsigned ms_utc_ts : 10;
	   unsigned type : 1;
	   unsigned frame_id : 16;
	   unsigned frm_ver : 4;
	   unsigned utc_ts : 32;
   } type;
} __attribute__ ((packed)) umrr_statistic_info_msg2_t;


/*********************************************************************
* 5.1.3 Cyclical Statistic Output – Feature Message 1
* Message Type: object_data
* Identifier: 0x781 (ID0), 0x789 (ID1), 0x791 (ID2), 0x799 (ID3)
* DLC: 8
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned msg_num : 9;
	   unsigned feature_part_id : 1;
	   unsigned mline : 2;
	   unsigned lane : 3;
	   unsigned headway : 17;
	   unsigned class : 4;
	   unsigned stuff_bits : 2;
	   unsigned percent_85_speed : 10;
	   unsigned avg_speed : 16;
   } type;
} __attribute__ ((packed)) umrr_statistic_feature_msg1_t;


/*********************************************************************
* 5.1.4 Cyclical Statistic Output – Feature Message 2
* Message Type: object_data
* Identifier: 0x781 (ID0), 0x789 (ID1), 0x791 (ID2), 0x799 (ID3)
* DLC: 8
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned msg_num : 9;
	   unsigned feature_part_id : 1;
	   unsigned mline : 2;
	   unsigned lane : 3;
	   unsigned gap : 17;
	   unsigned class : 4;
	   unsigned volume : 14;
	   unsigned occupancy : 14;
   } type;
} __attribute__ ((packed)) umrr_statistic_feature_msg2_t;



/*********************************************************************
5.1 Data output bound to Report Interval
**********************************************************************/
/*********************************************************************
* 5.2.1 Statistic Output – Time Message
* Message Type: sensor_control
* Identifier: 0x782 (ID0), 0x78A (ID1), 0x792 (ID2), 0x79A (ID3)
* DLC: 8
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned sensor_id : 4;
	   unsigned interval_cnt_down : 12;
	   unsigned num_lane : 16;
	   unsigned serial_num : 32;
   } type;
} __attribute__ ((packed)) umrr_statistic_time_msg_t;


/*********************************************************************
5.2.2 Statistic Output – Presence Message
* Message Type: object_data
* Identifier: 0x783 (ID0), 0x78B (ID1), 0x793 (ID2), 0x79B (ID3)
* DLC: variable – nof. used Classes + 1
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[8];
   struct {
	   unsigned feature_part_id : 1;
	   unsigned mline : 7;
	   unsigned class0 : 8;
	   unsigned class1 : 8;
	   unsigned class2 : 8;
	   unsigned class3 : 8;
	   unsigned class4 : 8;
   } type;
} __attribute__ ((packed)) umrr_statistic_presence_msg_t;


/*********************************************************************
* 5.2.3 Statistic Output – Wrong Direction Message
* Message Type: object_data
* Identifier: 0x783 (ID0), 0x78B (ID1), 0x793 (ID2), 0x79B (ID3)
* DLC: 2
* Source: UMRR sensor
* Destination: Controller
* Format: little endian (CAN) / big endian (RS485)
* Type: unsigned
**********************************************************************/
typedef union {
   uint8_t buf[4];
   struct {
	   unsigned feature_part_id : 1;
	   unsigned mline : 7;
	   unsigned lane : 8;
   } type;
} __attribute__ ((packed)) umrr_statistic_wrong_dir_msg_t;



/*********************************************************************
5.2.6 PVR – Per Vehicle Record
If PVR is active then all counted tracks will be transmitted one time within a 0x785 (ID0)
message. This message contains the unique ID, lane and measurement line position, class
and speed [m/s] of each counted track.
Optionally each counted track can be routed to a Relay (Lane0  Relay1,… Lane7 
Relay8).
**********************************************************************/

/*Identifier: 0x785 (ID0), 0x78D (ID1), 0x795 (ID2), 0x79D (ID3)
DLC: 7 / Source: UMRR sensor / Destination: Controller / Format: little endian (CAN) / big endian (RS485)*/

typedef union {
   uint8_t buf[7];
   struct {
	   unsigned part : 2;
	   unsigned obj_cnt : 6;
	   unsigned unix_tm : 32;
	   unsigned ms_tm : 10;
	   unsigned sen_nwk_id : 2;
   } type;
} __attribute__ ((packed)) umrr_pvr_hdr_t;


/*Identifier: 0x785 (ID0), 0x78D (ID1), 0x795 (ID2), 0x79D (ID3)
DLC: 4 / Source: UMRR sensor / Destination: Controller / Format: little endian (CAN) / big endian (RS485)*/
typedef union {
   uint8_t buf[4];
   struct {
	   unsigned part : 2;
	   unsigned obj_num : 5;
	   unsigned obj_id : 6;
	   unsigned lane_num : 3;
	   unsigned mline_num : 2;
	   unsigned class : 3;
	   unsigned speed : 11;
   } type;
} __attribute__ ((packed)) umrr_pvr_obj_msg_t;


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
void os_umrr_task_create(void);

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

#endif	//_UMRR_H

//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
