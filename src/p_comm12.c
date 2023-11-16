/*
 * p_comm12.c
 *
 *  Created on: 2023/06/22
 *      Author: VINH-NT
 */
/* 対HOST(工場) */
/* SHINKO No0 9600 7E1 */

#define EXTERN extern
#include "PPM.H"
#include "p_comm12.h"

void start_uart12(void){

    COMM12.set_device = 1;
    COMM12.set_speed = ESP_19200;
    COMM12.set_protocol = EPRO_RTU;
    COMM12.cflg.bitms.protocol = EPRO_RTU; 
    COMM12.cflg.bitms.enable_internal_cmd = 1;
    SCI12.SCR.BIT.RIE = 1U;
    SCI12.SCR.BIT.RE = 1U;
    R_Config_SCI12_Start();
}

void rx12_shinko(uint8_t dt){
    if(COMM12.set_databit==7){
        dt &= 0x7F;
    }
    if (dt == ETX) {  /* RS-485の場合は自機ETX受信でドライバOFFとする*/
        COMM12.cflg.bitms.sending = 0;
    }

    if(COMM12.cflg.bitms.sending == 0){   /* 自器応答コマンドは未処理とする  */
        if (dt == STX) {
            COMM12.rxpo = 1;
            COMM12.rxbff[0] = dt;
            COMM12.flg_rx = RXHEAD;
        }else if (COMM12.flg_rx == RXHEAD  && COMM12.rxpo < BFCAP_RX_MAX){
            COMM12.rxbff[COMM12.rxpo++] = dt;
            if (dt == ETX){
                COMM12.flg_rx = RXDELIMIT;
                if ((COMM12.rxbff[1] != (DEVISNO+COMM12.set_device)) && (COMM12.rxbff[1] != 0x7F)) { /* 機器番号判定を割り込みで行う */
                    COMM12.flg_rx = RXCLR;                                                         /* 対象外は無効とする           */
                }
            }
        }else if(COMM12.flg_rx != RXDELIMIT){
            COMM12.flg_rx = RXCLR;
        }
    }
}
void tx12_shinko(void){
    if (COMM12.txbff[COMM12.txpo-1] == ETX){
        SCI12.SCR.BIT.TIE = 0U;  /* Transmission disabled */
        SCI12.SCR.BIT.TEIE = 1U;
//      COMM12.txwie = txwietbl[COMM12.set_speed];  // TEIE:送信終了割込みでLEDと485ゲートをOFFする
        COMM12.cflg.bitms.sending = 0;
    }else{
        SCI12.TDR = COMM12.txbff[COMM12.txpo++];
    }
}


void rx12_rtu(uint8_t dt){
    // if(IO_OUT_RS485_xx_ONQ){  /* RS-485の場合は自機ETX受信でドライバOFFとする */
    //     if (++COMM12.rxcn >= COMM12.flg_txlen){
    //         IO_OUT_RS485_xx_OFF;  /* RS-485 drive OFF */
    //         COMM12.flg_rx = RXCLR;
    //         COMM12.cflg.bitms.sending = 0;
    //     }
    //     return;
    // }
    if(COMM12.cflg.bitms.sending == 0){  /* 自器応答コマンドは未処理とする */
        if(COMM12.flg_rx == RXCLR){
            COMM12.rxpo = 1;
            COMM12.rxbff[0] = dt;
            COMM12.flg_rx = RXHEAD;
            COMM12.modtim = mrtuwitbl[COMM12.set_speed];
        }else if (COMM12.flg_rx == RXHEAD  && COMM12.rxpo < BFCAP_RX_MAX){
            COMM12.rxbff[COMM12.rxpo++] = dt;
            COMM12.modtim = mrtuwitbl[COMM12.set_speed];
        }else if(COMM12.flg_rx != RXDELIMIT){
            COMM12.flg_rx = RXCLR;
        }
    }
}

void tx12_rtu(void){
    if (COMM12.txpo >= COMM12.flg_txlen){
        SCI12.SCR.BIT.TIE = 0U; /* Transmission disabled */
        SCI12.SCR.BIT.TEIE = 1U;
//      COMM12.txwie = txwietbl[COMM12.set_speed];  // TEIE:送信終了割込みでLEDと485ゲートをOFFする
        COMM12.cflg.bitms.sending = 0;
    }else{
        SCI12.TDR = COMM12.txbff[COMM12.txpo++];
    }
}

void rtu12_35(void){
    if(COMM12.modtim){
        if((--COMM12.modtim)==0){
            if ((COMM12.rxbff[0] != COMM12.set_device)&&(COMM12.rxbff[0] != 0)){  /* 機器番号判定を割り込みで行う*/
                COMM12.flg_rx = RXCLR;  /* 対象外は無効とする */
            }else{
                COMM12.flg_rx = RXDELIMIT;
            }
        }
    }
}

void uart12_tx_start(void){
    if(COMM12.txwis){  
        if ((--COMM12.txwis)==0){
            SCI12.SCR.BIT.TIE = 1U; // Transmission enabled
            SCI12.SCR.BIT.TE = 1U;
            PORT1.PMR.BIT.B1 = 1U;
            COMM12.cflg.bitms.sending = 1;
        }
    }
}