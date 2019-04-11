/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "tm_stm32f4_swo.h"

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* If SWO debug is enabled */
#if SWO_DEBUG_ENABLED == 1

/* File struct for SWO output */
//FILE TM_SWO_File;

//int TM_SWO_fputc(int ch, FILE *f) {
//	/* Check parameters */
//	if (
//		(ITM->TCR & ITM_TCR_ITMENA_Msk) &&      /* ITM enabled */
//		(ITM->TER & (1UL << 0))					/* ITM Port #0 enabled */
//	) {
//		while (ITM->PORT[0].u32 == 0);			/* Wait for available */
//		ITM->PORT[0].u8 = (uint8_t) ch;			/* Send character */
//
//		/* Return written character */
//		return ch;
//	}
//
//	/* Return EOF to stop writing */
//	return -1;
//}

//void TM_SWO_Init(void) {
//	/* Enable SWO output */
//	DBGMCU->CR = 0x00000020;
//
//	/* Link output function for output stream functionality */
//	//TM_STDIO_SetOutputFunction(&TM_SWO_File, TM_SWO_fputc);
//
//
//}

//void SWO_Init(uint32_t portBits, uint32_t cpuCoreFreqHz) {
//  uint32_t SWOSpeed = 64000; /* default 64k baud rate */
//  uint32_t SWOPrescaler = (cpuCoreFreqHz / SWOSpeed) - 1; /* SWOSpeed in Hz, note that cpuCoreFreqHz is expected to be match the CPU core clock */
//
//  CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; /* enable trace in core debug */
//  *((volatile unsigned *)(ITM_BASE + 0x400F0)) = 0x00000002; /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ, 1: SWO Manchester encoding) */
//  *((volatile unsigned *)(ITM_BASE + 0x40010)) = SWOPrescaler; /* "Async Clock Prescaler Register". Scale the baud rate of the asynchronous output */
//  *((volatile unsigned *)(ITM_BASE + 0x00FB0)) = 0xC5ACCE55; /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
//  ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
//  ITM->TPR = ITM_TPR_PRIVMASK_Msk; /* ITM Trace Privilege Register */
//  ITM->TER = portBits; /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
//  *((volatile unsigned *)(ITM_BASE + 0x01000)) = 0x400003FE; /* DWT_CTRL */
//  *((volatile unsigned *)(ITM_BASE + 0x40304)) = 0x00000100; /* Formatter and Flush Control Register */
//}

/*!
 * \brief Sends a character over the SWO channel
 * \param c Character to be sent
 * \param portNo SWO channel number, value in the range of 0 to 31
 */
//void SWO_PrintChar(char c, uint8_t portNo) {
//  volatile int timeout;
//
//  /* Check if Trace Control Register (ITM->TCR at 0xE0000E80) is set */
//  if ((ITM->TCR&ITM_TCR_ITMENA_Msk) == 0) { /* check Trace Control Register if ITM trace is enabled*/
//    return; /* not enabled? */
//  }
//  /* Check if the requested channel stimulus port (ITM->TER at 0xE0000E00) is enabled */
//  if ((ITM->TER & (1ul<<portNo))==0) { /* check Trace Enable Register if requested port is enabled */
//    return; /* requested port not enabled? */
//  }
//  timeout = 5000; /* arbitrary timeout value */
//  while (ITM->PORT[0].u32 == 0) {
//    /* Wait until STIMx is ready, then send data */
//    timeout--;
//    if (timeout==0) {
//      return; /* not able to send */
//    }
//  }
//  ITM->PORT[0].u16 = 0x08 | (c<<8);
//}

/*!
 * \brief Sends a string over SWO to the host
 * \param s String to send
 * \param portNumber Port number, 0-31, use 0 for normal debug strings
 */
//void SWO_PrintString(const char *s, uint8_t portNumber) {
//  while (*s!='\0') {
//    SWO_PrintChar(*s++, portNumber);
//  }
//}

//PUTCHAR_PROTOTYPE
//{
//	/* Check parameters */
//	if (
//		(ITM->TCR & ITM_TCR_ITMENA_Msk) &&      /* ITM enabled */
//		(ITM->TER & (1UL << 0))					/* ITM Port #0 enabled */
//	) {
//		while (ITM->PORT[0].u32 == 0);			/* Wait for available */
//		ITM->PORT[0].u8 = (uint8_t) ch;			/* Send character */
//
//		/* Return written character */
//		return ch;
//	}
//
//	/* Return EOF to stop writing */
//	return -1;
//}
#ifdef SWO_DEBUG
PUTCHAR_PROTOTYPE
{
	ITM_SendChar(ch);
	return ch;
}

int _write(int file, char *ptr, int len) {
	int ind;

	for (ind = 0; ind < len; ind++) {
		__io_putchar(*ptr++);
	}
	return len;
}
#endif
#endif
