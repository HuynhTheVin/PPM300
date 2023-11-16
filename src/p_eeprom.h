/*
 * p_eeprom.h
 *
 *  Created on: 2023/05/29
 *      Author: VINH-NT
 */

#ifndef P_EEPROM_H_
#define P_EEPROM_H_

#include "p_mainh.h"
/* 入力調整値 */
#define MMAXCH 3    /* マルチ入力数 */
#define MAXCH 5     /* 入力数       */
#define MMAXINPUT 5 /* number of input chanel */
#define PH_PMAX 122 /**/
#define PASSDT1 0x5555
#define PASSDT2 0xAAAA
#define PASSDT3 0xA55A

enum EPRADR2
{
    /* 製品情報 */
    ESYSTEM_ID0, //  0 開発番号: xxxx。  0：D版
    ESYSTEM_ID1, //  1 開発番号      -xx。
    ESYSTEM_ID2, //  2 MP番号 MPxxxx
    ESYSTEM_ID3, //  3 MP番号 MPxxxx-xx
    ESYSTEM0,    //  4 工場製品情報
    ESYSTEM1,    //  5 工場製品情報
    ESYSTEM2,    //  6 工場製品情報 (ハードウェアバージョン)
    ESYSTEM3,    //  7 工場製品情報 (製品コード)
    ESYSTEM4,    //  8 工場製品情報 (配線方式)
    ESYSTEM5,    //  9 工場製品情報 (製造年月)
    EOPUSE,      // 10  オプション機能指定１
    ESETTYPE,    // 11  出力形態選択
    /* ajust & function */
    EPTAJZH1,  //  12  抵抗体式入力ゼロ調整値(庫内温度入力Pt100) (上位)
    EPTAJZL1,  //  13 抵抗体式入力ゼロ調整値(庫内温度入力Pt100) (下位)
    EPTAJSH1,  //  14 スパン調整値(上位)
    EPTAJSL1,  //  15 スパン調整値(下位)
    EOFFSETH1, //  16 0℃入力時のオフセット(上位)
    EOFFSETL1, //  17 0℃入力時のオフセット(下位)
    EAJREFH1,  //  18 調整時の 抵抗ゲインのゼロ入力(上位)
    EAJREFL1,  //  19 調整時の 抵抗ゲインのゼロ入力(下位)
    EDCVAJZH2, //     電圧入力ゼロ調整値 0～1V(湿度入力 0～1V)(上位)
    EDCVAJZL2, //     電圧入力ゼロ調整値 0～1V(湿度入力 0～1V)(下位)
    EDCVAJSH2, //     スパン調整値(上位)
    EDCVAJSL2, //     スパン調整値(下位)
    EDCVOFSH2, //     0V入力時のオフセット(上位)
    EDCVOFSL2, //     0V入力時のオフセット(下位)
    ETCAJZH3,  //     熱電対式入力ゼロ調整値(上位)(マルチ入力1)
    ETCAJZL3,  //     熱電対式入力ゼロ調整値(下位)(マルチ入力1)
    ETCAJZH4,  //     熱電対式入力ゼロ調整値(上位)(マルチ入力2)
    ETCAJZL4,  //     熱電対式入力ゼロ調整値(下位)(マルチ入力2)
    ETCAJZH5,  //     熱電対式入力ゼロ調整値(上位)(マルチ入力3)
    ETCAJZL5,  //     熱電対式入力ゼロ調整値(下位)(マルチ入力3)
    ETCAJSH3,  //     スパン調整値(上位)(マルチ入力1)
    ETCAJSL3,  //     スパン調整値(下位)(マルチ入力1)
    ETCAJSH4,  //     スパン調整値(上位)(マルチ入力2)
    ETCAJSL4,  //     スパン調整値(下位)(マルチ入力2)
    ETCAJSH5,  //     スパン調整値(上位)(マルチ入力3)
    ETCAJSL5,  //     スパン調整値(下位)(マルチ入力3)
    EAJTZH3,   //     端子温度1ゼロ調整値(上位)(マルチ入力1)
    EAJTZL3,   //     端子温度1ゼロ調整値(下位)(マルチ入力1)
    EAJTZH4,   //     端子温度1ゼロ調整値(上位)(マルチ入力2)
    EAJTZL4,   //     端子温度1ゼロ調整値(下位)(マルチ入力2)
    EAJTZH5,   //     端子温度1ゼロ調整値(上位)(マルチ入力3)
    EAJTZL5,   //     端子温度1ゼロ調整値(下位)(マルチ入力3)
    EPTAJZH3,  //     抵抗体式入力ゼロ調整値(上位)(マルチ入力1)
    EPTAJZL3,  //     抵抗体式入力ゼロ調整値(下位)(マルチ入力1)
    EPTAJZH4,  //     抵抗体式入力ゼロ調整値(上位)(マルチ入力2)
    EPTAJZL4,  //     抵抗体式入力ゼロ調整値(下位)(マルチ入力2)
    EPTAJZH5,  //     抵抗体式入力ゼロ調整値(上位)(マルチ入力3)
    EPTAJZL5,  //     抵抗体式入力ゼロ調整値(下位)(マルチ入力3)
    EPTAJSH3,  //     スパン調整値(上位)(マルチ入力1)
    EPTAJSL3,  //     スパン調整値(下位)(マルチ入力1)
    EPTAJSH4,  //     スパン調整値(上位)(マルチ入力2)
    EPTAJSL4,  //     スパン調整値(下位)(マルチ入力2)
    EPTAJSH5,  //     スパン調整値(上位)(マルチ入力3)
    EPTAJSL5,  //     スパン調整値(下位)(マルチ入力3)
    EOFFSETH3, //     0℃入力時のオフセット(上位)(マルチ入力1)
    EOFFSETL3, //     0℃入力時のオフセット(下位)(マルチ入力1)
    EOFFSETH4, //     0℃入力時のオフセット(上位)(マルチ入力2)
    EOFFSETL4, //     0℃入力時のオフセット(下位)(マルチ入力2)
    EOFFSETH5, //     0℃入力時のオフセット(上位)(マルチ入力3)
    EOFFSETL5, //     0℃入力時のオフセット(下位)(マルチ入力3)
    EAJREFH3,  //     調整時の 抵抗ゲインのゼロ入力(上位)(マルチ入力1)
    EAJREFL3,  //     調整時の 抵抗ゲインのゼロ入力(下位)(マルチ入力1)
    EAJREFH4,  //     調整時の 抵抗ゲインのゼロ入力(上位)(マルチ入力2)
    EAJREFL4,  //     調整時の 抵抗ゲインのゼロ入力(下位)(マルチ入力2)
    EAJREFH5,  //     調整時の 抵抗ゲインのゼロ入力(上位)(マルチ入力3)
    EAJREFL5,  //     調整時の 抵抗ゲインのゼロ入力(下位)(マルチ入力3)
    EANTAJZ1,  //     伝送出力ゼロ調整
    EANTAJZ2,  //     スパン調整
    EANTAJS1,  //     伝送出力ゼロ調整
    EANTAJS2,  //     スパン調整
    CNTRL1,    //     ﾒﾓﾘｰ ｺﾝﾄﾛｰﾙ ﾁｴﾂｸ.1 (5555H)
/* SPECAL  set data */
#define PARA_DATA_MAX 218
    EPARAMODEL,                          /*  未使用  */
    EPARADATA0,                          // A0000 MC入力OFF確定時間を設定。
    CNTRL2 = EPARADATA0 + PARA_DATA_MAX, /* ﾒﾓﾘｰ ｺﾝﾄﾛｰﾙ ﾁｴﾂｸ.2 (AAAAH)           */
    // その他設定と状態保存用
    NECHECKD01NO,       /*  点検履歴   点検番号      */
    NECHECKD02NO,       /*  点検履歴   点検番号      */
    NECHECKD03NO,       /*  点検履歴   点検番号      */
    NECHECKD04NO,       /*  点検履歴   点検番号      */
    NECHECKD05NO,       /*  点検履歴   点検番号      */
    NECHECKD06NO,       /*  点検履歴   点検番号      */
    NECHECKD07NO,       /*  点検履歴   点検番号      */
    NECHECKD08NO,       /*  点検履歴   点検番号      */
    NECHECKD09NO,       /*  点検履歴   点検番号      */
    NECHECKD10NO,       /*  点検履歴   点検番号      */
    NECHECKD11NO,       /*  点検履歴   点検番号      */
    NECHECKD12NO,       /*  点検履歴   点検番号      */
    NECHECKD13NO,       /*  点検履歴   点検番号      */
    NECHECKD14NO,       /*  点検履歴   点検番号      */
    NECHECKD15NO,       /*  点検履歴   点検番号      */
    NECHECKD16NO,       /*  点検履歴   点検番号      */
    NECHECKD17NO,       /*  点検履歴   点検番号      */
    NECHECKD18NO,       /*  点検履歴   点検番号      */
    NECHECKD19NO,       /*  点検履歴   点検番号      */
    NECHECKD20NO,       /*  点検履歴   点検番号      */
    NECHECKD01AD,       /*  点検履歴   西暦      */
    NECHECKD02AD,       /*  点検履歴   西暦      */
    NECHECKD03AD,       /*  点検履歴   西暦      */
    NECHECKD04AD,       /*  点検履歴   西暦      */
    NECHECKD05AD,       /*  点検履歴   西暦      */
    NECHECKD06AD,       /*  点検履歴   西暦      */
    NECHECKD07AD,       /*  点検履歴   西暦      */
    NECHECKD08AD,       /*  点検履歴   西暦      */
    NECHECKD09AD,       /*  点検履歴   西暦      */
    NECHECKD10AD,       /*  点検履歴   西暦      */
    NECHECKD11AD,       /*  点検履歴   西暦      */
    NECHECKD12AD,       /*  点検履歴   西暦      */
    NECHECKD13AD,       /*  点検履歴   西暦      */
    NECHECKD14AD,       /*  点検履歴   西暦      */
    NECHECKD15AD,       /*  点検履歴   西暦      */
    NECHECKD16AD,       /*  点検履歴   西暦      */
    NECHECKD17AD,       /*  点検履歴   西暦      */
    NECHECKD18AD,       /*  点検履歴   西暦      */
    NECHECKD19AD,       /*  点検履歴   西暦      */
    NECHECKD20AD,       /*  点検履歴   西暦      */
    NECHECKD01MONTHDAY, /*  点検履歴   月日      */
    NECHECKD02MONTHDAY, /*  点検履歴   月日      */
    NECHECKD03MONTHDAY, /*  点検履歴   月日      */
    NECHECKD04MONTHDAY, /*  点検履歴   月日      */
    NECHECKD05MONTHDAY, /*  点検履歴   月日      */
    NECHECKD06MONTHDAY, /*  点検履歴   月日      */
    NECHECKD07MONTHDAY, /*  点検履歴   月日      */
    NECHECKD08MONTHDAY, /*  点検履歴   月日      */
    NECHECKD09MONTHDAY, /*  点検履歴   月日      */
    NECHECKD10MONTHDAY, /*  点検履歴   月日      */
    NECHECKD11MONTHDAY, /*  点検履歴   月日      */
    NECHECKD12MONTHDAY, /*  点検履歴   月日      */
    NECHECKD13MONTHDAY, /*  点検履歴   月日      */
    NECHECKD14MONTHDAY, /*  点検履歴   月日      */
    NECHECKD15MONTHDAY, /*  点検履歴   月日      */
    NECHECKD16MONTHDAY, /*  点検履歴   月日      */
    NECHECKD17MONTHDAY, /*  点検履歴   月日      */
    NECHECKD18MONTHDAY, /*  点検履歴   月日      */
    NECHECKD19MONTHDAY, /*  点検履歴   月日      */
    NECHECKD20MONTHDAY, /*  点検履歴   月日      */
    NECHECKD01MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD02MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD03MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD04MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD05MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD06MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD07MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD08MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD09MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD10MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD11MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD12MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD13MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD14MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD15MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD16MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD17MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD18MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD19MINUTE,   /*  点検履歴   時刻　分      */
    NECHECKD20MINUTE,   /*  点検履歴   時刻　分      */
    NERYCNT1L,          /*  リレー累積ON回数 DHH          */
    NERYCNT1H,          /*  リレー累積ON回数 DHH          */
    NERYCNT2L,          /*  リレー累積ON回数 DH           */
    NERYCNT2H,          /*  リレー累積ON回数 DH           */
    NERYCNT3L,          /*  リレー累積ON回数 FAN1         */
    NERYCNT3H,          /*  リレー累積ON回数 FAN1         */
    NERYCNT4L,          /*  リレー累積ON回数 FAN2         */
    NERYCNT4H,          /*  リレー累積ON回数 FAN2         */
    NERYCNT5L,          /*  リレー累積ON回数 FAN3           */
    NERYCNT5H,          /*  リレー累積ON回数 FAN3          */
    NERYCNT6L,          /*  リレー累積ON回数 TA          */
    NERYCNT6H,          /*  リレー累積ON回数 TA          */
    NERYCNT7L,          /*  リレー累積ON回数 SV1          */
    NERYCNT7H,          /*  リレー累積ON回数 SV1          */
    NERYCNT8L,          /*  リレー累積ON回数 SV2          */
    NERYCNT8H,          /*  リレー累積ON回数 SV2          */
    NERYCNT9L,          /*  リレー累積ON回数 SV3          */
    NERYCNT9H,          /*  リレー累積ON回数 SV3          */
    NERYCNT10L,         /*  リレー累積ON回数 SV4          */
    NERYCNT10H,         /*  リレー累積ON回数 SV4          */
    NERYCNT11L,         /*  リレー累積ON回数 CPC          */
    NERYCNT11H,         /*  リレー累積ON回数 CPC          */
    NERYCNT12L,         /*  リレー累積ON回数 HG1         */
    NERYCNT12H,         /*  リレー累積ON回数 HG1         */
    NERYCNT13L,         /*  リレー累積ON回数 DM1         */
    NERYCNT13H,         /*  リレー累積ON回数 DM1         */
    NERYCNT14L,         /*  リレー累積ON回数 DM2         */
    NERYCNT14H,         /*  リレー累積ON回数 DM2         */
    NERYCNT15L,         /*  リレー累積ON回数 DM3         */
    NERYCNT15H,         /*  リレー累積ON回数 DM3         */
    NERYCNT16L,         /*  リレー累積ON回数 LA         */
    NERYCNT16H,         /*  リレー累積ON回数 LA         */

