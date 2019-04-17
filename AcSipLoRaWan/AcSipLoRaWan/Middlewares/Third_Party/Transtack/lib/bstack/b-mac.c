////;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
////; File Name	 : tsk.c
////; Programmer   : Nopparat Ninsamran
////; Email@   	 : nopparat1122@gmail.com
////; Objective	 : Library TranStack Implementation
////; Create(dd/mm/yy) : 5/7/2016
////; [Revision and Description]
////; Rev1.0 - 5/7/2016: Create Library by N.Nin
////;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//
////<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
////<>
////<> Section 1. Include File
////<>
////<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
///*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><>*/
//
///*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><> */
//
///*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><> */
//#include "../../common.h"
//#include "trns-mac.h"
//#include "trns-typedef.h"
////#include "../../ql_log.h"
//
//#define BAUD_RATE1			(115200)
////# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
////#
////# Section 2. Private declare
////#
////# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
///* 2.1. enum declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */
//
///* 2.2. struct declare # # # # # # # # # # # # # # # # # # # # # # # # # # */
//
//
//
///* 2.3. function pointer declare # # # # # # # # # # # # # # # # # # # # # */
//
//// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
////
//// Section 3. Public Variable Declare
////
//// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
///* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//volatile uint32_t tick_sys;
//
//// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
////
//// Section 4. Private Variable Declare
////
//// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
///* 4.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 4.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 4.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
///* 4.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/
//
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
////*
////* Section 5. Private Function Prototype
////*
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
///* 5.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//
///* 5.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */
//
//int16_t build_pkt_bmac (conf_bstack_t* conf_pt,
//                             uint16_t    dst_addr,
//                             uint16_t    src_addr,
//                             ctrl_t      ctrl,
//                             hdr_typ_t      type,
//                             int8_t*    xmit_pyl_buf_pt,
//                             uint16_t    len_pyl_buf);
//
//int16_t split_pkt_bmac (conf_bstack_t* conf_pt,
//                             int8_t* buf_pt, int16_t len);
//
//void wait_receive_bmac (conf_bstack_t* conf_pt);
//
//int16_t hcs_bmac (conf_bstack_t* conf_pt);
//
//int16_t snd_btry_mac(conf_bstack_t* conf_pt);
//
//int16_t seq_chk_bmac(conf_bstack_t* conf_pt);
//
//int32_t tmout_calc_mac (uint32_t baud, uint16_t pdu_len);
//
//int16_t proc_tmout_mac (conf_bstack_t* conf_pt);
//int16_t proc_rcv_tmout_mac (conf_bstack_t* conf_pt);
//
//int16_t xmit_bmac    (conf_bstack_t* conf_pt,
//                      int8_t*     xmit_buf_pt,
//                      uint16_t     len_buf);
//
//int16_t rcv_ind_tran_mac (conf_bstack_t* conf_pt,
//                      uint16_t dst_addr,
//                      uint16_t src_addr,
//                      result_rcv_state_t result_rcv,
//                      int8_t* data_pt,
//                      uint16_t len);
//
//int16_t snd_cnf_bmac (conf_bstack_t* conf_pt,
//                      uint16_t     dst_addr,
//                      uint16_t     src_addr,
//					  result_xmit_state_t result_xmit);
//
//int16_t tmout_ind_bmac (conf_bstack_t* conf_pt,
//                        uint16_t dst_addr,
//                        uint16_t src_addr,
//                        result_rcv_state_t result_rcv);
//
////@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
////@
////@ Section 6. Interrupt Service Routine
////@
////@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
//
//
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
////*
////* Section 7. Public Function Implement
////*
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
//int16_t init_bmac (conf_bstack_t*       create_conf_pt,
//						int8_t mode,
//                       uint16_t           self_addr,
//					   snd_cnf_cb_t   snd_cnf_cb,
//					   rcv_ind_cb_t   rx_ind_cb,
//					   tmout_ind_cb_t tmout_ind_cb,
//					   int32_t  file_desc,
//					   rw_cb_t*       xmit_cb,
//					   rw_cb_t*       rcv_cb)
//{
//
//     create_conf_pt->self_addr =  self_addr;
//
//    if (create_conf_pt == NULL) return -1;
//
//
//    // setup payload maximum length
//    create_conf_pt->tx_pl_max = TRAN_PAYLOAD_BUFFER_MAX;
//    create_conf_pt->rx_pl_max = TRAN_PAYLOAD_BUFFER_MAX;
//
//    // setup indicator callback
//    if (snd_cnf_cb != NULL)     create_conf_pt->snd_cnf_cb = snd_cnf_cb;
//    if (rx_ind_cb != NULL) create_conf_pt->rcv_ind_cb = rx_ind_cb;
//    if (tmout_ind_cb != NULL)    create_conf_pt->tmout_ind_cb = tmout_ind_cb;
//
//    // setup transceiver callback
//    if (xmit_cb != NULL) create_conf_pt->xmit_cb    = xmit_cb;
//    if (rcv_cb != NULL)    create_conf_pt->rcv_cb     = rcv_cb;
//
//	if (file_desc >= 0)
//	{
//		create_conf_pt->file_desc = file_desc;
//	}
//
//	create_conf_pt->split_st = SPLIT_SOF_STS;
//
//    create_conf_pt->try_snd_pkt_trns = 0;
//
//    create_conf_pt->rx_ack = 0;
//    create_conf_pt->tx_seq = 0;
//
//    create_conf_pt->rx_try = 0;
//    create_conf_pt->tx_try = 0;
//
//    create_conf_pt->rx_tmout = 0;
//    create_conf_pt->tx_tmout = 0;
//    create_conf_pt->bst = TSK_RCV_STS;
//    create_conf_pt->mode = mode;
//    return 1;
//
//}
//
//void process_bmac (conf_bstack_t* conf_pt) {
//
//    switch (conf_pt->bst) {
//        case TSK_IDLE_STS:
//             conf_pt->bst = TSK_RCV_STS;
//            break;
//
//        case TSK_XMIT_STS:
//            //transmit_pkt_trns (conf_pt);
//            conf_pt->bst = TSK_RCV_STS;
//            break;
//
//        case TSK_RCV_STS:
//
//            receive_pkt_bmac (conf_pt);
//            break;
//
//        case TSK_RCV_IND_STS:
//            rcv_ind_tran_mac (conf_pt,
//                              MAKE16(conf_pt->rx_pdu_buf[DST_PDU_OFFSET], conf_pt->rx_pdu_buf[DST_PDU_OFFSET + 1]),
//                              MAKE16(conf_pt->rx_pdu_buf[SRC_PDU_OFFSET], conf_pt->rx_pdu_buf[SRC_PDU_OFFSET + 1]),
//                              RCV_COMPLETE_STS,
//							  &conf_pt->rx_pdu_buf[PL_PDU_OFFSET],
//                              conf_pt->tx_pl_len);
//             conf_pt->bst = TSK_RCV_STS;
//            break;
//
//        case TSK_RCV_TMOUT_STS:
//           // (*conf_pt->tmout_ind_cb)(&conf_pt->rcv_pkt_trns.type,
//            //                                    XMIT_TIMEOUT_STS);
//            conf_pt->bst = TSK_IDLE_STS;
//            break;
//
//        default :
//             conf_pt->bst = TSK_RCV_STS;
//            break;
//    }
//
//
//
//    proc_tmout_mac (conf_pt);
//
//
//   // proc_rcv_tmout_mac (conf_pt);
//
//}
//
//void exec_bmac (bstate_t state) {
//    //bstate = state;
//}
//
//
//int16_t snd_bmac (conf_bstack_t* conf_pt,
//                      uint16_t    dst_addr,
//                      uint16_t    src_addr,
//                      ctrl_t      ctrl,
//                      hdr_typ_t   hdr_type,
//                      int8_t*    xmit_pyl_buf_pt,
//                      int16_t    len_pyl_buf)
//{
//    int ret = 0;
//
//
//    if (conf_pt->xmit_cb == NULL){
//        snd_cnf_bmac (conf_pt,
//                          dst_addr,
//                          src_addr,
//                          NO_XMIT_REG_STS);
//    }
//
//    // generate
//    if ((hdr_type == HDR_TYP_REQR_PKT) || (hdr_type == HDR_TYP_REPR_PKT)) {
//    	ret = 1;
//    }
//    else {
//    	ret = build_pkt_bmac (conf_pt,
//                dst_addr,
//                src_addr,
//                ctrl,
//                hdr_type,
//                xmit_pyl_buf_pt,
//                len_pyl_buf);
//    }
//    conf_pt->tk_tmout_prev = tick_sys;
//    conf_pt->tk_tmout = tick_sys;
//
//    if (conf_pt->rx_try == 0) {
//        conf_pt->rx_tmout = tmout_calc_mac (BAUD_RATE1 , TRAN_HEADER_MAX + TRAN_HCS_MAX + len_pyl_buf + TRAN_CRC_MAX);
//    }
//    else {
//        conf_pt->rx_tmout *= 2;
//    }
//
//    if (ret == 1) {
//        ret = 0;
//        // transmit
//        if ((ret = xmit_bmac (conf_pt, &conf_pt->tx_pdu_buf[0], conf_pt->tx_pdu_len)) > 0) {
//        	if (hdr_type == HDR_TYP_REQ_PKT) {
//        	   conf_pt->rx_try = 0;
//        	}
//
//        } // transmit
//        else {
//           // LOGD("[TRANS_LIB]: Xmit Packet Fail\r\n");
//        }
//    }   // generate
//
//   //exec_trns (TSK_XMIT_STS);
//
//    //Call sent confirm
//    if (ret <= 0){
//        snd_cnf_bmac (conf_pt,
//                          dst_addr,
//                          src_addr,
//                          XMIT_FAIL_STS);
//    }
//    else {
//        snd_cnf_bmac (conf_pt,
//                          dst_addr,
//                          src_addr,
//                          XMIT_COMPLETE_STS);
//    }
//
// //   LOGD ("[TRANS_LIB]:[W]: rx_tmout = %u : Multiple = %ums\n\r", conf_pt->rx_tmout, TIME_BASE_MILLI);
//
//    return ret;
//}
//
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
////*
////* Section 8. Private Function Implement
////*
////* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//void wait_receive_bmac (conf_bstack_t* conf_pt) {
//
//     receive_pkt_bmac (conf_pt);
//}
//
//int16_t build_pkt_bmac (conf_bstack_t* conf_pt,
//                             uint16_t    dst_addr,
//                             uint16_t    src_addr,
//                             ctrl_t      ctrl,
//                             hdr_typ_t   hdr_type,
//                             int8_t*    xmit_pyl_buf_pt,
//                             uint16_t    len_pyl_buf)
//{
//    uint16_t var_tmp;
//    conf_pt->tx_pdu_len = 0;
//
//        ////////////////////// start of frame
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = TRAN_SOF;
//
//        //////////////////////  address
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)(dst_addr >> 8);
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t) dst_addr;
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)(src_addr >> 8);
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t) src_addr;
//
//        ////////////////////// length
//        if ( len_pyl_buf <= conf_pt->tx_pl_max ) {
//            var_tmp = (uint16_t)( ((len_pyl_buf & 0xFFF) << 4) | (TRAN_HEADER_MAX + TRAN_CRC_MAX)); // header+hcs = 11
//            conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)(var_tmp >> 8);
//            conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)var_tmp;
//        }
//        else {
//            return -1;
//        }
//
//        //////////////////// Control
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = ((uint8_t)ctrl & 0xE0) |
//                                       ((conf_pt->tx_seq<<3) & 0x38) |
//                                       ((conf_pt->rx_ack) & 0x07);
//
//        if (hdr_type == HDR_TYP_REQ_PKT) {
//            conf_pt->tx_seq++;
//            conf_pt->tx_seq &= 0x07;
//        }
//        else if (hdr_type == HDR_TYP_REP_PKT) {
//
//            conf_pt->rx_ack++;
//            conf_pt->rx_ack &= 0x07;
//        }
//        else {
//        	return -1;
//        }
//
//        ////////////////////// Type of frame
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)hdr_type;
//
//        //////////////////// Header check sequence
//        uint16_t tmp_crc = 0xFFFF;
//        tmp_crc = CRC16_FAST_GEN(tmp_crc, &conf_pt->tx_pdu_buf[0], TRAN_HEADER_MAX);
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t) (tmp_crc >> 8);
//        conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)  tmp_crc;
//
//        ////////////////////// payload unit
//        if ((xmit_pyl_buf_pt != NULL) && (len_pyl_buf > 0)) {
//            conf_pt->tx_pl_len = len_pyl_buf;
//            memcpy (&conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len], xmit_pyl_buf_pt, len_pyl_buf);
//
//            // payload crc
//            tmp_crc = 0xFFFF;
//            tmp_crc = CRC16_FAST_GEN(tmp_crc, &conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len], conf_pt->tx_pl_len);
//            conf_pt->tx_pdu_len += len_pyl_buf;
//            conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t) (tmp_crc >> 8);
//            conf_pt->tx_pdu_buf[conf_pt->tx_pdu_len++] = (uint8_t)  tmp_crc;
//        }
//        else {
//            conf_pt->tx_pl_len = 0;
//        }
//
//
//
//        return (1);
//}
//
//int16_t receive_pkt_bmac (conf_bstack_t* conf_pt) {
//    int16_t len_tmp = 0;
//    int8_t buf_tmp[TRAN_PKT_BUFFER_MAX];
//
//    len_tmp = (*conf_pt->rcv_cb) (conf_pt->file_desc, buf_tmp, TRAN_PKT_BUFFER_MAX);
//
//    if (len_tmp > 0) {
//    //	M2M_LOG_INFO ("data received at delta_t = %u ms\n\r",  (conf_pt->tk_tmout - conf_pt->tk_tmout_prev));
////    	LOG_INFO ("rx_tmout = %u ms\n\r", conf_pt->rx_tmout);
//
//     //  if (conf_pt->rx_tmout > 0) conf_pt->tk_tmout_prev = conf_pt->tk_tmout = tick_sys;
//       //xputn_uart2 (conf_pt, conf_pt->rcv_pdu_buf, len_tmp);
//       split_pkt_bmac (conf_pt, &buf_tmp[0], len_tmp);
//    }
//
//    return 0;
//}
//
//
//int16_t split_pkt_bmac (conf_bstack_t* conf_pt,
//                        	 int8_t* buf_pt, int16_t len)
//{
//	uint16_t tmp_cnt;
//
//    for (tmp_cnt = 0; tmp_cnt < len; tmp_cnt++)  {
//    	switch (conf_pt->split_st) {
//
//            case SPLIT_SOF_STS:
//
//                if (buf_pt[tmp_cnt] == (uint8_t)TRAN_SOF) {
//                    conf_pt->rx_pdu_buf[SOF_PDU_OFFSET] = (uint8_t)TRAN_SOF;
//                    conf_pt->len_tmp = 0;
//                    conf_pt->split_st = SPLIT_DEST_ADDR_STS;
//                   // conf_pt->tk_tmout = conf_pt->tk_tmout_prev =  tick_sys;
//                 //   M2M_LOG_INFO ("SOF_STS\r\n");
//                   // conf_pt->rx_tmout = tmout_calc_mac (BAUD_RATE1 , 4);
//                }
//                break;
//
//            case SPLIT_DEST_ADDR_STS:
//                conf_pt->rx_pdu_buf [DST_PDU_OFFSET + conf_pt->len_tmp++] = buf_pt[tmp_cnt];
//                if (conf_pt->len_tmp == 2) {
//                    conf_pt->split_st = SPLIT_SRC_ADDR_STS;
//                    conf_pt->len_tmp = 0;
//                   // LOGD ("[TRANS_LIB]: DEST_ADDRESS = 0x%04X\r\n", MAKE16(conf_pt->rx_pdu_buf [DST_PDU_OFFSET], conf_pt->rx_pdu_buf [DST_PDU_OFFSET + 1]));
//                }
//                break;
//
//            case SPLIT_SRC_ADDR_STS:
//
//                conf_pt->rx_pdu_buf [SRC_PDU_OFFSET + conf_pt->len_tmp++] = buf_pt[tmp_cnt];
//                //LOGD ("[TRANS_LIB]: SRC_ADDRESS = 0x%02X\r\n", buf_pt[tmp_cnt]);
//                if (conf_pt->len_tmp == 2) {
//                    conf_pt->split_st = SPLIT_LEN_STS;
//                    conf_pt->len_tmp = 0;
//                   // LOGD ("SRC_PDU\r\n");
//                    //LOGD ("[TRANS_LIB]: SRC_ADDRESS = 0x%04X\r\n", MAKE16(conf_pt->rx_pdu_buf [SRC_PDU_OFFSET], conf_pt->rx_pdu_buf [SRC_PDU_OFFSET + 1]));
//                }
//                break;
//
//            case SPLIT_LEN_STS:
//
//                conf_pt->rx_pdu_buf [LEN_PDU_OFFSET + conf_pt->len_tmp++] = buf_pt[tmp_cnt];
//
//                if (conf_pt->len_tmp == 2) {
//                    (*conf_pt).len_tmp = 0;
//                    conf_pt->rx_pl_len = 0;
//
//
//                    //LOGD ("LEN_PDU = 0x%lX\r\n", MAKE16(conf_pt->rcv_pdu_buf [LEN_PDU_OFFSET], conf_pt->rcv_pdu_buf [LEN_PDU_OFFSET + 1]));
//
//                    conf_pt->split_st = SPLIT_CTRL_STS;
//                }
//
//                break;
//
//            case SPLIT_CTRL_STS :
//                conf_pt->rx_pdu_buf[CTR_PDU_OFFSET] = buf_pt[tmp_cnt];
//                conf_pt->split_st = SPLIT_TPYE_STS;
//
//                break;
//
//            case SPLIT_TPYE_STS :
//                conf_pt->rx_pdu_buf[TYP_PDU_OFFSET] = buf_pt[tmp_cnt];
//                conf_pt->split_st = SPLIT_HCS_STS;
//
//                break;
//
//            case SPLIT_HCS_STS:
//
//                conf_pt->rx_pdu_buf[HCS_PDU_OFFSET + conf_pt->len_tmp++] = buf_pt[tmp_cnt];
//                if (conf_pt->len_tmp == 2) {
//                	conf_pt->split_st = SPLIT_SOF_STS;
//                    // Header CRC
//                    uint16_t tmp_crc = 0xFFFF;
//
//                    tmp_crc = CRC16_FAST_GEN(tmp_crc, &conf_pt->rx_pdu_buf[SOF_PDU_OFFSET], TRAN_HEADER_MAX);
//
//                    if (tmp_crc == MAKE16 (conf_pt->rx_pdu_buf[HCS_PDU_OFFSET], conf_pt->rx_pdu_buf[HCS_PDU_OFFSET + 1])) {
//
//                        if ((MAKE16(conf_pt->rx_pdu_buf[LEN_PDU_OFFSET],
//                                    conf_pt->rx_pdu_buf[LEN_PDU_OFFSET + 1]) >> 4) > 0) {
//                        //    LOGD ("HCS_PDU_PL\r\n");
//                            conf_pt->split_st = SPLIT_PAYLOAD_STS;
//                            conf_pt->len_tmp = 0;
//                            conf_pt->tk_tmout = conf_pt->tk_tmout_prev = tick_sys;
//
//                            conf_pt->rx_tmout = tmout_calc_mac (BAUD_RATE1 ,
//                                                                (TRAN_HEADER_MAX - 5) +
//                                                                TRAN_CRC_MAX +
//                                                                MAKE16(conf_pt->rx_pdu_buf [LEN_PDU_OFFSET], conf_pt->rx_pdu_buf [LEN_PDU_OFFSET + 1]));
//                          //  LOGD ("[PERIPH_INFO][RCV]: delta_t = %u x10ms:rx_tmout = %u x10ms\n\r",  (conf_pt->tk_tmout - conf_pt->tk_tmout_prev), conf_pt->rx_tmout);
//                        } else {
//                         //   LOGD ("HCS_PDU_NO_PL\r\n\r\n");
//                            conf_pt->rx_tmout = 0;
//                            hcs_bmac(conf_pt);
//                            //exec_trns (TSK_RCV_HCS_OK_IND_STS);
//                            conf_pt->split_st = SPLIT_SOF_STS;
//                        }
//                    }
//                    else {
//                      //  LOGD("[TRANS_LIB]: SPLIT_HCS_STS CAL_0x%04X =! RCV_0x%04X\r\n", tmp_crc, MAKE16 (conf_pt->rx_pdu_buf[HCS_PDU_OFFSET], conf_pt->rx_pdu_buf[HCS_PDU_OFFSET + 1]));
//
//                    }
//
//                }
//
//                break;
//
//            case SPLIT_PAYLOAD_STS:
//
//                conf_pt->rx_pdu_buf [PL_PDU_OFFSET + conf_pt->rx_pl_len++] = buf_pt[tmp_cnt];
//
//                if (conf_pt->rx_pl_len == (MAKE16(conf_pt->rx_pdu_buf [LEN_PDU_OFFSET], conf_pt->rx_pdu_buf [LEN_PDU_OFFSET + 1]) >> 4)) {
//                //	LOGD ("PL COMPLETE\r\n\r\n");
//                    conf_pt->split_st = SPLIT_CRC_STS;
//                }
//
//                if (conf_pt->rx_pl_len > conf_pt->rx_pl_max) {
//                //	LOGD ("ERROR : LEN = %d > LEN_MAX = %d\r\n\r\n", conf_pt->rx_pl_len, conf_pt->rx_pl_max);
//                	conf_pt->rx_tmout = 0;
//                    conf_pt->split_st = SPLIT_SOF_STS;
//                }
//
//
//                break;
//
//            case SPLIT_CRC_STS:
//
//                conf_pt->rx_pdu_buf [PL_CRC_PDU_OFFSET + conf_pt->len_tmp++] = buf_pt[tmp_cnt];
//
//                if (conf_pt->len_tmp == 2) {
//                    conf_pt->rx_tmout = 0;
//                    conf_pt->len_tmp = 0;
//                //    LOGD ("CRC_CHECK STS\r\n\r\n");
//                    hcs_bmac(conf_pt);
//
//                    conf_pt->split_st = SPLIT_SOF_STS;
//                }
//
//                break;
//
//            default :
//            	conf_pt->rx_tmout = 0;
//                conf_pt->split_st = SPLIT_SOF_STS;
//
//                break;
//        }
//    }
//
//    return (0);
//}
//
//int16_t hcs_bmac (conf_bstack_t* conf_pt) {
//
//    uint16_t dst_addr = MAKE16(conf_pt->rx_pdu_buf[DST_PDU_OFFSET], conf_pt->rx_pdu_buf[DST_PDU_OFFSET + 1]);
//    uint16_t src_addr = MAKE16(conf_pt->rx_pdu_buf[SRC_PDU_OFFSET], conf_pt->rx_pdu_buf[SRC_PDU_OFFSET + 1]);
//    result_rcv_state_t result_rcv;
//    int ret;
//
//    // Header CRC
//    uint16_t tmp_crc = 0xFFFF;
//    tmp_crc = CRC16_FAST_GEN(tmp_crc, &conf_pt->rx_pdu_buf[SOF_PDU_OFFSET], TRAN_HEADER_MAX);
//
//    if (tmp_crc == MAKE16 (conf_pt->rx_pdu_buf[HCS_PDU_OFFSET], conf_pt->rx_pdu_buf[HCS_PDU_OFFSET + 1])) {
//    	  //  	LOGD ("CRC_PASS\r\n");
//        if (conf_pt->rx_pl_len == 0) {
//
//            result_rcv = TSK_RCV_HCS_OK_IND_STS;
//            conf_pt->rx_try = 0;
//            conf_pt->rx_tmout = 0;
//            // RCV indicate call back Success
//            rcv_ind_tran_mac (conf_pt,
//                              dst_addr,
//                              src_addr,
//							  result_rcv,
//							  &conf_pt->rx_pdu_buf[PL_PDU_OFFSET],
//                              conf_pt->rx_pl_len);
//        }
//        else {
//            // Payload CRC
//            tmp_crc = 0xFFFF;
//            tmp_crc = CRC16_FAST_GEN (tmp_crc, &conf_pt->rx_pdu_buf[PL_PDU_OFFSET], conf_pt->rx_pl_len);
//            if (tmp_crc == MAKE16 (conf_pt->rx_pdu_buf[PL_CRC_PDU_OFFSET], conf_pt->rx_pdu_buf[PL_CRC_PDU_OFFSET + 1])) {
//
//
//                //ret = seq_chk_bmac(conf_pt);
//                ret = 1;
//
//                if (ret > 0) {
//                    conf_pt->rx_try = 0;
//                    conf_pt->rx_tmout = 0;
//                    // RCV indicate call back Success
//                    rcv_ind_tran_mac (conf_pt,
//                                      dst_addr,
//                                      src_addr,
//                                      TSK_RCV_OK_IND_STS,
//									  &conf_pt->rx_pdu_buf[PL_PDU_OFFSET],
//                                      conf_pt->rx_pl_len);
//                }
//                else if (ret < 0) {
//                	if (conf_pt->mode == MODE_MASTER) {
//                		snd_btry_mac(conf_pt);
//                	}
//
//                }else {
//  //                  ret = frcmnt_chk_bmac(conf_pt);
//                }
//            }
//            else {
//            //	LOGD("[PERIPH_STS]: PL_CRC_FAIL...\r\n");
//            	if (conf_pt->mode == MODE_MASTER) {
//            		snd_btry_mac(conf_pt);
//            	}
//            }
//        }
//    }
//    else {
//      //  LOGD ("CRC_NOT_PASS\r\n");
//    	if (conf_pt->mode == MODE_MASTER) {
//    		snd_btry_mac(conf_pt);
//    	}
//    }
//
//    // RCV indicate call back ERROR
//    if (conf_pt->rx_try == TRAN_TRY_MAX)
//    {
//        conf_pt->rx_try = 0;
//        rcv_ind_tran_mac (conf_pt,
//                          dst_addr,
//                          src_addr,
//                          TSK_RCV_ERROR_IND_STS,
//						  &conf_pt->rx_pdu_buf[PL_PDU_OFFSET],
//                          conf_pt->rx_pl_len);
//    }
//    return 1;
//}
//int16_t snd_btry_mac(conf_bstack_t* conf_pt) {
//int16_t res = 0;
//uint16_t dst_addr = MAKE16(conf_pt->tx_pdu_buf[DST_PDU_OFFSET], conf_pt->tx_pdu_buf[DST_PDU_OFFSET + 1]);
//uint16_t src_addr = MAKE16(conf_pt->tx_pdu_buf[SRC_PDU_OFFSET], conf_pt->tx_pdu_buf[SRC_PDU_OFFSET + 1]);
//
//res = snd_bmac (conf_pt,
//    			  dst_addr,  //Destination Address
//				  src_addr,  //Self Address or Source Address
//                  CTRL_NORMAL_PKT,
//                  HDR_TYP_REQR_PKT,  //HEADER TYPE
//				  &conf_pt->tx_pdu_buf[PL_PDU_OFFSET],
//                  conf_pt->tx_pl_len);
//
//    return  res;
//}
//
//int16_t seq_chk_bmac(conf_bstack_t* conf_pt) {
//    int result;
//    if (((conf_pt->rx_pdu_buf[CTR_PDU_OFFSET] >> 3)&0x07) == conf_pt->rx_ack ) {
//        conf_pt->rx_ack++;
//        result = 1;
//    }
//    else {
//        result = -1;
//    }
//
//
//    return result;
//}
//
//int32_t tmout_calc_mac (uint32_t baud, uint16_t pdu_len) {
//    uint32_t tm_out;
//
//    tm_out = (uint32_t)((((double)pdu_len * 1000.0 * 10.0) / (double)baud) + ((1000.0 * 10.0 ) / (double)baud));
//
//    tm_out = tm_out * 3;   //tx + process + rx
//
//    if (tm_out < TMOUT_RCV_MIN) tm_out = TMOUT_RCV_MIN;
//
//    return tm_out;
//}
//
//int16_t proc_tmout_mac (conf_bstack_t* conf_pt) {
//    //get time base
//    conf_pt->tk_tmout = tick_sys;
//
//    if (conf_pt->rx_tmout > 0) {
//     //   LOGD ("[TRANS_LIB]:[T]: delta_t = %u : rx_tmout = %u : Multiple = %ums\n\r",  (conf_pt->tk_tmout - conf_pt->tk_tmout_prev), conf_pt->rx_tmout, TIME_BASE_MILLI);
//
//        if ((conf_pt->tk_tmout - conf_pt->tk_tmout_prev) >= conf_pt->rx_tmout) {
//            conf_pt->tk_tmout_prev = conf_pt->tk_tmout;
//         //   LOGD ("[TRANS_LIB]:[T]: Timeout Occur.....(O_o)\r\n");
//            // RCV indicate call back ERROR
//            conf_pt->split_st = SPLIT_SOF_STS;
//            conf_pt->rx_try++;
//
//            if (conf_pt->rx_try >= TRAN_TRY_MAX) {
//
//                conf_pt->rx_try = 0;
//
//                tmout_ind_bmac (conf_pt,
//                                    MAKE16(conf_pt->tx_pdu_buf[DST_PDU_OFFSET], conf_pt->tx_pdu_buf[DST_PDU_OFFSET + 1]),
//                                    conf_pt->self_addr,
//                                    TSK_RCV_TIMEOUT_IND_STS);
//                conf_pt->rx_tmout = 0;
//            }
//            else {
//            	if (conf_pt->mode == MODE_MASTER) {
//            		snd_btry_mac(conf_pt);
//            	}
//            }
//        }
//    }
//
//    return 1;
//}
//
//int16_t proc_rcv_tmout_mac (conf_bstack_t* conf_pt) {
//
//    return 1;
//}
//
//int16_t xmit_bmac (conf_bstack_t* conf_pt,
//                   int8_t*     xmit_buf_pt,
//                   uint16_t     len_buf)
//{
//    // Transmitter Callback
//    int result = (*conf_pt->xmit_cb) (conf_pt->file_desc,
//                                           xmit_buf_pt,
//                                           len_buf);
//
//    return result;
//}
//
//int16_t rcv_ind_tran_mac (conf_bstack_t* conf_pt,
//                      uint16_t     dst_addr,
//                      uint16_t     src_addr,
//                      result_rcv_state_t result_rcv,
//                      int8_t*     data_pt,
//                      uint16_t     len)
//{
//    int result = (*conf_pt->rcv_ind_cb)(dst_addr,
//                                             src_addr,
//                                             result_rcv,
//                                             data_pt,
//                                             len);
//    return result;
//}
//
//int16_t snd_cnf_bmac (conf_bstack_t* conf_pt,
//                      uint16_t     dst_addr,
//                      uint16_t     src_addr,
//                      result_xmit_state_t result_xmit)
//{
//    int result =  (*conf_pt->snd_cnf_cb)(dst_addr,
//                                              src_addr,
//                                              result_xmit);
//    return result;
//}
//
//int16_t tmout_ind_bmac (conf_bstack_t* conf_pt,
//                        uint16_t dst_addr,
//                        uint16_t src_addr,
//                        result_rcv_state_t result_rcv)
//{
//    int result =  (*conf_pt->tmout_ind_cb)(dst_addr,
//                                                src_addr,
//                                                result_rcv);
//
//    return result;
//}
//
////------------------------------------------------------------------------------
////- END of File.
////------------------------------------------------------------------------------
