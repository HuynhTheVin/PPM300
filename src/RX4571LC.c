/*
 * RX4571LC.c
 *
 *  Created on: 2023/06/20
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "RX4571LC.h"
#include "PPM.h"

/*** 関数プロトタイプ ***/
void rtc_skon(void){ IO_RTC_SK_ON; }
void rtc_skoff(void){ IO_RTC_SK_OFF; }

void rtc_doon(void){ IO_RTC_DO_ON; }
void rtc_dooff(void){ IO_RTC_DO_OFF; }
void rtc_ceon(void){  IO_RTC_CE_ON; }
void rtc_ceoff(void){ IO_RTC_CE_OFF; }

void rtc_skset(void)
{
    rtc_skon();            /* clock high */
    rtc_skoff();           /* clock low  */
}

/* enable RX4571LC */
void rtc_chip_e(void)
{
    rtc_skoff();           /* clock low */
    rtc_ceon();            /* ce high */
    rtc_dooff();           /* dio low */
}

/* disable RX4571LC */
void rtc_chip_d(void)
{
    rtc_ceoff();           /* ce low */
}
BYTE rtcin(void){/* PA6 */
    //IO_FRAM_DATA_TO_IN;
    return IO_RTC_DATA_IN_ONQ;
}
/***********************************
   RX-4571LCから8bits読み込み
 ***********************************/
BYTE rtcinp8(void)
{
    BYTE   i, data;

    IO_FRAM_DATA_TO_IN;     /* PA6を一時的に入力ポートにする*/
    data = 0;
    for (i = 0; i < 8; i++) {
        data <<= 1;
        if (rtcin())
            data++;
        skset();            	/* clock high & low active */
    }
    IO_RTC_DATA_TO_OUT;/* PA6を出力ポートに戻す*/
    return (data);
}
/***********************************
   RX-4571LCへ8bits書込み
 ***********************************/
void rtcout8(BYTE data)
{
    BYTE   i;
    
    for (i = 0; i < 8; i++, data <<= 1) {	/* MSBファースト */
        if (data & 0x80)
            rtc_doon();
        else
            rtc_dooff();
        skset();	/* clock high & low active */
    }
}

BYTE makertc1(BYTE dt)
{
    BYTE da;
    da = ((dt>>4) & 0x0F)*10; /* 10位桁作成 */
    da += (dt & 0x0F);        /*  1位桁加算 */
    return da;
}
BYTE makertc2(BYTE dt)
{
    BYTE da;
    da = ((dt>>4) & 0x07)*10; /* 10位桁作成 */
    da += (dt & 0x0F);        /*  1位桁加算 */
    return da;
}
BYTE makertc3(BYTE dt)
{
    BYTE da;
    da = ((dt>>4) & 0x03)*10; /* 10位桁作成 */
    da += (dt & 0x0F);        /*  1位桁加算 */
    return da;
}
BYTE makertc4(BYTE dt)
{
    BYTE da;
    da = ((dt>>4) & 0x01)*10; /* 10位桁作成 */
    da += (dt & 0x0F);        /*  1位桁加算 */
    return da;
}
BYTE makertc5(BYTE dt)
{
    BYTE da;
//*    da = ((dt>>4) & 0x07)*10; /* 10位桁作成 */
//*    da += (dt & 0x0F);        /*  1位桁加算 */
    
    switch (dt){	/* 1H～40Hを0～6で扱う */
    	case 0x01:
        	da = 0;		/* 日 */
        	break;
        case 0x02:
            da = 1;		/* 月 */
            break;
        case 0x04:
            da = 2;		/* 火 */
            break;
        case 0x08:
            da = 3;		/* 水 */
            break;
        case 0x10:
            da = 4;		/* 木 */
            break;
        case 0x20:
            da = 5;		/* 金 */
            break;
        case 0x40:
            da = 6;		/* 土 */
            break;
    }
    return da;
}

/***********************************
   RX4571からの現在時刻読取り
     年: setyear    アドレス 6
     月: setmonth   アドレス 5
     日: setday     アドレス 4
   曜日: setweek    アドレス 3
     時: sethour    アドレス 2
     分: setmin     アドレス 1
     秒: setsec     アドレス 0
   各変数にデータセット
   
   桁上げ時に2度読みする
 ***********************************/