    /*  Direct set data */
    NEHOLYDAY,          /*  休日日数 cf7                    */
    NEKANETU,           /*  加熱動作有効/無効選択                   */
    NEMEM1REITOU,       /* メモリ1　冷凍温度設定        */
    NEMEM1REITOUZOU,    /* メモリ1　冷凍・冷蔵温度設定   */
    NEMEM1TIME,         /* メモリ1　切替り時刻設定      */
    NEJOSOUHOUSHIKI,    /* 除霜方式                    */
    NEJOSOUSTARTTIME1,  /* 除霜開始時刻 1  */
    NEJOSOUSTARTTIME2,  /* 除霜開始時刻 2  */
    NEJOSOUSTARTTIME3,  /* 除霜開始時刻 3  */
    NEJOSOUSTARTTIME4,  /* 除霜開始時刻 4  */
    NEJOSOUSTARTTIME5,  /* 除霜開始時刻 5  */
    NEJOSOUSTARTTIME6,  /* 除霜開始時刻 6  */
    NEJOSOUSTARTTIME7,  /* 除霜開始時刻 7  */
    NEJOSOUSTARTTIME8,  /* 除霜開始時刻 8  */
    NEJOSOUSTARTTIME9,  /* 除霜開始時刻 9  */
    NEJOSOUSTARTTIME10, /* 除霜開始時刻 10  */
    NEMODE,             /*  電源断時の運転状態              */
    NERUNMD,            /*  電源断時の運転モード状態（手動）*/
    NECF4MD,            /*  電源断時のcf4モード状態（手動加湿）*/
    NERCTCUNT,          /* RCT入力ON回数 */
    NEYOBI_01,          /*  dummy */
    NEYOBI_02,          /*  dummy */
    NEYOBI_03,          /*  dummy */
    NEYOBI_04,          /*  dummy */
    NEYOBI_05,          /*  dummy */
    NEYOBI_06,          /*  dummy */
    NEYOBI_07,          /*  dummy */
    NEYOBI_08,          /*  dummy */
    NEYOBI_09,          /*  dummy */
    CNTRL3,             /* ﾒﾓﾘｰ ｺﾝﾄﾛｰﾙ ﾁｴﾂｸ.2 (55AAH)        */
    EFRAM_MAX,
    EFREE_START = 0x0C00,
    EFREE_END = 0x0FFF
    /* 64Kb FRAM = 0x0000～0x0FFF (4096 Word) */

};

