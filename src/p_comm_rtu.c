/*
 * p_comm_rtu.c
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.h"
#include "p_comm_rtu.h"


void mksendt_rtu(char *ap ,uint16_t cdt)
{
    *(ap++) = cdt >>8;
    uartp->flg_txlen++;
    *(ap++) = cdt;
    uartp->flg_txlen++;
}

void mksendt_1b_rtu(char *ap ,uint8_t cdt)
{
    *ap = cdt;
    uartp->flg_txlen++;
}

uint16_t getdt_rtu(uint8_t n)
{
    uint8_t i;
    uint16_t t=0;

    for (i=0;i<n;i++){
        t = (uint16_t)t*256+uartp->rxbff[uartp->flg_rxlen++];
    }
    return t;
}

uint16_t makecrc(uint8_t *p,uint16_t n)  
{
    uint16_t i,b;
    uint16_t sum;

    sum = 0xFFFF;
    for (i=0;i<n;i++) {
        sum ^= *p++;;
        for (b=0;b<8;b++) {
            if(sum & BN0){
                sum = (sum>>1) ^ 0xA001;
            }else{
                sum >>=1;
            }
        }
    } 
    return sum;
}

BOOL check_sum_rtu(void){
    uint8_t  sum_h, sum_l;
    uint16_t sumr;

    if(uartp->rxpo<2){
        return false;
    }
    sumr = makecrc(&uartp->rxbff[0],uartp->rxpo-2);
    sum_h = sumr >>8;        /* CRC-16 High byte */
    sum_l = sumr & 0xFF;     /* CRC-16 Low  byte */

    if ((sum_l==uartp->rxbff[uartp->rxpo-2]) && (sum_h==uartp->rxbff[uartp->rxpo-1])){
        return true;
    }else{
        return false;
    }
}


void make_sum_rtu(void){
    uint8_t sum_h, sum_l;
    uint16_t sumr;

    sumr = makecrc(&uartp->txbff[0],uartp->flg_txlen);
    sum_h = sumr >>8;        /* CRC-16 High byte */
    sum_l = sumr & 0xFF;     /* CRC-16 Low  byte */

    uartp->txbff[uartp->flg_txlen++]=sum_l;
    uartp->txbff[uartp->flg_txlen++]=sum_h;

    if (uartp->moddev != 0x00) { /*機器番号0はブロードキャストとして無応答とする*/
        txbegin();             /* 送信の起動 */
    }
}

void mhead_ack_r_rtu(void){  /* 03H/04H応答 */
    uartp->txbff[0] = uartp->set_device; 
    uartp->txbff[1] = uartp->moditem;  /* 機能コード */
    if((uartp->moditem == 0x03) || (uartp->moditem == 0x04)){
        uartp->txbff[2] = (uartp->itempo+1)*2;  /* 応答バイト数 */
//* }else if(uartp->moditem == 0x2B){  /* 処理済み */
    }
    make_sum_rtu();
}

void mhead_ack_w_rtu(void){
    uartp->txbff[0] = uartp->set_device;
    uartp->txbff[1] = uartp->moditem;  /* 機能コード */
    uartp->flg_txlen = 2;
    mksendt_rtu((char *)&uartp->txbff[uartp->flg_txlen],uartp->modadr);  /* アドレス */
    if(uartp->moditem == 0x10){
        mksendt_rtu((char *)&uartp->txbff[uartp->flg_txlen],uartp->datasuu);  /* データ数 */ 
    }else{           /* 0x06 */
        mksendt_rtu((char *)&uartp->txbff[uartp->flg_txlen],uartp->modbdt);  /* 設定データ */
    }
    make_sum_rtu();
}

void mhead_nak_rtu(void){
    uint8_t  d;

    uartp->moditem |= 0x80;  /* エラーコード(機能コード+0x80) */
    uartp->txbff[0] = uartp->set_device;
    uartp->txbff[1] = uartp->moditem;  /* エラーコード(機能コード+0x80) */
    switch (uartp->flg_xerr){
        case ATSTAT:
        case SETSTAT:
            d = (uartp->flg_xerr+13);  /* 11H,12Hﾆｽﾙ */
            break;
        case NOTCOMM:  /* 存在しないコマンド */
        case FSTEP:
        case SOVER:  /* 設定値の範囲外 */
        default:
            d = uartp->flg_xerr;
            break;
    }
    uartp->txbff[2] = d; /*エラーコード*/
    uartp->flg_txlen = 3;
    make_sum_rtu();
}

