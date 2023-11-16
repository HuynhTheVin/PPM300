/*
 * p_factory.c
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.H"
#include "p_factory.h"

void fact_out_off(void){  CNT_STAT.out_put.data = 0; }
void fact_out_on(void){  CNT_STAT.out_put.data = 0xFFFF ; }
void fact_out_DH(void){  CNT_STAT.out_put.bitms.out_DH= 1; }
void fact_out_JOSO(void){  CNT_STAT.out_put.bitms.out_JOSO = 1; }
void fact_out_DHH(void){  CNT_STAT.out_put.bitms.out_DHH = 1; }
void fact_out_SV2(void){  CNT_STAT.out_put.bitms.out_SV2 = 1; }
void fact_out_SV3(void){  CNT_STAT.out_put.bitms.out_SV3 = 1; }
void fact_out_SV4(void){  CNT_STAT.out_put.bitms.out_SV4 = 1; }
void fact_out_ARSV(void){  CNT_STAT.out_put.bitms.out_ARSV = 1; }
void fact_out_SPSV(void){  CNT_STAT.out_put.bitms.out_SPSV = 1; }
void fact_out_FAN1(void){  CNT_STAT.out_put.bitms.out_FAN1 = 1; }
void fact_out_FAN2(void){  CNT_STAT.out_put.bitms.out_FAN2 = 1; }
void fact_out_FAN3(void){  CNT_STAT.out_put.bitms.out_FAN3 = 1; }
void fact_out_OVN(void){  CNT_STAT.out_put.bitms.out_OVN = 1; }
void fact_out_TA(void){  CNT_STAT.out_put.bitms.out_TA = 1; }
void fact_out_LA(void){  CNT_STAT.out_put.bitms.out_LA = 1; }
void fact_out_H1(void){  CNT_STAT.out_put.bitms.out_H1 = 1; }
void fact_out_H2(void){  CNT_STAT.out_put.bitms.out_H2 = 1; }
void fact_out_CPC(void){  CNT_STAT.out_put.bitms.out_CPC = 1; }
void fact_out_H3(void){  CNT_STAT.out_put.bitms.out_H3 = 1; }
void fact_out_H4(void){  CNT_STAT.out_put.bitms.out_H4 = 1; }
void fact_out_HG(void){  CNT_STAT.out_put.bitms.out_HG = 1; }
void fact_out_WG(void){  CNT_STAT.out_put.bitms.out_WG = 1; }
void fact_out_yobi(void){  CNT_STAT.out_put.bitms.out_yobi = 1; }
void fact_out_MT1(void){  CNT_STAT.out_put.bitms.out_MT1 = 1; }
void fact_out_MT2(void){  CNT_STAT.out_put.bitms.out_MT2 = 1; }
void fact_out_MT3(void){  CNT_STAT.out_put.bitms.out_MT3 = 1; }
void fact_out_buzz(void){  CNT_STAT.out_put.bitms.out_buzz = 1; }
void fact_in_buzz(void){  CNT_STAT.out_put.bitms.in_buzz = 1; }/* 内部ブザー */ 

const FTBLV fact_out_tbl[] ={
    fact_out_off, 
    fact_out_DHH,
    fact_out_DH,
    fact_out_FAN1, 
    fact_out_FAN2,
    fact_out_FAN3,
    fact_out_TA,
    fact_out_SPSV,
    fact_out_SV2, 
    fact_out_SV3, 
    fact_out_SV4,
    fact_out_CPC,
    fact_out_ARSV,
    fact_out_HG,
    fact_out_MT1,
    fact_out_MT2,
    fact_out_MT3,
    fact_out_LA,
    fact_out_H1,  
    fact_out_H2,
    fact_out_H3,
    fact_out_H4,
    fact_out_OVN,
    fact_out_WG, 
    fact_out_JOSO,
    fact_out_yobi,
    fact_in_buzz/* 内部ブザー */ 
};

void factchk(void){
    union UOUT temp_out;
    temp_out.data = 0;

    if(limit_check(0,sizeof(fact_out_tbl)/4-1,FACT_DATA.out_mode)){
        fact_out_off();
        (*fact_out_tbl[FACT_DATA.out_mode])();
    }else{
        fact_out_off();
    }
    set_self_out();
}