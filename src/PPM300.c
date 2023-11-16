/***********************************************************************
 *
 *  FILE        : PPM300.c
 *  DATE        : 2023-05-26
 *  DESCRIPTION : Main Program
 *
 *  NOTE:THIS IS A TYPICAL EXAMPLE.
 *
 ***********************************************************************/
#define EXTERN extern
#include "r_smc_entry.h"
#include "PPM.h"
#include "PPM300.h"
#include "p_prototype.h"

void main(void);
void iniram(void);
void nextmodeclr(BYTE mode);
void contrefresh(BYTE d);
void nextmodeclr(BYTE mode)
{
    KEY_MODE.flg_mode = mode;
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        put_fram2(NEMODE, UNTENMD);
        break;
    default:
        put_fram2(NEMODE, STANDBYMD);
        break;
    }
}
/* Check lock mode */
BYTE lockchk1(void)
{
    if (KEY_MODE.flg_mode == STANDBYMD)
    {
        TIMDT.bztm = 2;  /* キー入力ブザー音 0.1秒 */
        TIMDT.bzcnt = 4; /* ブザー音”ピッピッ”   */
        return NG;
    }
    return OK;
}
/*******************************
  異常発生時の点検履歴保存処理
********************************/
void checksave(int t)
{
    BYTE d;
    WORD ad, ad1;
    int *p, *p_1;
    int j;
    WORD d1;
    /* 点検番号 */
    p = &SET_PARA.nerrcode01[18];   /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    p_1 = &SET_PARA.nerrcode01[19]; /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    ad = NECHECKD20NO;              /* FRAM ｱﾄﾞﾚｽｾｯ     */
    /* 一番古い履歴を破棄して並べ替える*/
    for (d = 19; 0 < d; d--)
    {
        *p_1 = *p;
        put_fram2(ad, *p); /* to fram2 save */
        *p--;
        *p_1--;
        ad--;
    }
    /* 西暦 */
    p = &SET_PARA.nerrcode02[18];   /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    p_1 = &SET_PARA.nerrcode02[19]; /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    ad = NECHECKD20AD;              /* FRAM ｱﾄﾞﾚｽｾｯ     */
    /* 一番古い履歴を破棄して並べ替える*/
    for (d = 19; 0 < d; d--)
    {
        *p_1 = *p;
        put_fram2(ad, *p); /* to fram2 save */
        *p--;
        *p_1--;
        ad--;
    }
    /* 月日 */
    p = &SET_PARA.nerrcode03[18];   /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    p_1 = &SET_PARA.nerrcode03[19]; /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    ad = NECHECKD20MONTHDAY;        /* FRAM ｱﾄﾞﾚｽｾｯ     */
    /* 一番古い履歴を破棄して並べ替える*/
    for (d = 19; 0 < d; d--)
    {
        *p_1 = *p;
        put_fram2(ad, *p); /* to fram2 save */
        *p--;
        *p_1--;
        ad--;
    }
    /* 時刻 */
    p = &SET_PARA.nerrcode04[18];   /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    p_1 = &SET_PARA.nerrcode04[19]; /* 内部RAM ｱﾄﾞﾚｽｾｯﾄ */
    ad = NECHECKD20MINUTE;          /* FRAM ｱﾄﾞﾚｽｾｯ     */
    /* 一番古い履歴を破棄して並べ替える*/
    for (d = 19; 0 < d; d--)
    {
        *p_1 = *p;
        put_fram2(ad, *p); /* to fram2 save */
        *p--;
        *p_1--;
        ad--;
    }
    /* 発生した異常の保存 */
    /* 点検番号 */
    SET_PARA.nerrcode01[0] = t; /* 点検番号書き込み */
    put_fram2(NECHECKD01NO, t); /* to fram2 save */
    /* 西暦 */
    j = 2000 + SET_TIME.setyear;
    SET_PARA.nerrcode02[0] = j;
    put_fram2(NECHECKD01AD, j); /* to fram2 save */
    /* 月日 */
    j = 256 * SET_TIME.setmonth + SET_TIME.setday;
    SET_PARA.nerrcode03[0] = j;
    put_fram2(NECHECKD01MONTHDAY, j); /* to fram2 save */
    /* 時刻 */
    j = 256 * SET_TIME.sethour + SET_TIME.setmin;
    SET_PARA.nerrcode04[0] = j;
    put_fram2(NECHECKD01MINUTE, j); /* to fram2 save */
}
uint8_t start_unten(void)
{
    return K_RES_OK;
}
uint8_t start_reitou_unten(void)
{
    int i;
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        /* code */
        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2初期動作ﾃﾞｰﾀ要求ﾌﾗｸﾞ */
        contrefresh(KEY_MODE.flg_rmode);                              /* 制御動作初期化 */
        CNT_STAT.cfjoso_flg.data = 0x00;                              /* 除霜運転待機,ｻｲｸﾙﾀｲﾏｰ減算停止*/
        CNT_STAT.cffan_flg.data = 0x00;                               /* ファンフラグクリア*/
        TIMDT.defshudotim = 0;                                        /* A0014 サイクル時間　無し */
        TIMDT.deftONtim = 0;                                          /* A0024 t-ON　無し */
        TIMDT.dhhontime = 0;
        TIMDT.fan1ontim = 0;
        TIMDT.t60s = INTCLK1M;
        break;
    case STANDBYMD:
        CNT_STAT.cfjoso_flg.data = 0x00; /* 除霜運転待機,ｻｲｸﾙﾀｲﾏｰ減算停止*/
        CNT_STAT.cffan_flg.data = 0x00;  /* ファンフラグクリア*/
        TIMDT.defshudotim = 0;           /* A0014 サイクル時間　無し */
        TIMDT.deftONtim = 0;             /* A0024 t-ON　無し */
        TIMDT.dhhontime = 0;
        TIMDT.fan1ontim = 0;
        break;
    default:

        break;
    }
    return K_RES_OK;
}
uint8_t start_reitouzou_unten(void)
{

    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        /* code */
        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2初期動作ﾃﾞｰﾀ要求ﾌﾗｸﾞ */
        contrefresh(KEY_MODE.flg_rmode);                              /* 制御動作初期化 */
        CNT_STAT.cfjoso_flg.data = 0x00;                              /* 除霜運転待機,ｻｲｸﾙﾀｲﾏｰ減算停止*/
        CNT_STAT.cffan_flg.data = 0x00;                               /* ファンフラグクリア*/
        TIMDT.defshudotim = 0;                                        /* A0014 サイクル時間　無し */
        TIMDT.deftONtim = 0;                                          /* A0024 t-ON　無し */
        TIMDT.dhhontime = 0;
        TIMDT.fan1ontim = 0;
        TIMDT.t60s = INTCLK1M;
        break;
    case STANDBYMD:
        CNT_STAT.cfjoso_flg.data = 0x00; /* 除霜運転待機,ｻｲｸﾙﾀｲﾏｰ減算停止*/
        CNT_STAT.cffan_flg.data = 0x00;  /* ファンフラグクリア*/
        TIMDT.defshudotim = 0;           /* A0014 サイクル時間　無し */
        TIMDT.deftONtim = 0;             /* A0024 t-ON　無し */
        TIMDT.dhhontime = 0;
        TIMDT.fan1ontim = 0;
        break;
    default:
        break;
    }
    return K_RES_OK;
}
/*********************
    表示データ更新
**********************/
void datarefresh(void)
{

    if (KEY_MODE.flg_mode == UNTENMD)
    {
        switch (KEY_MODE.flg_rmode)
        {
        case REITOMD:
            CONTROL.rundata[0] = get_data(PH_MEM1REITOU);
            break;
        default:
            CONTROL.rundata[0] = get_data(PH_MEM1REITOUZOU);
            break;
        }
        switch (get_data((PH_KANETU)))
        {
        case 0x0000:
            CNT_STAT.cfkanetu_flg.bitms.heating_active = 0;
            break;
        default:
            CNT_STAT.cfkanetu_flg.bitms.heating_active = 1;
            break;
        }
    }
}
/***************
 * Control 更新
 **************/
