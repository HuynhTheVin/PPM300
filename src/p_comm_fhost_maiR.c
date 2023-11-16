/*
 * p_comm_fhost_maiR.c
 *
 *  Created on: 2023/06/28
 *      Author: VINH-NT
 */
/* 対HOST-MAINTENANCE READ エリア */

#define EXTERN extern
#include "PPM.H"

/**
 * @brief DHHリレー累積ON回数
 *
 */
void rd_DHH(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[0] / 15));
}
/**
 * @brief DHリレー累積ON回数
 *
 */
void rd_DH(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[1] / 15));
}
/**
 * @brief FAN1リレー累積ON回数
 *
 */
void rd_FAN1(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[2] / 15));
}
/**
 * @brief  FAN2リレー累積ON回数
 *
 */
void rd_FAN2(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[3] / 15));
}
/**
 * @brief  FAN3リレー累積ON回数
 *
 */
void rd_FAN3(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[4] / 15));
}
/**
 * @brief TAリレー累積ON回数
 *
 */
void rd_TA(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[5] / 15));
}
/**
 * @brief SV1リレー累積ON回数
 *
 */
void rd_SV1(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[6] / 15));
}
/**
 * @brief SV2リレー累積ON回数
 *
 */
void rd_SV2(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[7] / 15));
}
/**
 * @brief SV3リレー累積ON回数
 *
 */
void rd_SV3(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[8] / 15));
}
/**
 * @brief SV4リレー累積ON回数
 *
 */
void rd_SV4(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[9] / 15));
}
/**
 * @brief CPCリレー累積ON回数
 *
 */
void rd_CPC(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[10] / 15));
}
/**
 * @brief HG1リレー累積ON回数
 *
 */
void rd_HG1(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[11] / 15));
}
/**
 * @brief DM1リレー累積ON回数
 *
 */
void rd_DM1(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[12] / 15));
}
/**
 * @brief DM2リレー累積ON回数
 *
 */
void rd_DM2(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[13] / 15));
}
/**
 * @brief DM3リレー累積ON回数
 *
 */
void rd_DM3(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[14] / 15));
}
/**
 * @brief LAリレー累積ON回数
 *
 */
void rd_LA(void)
{
    comret_dt((WORD)(SET_PARA.rycnt[15] / 15));
}

/**
 * @brief 冷却不良判定残り時間(A0067)
 *
 */
void rd_t_left_A0067(void)
{
    comret_dt(SET_PARA.setpara[PH_DATA67] * 60 - TIMDT.errtim3);
}
/**
 * @brief 除霜タイマ
 *
 */
void rd_t_joso(void)
{
    comret_dt(TIMDT.defrosttim); /* 分 */
}
/**
 * @brief 冷蔵ファン遅延タイマ
 *
 */
void rd_t_delay_reizou(void)
{
    rdyaku();
}
/**
 * @brief H1,H2(加熱)ヒータ出力切替えタイマ
 *
 */
void rd_t_sw_H1_H2(void)
{
    rdyaku();
}
/**
 * @brief SV1出力切替えタイマ
 *
 */
void rd_t_sw_SV1(void)
{
    rdyaku();
}
/**
 * @brief SV2出力切替えタイマ
 *
 */
void rd_t_sw_SV2(void)
{
    rdyaku();
}
/**
 * @brief SV3出力切替えタイマ
 *
 */
void rd_t_sw_SV3(void)
{
    rdyaku();
}
/**
 * @brief FAN1出力切替えタイマ
 *
 */
void rd_t_sw_FAN1(void)
{
    rdyaku();
}
/**
 * @brief FAN2出力切替えタイマ
 *
 */
void rd_t_sw_FAN2(void)
{
    rdyaku();
}
/**
 * @brief FAN3出力切替えタイマ
 *
 */
void rd_t_sw_FAN3(void)
{
    rdyaku();
}
/**
 * @brief 制御開始するまでウエイトタイマ
 *　t0083
 */
void rd_t_sw_wait(void)
{
    comret_dt(TIMDT.ta0083 / 4);
}
/**
 * @brief 外部入力
 *
 */
void rdgaibuinput(void)
{
    comret_dt(KEY_MODE.extcomm.data);
}