enum EPRADR
{
    /* SPECAL  set data */
    PARAMODEL = EPARAMODEL, /*  A0000  MC入力OFF確定時間を設定  */
    NEPDATA0,               // A0000  MC入力OFF確定時間を設定。
    NEPDATA1,               // A0001  冷却動作再確認時間を設定
    NEPDATA2,               // A0002  点検「A」発生時の冷凍機ON時間を設定。
    NEPDATA3,               // A0003  点検「A」発生時の冷凍機OFF時間を設定。
    NEPDATA4,               // A0004  加熱「強」のON時間を設定。
    NEPDATA5,               // A0005  加熱「強」のOFF時間を設定。
    NEPDATA6,               // A0006  除霜サイクル時間を設定。
    NEPDATA7,               // A0007  除霜時間(庫内温度「高」用)を設定。
    NEPDATA8,               // A0008  除霜時間(庫内温度「中」用)を設定。
    NEPDATA9,               // A0009  除霜時間(庫内温度「低」用)を設定。
    NEPDATA10,              // A0010  除霜不可の温度差(現在温度に対しての温度差)を設定。
    NEPDATA11,              // A0011  除霜不可の温度差継続時間を設定。
    NEPDATA12,              // A0012  冷却不良監視の有効/無効を選択。
    NEPDATA13,              // A0013  異常表示「L」監視の有効/無効を選択。
    NEPDATA14,              // A0014  除霜解除コマンド受信時の除霜サイクル時間(1サイクルのみ)を設定。
    NEPDATA15,              // A0015  異常表示「P」監視の有効/無効を選択。
    NEPDATA16,              // A0016  除霜解除回数を設定。
    NEPDATA17,              // A0017  加熱「弱」のON時間を設定。
    NEPDATA18,              // A0018  加熱「弱」のOFF時間を設定。
    NEPDATA19,              // A0019  予約
    NEPDATA20,              // A0020  予約
    NEPDATA21,              // A0021  予約
    NEPDATA22,              // A0022  冷凍・冷蔵モード加熱2動作時、FAN1 ON周期時間を設定。(切替り1秒含む)
    NEPDATA23,              // A0023  冷凍・冷蔵モード加熱2動作時、FAN2 ON周期時間を設定。(切替り1秒含む)
    NEPDATA24,              // A0024  ドレンホースヒータON開始時刻を設定。(除霜開始直前の時間)
    NEPDATA25,              // A0025  予約
    NEPDATA26,              // A0026  MCチャタリング監視時間を設定。
    NEPDATA27,              // A0027  MCチャタリング監視時間内のON/OFF回数を設定。
    NEPDATA28,              // A0028  予約
    NEPDATA29,              // A0029  予約
    NEPDATA30,              // A0030  加熱「強」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
    NEPDATA31,              // A0031  加熱「強」で庫内温度設定に対して加熱出力がONする温度差を設定。(メモリ3の冷凍・冷蔵モードのみ)
    NEPDATA32,              // A0032  冷凍機起動時のGA出力繰り返し回数を設定。
    NEPDATA33,              // A0033  庫内温度設定に対して冷却信号がOFFする温度差を設定。
    NEPDATA34,              // A0034  庫内温度設定に対して冷却信号がONする温度差を設定。
    NEPDATA35,              // A0035  冷凍機起動時のGA出力ON時間を設定
    NEPDATA36,              // A0036  冷凍機起動時のGA出力OFF時間を設定。
    NEPDATA37,              // A0037  予約
    NEPDATA38,              // A0038  GA出力OFF後M1出力(CPC)がOFFするまでの時間を設定。
    NEPDATA39,              // A0039  SV2出力インチング動作(電源投入時)の有効/無効を選択。
    NEPDATA40,              // A0040  SV2出力インチング動作(除霜終了時)の有効/無効を選択。
    NEPDATA41,              // A0041  除霜ヒータOFF条件温度差設定(庫内)
    NEPDATA42,              // A0042  除霜ヒータOFF条件温度差設定(庫内)に対するディファレンシャル設定
    NEPDATA43,              // A0043  A0043
    NEPDATA44,              // A0044  A0044
    NEPDATA45,              // A0045  A0045
    NEPDATA46,              // A0046  異常「4」発生カウント数を設定。
    NEPDATA47,              // A0047  予約
    NEPDATA48,              // A0048  SV4出力がOFFする温度を設定。
    NEPDATA49,              // A0049  SV4出力がONする温度差を設定。(A0048に対して)
    NEPDATA50,              // A0050  予約
    NEPDATA51,              // A0051  加熱「弱」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
    NEPDATA52,              // A0052  加熱「弱」で庫内温度設定に対して加熱出力がONする温度差を設定。
    NEPDATA53,              // A0053  予約
    NEPDATA54,              // A0054  水切り時間を設定。
    NEPDATA55,              // A0055  加熱2終了時のFAN1の遅延時間を設定。(メモリ3の冷凍・冷蔵モードのみ)
    NEPDATA56,              // A0056  冷凍・冷蔵モード冷却信号ON時、FAN2 ON時間を設定。(切替り1秒含む)
    NEPDATA57,              // A0057  冷凍・冷蔵モード冷却信号ON時、FAN1 ON時間を設定。(切替り1秒含む)
    NEPDATA58,              // A0058  除霜ヒータOFF温度設定。(外部)
    NEPDATA59,              // A0059  除霜ヒータOFF温度設定(外部)に対するディファレンシャルを設定。
    NEPDATA60,              // A0060  予約
    NEPDATA61,              // A0061  除霜時間(庫内温度「中高」用)を設定。
    NEPDATA62,              // A0062  予約
    NEPDATA63,              // A0063  ドアヒータ温度設定値を設定。
    NEPDATA64,              // A0064  庫内温度センサ補正値を設定。
    NEPDATA65,              // A0065  予約
    NEPDATA66,              // A0066  予約
    NEPDATA67,              // A0067  冷却不良待ち時間を設定。
    NEPDATA68,              // A0068  除霜時間設定用庫内温度を設定。(高位)
    NEPDATA69,              // A0069  除霜時間設定用庫内温度を設定。(中位)
    NEPDATA70,              // A0070  除霜時間設定用庫内温度を設定。(低位)
    NEPDATA71,              // A0071  予約
    NEPDATA72,              // A0072  メモリ3の冷凍・冷蔵モード時、DHH出力を常時ONする温度を設定。
    NEPDATA73,              // A0073  予約
    NEPDATA74,              // A0074  予約
    NEPDATA75,              // A0075  切替り時のブザーON時間を設定。(自動切換運転時)
    NEPDATA76,              // A0076  切替り時のブザーOFF時間を設定。(自動切換運転時)
    NEPDATA77,              // A0077  切替り時のブザー回数を設定。(自動切換運転時)
    NEPDATA78,              // A0078  予約
    NEPDATA79,              // A0079  予約
    NEPDATA80,              // A0080  予約
    NEPDATA81,              // A0081  点検「L」発生時、冷却動作再確認時間(A0001)による出力回数を設定。
    NEPDATA82,              // A0082  予約
    NEPDATA83,              // A0083  運転開始時、制御開始するまでのウエイト時間を設定。
    NEPDATA84,              // A0084  冷却用制御信号M1出力(CPC)がOFF後、ONしない時間を設定。
    NEPDATA85,              // A0085  予約
    NEPDATA86,              // A0086  フリーザー/ショックフリーザーを選択。
    NEPDATA87,              // A0087  冷凍機有(固定値)
    NEPDATA88,              // A0088  除霜監視時間を設定する。
    NEPDATA89,              // A0089  予約
    NEPDATA90,              // A0090  予約
    NEPDATA91,              // A0091  予約
    NEPDATA92,              // A0092  冷凍機運転信号(MC)の判定タイプ(a接点/b接点)を選択。
    NEPDATA93,              // A0093  CPUリセット累積回数(設定不可)。
    NEPDATA94,              // A0094  予約
    NEPDATA95,              // A0095  予約
    NEPDATA96,              // A0096  SV3の緊急冷却ON時間を設定。
    NEPDATA97,              // A0097  SV3の緊急冷却OFF時間を設定。
    NEPDATA98,              // A0098  通信機器番号
    NEPDATA99,              // A0099  通信速度
    NEPDATA100,             // A0100  通信パリティビット
    NEPDATA101,             // A0101  通信ストップビット
    NEPDATA102,             // A0102  予約
    NEPDATA103,             // A0103  予約
    NEPDATA104,             // A0104  予約
    NEPDATA105,             // A0105  予約
    NEPDATA106,             // A0106  予約
    NEPDATA107,             // A0107  予約
    NEPDATA108,             // A0108  予約
    NEPDATA109,             // A0109  予約
    NEPDATA110,             // A0110  予約
    NEPDATA111,             // A0111  予約
    NEPDATA112,             // A0112  予約
    NEPDATA113,             // A0113  予約
    NEPDATA114,             // A0114  予約
    NEPDATA115,             // A0115  予約
    NEPDATA116,             // A0116  予約
    NEPDATA117,             // A0117  予約
    NEPDATA118,             // A0118  予約
    NEPDATA119,             // A0119  予約
    NEPDATA120,             // A0120  予約
    NEPDATA121,             // A0121  予約
    NEPDATA122,             // A0122  予約
    NEPDATA123,             // A0123  予約
    NEPDATA124,             // A0124  予約
    NEPDATA125,             // A0125  予約
    NEPDATA126,             // A0126  予約
    NEPDATA127,             // A0127  予約
    NEPDATA128,             // A0128  予約
    NEPDATA129,             // A0129  予約
    NEPDATA130,             // A0130  予約
    NEPDATA131,             // A0131  予約
    NEPDATA132,             // A0132  予約
    NEPDATA133,             // A0133  予約
    NEPDATA134,             // A0134  予約
    NEPDATA135,             // A0135  予約
    NEPDATA136,             // A0136  予約
    NEPDATA137,             // A0137  予約
    NEPDATA138,             // A0138  予約
    NEPDATA139,             // A0139  予約
    NEPDATA140,             // A0140  予約
    NEPDATA141,             // A0141  予約
    NEPDATA142,             // A0142  予約
    NEPDATA143,             // A0143  予約
    NEPDATA144,             // A0144  予約
    NEPDATA145,             // A0145  予約
    NEPDATA146,             // A0146  予約
    NEPDATA147,             // A0147  予約
    NEPDATA148,             // A0148  予約
    NEPDATA149,             // A0149  予約
    NEPDATA150,             // A0150  予約
    NEPDATA151,             // A0151  予約
    NEPDATA152,             // A0152  予約
    NEPDATA153,             // A0153  予約
    NEPDATA154,             // A0154  予約
    NEPDATA155,             // A0155  予約
    NEPDATA156,             // A0156  予約
    NEPDATA157,             // A0157  予約
    NEPDATA158,             // A0158  予約
    NEPDATA159,             // A0159  予約
    NEPDATA160,             // A0160  予約
    NEPDATA161,             // A0161  予約
    NEPDATA162,             // A0162  予約
    NEPDATA163,             // A0163  予約
    NEPDATA164,             // A0164  予約
    NEPDATA165,             // A0165  予約
    NEPDATA166,             // A0166  予約
    NEPDATA167,             // A0167  予約
    NEPDATA168,             // A0168  予約
    NEPDATA169,             // A0169  予約
    NEPDATA170,             // A0170  予約
    NEPDATA171,             // A0171  予約
    NEPDATA172,             // A0172  予約
    NEPDATA173,             // A0173  予約
    NEPDATA174,             // A0174  予約
    NEPDATA175,             // A0175  予約
    NEPDATA176,             // A0176  予約
    NEPDATA177,             // A0177  予約
    NEPDATA178,             // A0178  予約
    NEPDATA179,             // A0179  予約
    NEPDATA180,             // A0180  予約
    NEPDATA181,             // A0181  予約
    NEPDATA182,             // A0182  予約
    NEPDATA183,             // A0183  予約
    NEPDATA184,             // A0184  予約
    NEPDATA185,             // A0185  予約
    NEPDATA186,             // A0186  予約
    NEPDATA187,             // A0187  予約
    NEPDATA188,             // A0188  予約
    NEPDATA189,             // A0189  予約
    NEPDATA190,             // A0190  予約
    NEPDATA191,             // A0191  予約
    NEPDATA192,             // A0192  予約
    NEPDATA193,             // A0193  予約
    NEPDATA194,             // A0194  予約
    NEPDATA195,             // A0195  予約
    NEPDATA196,             // A0196  予約
    NEPDATA197,             // A0197  予約
    NEPDATA198,             // A0198  予約
    NEPDATA199,             // A0199  予約
    NEPDATA200,             // A0200  外部温度センサ1の有効/無効を選択。
    NEPDATA201,             // A0201  予約(外部温度センサ2の有効/無効を選択。)
    NEPDATA202,             // A0202  予約(外部温度センサ3の有効/無効を選択。)
    NEPDATA203,             // A0203  外部温度センサ1入力種類を選択。
    NEPDATA204,             // A0204  予約(外部温度センサ2入力種類を選択。)
    NEPDATA205,             // A0205  予約(外部温度センサ3入力種類を選択。)
    NEPDATA206,             // A0206  温度表示範囲下限値を設定。
    NEPDATA207,             // A0207  温度表示範囲上限値を設定。
    NEPDATA208,             // A0208  温度設定範囲下限値を設定。
    NEPDATA209,             // A0209  温度設定範囲上限値を設定。
    NEPDATA210,             // A0210  温度表示範囲下限値を設定。
    NEPDATA211,             // A0211  温度表示範囲上限値を設定。
    NEPDATA212,             // A0212  温度設定範囲下限値を設定。
    NEPDATA213,             // A0213  温度設定範囲上限値を設定。
    NEPDATA214,             // A0214  温度表示範囲下限値を設定。
    NEPDATA215,             // A0215  温度表示範囲上限値を設定。
    NEPDATA216,             // A0216  温度設定範囲下限値を設定。
    NEPDATA217,             // A0217  温度設定範囲上限値を設定。
    NEPDATAMAX, // Area distinction dummy phase
};
#endif /* P_EEPROM_H_ */