void contrefresh(BYTE d)
{
    BYTE i;
    i = d;
    switch (i)
    {
    case REITOMD:
    case REITOZOUMD:
        TIMDT.t60s = INTCLK1M;                               /* 1分ﾀｲﾏｰ初期化*/
        TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60; /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
        TIMDT.defrosttim = SET_PARA.setpara[PH_DATA6];       /* A0006 */
        /* 冷却運転の初期化 */
        if (CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off != 1)
        { /* M1(CPC)出力強制OFFなら時間更新しない　20111024 */
            if ((TIMDT.m1waittim != 0) && (TIMDT.m1waittim > (SET_PARA.setpara[PH_DATA84] * 60)))
            {
                TIMDT.m1waittim = SET_PARA.setpara[PH_DATA84] * 60; /* M1出力がOFF後OFF継続する時間ｾｯﾄ A0084*/
            }
        }
        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2初期動作ﾃﾞｰﾀ要求 */
        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 0;             /* SV2初期動作 未実行 */
        break;
    default:
        break;
    }
    // return i;
}
/**************************************************************
 250msec Routine
 **************************************************************/
void nowset(void)
{
    if (CNT_STAT.cf2_flg.bitms.current_time_capture_flag == 1)
    {
        CNT_STAT.cf2_flg.bitms.current_time_capture_flag = 0; /* 現在時刻取り込みフラグクリア */
                                                              /* 通常倍速 */
        rd_rtc();                                             /* 現在時刻取り込み厳しい*/
    }
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        set_data(PH_MODE, UNTENMD); /* put fram2/sram to save  */
        switch (KEY_MODE.flg_rmode)
        {
        case REITOMD:
            set_data(PH_RUNMD, REITOMD); /* put fram2/sram to save  */
            break;
        default:
            set_data(PH_RUNMD, REITOZOUMD); /* put fram2/sram to save  */
            break;
        }
        break;
    case SELFMD:
        CONTROL.self_md = 1; /*自己診断状態 1:ON */
        set_data(PH_MODE, STANDBYMD); /* put fram2/sram to save  */
        break;
    default:
        if(CONTROL.self_md)
        {
            FACT_DATA.out_mode = 0;
            /* チェックモードから戻った場合、全て出力をOFFしておく */
            turnof_all_output();
        }
        CONTROL.self_md = 0; /*自己診断状態 1:OFF */
        set_data(PH_MODE, STANDBYMD); /* put fram2/sram to save  */
        break;
    }
}
void chkover(void)
{
    int pv, sv;
    if (TIMDT.iw)
    {
        return;
    }
    /*庫内温度*/
    pv = (int)INPUT_ADC.rtempc[CH1]; /* PV */
    sv = cscalsub2(1100);            /* SV= 110℃ */
    if ((sv <= pv) || (INPUT_ADC.sensin[CH1] > (INPUT_ADC.ref_s1 + INPUT_ADC.ref_s1 / 4)) || (INPUT_ADC.sensinb[CH1] > INPUT_ADC.ref_s1))
    {
        if (CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)
        {
            TIMDT.cunton_off[CPC] = 1;                            /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
            CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 0; /* 冷却条件成立(冷却信号OFF) */
        }
        if (CONTROL.input_over_flg[CH1].bitms.up_scal_err != 1)
        {
            CNT_STAT.alarm_flg1.bitms.al_konai_over = 1;       /* 庫内温度ｾﾝｻ断線 */
            CONTROL.input_over_flg[CH1].bitms.up_scal_err = 1; /* Up scal err  センサ断線 */
            checksave(10);                                     /* 庫内温度ｾﾝｻ断線 */
        }
    }
    else
    {
        if (CONTROL.input_over_flg[CH1].bitms.up_scal_err)
        {
            CONTROL.input_over_flg[CH1].bitms.up_scal_err = 0; /* Up scal OK    */
        }
    }
    sv = cscalsub2(-700); /* SV */
    if ((sv > pv) || (INPUT_ADC.sensin[CH1] == 0))
    {
        if (CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)
        {
            TIMDT.cunton_off[CPC] = 1;                            /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
            CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 0; /* 冷却条件成立(冷却信号OFF) */
        }
        if (CONTROL.input_over_flg[CH1].bitms.down_scal_err != 1)
        {
            CNT_STAT.alarm_flg1.bitms.al_konai_over = 1;         /* 庫内温度ｾﾝｻ断線 */
            CONTROL.input_over_flg[CH1].bitms.down_scal_err = 1; /* Down scal err         */
            checksave(10);                                       /* 庫内温度ｾﾝｻ断線 */
        }
    }
    else
    {
        if (CONTROL.input_over_flg[CH1].bitms.down_scal_err)
        {
            CONTROL.input_over_flg[CH1].bitms.down_scal_err = 0; /* Down scal OK  */
        }
    }
    /*外部Pt温度1*/
    pv = (int)INPUT_ADC.rtempc[CH3]; /* PV */
    sv = cscalsub2(1100);            // cscalsub3(SET_PARA.setpara[PH_DATA209] + 100); /* SV */
    if (SET_PARA.setpara[PH_DATA200] != 1)
    {
        if ((sv <= pv) || (INPUT_ADC.sensin[CH3] > (INPUT_ADC.ref_s1 + INPUT_ADC.ref_s1 / 4)) || (INPUT_ADC.sensinb[CH3] > INPUT_ADC.ref_s1))
        {
            CNT_STAT.alarm_flg1.bitms.al_gaibu1_over = 1; /* 外部温度ｾﾝｻ断線 */
            if (CONTROL.input_over_flg[CH3].bitms.up_scal_err != 1)
            {
                CONTROL.input_over_flg[CH3].bitms.up_scal_err = 1; /* Up scal err  センサ断線 */
                checksave(13);                                     /* 外部Ptｾﾝｻ断線 */
            }
        }
        else
        {
            if (CONTROL.input_over_flg[CH3].bitms.up_scal_err)
            {
                CONTROL.input_over_flg[CH3].bitms.up_scal_err = 0; /* Up scal OK    */
            }
        }

        sv = cscalsub2(-700); // cscalsub3(SET_PARA.setpara[PH_DATA208] - 200); /* SV */
        if ((sv > pv) || (INPUT_ADC.sensin[CH3] == 0))
        {
            if (CONTROL.input_over_flg[CH3].bitms.down_scal_err != 1)
            {
                CNT_STAT.alarm_flg1.bitms.al_gaibu1_over = 1;        /* 外部温度ｾﾝｻ断線 */
                CONTROL.input_over_flg[CH3].bitms.down_scal_err = 1; /* Down scal err         */
                checksave(13);                                       /* 外部温度ｾﾝｻ断線 */
            }
        }
        else
        {
            if (CONTROL.input_over_flg[CH3].bitms.down_scal_err)
            {
                CONTROL.input_over_flg[CH3].bitms.down_scal_err = 0; /* Down scal OK  */
            }
        }
    }
}
void iventchk(void)
{
    int j;
    /* 冷却不良 */
    if ((CNT_STAT.alarm_flg2.bitms.al_poor_cool != 1) && (CNT_STAT.tenken_flg.bitms.reikyaku_furyou))
    {
        CNT_STAT.alarm_flg2.bitms.al_poor_cool = 1; /* 冷却不良 */
        checksave(3);                               /* 冷却不良 */
    }
    /* 停電告知 */
    if ((CNT_STAT.alarm_flg1.bitms.al_power_outages != 1) && (CNT_STAT.tenken_flg.bitms.power_outages))
    {
        CNT_STAT.alarm_flg1.bitms.al_power_outages = 1; /* 停電告知 */
        CNT_STAT.tenken_flg.bitms.power_outages = 0;    /* 停電告知状態正常  */
        checksave(9);                                   /* 停電告知 */
    }
    /* 不揮発性メモリ異常 */
    if ((CNT_STAT.alarm_flg2.bitms.al_eeprom != 1) && (CNT_STAT.sys_flg.bitms.e_eeprom))
    {
        CNT_STAT.alarm_flg2.bitms.al_eeprom = 1;
        checksave(14); /* 点検E 不揮発性メモリ異常*/
    }
    /************************
     * 出力累積ON回数処理
     *************************/
    /*DHH*/
    if ((CNT_STAT.out_put_previous.bitms.out_DHH == 0) && (CNT_STAT.out_put.bitms.out_DHH))
    { /* ONになったら */
        SET_PARA.rycnt[0]++;
        j = (int)((SET_PARA.rycnt[0] / 15) & 0xFFFF);
        put_fram2(NERYCNT1L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[0] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT1H, j); /* 上位保存 */
    }
    /*DH*/
    if ((CNT_STAT.out_put_previous.bitms.out_DH == 0) && (CNT_STAT.out_put.bitms.out_DH))
    { /* ONになったら */
        SET_PARA.rycnt[1]++;
        j = (int)((SET_PARA.rycnt[1] / 15) & 0xFFFF);
        put_fram2(NERYCNT2L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[1] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT2H, j); /* 上位保存 */
    }
    /*FAN1*/
    if ((CNT_STAT.out_put_previous.bitms.out_FAN1 == 0) && (CNT_STAT.out_put.bitms.out_FAN1))
    { /* ONになったら */
        SET_PARA.rycnt[2]++;
        j = (int)((SET_PARA.rycnt[2] / 15) & 0xFFFF);
        put_fram2(NERYCNT3L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[2] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT3H, j); /* 上位保存 */
    }
    /*FAN2*/
    if ((CNT_STAT.out_put_previous.bitms.out_FAN2 == 0) && (CNT_STAT.out_put.bitms.out_FAN2))
    { /* ONになったら */
        SET_PARA.rycnt[3]++;
        j = (int)((SET_PARA.rycnt[3] / 15) & 0xFFFF);
        put_fram2(NERYCNT4L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[3] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT4H, j); /* 上位保存 */
    }
    /*FAN3*/
    if ((CNT_STAT.out_put_previous.bitms.out_FAN3 == 0) && (CNT_STAT.out_put.bitms.out_FAN3))
    { /* ONになったら */
        SET_PARA.rycnt[4]++;
        j = (int)((SET_PARA.rycnt[4] / 15) & 0xFFFF);
        put_fram2(NERYCNT5L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[4] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT5H, j); /* 上位保存 */
    }
    /*TA*/
    if ((CNT_STAT.out_put_previous.bitms.out_TA == 0) && (CNT_STAT.out_put.bitms.out_TA))
    { /* ONになったら */
        SET_PARA.rycnt[5]++;
        j = (int)((SET_PARA.rycnt[5] / 15) & 0xFFFF);
        put_fram2(NERYCNT6L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[5] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT6H, j); /* 上位保存 */
    }
    /*SV1*/
    if ((CNT_STAT.out_put_previous.bitms.out_SPSV == 0) && (CNT_STAT.out_put.bitms.out_SPSV))
    { /* ONになったら */
        SET_PARA.rycnt[6]++;
        j = (int)((SET_PARA.rycnt[6] / 15) & 0xFFFF);
        put_fram2(NERYCNT7L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[6] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT7H, j); /* 上位保存 */
    }
    /*SV2*/
    if ((CNT_STAT.out_put_previous.bitms.out_SV2 == 0) && (CNT_STAT.out_put.bitms.out_SV2))
    { /* ONになったら */
        SET_PARA.rycnt[7]++;
        j = (int)((SET_PARA.rycnt[7] / 15) & 0xFFFF);
        put_fram2(NERYCNT8L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[7] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT8H, j); /* 上位保存 */
    }
    /*SV3*/
    if ((CNT_STAT.out_put_previous.bitms.out_SV3 == 0) && (CNT_STAT.out_put.bitms.out_SV3))
    { /* ONになったら */
        SET_PARA.rycnt[8]++;
        j = (int)((SET_PARA.rycnt[8] / 15) & 0xFFFF);
        put_fram2(NERYCNT9L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[8] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT9H, j); /* 上位保存 */
    }
    /*SV4*/
    if ((CNT_STAT.out_put_previous.bitms.out_SV4 == 0) && (CNT_STAT.out_put.bitms.out_SV4))
    { /* ONになったら */
        SET_PARA.rycnt[9]++;
        j = (int)((SET_PARA.rycnt[9] / 15) & 0xFFFF);
        put_fram2(NERYCNT10L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[9] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT10H, j); /* 上位保存 */
    }
    /*CPC*/
    if ((CNT_STAT.out_put_previous.bitms.out_CPC == 0) && (CNT_STAT.out_put.bitms.out_CPC))
    { /* ONになったら */
        SET_PARA.rycnt[10]++;
        j = (int)((SET_PARA.rycnt[10] / 15) & 0xFFFF);
        put_fram2(NERYCNT11L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[10] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT11H, j); /* 上位保存 */
    }
    /*HG1*/
    if ((CNT_STAT.out_put_previous.bitms.out_HG == 0) && (CNT_STAT.out_put.bitms.out_HG))
    { /* ONになったら */
        SET_PARA.rycnt[11]++;
        j = (int)((SET_PARA.rycnt[11] / 15) & 0xFFFF);
        put_fram2(NERYCNT12L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[11] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT12H, j); /* 上位保存 */
    }
    /*DM1 MT1*/
    if ((CNT_STAT.out_put_previous.bitms.out_MT1 == 0) && (CNT_STAT.out_put.bitms.out_MT1))
    { /* ONになったら */
        SET_PARA.rycnt[12]++;
        j = (int)((SET_PARA.rycnt[12] / 15) & 0xFFFF);
        put_fram2(NERYCNT13L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[12] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT13H, j); /* 上位保存 */
    }
    /*DM2 MT2*/
    if ((CNT_STAT.out_put_previous.bitms.out_MT2 == 0) && (CNT_STAT.out_put.bitms.out_MT2))
    { /* ONになったら */
        SET_PARA.rycnt[13]++;
        j = (int)((SET_PARA.rycnt[13] / 15) & 0xFFFF);
        put_fram2(NERYCNT14L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[13] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT14H, j); /* 上位保存 */
    }
    /*DM3 MT3*/
    if ((CNT_STAT.out_put_previous.bitms.out_MT3 == 0) && (CNT_STAT.out_put.bitms.out_MT3))
    { /* ONになったら */
        SET_PARA.rycnt[14]++;
        j = (int)((SET_PARA.rycnt[14] / 15) & 0xFFFF);
        put_fram2(NERYCNT15L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[14] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT15H, j); /* 上位保存 */
    }
    /*LA*/
    if ((CNT_STAT.out_put_previous.bitms.out_LA == 0) && (CNT_STAT.out_put.bitms.out_LA))
    { /* ONになったら */
        SET_PARA.rycnt[15]++;
        j = (int)((SET_PARA.rycnt[15] / 15) & 0xFFFF);
        put_fram2(NERYCNT16L, j); /* 下位保存 */
        j = (int)((SET_PARA.rycnt[15] / 15) >> 16 & 0xFFFF);
        put_fram2(NERYCNT16H, j); /* 上位保存 */
    }
    CNT_STAT.out_put_previous.data = CNT_STAT.out_put.data;
}
/***************************************
    PPM-300 Main Rutine
 ***************************************/
