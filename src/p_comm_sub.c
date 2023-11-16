/*
 * p_comm_sub.c
 *
 *  Created on: 2023/06/02
 *      Author: VINH-NT
 */
#define EXTERN	extern
#include "PPM.h"
#include "p_comm_sub.h"
//void read_cmd_host(void);
/* 9600 19200 38400 57600 */
const uint8_t txwietbl[] = {  12,  8,  8,  8 };
const uint8_t mrtuwitbl[] = { 36, 18,  9, 6 };  // 3.5キャラクタの時間 (100us×定数)

void clr_tx(void){
    uint8_t *p;
    uint16_t i;

    p = (uint8_t *)&uartp->txbff;
    for(i=0;i<BFCAP_TX_MAX;i++){
        *(p++) = 0;
    }
}

void clr_rx(void){
    uint8_t *p;
    uint16_t i;

    p = (uint8_t *)&uartp->rxbff;
    for(i=0;i<BFCAP_RX_MAX;i++){
        *(p++) = 0;
    }
}
void txbegin(void){
    clr_rx();
    switch (uartp->uartnumber)
    {
    case EUART1_DIS:
        IO_OUT_RS485_DISPLAY_ON;  /* RS-485 drive ON */
        break;
    case EUART0_HOST:
        IO_OUT_RS485_HOST_ON;  /* RS-485 drive ON */
        break;
    }
    uartp->flg_rx = RXCLR;  // 受信フェーズ初期化
    uartp->txpo = 0;    // １文字目の送信
    uartp->rxcn = 0;
    uartp->txwis = 20;  // 2ms
}

void comret_dt(int16_t i){
    switch (uartp->cflg.bitms.protocol){
    case EPRO_SHINKO:
        hextoasc(4,i,(char *)&uartp->txbff[(uartp->itempo * 4) + DATATOP+3]);
        break;
    default:  /* RTU */
        uartp->modbdt = i;
        uartp->flg_txlen = uartp->datatop + uartp->itempo*2;
        mksendt_rtu((char *)&uartp->txbff[uartp->flg_txlen],uartp->modbdt);/*応答データ  */
        break;
    }
}

uint16_t cmkdat(void)
{

	uartp->flg_xerr= NONEACK;
	switch (uartp->cflg.bitms.protocol){
	case EPRO_SHINKO:
		return asctodec((char *)&uartp->rxbff[(uartp->itempo * 4) + DATATOP], 4);
	default:  /* RTU */
	uartp->flg_rxlen =  uartp->itempo*2 +  uartp->datatop;
	uartp->modbdt = getdt_rtu(2);
	return uartp->modbdt;
	}
}

void readcmd(uint16_t ad)
{
    uartp->commadr = ad;  // データ項目保存
    switch (uartp->uartnumber)
    {
    case EUART0_HOST:
        switch (uartp->cflg.bitms.protocol)
        {
        case EPRO_SHINKO:
            read_cmd_host();
            break;
        default:
            read_cmd_host(); /* RTU */
            break;
        }
        break;
    case EUART1_DIS:
        read_cmd_host();
        break;
    case EUART12_CONS:
        read_cmd_host();
        break;
    default:
    	break;
    }
    
}

void readcmdblk(void){
    uint16_t i,adr;

    for(i=0;i<uartp->datasuu;i++){
        uartp->itempo = i;
        adr = uartp->modadr+i;
        readcmd(adr);
        if ((uartp->flg_xerr != NONEACK) && (uartp->flg_xerr != NOER)){
            if((uartp->flg_bxerr == NONEACK) || (uartp->flg_bxerr == NOER)){
                uartp->flg_bxerr =uartp->flg_xerr;/* 最初のエラーコード取る */
            }
        }
    }
    if (uartp->flg_bxerr != NOER){/* ブロック最初のエラー */
        uartp->flg_xerr = uartp->flg_bxerr;
    }
}

/**
 * @brief プログラムのデータアクセスか調べる
 * 
 * @return BOOL true=プログラムのデータアクセス項目ある
 */
