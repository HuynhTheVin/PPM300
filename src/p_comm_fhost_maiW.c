/*
 * p_comm_fhost_maiW.c
 *
 *  Created on: 2023/06/28
 *      Author: VINH-NT
 */
/* 対HOST-MAINTENANCE READ エリア */

#define EXTERN extern
#include "PPM.H"
#include "p_comm_fhost.h"
/**
 * @brief DHHリレー累積ON回数クリア
 *
 */
void wr_clr_DHH(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT1L, 0);
        put_fram2(NERYCNT1H, 0);
        SET_PARA.rycnt[0] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief DHリレー累積ON回数クリア
 *
 */
void wr_clr_DH(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT2L, 0);
        put_fram2(NERYCNT2H, 0);
        SET_PARA.rycnt[1] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief FAN1リレー累積ON回数クリア
 *
 */
void wr_clr_FAN1(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT3L, 0);
        put_fram2(NERYCNT3H, 0);
        SET_PARA.rycnt[2] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief FAN2リレー累積ON回数クリア
 *
 */
void wr_clr_FAN2(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT4L, 0);
        put_fram2(NERYCNT4H, 0);
        SET_PARA.rycnt[3] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief FAN3リレー累積ON回数クリア
 *
 */
void wr_clr_FAN3(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT5L, 0);
        put_fram2(NERYCNT5H, 0);
        SET_PARA.rycnt[4] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief TAリレー累積ON回数クリア
 *
 */
void wr_clr_TA(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT6L, 0);
        put_fram2(NERYCNT6H, 0);
        SET_PARA.rycnt[5] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief SV1リレー累積ON回数クリア
 *
 */
void wr_clr_SV1(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT7L, 0);
        put_fram2(NERYCNT7H, 0);
        SET_PARA.rycnt[6] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief SV2リレー累積ON回数クリア
 *
 */
void wr_clr_SV2(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT8L, 0);
        put_fram2(NERYCNT8H, 0);
        SET_PARA.rycnt[7] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief SV3リレー累積ON回数クリア
 *
 */
void wr_clr_SV3(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT9L, 0);
        put_fram2(NERYCNT9H, 0);
        SET_PARA.rycnt[8] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief SV4リレー累積ON回数クリア
 *
 */
void wr_clr_SV4(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT10L, 0);
        put_fram2(NERYCNT10H, 0);
        SET_PARA.rycnt[9] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief CPCリレー累積ON回数クリア
 *
 */
void wr_clr_CPC(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT11L, 0);
        put_fram2(NERYCNT11H, 0);
        SET_PARA.rycnt[10] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief HG1リレー累積ON回数クリア
 *
 */
void wr_clr_HG1(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT12L, 0);
        put_fram2(NERYCNT12H, 0);
        SET_PARA.rycnt[11] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief DM1リレー累積ON回数クリア
 *
 */
void wr_clr_DM1(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT13L, 0);
        put_fram2(NERYCNT13H, 0);
        SET_PARA.rycnt[12] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief DM2リレー累積ON回数クリア
 *
 */
void wr_clr_DM2(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT14L, 0);
        put_fram2(NERYCNT14H, 0);
        SET_PARA.rycnt[13] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief DM3リレー累積ON回数クリア
 *
 */
void wr_clr_DM3(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT15L, 0);
        put_fram2(NERYCNT15H, 0);
        SET_PARA.rycnt[14] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
/**
 * @brief LAリレー累積ON回数クリア
 *
 */
void wr_clr_LA(void)
{
    switch (cmkdat())
    {
    case 1:
        put_fram2(NERYCNT16L, 0);
        put_fram2(NERYCNT16H, 0);
        SET_PARA.rycnt[15] = 0;
        wryaku(); /* どんな状態でもACK */
        break;
    default:
        wrnak3();
        break;
    }
}
const FTBLV host_w_maintenaceW_tbl[] = {
    wr_clr_DHH,  /* DHHリレー累積ON回数クリア */
    wr_clr_DH,   /* DHリレー累積ON回数クリア */
    wr_clr_FAN1, /* FAN1リレー累積ON回数クリア */
    wr_clr_FAN2, /* FAN2リレー累積ON回数クリア */
    wr_clr_FAN3, /* FAN3リレー累積ON回数クリア */
    wr_clr_TA,   /* TAリレー累積ON回数クリア */
    wr_clr_SV1,  /* SV1リレー累積ON回数クリア */
    wr_clr_SV2,  /* SV2リレー累積ON回数クリア */
    wr_clr_SV3,  /* SV3リレー累積ON回数クリア */
    wr_clr_SV4,  /* SV4リレー累積ON回数クリア */
    wr_clr_CPC,  /* CPCリレー累積ON回数クリア */
    wr_clr_HG1,  /* HG1リレー累積ON回数クリア */
    wr_clr_DM1,  /* DM1リレー累積ON回数クリア */
    wr_clr_DM2,  /* DM2リレー累積ON回数クリア */
    wr_clr_DM3,  /* DM3リレー累積ON回数クリア */
    wr_clr_LA,   /* LAリレー累積ON回数クリア */
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku,      /* 予約　*/
    wryaku       /* 予約　*/
};
/*------------------------------------------------- */
void host_maintenaceW_make_phase(uint16_t base_addr)
{
    uartp->id = base_addr;
    uartp->commitem = base_addr;
    uartp->phase = PH_DUMMY; /* dummy */
}
void host_read_maintenaceW_data(void)
{
    host_maintenaceW_make_phase(uartp->base_addr);
    rdnone();
}
void host_write_maintenaceW_data(void)
{
    host_maintenaceW_make_phase(uartp->base_addr);
    if (uartp->commitem < sizeof(host_w_maintenaceW_tbl) / 4)
    {
        (*host_w_maintenaceW_tbl[uartp->commitem])();
    }
    else
    {
        wrnone();
    }
}
