/*
 * p_comm_fhost_mon.c
 *
 *  Created on: 2023/06/27
 *      Author: VINH-NT
 */
/* 対HOST-MONITORエリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"


/**
 * @brief 現在の庫内温度設定値
 * 
 */
void rd_h_set_sv1(void)
{
    comret_dt(CONTROL.rundata[0]);
}
/**
 * @brief 現在の庫内湿度設定
 * 
 */
void rd_h_set_sv2(void)
{
    comret_dt(0);
    //comret_dt(RUN_DATA.ckrun_sv2);
}
/**
 * @brief 点検番号
 * 
 */
void rd_h_tenken(void)
{
    comret_dt(0);
}
/**
 * @brief 現在のメモリ番号
 * 
 */
void rd_h_memory(void)
{
    comret_dt(1);/* 現在値(1固定) */
}
/**
 * @brief 現在の運転モ－ド
 * 0000H スタンバイ
 * 0001H 急速冷却
 * 0002H 冷凍・冷蔵
 * 
 */
void rd_h_unten_md(void)
{
    int16_t data;

    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        switch (KEY_MODE.flg_rmode)
        {
        case REITOMD:
            data = 0x0001;
            break;
        case REITOZOUMD:
            data = 0x0002;
            break;
        default:
            data = 0x0000;
            break;
        }
        break;
    default:
        data = 0x0000;
        break;
    }
    comret_dt(data);
}
/**
 * @brief 残り休日日数
 * 
 */
void rd_h_holidays_left(void)
{
    int16_t data;
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        data = CONTROL.holiday_num;
        break;
    default:
        data = 0x0000;
        break;
    }
    comret_dt(data);
}
/**
 * @brief 状態フラグ1
 * 
 */
void rd_h_status1(void)
{
    union U_BIT16 data;
    data.data = 0;
    if(IO_OUT_H1_ONQ)
    {
        data.bitms.B0 = 1;/* 加熱　0:OFF　1:ON */
        if(CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong)
        {
            data.bitms.B10 = 1; /* 加熱制御　0:弱運転　1:強運転 */
        }
    }
    comret_dt(data.data);
}
/**
 * @brief 状態フラグ2
 * 
 */
void rd_h_status2(void)
{
    union U_BIT16 data;
    data.data = 0;
    if(IO_OUT_H1_ONQ)
    {
        data.bitms.B0 = 1;/* B0:　加熱ヒータ出力（H1）0:OFF　1:ON */
    }
    if(IO_OUT_DHH_ONQ)
    {
        data.bitms.B4 = 1;/* B4:　ドレンホースヒータ出力（DHH）0:OFF　1:ON */
    }
    if(IO_OUT_DH_ONQ)
    {
        data.bitms.B5 = 1;/* B5:　ドアヒータ出力（DH）0:OFF　1:ON */
    }
    if(IO_OUT_FAN1_ONQ)
    {
        data.bitms.B6 = 1;/* B6:　FAN1出力（FAN1）0:OFF　1:ON */
    }
    if(IO_OUT_FAN2_ONQ)
    {
        data.bitms.B7 = 1;/* B7:　FAN2出力（FAN2）0:OFF　1:ON */
    }
    if(IO_OUT_FAN3_ONQ)
    {
        data.bitms.B8 = 1;/* B6:　FAN3出力（FAN3）0:OFF　1:ON */
    }
    if(IO_OUT_TA_ONQ)
    {
        data.bitms.B9 = 1;/* B9:　警報出力（TA）0:OFF　1:ON */
    }
    if(IO_OUT_SPSV_ONQ)
    {
        data.bitms.B10 = 1;/* B10:　給水出力（SV1/SPSV）0:OFF　1:ON */
    }
    if(IO_OUT_SV2_ONQ)
    {
        data.bitms.B11 = 1;/* B11:　冷媒出力（SV2）0:OFF　1:ON */
    }
    if(IO_OUT_SV3_ONQ)
    {
        data.bitms.B12 = 1;/* B12:　緊急水冷出力（SV3）0:OFF　1:ON */
    }
    if(IO_OUT_SV4_ONQ)
    {
        data.bitms.B13 = 1;/* B13:　冷媒BY出力（SV4）0:OFF　1:ON */
    }
    comret_dt(data.data);
}
/**
 * @brief 状態フラグ3
 * 
 */
