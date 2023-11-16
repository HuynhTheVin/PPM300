/*
 * p_startup.c
 *
 *  Created on: 2023/05/29
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.h"
#include "p_startup.h"

/********************
 * Eeprom の初期化   *
 *********************/
void rdsramajs(void)
{

    BYTE i;
    uint16_t *p;

    p = (uint16_t *)&IN_AJUST.systemid0;
    i = ESYSTEM_ID0;
    do
    {
        *p++ = get_fram2(i); /* 調整値 読取り */
    } while (++i < CNTRL1);
}

void rdsram(void)
{
    WORD i;
    int16_t *p;

    // WORD st;
    // WORD endprg;
    // st = SET_PARA.flg_ckstep;
    // endprg = SET_PARA.flg_endprg;

    /* パラメータ */
    p = &SET_PARA.setpara[0];
    i = NEPDATA0;
    do
    {
        *p++ = get_fram2(i); /* 設定値 読取り */
    } while (++i < CNTRL2);
    /* ダイレクトとその他 */
    p = &SET_PARA.nerrcode01;
    i = NECHECKD01NO;
    do
    {
        *p++ = get_fram2(i); /* 設定値 読取り */
    } while (++i < CNTRL3);

    INPUT_ADC.wksens[0] = get_fram2(NEPDATA203); /* マルチ入力レンジ選択 */
    INPUT_ADC.wksens[1] = get_fram2(NEPDATA204); /* マルチ入力レンジ選択 */
    INPUT_ADC.wksens[2] = get_fram2(NEPDATA205); /* マルチ入力レンジ選択 */
}

void chk_harware_fram(void)
{
    if (get_fram2(ESYSTEM_ID2) != (WORD)MPBANGOU0)
    {
        put_fram2(ESYSTEM_ID2, MPBANGOU0);
    }
    if (get_fram2(ESYSTEM_ID3) != (WORD)MPBANGOU1)
    {
        put_fram2(ESYSTEM_ID3, MPBANGOU1);
    }

    /* FRAMアクセス状態を確認する。FRAM故障異常フラグに反映する */
    CNT_STAT.sys_flg.bitms.e_hardware_eeprom =
    (get_fram2(ESYSTEM_ID2) != (WORD)MPBANGOU0 || get_fram2(ESYSTEM_ID3) != (WORD)MPBANGOU1) ? (1) : (0);
}

void chk_eeprom(void)
{
    CNT_STAT.alarm_flg2.bitms.al_eeprom = 0;
    CNT_STAT.sys_flg.bitms.e_eeprom = 0;
    if (get_fram2(CNTRL1) != (WORD)PASSDT1 || get_fram2(CNTRL2) != (WORD)PASSDT2 || get_fram2(CNTRL3) != (WORD)PASSDT3)
    {
        CNT_STAT.sys_flg.bitms.e_eeprom = 1; /* EEPROM Error flag set */
    }
    else
    {
        CNT_STAT.sys_flg.bitms.e_eeprom = 0;
    }
}

void iniram(void)
{
    WORD i = get_fram2(0);    /* dummy to correct level   */
    TIMDT.tasktm = 2;         /* タスクリクエストタイマ 2ms           */
    TIMDT.iw = 24;            /* 0.125sec * 24 = 3000msec             */
    TIMDT.iw1000m = INTTIM;   /* 1秒ﾀｲﾏｰ初期化                        */
    TIMDT.t025s = INTTIM / 4; /* 1sec/4 = 250 msec        */

    chk_eeprom(); /* EEPROM Error flag set                */
    chk_harware_fram();
    rdsramajs(); /* EEPROM ajust data --> SRAM data copy */
    rdsram();    /* EEPROM set data --> SRAM data copy   */

    range_chk(); /* Range data setup                     */

    initADS1148A(); /* ADC初期化 */
    R_Config_MTU0_Start();
    rd_rtc(); /*RTC 読み取り*/

    CONTROL.holiday_num = get_data(PH_MEM1TIME);
    if(CONTROL.holiday_num == 0)
    {
        CNT_STAT.cfholiday_flg.bitms.reitou_unten_holiday0 == 0;
    }
    TIMDT.cunton_off[heatch] = 1;	/* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
    TIMDT.cunton_off[cooling] = 1;  /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */

    CNT_STAT.tenken_flg.bitms.power_outages = 1; /* 停電告知ｾｯﾄ */
    
    start_timer_r0();
    start_uart0();
    start_uart1();
}
