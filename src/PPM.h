/*
 * PPM.h
 *
 *  Created on: 2023/06/09
 *      Author: VINH-NT
 */

#ifndef PPM_H_
#define PPM_H_

#include "p_mainh.h"
//#include "PPM300.h"

/****************************************************
    Software Ver.
 ****************************************************/
#define SOFTPRS 2023          // Number of program management
#define SOFTVER 0x0001        // High 8bit:Ver. / Low8bit:Rev. 0.01
#define SOFT_USER_VER SOFTVER // High 8bit:Ver. / Low8bit:Rev. 0.04

#define MPBANGOU0 1234 // MP1234
#define MPBANGOU1 0    // MP1234-0

#define DBANGOU1 20 // 20-008
#define DBANGOU2 8
#define DBANGOU3 0

EXTERN struct AJUST_TYPE IN_AJUST;
EXTERN struct SET_DATA_TYPE SET_PARA;
EXTERN struct CON_STATUS_TYPE CNT_STAT;
EXTERN struct INPUT_TYPE INPUT_ADC;
EXTERN struct KEY_TYPE KEY_MODE;
EXTERN struct UART_WORK COMM0;
EXTERN struct UART_WORK COMM1;
EXTERN struct UART_WORK COMM5;
EXTERN struct UART_WORK COMM12;
EXTERN struct UART_WORK *uartp;
EXTERN struct TIME_TYPE TIMDT;
EXTERN struct SET_RTCTIME SET_TIME;
EXTERN struct CONTROL_TYPE CONTROL;
EXTERN struct RUN_DATA_TYPE RUN_DATA;
EXTERN struct FACT_TYPE FACT_DATA;
EXTERN struct SELF_TYPE SELF_DATA;
/* Other works */
EXTERN WORD wdtcou1; /* WDT counter_1 Main  */
EXTERN WORD wdtadc;  /* WDT counter_ADC     */
EXTERN WORD dummy;   /* 未使用データ参照用 */
/* 自己デバッグ用データワーク */
EXTERN struct LOG_TYPE
{
    union LOG_FLAG
    {
        WORD data;
        struct
        {
            BYTE data_tbl_pointer_exception : 1; /* pointer acess exception  */
            BYTE data_tbl_phase_exception : 1;   /* data */
        } bitms;
    } data_ex;
    WORD exception_phase;
} log_data;
#endif /* PPM_H_ */
