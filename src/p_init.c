/*
 * p_init.c
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.h"
#include "p_init.h"

WORD clr_eng_ph_tbl[] = {
    PH_DATA0,   // A0000  MC入力OFF確定時間を設定。
    PH_DATA1,   // A0001  冷却動作再確認時間を設定
    PH_DATA2,   // A0002  点検「A」発生時の冷凍機ON時間を設定。
    PH_DATA3,   // A0003  点検「A」発生時の冷凍機OFF時間を設定。
    PH_DATA4,   // A0004  加熱「強」のON時間を設定。
    PH_DATA5,   // A0005  加熱「強」のOFF時間を設定。
    PH_DATA6,   // A0006  除霜サイクル時間を設定。
    PH_DATA7,   // A0007  除霜時間(庫内温度「高」用)を設定。
    PH_DATA8,   // A0008  除霜時間(庫内温度「中」用)を設定。
    PH_DATA9,   // A0009  除霜時間(庫内温度「低」用)を設定。
    PH_DATA10,  // A0010  除霜不可の温度差(現在温度に対しての温度差)を設定。
    PH_DATA11,  // A0011  除霜不可の温度差継続時間を設定。
    PH_DATA12,  // A0012  冷却不良監視の有効/無効を選択。
    PH_DATA13,  // A0013  異常表示「L」監視の有効/無効を選択。
    PH_DATA14,  // A0014  除霜解除コマンド受信時の除霜サイクル時間(1サイクルのみ)を設定。
    PH_DATA15,  // A0015  異常表示「P」監視の有効/無効を選択。
    PH_DATA16,  // A0016  除霜解除回数を設定。
    PH_DATA17,  // A0017  加熱「弱」のON時間を設定。
    PH_DATA18,  // A0018  加熱「弱」のOFF時間を設定。
    PH_DATA19,  // A0019  予約
    PH_DATA20,  // A0020  予約
    PH_DATA21,  // A0021  予約
    PH_DATA22,  // A0022  冷凍・冷蔵モード加熱2動作時、FAN1 ON周期時間を設定。(切替り1秒含む)
    PH_DATA23,  // A0023  冷凍・冷蔵モード加熱2動作時、FAN2 ON周期時間を設定。(切替り1秒含む)
    PH_DATA24,  // A0024  ドレンホースヒータON開始時刻を設定。(除霜開始直前の時間)
    PH_DATA25,  // A0025  予約
    PH_DATA26,  // A0026  MCチャタリング監視時間を設定。
    PH_DATA27,  // A0027  MCチャタリング監視時間内のON/OFF回数を設定。
    PH_DATA28,  // A0028  予約
    PH_DATA29,  // A0029  予約
    PH_DATA30,  // A0030  加熱「強」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
    PH_DATA31,  // A0031  加熱「強」で庫内温度設定に対して加熱出力がONする温度差を設定。(メモリ3の冷凍・冷蔵モードのみ)
    PH_DATA32,  // A0032  冷凍機起動時のGA出力繰り返し回数を設定。
    PH_DATA33,  // A0033  庫内温度設定に対して冷却信号がOFFする温度差を設定。
    PH_DATA34,  // A0034  庫内温度設定に対して冷却信号がONする温度差を設定。
    PH_DATA35,  // A0035  冷凍機起動時のGA出力ON時間を設定
    PH_DATA36,  // A0036  冷凍機起動時のGA出力OFF時間を設定。
    PH_DATA37,  // A0037  予約
    PH_DATA38,  // A0038  GA出力OFF後M1出力(CPC)がOFFするまでの時間を設定。
    PH_DATA39,  // A0039  SV2出力インチング動作(電源投入時)の有効/無効を選択。
    PH_DATA40,  // A0040  SV2出力インチング動作(除霜終了時)の有効/無効を選択。
    PH_DATA41,  // A0041  A0041
    PH_DATA42,  // A0042  A0042
    PH_DATA43,  // A0043  A0043
    PH_DATA44,  // A0044  A0044
    PH_DATA45,  // A0045  A0045
    PH_DATA46,  // A0046  異常「4」発生カウント数を設定。
    PH_DATA47,  // A0047  予約
    PH_DATA48,  // A0048  SV4出力がOFFする温度を設定。
    PH_DATA49,  // A0049  SV4出力がONする温度差を設定。(A0048に対して)
    PH_DATA50,  // A0050  予約
    PH_DATA51,  // A0051  加熱「弱」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
    PH_DATA52,  // A0052  加熱「弱」で庫内温度設定に対して加熱出力がONする温度差を設定。
    PH_DATA53,  // A0053  予約
    PH_DATA54,  // A0054  水切り時間を設定。
    PH_DATA55,  // A0055  加熱2終了時のFAN1の遅延時間を設定。(メモリ3の冷凍・冷蔵モードのみ)
    PH_DATA56,  // A0056  冷凍・冷蔵モード冷却信号ON時、FAN2 ON時間を設定。(切替り1秒含む)
    PH_DATA57,  // A0057  冷凍・冷蔵モード冷却信号ON時、FAN1 ON時間を設定。(切替り1秒含む)
    PH_DATA58,  // A0058  除霜ヒータOFF温度設定。(外部)
    PH_DATA59,  // A0059  除霜ヒータOFF温度設定(外部)に対するディファレンシャルを設定。
    PH_DATA60,  // A0060  予約
    PH_DATA61,  // A0061  除霜時間(庫内温度「中高」用)を設定。
    PH_DATA62,  // A0062  予約
    PH_DATA63,  // A0063  ドアヒータ温度設定値を設定。
    PH_DATA64,  // A0064  庫内温度センサ補正値を設定。
    PH_DATA65,  // A0065  予約
    PH_DATA66,  // A0066  予約
    PH_DATA67,  // A0067  冷却不良待ち時間を設定。
    PH_DATA68,  // A0068  除霜時間設定用庫内温度を設定。(高位)
    PH_DATA69,  // A0069  除霜時間設定用庫内温度を設定。(中位)
    PH_DATA70,  // A0070  除霜時間設定用庫内温度を設定。(低位)
    PH_DATA71,  // A0071  予約
    PH_DATA72,  // A0072  メモリ3の冷凍・冷蔵モード時、DHH出力を常時ONする温度を設定。
    PH_DATA73,  // A0073  予約
    PH_DATA74,  // A0074  予約
    PH_DATA75,  // A0075  切替り時のブザーON時間を設定。(自動切換運転時)
    PH_DATA76,  // A0076  切替り時のブザーOFF時間を設定。(自動切換運転時)
    PH_DATA77,  // A0077  切替り時のブザー回数を設定。(自動切換運転時)
    PH_DATA78,  // A0078  予約
    PH_DATA79,  // A0079  予約
    PH_DATA80,  // A0080  予約
    PH_DATA81,  // A0081  点検「L」発生時、冷却動作再確認時間(A0001)による出力回数を設定。
    PH_DATA82,  // A0082  予約
    PH_DATA83,  // A0083  運転開始時、制御開始するまでのウエイト時間を設定。
    PH_DATA84,  // A0084  冷却用制御信号M1出力(CPC)がOFF後、ONしない時間を設定。
    PH_DATA85,  // A0085  予約
    PH_DATA86,  // A0086  フリーザー/ショックフリーザーを選択。
    PH_DATA87,  // A0087  冷凍機有(固定値)
    PH_DATA88,  // A0088  除霜監視時間を設定する。
    PH_DATA89,  // A0089  予約
    PH_DATA90,  // A0090  予約
    PH_DATA91,  // A0091  予約
    PH_DATA92,  // A0092  冷凍機運転信号(MC)の判定タイプ(a接点/b接点)を選択。
    PH_DATA93,  // A0093  CPUリセット累積回数(設定不可)。
    PH_DATA94,  // A0094  予約
    PH_DATA95,  // A0095  予約
    PH_DATA96,  // A0096  SV3の緊急冷却ON時間を設定。
    PH_DATA97,  // A0097  SV3の緊急冷却OFF時間を設定。
    PH_DATA98,  // A0098  予約 通信プロトコル
    PH_DATA99,  // A0099  予約 通信機器番号
    PH_DATA100, // A0100  予約 通信速度
    PH_DATA101, // A0101  予約 通信データビット
    PH_DATA102, // A0102  予約
    PH_DATA103, // A0103  予約
    PH_DATA104, // A0104  予約
    PH_DATA105, // A0105  予約
    PH_DATA106, // A0106  予約
    PH_DATA107, // A0107  予約
    PH_DATA108, // A0108  予約
    PH_DATA109, // A0109  予約
    PH_DATA110, // A0110  予約
    PH_DATA200, // A0200  外部温度センサ1の有効/無効を選択。
    PH_DATA201, // A0201  予約(外部温度センサ2の有効/無効を選択。)
    PH_DATA202, // A0202  予約(外部温度センサ3の有効/無効を選択。)
    PH_DATA203, // A0203  外部温度センサ1入力種類を選択。
    PH_DATA204, // A0204  予約(外部温度センサ2入力種類を選択。)
    PH_DATA205, // A0205  予約(外部温度センサ3入力種類を選択。)
    PH_DATA206, // A0206  温度表示範囲下限値を設定。
    PH_DATA207, // A0207  温度表示範囲上限値を設定。
    PH_DATA208, // A0208  温度設定範囲下限値を設定。
    PH_DATA209, // A0209  温度設定範囲上限値を設定。
    PH_DATA210, // A0210  予約
    PH_DATA211,
    PH_DATA212,
    PH_DATA213,
    PH_DATA214,
    PH_DATA215,
    PH_DATA216,
    PH_DATA217};
WORD clr_err_rireki_ph_tbl[] = {
    PH_CHECKD01NO,       //  点検履歴   点検番号
    PH_CHECKD02NO,       //  点検履歴   点検番号
    PH_CHECKD03NO,       //  点検履歴   点検番号
    PH_CHECKD04NO,       //  点検履歴   点検番号
    PH_CHECKD05NO,       //  点検履歴   点検番号
    PH_CHECKD06NO,       //  点検履歴   点検番号
    PH_CHECKD07NO,       //  点検履歴   点検番号
    PH_CHECKD08NO,       //  点検履歴   点検番号
    PH_CHECKD09NO,       //  点検履歴   点検番号
    PH_CHECKD10NO,       //  点検履歴   点検番号
    PH_CHECKD11NO,       //  点検履歴   点検番号
    PH_CHECKD12NO,       //  点検履歴   点検番号
    PH_CHECKD13NO,       //  点検履歴   点検番号
    PH_CHECKD14NO,       //  点検履歴   点検番号
    PH_CHECKD15NO,       //  点検履歴   点検番号
    PH_CHECKD16NO,       //  点検履歴   点検番号
    PH_CHECKD17NO,       //  点検履歴   点検番号
    PH_CHECKD18NO,       //  点検履歴   点検番号
    PH_CHECKD19NO,       //  点検履歴   点検番号
    PH_CHECKD20NO,       //  点検履歴   点検番号
    PH_CHECKD01AD,       //  点検履歴   西暦
    PH_CHECKD02AD,       //  点検履歴   西暦
    PH_CHECKD03AD,       //  点検履歴   西暦
    PH_CHECKD04AD,       //  点検履歴   西暦
    PH_CHECKD05AD,       //  点検履歴   西暦
    PH_CHECKD06AD,       //  点検履歴   西暦
    PH_CHECKD07AD,       //  点検履歴   西暦
    PH_CHECKD08AD,       //  点検履歴   西暦
    PH_CHECKD09AD,       //  点検履歴   西暦
    PH_CHECKD10AD,       //  点検履歴   西暦
    PH_CHECKD11AD,       //  点検履歴   西暦
    PH_CHECKD12AD,       //  点検履歴   西暦
    PH_CHECKD13AD,       //  点検履歴   西暦
    PH_CHECKD14AD,       //  点検履歴   西暦
    PH_CHECKD15AD,       //  点検履歴   西暦
    PH_CHECKD16AD,       //  点検履歴   西暦
    PH_CHECKD17AD,       //  点検履歴   西暦
    PH_CHECKD18AD,       //  点検履歴   西暦
    PH_CHECKD19AD,       //  点検履歴   西暦
    PH_CHECKD20AD,       //  点検履歴   西暦
    PH_CHECKD01MONTHDAY, //  点検履歴   月日
    PH_CHECKD02MONTHDAY, //  点検履歴   月日
    PH_CHECKD03MONTHDAY, //  点検履歴   月日
    PH_CHECKD04MONTHDAY, //  点検履歴   月日
    PH_CHECKD05MONTHDAY, //  点検履歴   月日
    PH_CHECKD06MONTHDAY, //  点検履歴   月日
    PH_CHECKD07MONTHDAY, //  点検履歴   月日
    PH_CHECKD08MONTHDAY, //  点検履歴   月日
    PH_CHECKD09MONTHDAY, //  点検履歴   月日
    PH_CHECKD10MONTHDAY, //  点検履歴   月日
    PH_CHECKD11MONTHDAY, //  点検履歴   月日
    PH_CHECKD12MONTHDAY, //  点検履歴   月日
    PH_CHECKD13MONTHDAY, //  点検履歴   月日
    PH_CHECKD14MONTHDAY, //  点検履歴   月日
    PH_CHECKD15MONTHDAY, //  点検履歴   月日
    PH_CHECKD16MONTHDAY, //  点検履歴   月日
    PH_CHECKD17MONTHDAY, //  点検履歴   月日
    PH_CHECKD18MONTHDAY, //  点検履歴   月日
    PH_CHECKD19MONTHDAY, //  点検履歴   月日
    PH_CHECKD20MONTHDAY, //  点検履歴   月日
    PH_CHECKD01MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD02MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD03MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD04MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD05MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD06MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD07MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD08MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD09MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD10MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD11MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD12MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD13MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD14MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD15MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD16MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD17MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD18MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD19MINUTE,   //  点検履歴   時刻　分
    PH_CHECKD20MINUTE    //  点検履歴   時刻　分
};
WORD clr_pro_ph_tbl[] = {
    PH_NUMYASUMI,       //  休日日数
    PH_KANETU,          //  加熱動作有効/無効選択
    PH_MEM1REITOU,      //  メモリ1　冷凍温度設定
    PH_MEM1REITOUZOU,   //  メモリ1　冷凍・冷蔵温度設定
    PH_MEM1TIME,        //  メモリ1　切替り時刻設定
    PH_JOSOUHOUSHIKI,   //  除霜方式
    PH_JOSOUSTARTTIME1, //  除霜開始時刻 1
    PH_JOSOUSTARTTIME2, //  除霜開始時刻 2
    PH_JOSOUSTARTTIME3, //  除霜開始時刻 3
    PH_JOSOUSTARTTIME4, //  除霜開始時刻 4
    PH_JOSOUSTARTTIME5, //  除霜開始時刻 5
    PH_JOSOUSTARTTIME6, //  除霜開始時刻 6
    PH_JOSOUSTARTTIME7, //  除霜開始時刻 7
    PH_JOSOUSTARTTIME8, //  除霜開始時刻 8
    PH_JOSOUSTARTTIME9, //  除霜開始時刻 9
    PH_JOSOUSTARTTIME10 //  除霜開始時刻 10
};
/* Clear eng parameter. @see clr_eng_ph_tbl */
/* @para rdram: true to call rdsram to update sram data. */
void clrprog_para(BOOL rdram)
{
    WORD cn;
    WORD cmax;
    WORD phase;

    cmax = sizeof(clr_eng_ph_tbl) / 2;
    for (cn = 0; cn < cmax; cn++)
    {
        phase = clr_eng_ph_tbl[cn];
        set_data(phase, get_default(phase));
    }
    put_fram2(CNTRL2, PASSDT2);

    if (rdram == CLR_READ_FRAM)
    {
        rdsram();
    }

    // /* update UART5 para */
    // COMM0.cflg.bitms.change_dev = 1; /* 機器番号更新 */
    // if (get_speed_uart0() != COMM0.set_speed)
    // { /* 通信パラメーター更新 */
    //     COMM0.cflg.bitms.change_para = 1;
    // }
}
/* Clear eng parameter. @see clr_eng_ph_tbl */
/* @para rdram: true to call rdsram to update sram data. */
void clrprog_pro(BOOL rdram)
{
    WORD cn;
    WORD cmax;
    WORD phase;

    cmax = sizeof(clr_pro_ph_tbl) / 2;
    for (cn = 0; cn < cmax; cn++)
    {
        phase = clr_pro_ph_tbl[cn];
        set_data(phase, get_default(phase));
    }
    if (rdram == CLR_READ_FRAM)
    {
        rdsram();
    }
}

