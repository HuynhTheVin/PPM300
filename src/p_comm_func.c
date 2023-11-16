/*
 * p_comm_func.c
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_func.h"

void rdyaku(void){ comret_dt(0);}
void rdnone(void){ 
    if(uartp->set_protocol==EPRO_ASCII || uartp->set_protocol==EPRO_RTU){
        if(!uartp->cflg.bitms.enable_internal_cmd){
            uartp->flg_xerr = FSTEP; /* 存在しないデータ項目 */
        }else{
            uartp->flg_xerr = NOTCOMM;
        }
    }else{
        uartp->flg_xerr = NOTCOMM;
    }
}

void rdcomm(void){
    comret_dt(get_data(uartp->phase));
}

void rd_time(void){
//    union TIMEDATA timedt;
//    timedt.data = get_data(uartp->phase);
//    if(get_para(PH_P58)) {   /*調理時間1時間未満の分形式/秒形式を選択する: 秒。*/
//        if(timedt.data ==0){
//            timedt.bitms.tani = 1; /* 秒単位*/
//        }
//        comret_dt(timedt.data);
//    }else{ /*調理時間1時間未満の分形式/秒形式を選択する: 分。*/
//        if(timedt.bitms.tani){ /* 秒*/
//            comret_dt((timedt.bitms.time + 30)/60);
//        }else{
//            comret_dt(timedt.data);
//        }
//
//    }
}

void rd_prs(void){ comret_dt(SOFTPRS);}
void rd_ver(void){ comret_dt(SOFTVER);}
void rd_rom(void){ comret_dt(MPBANGOU0);}
void rd_opuse(void){ comret_dt(IN_AJUST.opuse);}
void rd_settype(void){ comret_dt(IN_AJUST.settype);}
void rd_pv1(void){ comret_dt(INPUT_ADC.rtempdp[CH1]);}
void rd_pv2(void){ comret_dt(INPUT_ADC.rtempdp[CH2]);}
void rd_pv3(void){ comret_dt(INPUT_ADC.rtempdp[CH3]);}
void rd_pv4(void){ comret_dt(INPUT_ADC.rtempdp[CH4]);}
void rd_pv5(void){ comret_dt(INPUT_ADC.rtempdp[CH5]);}
void rd_ttemp1(void){comret_dt(INPUT_ADC.ttemp1);} /* 端子温度1 */
void rd_ttemp2(void){comret_dt(INPUT_ADC.ttemp2);} /* 端子温度2 */
/************************************************/
/* 書き込み */
/************************************************/
void wrnone(void){
    if(uartp->set_protocol==EPRO_ASCII || uartp->set_protocol==EPRO_RTU){
        if(!uartp->cflg.bitms.enable_internal_cmd){
            uartp->flg_xerr = FSTEP; /* 存在しないデータ項目 */
        }else{
            uartp->flg_xerr = NOTCOMM;
        }
    }else{
        uartp->flg_xerr = NOTCOMM;
    }
}
void wryaku(void){ uartp->flg_xerr = NONEACK;}
void wrnak3(void){ uartp->flg_xerr = SOVER;}
void wrnak4(void){ uartp->flg_xerr = ATSTAT;}
void wrnak5(void){ uartp->flg_xerr = SETSTAT;}
void wrcomm(void){
    int16_t data;

    data = cmkdat();
    if(limit_check(get_min(uartp->phase), get_max(uartp->phase),data)){
        set_data(uartp->phase,data);

        wryaku();
    }else{
        wrnak3();
    }
}
void wr_prs(void){
    uint16_t i;
    uint8_t ret;

    i = cmkdat();
    switch (i){
    case 0x5963:
        uartp->cflg.bitms.enable_internal_cmd = 1;
        R_Config_SCI5_Stop();
        R_Config_SCI5_Create();
        start_uart0();
        ret = NONEACK;
        break;
    case 0x3684:
        if(uartp->cflg.bitms.enable_internal_cmd){
            sysClear();
            ret = NONEACK;
        }else{
            ret = SOVER;
        }
        break;
    case 0x3695:  /* P00クリアモード */
        clr_prog();
        ret = NONEACK;
        break;
    // case 0x3696:  /* P00クリアしないモード */
    //     data_clr(CLR_ALL);
    //     ret = NONEACK;
    //     break;
    // case 0x36F0:  /* free fram clear */
    //     if(uartp->uartnumber != EUART5_HOST){
    //         freeFramClr();
    //         ret = NONEACK;
    //     }else{
    //         ret = SOVER;
    //     }
    //     break;
    case 0x1985:
        if((KEY_MODE.flg_rmode == AJUSTMD) && (uartp->cflg.bitms.enable_internal_cmd)){
            adjsave();
            ret = NONEACK;
        }else{
            ret = ATSTAT;
        }
        break;
    default:
        uartp->cflg.bitms.enable_internal_cmd = 0;
        ret = SOVER;
    }
    // case 0x3664:/* エラー履歴 */
    // case 0x3665:/* エラー履歴と保持データ */
    uartp->flg_xerr = ret;
}
