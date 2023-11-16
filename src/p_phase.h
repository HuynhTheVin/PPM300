/*
 * p_phase.h
 *
 *  Created on: 2023/06/12
 *      Author: VINH-NT
 */

#ifndef P_PHASE_H_
#define P_PHASE_H_

/* phase number. */
/* Note: the Order must be same EEPROM and SRAM . */
enum SET_PHASE
{
    /* Gruop Parameter Axxxx */
    /* note: The order should be the same for FRAM and SRAM. */
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
    PH_DATA41,  // A0041  除霜ヒータOFF条件温度差設定(庫内)
    PH_DATA42,  // A0042  除霜ヒータOFF条件温度差設定(庫内)に対するディファレンシャル設定
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
    PH_DATA98,  // A0098  通信機器番号
    PH_DATA99,  // A0099  通信速度
    PH_DATA100, // A0100  通信パリティビット
    PH_DATA101, // A0101  通信ストップビット
    PH_DATA102, // A0102  予約
    PH_DATA103, // A0103  予約
    PH_DATA104, // A0104  予約
    PH_DATA105, // A0105  予約
    PH_DATA106, // A0106  予約
    PH_DATA107, // A0107  予約
    PH_DATA108, // A0108  予約
    PH_DATA109, // A0109  予約
    PH_DATA110, // A0110  予約
    PH_DATA111, // A0111  予約
    PH_DATA112, // A0112  予約
    PH_DATA113, // A0113  予約
    PH_DATA114, // A0114  予約
    PH_DATA115, // A0115  予約
    PH_DATA116, // A0116  予約
    PH_DATA117, // A0117  予約
    PH_DATA118, // A0118  予約
    PH_DATA119, // A0119  予約
    PH_DATA120, // A0120  予約
    PH_DATA121, // A0121  予約
    PH_DATA122, // A0122  予約
    PH_DATA123, // A0123  予約
    PH_DATA124, // A0124  予約
    PH_DATA125, // A0125  予約
    PH_DATA126, // A0126  予約
    PH_DATA127, // A0127  予約
    PH_DATA128, // A0128  予約
    PH_DATA129, // A0129  予約
    PH_DATA130, // A0130  予約
    PH_DATA131, // A0131  予約
    PH_DATA132, // A0132  予約
    PH_DATA133, // A0133  予約
    PH_DATA134, // A0134  予約
    PH_DATA135, // A0135  予約
    PH_DATA136, // A0136  予約
    PH_DATA137, // A0137  予約
    PH_DATA138, // A0138  予約
    PH_DATA139, // A0139  予約
    PH_DATA140, // A0140  予約
    PH_DATA141, // A0141  予約
    PH_DATA142, // A0142  予約
    PH_DATA143, // A0143  予約
    PH_DATA144, // A0144  予約
    PH_DATA145, // A0145  予約
    PH_DATA146, // A0146  予約
    PH_DATA147, // A0147  予約
    PH_DATA148, // A0148  予約
    PH_DATA149, // A0149  予約
    PH_DATA150, // A0150  予約
    PH_DATA151, // A0151  予約
    PH_DATA152, // A0152  予約
    PH_DATA153, // A0153  予約
    PH_DATA154, // A0154  予約
    PH_DATA155, // A0155  予約
    PH_DATA156, // A0156  予約
    PH_DATA157, // A0157  予約
    PH_DATA158, // A0158  予約
    PH_DATA159, // A0159  予約
    PH_DATA160, // A0160  予約
    PH_DATA161, // A0161  予約
    PH_DATA162, // A0162  予約
    PH_DATA163, // A0163  予約
    PH_DATA164, // A0164  予約
    PH_DATA165, // A0165  予約
    PH_DATA166, // A0166  予約
    PH_DATA167, // A0167  予約
    PH_DATA168, // A0168  予約
    PH_DATA169, // A0169  予約
    PH_DATA170, // A0170  予約
    PH_DATA171, // A0171  予約
    PH_DATA172, // A0172  予約
    PH_DATA173, // A0173  予約
    PH_DATA174, // A0174  予約
    PH_DATA175, // A0175  予約
    PH_DATA176, // A0176  予約
    PH_DATA177, // A0177  予約
    PH_DATA178, // A0178  予約
    PH_DATA179, // A0179  予約
    PH_DATA180, // A0180  予約
    PH_DATA181, // A0181  予約
    PH_DATA182, // A0182  予約
    PH_DATA183, // A0183  予約
    PH_DATA184, // A0184  予約
    PH_DATA185, // A0185  予約
    PH_DATA186, // A0186  予約
    PH_DATA187, // A0187  予約
    PH_DATA188, // A0188  予約
    PH_DATA189, // A0189  予約
    PH_DATA190, // A0190  予約
    PH_DATA191, // A0191  予約
    PH_DATA192, // A0192  予約
    PH_DATA193, // A0193  予約
    PH_DATA194, // A0194  予約
    PH_DATA195, // A0195  予約
    PH_DATA196, // A0196  予約
    PH_DATA197, // A0197  予約
    PH_DATA198, // A0198  予約
    PH_DATA199, // A0199  予約
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
    PH_DATA210, // A0210  温度表示範囲下限値を設定。
    PH_DATA211, // A0211  温度表示範囲上限値を設定。
    PH_DATA212, // A0212  温度設定範囲下限値を設定。
    PH_DATA213, // A0213  温度設定範囲上限値を設定。
    PH_DATA214, // A0214  温度表示範囲下限値を設定。
    PH_DATA215, // A0215  温度表示範囲上限値を設定。
    PH_DATA216, // A0216  温度設定範囲下限値を設定。
    PH_DATA217, // A0217  温度設定範囲上限値を設定。
    PH_DATAMAX, // Area distinction dummy phase