/* 異常履歴*/
void clr_err_rireki(BOOL rdram)
{
    WORD cn;
    WORD cmax;
    WORD phase;

    cmax = sizeof(clr_err_rireki_ph_tbl) / 2;
    for (cn = 0; cn < cmax; cn++)
    {
        phase = clr_err_rireki_ph_tbl[cn];
        set_data(phase, 0);
    }

    if (rdram == CLR_READ_FRAM)
    {
        rdsram();
    }
}
/* All Setting Data Clear. */
/* Used when clearing all data at the time of factory production */
void clr_prog(void)
{
    WORD phase;
    uint8_t ch;
    // Turn off all Output
    CNT_STAT.out_put.data = 0;
    make_IO_out(0);

    /* Clear alarm flags */
    CNT_STAT.alarm_flg1.data = 0;
    CNT_STAT.alarm_flg2.data = 0;
    // clr_in_err_hold_data();
    for (ch = 0; ch < 5; ch++)
    {
        CONTROL.input_over_flg[ch].data = 0;
    }
    KEY_MODE.flg_mode = STANDBYMD;/* モード解除でSTANDBYモード遷移するため */
    /* Parameter */
    for (phase = PH_DATA0; phase < PH_PMAX; phase++)
    {
        put_fram2(phase - PH_DATA0 + EPARAMODEL,
                  DATA_TBL_PARA[(phase - PH_DATA0) * DTID_NUMBERS + DTID_DEFAULT]);
    }
    put_fram2(CNTRL2, PASSDT2);

    /* 異常履歴 */
    for (phase = PH_CHECKD01NO; phase < PH_OTHER_MAX; phase++)
    {
        put_fram2(phase - PH_CHECKD01NO + NECHECKD01NO,
                  0);
    }

    /* Other */
    for (phase = PH_NUMYASUMI; phase < PH_DM_LAST; phase++)
    {
        put_fram2(phase - PH_NUMYASUMI + NEHOLYDAY,
                  DATA_TBL_OTHER[(phase - PH_NUMYASUMI) * DTID_NUMBERS + DTID_DEFAULT]);
    }
    put_fram2(CNTRL3, PASSDT3);

    rdsram();
    chk_eeprom();

    if ((KEY_MODE.flg_rmode != SELFMD))
    {                           /* 自己診断モードではない */
        nextmodeclr(STANDBYMD); /* スタンバイモード */
    }

    // /* update UART5 para */
    // COMM0.cflg.bitms.change_dev = 1; /* 機器番号更新 */
    // if (get_speed_uart0() != COMM0.set_speed)
    // { /* 通信パラメーター更新 */
    //     COMM0.cflg.bitms.change_para = 1;
    // }
}