/**
 * @brief 加熱強ON時間
 *
 */
void rd_t_kanetu_strong(void)
{
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        if (CNT_STAT.out_put.bitms.out_H1 && CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong)
        {
            comret_dt(TIMDT.cunton_off[heatch] / 20);
        }
        else
            comret_dt(0);
    }
    else
        comret_dt(0);
}
/**
 * @brief 加熱弱ON時間
 *
 */
void rd_t_kanetu_low(void)
{
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        if (CNT_STAT.out_put.bitms.out_H1 && (CNT_STAT.cfkanetu_flg.bitms.heating_operation_weak_strong == 0))
        {
            comret_dt(TIMDT.cunton_off[heatch] / 20);
        }
        else
            comret_dt(0);
    }
    else
        comret_dt(0);
}
/**
 * @brief 加湿強ON時間
 *
 */
void rd_t_kashitu_strong(void)
{
    rdyaku();
}
/**
 * @brief 加湿弱ON時間
 *
 */
void rd_t_kashitu_low(void)
{
    rdyaku();
}
const FTBLV host_r_maintenaceR_tbl[] = {
    rd_DHH,              /* DHHリレー累積ON回数 */
    rd_DH,               /* DHリレー累積ON回数 */
    rd_FAN1,             /* FAN1リレー累積ON回数 */
    rd_FAN2,             /* FAN2リレー累積ON回数 */
    rd_FAN3,             /* FAN3リレー累積ON回数 */
    rd_TA,               /* TAリレー累積ON回数 */
    rd_SV1,              /* SV1リレー累積ON回数 */
    rd_SV2,              /* SV2リレー累積ON回数 */
    rd_SV3,              /* SV3リレー累積ON回数 */
    rd_SV4,              /* SV4リレー累積ON回数 */
    rd_CPC,              /* CPCリレー累積ON回数 */
    rd_HG1,              /* HG1リレー累積ON回数 */
    rd_DM1,              /* DM1リレー累積ON回数 */
    rd_DM2,              /* DM2リレー累積ON回数 */
    rd_DM3,              /* DM3リレー累積ON回数 */
    rd_LA,               /* LAリレー累積ON回数 */
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rd_t_left_A0067,     /* 冷却不良判定残り時間(A0067) */
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rd_t_joso,           /* 除霜タイマ */
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rd_t_delay_reizou,   /* 冷蔵ファン遅延タイマ */
    rdyaku,              /* 予約　*/
    rd_t_sw_H1_H2,       /* H1,H2(加熱)ヒータ出力切替えタイマ */
    rdyaku,              /* 予約　*/
    rd_t_sw_SV1,         /* SV1出力切替えタイマ */
    rd_t_sw_SV2,         /* SV2出力切替えタイマ */
    rd_t_sw_SV3,         /* SV3出力切替えタイマ */
    rd_t_sw_FAN1,        /* FAN1出力切替えタイマ */
    rd_t_sw_FAN2,        /* FAN2出力切替えタイマ */
    rd_t_sw_FAN3,        /* FAN3出力切替えタイマ */
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rd_t_sw_wait,        /* 制御開始するまでウエイトタイマ */
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rdyaku,              /* 予約　*/
    rd_rom,              /* ROM番号*/
    rdgaibuinput,        /* 外部入力 */
    rd_t_kanetu_strong,  /* 加熱強ON時間 */
    rd_t_kanetu_low,     /* 加熱弱ON時間 */
    rd_t_kashitu_strong, /* 加湿強ON時間 */
    rd_t_kashitu_low,    /* 加湿弱ON時間 */
    rd_ver               /* バージョン番号 */
};
void host_maintenaceR_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = PH_DUMMY; /* dummy */
}

void host_read_maintenaceR_data(void)
{
    host_maintenaceR_make_phase(uartp->base_addr);
    if (uartp->commitem < sizeof(host_r_maintenaceR_tbl) / 4)
    {
        (*host_r_maintenaceR_tbl[uartp->commitem])();
    }
    else
    {
        rdnone();
    }
}

void host_write_maintenaceR_data(void)
{
    host_maintenaceR_make_phase(uartp->base_addr);
    wrnone();
}