    /* note: The order should be the same for FRAM and SRAM. */
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
    PH_CHECKD20MINUTE,   //  点検履歴   時刻　分
    PH_RYCNT1L,          //  リレー累積ON回数 DHH
    PH_RYCNT1H,          //  リレー累積ON回数 DHH
    PH_RYCNT2L,          //  リレー累積ON回数 DH
    PH_RYCNT2H,          //  リレー累積ON回数 DH
    PH_RYCNT3L,          //  リレー累積ON回数 FAN1
    PH_RYCNT3H,          //  リレー累積ON回数 FAN1
    PH_RYCNT4L,          //  リレー累積ON回数 FAN2
    PH_RYCNT4H,          //  リレー累積ON回数 FAN2
    PH_RYCNT5L,          //  リレー累積ON回数 FAN3
    PH_RYCNT5H,          //  リレー累積ON回数 FAN3
    PH_RYCNT6L,          //  リレー累積ON回数 TA
    PH_RYCNT6H,          //  リレー累積ON回数 TA
    PH_RYCNT7L,          //  リレー累積ON回数 SV1
    PH_RYCNT7H,          //  リレー累積ON回数 SV1
    PH_RYCNT8L,          //  リレー累積ON回数 SV2
    PH_RYCNT8H,          //  リレー累積ON回数 SV2
    PH_RYCNT9L,          //  リレー累積ON回数 SV3
    PH_RYCNT9H,          //  リレー累積ON回数 SV3
    PH_RYCNT10L,         //  リレー累積ON回数 SV4
    PH_RYCNT10H,         //  リレー累積ON回数 SV4
    PH_RYCNT11L,         //  リレー累積ON回数 CPC
    PH_RYCNT11H,         //  リレー累積ON回数 CPC
    PH_RYCNT12L,         //  リレー累積ON回数 HG1
    PH_RYCNT12H,         //  リレー累積ON回数 HG1
    PH_RYCNT13L,         //  リレー累積ON回数 DM1
    PH_RYCNT13H,         //  リレー累積ON回数 DM1
    PH_RYCNT14L,         //  リレー累積ON回数 DM2
    PH_RYCNT14H,         //  リレー累積ON回数 DM2
    PH_RYCNT15L,         //  リレー累積ON回数 DM3
    PH_RYCNT15H,         //  リレー累積ON回数 DM3
    PH_RYCNT16L,         //  リレー累積ON回数 LA
    PH_RYCNT16H,         //  リレー累積ON回数 LA
    PH_OTHER_MAX,        // Area distinction dummy phase

    /* note: The order should be the same for FRAM and SRAM. */
    PH_NUMYASUMI,        //  休日日数
    PH_KANETU,           //  加熱動作有効/無効選択
    PH_MEM1REITOU,       //  メモリ1　冷凍温度設定
    PH_MEM1REITOUZOU,    //  メモリ1　冷凍・冷蔵温度設定
    PH_MEM1TIME,         //  メモリ1　切替り時刻設定
    PH_JOSOUHOUSHIKI,    //  除霜方式
    PH_JOSOUSTARTTIME1,  //  除霜開始時刻 1
    PH_JOSOUSTARTTIME2,  //  除霜開始時刻 2
    PH_JOSOUSTARTTIME3,  //  除霜開始時刻 3
    PH_JOSOUSTARTTIME4,  //  除霜開始時刻 4
    PH_JOSOUSTARTTIME5,  //  除霜開始時刻 5
    PH_JOSOUSTARTTIME6,  //  除霜開始時刻 6
    PH_JOSOUSTARTTIME7,  //  除霜開始時刻 7
    PH_JOSOUSTARTTIME8,  //  除霜開始時刻 8
    PH_JOSOUSTARTTIME9,  //  除霜開始時刻 9
    PH_JOSOUSTARTTIME10, //  除霜開始時刻 10
    PH_MODE,             //  電源断時の運転状態
    PH_RUNMD,            //  電源断時の運転モード状態（手動）
    PH_CF4MD,            //  電源断時のcf4モード状態（手動加湿）
    PH_RCTCUNT,          //  RCT入力ON回数
    PH_YOBI_01,          //  dummy
    PH_YOBI_02,          //  dummy
    PH_YOBI_03,          //  dummy
    PH_YOBI_04,          //  dummy
    PH_YOBI_05,          //  dummy
    PH_YOBI_06,          //  dummy
    PH_YOBI_07,          //  dummy
    PH_YOBI_08,          //  dummy
    PH_YOBI_09,          //  dummy
    PH_DUMMY,            /*  Area distinction dummy phase. */
    PH_PASS3,            //  ﾒﾓﾘｰ ｺﾝﾄﾛｰﾙ ﾁｴﾂｸ.2 (55AAH)  
    PH_DM_LAST           //  Area distinction dummy phase. This is last phase.

};
#endif /* P_PHASE_H_ */
