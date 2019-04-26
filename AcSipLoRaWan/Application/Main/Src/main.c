/**
 ******************************************************************************
 * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Src/main.c
 * @author  MCD Application Team
 * @version V1.5.0
 * @date    29-April-2016
 * @brief   This example describes how to send/receive bytes over USART IP using
 *          the STM32L4xx USART LL API in DMA mode.
 *          Peripheral initialization done using LL unitary services functions.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
/* Kernel includes. */
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
static void prvSetupHardware(void);
static void osTestTask(void *pvParameters);

int main(void) {

	prvSetupHardware();

	//os_dio_task_create();

	//os_buzzer_task_create();

	os_tmbase_task_create();

	//os_pm_task_create();

	//os_transtack_task_create();

	//os_rfid_task_create();

	//os_fuel_task_create();

	//os_sdcard_task_create();

	//os_can_task_create();

	//os_umrr_task_create();

	/* Application Task Create */
	xTaskCreate(osTestTask, "TEST", 4095, (void *) NULL, tskIDLE_PRIORITY,
			NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Infinite loop */
	while (1)
		continue;
}

uint8_t uart2_buf[2048];
int32_t uart2_len;

uint8_t uart3_buf[2048];
int32_t uart3_len;

#define UART3_CONN_UART2 		1

struct {
	uint32_t lat;
	uint32_t lon;
}__attribute__ ((packed)) gps_loc;


static void osTestTask(void *pvParameters) {
	portTickType xLastExecutionTime;
	uint32_t tick_snd_now = 0;
	uint32_t tick_snd_prev = 0;
	char reply_buf[128];
	uint8_t data[32];
	acsip_ret_t ret;

	uint32_t lat = 0;
	uint32_t lon = 0;

	// Initialise the xLastWakeTime variable with the current time.
	//xLastExecutionTime = xTaskGetTickCount();

	vTaskDelay(1000);

	tick_snd_prev = tick_snd_now = tick_sys;

	sip_reset_acsip();
	sip_set_echo_acsip(0);


//	gps_set_level_shift_acsip(1);
//
//	gps_set_positioning_cycle_acsip(15000);
//
//	gps_set_mode_acsip (GPS_MANUAL_MODE);

//	mac_join_acsip(ABP_MODE, reply_buf, sizeof(reply_buf));

	for (int i=0; i<sizeof(data); i++){
		data[i] = i;
	}

// *** Test Lib ACsip ***
	sip_testing();
	mac_testing();
	rf_testing();
	rm_testing();
	gps_testing();

	for (;;) {
		vTaskDelay(10);

		tick_snd_now = tick_sys;

		if ((tick_snd_now - tick_snd_prev) >= 30000) {
			tick_snd_prev = tick_snd_now;

//			ret = sip_get_ver_acsip(reply_buf, sizeof(reply_buf));
//			ret = gps_get_data_acsip(GPS_DD_DATA, reply_buf, sizeof(reply_buf));


			if (ret == ACSIP_OK_RET) {
				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n reply_buf : %s\r\n", reply_buf);
				gps_loc.lat = (uint32_t) (strtod (strstr(reply_buf, "LAT( ") + 5, NULL) * 1000000.0);
				gps_loc.lon = (uint32_t) (strtod (strstr(reply_buf, "LONG( ") + 6, NULL) * 1000000.0);

				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n LAT : %s\r\n LON : %s\r\n}\r\n\r\n", strstr(reply_buf, "LAT( ") , strstr(reply_buf, "LONG( ") );

				//LOG_INFO("\r\n\r\n[DEBUG]:{\r\n LAT : %lu\r\nLON : %lu\r\SIZE : %lu}\r\n\r\n",gps_loc.lat, gps_loc.lon, sizeof(gps_loc));



//				ret = mac_tx_acsip(UCNF_TYPE, 5, &gps_loc, sizeof(gps_loc));

				if (ret == ACSIP_OK_RET) {
					LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
					vTaskDelay(100);
					LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
				}else {
					LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
					vTaskDelay(100);
					LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				}

			} else {
				//os_puts_uart2("\n\r:error:\n\r");
				LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
				vTaskDelay(100);
				LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			}
		}


		if (UART3_CONN_UART2) {
			uart3_len = os_read_uart3(0, &uart3_buf[0], sizeof(uart3_buf));

			if (uart3_len > 0) {
				LL_GPIO_SetOutputPin(LED1_GPIO_PORT, LED1_PIN);
				// forward data from PC to ACSIP module
				os_write_uart2(0, &uart3_buf[0], uart3_len);

				vTaskDelay(100);
				LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);
			}

			uart2_len = os_read_uart2(0, &uart2_buf[0], sizeof(uart2_buf));

			if (uart2_len > 0) {
				LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
				// forward data from PC to ACSIP module
				os_write_uart3(0, &uart2_buf[0], uart2_len);

				vTaskDelay(100);
				LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
			}
		}

	}
}

// ************ SIP commands ************
sip_testing(void){
	char reply_buf[128];

	if(sip_factory_reset_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_factory_reset_acsip : Ok ^^\r\n");
//
//	if(sip_get_ver_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_ver_acsip : Ok ^^\r\n");
//
//	if(sip_get_hw_deveui_acsip(reply_buf,sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_hw_deveui_acsip : Ok ^^\r\n");

//	if(sip_reset_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_reset_acsip : Ok ^^\r\n");

//	if(sip_get_hw_model_acsip(reply_buf,sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_hw_model_acsip : Ok ^^\r\n");

//	if(sip_set_echo_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_echo_acsip : Ok ^^\r\n");

//	if(sip_set_log_info_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_log_info_acsip : Ok ^^\r\n");

//	if(sip_sleep_acsip(100, 1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_sleep_acsip : Ok ^^\r\n");

	// sip_set_baudrate_acsip --> Invalid
//	if(sip_set_baudrate_acsip(9600, "12345678") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_baudrate_acsip : Ok ^^\r\n");

//	if(sip_get_hw_model_ver_acsip(reply_buf,sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_hw_model_ver_acsip : Ok ^^\r\n");

//	if(sip_set_gpio_mode_acsip("A",0,1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_gpio_mode_acsip : Ok ^^\r\n");

//	if(sip_set_gpio_acsip("A",0,1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_gpio_acsip : Ok ^^\r\n");

//	if(sip_get_gpio_acsip("A", 2, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_gpio_acsip : Ok ^^\r\n");

//	if(sip_get_uuid_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_uuid_acsip : Ok ^^\r\n");

	// sip_set_storage_acsip --> Program error
//	if(sip_set_storage_acsip(1j3bf1vvTY7lEdhrnfJK+uFxBjMWzLXQrUX7bb7EqQLJ4NP0YHZ3Kx/Z39u50snKeeGizv/DHFf1wXFx+TR+oIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1rwYDg81gdqb2ANjEGXRcDnQjLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1ryMtkdk9IM0ibeWsSxpsda8jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1rzXbAusdw1dbcvlhRj11dt6jLZHZPSDNIm3lrEsabHWvIy2R2T0gzSJt5axLGmx1rxd3SJLjXB7aVreRHoaK2PJRYCHslxIF7oWIMDpA2ZFudNsyua50gvq7NZ1+p54yvcpgkC1kKnJQsJEFaZB9wUsqCSRa2mrXPWv5cDrpEKqLWJfD6s8GSdAMfMEUCCliP6tfxpiGbCIjbjr9OHIAyqxkL3+eSCanPl7t3fRO2ZNxRUWmd81m0G9obSqtaYJ7jFDhUsUgBQVje4WXsi4hwttjLZHZPSDNIm3lrEsabHWvN6pDShrAmgLVvT135RJYmrDODVMY5rehuabJ/dTHwHBoHWkumOiDN5tRiXutdnmwEyJq2xTW/IUwjpD022HduQ=cKs4b53) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_storage_acsip : Ok ^^\r\n");

//	if(sip_get_storage_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_get_storage_acsip : Ok ^^\r\n");

	// sip_set_iap_acsip --> Unknown command!
//	if(sip_set_iap_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_iap_acsip : Ok ^^\r\n");

	// sip_set_iap_mode_acsip --> Unknown command!
//	if(sip_set_iap_mode_acsip(0) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n sip_set_iap_mode_acsip : Ok ^^\r\n");
}

// ************ MAC commands ************
mac_testing(void){
	char reply_buf[128];

//	if(mac_set_linkchk_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_linkchk_acsip : Ok ^^\r\n");
//
//	if(mac_set_deveui_acsip(HW_DEVEUI) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_deveui_acsip : Ok ^^\r\n");
//
//	if(mac_set_appeui_acsip("0000000000000000") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_appeui_acsip : Ok ^^\r\n");
//
//	if(mac_set_appkey_acsip("2b7e151628aed2a6abf7158809cf4f3c") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_appkey_acsip : Ok ^^\r\n");
//
//	if(mac_set_devaddr_acsip("01234567") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_devaddr_acsip : Ok ^^\r\n");
//
//	if(mac_set_nwkskey_acsip("2b7e151628aed2a6abf7158809cf4f3c") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_nwkskey_acsip : Ok ^^\r\n");
//
//	if(mac_set_appskey_acsip("2b7e151628aed2a6abf7158809cf4f3c") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_appskey_acsip : Ok ^^\r\n");

//	if(mac_set_power_acsip("14") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_power_acsip : Ok ^^\r\n");
//
//	if(mac_set_dr_acsip("0") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_dr_acsip : Ok ^^\r\n");
//
//	if(mac_set_adr_acsip("1") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_adr_acsip : Ok ^^\r\n");
//
//	if(mac_set_txretry_acsip(8) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_txretry_acsip : Ok ^^\r\n");

//	if(mac_set_rxdelay1_acsip(1000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_rxdelay1_acsip : Ok ^^\r\n");
//
//	if(mac_set_rx2_acsip(0, 868000000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_rx2_acsip : Ok ^^\r\n");
//
//	if(mac_set_sync_acsip(34) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_sync_acsip : Ok ^^\r\n");
//
//	if(mac_set_ch_freq_acsip(0, 868000000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_ch_freq_acsip : Ok ^^\r\n");
//
//	if(mac_set_ch_dr_range(0, 0, 6) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_ch_dr_range : Ok ^^\r\n");

//	if(mac_set_ch_status_acsip(0, 1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_ch_status_acsip : Ok ^^\r\n");
//
//	if(mac_set_dc_ctl_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_dc_ctl_acsip : Ok ^^\r\n");
//
//	if(mac_set_dc_band_acsip(1, 100) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_dc_band_acsip : Ok ^^\r\n");
//
//	if(mac_set_join_ch_acsip(1, 1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_join_ch_acsip : Ok ^^\r\n");
//
//	if(mac_set_upcnt_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_upcnt_acsip : Ok ^^\r\n");

//	if(mac_set_downcnt_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_downcnt_acsip : Ok ^^\r\n");
//
//	if(mac_set_class_acsip(0) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_class_acsip : Ok ^^\r\n");

//	if(mac_join_acsip(ABP_MODE, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_join_acsip : Ok ^^\r\n");
//
//	if(mac_get_join_status_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_join_status_acsip : Ok ^^\r\n");
//
//	if(mac_save_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_save_acsip : Ok ^^\r\n");

//	if(mac_get_devaddr_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_devaddr_acsip : Ok ^^\r\n");
//
//	if(mac_get_deveui_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_deveui_acsip : Ok ^^\r\n");
//
//	if(mac_get_appeui_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_appeui_acsip : Ok ^^\r\n");
//
//	if(mac_get_nwkskey_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_nwkskey_acsip : Ok ^^\r\n");
//
//	if(mac_get_appskey_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_appskey_acsip : Ok ^^\r\n");
//
//	if(mac_get_appkey_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_appkey_acsip : Ok ^^\r\n");

//	if(mac_get_dr_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_dr_acsip : Ok ^^\r\n");
//
//	if(mac_get_band_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_band_acsip : Ok ^^\r\n");
//
//	if(mac_get_power_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_power_acsip : Ok ^^\r\n");
//
//	if(mac_get_adr_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_adr_acsip : Ok ^^\r\n");
//
//	if(mac_get_txretry_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_txretry_acsip : Ok ^^\r\n");
//
//	if(mac_get_rxdelay_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_rxdelay_acsip : Ok ^^\r\n");
//
//	if(mac_get_rx2_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_rx2_acsip : Ok ^^\r\n");
//
//	if(mac_get_sync_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_sync_acsip : Ok ^^\r\n");
//
//	if(mac_get_ch_para_acsip(0, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_ch_para_acsip : Ok ^^\r\n");
//
//	if(mac_get_ch_status_acsip(0, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_ch_status_acsip : Ok ^^\r\n");

//	if(mac_get_dc_ctl_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_dc_ctl_acsip : Ok ^^\r\n");
//
//	if(mac_get_dc_band_acsip(2, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_dc_band_acsip : Ok ^^\r\n");
//
//	if(mac_get_join_ch_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_join_ch_acsip : Ok ^^\r\n");
//
//	if(mac_get_upcnt_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_upcnt_acsip : Ok ^^\r\n");
//
//	if(mac_get_downcnt_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_downcnt_acsip : Ok ^^\r\n");
//
//	if(mac_get_class_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_class_acsip : Ok ^^\r\n");
//
//	if(mac_set_tx_mode_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_tx_mode_acsip : Ok ^^\r\n");
//
//	if(mac_get_tx_mode_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_tx_mode_acsip : Ok ^^\r\n");
//
//	if(mac_set_batt_acsip("254") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_batt_acsip : Ok ^^\r\n");
//
//	if(mac_get_batt_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_batt_acsip : Ok ^^\r\n");
//
//	if(mac_set_tx_confirm_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_tx_confirm_acsip : Ok ^^\r\n");
//
//	if(mac_get_tx_confirm_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_tx_confirm_acsip : Ok ^^\r\n");
//
//	// mac_set_claa_acsip --> Unknown command!
//	if(mac_set_claa_acsip("A") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_claa_acsip : Ok ^^\r\n");
//
//	// mac_get_claa_acsip --> Unknown command!
//	if(mac_get_claa_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_claa_acsip : Ok ^^\r\n");

//	// mac_set_getchinfo_acsip --> Unknown command!
//	if(mac_set_getchinfo_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_getchinfo_acsip : Ok ^^\r\n");
//
//	// mac_set_gettimeinfo_acsip --> Unknown command!
//	if(mac_set_gettimeinfo_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_gettimeinfo_acsip : Ok ^^\r\n");
//
//	// mac_set_jumboframe_acsip --> Unknown command!
//	if(mac_set_jumboframe_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_jumboframe_acsip : Ok ^^\r\n");
//
//	if(mac_set_lbt_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_lbt_acsip : Ok ^^\r\n");
//
//	if(mac_get_lbt_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_lbt_acsip : Ok ^^\r\n");
//
//	if(mac_set_uplink_dwell_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_uplink_dwell_acsip : Ok ^^\r\n");
//
//	if(mac_get_uplink_dwell_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_uplink_dwell_acsip : Ok ^^\r\n");
//
//	if(mac_set_downlink_dwell_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_downlink_dwell_acsip : Ok ^^\r\n");
//
//	if(mac_get_downlink_dwell_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_downlink_dwell_acsip : Ok ^^\r\n");
//
//	if(mac_set_max_eirp_acsip(4) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_max_eirp_acsip : Ok ^^\r\n");
//
//	if(mac_get_max_eirp_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_max_eirp_acsip : Ok ^^\r\n");
//
//	// mac set_ch_count 16 500 --> Invalid
//	if(mac_set_ch_count_acsip(16, 125) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_ch_count_acsip : Ok ^^\r\n");
//
//	if(mac_get_ch_count_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_ch_count_acsip : Ok ^^\r\n");

//	if(mac_set_keys_acsip("876543210", HW_DEVEUI, "0011223344556677", "00112233445566778899aabbccddeeff", "01112233445566778899aabbccddeeff", "02112233445566778899aabbccddeeff") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_keys_acsip : Ok ^^\r\n");

//	if(mac_set_tx_interval_acsip(6000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_tx_interval_acsip : Ok ^^\r\n");
//
//	if(mac_get_tx_interval_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_tx_interval_acsip : Ok ^^\r\n");
//
//	if(mac_set_rx1_freq_acsip(500300000, 200000, 8) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_rx1_freq_acsip : Ok ^^\r\n");
//
//	if(mac_get_rx1_freq_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_rx1_freq_acsip : Ok ^^\r\n");
//
//	if(mac_set_auto_join_otaa_acsip(1,3) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_auto_join_otaa_acsip : Ok ^^\r\n");
//
//	if(mac_set_auto_join_abp_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_auto_join_abp_acsip : Ok ^^\r\n");
//
//	if(mac_set_auto_join_off_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_set_auto_join_off_acsip : Ok ^^\r\n");
//
//	if(mac_get_auto_join_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_get_auto_join_acsip : Ok ^^\r\n");

	// DataIn is difference DataOut
//	if(mac_tx_acsip(UCNF_TYPE, 5, 1150, 5) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n mac_tx_acsip : Ok ^^\r\n");

}

// ************ RF commands ************
rf_testing(void){
	char reply_buf[128];

	//DataIn not equal to Dataout
//	if(rf_tx_acsip(15, 2) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_tx_acsip : Ok ^^\r\n");
//
//	if(rf_rx_acsip(1000, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_tx_acsip : Ok ^^\r\n");

//	if(rf_set_freq_acsip(915000000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_freq_acsip : Ok ^^\r\n");
//
//	if(rf_set_pwr_acsip(14) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_pwr_acsip : Ok ^^\r\n");

//	if(rf_set_sf_acsip(8) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_sf_acsip : Ok ^^\r\n");
//
//	if(rf_set_bw_acsip(250) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_bw_acsip : Ok ^^\r\n");
//
//	if(rf_set_cr_acsip("4/5") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_cr_acsip : Ok ^^\r\n");
//
//	if(rf_set_prlen_acsip(12) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_prlen_acsip : Ok ^^\r\n");
//
//	if(rf_set_crc_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_crc_acsip : Ok ^^\r\n");
//
//	if(rf_set_iqi_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_iqi_acsip : Ok ^^\r\n");
//
//	if(rf_set_sync_acsip(12) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_sync_acsip : Ok ^^\r\n");
//
//	if(rf_save_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_save_acsip : Ok ^^\r\n");

//	if(rf_get_freq_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_freq_acsip : Ok ^^\r\n");
//
//	if(rf_get_pwr_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_pwr_acsip : Ok ^^\r\n");
//
//	if(rf_get_sf_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_sf_acsip : Ok ^^\r\n");
//
//	if(rf_get_bw_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_bw_acsip : Ok ^^\r\n");
//
//	if(rf_get_prlen_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_prlen_acsip : Ok ^^\r\n");
//
//	if(rf_get_crc_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_crc_acsip : Ok ^^\r\n");
//
//	if(rf_get_iqi_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_iqi_acsip : Ok ^^\r\n");
//
//	if(rf_get_cr_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_cr_acsip : Ok ^^\r\n");
//
//	if(rf_get_sync_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_sync_acsip : Ok ^^\r\n");

	// rf_rx_con_acsip --> have a problem
//	if(rf_rx_con_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_rx_con_acsip : Ok ^^\r\n");

	// rf_fsk_acsip --> have a problem
//	if(rf_fsk_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_fsk_acsip : Ok ^^\r\n");

	// rf_lora_tx_start_acsip --> have a problem
//	if(rf_lora_tx_start_acsip(100, 200, "aaaa5555") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_lora_tx_start_acsip : Ok ^^\r\n");

//	if(rf_lora_rx_start_acsip("aaaa5555", reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_lora_rx_start_acsip : Ok ^^\r\n");

	if(rf_lora_tx_stop_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_lora_tx_stop_acsip : Ok ^^\r\n");

//	if(rf_set_fdev_acsip(100) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_fdev_acsip : Ok ^^\r\n");

//	if(rf_get_fdev_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_fdev_acsip : Ok ^^\r\n");

//	if(rf_set_cad_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_set_cad_acsip : Ok ^^\r\n");

//	if(rf_get_cad_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_get_cad_acsip : Ok ^^\r\n");

//	if(rf_cad_acsip(922500000, 10, 125, 12, 1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rf_cad_acsip : Ok ^^\r\n");
}

// ************ RM commands ************
rm_testing(void){
	char reply_buf[128];

//	if(rm_set_gpio_acsip("in", 0, "C", 9) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_gpio_acsip : Ok ^^\r\n");
//
//	if(rm_get_gpio_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_gpio_acsip : Ok ^^\r\n");
//
//	if(rm_set_gpio_swtich_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_gpio_swtich_acsip : Ok ^^\r\n");
//
//	if(rm_get_gpio_swtich_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_gpio_swtich_acsip : Ok ^^\r\n");
//
//	if(rm_set_adc_acsip(1, 1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_adc_acsip : Ok ^^\r\n");
//
//	if(rm_get_adc_acsip(0, reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_adc_acsip : Ok ^^\r\n");
//
//	if(rm_set_adc_switch_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_adc_switch_acsip : Ok ^^\r\n");
//
//	if(rm_get_adc_switch_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_adc_switch_acsip : Ok ^^\r\n");
//
//	if(rm_set_port_uplink_acsip(200) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_port_uplink_acsip : Ok ^^\r\n");
//
//	if(rm_set_port_downlink_acsip(201) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_port_downlink_acsip : Ok ^^\r\n");
//
//	if(rm_get_port_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_port_acsip : Ok ^^\r\n");
//
//	if(rm_set_mode_acsip("cycle") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_mode_acsip : Ok ^^\r\n");
//
//	if(rm_get_mode_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_mode_acsip : Ok ^^\r\n");
//
//	if(rm_set_trigger_acsip("C", 7, "rising") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_set_trigger_acsip : Ok ^^\r\n");
//
//	if(rm_get_trigger_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n rm_get_trigger_acsip : Ok ^^\r\n");
}

// ************ GPS commands ************
gps_testing(void){
	char reply_buf[128];

//	if(gps_set_level_shift_acsip(1) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_level_shift_acsip : Ok ^^\r\n");
//
//	if(gps_set_nmea_rmc_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_nmea_rmc_acsip : Ok ^^\r\n");
//
//	if(gps_set_port_uplink_acsip(20) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_port_uplink_acsip : Ok ^^\r\n");
//
//	if(gps_set_format_uplink_acsip("raw") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_format_uplink_acsip : Ok ^^\r\n");
//
//	if(gps_set_positioning_cycle_acsip(3000) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_positioning_cycle_acsip : Ok ^^\r\n");
//
//	if(gps_set_mode_acsip("auto") == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_set_mode_acsip : Ok ^^\r\n");
//
//	if(gps_get_mode_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_get_mode_acsip : Ok ^^\r\n");
//
//	if(gps_get_data_acsip("dd", reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_get_data_acsip : Ok ^^\r\n");
//
//	if(gps_sleep_on_acsip(0) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_sleep_on_acsip : Ok ^^\r\n");
//
//	if(gps_sleep_off_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_sleep_off_acsip : Ok ^^\r\n");
//
//	if(gps_get_ttff_acsip(reply_buf, sizeof(reply_buf)) == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_get_ttff_acsip : Ok ^^\r\n");
//
//	if(gps_reset_acsip() == ACSIP_OK_RET) LOG_INFO("\r\n\r\n[SIP]:\r\n gps_reset_acsip : Ok ^^\r\n");
}

#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
static void prvSetupHardware(void) {
	/* Configure the system clock to 80 MHz */
	SystemClock_Config();

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	NVIC_SetPriority(MemoryManagement_IRQn, 0);
	/* BusFault_IRQn interrupt configuration */
	NVIC_SetPriority(BusFault_IRQn, 0);
	/* UsageFault_IRQn interrupt configuration */
	NVIC_SetPriority(UsageFault_IRQn, 0);
	/* SVCall_IRQn interrupt configuration */
	NVIC_SetPriority(SVCall_IRQn, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	NVIC_SetPriority(DebugMonitor_IRQn, 0);
	/* PendSV_IRQn interrupt configuration */
	NVIC_SetPriority(PendSV_IRQn, 15);
	/* SysTick  IRQn interrupt configuration */
	NVIC_SetPriority(SysTick_IRQn, 15);

	/* Initialize LED2 */
	init_led();

	/* Initialize button in EXTI mode */
	//init_usr_btn();
	os_init_uart1(115200UL, 4096UL);

	os_init_uart2(115200UL, 2048UL);

	os_init_uart3(115200UL, 2048UL);

	//os_init_uart3(115200UL, 4096UL);

	os_init_uart4(115200UL, 4096UL);

	os_init_uart5(115200UL, 2048UL);   //GPS Module Interface

	xInit_adc();

	LOG_INFO("\r\n[SYSTEM]: RESET STATUS {\r\n");

	if (LL_RCC_IsActiveFlag_FWRST())
		LOG_INFO("  >>>>>> Reset from the firewall occurred");

	if (LL_RCC_IsActiveFlag_IWDGRST())
		LOG_INFO("  >>>>>> Independent watchdog reset occurred");

	if (LL_RCC_IsActiveFlag_LPWRRST())
		LOG_INFO("  >>>>>> Illegal mode reset occurred");

	if (LL_RCC_IsActiveFlag_OBLRST())
		LOG_INFO("  >>>>>> Reset from Option Byte loading occurred");

	if (LL_RCC_IsActiveFlag_PINRST())
		LOG_INFO("  >>>>>> Reset from NRST pin occurred");

	if (LL_RCC_IsActiveFlag_SFTRST())
		LOG_INFO("  >>>>>> Software reset occurred");

	if (LL_RCC_IsActiveFlag_WWDGRST())
		LOG_INFO("  >>>>>> Window watchdog reset occurred");

	if (LL_RCC_IsActiveFlag_BORRST())
		LOG_INFO("  >>>>>> BOR occurred");

	LL_RCC_ClearResetFlags();
	LOG_INFO("\r\n}\r\n\r\n");

}
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler */
}
#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d", file, line) */

	/* Infinite loop */
	while (1) {
	}
}
#endif

/*-----------------------------------------------------------*/
void vApplicationTickHook(void) {

}

/*-----------------------------------------------------------*/
void vApplicationMallocFailedHook(void) {
	/* vApplicationMallocFailedHook() will only be called if
	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	 function that will get called if a call to pvPortMalloc() fails.
	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
	 timer or semaphore is created.  It is also called by various parts of the
	 demo application.  If heap_1.c or heap_2.c are used, then the size of the
	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	 to query the size of free heap space that remains (although it does not

	 provide information on how the remaining heap might be fragmented). */
	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	 task.  It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()).  If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
	(void) pcTaskName;
	(void) pxTask;

	/* Run time stack overflow checking is performed if
	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	 function is called if a stack overflow is detected. */
	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
	taskDISABLE_INTERRUPTS();
	for (;;)
		;
}
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

///**
// ******************************************************************************
// * @file    Examples_LL/USART/USART_Communication_TxRx_DMA/Src/main.c
// * @author  MCD Application Team
// * @version V1.5.0
// * @date    29-April-2016
// * @brief   This example describes how to send/receive bytes over USART IP using
// *          the STM32L4xx USART LL API in DMA mode.
// *          Peripheral initialization done using LL unitary services functions.
// ******************************************************************************
// * @attention
// *
// * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
// *
// * Redistribution and use in source and binary forms, with or without modification,
// * are permitted provided that the following conditions are met:
// *   1. Redistributions of source code must retain the above copyright notice,
// *      this list of conditions and the following disclaimer.
// *   2. Redistributions in binary form must reproduce the above copyright notice,
// *      this list of conditions and the following disclaimer in the documentation
// *      and/or other materials provided with the distribution.
// *   3. Neither the name of STMicroelectronics nor the names of its contributors
// *      may be used to endorse or promote products derived from this software
// *      without specific prior written permission.
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// ******************************************************************************
// */
//
///* Includes ------------------------------------------------------------------*/
///* Kernel includes. */
//#include "main.h"
//
///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
///* Private function prototypes -----------------------------------------------*/
///* Private functions ---------------------------------------------------------*/
//
///**
// * @brief  Main program
// * @param  None
// * @retval None
// */
//static void prvSetupHardware(void);
//static void osTestTask(void *pvParameters);
//
//int main(void) {
//
//	prvSetupHardware();
//
//	//os_dio_task_create();
//
//	//os_buzzer_task_create();
//
//	os_tmbase_task_create();
//
//	//os_pm_task_create();
//
//	//os_transtack_task_create();
//
//	//os_rfid_task_create();
//
//	//os_fuel_task_create();
//
//	//os_sdcard_task_create();
//
//	//os_can_task_create();
//
//
//	//os_umrr_task_create();
//
//	/* Application Task Create */
//	xTaskCreate(osTestTask, "TEST", 2048, (void *) NULL, tskIDLE_PRIORITY, NULL);
//
//	/* Start the scheduler. */
//	vTaskStartScheduler();
//
//	/* Infinite loop */
//	while (1)
//		continue;
//}
//
//
//static void osTestTask(void *pvParameters) {
//	portTickType xLastExecutionTime;
//	uint32_t tick_led=0;
//	char* res;
//	// Initialise the xLastWakeTime variable with the current time.
//	xLastExecutionTime = xTaskGetTickCount();
//
//	sip_reset_acsip();
//	sip_set_echo_acsip(0);
//
//
//	res = mac_join_abp_acsip();
//
//	if (strstr (res, "Ok") != NULL ) {
//		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//		vTaskDelay(100);
//		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//	}
//	else {
//		//os_puts_uart2("\n\r:error:\n\r");
//		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//		vTaskDelay(100);
//		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//	}
//
//
//	for (;;) {
//
//		vTaskDelayUntil(&xLastExecutionTime, 1000);
//
//        if (++tick_led == 10) {
//        	tick_led = 0;
//
//        	//res = sip_get_ver_acsip();
//        	//res = sip_get_hw_deveui_acsip();
//
//
//        	res = mac_tx_acsip(CNF_TYPE, 5, "1234");
//
//        	if (strstr (res, "Ok") != NULL ) {
//        		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//        		vTaskDelay(100);
//        		LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
//        	}
//        	else {
//        		//os_puts_uart2("\n\r:error:\n\r");
//        		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//        		vTaskDelay(100);
//        		LL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
//        	}
//        }
//
//
//	}
//}
//
//#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
//                                                                 0 bit  for subpriority */
//static void prvSetupHardware(void) {
//	/* Configure the system clock to 80 MHz */
//	SystemClock_Config();
//
//	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
//
//	/* System interrupt init*/
//	/* MemoryManagement_IRQn interrupt configuration */
//	NVIC_SetPriority(MemoryManagement_IRQn, 0);
//	/* BusFault_IRQn interrupt configuration */
//	NVIC_SetPriority(BusFault_IRQn, 0);
//	/* UsageFault_IRQn interrupt configuration */
//	NVIC_SetPriority(UsageFault_IRQn, 0);
//	/* SVCall_IRQn interrupt configuration */
//	NVIC_SetPriority(SVCall_IRQn, 0);
//	/* DebugMonitor_IRQn interrupt configuration */
//	NVIC_SetPriority(DebugMonitor_IRQn, 0);
//	/* PendSV_IRQn interrupt configuration */
//	NVIC_SetPriority(PendSV_IRQn, 15);
//	/* SysTick_IRQn interrupt configuration */
//	NVIC_SetPriority(SysTick_IRQn, 15);
//
//	/* Initialize LED2 */
//	init_led();
//
//	/* Initialize button in EXTI mode */
//	//init_usr_btn();
//	os_init_uart1(115200UL, 4096UL);
//
//	os_init_uart2(115200UL, 4096UL);
//
//	os_init_uart3(9600UL, 2048UL);
//
//	//os_init_uart3(115200UL, 4096UL);
//
//	os_init_uart4(115200UL, 4096UL);
//
//	os_init_uart5(115200UL, 2048UL);   //GPS Module Interface
//
//	xInit_adc();
//
//
//
//	/*	LOG_INFO("\r\n[SYSTEM]: RESET STATUS {\r\n");
//
//	if (LL_RCC_IsActiveFlag_FWRST())
//		LOG_INFO ("  >>>>>> Reset from the firewall occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_IWDGRST())
//		LOG_INFO("  >>>>>> Independent watchdog reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_LPWRRST())
//		LOG_INFO("  >>>>>> Illegal mode reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_OBLRST())
//		LOG_INFO("  >>>>>> Reset from Option Byte loading occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_PINRST())
//		LOG_INFO("  >>>>>> Reset from NRST pin occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_SFTRST())
//		LOG_INFO("  >>>>>> Software reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_WWDGRST())
//		LOG_INFO("  >>>>>> Window watchdog reset occurred\r\n");
//
//	if (LL_RCC_IsActiveFlag_BORRST())
//		LOG_INFO("  >>>>>> BOR occurred\r\n");
//
//	LL_RCC_ClearResetFlags();
//	LOG_INFO("}\r\n\r\n");*/
//
//}
//void Error_Handler(void)
//{
//  /* USER CODE BEGIN Error_Handler */
//  /* User can add his own implementation to report the HAL error return state */
//  while(1)
//  {
//  }
//  /* USER CODE END Error_Handler */
//}
//#ifdef  USE_FULL_ASSERT
//
///**
// * @brief  Reports the name of the source file and the source line number
// *         where the assert_param error has occurred.
// * @param  file: pointer to the source file name
// * @param  line: assert_param error line source number
// * @retval None
// */
//void assert_failed(uint8_t *file, uint32_t line) {
//	/* User can add his own implementation to report the file name and line number,
//	 ex: printf("Wrong parameters value: file %s on line %d", file, line) */
//
//	/* Infinite loop */
//	while (1) {
//	}
//}
//#endif
//
///*-----------------------------------------------------------*/
//void vApplicationTickHook(void) {
//
//}
//
///*-----------------------------------------------------------*/
//void vApplicationMallocFailedHook(void) {
//	/* vApplicationMallocFailedHook() will only be called if
//	 configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
//	 function that will get called if a call to pvPortMalloc() fails.
//	 pvPortMalloc() is called internally by the kernel whenever a task, queue,
//	 timer or semaphore is created.  It is also called by various parts of the
//	 demo application.  If heap_1.c or heap_2.c are used, then the size of the
//	 heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
//	 FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
//	 to query the size of free heap space that remains (although it does not
//
//	 provide information on how the remaining heap might be fragmented). */
//	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
//	taskDISABLE_INTERRUPTS();
//	for (;;)
//		;
//}
///*-----------------------------------------------------------*/
//
//void vApplicationIdleHook(void) {
//	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
//	 to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
//	 task.  It is essential that code added to this hook function never attempts
//	 to block in any way (for example, call xQueueReceive() with a block time
//	 specified, or call vTaskDelay()).  If the application makes use of the
//	 vTaskDelete() API function (as this demo application does) then it is also
//	 important that vApplicationIdleHook() is permitted to return to its calling
//	 function, because it is the responsibility of the idle task to clean up
//	 memory allocated by the kernel to any task that has since been deleted. */
//}
///*-----------------------------------------------------------*/
//
//void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
//	(void) pcTaskName;
//	(void) pxTask;
//
//	/* Run time stack overflow checking is performed if
//	 configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
//	 function is called if a stack overflow is detected. */
//	LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
//	taskDISABLE_INTERRUPTS();
//	for (;;)
//		;
//}
///*-----------------------------------------------------------*/
//
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

