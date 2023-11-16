/*
 * p_comm_fhost_dir.c
 *
 *  Created on: 2023/06/27
 *      Author: VINH-NT
 */

/* 対HOST-DIRECTエリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"
void rdyear(void)
{
    comret_dt(SET_TIME.setyear + 2000);
}
void rdmonth(void)
{
    comret_dt(SET_TIME.setmonth);
}
void rdday(void)
{
    comret_dt(SET_TIME.setday);
}
void rdweek(void)
{
    comret_dt(SET_TIME.setweek);
}
void rdhour(void)
{
    comret_dt(SET_TIME.sethour);
}
void rdminute(void)
{
    comret_dt(SET_TIME.setmin);
}
void rdsecond(void)
{
    comret_dt(SET_TIME.setsec);
}
const FTBLV host_r_direct_tbl[] = {
    rdcomm, /* 休日日数 */
    rdcomm, /* 加熱動作有効/無効選択 */
    rdcomm, /* メモリ1　冷凍温度設定 */
    rdcomm, /* メモリ1　冷凍・冷蔵温度設定 */
    rdcomm, /* メモリ1切替り時刻設定 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku, /* 予約 */
    rdyaku  /* 予約 */
};
const uint16_t disp_phase_direct_tbl[] = {
    PH_NUMYASUMI,     /* 休日日数 */
    PH_KANETU,        /* 加熱動作有効/無効選択 */
    PH_MEM1REITOU,    /* メモリ1　冷凍温度設定 */
    PH_MEM1REITOUZOU, /* メモリ1　冷凍・冷蔵温度設定 */
    PH_MEM1TIME,      /* メモリ1切替り時刻設定 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY,         /* 予約 */
    PH_DUMMY          /* 予約 */
};
const FTBLV host_r_direct_time_tbl[] = {
    rdyear,   /* 西暦 */
    rdmonth,  /* 月 */
    rdday,    /* 日 */
    rdweek,   /* 曜日 */
    rdhour,   /* 時 */
    rdminute, /* 分 */
    rdsecond, /* 秒 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku,   /* 予約 */
    rdyaku    /* 予約 */
};
void wr_dir_holiday(void)
{
    int16_t data;

    data = cmkdat();
    if (limit_check(get_min(uartp->phase), get_max(uartp->phase), data))
    {
        set_data(uartp->phase, data);
        CONTROL.holiday_num = SET_PARA.dummy;
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wr_dir_kanetu(void)
{
    int16_t data;

    data = cmkdat();
    if (limit_check(get_min(uartp->phase), get_max(uartp->phase), data))
    {
        set_data(uartp->phase, data);
        switch (data)
        {
        case 0x0000:
            CNT_STAT.cfkanetu_flg.bitms.heating_active = 0;
            break;
        default:
            CNT_STAT.cfkanetu_flg.bitms.heating_active = 1;
            break;
        }
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wr_dir_sv_reitou(void)
{
    int16_t data;

    data = cmkdat();
    if (limit_check(get_min(uartp->phase), get_max(uartp->phase), data))
    {
        set_data(uartp->phase, data);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wr_dir_sv_reitouzou(void)
{
    int16_t data;

    data = cmkdat();
    if (limit_check(get_min(uartp->phase), get_max(uartp->phase), data))
    {
        set_data(uartp->phase, data);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wr_dir_time(void)
{
    int16_t data;

    data = cmkdat();
    if (limit_check(get_min(uartp->phase), get_max(uartp->phase), data))
    {
        set_data(uartp->phase, data);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wryear(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(2000, 2099, data))
    {

        wr_rtc(6, data - 2000);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
/* 西暦と日によって月が正しいかどうかチェック*/
BOOL checkmonth(int16_t data)
{
    int daysInMonth;
    if (data < 1 || data > 12)
    {
        return false;
    }
    if (data == 2)
    {
        if ((SET_TIME.setyear % 4 == 0 && SET_TIME.setyear % 100 != 0))
        {
            daysInMonth = 29;
        }
        else
        {
            daysInMonth = 28;
        }
    }
    else if (data == 4 || data == 6 || data == 9 || data == 11)
    {
        daysInMonth = 30;
    }
    else
    {
        daysInMonth = 31;
    }
    if (SET_TIME.setday > daysInMonth)
    {
        return false;
    }
    return true;
}
void wrmonth(void)
{
    int16_t data;
    data = cmkdat();
    if (checkmonth(data))
    {
        wr_rtc(5, data);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wrday(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(1, get_max_day(), data))
    {
        wr_rtc(4, data);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wrweek(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(0, 6, data))
    {
        wr_rtc(3, data);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wrhour(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(0, 24, data))
    {
        wr_rtc(2, data);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wrminute(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(0, 59, data))
    {
        wr_rtc(1, data);
        wr_rtc(0, 0);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
void wrsecond(void)
{
    int16_t data;
    data = cmkdat();
    if (limit_check(0, 59, data))
    {
        wr_rtc(0, data);
        wryaku();
    }
    else
    {
        wrnak3();
    }
}
const FTBLV host_w_direct_tbl[] = {
    wr_dir_holiday,      /* 休日日数 */
    wr_dir_kanetu,       /* 加熱動作有効/無効選択 */
    wr_dir_sv_reitou,    /* メモリ1　冷凍温度設定 */
    wr_dir_sv_reitouzou, /* メモリ1　冷凍・冷蔵温度設定 */
    wr_dir_time,         /* メモリ1　切替り時刻設定 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku,              /* 予約 */
    wryaku               /* 予約 */

};
const FTBLV host_w_direct_time_tbl[] = {
    wryear,   /* 西暦 */
    wrmonth,  /* 月 */
    wrday,    /* 日 */
    wrweek,   /* 曜日 */
    wrhour,   /* 時 */
    wrminute, /* 分 */
    wrsecond, /* 秒 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku,   /* 予約 */
    wryaku    /* 予約 */
};
void disp_direct_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    if (uartp->commitem < sizeof(disp_phase_direct_tbl) / 2)
    {
        uartp->phase = disp_phase_direct_tbl[uartp->id];
    }
    else
    {
        uartp->phase = PH_DUMMY; /* dummy */
    }
}
void disp_direct_time_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = PH_DUMMY; /* dummy */
}

void host_read_direct_data(void)
{
    disp_direct_make_phase(uartp->base_addr); /* 対表示器共通 */
    if (uartp->commitem < sizeof(host_r_direct_tbl) / 4)
    {
        (*host_r_direct_tbl[uartp->commitem])();
    }
    else
    {
        rdnone();
    }
}
/**
 * @brief 対ホスト：ダイレクトエリア項目の設定
 *
 *
 */
void host_write_direct_data(void)
{
    disp_direct_make_phase(uartp->base_addr); /* 対表示器共通 */

    if (uartp->commitem < sizeof(host_w_direct_tbl) / 4)
    {
        if (host_write_status_check(uartp->erea))
        {
            (*host_w_direct_tbl[uartp->commitem])();
        }
    }
    else
    {
        wrnone();
    }
}

void host_read_direct_time_data(void)
{
    disp_direct_time_make_phase(uartp->base_addr); /* 対表示器共通 */
    if (uartp->commitem < sizeof(host_r_direct_time_tbl) / 4)
    {
        (*host_r_direct_time_tbl[uartp->commitem])();
    }
    else
    {
        rdnone();
    }
}
/**
 * @brief 対ホスト：ダイレクトエリア項目の設定
 *
 *
 */
void host_write_direct_time_data(void)
{
    disp_direct_time_make_phase(uartp->base_addr); /* 対表示器共通 */

    if (uartp->commitem < sizeof(host_w_direct_time_tbl) / 4)
    {
        if (host_write_status_check(uartp->erea))
        {
            (*host_w_direct_time_tbl[uartp->commitem])();
        }
    }
    else
    {
        wrnone();
    }
}
