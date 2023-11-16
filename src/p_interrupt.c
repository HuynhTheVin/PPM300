/*
 * p_interrupt.c
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#define EXTERN extern

#include "PPM.h"
#include "p_interrupt.h"

void SCI0_rx_interrupt(void) // SCI0 RX Interrupt
{
    // FE,PE,ORER発生時は r_Config_SCI1_receiveerror_interrupt()にてフラグクリアを別途行なっているので受信データは破棄される
    if (COMM0.cflg.bitms.protocol == EPRO_RTU)
    {
        rx0_rtu(SCI0.RDR);
    }
    else
    {
        rx0_shinko(SCI0.RDR);
    }
}

void SCI0_tx_interrupt(void) // SCI0 TX Interrupt
{
    if (COMM0.cflg.bitms.protocol == EPRO_RTU)
    {
        tx0_rtu();
    }
    else
    {
        tx0_shinko();
    }
}

void SCI1_rx_interrupt(void) // SCI1 RX Interrupt
{
    // FE,PE,ORER発生時は r_Config_SCI1_receiveerror_interrupt()にてフラグクリアを別途行なっているので受信データは破棄される
    rx1_rtu(SCI1.RDR);
}

void SCI1_tx_interrupt(void) // SCI1 TX Interrupt
{
    tx1_rtu();
}

void SCI12_rx_interrupt(void) // SCI12 RX Interrupt
{
    // FE,PE,ORER発生時は r_Config_SCI1_receiveerror_interrupt()にてフラグクリアを別途行なっているので受信データは破棄される
    rx12_rtu(SCI12.RDR);
}

void SCI12_tx_interrupt(void) // SCI12 TX Interrupt
{
    tx12_rtu();
}

void ext_wdt_reset(void)
{ /*外部WDT処理*/ /*x220322-2*/
    if (IO_WDT_ONQ)
    {
        IO_WDT_OFF;
    }
    else
    {
        IO_WDT_ON;
    }
}

void wdtchk(void)
{
    ext_wdt_reset();
    if (++wdtcou1 < 1000)
    {                            /* 1秒 */
        R_Config_IWDT_Restart(); // WDTカウンタリセット
    }
    else
    {
        // ここでソフトウェアリセット実行する
        SYSTEM.PRCR.WORD = 0xA502; // PRCR.PRC1 = 1;
        SYSTEM.SWRR = 0xA501;      // ソフトウェアリセットコマンド
    }
}
/* CMT0 Interrupt ----------------------------------------------------------------------*/
void timer_cmt0_interrupt(void)
{
    if (--TIMDT.iw5 <= 0) /* 1/1000秒経過処理 */
    {
        TIMDT.iw5 = INTTIM2;
        adc(); /* センサ入力 */
        if (--TIMDT.iw1000m == 0)
        { /* 1秒経過処理 */
            TIMDT.iw1000m = INTTIM;
            systm1sec();
        }
        if (--TIMDT.tasktm == 0)
        {
            CNT_STAT.cf3_flg.bitms.main_task_request_flag = 1; /* 要求フラグセット */
            TIMDT.tasktm = 2;                                  /* 2msec            */
        }
        if (--TIMDT.t025s <= 0)
        {
            CNT_STAT.cf2_flg.bitms.current_time_capture_flag = 1; /*  現在時刻取り込みフラグ */
            TIMDT.t025s = INTTIM / 4;                             /* 250 msec  */
            TIMDT.m250ms = true;
            systm250msec();
        }
        if (TIMDT.cpt3stim)
        {
            --TIMDT.cpt3stim; /* CPT異常入力3秒遅延ﾀｲﾏｰ*/
        }
        wdtchk();
    }
}

/* TMR0 Interrupt */
void tmr0_interrupt(void)
{              /* 100us */
    rtu0_35(); /* 3.5キャラクタ */
    rtu1_35(); /* 3.5キャラクタ */

    uart0_tx_start();  /* フレーム送信開始 */
    uart1_tx_start();  /* フレーム送信開始 */
    uart12_tx_start(); /* フレーム送信開始 */
}
