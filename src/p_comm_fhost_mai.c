/*
 * p_comm_fhost_mai.c
 *
 *  Created on: 2023/07/20
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"

int16_t rd_factory_mode_sub(void)
{
    int16_t data = MD_STANDBY;

    switch (KEY_MODE.flg_mode)
    {
    case FACTRYMD:
        data = MD_FACT;
        break;
    }
    return data;
}
void rd_factory_mode(void)
{ /* モード切替 */
    comret_dt(rd_factory_mode_sub());
}
void rd_factory_output(void)
{ /* ファクトリモード出力ON番号 */
    if (KEY_MODE.flg_mode == FACTRYMD || KEY_MODE.flg_mode == SELFMD)
    {
        comret_dt(FACT_DATA.out_mode);
    }
    else
    {
        rdyaku();
    }
}
const FTBLV host_r_maintenace_tbl[] = {
    rd_factory_mode,
    rd_factory_output,
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
void wr_factory_mode(void) /* モード切替 */
{
    int16_t data = 0;
    data = cmkdat();
    switch (data)
    {
    case MD_STANDBY:
        if (KEY_MODE.flg_mode == FACTRYMD || KEY_MODE.flg_mode == SELFMD)
        {
            /* チェックモードから戻った場合、全て出力をOFFしておく */
            turnof_all_output();
        }
        nextmodeclr(STANDBYMD);
        break;
    case MD_FACT:
        FACT_DATA.out_mode = 0;
        nextmodeclr(FACTRYMD);
        break;
    default:
        wrnak3();
        break;
    }
}
void wr_factory_output(void) /* ファクトリモード出力ON番号 */
{
    int16_t data = 0;

    data = cmkdat();
    if (KEY_MODE.flg_mode == SELFMD)
    {
        /* 自己診断では全て出力設定できるように巣する */
        if (limit_check(0, SELF_OUT_NUMBER, data))
        {
            FACT_DATA.out_mode = data;
        }
        else
        { /* Bitで任意設定 */
            wrnak3();
        }
    }
    else
    {
        if (KEY_MODE.flg_mode == FACTRYMD)
        {
            if (limit_check(0, 26, data))
            {
                FACT_DATA.out_mode = data;
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
}
const FTBLV host_w_maintenace_tbl[] = {
    wr_factory_mode,   /* モード切替 */
    wr_factory_output, /* ファクトリモード出力ON番号 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku,            /* 予約 */
    wryaku             /* 予約 */
};
/*------------------------------------------------- */
void host_maintenace_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = PH_DUMMY; /* dummy */
}
void host_read_maintenace_data(void)
{
    host_maintenace_make_phase(uartp->base_addr);
    if (uartp->commitem < sizeof(host_r_maintenace_tbl) / 4)
    {
        (*host_r_maintenace_tbl[uartp->commitem])();
    }
    else
    {
        rdnone();
    }
}
void host_write_maintenace_data(void)
{
    host_maintenace_make_phase(uartp->base_addr);
    if (host_write_status_check(uartp->erea))
    {
        if (uartp->commitem < sizeof(host_w_maintenace_tbl) / 4)
        {
            (*host_w_maintenace_tbl[uartp->commitem])();
        }
        else
        {
            wrnone();
        }
    }
}
