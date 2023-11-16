/*
 * p_comm_fhost_cmd.c
 *
 *  Created on: 2023/06/29
 *      Author: VINH-NT
 */

/* 対HOST-COMMANDエリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"

BYTE lockchk1(void);
/**
 * @brief 運転開始実行
 * 0001H: 実行
 */
void wr_h_unten_start(void)
{
    if (cmkdat() == 1)
    {
        /* どんな状態でもACK(RY同様にする) */
        if (KEY_MODE.flg_mode < SPECALMD)
        {
            TIMDT.ta0083 = get_data(PH_DATA83) * 1000 / 250; /* A0083 */
            if (TIMDT.ta0083 == 0)
            {
                ie_KEYSTART();
            }
        }
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief 運転停止実行
 *
 */
void wr_h_unten_stop(void)
{
    if (cmkdat() == 1)
    {
        /* どんな状態でもACK(RY同様にする) */
        if (KEY_MODE.flg_mode < SPECALMD)
        {
            ie_KEYSTOP();
        }
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief 庫内灯ON/OFF選択
 * 0000H: 消灯
 * 0001H: 点灯
 *
 */
void wr_h_light(void)
{
    int16_t data;

    data = cmkdat();
    switch (cmkdat())
    {
    case 1:
    case 0:
        CNT_STAT.out_put.bitms.out_LA = !CNT_STAT.out_put.bitms.out_LA;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief ブザー停止実行
 *
 */
void wr_h_buzzer_stop(void)
{
}
/**
 * @brief 点検クリア実行
 *　0001H：実行
 */
void wr_h_tenken_clear(void)
{
    if (cmkdat() == 1)
    {
        if (lockchk1() == OK)
        {
            switch (KEY_MODE.flg_mode)
            {
            case UNTENMD:
                TIMDT.bztm = 2; /* キー入力ブザー音 0.1秒 */
                if (CNT_STAT.alarm_flg2.bitms.al_gaibu1RCT)
                {
                    CNT_STAT.alarm_flg2.bitms.al_gaibu1RCT = 0;
                    set_data(PH_RCTCUNT, 0); /* to fram2 save, sram save */
                }
                if(CNT_STAT.alarm_flg2.bitms.al_poor_cool){  /* 冷却不良   */
					CNT_STAT.alarm_flg2.bitms.al_poor_cool = 0;
			        CNT_STAT.tenken_flg.bitms.reikyaku_furyou = 0; /* 冷却不良状態正常 */
					TIMDT.errtim3 = 0; /* 冷却不良計測ﾀｲﾏｰｸﾘｱ */
                }
                else/* 冷却不良持ち時間リセットされる */
                {
                    TIMDT.errtim3 = 0; /* 冷却不良計測ﾀｲﾏｰｸﾘｱ */
                }
                if(CNT_STAT.alarm_flg1.bitms.al_konai_over){  /* 庫内温度断線   */
					CNT_STAT.alarm_flg1.bitms.al_konai_over = 0;
                }
                if(CNT_STAT.alarm_flg1.bitms.al_gaibu1_over){  /* 庫内温度断線   */
					CNT_STAT.alarm_flg1.bitms.al_konai_over = 0;
                }
                break;

            default:
                break;
            }
        }
        wryaku(); /* どんな状態でもACK */
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief 手動除霜開始実行
 *　0001H：実行
 */
void wr_h_shudoujoso_start(void)
{
    if (cmkdat() == 1)
    {
        if ((CNT_STAT.cfjoso_flg.bitms.joso_unten != 1) && (CNT_STAT.out_put.bitms.out_DHH != 1))
        {                                                    /* 除霜待機 */
            CNT_STAT.cfjoso_flg.bitms.shudou_joso_start = 1; /* 手動除霜開始　ON */
            TIMDT.t60s = INTCLK1M;
            TIMDT.dhhontime = SET_PARA.setpara[PH_DATA24]; /* ON時間時刻設定　*/
        }
        wryaku(); /* どんな状態でもACK */
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief 手動除霜解除実行
 *　0001H：実行
 */
void wr_h_shudoujoso_stop(void)
{
    if (cmkdat() == 1)
    {
        // if (CNT_STAT.cfjoso_flg.bitms.joso_unten == 1)
        // { /* 除霜運転 */
        if (CNT_STAT.cfjoso_flg.bitms.shudou_joso_start)
        { /* 手動除霜開始　ONなら*/
            TIMDT.t60s = INTCLK1M;
            switch (SET_PARA.josouhoushiki)
            {
            case 0: /* 除霜ｻｲｸﾙ時間ｶｳﾝﾄｸﾘｱ処理*/
                TIMDT.defshudotim = SET_PARA.setpara[PH_DATA14];
                CNT_STAT.cfjoso_flg.bitms.shudou_joso_start = 0; /* 手動除霜開始　OFF */
                break;
            default:
                CNT_STAT.cfjoso_flg.bitms.shudou_joso_start = 0; /* 手動除霜開始　OFF */
                break;
            }
            CNT_STAT.cfjoso_flg.bitms.joso_unten = 0; /* 除霜待機     */
            if (SET_PARA.setpara[PH_DATA40])
            {                                                                 /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 0;             /* SV2初期動作未実行にする  */
                CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;             /* SV2初期動作未実行にする  */
            }
            else
            {
                CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* SV2ｻｲｸﾙなし             */
                CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0; /* SV2初期動作未実行にする */
            }
        }
        wryaku(); /* どんな状態でもACK */
    }
    else
    {
        wrnak3();
    }
    //}
}
/**
 * @brief 異常履歴クリア
 *　0001H：実行
 */
void wr_h_errclr(void)
{
    if (cmkdat() == 1)
    {
        int *p;
        WORD i, j;
        /* 点検番号クリア */
        i = NECHECKD01NO;
        j = NECHECKD20MINUTE;
        p = &SET_PARA.nerrcode01[0];
        do
        {
            *p = 0;
            put_fram2(i, 0); /* 設定値 Initialize                   */
            i++;
            *p++;
        } while (i <= j);
        wryaku(); /* どんな状態でもACK */
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief プログラムモードクリア実行
 *　0001H：実行
 */
void wr_h_program_clear(void)
{
    if (cmkdat() == 1)
    {
        if(KEY_MODE.flg_mode == STANDBYMD)
        {
            clrprog_pro(CLR_READ_FRAM);
            /*code*/
            wryaku(); /* どんな状態でもACK */
        }
        else
        {
            wrnak3();
        }

        
    }
    else
    {
        wrnak3();
    }
}
/**
 * @brief パラメータモードクリア実行
 *　0001H：実行
 */
void wr_h_parameter_clear(void)
{
    if (cmkdat() == 1)
    {
        if(KEY_MODE.flg_mode == STANDBYMD)
        {
            clrprog_para(CLR_READ_FRAM);
            /*code*/
            wryaku(); /* どんな状態でもACK */
        }
        else
        {
            wrnak3();
        }
    }
    else
    {
        wrnak3();
    }
}

const FTBLV host_w_command_tbl[] = {
    wr_h_unten_start,      /* 運転開始実行 */
    wr_h_unten_stop,       /* 運転停止実行 */
    wr_h_light,            /* 庫内灯ON/OFF選択 */
    wr_h_buzzer_stop,      /* ブザー停止実行 */
    wr_h_shudoujoso_start, /* 手動除霜開始実行 */
    wr_h_shudoujoso_stop,  /* 手動除霜解除実行 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wr_h_errclr,           /* 異常履歴クリア */
    wr_h_tenken_clear,     /* 点検クリア実行 */
    wr_h_program_clear,    /* プログラムモードクリア実行 */
    wr_h_parameter_clear,  /* パラメータモードクリア実行 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku,                /* 予約 */
    wryaku                 /* 予約 */

};

/*------------------------------------------------- */
void host_command_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = PH_DUMMY; /* dummy */
}
void host_read_command_data(void)
{
    host_command_make_phase(uartp->base_addr);
    rdnone();
}
void host_write_command_data(void)
{
    host_command_make_phase(uartp->base_addr);
    if (uartp->commitem < sizeof(host_w_command_tbl) / 4)
    {
        if (TIMDT.iw == 0)
        {
            if(host_write_status_check(uartp->erea))
            {
                (*host_w_command_tbl[uartp->commitem])();
            }
        }
        else
        { /* ウォームアップ中は操作コマンド受けない */
            wryaku();
        }
    }
    else
    {
        wrnone();
    }
}
