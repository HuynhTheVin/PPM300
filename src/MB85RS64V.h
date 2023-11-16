/*
 * MB85RS64V.h
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */

#ifndef MB85RS64V_H_
#define MB85RS64V_H_

#include "p_type_define.h"

WORD get_fram2(WORD address); /* 16bit access */
void put_fram2(WORD address, WORD data); /* 16bit access */

/* 8bit access. Note: Double the base address to match 16bit data access. */
WORD get_fram1(WORD address);
/* 8bit access. Note: Double the base address to match 16bit data access. */
void put_fram1(WORD address, WORD data);


#define IO_FRAM_CS_ON           PORT5.PODR.BIT.B3 = 0       /* cs */
#define IO_FRAM_CS_OFF          PORT5.PODR.BIT.B3 = 1       /* cs */

#define IO_FRAM_CLOCK_ON        PORT5.PODR.BIT.B1 = 1       /* Clock */
#define IO_FRAM_CLOCK_OFF       PORT5.PODR.BIT.B1 = 0       /* Clock */

#define IO_FRAM_DATA_OUT_ON     PORT5.PODR.BIT.B0 = 1       /* Data out */
#define IO_FRAM_DATA_OUT_OFF    PORT5.PODR.BIT.B0 = 0       /* Data out */

#define IO_FRAM_DATA_IN_ON     (PORT5.PIDR.BIT.B2)       /* Data in */
#define IO_FRAM_DATA_IN_OFF    PORT5.PIDR.BIT.B2 = 0       /* Data in */

#define IO_FRAM_DATA_TO_OUT     PORT5.PDR.BIT.B0 = 1        /* Output */
#define IO_FRAM_DATA_TO_IN      PORT5.PDR.BIT.B2 = 0        /* Input */



#endif /* MB85RS64V_H_ */
