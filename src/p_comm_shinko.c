/*
 * p_comm_shinko.c
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_comm_shinko.h"

char asc_h(uint8_t d){
    return (d < 10) ? d+'0' : d-10+'A' ;
}

void hextoasc(uint8_t n,uint16_t hdt, char *sp )
{
    uint8_t i=0;

    do{
        *(sp--) = asc_h(hdt & 0x000f);
        hdt >>= 4;
    }
    while(++i < n);
}

uint8_t d_hex(uint8_t d)
{
    if (d >= '0' && d <= '9'){
        return d-'0';
    }else if (d >= 'A' && d <= 'F'){
        return d-'A'+10;
    }else{
        return 16; /* error */
    }
}

uint16_t asctodec(char *ap, uint8_t n)
{
    uint8_t   i,t;
    uint16_t d=0;

    for (i = 0; i < n; i++) {
        if ((t = d_hex(*ap)) < 16) {
            d = (d << 4) + t;
            ap++;
        } else {
            return 0x8000;   /* SP ąÄŢÚ˝ */
        }
    }
    return d;
}

void make_sum_shinko(void)
{
    uint16_t i=1;
    uint8_t sum=0;

    while (uartp->txbff[i+2] != ETX && i < BFCAP_TX_MAX -3){
        sum += uartp->txbff[i++];
    }
    if (i < BFCAP_TX_MAX -2){
        hextoasc(2,(uint16_t)(~sum+1),(char *)&uartp->txbff[i+1]);
    }
    if (uartp->rxbff[1] != 0x7F) {
        txbegin();  /* MĚNŽ */
    }
}

void mhead_ack_r_shinko(void)
{
    uint8_t  *pt,*pt1;
    uint8_t  d;

    uartp->txbff[0]= ACK;
    pt = &uartp->txbff[1];
    pt1 = &uartp->rxbff[1];
    d = 7;
    do
        *pt++ = *pt1++;
    while(--d != 0);
}

uint8_t check_sum_shinko(void)
{
    uint16_t i;
    uint8_t sum, sum_h, sum_l;

    sum = 0;
    i = 1;
    while (uartp->rxbff[i+2] != ETX && i < BFCAP_RX_MAX -3){
        sum += uartp->rxbff[i++];
    }
    if (i < BFCAP_RX_MAX -2){
        sum_h = d_hex(uartp->rxbff[i]);
        sum_l = d_hex(uartp->rxbff[i+1]);
        if (sum_h > 15 || sum_l > 15)
            return false;
        if ((uint8_t)(sum + (sum_h<<4) + sum_l) == 0)
            return true;
        else
            return false;
    } else{
        return false;
    }
}

uint16_t cmkadd(void)
{
    return asctodec((char *)&uartp->rxbff[ADRESTOP], 4);
}
uint16_t cmkdatasuu(void)
{
    return asctodec((char *)&uartp->rxbff[ADRESTOP+4], 4);
}

void rd0x20(void){

    if (uartp->rxbff[2] == 0+DEVISNO ){
        uartp->modadr = cmkadd();             /* AhX         */
        uartp->datasuu = 1;
        readcmd(cmkadd()); /* ÎŰÚÔĎˇ */
    }else{
        uartp->flg_xerr= NOTCOMM;
    }
}

void rd0x24(void)
{
    uartp->modadr = cmkadd();             /* AhX         */
    uartp->datasuu = cmkdatasuu();        /* f[^         */
    if (uartp->rxbff[2] == 0+DEVISNO ){
        if(uartp->datasuu>0 && uartp->datasuu<=BLKSIZE_RD){            /* f[^Í1`100 */
            readcmdblk(); /* ÎŰÚÔĎˇ */
        }else{
            uartp->flg_xerr = SOVER;      /* Error 3 */
        }
    }else{
        uartp->flg_xerr = NOTCOMM;
    }
}

void wr0x50(void)
{
    uartp->flg_xerr = NONEACK;  /* clear error flag */
    uartp->modadr = cmkadd();
    if ((uartp->rxbff[2] == 0+DEVISNO) || ((uartp->rxbff[2] == 1+DEVISNO) && (uartp->rxbff[1] == 0x7F))){
        wrsetcmd(uartp->modadr);  /* ÎŰÚÔĎˇ */
    }else{
        uartp->flg_xerr= NOTCOMM;
    }
}

void wr0x54(void)
{
    uint16_t dt;

    uartp->flg_xerr = NONEACK;  /* clear error flag */
    if(uartp->rxpo>14){  // f[^ĚmF
        dt = uartp->rxpo-11;
        if((dt%4)==0){  // ]č=0Ĺłľ˘R}hÉČé
            uartp->datasuu = dt/4;
        }else{
            uartp->flg_xerr= NOTCOMM;
            return;
        }
    }else{
        uartp->datasuu = 0;
        uartp->flg_xerr= NOTCOMM;
        return ;
    }
    uartp->modadr = cmkadd();
    if ((uartp->rxbff[2] == 0+DEVISNO) ||
        ((uartp->rxbff[2] == 1+DEVISNO) && (uartp->rxbff[1] == 0x7F))){
        if((uartp->datasuu>0) && (uartp->datasuu<=BLKSIZE_WR)){
            wrsetcmdblk();
        }else{
            uartp->flg_xerr = SOVER;
        }
    }else{
        uartp->flg_xerr= NOTCOMM;
    }
}

