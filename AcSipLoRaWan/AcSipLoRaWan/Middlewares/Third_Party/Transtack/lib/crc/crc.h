#ifndef __CRC_H__
#define __CRC_H__
// CRC-16 (Modbus) 
extern volatile const uint8_t auchCRCLo[];
extern volatile const uint8_t auchCRCHi[];

extern uint16_t CRC16_FAST_GEN(uint16_t value_init, uint8_t *u8Data, uint8_t u8Length);
extern uint16_t CRC16_GEN(uint16_t value_init, uint8_t *u8Data, uint8_t u8Length);
extern void CRC_TST(void);
#endif 

