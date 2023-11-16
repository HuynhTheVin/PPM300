/*
 * p_key.c
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_key.h"

void datarefresh(void);
/**
 * @brief 調理スタート
 *
 * @return @see K_RES_xx
 */
BYTE ie_KEYSTART(void)
{
    uint8_t k_ret = K_RES_OK;

    switch (KEY_MODE.flg_mode)
    {
    case STANDBYMD:
    case UNTENMD: /* 運転モード */
        break;    /* 有効 */
    default:
        return K_RES_NG_KEY; /* 無効 */
    }

    switch (KEY_MODE.flg_mode)
    {
    case TIMEMD:             /* 時刻管理*/
    case JOSOMD:             /* 除霜設定管理  */
    case SPECALMD:           /* パラメータモード */
    case CHECKMD:            /* 点検履歴モード    */
        return K_RES_NG_KEY; /* nothing to do */
    case UNTENMD:            /* 運転モード */
        CNT_STAT.cfreikyaku_flg.data = 0x00;
        datarefresh();
        switch (KEY_MODE.flg_rmode)
        {
        case REITOMD:
            k_ret = start_reitou_unten();
            /* code */
            break;
        case REITOZOUMD:
            k_ret = start_reitouzou_unten();
            /* code */
            break;
        default:
            break;
        }
    case STANDBYMD: /* 無表示モード                   */
        KEY_MODE.flg_mode = UNTENMD;
        KEY_MODE.flg_rmode = REITOMD;
        CNT_STAT.cfreikyaku_flg.data = 0x00;
        k_ret = start_reitou_unten();
        if (is_untenchu())
        {
            /* 運転中、CODE*/
        }
        break;

    default:
        return K_RES_NG_KEY; /* nothing to do */
    }
    return k_ret;
}
/**
 * @brief 運転停止
 *
 */
void ie_KEYSTOP(void)
{
    switch (KEY_MODE.flg_mode)
    {
    case TIMEMD:   /* 除霜設定管理 */
    case JOSOMD:   /* 時刻管理 */
    case SPECALMD: /* 詳細パラメータモード */
    case CHECKMD:  /* 点検履歴モード    */
        break;
    case UNTENMD:   /* 運転モード */
    case STANDBYMD: /* 無表示モード                   */
        KEY_MODE.flg_mode = STANDBYMD;
        CNT_STAT.con_sflg.data = 0;
        stop_sub();
        fact_out_off(); /* 出力OFF　*/
        make_IO_out(0);
        break;
    default:
        break;
    }
}
void stop_sub(void)
{
    TIMDT.ta0083 = 0;                    /* タイマ初期化 */
    CNT_STAT.out_put.bitms.out_buzz = 0; /* ブザー OFF  */
}
/************************
 * 外部入力の処理
 **************************/
void extcommandsub(void)
{
    union UEVTI d;

    if (KEY_MODE.flg_mode == SELFMD)
    {
        return;
    }
    d.data = KEY_MODE.extcomm.data; /* 外部入力取り込み */
    if ((d.bitms.CPT != 1) && (CONTROL.cf4_flg.bitms.al_gaibu2CPT != 1))
    { /* CPT ON （200V印加でON）*/
        if (TIMDT.cpt3stim == 0)
        { 
            CONTROL.cf4_flg.bitms.al_gaibu2CPT = 1;
            CNT_STAT.alarm_flg2.bitms.al_gaibu2CPT = 1;
            checksave(5); /* CPT異常*/
        }
    }
    else
    {
        if (d.bitms.CPT)
        { /* CPT OFF */
            CONTROL.cf4_flg.bitms.al_gaibu2CPT = 0;
            TIMDT.cpt3stim = 3000; /* 正常時3秒時間常時ｾｯﾄ */
        }
    }
    if (d.bitms.THF1 != 1)
    { /* HTF1 OFF */
        if (CNT_STAT.alarm_flg1.bitms.al_kanetsufuse_break != 1)
        {
            checksave(8); /* HTF1異常*/
        }
        CNT_STAT.alarm_flg1.bitms.al_kanetsufuse_break = 1;
    }
    /* フロートスイッチ状態 */
    if (d.bitms.FS)
    {                                                                  /* FS1 ON */
        CNT_STAT.cf3_flg.bitms.external_input_float_switch_status = 1; /* フロートスイッチON  */
    }
    else
    {
        CNT_STAT.cf3_flg.bitms.external_input_float_switch_status = 0; /* フロートスイッチOFF */
    }
}
void exitchk(void)
{
    union UEVTI d;
    union UDSWI sw;

    d.data = 0;
    /* 外部入力  CPT    B4 */
    /* 外部入力  RCT    B3 */
    /* 外部入力  FS1    B2 */
    /* 外部入力  HTF2   B0 */
    /* 外部入力  HTF1   B1 */
    if (IO_IN_THF1_ONQ)
    {
        d.bitms.THF1 = 1;
    }
    if (IO_IN_THF2_ONQ)
    {
        d.bitms.THF2 = 1;
    }
    if (IO_IN_FS_ONQ)
    {
        d.bitms.FS = 1;
    }
    if (IO_IN_RCT_ONQ)
    {
        d.bitms.RCT = 1;
    }
    if (IO_IN_CPT_ONQ)
    {
        d.bitms.CPT = 1;
    }
    if (IO_IN_N_ONQ)
    {
        d.bitms.n = 1;
    }
    if (IO_IN_YOHI_ONQ)
    {
        d.bitms.yobi = 1;
    }
    if (KEY_MODE.extcat1.data != d.data)
    {
        KEY_MODE.extcat1.data = d.data; /* 1st check */
    }
    else if (KEY_MODE.extcat2.data != d.data)
    {
        KEY_MODE.extcat2.data = d.data; /* 2 check */
    }
    else
    {
        KEY_MODE.extcomm.data = d.data; /* 3 OK */
        extcommandsub();
    }

    /* SW: Only check when power on or self check mode. */
    if ((TIMDT.iw == 0) || (KEY_MODE.flg_mode == SELFMD))
    {
        sw.data = 0;
        if (IO_IN_SW1_ONQ)
        {
            sw.bitms.sw1 = 1;
        }
        if (IO_IN_SW2_ONQ)
        {
            sw.bitms.sw2 = 1;
        }
        if (IO_IN_SW3_ONQ)
        {
            sw.bitms.sw3 = 1;
        }
        if (KEY_MODE.swcat1.data != sw.data)
        {
            KEY_MODE.swcat1.data = sw.data; /* 1st check */
        }
        else if (KEY_MODE.swcat2.data != sw.data)
        {
            KEY_MODE.swcat2.data = sw.data; /* 2 check */
        }
        else
        {
            KEY_MODE.swcomm.data = sw.data; /* 3 OK */
        }
    }
}

void command(void)
{
    if (KEY_MODE.krditv == 0)
    {
        KEY_MODE.krditv = DIGNUM;
        exitchk(); /* Capture of digital external input */
    }
}
