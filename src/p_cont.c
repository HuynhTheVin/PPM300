/*
 * p_cont.c
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.H"
#include "p_cont.h"
/* 運転中 */
BOOL is_untenchu(void){
    return CNT_STAT.con_flg.bitms.untenchu;
}
void make_IO_out(BYTE bzzcnt){
    
    if(CNT_STAT.out_put.bitms.out_DH)   {IO_OUT_DH_ON;  }else{IO_OUT_DH_OFF;}           /* DH出力 */
    if(CNT_STAT.out_put.bitms.out_JOSO)   {IO_OUT_JOSO_ON;  }else{IO_OUT_JOSO_OFF;}     /* 除霜出力 */
    if(CNT_STAT.out_put.bitms.out_DHH) {IO_OUT_DHH_ON;}else{IO_OUT_DHH_OFF;}            /* DHH出力 */
    if(CNT_STAT.out_put.bitms.out_SV2)  {IO_OUT_SV2_ON; }else{IO_OUT_SV2_OFF;}          /* SV2出力 */
    if(CNT_STAT.out_put.bitms.out_SV3)  {IO_OUT_SV3_ON; }else{IO_OUT_SV3_OFF;}          /* SV3出力 */
    if(CNT_STAT.out_put.bitms.out_SV4)    {IO_OUT_SV4_ON;   }else{IO_OUT_SV4_OFF;}      /* SV4出力 */
    if(CNT_STAT.out_put.bitms.out_ARSV)   {IO_OUT_ARSV_ON;  }else{IO_OUT_ARSV_OFF;}     /* ARSV出力 */
    if(CNT_STAT.out_put.bitms.out_SPSV)   {IO_OUT_SPSV_ON;  }else{IO_OUT_SPSV_OFF;}     /* SPSV出力 */
    if(CNT_STAT.out_put.bitms.out_FAN1)  {IO_OUT_FAN1_ON; }else{IO_OUT_FAN1_OFF;}   /* FAN1出力 */
    if(CNT_STAT.out_put.bitms.out_FAN2)   {IO_OUT_FAN2_ON;  }else{IO_OUT_FAN2_OFF;}    /* FAN2出力 */
    if(CNT_STAT.out_put.bitms.out_FAN3)   {IO_OUT_FAN3_ON;  }else{IO_OUT_FAN3_OFF;}     /*FAN3出力 */
    if(CNT_STAT.out_put.bitms.out_OVN)     {IO_OUT_OVN_ON;    }else{IO_OUT_OVN_OFF;}      /* OVN出力 */
    if(CNT_STAT.out_put.bitms.out_TA)     {IO_OUT_TA_ON;    }else{IO_OUT_TA_OFF;}      /* TA出力 */
    if(CNT_STAT.out_put.bitms.out_LA)   {IO_OUT_LA_ON;  }else{IO_OUT_LA_OFF;}    /* LA出力 */
    if(CNT_STAT.out_put.bitms.out_H1)     {IO_OUT_H1_ON;    }else{IO_OUT_H1_OFF;}      /* H1出力 */
    if(CNT_STAT.out_put.bitms.out_H2)   {IO_OUT_H2_ON;  }else{IO_OUT_H2_OFF;}    /* H2出力 */

    if(CNT_STAT.out_put.bitms.out_H3){   IO_OUT_H3_ON;    }else{  IO_OUT_H3_OFF;} /* H3出力  */
    if(CNT_STAT.out_put.bitms.out_H4){   IO_OUT_H4_ON;    }else{  IO_OUT_H4_OFF;}/* H4出力  */
    if(CNT_STAT.out_put.bitms.out_HG){   IO_OUT_HG_ON;    }else{  IO_OUT_HG_OFF;}/* HG出力  */
    if(CNT_STAT.out_put.bitms.out_WG){   IO_OUT_WG_ON;    }else{  IO_OUT_WG_OFF;}  /* WG出力  */
    if(CNT_STAT.out_put.bitms.out_yobi){   IO_OUT_YOBI_ON;    }else{  IO_OUT_YOBI_OFF;}/* 予備出力  */
    if(CNT_STAT.out_put.bitms.out_MT1){   IO_OUT_MT1_ON;    }else{  IO_OUT_MT1_OFF;} /* MT1出力 */
    if(CNT_STAT.out_put.bitms.out_MT2){   IO_OUT_MT2_ON;    }else{  IO_OUT_MT2_OFF;} /* MT2出力 */
    if(CNT_STAT.out_put.bitms.out_MT3){ IO_OUT_MT3_ON;  }else{  IO_OUT_MT3_OFF;}     /* MT3出力 */
    if(CNT_STAT.out_put.bitms.out_CPC){   IO_OUT_CPC_ON;    }else{  IO_OUT_CPC_OFF;} /* CPC出力 */

    if(bzzcnt==0){
         if((CNT_STAT.out_put.bitms.out_buzz) || (CNT_STAT.com_out.bitms.out_buzz)){
            IO_OUT_BUZZER_ON;
         }else{
            IO_OUT_BUZZER_OFF;
        }
    }
}
/**********************
 * Control            *
 **********************/