void rd_h_status3(void)
{
    union U_BIT16 data;
    data.data = 0;
    if(IO_OUT_CPC_ONQ)
    {
        data.bitms.B0 = 1;/* B0:　冷凍機制御信号出力出力（CPC）0:OFF　1:ON */
    }
    // if(IO_OUT_SPSV_ONQ)
    // {
    //     data.bitms.B1 = 1;/* B1:　SPSV出力（SV1/SPSV）0:OFF　1:ON */
    // }
    if(IO_OUT_HG_ONQ)
    {
        data.bitms.B3 = 1;/* B3:　加熱保護リレー制御信号出力（HG）0:OFF　1:ON */
    }
    if(IO_OUT_MT1_ONQ)
    {
        data.bitms.B5 = 1;/* B5:　ダンパモータ出力（MT1）0:OFF　1:ON */
    }
    if(IO_OUT_MT2_ONQ)
    {
        data.bitms.B6 = 1;/* B6:　ダンパモータ出力（MT2）0:OFF　1:ON */
    }
    if(IO_OUT_MT3_ONQ)
    {
        data.bitms.B7 = 1;/* B7:　ダンパモータ出力（MT3）0:OFF　1:ON */
    }
    if(IO_OUT_LA_ONQ)
    {
        data.bitms.B8 = 1;/* B8:　庫内照明出力（LA）0:OFF　1:ON */
    }
    if(IO_OUT_BUZZER_ONQ)
    {
        data.bitms.B9 = 1;/* B9:　ブザー出力(BZ) 0:OFF　1:ON */
    }
    if(IO_IN_THF1_ONQ)
    {
        data.bitms.B11 = 1;/* B11:　加熱温度ﾋｭｰｽﾞ入力(HTF1) 0:OFF　1:ON */
    }
    if(IO_IN_RCT_ONQ)
    {
        data.bitms.B14 = 1;/* B14:　冷凍機液温異常入力(RTC) 0:OFF　1:ON */
    }
    if(IO_IN_CPT_ONQ)
    {
        data.bitms.B15 = 1;/* B15:　冷凍機異常入力(CPT)  0:OFF　1:ON */
    }
    comret_dt(data.data);
}
/**
 * @brief エラーフラグ1
 * 
 */
void rd_h_err1(void)
{
    union U_BIT16 data;
    data.data = CNT_STAT.alarm_flg1.data;
    comret_dt(data.data);
}
/**
 * @brief エラーフラグ2
 * 
 */
void rd_h_err2(void)
{
    union U_BIT16 data;
    data.data = CNT_STAT.alarm_flg2.data;
    comret_dt(data.data);
}
/**
 * @brief エラーフラグ3
 * 
 */
void rd_h_err3(void)
{
    rdyaku();
}
/**
 * @brief エラーフラグ4
 * 
 */
void rd_h_err4(void)
{
    rdyaku();
}
/**
 * @brief 現在時刻
 * 
 */
void rd_h_time(void)
{
    comret_dt(convert_min(SET_TIME.sethour, SET_TIME.setmin));
}
const FTBLV host_r_monitor_tbl[] = {
    rd_pv1,             /* 庫内温度入力値 */
    rd_pv2,             /* 庫内湿度入力値 */
    rd_pv3,             /* マルチ入力1　入力値 */
    rd_pv4,             /* マルチ入力2　入力値 */
    rd_pv5,             /* マルチ入力3　入力値 */
    rd_h_set_sv1,       /* 現在の庫内温度設定値 */
    rd_h_set_sv2,       /* 現在の庫内湿度設定 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rd_h_tenken,        /* 点検番号 */
    rd_h_memory,        /* 現在のメモリ番号 */
    rd_h_unten_md,      /* 現在の運転モ－ド */
    rd_h_holidays_left, /* 残り休日日数 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rdyaku,             /* 予約 */
    rd_h_status1,       /* 状態フラグ1 */
    rd_h_status2,       /* 状態フラグ2 */
    rd_h_status3,       /* 状態フラグ3 */
    rd_h_err1,          /* エラーフラグ1 */
    rd_h_err2,          /* エラーフラグ2 */
    rd_h_err3,          /* エラーフラグ3 */
    rd_h_err4,          /* エラーフラグ4 */
    rd_h_time           /* 現在時刻 */
};
void host_monitor_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    if (uartp->commitem < sizeof(host_r_monitor_tbl) / 4)
    {
        uartp->phase = PH_DUMMY; /* dummy */
    }
    else if (uartp->commitem < 80 + sizeof(host_r_monitor_tbl) / 4) /* 点検履歴最大数 + 。。。 */
    {
        uartp->phase = PH_CHECKD01NO + uartp->id - sizeof(host_r_monitor_tbl) / 4;
    }
    else
    {
        uartp->phase = PH_DUMMY; /* dummy */
    }
}

void host_read_monitor_data(void)
{
    host_monitor_make_phase(uartp->base_addr);
    if (uartp->commitem < sizeof(host_r_monitor_tbl) / 4)
    {
        (*host_r_monitor_tbl[uartp->commitem])();
    }
    else if (uartp->commitem < 80 + sizeof(host_r_monitor_tbl) / 4) /* 点検履歴最大数 + 。。。 */
    {
        comret_dt(get_data(uartp->phase));
    }
    else
    {
        rdnone();
    }
}

void host_write_monitor_data(void)
{
    host_monitor_make_phase(uartp->base_addr);
    wrnone();
}
