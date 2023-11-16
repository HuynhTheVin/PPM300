/*
 * p_comm0.c
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.h"
#include "p_comm0.h"

//@see SCI0.SMR.BYTE in Config_SCI0
// CKS= PCKL/4 = 32M/4
// BBR= (32M/4)/38400/16-1 = 12 0x0CU
/* 9600 19200 38400 */
const uint8_t BRR0_TBL[] = {0x33U, 0x1AU, 0x0CU};

int16_t get_speed_uart0(void)
{
    int16_t sp = get_fram2(NEPDATA99);

    if (sp == 0)
    {
        return ESP_9600;
    }
    if (sp == 1)
    {
        return ESP_19200;
    }
    return ESP_38400;
}
int16_t get_device_uart0(void)
{
    int16_t sp = get_fram2(NEPDATA98);
    if(CNT_STAT.sys_flg.bitms.e_eeprom)
    {
       return 1;
    }
    else
    {
        if (sp == 0)
        {
            return ESP_9600;
        }
        if (sp == 1)
        {
            return ESP_19200;
        }
        return ESP_38400;
    }
}
void get_parity_uart0(void)
{
   int16_t sp = get_fram2(NEPDATA100);

   if (sp == 0)
   {
       SCI0.SMR.BIT.PE = _00_SCI_PARITY_DISABLE;
   }
   else if (sp == 1)
   {
       SCI0.SMR.BIT.PE = _20_SCI_PARITY_ENABLE;
       SCI0.SMR.BIT.PM = _00_SCI_PARITY_EVEN;
   }
   else
   {
       SCI0.SMR.BIT.PE = _20_SCI_PARITY_ENABLE;
       SCI0.SMR.BIT.PM = _10_SCI_PARITY_ODD;
   }
}
void get_stopbit_uart0(void)
{
   int16_t sp = get_fram2(NEPDATA101);
   if (sp == 0)
   {
       SCI0.SMR.BIT.STOP = _00_SCI_STOP_1;
   }
   else
   {
       SCI0.SMR.BIT.STOP = _08_SCI_STOP_2;
   }
}
void start_uart0(void)
{
    if (uartp->cflg.bitms.enable_internal_cmd != 1)
    {
        // COMM0.set_protocol = CNT_STAT.sys_flg.bitms.e_eeprom ? EPRO_RTU : get_protocol_uart0();
        COMM0.set_protocol = EPRO_RTU;
        COMM0.set_device = get_device_uart0();
        //COMM0.set_device = CNT_STAT.sys_flg.bitms.e_eeprom ? 1 : get_fram2(NEPDATA98);
        COMM0.set_speed = CNT_STAT.sys_flg.bitms.e_eeprom ? ESP_38400 : get_speed_uart0();
        // COMM0.set_databit = CNT_STAT.sys_flg.bitms.e_eeprom ? 8 : get_databit_uart0();
        COMM0.cflg.bitms.protocol = EPRO_RTU;
        get_parity_uart0();
        get_stopbit_uart0();
        /* Set bit rate */
        SCI0.BRR = BRR0_TBL[COMM0.set_speed];
    }
    else
    {
        COMM0.set_device = 0;
        COMM0.set_speed = ESP_9600;
        COMM0.set_databit = 7;
        COMM0.set_protocol = EPRO_SHINKO;
        COMM0.cflg.bitms.protocol = EPRO_SHINKO;
        COMM0.cflg.bitms.enable_internal_cmd = 1;
        SCI0.SMR.BIT.PE = _20_SCI_PARITY_ENABLE;
        SCI0.SMR.BIT.PM = _00_SCI_PARITY_EVEN;
        SCI0.SMR.BIT.STOP = _00_SCI_STOP_1;
        SCI0.SMR.BIT.CHR = _40_SCI_DATA_LENGTH_7;
        SCI0.BRR = BRR0_TBL[COMM0.set_speed];
    }
    SCI0.SCR.BIT.RIE = 1U;
    SCI0.SCR.BIT.RE = 1U;
    R_Config_SCI0_Start();
}