void rd0x60(void)
{
    uint8_t *cc;

    cc =(uint8_t *)cmkadd();
    comret_dt(*cc);
}

void rd0x61(void)
{
    uint16_t *cc;

    cc =(uint16_t *)cmkadd();
    comret_dt(*cc);
}

void rd0x63(void)
{
    long *cc;
    uint16_t dt;

    cc =(long *)cmkadd();
    dt = ((*cc>>16) & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+3]);  /* High */
    dt = (*cc & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+7]);  /* Low */
//  uartp->txbff[DATATOP+10]= ETX;
    uartp->itempo = 1;
}

void rd0x64(void)
{
    long *cc;
    uint16_t  dt;

    cc =(long *)(cmkadd()+4);

    dt = ((*cc>>16) & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+3]);       /* High */
    dt = (*cc & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+7]);       /* Low */

    cc =(long *)cmkadd();
    dt = ((*cc>>16) & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+11]);      /* High */
    dt = (*cc & 0xFFFF);
    hextoasc(4,dt,(char *)&uartp->txbff[DATATOP+15]);      /* Low */
//  uartp->txbff[DATATOP+18]= ETX;
    uartp->itempo = 3;
}

void rd0x62(void)
{
    comret_dt(get_fram2(cmkadd()));
}

void wr0x70(void)
{
    uint8_t *cc;

    cc =(uint8_t *)cmkadd();
    *cc = cmkdat();
    uartp->flg_xerr= NONEACK;
}

void wr0x71(void)
{
    uint16_t *cc;

    cc =(uint16_t *)cmkadd();
    *cc = cmkdat();
    uartp->flg_xerr= NONEACK;
}

void wr0x73(void)
{
    long *cc;
    long dt;

    cc =(long *)cmkadd();
    dt = asctodec((char *)&uartp->rxbff[DATATOP], 4);      /* High */
    dt = (dt << 16);
    dt += asctodec((char *)&uartp->rxbff[DATATOP+4], 4);   /* Low */
    *cc = dt;
    uartp->flg_xerr= NONEACK;
}

void wr0x72(void)
{
    put_fram2(cmkadd(),cmkdat());
    uartp->flg_xerr= NONEACK;
}

const uint8_t xcom_tbl_shinko[] ={
    0x20, 0x50, 0x24, 0x54,
    0x63, 0x73,
    0x60, 0x61, 0x62, 0x70, 0x71, 0x72,
    0x64
};

const FTBLV xfunc_tbl_shinko[] ={
    rd0x20, wr0x50, rd0x24, wr0x54,
    rd0x63, wr0x73,
    rd0x60, rd0x61, rd0x62, wr0x70, wr0x71,wr0x72,
    rd0x64
};

void scomu_shinko_sub(void){
    switch (uartp->flg_xerr) {
        case NOER:
            mhead_ack_r_shinko();
            uartp->txbff[(uartp->itempo * 4) + DATATOP+6]= ETX;
            make_sum_shinko();
            break;
        case NONEACK:
            uartp->txbff[0]= ACK;
            uartp->txbff[1]= DEVISNO+uartp->set_device;
            uartp->txbff[4]= ETX;
            make_sum_shinko();
            break;
        case SUMERROR:
            break;
        default:        /* ERROR */
//*     case NOTCOMM:
//*     case FSTEP:
//*     case SOVER:
//*     case ATSTAT:
//*     case SETSTAT:
            uartp->txbff[0]= NAK;
            uartp->txbff[1]= DEVISNO+uartp->set_device;
            uartp->txbff[2]= (uint8_t)uartp->flg_xerr + '0';
            uartp->txbff[5]= ETX;
            make_sum_shinko();
    }
}

void scomu_shinko(void){
    uint8_t i,*cc;

    if (check_sum_shinko() == true) {
        cc = (uint8_t *)&xcom_tbl_shinko;
        for (i = 0; i < sizeof(xcom_tbl_shinko); i++ ) {
            if (*cc == uartp->rxbff[3]) {
                if (uartp->rxbff[uartp->rxpo-1] != ETX) {
                    uartp->flg_xerr = NOTCOMM;
                    break;
                }
                if (i < 4){
                    (*xfunc_tbl_shinko[i])();
                }else if (uartp->cflg.bitms.enable_internal_cmd){
                    (*xfunc_tbl_shinko[i])();
                }else{
                    uartp->flg_xerr = ATSTAT;
                }
                break;
            } else {
                if (i >= sizeof(xcom_tbl_shinko) -1)
                    uartp->flg_xerr= NOTCOMM;
                else
                    cc++;
            }
        }
    } else{
        uartp->flg_xerr = SUMERROR;
    }
    scomu_shinko_sub();
}