//BOOL is_pro_erea_access(void){/* プログラムデータアクセス */
//    switch (uartp->uartnumber){
//    case EUART0_HOST:
//        return (uartp->erea == EHOST_ADDR_PROGRAM) ? (true) : (false);
//    case EUART1_DIS:
//    // case EUART1_FACT:
//        return (uartp->erea == EDISP_ADDR_PROGRAM) ? (true) : (false);
//    }
//    return false;
//}

//void update_pro_data(void){/* 予約データを制御中間データに更新する */
//    if(KEY_MODE.flg_rmode == RESERVEMD){/* 予約 */
//        if(!is_ck_or_pre() && !is_fan5m()){
//            rdstepdt(); /* FRAM --> 中間ワーク */
//            rddata();   /* 設定値 --> udbuffへ リミット値読出し */
//            rdfandata(); /* FANの更新 */
//        }
//    }
//}

void wrsetcmd(uint16_t ad)
{
    uartp->commadr = ad;  // データ項目保存
    switch (uartp->uartnumber)
    {
    case EUART0_HOST:
        switch (uartp->cflg.bitms.protocol)
        {
        case EPRO_SHINKO:
           write_cmd_host();
            break;
        default:
            write_cmd_host();/* RTU */
            break;
        }
        break;
    case EUART1_DIS:
         write_cmd_host();/* RTU */
        break;
    case EUART12_CONS:
        write_cmd_host();/* RTU */
        break;
    default:
    	break;
    }
    // if(uartp->datasuu==1){/* 単体であれば中間予約を更新 */
    //     if(is_pro_erea_access()){
    //         update_pro_data(); /* プログラムデータ設定のであれば、予約モード中にデータを更新する */
    //         data_set_stop();   /* 停止時の中間データ更新 */
    //     }
    // }/* ブロック場合は、まとめて、最後一回に更新 */
}

void wrsetcmdblk(void){
    //BOOL flg_pro = false;
    uint8_t i;

    for (i = 0; i < uartp->datasuu; i++ ) {
        uartp->itempo = i;
        wrsetcmd(uartp->modadr+uartp->itempo);     /* 対象項目番号変換 */
        if ((uartp->flg_xerr != NONEACK) && (uartp->flg_xerr != NOER)){
            if((uartp->flg_bxerr == NONEACK) || (uartp->flg_bxerr == NOER)){
                uartp->flg_bxerr = uartp->flg_xerr;   /* 最初のエラーコード取る */
            }
        }
      //  if(is_pro_erea_access()){flg_pro = true;}  /* プログラムのデータアクセスか調べる */
    }

    /* 中間予約データを更新する。ブロック設定なので、こちらに一回処理する。 */
    // if((uartp->datasuu>1) && flg_pro){/* 複数のであれば更新 */
    //     update_pro_data(); /* プログラムデータ設定のであれば、予約モード中にデータを更新する */
    //     data_set_stop();   /* 停止時の中間データ更新 */
    // }/* 単体のであれば@wrsetcmd()内に処理があった為、処理しない */

    if (uartp->flg_bxerr != NOER){/* ブロック最初のエラー */
        uartp->flg_xerr = uartp->flg_bxerr;
    }
}

void scomu(void){

	if(uartp->flg_rx == RXDELIMIT){
		uartp->flg_xerr = NOER;  /* clear error flag */
		uartp->flg_bxerr = NOER;  /* clear error flag */
		uartp->itempo = 0;
		uartp->datasuu = 1;  /* 初期値 */
		clr_tx();
		switch (uartp->cflg.bitms.protocol){
		case EPRO_SHINKO:
			scomu_shinko();
			break;
		default:
			scomu_rtu();
			break;
		}
		uartp->flg_rx = RXCLR;
	}
	//update_para_uart_5(); /* UART0のパラメータ設定を更新 */
}
void uartm_comm(void){
	switch (uartp->uartnumber)
	{
	case EUART1_DIS:
		uartp= &COMM0;
		uartp->uartnumber = EUART0_HOST;
		break;
	case EUART0_HOST:
		uartp = &COMM12;
		uartp->uartnumber = EUART12_CONS;
		break;
	case EUART12_CONS:
		uartp = &COMM1;
		uartp->uartnumber = EUART1_DIS;
		break;
	default:
//		uartp = &COMM5;
//		uartp->uartnumber = EUART5_BLE;
		break;
	}
	scomu();
}