void rx0_shinko(uint8_t dt)
{
    if (COMM0.set_databit == 7)
    {
        dt &= 0x7F;
    }
    if (dt == ETX)
    { /* RS-485の場合は自機ETX受信でドライバOFFとする*/
        COMM0.cflg.bitms.sending = 0;
    }

    if (COMM0.cflg.bitms.sending == 0)
    { /* 自器応答コマンドは未処理とする  */
        if (dt == STX)
        {
            COMM0.rxpo = 1;
            COMM0.rxbff[0] = dt;
            COMM0.flg_rx = RXHEAD;
        }
        else if (COMM0.flg_rx == RXHEAD && COMM0.rxpo < BFCAP_RX_MAX)
        {
            COMM0.rxbff[COMM0.rxpo++] = dt;
            if (dt == ETX)
            {
                COMM0.flg_rx = RXDELIMIT;
                if ((COMM0.rxbff[1] != (DEVISNO + COMM0.set_device)) && (COMM0.rxbff[1] != 0x7F))
                {                         /* 機器番号判定を割り込みで行う */
                    COMM0.flg_rx = RXCLR; /* 対象外は無効とする           */
                }
            }
        }
        else if (COMM0.flg_rx != RXDELIMIT)
        {
            COMM0.flg_rx = RXCLR;
        }
    }
}
void tx0_shinko(void)
{
    if (COMM0.txbff[COMM0.txpo - 1] == ETX)
    {
        SCI0.SCR.BIT.TIE = 0U; /* Transmission disabled */
        SCI0.SCR.BIT.TEIE = 1U;
        //      COMM0.txwie = txwietbl[COMM0.set_speed];  // TEIE:送信終了割込みでLEDと485ゲートをOFFする
        COMM0.cflg.bitms.sending = 0;
    }
    else
    {
        SCI0.TDR = COMM0.txbff[COMM0.txpo++];
    }
}

void rx0_rtu(uint8_t dt)
{
    if (IO_OUT_RS485_DISPLAY_ONQ)
    { /* RS-485の場合は自機ETX受信でドライバOFFとする */
        if (++COMM0.rxcn >= COMM0.flg_txlen)
        {
            IO_OUT_RS485_DISPLAY_OFF; /* RS-485 drive OFF */
            COMM0.flg_rx = RXCLR;
            COMM0.cflg.bitms.sending = 0;
        }
        return;
    }
    if (COMM0.cflg.bitms.sending == 0)
    { /* 自器応答コマンドは未処理とする */
        if (COMM0.flg_rx == RXCLR)
        {
            COMM0.rxpo = 1;
            COMM0.rxbff[0] = dt;
            COMM0.flg_rx = RXHEAD;
            COMM0.modtim = mrtuwitbl[COMM0.set_speed];
        }
        else if (COMM0.flg_rx == RXHEAD && COMM0.rxpo < BFCAP_RX_MAX)
        {
            COMM0.rxbff[COMM0.rxpo++] = dt;
            COMM0.modtim = mrtuwitbl[COMM0.set_speed];
        }
        else if (COMM0.flg_rx != RXDELIMIT)
        {
            COMM0.flg_rx = RXCLR;
        }
    }
}

void tx0_rtu(void)
{
    if (COMM0.txpo >= COMM0.flg_txlen)
    {
        SCI0.SCR.BIT.TIE = 0U; /* Transmission disabled */
        SCI0.SCR.BIT.TEIE = 1U;
        //      COMM0.txwie = txwietbl[COMM0.set_speed];  // TEIE:送信終了割込みでLEDと485ゲートをOFFする
        COMM0.cflg.bitms.sending = 0;
    }
    else
    {
        SCI0.TDR = COMM0.txbff[COMM0.txpo++];
    }
}

void rtu0_35(void)
{
    if (COMM0.modtim)
    {
        if ((--COMM0.modtim) == 0)
        {
            if ((COMM0.rxbff[0] != COMM0.set_device) && (COMM0.rxbff[0] != 0))
            {                         /* 機器番号判定を割り込みで行う*/
                COMM0.flg_rx = RXCLR; /* 対象外は無効とする */
            }
            else
            {
                COMM0.flg_rx = RXDELIMIT;
            }
        }
    }
}

void uart0_tx_start(void)
{
    if (COMM0.txwis)
    {
        if ((--COMM0.txwis) == 0)
        {
            SCI0.SCR.BIT.TIE = 1U; // Transmission enabled
            SCI0.SCR.BIT.TE = 1U;
            COMM0.cflg.bitms.sending = 1;
        }
    }
}
