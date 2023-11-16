/*
 * p_macro_define.h
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */

#ifndef P_MACRO_DEFINE_H_
#define P_MACRO_DEFINE_H_

#include "r_smc_entry.h"

#define IO_POWER_OFF                PORT6.PODR.BIT.B0 = 0     /*電源OFF */

#define IO_OUT_DH_ONQ     (PORTE.PODR.BIT.B2 == 1)    /* DH 出力             */
#define IO_OUT_DH_ON      PORTE.PODR.BIT.B2 = 1       /* DH 出力             */
#define IO_OUT_DH_OFF     PORTE.PODR.BIT.B2 = 0       /* DH 出力             */

#define IO_OUT_JOSO_ONQ     (PORTE.PODR.BIT.B3 == 1)    /* 除霜出力             */
#define IO_OUT_JOSO_ON      PORTE.PODR.BIT.B3 = 1       /* 除霜出力              */
#define IO_OUT_JOSO_OFF     PORTE.PODR.BIT.B3 = 0       /* 除霜出力              */

#define IO_OUT_DHH_ONQ     (PORTE.PODR.BIT.B4 == 1)    /* DHH出力             */
#define IO_OUT_DHH_ON      PORTE.PODR.BIT.B4 = 1       /* DHH出力              */
#define IO_OUT_DHH_OFF     PORTE.PODR.BIT.B4 = 0       /* DHH出力              */

#define IO_OUT_SV2_ONQ     (PORTE.PODR.BIT.B5 == 1)    /* SV2出力             */
#define IO_OUT_SV2_ON      PORTE.PODR.BIT.B5 = 1       /* SV2出力              */
#define IO_OUT_SV2_OFF     PORTE.PODR.BIT.B5 = 0       /* SV2出力              */

#define IO_OUT_SV3_ONQ     (PORTE.PODR.BIT.B6 == 1)    /* SV3出力             */
#define IO_OUT_SV3_ON      PORTE.PODR.BIT.B6 = 1       /* SV3出力              */
#define IO_OUT_SV3_OFF     PORTE.PODR.BIT.B6 = 0       /* SV3出力              */

#define IO_OUT_SV4_ONQ     (PORTE.PODR.BIT.B7 == 1)    /* SV4出力             */
#define IO_OUT_SV4_ON      PORTE.PODR.BIT.B7 = 1       /* SV4出力              */
#define IO_OUT_SV4_OFF     PORTE.PODR.BIT.B7 = 0       /* SV4出力              */

#define IO_OUT_ARSV_ONQ     (PORTA.PODR.BIT.B0 == 1)    /* ARSV出力             */
#define IO_OUT_ARSV_ON      PORTA.PODR.BIT.B0 = 1       /* ARSV出力              */
#define IO_OUT_ARSV_OFF     PORTA.PODR.BIT.B0 = 0       /* ARSV出力              */

#define IO_OUT_SPSV_ONQ     (PORTA.PODR.BIT.B1 == 1)    /* SPSV出力             */
#define IO_OUT_SPSV_ON      PORTA.PODR.BIT.B1 = 1       /* SPSV出力              */
#define IO_OUT_SPSV_OFF     PORTA.PODR.BIT.B1 = 0       /* SPSV出力              */

#define IO_OUT_FAN1_ONQ     (PORTA.PODR.BIT.B2 == 1)    /* FAN1出力             */
#define IO_OUT_FAN1_ON      PORTA.PODR.BIT.B2 = 1       /* FAN1出力              */
#define IO_OUT_FAN1_OFF     PORTA.PODR.BIT.B2 = 0       /* FAN1出力              */

#define IO_OUT_FAN2_ONQ     (PORTA.PODR.BIT.B3 == 1)    /* FAN2出力             */
#define IO_OUT_FAN2_ON      PORTA.PODR.BIT.B3 = 1       /* FAN2出力              */
#define IO_OUT_FAN2_OFF     PORTA.PODR.BIT.B3 = 0       /* FAN2出力              */