void control1(void)
{
    int pv, sv, defsv;
    int hys1, hys2;
    WORD ontim, offtim, waittim;
    BYTE d = PH_DATA7;
    /*ｳｫｰﾑｱｯﾌﾟ中とFRAM ERRERと電源投入後A0041秒間は処理しない */
	if((TIMDT.iw) || (CNT_STAT.sys_flg.bitms.e_eeprom) || (TIMDT.ta0083) || (KEY_MODE.flg_mode == SELFMD)){
		return;
	}
    /* 加熱制御 H1*/
    /* 運転以外は加熱温度ヒューズが断線 */    
    if((KEY_MODE.flg_mode >= STANDBYMD)||(CNT_STAT.alarm_flg1.bitms.al_kanetsufuse_break)||(CNT_STAT.cfkanetu_flg.bitms.heating_active == 0)||(CNT_STAT.alarm_flg1.bitms.al_konai_over)){
      	CNT_STAT.out_put.bitms.out_H1 = 0; /* H1出力 off */
		CNT_STAT.cfkanetu_flg.bitms.H1_start_enable = 0;         /* H1,H2出力動作不許可,加熱運転　弱,出力状態 OFF */
		CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong = 0;  
        CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0;  
        TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
		return;
	}
    pv = (int)INPUT_ADC.rtempc[CH1];              /* PV */
	sv = cscalsub2(CONTROL.rundata[0]);    /* SV */

    if(KEY_MODE.flg_mode == UNTENMD){
	/* 急速冷却運転、冷凍・冷蔵運転の場合 */
       if(CNT_STAT.cfjoso_flg.bitms.joso_unten != 1)
       {/* 除霜運転待機中 */
            if(get_data(PH_KANETU) == 0)
            {
            CNT_STAT.out_put.bitms.out_H1 = 0; /* H1出力 off */
            CNT_STAT.cfkanetu_flg.bitms.H1_start_enable = 0;         /* H1,H2出力動作不許可,加熱運転　弱,出力状態 OFF */
            CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong = 0;  
            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0;  
            TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
            }
            else
            {
            hys1 = cscalsub2(SET_PARA.setpara[PH_DATA30]); /* 加熱「強」で加熱出力動作スキマ設定 */
            hys2 = cscalsub2(SET_PARA.setpara[PH_DATA31]); /* 加熱「強」で庫内温度設定に対して加熱出力がONする温度差設定 */
            /* 強/弱運転ﾁｪｯｸ */
            if((sv - hys2 + hys1) <= pv){
                if(CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong){
                    TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
                    CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong = 0; /* 弱運転 */
                    CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0; /* 出力条件 OFF*/
                    
                }
            }
            else{
                if((sv - hys2) >= pv){
                    if(CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong != 1){
                        TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
                        CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong = 1; /* 強運転 */
                        CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0; /* 出力条件 OFF*/
                        
                    }
                }
            }
            hys1 = cscalsub2(SET_PARA.setpara[PH_DATA51]); /* 加熱「弱」で加熱出力動作スキマ設定 */
            hys2 = cscalsub2(SET_PARA.setpara[PH_DATA52]); /* 加熱「弱」で庫内温度設定に対して加熱出力がONする温度差設定 */
            if ((sv - hys2 + hys1) <= pv)
            {
                if( CNT_STAT.cfkanetu_flg.bitms.H1_start_enable)
                    {
                        CNT_STAT.cfkanetu_flg.bitms.H1_start_enable = 0;/* H1,H2出力動作不許可*/ 
                        /* 加熱2終了時のFAN1遅延時間 */
                        TIMDT.fan1ontim = SET_PARA.setpara[PH_DATA55];
                        CNT_STAT.cffan_flg.bitms.fan1_waittime_off = 1; /* FAN1遅延時間　ON */
                    }
            }
            else 
            {
                if((sv - hys2) >= pv){
                    if( CNT_STAT.cfkanetu_flg.bitms.H1_start_enable != 1)
                    {
                        CNT_STAT.cfkanetu_flg.bitms.H1_start_enable = 1;/* H1,H2出力動作不許可 */ 
                        TIMDT.cunton_off[fan1] = 1; /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */ 
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1状態　OFF*/     
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1状態　OFF*/          
                    }
                }
            }
            /* 加熱信号がOFFからONとなり加熱開始する場合、H1は0.5秒間待ってから同じする　*/
            if(CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong == 0)
            {
                if( CNT_STAT.cfkanetu_flg.bitms.H1_start_enable == 0)
                {
                    waittim = 10; /* 弱運転に移行すると、待ち時間　0.5秒＝50ms*waittim */                  
                }
            }
            /* 強/弱運転でOFF時間をｾｯﾄ*/
            if(CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong)
            {
                ontim = SET_PARA.setpara[PH_DATA4] * 20;  /* 強 A0004 50ms*ontim = ON時間 */
                offtim = SET_PARA.setpara[PH_DATA5] * 20; /* 強 A0005 50ms*offtim = OFF時間 */
            }
            else
            {
                ontim = SET_PARA.setpara[PH_DATA17] * 20;  /* 弱 A0017 50ms*ontim = ON時間 */
                offtim = SET_PARA.setpara[PH_DATA18] * 20; /* 弱 A0018 50ms*offtim=OFF時間 */
                
            }   
            }                   
       }
    }
    if(CNT_STAT.cfkanetu_flg.bitms.heating_active)
    {
        if(CNT_STAT.cfkanetu_flg.bitms.H1_start_enable)
        {
            if(TIMDT.cunton_off[heatch])
            {
                if(--TIMDT.cunton_off[heatch] == 0)
                {
                    if(CNT_STAT.cfkanetu_flg.bitms.H1_out_status)
                    {	                      
                        /* 出力ONだったら */
                        if(offtim)
                        {/* OFF時間が0設定の場合常時ON　20040701 V1.10*/
                            TIMDT.cunton_off[heatch] = offtim;
                            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0;
                            CNT_STAT.out_put.bitms.out_H1 = 0; /* H1出力 off */
                        }
                        else
                        {
                            /* 強/弱運転でON時間をｾｯﾄ */
                            TIMDT.cunton_off[heatch] = ontim;
                            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 1; /* 出力条件 ON*/
                            CNT_STAT.out_put.bitms.out_H1 = 1; /* H1出力 ON */
                        }                    
                    }
                    else
                    {	
                        if(waittim)
                        {
                            TIMDT.cunton_off[heatch] = waittim;
                            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0;
                            CNT_STAT.out_put.bitms.out_H1 = 0; /* H1出力 off */
                            waittim = 0;
                        }
                        else
                        {			/* 出力OFFだったら */
                            /* 強/弱運転でON時間をｾｯﾄ */
                            TIMDT.cunton_off[heatch] = ontim;
                            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 1; /* 出力条件 ON*/
                            CNT_STAT.out_put.bitms.out_H1 = 1; /* H1出力 ON */
                        }
                    }
                }
                else
                {
                    TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰが0にならないように異常時の対策 */
                }
            }
        }
        else
        {
            CNT_STAT.cfkanetu_flg.bitms.H1_out_status = 0;
            CNT_STAT.out_put.bitms.out_H1 = 0; /* H1出力 off */
        }
    }

    if(KEY_MODE.flg_mode == UNTENMD)/* 冷凍、冷凍冷蔵モード 除霜運転 */
    {
        if((CNT_STAT.cfjoso_flg.bitms.shudou_joso_start != 1))
        {/* 手動除霜動作以外 */
            
            switch (SET_PARA.josouhoushiki)
            {
            case 0:/* 除霜ｻｲｸﾙ時間ｶｳﾝﾄｸﾘｱ処理*/
                josoCYCL(sv,pv,d);
                break;
            default:/* 除霜方式 t-ON 処理*/
                josotON(pv,d);
                break;
            }   
        }
        else if(CNT_STAT.cfjoso_flg.bitms.shudou_joso_start)
        {/* 手動除霜動作中 */
            if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
            {
                CNT_STAT.out_put.bitms.out_H1 = 1; /* H1 出力 ON */
                if(CNT_STAT.alarm_flg1.bitms.al_gaibu1_over != 1)/* 外部温度異常 */
                {
                    CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
                }
                TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
            }
        }
    }
    /* 除霜中ヒータのOFF条件 */
	/*ヒータOFF条件1  開始時の庫内温度差*/
	if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
    {/* 除霜中  */
        if(SET_PARA.setpara[PH_DATA200] != 1)
        {/* 庫内温度　外部温度センサ無効の場合 */ 
            pv = (int)INPUT_ADC.rtempc[CH1];              /* PV　庫内温度 */
            defsv = CONTROL.defrostpv + cscalsub2(SET_PARA.setpara[PH_DATA41]);    /* SV A0041 小数点なしないなら10倍する */
            hys1 = cscalsub2(SET_PARA.setpara[PH_DATA42]);  /* HYS A0042 小数点なしないなら10倍する*/
            if((pv>=defsv)&&(CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)){/* 除霜中で庫内センサ断線なしなら   */
                CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
                CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1 = 1; /* 条件1でOFFした */
            }else{
                if((pv >(defsv - hys1)) && (CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1)){
                    CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
                }else{
                    CNT_STAT.out_put.bitms.out_H1 = 1; /* H1 出力  ON */
                    CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1 = 0; /* 条件1待機 */
                }
            }
        }
        else 
        {/* 外部入力温度　外部温度センサ有効の場合 */
            if(CNT_STAT.alarm_flg1.bitms.al_gaibu1_over != 1)
            {
                pv = (int)INPUT_ADC.rtempc[CH2];              /* PV 外部温度*/
                defsv = cscalsub2(SET_PARA.setpara[PH_DATA58]) * 10;    /* SV A0041 小数点なしないなら10倍する */
                hys1 = cscalsub2(SET_PARA.setpara[PH_DATA59]);  /* HYS A0042 小数点なしないなら10倍する*/
                if((pv>=defsv)&&(CNT_STAT.alarm_flg1.bitms.al_gaibu1_over != 1)){/* 除霜中で外部センサ断線なしなら   */
                    CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
                    CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1 = 1; /* 条件1でOFFした */
                }else{
                    if((pv >(defsv - hys1)) && (CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1)){
                        CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
                    }else{
                        CNT_STAT.out_put.bitms.out_H1 = 1; /* H1 出力  ON */
                        CNT_STAT.cfjoso_flg.bitms.H1_OFF_condition1 = 0; /* 条件1待機 */
                    }
                }
            }
        }
    }
    if(CNT_STAT.cfkanetu_flg.bitms.H1_start_enable != 1){
		TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
		CNT_STAT.out_put.bitms.out_H1 = 0; /* H1 出力 OFF */
	}
}
/**********************
 * Control2            
 * 除霜開始時刻処理 (t‐ON)
 **********************/
