/*
 * RX4571LC.h
 *
 *  Created on: 2023/06/20
 *      Author: VINH-NT
 */

#ifndef RX4571LC_H_
#define RX4571LC_H_

#include "p_type_define.h"

#define IO_RTC_SK_ON           PORTB.PODR.BIT.B0 = 1      /* Clock */
#define IO_RTC_SK_OFF          PORTB.PODR.BIT.B0 = 0       /* Clock */

#define IO_RTC_DO_ON        PORTA.PODR.BIT.B6 = 1       /*DO */
#define IO_RTC_DO_OFF       PORTA.PODR.BIT.B6 = 0       /*DO */

#define IO_RTC_CE_ON     PORTA.PODR.BIT.B7 = 1       /* CE */
#define IO_RTC_CE_OFF    PORTA.PODR.BIT.B7 = 0       /* CE */

#define IO_RTC_DATA_IN_ONQ     (PORTA.PIDR.BIT.B6)         /* Data in */

#define IO_RTC_DATA_TO_OUT     PORTA.PDR.BIT.B6 = 1        /* Output */
#define IO_RTC_DATA_TO_IN      PORTA.PDR.BIT.B6 = 0        /* Input */

#endif /* RX4571LC_H_ */
