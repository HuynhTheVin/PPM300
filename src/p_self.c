/*
 * p_self.c
 *
 *  Created on: 2023/07/20
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.H"
#include "p_self.h"

void set_self_out(void){
    make_IO_out(0);
}
void auto_self_output(void){
    union UOUT temp_out;
    temp_out.data = 0;
    
    switch (SELF_DATA.self_mode2)
    {
    case 1: temp_out.bitms.out_DH = 1; break;
    case 2: temp_out.bitms.out_JOSO = 1; break;
    case 3: temp_out.bitms.out_DHH = 1; break;
    case 4: temp_out.bitms.out_SV2 = 1; break;
    case 5: temp_out.bitms.out_SV3 = 1; break;
    case 6: temp_out.bitms.out_SV4 = 1; break;
    case 7: temp_out.bitms.out_ARSV = 1; break;
    case 8: temp_out.bitms.out_SPSV = 1; break;
    case 9: temp_out.bitms.out_FAN1 = 1; break;
    case 10: temp_out.bitms.out_FAN2 = 1; break;
    case 11: temp_out.bitms.out_FAN3 = 1; break;
    case 12: temp_out.bitms.out_OVN = 1; break;
    case 13: temp_out.bitms.out_H1 = 1; break;
    case 14: temp_out.bitms.out_H2 = 1; break;
    case 15: temp_out.bitms.out_CPC = 1; break;
    case 16: temp_out.bitms.out_H2 = 1; break;
    case 17: temp_out.bitms.out_H4 = 1; break;
    case 18: temp_out.bitms.out_HG = 1; break;
    case 19: temp_out.bitms.out_WG = 1; break;
    case 20: temp_out.bitms.out_yobi = 1; break;
    case 21: temp_out.bitms.out_MT1 = 1; break;
    case 22: temp_out.bitms.out_MT2 = 1; break;
    case 23: temp_out.bitms.out_MT3 = 1; break;
    case 24: temp_out.bitms.out_buzz = 1; break;
    case 25: temp_out.bitms.in_buzz = 1; break;
    case 26: temp_out.data=  0xffffffff; break;
    default:
        temp_out.data = 0;
        break;
    }
    CNT_STAT.out_put.data = temp_out.data;
}

void self_250ms(void){
    if(KEY_MODE.flg_mode == SELFMD){
        if(SELF_DATA.self_mode1==SELFMD1_AUTO_OUT){
            if(SELF_DATA.self_cnt){
                if(--SELF_DATA.self_cnt==0){
                    SELF_DATA.self_cnt = 4; /* 1秒 */
                    if(++SELF_DATA.self_mode2>SELF_OUT_NUMBER){
                        SELF_DATA.self_mode2 = 0;
                    }
                }
            }
        }
    }
}

/* 出力が順次にONさせる */
void set_self_out_auto(void){
    KEY_MODE.flg_rmode = SELFMD;
    SELF_DATA.self_mode1 = SELFMD1_AUTO_OUT;
    SELF_DATA.self_cnt = 8;
    SELF_DATA.self_mode2 = 0;
    CNT_STAT.out_put.data = 0;
}
/* 出力は通信で設定する */
void set_self_out_set(void){
    KEY_MODE.flg_rmode = SELFMD;
    SELF_DATA.self_mode1 = SELFMD1_SET_BOUT;
    SELF_DATA.self_cnt = 8;
    SELF_DATA.self_mode2 = 0;
    CNT_STAT.out_put.data = 0;
}
const FTBLV self_out_tbl[] ={
    fact_out_off,
    fact_out_on,
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
void selfchk(void){

    union UOUT temp_out;
    temp_out.data = 0;

    if(limit_check(0,sizeof(self_out_tbl)/4-1,FACT_DATA.out_mode)){
        fact_out_off();
        (*fact_out_tbl[FACT_DATA.out_mode])();
    }else{
        fact_out_off();
    }
    set_self_out();

}