#define IO_OUT_FAN3_ONQ     (PORTA.PODR.BIT.B4 == 1)    /* FAN3出力             */
#define IO_OUT_FAN3_ON      PORTA.PODR.BIT.B4 = 1       /* FAN3出力              */
#define IO_OUT_FAN3_OFF     PORTA.PODR.BIT.B4 = 0       /* FAN3出力              */

#define IO_OUT_OVN_ONQ     (PORTJ.PODR.BIT.B2 == 1)    /* OVN出力             */
#define IO_OUT_OVN_ON      PORTJ.PODR.BIT.B2 = 1       /* OVN出力              */
#define IO_OUT_OVN_OFF     PORTJ.PODR.BIT.B2 = 0       /* OVN出力              */

#define IO_OUT_TA_ONQ     (PORT0.PODR.BIT.B7 == 1)    /* TA出力             */
#define IO_OUT_TA_ON      PORT0.PODR.BIT.B7 = 1       /* TA出力              */
#define IO_OUT_TA_OFF     PORT0.PODR.BIT.B7 = 0       /* TA出力              */

#define IO_OUT_LA_ONQ     (PORTD.PODR.BIT.B0 == 1)    /* LA出力             */
#define IO_OUT_LA_ON      PORTD.PODR.BIT.B0 = 1       /* LA出力              */
#define IO_OUT_LA_OFF     PORTD.PODR.BIT.B0 = 0       /* LA出力              */

#define IO_OUT_H1_ONQ     (PORTA.PODR.BIT.B5 == 1)    /* H1出力             */
#define IO_OUT_H1_ON      PORTA.PODR.BIT.B5 = 1       /* H1出力              */
#define IO_OUT_H1_OFF     PORTA.PODR.BIT.B5 = 0       /* H1出力              */

#define IO_OUT_H2_ONQ     (PORTB.PODR.BIT.B1 == 1)    /* H2出力             */
#define IO_OUT_H2_ON      PORTB.PODR.BIT.B1 = 1       /* H2出力              */
#define IO_OUT_H2_OFF     PORTB.PODR.BIT.B1 = 0       /* H2出力              */

#define IO_OUT_H3_ONQ     (PORTB.PODR.BIT.B2 == 1)    /* H3出力             */
#define IO_OUT_H3_ON      PORTB.PODR.BIT.B2 = 1       /* H3出力              */
#define IO_OUT_H3_OFF     PORTB.PODR.BIT.B2 = 0       /* H3出力              */

#define IO_OUT_H4_ONQ     (PORTB.PODR.BIT.B3 == 1)    /* H4出力             */
#define IO_OUT_H4_ON      PORTB.PODR.BIT.B3 = 1       /* H4出力              */
#define IO_OUT_H4_OFF     PORTB.PODR.BIT.B3 = 0       /* H4出力              */

#define IO_OUT_HG_ONQ     (PORTB.PODR.BIT.B4 == 1)    /* HG出力             */
#define IO_OUT_HG_ON      PORTB.PODR.BIT.B4 = 1       /* HG出力              */
#define IO_OUT_HG_OFF     PORTB.PODR.BIT.B4 = 0       /* HG出力              */

#define IO_OUT_WG_ONQ     (PORTB.PODR.BIT.B5 == 1)    /* WG出力             */
#define IO_OUT_WG_ON      PORTB.PODR.BIT.B5 = 1       /* WG出力              */
#define IO_OUT_WG_OFF     PORTB.PODR.BIT.B5 = 0       /* WG出力              */

#define IO_OUT_YOBI_ONQ     (PORTB.PODR.BIT.B6 == 1)    /* 予備出力             */
#define IO_OUT_YOBI_ON      PORTB.PODR.BIT.B6 = 1       /* 予備出力              */
#define IO_OUT_YOBI_OFF     PORTB.PODR.BIT.B6 = 0       /* 予備出力              */

#define IO_OUT_BUZZER_ONQ     (PORTB.PODR.BIT.B7 == 1)    /* ブザー出力             */
#define IO_OUT_BUZZER_ON      PORTB.PODR.BIT.B7 = 1       /* ブザー出力              */
#define IO_OUT_BUZZER_OFF     PORTB.PODR.BIT.B7 = 0       /* ブザー出力              */

