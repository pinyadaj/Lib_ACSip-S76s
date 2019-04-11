
#ifndef _BSTACK_TYPEDEF_H
#define _BSTACK_TYPEDEF_H

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><><><*/
/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/

#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif

//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 2. Constant #Define
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #       
#define TRAN_SOF                    (0x55)

#define TRAN_HEADER_MAX             (9)
#define TRAN_PAYLOAD_BUFFER_MAX     (1*1024)
#define TRAN_CRC_MAX                (2)
#define TRAN_HCS_MAX				(2)
#define TRAN_PKT_BUFFER_MAX     	(TRAN_HEADER_MAX + TRAN_HCS_MAX + TRAN_PAYLOAD_BUFFER_MAX + TRAN_CRC_MAX)

#define SOF_PDU_OFFSET		0
#define DST_PDU_OFFSET		1
#define SRC_PDU_OFFSET		3
#define LEN_PDU_OFFSET		5
#define CTR_PDU_OFFSET		7
#define TYP_PDU_OFFSET		8
#define HCS_PDU_OFFSET		9
#define PL_PDU_OFFSET		11
#define PL_CRC_PDU_OFFSET	(TRAN_HEADER_MAX + TRAN_HCS_MAX + TRAN_PAYLOAD_BUFFER_MAX)

#define TIME_BASE_MILLI		(1)

#define TMOUT_RCV_MIN		(200 / TIME_BASE_MILLI)
#define TRAN_TRY_MAX                (1)

#define MODE_MASTER               (1)
#define MODE_SLAVE                (0)

//#define MAKE16(HI, LOW)     ((((uint16_t)(HI&0xFF)<<8) | (LOW&0xFF)) & 0xFFFF)

#define MAKE16(HI, LOW)     ((uint16_t)(HI<<8) | (LOW))
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
//#
//# Section 3. General Definition
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
/* 3.1. function pointer definition # # # # # # # # # # # # # # # # # # # # # */

/* 3.2. enum definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */
typedef enum {
    TSK_IDLE_STS = 0,
    TSK_XMIT_STS,
    TSK_RCV_STS,
    TSK_RCV_IND_STS,
    TSK_RCV_TMOUT_STS
} bstate_t;

typedef enum {
    SPLIT_SOF_STS = 0,
    SPLIT_DEST_ADDR_STS,
    SPLIT_SRC_ADDR_STS,
    SPLIT_LEN_STS,
    SPLIT_CTRL_STS,
    SPLIT_TPYE_STS,
    SPLIT_HCS_STS,
    SPLIT_PAYLOAD_STS,
    SPLIT_CRC_STS
} split_state_t;

typedef enum {
    XMIT_IDLE_STS = 0,
    XMIT_COMPLETE_STS,
    XMIT_TIMEOUT_STS,
    XMIT_TRY_STS,
    XMIT_FAIL_STS,
    NO_XMIT_REG_STS
} result_xmit_state_t;

typedef enum {
    RCV_IDLE_STS = 0,
    RCV_COMPLETE_STS,
    RCV_TIMEOUT_STS,
    NO_RECEIVER_REG_STS,

    TSK_RCV_HCS_OK_IND_STS,
    TSK_RCV_OK_IND_STS,
    TSK_RCV_PYL_ERROR_IND_STS,
    TSK_RCV_ERROR_IND_STS,
    TSK_RCV_TIMEOUT_IND_STS

} result_rcv_state_t;

typedef enum {
    SND_IDLE_STS = 0,
    SND_BUILD_STS,
    SND_XMIT_STS,
    SND_CNF_STS
} snd_state_t;


/*typedef enum {
    HCS_DST_ADDR_CHK_STS  = 0x00,
	HCS_SRC_ADDR_CHK_STS,

} hdr_typ_t;  */
/*
typedef enum {
    HDR_TYP_REQ_PKT  = 0x00,
	HDR_TYP_RES_PKT  = 0x20,
    HDR_TYP_REJ_PKT  = 0x40,
    HDR_TYP_RECR_PKT = 0x60
} hdr_typ_t;  //type of frame
*/
typedef enum {
    HDR_TYP_REQ_PKT  = 0x00,
    HDR_TYP_REP_PKT  = 0x01,
    HDR_TYP_REQR_PKT  = 0x02,
    HDR_TYP_REPR_PKT = 0x03
} hdr_typ_t;  //type of frame


