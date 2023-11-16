/*
 * p_cont_fan.c
 *
 *  Created on: 2023/07/12
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_cont_fan.h"

/**************
 * ファン動作
 **************/
void control_FAN(void)
{
    /*ｳｫｰﾑｱｯﾌﾟ中とFRAM ERRERと電源投入後A0041秒間は処理しない */
    if ((TIMDT.iw) || (CNT_STAT.sys_flg.bitms.e_eeprom) || (TIMDT.ta0083) || (KEY_MODE.flg_mode == SELFMD))
    {
        return;
    }
    /* ファン動作 */

    if (KEY_MODE.flg_mode >= STANDBYMD)
    {                                        /* 運転モード以外は停止   */
        CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1　OFF */
        CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2　OFF */
        return;
    }
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        switch (KEY_MODE.flg_rmode)
        {
        case REITOMD:
            control_FAN_reitou();
            break;
        default:
            control_FAN_reitouzou();
            break;
        }
    }
}
/**************
 * 冷凍モードのファン動作
 **************/
void control_FAN_reitou(void)
{
    if (CNT_STAT.cfjoso_flg.bitms.joso_unten) /* 除霜中の場合、FAN1,2　OFF */
    {
        CNT_STAT.out_put.bitms.out_FAN1 = 0;          /* FAN1出力　OFF */
        CNT_STAT.out_put.bitms.out_FAN2 = 0;          /* FAN2出力　OFF */
        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1制御　OFF */
        CNT_STAT.cffan_flg.bitms.fan2_out_status = 0; /* FAN2制御　OFF */
        TIMDT.fan1wait1st = 0;                        /* FAN1,2切り替え時、タイムラグなし */
        TIMDT.fan2wait1st = 0;                        /* FAN1,2切り替え時、タイムラグなし */
    }
    else
    {
        if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op)         /* SV2インチング動作ではない */
        {                                                         /* SV2初期動作実行済みなら */
            if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition) /* 冷却信号がONの場合 */
            {
                if (CNT_STAT.out_put.bitms.out_FAN2 == 0) /* FAN2出力がOFFの場合 */
                {
                    TIMDT.fan2wait1st = 0;                             /* FAN1,2切り替え時、タイムラグなし */
                    if (CNT_STAT.cffan_flg.bitms.fan1_out_status != 1) /* FAN2状態　OFFなら */
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 1;
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 1; /* FAN1制御　ON */
                    }
                }
                else /* FAN2出力がONの場合 */
                {
                    CNT_STAT.out_put.bitms.out_FAN2 = 0;
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 1; /* FAN1状態　ON */
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 0; /* FAN2状態　OFF */
                    TIMDT.fan1wait1st = 4;                        /* FAN1,2切り替え時、1秒間のタイムラグ */
                }
            }
            else /* 冷却信号がOFFの場合 */
            {
                if (CNT_STAT.out_put.bitms.out_FAN1 == 0) /* FAN1出力がOFFの場合 */
                {
                    TIMDT.fan1wait1st = 0;                             /* FAN1,2切り替え時、タイムラグなし */
                    if (CNT_STAT.cffan_flg.bitms.fan2_out_status != 1) /* FAN2状態　OFFなら */
                    {
                        CNT_STAT.out_put.bitms.out_FAN2 = 0;
                        CNT_STAT.cffan_flg.bitms.fan2_out_status = 1;
                    }
                }
                else /* FAN1出力がONの場合 */
                {
                    CNT_STAT.out_put.bitms.out_FAN1 = 0;
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 1; /* FAN2状態　ON */
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1制御　OFF */
                    TIMDT.fan2wait1st = 4;                        /* FAN1,2切り替え時、1秒間のタイムラグ */
                }
            }
        }
    }
}
/**************
 * 冷凍冷蔵モードのファン動作
 **************/