void scomu_rtu_sub(void){
    switch (uartp->flg_xerr) {
    case NOER:
        mhead_ack_r_rtu();  /* ACK */
        break;
    case NONEACK:
        mhead_ack_w_rtu();  /* ACK */
        break;
    case SUMERROR:
        break;     /* 応答しない */
    case NOTCOMM:  /* 存在しないコマンド */
    case FSTEP: 
    case SOVER:    /* 設定値の範囲外 */
    case ATSTAT:
    case SETSTAT:
    default:
        mhead_nak_rtu();  /* NAK */
        break;
    }
}

void rdm0x03(void){
    uint8_t max_item;
    uartp->flg_rxlen = 2;
    uartp->modadr = getdt_rtu(2);
    uartp->datasuu = getdt_rtu(2);  /* データ数チェック */
    uartp->datatop = 3;/* 応答データ */

    max_item = (uartp->uartnumber == EUART0_HOST) ? (BLKSIZE_HOST_RD) : (BLKSIZE_RD);
    if (uartp->datasuu >0 && uartp->datasuu <= max_item){  /* データ数チェック */
        readcmdblk();  /* 対象項目番号変換 */
    }else{
        uartp->flg_xerr = SOVER;  /* Error 3 */
    }
}

void rdm0x06(void){
    uartp->flg_xerr = NONEACK;
    uartp->flg_rxlen = 2;
    uartp->modadr = getdt_rtu(2);
    uartp->datatop = 4;
    uartp->datasuu = 1;
    wrsetcmd(uartp->modadr);  /* 設定 */
}

void rdm0x10(void){
    uint16_t ndt;
    uint8_t max_item;

    uartp->flg_xerr= NONEACK;
    uartp->flg_rxlen = 2;
    uartp->modadr = getdt_rtu(2);  /* アドレス */
    uartp->datasuu = getdt_rtu(2);  /* データ数 */
    ndt = getdt_rtu(1);  /* バイト数 */
    uartp->datatop = 7;
    max_item = (uartp->uartnumber == EUART0_HOST) ? (BLKSIZE_HOST_WR) : (BLKSIZE_WR);
    if(uartp->datasuu*2 == ndt){  /* バイト数 = 2×データ数 */
        if (uartp->datasuu >0 && uartp->datasuu <= max_item){  /* データ数チェック */
            wrsetcmdblk();  /* 対象項目番号変換 */
        }else{
            uartp->flg_xerr = SOVER;
        }
    }else{
        uartp->flg_xerr = SOVER;
    }
}

const uint8_t xcom_tbl_modbus[] ={
    0x03, 0x06, 0x10
};

const FTBLV xfunc_tbl_modbus[] ={
    rdm0x03, rdm0x06, rdm0x10
};

void scomu_rtu(void){
    uint8_t i,*cc;

    /* MODBUS-RTU */
    if(check_sum_rtu()){
        uartp->moddev = uartp->rxbff[0]; /* Device No. */
        if ((uartp->moddev == uartp->set_device)||(uartp->moddev == 0)){  /* アドレスチェック */
            uartp->moditem = uartp->rxbff[1];
            cc = (uint8_t *)&xcom_tbl_modbus;
            for (i = 0; i < sizeof(xcom_tbl_modbus); i++ ) {
                if (*cc ==  uartp->moditem) {
                    (*xfunc_tbl_modbus[i])();
                    break;
                } else {
                    if (i >= sizeof(xcom_tbl_modbus) -1){
                        uartp->flg_xerr= NOTCOMM;
                    }else{
                        cc++;
                    }
                }
            }
        }else{
            uartp->flg_xerr = SUMERROR;
        }
    }else{
        uartp->flg_xerr = SUMERROR;
    }
    scomu_rtu_sub();
}