void taskdummy(void) {}
const FTBLV taskfunc3[] = {
    /* 50ms×5 250ms毎の処理 */
    control_FAN, /* ファン動作 */
    chkover,     /* アップ･ダウンスケール    */
    iventchk,    /* イベントチェック処理 */
    set_output,  /* 出力I/O更新 */
    taskdummy};
void tasksub1(void) /* 250ms周期処理コール      */
{
    (*taskfunc3[TIMDT.taskcn2])(); /* 各タスク処理      */
    if (++TIMDT.taskcn2 >= 5)
    {
        TIMDT.taskcn2 = 0; /*タスクカウンタクリア      */
    }
}
const FTBLV taskfunc1[] = {
    /* 10ms×5 50ms毎の処理*/
    nowset,           /* 進行時間管理 (ランプ等) ブザー処理 */
    control1,         /* 加熱制御                 */
    control_reikyaku, /* 冷却制御                 */
    control_SV3_4,    /* 冷却制御  sv3               */
    tasksub1          /* 250ms周期処理コール      */
};
void tasksub(void) /* 50ms周期処理コール      */
{
    (*taskfunc1[TIMDT.taskcn1])(); /* 各タスク処理      */
    if (++TIMDT.taskcn1 >= 5)
    {
        TIMDT.taskcn1 = 0; /*タスクカウンタクリア      */
    }
}
const FTBLV taskfunc[] = {         /* 2ms×5 10ms毎の処理*/
                          tasksub, /* 50ms周期処理コール           */
                          control_holiday,
                          taskdummy,
                          taskdummy,
                          taskdummy};