void control_FAN_reitouzou(void)
{
    int ontim, offtim;
    if (CNT_STAT.cfjoso_flg.bitms.joso_unten) /* 除霜中の場合、FAN1,2　OFF */
    {
        CNT_STAT.out_put.bitms.out_FAN1 = 0;          /* FAN1出力　OFF */
        CNT_STAT.out_put.bitms.out_FAN2 = 0;          /* FAN2出力　OFF */
        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1制御　OFF */
        CNT_STAT.cffan_flg.bitms.fan2_out_status = 0; /* FAN2制御　OFF */
        TIMDT.fan1wait1st = 0;                        /* FAN1,2切り替え時、タイムラグなし */
        TIMDT.fan2wait1st = 0;                        /* FAN1,2切り替え時、タイムラグなし */
    }
    else
    {
        if (CNT_STAT.cfkanetu_flg.bitms.H1_start_enable) /* 加熱２信号　ONの場合*/
        {
            /* FAN 1 ON-OFF 時間設定 */
            ontim = SET_PARA.setpara[PH_DATA22] * 4; /* A0022 */ /* 250ms毎の処理なので4倍する */
            offtim = SET_PARA.setpara[PH_DATA23] * 4;            /* A0023 */
            // CNT_STAT.cffan_flg.bitms.fan1_out_status = 1;
            control_FAN12_ONOFF(ontim, offtim);
        }
        else
        {
            if (CNT_STAT.cffan_flg.bitms.fan1_waittime_off) /* 加熱2信号終了時FAN1遅延時間　ONの場合*/
            {
                if (TIMDT.fan1ontim != 0)
                {
                    CNT_STAT.out_put.bitms.out_FAN1 = 1; /* FAN1 ON */
                    CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2 OFF */
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 1;
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 0;
                }
                else
                {
                    CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                    CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2 OFF */
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 0;
                    if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op)         /* SV2インチング動作ではない */
                    {                                                         /* SV2初期動作実行済みなら */
                        if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition) /* 冷却信号がONの場合 */
                        {
                            CNT_STAT.cffan_flg.bitms.fan1_ontime_reikyaku_on = 1; /* A0055遅延時間中,冷却信号ON */
                        }
                        else
                        {
                            CNT_STAT.cffan_flg.bitms.fan1_ontime_reikyaku_on = 0; /* A0055遅延時間中,冷却信号OFF */
                        }
                    }
                    CNT_STAT.cffan_flg.bitms.fan1_waittime_off = 0;
                    TIMDT.cunton_off[fan1] = 1;
                }
            }
            else
            {
                if (CNT_STAT.cffan_flg.bitms.fan1_ontime_reikyaku_on)
                {
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 1; /*FAN1,2 ON OFF 切り替わる */
                }
                else
                {
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                }
                if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op)         /* SV2インチング動作ではない */
                {                                                         /* SV2初期動作実行済みなら */
                    if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition) /* 冷却信号がONの場合 */
                    {
                        ontim = SET_PARA.setpara[PH_DATA57] * 4; /* A0057 */ /* 250ms毎の処理なので4倍する */
                        offtim = SET_PARA.setpara[PH_DATA56] * 4;            /* A0056 */
                        control_FAN12_ONOFF(ontim, offtim);
                    }
                    else
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 0;          /* FAN1出力　OFF */
                        CNT_STAT.out_put.bitms.out_FAN2 = 0;          /* FAN2出力　OFF */
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1制御　OFF */
                        CNT_STAT.cffan_flg.bitms.fan2_out_status = 0; /* FAN2制御　OFF */
                        TIMDT.cunton_off[fan1] = 1;
                    }
                }
                else
                {
                    CNT_STAT.out_put.bitms.out_FAN1 = 0;          /* FAN1出力　OFF */
                    CNT_STAT.out_put.bitms.out_FAN2 = 0;          /* FAN2出力　OFF */
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 0; /* FAN1制御　OFF */
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 0; /* FAN2制御　OFF */
                    TIMDT.cunton_off[fan1] = 1;
                }
            }
        }
    }
}

void control_FAN12_ONOFF(int ontim, int offtim)
{
    if (TIMDT.cunton_off[fan1])
    {
        if (--TIMDT.cunton_off[fan1] == 0)
        {
            if (CNT_STAT.cffan_flg.bitms.fan1_out_status == 0)
            {
                if (ontim)
                {
                    TIMDT.cunton_off[fan1] = ontim;
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 1;
                    if (CNT_STAT.cffan_flg.bitms.fan2_out_status != 1)
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 1; /* FAN1 ON */
                    }
                    else
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                    }
                }
                else
                {
                    if (offtim)
                    {
                        TIMDT.cunton_off[fan1] = offtim;
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                        CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                    }
                    else /* A0022, A0023時間が0なら */
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                        CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2 OFF */
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                        CNT_STAT.cffan_flg.bitms.fan2_out_status = 0;
                        TIMDT.cunton_off[fan1] = 1;
                    }
                }
            }
            else
            {
                if (offtim)
                {
                    TIMDT.cunton_off[fan1] = offtim;
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                    CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                }
                else
                {
                    TIMDT.cunton_off[fan1] = ontim;
                    CNT_STAT.cffan_flg.bitms.fan1_out_status = 1;
                    CNT_STAT.out_put.bitms.out_FAN1 = 1; /* FAN1 ON */
                }
            }
        }
        else
        {
            if (CNT_STAT.cffan_flg.bitms.fan1_out_status == 0)
            {
                if (TIMDT.cunton_off[fan1] >= (offtim - 4))
                {
                    CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2 OFF */
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 0;
                }
                else
                {
                    CNT_STAT.out_put.bitms.out_FAN2 = 1; /* FAN2 ON */
                    CNT_STAT.cffan_flg.bitms.fan2_out_status = 1;
                }
            }
            else
            {
                CNT_STAT.out_put.bitms.out_FAN2 = 0; /* FAN2 OFF */
                if (CNT_STAT.cffan_flg.bitms.fan2_out_status == 1)
                {
                    if (TIMDT.cunton_off[fan1] >= (ontim - 4))
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 0; /* FAN1 OFF */
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 0;
                    }
                    else
                    {
                        CNT_STAT.out_put.bitms.out_FAN1 = 1; /* FAN1 ON */
                        CNT_STAT.cffan_flg.bitms.fan1_out_status = 1;
                    }
                }
            }
        }
    }
}