bool checkRealTime(int hour, int minute)
{
    int realtimeMin;
    for (int i = 0; i < 10; i++) {
        realtimeMin = hour*60 + minute + SET_PARA.setpara[PH_DATA24]; /* 時刻から分を取得します　*/
        if (realtimeMin == SET_PARA.josoustarttime[i]) {

            return true;    // 実際の時間と配列内の値が一致する場合はtrueを返します
        }
    }
    return false;   // 配列内の値と一致するものが見つからない場合はfalseを返します
}
/********************
 * Control除霜　CYCL
 ********************/
void josoCYCL(int sv, int pv, BYTE d)
{
    int hys1;
    if(CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)/* 点検A発生しない場合 */
    {
        if(CNT_STAT.cfjoso_flg.bitms.joso_unten != 1)
        {
            hys1 = cscalsub2(SET_PARA.setpara[PH_DATA10]); /* A0010 除霜不可の温度差（現在温度に対しての温度差）設定  */
            if(sv + hys1 <= pv)
            {
                CNT_STAT.cfjoso_flg.bitms.joso_cycle_clear_counter = 1;  /* 除霜ｻｲｸﾙ時間ｸﾘｱﾀｲﾏｰ減算 */
            }
            else
            {
                CNT_STAT.cfjoso_flg.bitms.joso_cycle_clear_counter = 0; /* 除霜ｻｲｸﾙ時間ｸﾘｱﾀｲﾏｰ減算停止  */
                TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60;  /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
            }
        }
        else
        {
            TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
        }
    }
    else/* 点検A発生中除霜ヒータOFF断条件2キャンセルする場合 */
    {
        CNT_STAT.cfjoso_flg.bitms.joso_cycle_clear_counter = 0; /* 除霜ｻｲｸﾙ時間ｸﾘｱﾀｲﾏｰ減算停止  */
        TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60;  /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
    }                   
    if(TIMDT.defrosttim == 0)
    {   
        if(SET_PARA.setpara[PH_DATA200] != 1)/* 外部センサ入力　無効の場合 */
        {
            /*庫内温度によって除霜時間を変更 */
            if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA68]))
            { /* 庫内温度がA0068以上 */
                d = PH_DATA7;
            }
            else
            {
                if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA69]))
                { /* 庫内温度がA0068未満でA0069以上 */
                    d = PH_DATA61;
                }
                else
                {
                    if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA69]))
                    { /* 庫内温度がA0069未満でA0070以上 */
                        d = PH_DATA8;
                    }
                    else
                    { /* 庫内温度がA0070未満 */
                        d = PH_DATA9;
                    }
                }
            }
        }
        else
        {/* 外部センサ入力　有効の場合 */
            d = PH_DATA88;
        }
        //manudeftim = nsetpara[d];      /* A0013 or A0014 or A0015 or A0016 通信用*/
        TIMDT.t60s = INTCLK1M;                       /* 1分ﾀｲﾏｰ初期化*/
        if(CNT_STAT.cfjoso_flg.bitms.joso_unten != 1)
        {              /* 除霜運転開始 */
            CONTROL.defrostpv = pv;     /* 除霜開始時の庫内温度保存*/
            CNT_STAT.cfjoso_flg.bitms.joso_unten = 1;                     /* 除霜運転中   */
            TIMDT.defrosttim = SET_PARA.setpara[d];      /* A0007 or A0061 or A0008 or A0009 */	
        }
        else
        {
            TIMDT.defrosttim = SET_PARA.setpara[PH_DATA6] - SET_PARA.setpara[d];      /* A0006 - A0007 or A0061 or A0008 or A0009 */	
            if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
            {     /* 除霜中なら   */
                CNT_STAT.cfjoso_flg.bitms.joso_unten = 0;        /* 除霜待機     */
                if(SET_PARA.setpara[PH_DATA40])
                { /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 0;/* SV2初期動作未実行にする  */
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;/* SV2初期動作未実行にする  */                   
                }
                else
                {
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1;/* SV2ｻｲｸﾙなし             */
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;/* SV2初期動作未実行にする */
                }
            }
        }
    }
    if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
    {
        CNT_STAT.out_put.bitms.out_H1 = 1; /* H1 出力 ON */
        TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60;  /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
    }
}
/********************
 * Control除霜　t‐ON　　　　*
 ********************/
