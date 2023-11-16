/*
 * p_comm_fhost_joso.c
 *
 *  Created on: 2023/06/27
 *      Author: VINH-NT
 */

/* 対HOST-JOSOエリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"

const FTBLV host_r_joso_tbl[] = {
    rdcomm, /* 除霜方式 */
    rdcomm, /* 除霜開始時刻1 */
    rdcomm, /* 除霜開始時刻2 */
    rdcomm, /* 除霜開始時刻3 */
    rdcomm, /* 除霜開始時刻4 */
    rdcomm, /* 除霜開始時刻5 */
    rdcomm, /* 除霜開始時刻6 */
    rdcomm, /* 除霜開始時刻7 */
    rdcomm, /* 除霜開始時刻8 */
    rdcomm, /* 除霜開始時刻9 */
    rdcomm  /* 除霜開始時刻10 */
};
const uint16_t disp_phase_joso_tbl[] = {
    PH_JOSOUHOUSHIKI,   /* 除霜方式 */
    PH_JOSOUSTARTTIME1, /* 除霜開始時刻1 */
    PH_JOSOUSTARTTIME2, /* 除霜開始時刻2 */
    PH_JOSOUSTARTTIME3, /* 除霜開始時刻3 */
    PH_JOSOUSTARTTIME4, /* 除霜開始時刻4 */
    PH_JOSOUSTARTTIME5, /* 除霜開始時刻5 */
    PH_JOSOUSTARTTIME6, /* 除霜開始時刻6 */
    PH_JOSOUSTARTTIME7, /* 除霜開始時刻7 */
    PH_JOSOUSTARTTIME8, /* 除霜開始時刻8 */
    PH_JOSOUSTARTTIME9, /* 除霜開始時刻9 */
    PH_JOSOUSTARTTIME10 /* 除霜開始時刻10 */
};

const FTBLV host_w_joso_tbl[] = {
    wrcomm, /* 除霜方式 */
    wrcomm, /* 除霜開始時刻1 */
    wrcomm, /* 除霜開始時刻2 */
    wrcomm, /* 除霜開始時刻3 */
    wrcomm, /* 除霜開始時刻4 */
    wrcomm, /* 除霜開始時刻5 */
    wrcomm, /* 除霜開始時刻6 */
    wrcomm, /* 除霜開始時刻7 */
    wrcomm, /* 除霜開始時刻8 */
    wrcomm, /* 除霜開始時刻9 */
    wrcomm  /* 除霜開始時刻10 */
};

void disp_joso_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    if (uartp->commitem < sizeof(disp_phase_joso_tbl)/2)
    {
        uartp->phase = disp_phase_joso_tbl[uartp->id];
    }
    else
    {
        uartp->phase = PH_DUMMY; /* dummy */
    }
}

void host_read_joso_data(void)
{
    disp_joso_make_phase(uartp->base_addr); /* 対表示器共通 */
    if (uartp->commitem < sizeof(host_r_joso_tbl)/4)
    {
        (*host_r_joso_tbl[uartp->commitem])();
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
void host_write_joso_data(void)
{
    disp_joso_make_phase(uartp->base_addr); /* 対表示器共通 */

    if (uartp->commitem < sizeof(host_w_joso_tbl)/4)
    {
        if (host_write_status_check(uartp->erea))
        {
            (*host_w_joso_tbl[uartp->commitem])();
        }
    }
    else
    {
        wrnone();
    }
}