/*************************************
 *  Task dummy routine                *
 **************************************/

extern void main(void)
{
    iniram();
    for (;;)
    {                /* 無限ループ (ﾒｲﾝ ｼｮﾘ)     */
        wdtcou1 = 0; /* WDT counter 2 clear      */
        command();   /* key an external input capture */
        if (TIMDT.iw == 0)
        {
            switch (KEY_MODE.flg_mode)
            {
            case FACTRYMD:
                factchk(); /*check 出力*/
                break;
            case SELFMD:
                selfchk();/*　自己診断　*/
                break;
            default:
                break;
            }
        }
        if (CNT_STAT.cf3_flg.bitms.main_task_request_flag == 1)
        {
            CNT_STAT.cf3_flg.bitms.main_task_request_flag = 0; /*タスク要求フラグクリア    */
            (*taskfunc[TIMDT.taskcn])();                       /* 各タスク処理      */
            if (++TIMDT.taskcn >= 5)
            {
                TIMDT.taskcn = 0; /*タスクカウンタクリア      */
            }
        }

        if (INPUT_ADC.cfadc2.bitms.ADC_125ms == 1)
        {
            INPUT_ADC.cfadc2.bitms.ADC_125ms = 0;
            advalue();
        }
        uartm_comm(); /* 通信コマンド処理         */
    }
}
