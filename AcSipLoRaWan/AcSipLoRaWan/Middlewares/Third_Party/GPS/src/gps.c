//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : gps.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : GPS Implementation
//; Create(dd/mm/yy) : 26/11/2016
//; [Revision and Description]
//; Rev1.0 - 26/11/2016: Create Library by N.Nin
//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "gps.h"


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


// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
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
uint16_t init_gps (conf_gps_t* create_conf_ptr,
				   const char* filter_type_ptr,
				   char*       buf_rx_ptr, 
				   uint16_t    len_buf_rx)
{
	    if (create_conf_ptr == NULL) return -1;

	    if (buf_rx_ptr != NULL){
	        create_conf_ptr->pyl_buf_ptr = buf_rx_ptr;
	        memset (buf_rx_ptr, 0x00, len_buf_rx);
	    }
		
	    if (filter_type_ptr != NULL) {
	    	strcpy(create_conf_ptr->gps_filter_type, filter_type_ptr);
	    }else{
	    	strcpy(create_conf_ptr->gps_filter_type, GPRMC_TYPE);
	    }

	    // setup payload maximum length
	    create_conf_ptr->pyl_max_len_rx = len_buf_rx;

	 
		create_conf_ptr->split_state = SPLIT_GPS_SOF_STS;


	    create_conf_ptr->rcv_try = 0;
	    create_conf_ptr->rcv_tmout = 0;

	    return 1;
}

int16_t split_pkt_gps (conf_gps_t* conf_ptr, char* read_buf_ptr, int16_t* len_read_buf) {
	uint16_t tmp_cnt;

	if (*len_read_buf == 0) return 0;

    for (tmp_cnt = 0; tmp_cnt < *len_read_buf; tmp_cnt++)  {
    	switch (conf_ptr->split_state) {

            case SPLIT_GPS_SOF_STS:

                if (read_buf_ptr[tmp_cnt] == '$') {
                    conf_ptr->pyl_now_len_rx = 0;
                    conf_ptr->split_state = SPLIT_GPS_TPYE_STS;
                   // conf_ptr->tick_tmout = conf_ptr->tick_tmout_prev =  tick_sys;
                   // conf_ptr->rcv_tmout = 200;//tmout_calc_mac (BAUD_RATE1 , 4);
				//	printf("SPLIT_GPS_SOF_STS OK\n\r");
                  //  xputs_uart2("SPLIT_GPS_SOF_STS OK\n\r");
                }
                break;

            case SPLIT_GPS_TPYE_STS:

                conf_ptr->pyl_buf_ptr[conf_ptr->pyl_now_len_rx++] = read_buf_ptr[tmp_cnt];

                if (conf_ptr->pyl_now_len_rx == 6) {

                    if (memcmp(&conf_ptr->gps_filter_type[0], &conf_ptr->pyl_buf_ptr[0], strlen(&conf_ptr->gps_filter_type[0])) == 0){
						// xputs_uart2("SPLIT_GPS_TPYE_STS OK\n\r");
                    	conf_ptr->split_state = SPLIT_GPS_PAYLOAD_STS;
                    }
                    else {
                    	conf_ptr->split_state = SPLIT_GPS_SOF_STS;
                    }
                }

                break;

            case SPLIT_GPS_PAYLOAD_STS:

                conf_ptr->pyl_buf_ptr[conf_ptr->pyl_now_len_rx++] = read_buf_ptr[tmp_cnt];

                if (read_buf_ptr[tmp_cnt] == '*') {
                	conf_ptr->pyl_tmp_len_rx = 0;
					//xputs_uart2("SPLIT_GPS_PAYLOAD_STS OK\n\r");
                	conf_ptr->split_state = SPLIT_GPS_CHKSUM_STS;
                }

                if (conf_ptr->pyl_now_len_rx > conf_ptr->pyl_max_len_rx) {
                    conf_ptr->split_state = SPLIT_GPS_SOF_STS;
                }

                break;

            case SPLIT_GPS_CHKSUM_STS:

            	conf_ptr->pyl_buf_ptr[conf_ptr->pyl_now_len_rx++] = read_buf_ptr[tmp_cnt];
				conf_ptr->pyl_tmp_len_rx++;
                if (conf_ptr->pyl_tmp_len_rx == 2) {
                    conf_ptr->rcv_tmout = 0;
					conf_ptr->pyl_buf_ptr[conf_ptr->pyl_now_len_rx] = 0;
                    conf_ptr->split_state = SPLIT_GPS_SOF_STS;
					//xputs_uart2("SPLIT_GPS_CHKSUM_STS OK\n\r");
					*len_read_buf -= (tmp_cnt + 1);
					return conf_ptr->pyl_now_len_rx;
                }

                break;

            default :
                conf_ptr->split_state = SPLIT_GPS_SOF_STS;

                break;
        }
    }
	
	*len_read_buf -= tmp_cnt;
	return 0;
}

