/*
 * p_comm1.c
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */
/* 対表示器 */
/* MODBUS-RTU No1 38400 8E1 */

#define EXTERN extern
#include "PPM.h"
#include "p_comm1.h"

void start_uart1(void){

    COMM1.set_device = 1;
    COMM1.set_speed = ESP_38400;
    COMM1.set_protocol = EPRO_RTU;
    COMM1.cflg.bitms.protocol = EPRO_RTU;

    SCI1.SCR.BIT.RIE = 1U;
    SCI1.SCR.BIT.RE = 1U;
    R_Config_SCI1_Start();

}

void rx1_rtu(uint8_t dt){
    if(IO_OUT_RS485_DISPLAY_ONQ){  /* RS-485の場合は自機ETX受信でドライバOFFとする */
        if (++COMM1.rxcn >= COMM1.flg_txlen){
            IO_OUT_RS485_DISPLAY_OFF;  /* RS-485 drive OFF */
            COMM1.flg_rx = RXCLR;
            COMM1.cflg.bitms.sending = 0;
        }
        return;
    }
    if(COMM1.cflg.bitms.sending == 0){  /* 自器応答コマンドは未処理とする */
        if(COMM1.flg_rx == RXCLR){
            COMM1.rxpo = 1;
            COMM1.rxbff[0] = dt;
            COMM1.flg_rx = RXHEAD;
            COMM1.modtim = mrtuwitbl[COMM1.set_speed];
        }else if (COMM1.flg_rx == RXHEAD  && COMM1.rxpo < BFCAP_RX_MAX){
            COMM1.rxbff[COMM1.rxpo++] = dt;
            COMM1.modtim = mrtuwitbl[COMM1.set_speed];
        }else if(COMM1.flg_rx != RXDELIMIT){
            COMM1.flg_rx = RXCLR;
        }
    }
}

void tx1_rtu(void){
    if (COMM1.txpo >= COMM1.flg_txlen){
        SCI1.SCR.BIT.TIE = 0U; /* Transmission disabled */
        SCI1.SCR.BIT.TEIE = 1U;
//      COMM1.txwie = txwietbl[COMM1.set_speed];  // TEIE:送信終了割込みでLEDと485ゲートをOFFする
        COMM1.cflg.bitms.sending = 0;
    }else{
        SCI1.TDR = COMM1.txbff[COMM1.txpo++];
    }
}

void rtu1_35(void){
    if(COMM1.modtim){
        if((--COMM1.modtim)==0){
            if ((COMM1.rxbff[0] != COMM1.set_device)&&(COMM1.rxbff[0] != 0)){  /* 機器番号判定を割り込みで行う*/
                COMM1.flg_rx = RXCLR;  /* 対象外は無効とする */
            }else{
                COMM1.flg_rx = RXDELIMIT;
            }
        }
    }
}

void uart1_tx_start(void){
    if(COMM1.txwis){
        if ((--COMM1.txwis)==0){
            SCI1.SCR.BIT.TIE = 1U; // Transmission enabled
            SCI1.SCR.BIT.TE = 1U;
            COMM1.cflg.bitms.sending = 1;
        }
    }
}
