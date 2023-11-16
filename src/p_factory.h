/*
 * p_factory.h
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */

#ifndef P_FACTORY_H_
#define P_FACTORY_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void factchk(void);
void fact_out_off(void);
void fact_out_on(void);
void fact_out_DHH(void);
void fact_out_DH(void);
void fact_out_FAN1(void);
void fact_out_FAN2(void);
void fact_out_FAN3(void);
void fact_out_TA(void);
void fact_out_SPSV(void);
void fact_out_SV2(void);
void fact_out_SV3(void);
void fact_out_SV4(void);
void fact_out_CPC(void);
void fact_out_ARSV(void);
void fact_out_HG(void);
void fact_out_MT1(void);
void fact_out_MT2(void);
void fact_out_MT3(void);
void fact_out_LA(void);
void fact_out_H1(void);
void fact_out_H2(void);
void fact_out_H3(void);
void fact_out_H4(void);
void fact_out_OVN(void);
void fact_out_WG(void);
void fact_out_JOSO(void);
void fact_out_yobi(void);
void fact_in_buzz(void);
struct FACT_TYPE
{
    uint16_t  sub_flg;  /* サブフラグ */
    uint16_t  out_mode; /* 出力モード */
    uint16_t  clr_mode; /* クリアモード */
    BOOL      clr_cmd;  /* クリアコマンド */
};

#endif /* P_FACTORY_H_ */