typedef enum {
    CTRL_NORMAL_PKT = 0x00,
    CTRL_FIRST_PKT   = 0x10,
    CTRL_CONTI_PKT  = 0x20,
    CTRL_LAST_PKT   = 0x30
} ctrl_t;  //type of frame


/* 3.4. struct and union definition # # # # # # # # # # # # # # # # # # # # # */
// for version 2.0
//typedef struct {
//    uint8_t  sof;         	// | START OF FRAME 8 BIT FIXED 0x55 |
//    uint8_t  dst_addr[2];       // | Logical/Physical 8 BIT | ADDRESS 8 BIT |
//    uint8_t  src_addr[2];       // | Logical/Physical 8 BIT | ADDRESS 8 BIT |
//    uint8_t  len[2];            // | LENGHT OF PAYLOAD 12 BIT | LENGHT OF HEADER 4 BIT |
//    uint8_t  ctrl;        	// | FRAGMENT CTRL 2 BIT() | SEQ XMIT 3 BIT | ACK RCV 3BIT  |
//    uint8_t  type;        	// | TYPE OF HEADER 8BIT |
//    uint8_t  hcs[2];            // | HEADER CHECK SEQUENCE AS CRC (MODBUS) 16BIT CRC-16 0x8005	x16 + x15 + x2 + 1 | start at SOF to TYPE |
//    uint8_t* pyl_buf_pt;       // | DATA PAYLOAD 0-4095 BYTE |
//    uint8_t  ply_crc[2];        // | PAYLOAD CHECK SEQUENCE AS CRC (MODBUS) 16BIT CRC-16 0x8005	x16 + x15 + x2 + 1 | start at first payload to last payload |
//                                // | https://www.lammertbies.nl/comm/info/crc-calculation.html
//} __attribute__ ((packed)) pkt_bt;

typedef struct {
    uint16_t dst_addr;
    uint16_t src_addr;
    int8_t  *buf_pt;
    int16_t len;
} __attribute__ ((packed)) queue_bt;

typedef int16_t (rw_cb_t)      (int32_t fd,
                                uint8_t* data_pt,
                                int16_t len);

typedef int16_t (snd_cnf_cb_t) (uint16_t dst_addr,
                                uint16_t src_addr,
                                result_xmit_state_t result_xmit);

typedef int16_t (rcv_ind_cb_t) (uint16_t dst_addr,
                                uint16_t src_addr,
                                result_rcv_state_t result_rcv,
                                uint8_t* data_pt,
                                int16_t len);

typedef int16_t (tmout_ind_cb_t) (uint16_t dst_addr,
                                  uint16_t src_addr,
                                  result_rcv_state_t result_rcv);



/* 3.5. re-definition # # # # # # # # # # # # # # # # # # # # # # # # # # # */

typedef struct {
    uint8_t rx_pdu_buf[TRAN_PKT_BUFFER_MAX];
    int16_t rx_pdu_len;
    int16_t rx_pdu_max;

    uint8_t tx_pdu_buf[TRAN_PKT_BUFFER_MAX];
    int16_t tx_pdu_len;
    int16_t tx_pdu_max;

    split_state_t split_st;
    bstate_t bst;
    snd_state_t snd_st;

    int32_t file_desc;
    rw_cb_t* xmit_cb;
    rw_cb_t* rcv_cb;

    snd_cnf_cb_t* snd_cnf_cb;
    rcv_ind_cb_t* rcv_ind_cb;
    tmout_ind_cb_t* tmout_ind_cb;

    int16_t tx_pl_max;
    int16_t tx_pl_len;

    int16_t rx_pl_max;
    int16_t rx_pl_len;

    int8_t try_snd_pkt_trns;

    int8_t rx_ack;
    int8_t tx_seq;

    uint16_t self_addr;
    uint16_t dest_addr;

    int8_t rx_try;
    int8_t tx_try;

    uint32_t rx_tmout;
    uint32_t tx_tmout;
    uint32_t tk_tmout;
    uint32_t tk_tmout_prev;
    uint16_t len_tmp;

    int8_t mode;
} __attribute__ ((packed)) conf_bstack_t;

// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 4. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 5. Public Function Prototype
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 5.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//*
//* Section 6. Private Function Prototype (helper function for debug)
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 6.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 6.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */


#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif	//_bTYPEDEF_H


//------------------------------------------------------------------------------
// END of File.
//------------------------------------------------------------------------------