void rd_rtc(void)
{
    BYTE f,i,ecn;
//*    BYTE dt[16];
    BYTE dt[17];
    ecn=0;                  /* 計時エラーカウンタ              */

    do{                     /* RTC read                        */
        f = 0;
        rtc_chip_e();			/* アクセス可能                    */
        rtcout8(0x90);      /* RTC アクセスモード､アドレス出力 */
//*        for (i = 0; i < 16; i++) {
        for (i = 0; i < 17; i++) {
            dt[i] = rtcinp8();
        }
        rtc_chip_d();			/* 非選択状態                    */
        if(dt[14] & B1){    /* RX4571バッテリ低下異常フラグ   */
            CNT_STAT.cf3_flg.bitms.rtc_RX4571_power_drop_error = 1;
            break;
        }
        if(dt[15] & B1){    /* RX4571停止フラグ               */
            if(++ecn>2){
                CNT_STAT.cf3_flg.bitms.current_time_not_set = 1;
                break;
            }else{
                f=1;
            }
        }
        if((dt[0] != 0) && (dt[16] == 0)){	/* 読み取り中の1秒桁上げ発生チェック */
        	f = 1; break;					/* 桁上げが発生した場合は再度読み直す*/
        }
    }while(f);

    SET_TIME.setsec = makertc2(dt[0]);	/* 秒 */
    SET_TIME.setmin = makertc2(dt[1]);	/* 分 */
    SET_TIME.sethour = makertc3(dt[2]);	/* 時 */
    SET_TIME.setweek = makertc5(dt[3]);  /* 曜日 */
    SET_TIME.setday = (makertc3(dt[4]) == 0) ? (1) : makertc3(dt[4]);	/* 日 */
    SET_TIME.setmonth = (makertc4(dt[5]) == 0) ? (1) : makertc4(dt[5]);	/* 月 */
    SET_TIME.setyear = makertc1(dt[6]);	/* 年 */
}
/***********************************
   RX4571LCの時刻設定 (指定項目を書込む)
     f:設定項目(アドレスを引数化する)
       
       年: setyear    アドレス 6
       月: setmonth   アドレス 5
       日: setday     アドレス 4
     曜日: setweek    アドレス 3
       時: sethour    アドレス 2
       分: setmin     アドレス 1
       秒: setsec     アドレス 0
       
   da:書き込みデータ(上位､下位4bitsに分割する)
 ***********************************/
void wr_rtc(BYTE f,BYTE da)
{
    BYTE dt;

	if(f==3){
		switch (da){	/* 1H～40Hを0～6で扱う */
    		case 0:
        		dt = 0x01;		/* 日 */
        		break;
        	case 1:
            	dt = 0x02;		/* 月 */
            	break;
        	case 2:
            	dt = 0x04;		/* 火 */
            	break;
        	case 3:
            	dt = 0x08;		/* 水 */
            	break;
        	case 4:
            	dt = 0x10;		/* 木 */
            	break;
        	case 5:
            	dt = 0x20;		/* 金 */
            	break;
        	case 6:
            	dt = 0x40;		/* 土 */
            	break;
    	}
	}else{
		dt = (da/10);
    	dt <<=4;            /* 10位桁 を上位4bitsにセット      */
    	dt += (da%10);      /* 1位桁を下位4bitsにセット        */
	}
//*    dt = (da/10);
//*    dt <<=4;            /* 10位桁 を上位4bitsにセット      */
//*    dt += (da%10);      /* 1位桁を下位4bitsにセット        */
    rtc_chip_e();			/* アクセス可能                    */
    rtcout8(0x10+f);    /* RTC アクセスモード､アドレス出力 */
    rtcout8(dt);
    rtc_chip_d();			/* 非選択状態                      */
    CNT_STAT.cf3_flg.bitms.current_time_not_set = 0;	/* 計時停止フラグのクリア          */      
	rd_rtc();           /* 時刻の読取り                    */

}
/***********************************
    初回通電時にRX4571LCを初期化する
 ***********************************/
void initrtc(void)
{
    BYTE i;

	rtc_chip_e();			/* アクセス可能                    */
	rtcout8(0x10);      /* RTC アクセスモード､アドレス出力 */
    rtcout8(0x00);      /* 秒                              */
    rtcout8(0x00);      /* 分                              */
    rtcout8(0x00);      /* 時                              */
    rtcout8(0x01);      /* 曜日                            */
    rtcout8(0x01);      /* 日                              */
    rtcout8(0x01);      /* 月                              */
    rtcout8(0x00);      /* 年                              */
    
    rtcout8(0x00);      /* RAM                             */
    
    rtcout8(0x00);      /* MIN ALARM                       */
    rtcout8(0x00);      /* HOUR ALARM                      */
    rtcout8(0x00);      /* WEEK/DAY ALARM                  */
    
    rtcout8(0x00);      /* TIMER0                          */
    rtcout8(0x00);      /* TIMER1                          */
    
    rtcout8(0x00);      /* 拡張レジスタ                    */
    rtcout8(0x00);      /* フラグレジスタ                  */
    rtcout8(0x00);      /* コントロールレジスタ            */
    
    rtc_chip_d();			/* 非選択状態                    */
    rd_rtc();           /* 時刻の読取り                    */
}