int16_t date_time_conv_utc(char* date, char* time, char* utc_buf) {
	//Date format
	utc_buf[0] = '2';
	utc_buf[1] = '0';
	utc_buf[2] = date[4];
	utc_buf[3] = date[5];
	utc_buf[4] = '-';
	utc_buf[5] = date[2];
	utc_buf[6] = date[3];
	utc_buf[7] = '-';
	utc_buf[8] = date[0];
	utc_buf[9] = date[1];

	//Time format
	utc_buf[10] = 'T';
	utc_buf[11] = time[0];
	utc_buf[12] = time[1];
	utc_buf[13] = ':';
	utc_buf[14] = time[2];
	utc_buf[15] = time[3];
	utc_buf[16] = ':';
	utc_buf[17] = time[4];
	utc_buf[18] = time[5];
	utc_buf[19] = time[6];
	utc_buf[20] = time[7];
	utc_buf[21] = time[8];
	utc_buf[22] = time[9];
	utc_buf[23] = 'Z';
//	utc_buf[23] = '+';
//	utc_buf[24] = '0';
//	utc_buf[25] = '7';
//	utc_buf[26] = ':';
//	utc_buf[27] = '0';
//	utc_buf[28] = '0';

	utc_buf[24] = '\0';
	return 24;
}


char* get_gps_pkt_field (conf_gps_t *conf_ptr, uint16_t field_index) {
char* packet_ptr;
uint16_t i_cnt;

	packet_ptr = conf_ptr->pyl_buf_ptr;

	for (i_cnt = 0; i_cnt < field_index; i_cnt++) {
		packet_ptr = strchr (packet_ptr, ',');
		if (packet_ptr == NULL) {
			return NULL;
		}
		packet_ptr++;
	}

	return packet_ptr;
}

int16_t split_gprmc (conf_gps_t* conf_ptr, pktGPRMC_t* pkt_gprmc) {
char* tmp_ptr;
	tmp_ptr = GET_GNRMC_TIME_PTR(conf_ptr);
	if (*tmp_ptr != ',') memcpy(pkt_gprmc->utc_time, tmp_ptr , 10);

	tmp_ptr = GET_GNRMC_STATUS_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->status = *tmp_ptr;
	else pkt_gprmc->status = 'V';

	tmp_ptr = GET_GNRMC_LAT_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->lat = strtod (tmp_ptr, NULL);
	else pkt_gprmc->lat = 0.0;

	tmp_ptr = GET_GNRMC_NS_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->ns_ind = *tmp_ptr;
	else pkt_gprmc->ns_ind = 'N';

	tmp_ptr = GET_GNRMC_LON_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->lon = strtod (tmp_ptr, NULL);
	else pkt_gprmc->lon = 0.0;

	tmp_ptr = GET_GNRMC_EW_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->we_ind = *tmp_ptr;
	else pkt_gprmc->we_ind = 'W';

	tmp_ptr = GET_GNRMC_SPEED_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->speed_gnd = strtod (tmp_ptr, NULL);
	else pkt_gprmc->speed_gnd = 0.0;

	tmp_ptr = GET_GNRMC_COURSE_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gprmc->course_gnd =strtod (tmp_ptr, NULL);
	else pkt_gprmc->course_gnd = 0.0;

	tmp_ptr = GET_GNRMC_DATE_PTR(conf_ptr);
	if (*tmp_ptr != ',') memcpy(pkt_gprmc->utc_date, tmp_ptr , 6);
return 1;
}

int16_t split_gpgsa (conf_gps_t* conf_ptr, pktGPGSA_t* pkt_gpgsa) {
char* tmp_ptr;
uint8_t i_cnt;

	tmp_ptr = GET_GPGSA_OPER_MODE_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gpgsa->oper_mode = *tmp_ptr;

	tmp_ptr = GET_GPGSA_FIX_MODE_PTR(conf_ptr);
	if (*tmp_ptr != ',') pkt_gpgsa->fix_mode = *tmp_ptr;

	for (i_cnt = 0; i_cnt < 12; i_cnt++) {
		tmp_ptr = get_gps_pkt_field (conf_ptr, 3 + i_cnt);
		if (*tmp_ptr != ',') pkt_gpgsa->sat_used_ch[i_cnt] = atoi (tmp_ptr);
		else pkt_gpgsa->sat_used_ch[i_cnt] = 0;
	}

	tmp_ptr = GET_GPGSA_PDOP_PTR (conf_ptr);
	if (*tmp_ptr != ',') pkt_gpgsa->pdop = strtod (tmp_ptr, NULL);

	tmp_ptr = GET_GPGSA_HDOP_PTR (conf_ptr);
	if (*tmp_ptr != ',') pkt_gpgsa->hdop = strtod (tmp_ptr, NULL);

	tmp_ptr = GET_GPGSA_VDOP_PTR (conf_ptr);
	if (*tmp_ptr != ',') pkt_gpgsa->vdop = strtod (tmp_ptr, NULL);

	return 1;
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
//- END of File.
//------------------------------------------------------------------------------