void josotON(int pv,BYTE d)
{
    if(CNT_STAT.out_put.bitms.out_DHH != 1)/* DHHがOFFの場合 */
    {
        if(checkRealTime(SET_TIME.sethour, SET_TIME.setmin))/* 除霜開始時刻チェック */
        {            
            CNT_STAT.cfjoso_flg.bitms.joso_realtime_clear = 1; /* 除霜開始時刻 */         
            TIMDT.deftONtim = SET_PARA.setpara[PH_DATA24]; /* 0024 */
            CNT_STAT.out_put.bitms.out_DHH = 1; /* DHH出力 ON */
        }
        else
        {
            CNT_STAT.cfjoso_flg.bitms.joso_realtime_clear = 0; /* 除霜開始時刻 */ 
        }
        
    }
    else/* DHH出力がONの場合 */
    {
        TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
    }
    if(CNT_STAT.cfjoso_flg.bitms.joso_realtime_clear)
    {
        if(TIMDT.deftONtim == 0)
        {   
            if(SET_PARA.setpara[PH_DATA200] != 1)/* 外部センサ入力　無効の場合 */
            {
                /*庫内温度によって除霜時間を変更 */
                if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA68]))
                { /* 庫内温度がA0068以上 */
                    d = PH_DATA7;
                }
                else
                {
                    if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA69]))
                    { /* 庫内温度がA0068未満でA0069以上 */
                        d = PH_DATA61;
                    }
                    else
                    {
                        if(pv >= cscalsub2(SET_PARA.setpara[PH_DATA69]))
                        { /* 庫内温度がA0069未満でA0070以上 */
                            d = PH_DATA8;
                        }
                        else
                        { /* 庫内温度がA0070未満 */
                            d = PH_DATA9;
                        }
                    }
                }
            }
            else
            {/* 外部センサ入力　有効の場合 */
                d = PH_DATA88;
            }
            //manudeftim = nsetpara[d];      /* A0013 or A0014 or A0015 or A0016 通信用*/
            TIMDT.t60s = INTCLK1M;                       /* 1分ﾀｲﾏｰ初期化*/
            if(CNT_STAT.cfjoso_flg.bitms.joso_unten != 1)
            {              /* 除霜運転開始 */
                CONTROL.defrostpv = pv;     /* 除霜開始時の庫内温度保存*/
                CNT_STAT.cfjoso_flg.bitms.joso_unten = 1;                     /* 除霜運転中   */
                TIMDT.deftONtim = SET_PARA.setpara[d];      /* A0007 or A0061 or A0008 or A0009 */	
            }
            else
            {
                if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
                {     /* 除霜中なら   */
                    CNT_STAT.cfjoso_flg.bitms.joso_unten = 0;        /* 除霜待機     */
                    if(SET_PARA.setpara[PH_DATA40])
                    { /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 0;/* SV2初期動作未実行にする  */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;/* SV2初期動作未実行にする  */                   
                    }
                    else
                    {
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1;/* SV2ｻｲｸﾙなし             */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;/* SV2初期動作未実行にする */
                    }
                }
            }
        }
    }
    if(CNT_STAT.cfjoso_flg.bitms.joso_unten)
    {
        CNT_STAT.out_put.bitms.out_H1 = 1; /* H1 出力 ON */
    }
}
void set_output(void)
{
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        break;
    default:
        fact_out_off(); /* OUT OFF */
        break;
    }
    /* Set to IO port */   
    make_IO_out(1);/* ブザー以外 */
}
void turnof_all_output(void){ /* 全て出力をOFFする */
     CNT_STAT.out_put.data = 0;;
     make_IO_out(0);/* ブザー含む */
}