/* data clear */
/* Initial value when the user runs in clear mode */
/* @see CLR_MODE */
void data_clr(BYTE clrmd)
{

    WORD phase;

    // Turn off all Output
    CNT_STAT.out_put.data = 0;
    make_IO_out(0);

    switch (clrmd)
    {
    case CLR_ALL: /* All data *
     /* Parameter */
        for (phase = PH_DATA0; phase < PH_PMAX; phase++)
        {
            put_fram2(phase - PH_DATA0 + EPARAMODEL,
                      DATA_TBL_PARA[(phase - PH_DATA0) * DTID_NUMBERS + DTID_DEFAULT]);
        }
        put_fram2(CNTRL2, PASSDT2);
        /* 異常履歴 */
        for (phase = PH_CHECKD01NO; phase < PH_OTHER_MAX; phase++)
        {
            put_fram2(phase - PH_CHECKD01NO + NECHECKD01NO, 0);
        }
        /* Other */
        for (phase = PH_NUMYASUMI; phase < PH_DM_LAST; phase++)
        {
            put_fram2(phase - PH_NUMYASUMI + NEHOLYDAY, DATA_TBL_OTHER[(phase - PH_NUMYASUMI) * DTID_NUMBERS + DTID_DEFAULT]);
        }
        put_fram2(CNTRL3, PASSDT3);
        CNT_STAT.alarm_flg2.bitms.al_eeprom = 0;
        CNT_STAT.alarm_flg1.data = 0;
        CNT_STAT.alarm_flg2.data = 0;
        rdsram();
        break;
    case CLR_RIREKI: /* All data + error reset */
        clr_err_rireki(CLR_READ_FRAM);
        break;
    case CLR_PARA: /* エンジニアリン */
        clrprog_para(CLR_READ_FRAM);
        break;
    case CLR_PRO: /* Program */
        clrprog_pro(CLR_READ_FRAM);
        break;
    default:
        break;
    }
    chk_eeprom();
}
void clerachk(void)
{
    if (FACT_DATA.clr_cmd)
    {
        data_clr(FACT_DATA.clr_mode);
        FACT_DATA.clr_cmd = false;
    }
}

void sysClear(void)
{ /* システムクリア */
    put_fram2(EOPUSE, 0);
    put_fram2(ESETTYPE, 0);
    put_fram2(CNTRL1, PASSDT1);
    rdsramajs(); /* 調整値 */
    chk_eeprom();
}

void adjsave(void)
{ /* 調整データバックアップ */
    uint16_t i;
    uint16_t *p;
    uint16_t addr;
    uint16_t quality;

    p = &IN_AJUST.settype;
    p++;
    addr = ESETTYPE + 1;
    quality = CNTRL1 - addr;

    for (i = 0; i < quality; i++)
    {
        put_fram2(addr + i, *p++);
    }
}

/* free fram clear */
// void freeFramClr(void){
//     uint16_t i;

//     for ( i = EFREE_START; i <= EFREE_END; i++)
//     {
//         wdtcou1 = 0;
//         put_fram2(i, 0);
//     }

// }