#define IO_OUT_MT1_ONQ     (PORTC.PODR.BIT.B1 == 1)    /* MT1出力             */
#define IO_OUT_MT1_ON      PORTC.PODR.BIT.B1 = 1       /* MT1出力              */
#define IO_OUT_MT1_OFF     PORTC.PODR.BIT.B1 = 0       /* MT1出力              */

#define IO_OUT_MT2_ONQ     (PORTB.PODR.BIT.B4 == 1)    /* MT2出力             */
#define IO_OUT_MT2_ON      PORTB.PODR.BIT.B4 = 1       /* MT2出力              */
#define IO_OUT_MT2_OFF     PORTB.PODR.BIT.B4 = 0       /* MT2出力              */

#define IO_OUT_MT3_ONQ     (PORTB.PODR.BIT.B5 == 1)    /* MT3出力             */
#define IO_OUT_MT3_ON      PORTB.PODR.BIT.B5 = 1       /* MT3出力              */
#define IO_OUT_MT3_OFF     PORTB.PODR.BIT.B5 = 0       /* MT3出力              */

#define IO_OUT_CPC_ONQ     (PORTD.PODR.BIT.B2 == 1)    /* CPC出力             */
#define IO_OUT_CPC_ON      PORTD.PODR.BIT.B2 = 1       /* CPC出力              */
#define IO_OUT_CPC_OFF     PORTD.PODR.BIT.B2 = 0       /* CPC出力              */

#define IO_OUT_RS485_HOST_ONQ       (PORT2.PODR.BIT.B2 == 0)    /* 対HOST RS485 */
#define IO_OUT_RS485_HOST_ON        PORT2.PODR.BIT.B2 = 0       /* 対HOST RS485 */
#define IO_OUT_RS485_HOST_OFF       PORT2.PODR.BIT.B2 = 1       /* 対HOST RS485 */

#define IO_OUT_RS485_DISPLAY_ONQ    (PORT2.PODR.BIT.B7 == 0)    /* 対Display RS485 */
#define IO_OUT_RS485_DISPLAY_ON     PORT2.PODR.BIT.B7 = 0       /* 対ｾDisplay RS485 */
#define IO_OUT_RS485_DISPLAY_OFF    PORT2.PODR.BIT.B7 = 1       /* 対ｾDisplay RS485 */

#define IO_IN_N_ONQ         (PORTD.PIDR.BIT.B1 == 0)    /* n入力(未実装) */
#define IO_IN_CPT_ONQ       (PORTD.PIDR.BIT.B3 == 0)    /* CPT入力  */
#define IO_IN_RCT_ONQ       (PORTD.PIDR.BIT.B4 == 0)    /* RCT入力 */
#define IO_IN_THF1_ONQ      (PORTE.PIDR.BIT.B6 == 0)    /* THF1入力 */
#define IO_IN_FS_ONQ        (PORTE.PIDR.BIT.B7 == 0)    /* FS入力 (未実装)*/
#define IO_IN_THF2_ONQ      (PORTE.PIDR.BIT.B0 == 0)    /* THF2入力 (未実装)*/
#define IO_IN_YOHI_ONQ      (PORTE.PIDR.BIT.B1 == 0)    /* 予備の無電圧A接点入力 (未実装)*/

#define IO_IN_SW1_ONQ     (PORT5.PIDR.BIT.B5 == 0)    /* SW1 */
#define IO_IN_SW2_ONQ     (PORT5.PIDR.BIT.B4 == 0)    /* SW2 */
#define IO_IN_SW3_ONQ     (PORTC.PIDR.BIT.B7 == 0)    /* SW3 */

#define IO_WDT_ONQ                  (PORT3.PODR.BIT.B1 == 0)    /* 外部WDT */
#define IO_WDT_ON                   PORT3.PODR.BIT.B1 = 0       /* 外部WDT */
#define IO_WDT_OFF                  PORT3.PODR.BIT.B1 = 1       /* 外部WDT */

#endif /* P_MACRO_DEFINE_H_ */
