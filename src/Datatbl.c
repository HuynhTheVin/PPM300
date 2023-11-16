/*
 * Datatbl.c
 *
 * Created on: 2023/06/23
 * Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.h"
#include "Datatbl.h"

/*
Data table.
note: The order should be the same for FRAM and SRAM and PHASE.
@see SET_PHASE enum for more information.
*/
const int16_t DATA_TBL_PARA[] =
    {
        /* テーブルデータ */
        /* MIN MAX DEFAULT DP DT1: B0=予約(not use) */ /* Gruop Parameter Axxxx */
        0, 999, 300, 0, 0x0000,                        // A0000 MC入力OFF確定時間を設定。
        0, 999, 3, 0, 0x0000,                          // A0001 冷却動作再確認時間を設定
        0, 999, 900, 0, 0x0000,                        // A0002 点検「A」発生時の冷凍機ON時間を設定。
        0, 999, 300, 0, 0x0000,                        // A0003 点検「A」発生時の冷凍機OFF時間を設定。
        0, 999, 60, 0, 0x0000,                         // A0004 加熱「強」のON時間を設定。
        0, 999, 5, 0, 0x0000,                          // A0005 加熱「強」のOFF時間を設定。
        0, 9999, 240, 0, 0x0000,                       // A0006 除霜サイクル時間を設定。
        0, 99, 5, 0, 0x0000,                           // A0007 除霜時間(庫内温度「高」用)を設定。
        0, 99, 15, 0, 0x0000,                          // A0008 除霜時間(庫内温度「中」用)を設定。
        0, 99, 20, 0, 0x0000,                          // A0009 除霜時間(庫内温度「低」用)を設定。
        1, 999, 50, 1, 0x0000,                         // A0010 除霜不可の温度差(現在温度に対しての温度差)を設定。
        0, 999, 120, 0, 0x0000,                        // A0011 除霜不可の温度差継続時間を設定。
        0, 1, 1, 0, 0x0000,                            // A0012 冷却不良監視の有効/無効を選択。
        0, 1, 1, 0, 0x0000,                            // A0013 異常表示「L」監視の有効/無効を選択。
        0, 9999, 120, 0, 0x0000,                       // A0014 除霜解除コマンド受信時の除霜サイクル時間(1サイクルのみ)を設定。
        0, 1, 1, 0, 0x0000,                            // A0015 異常表示「P」監視の有効/無効を選択。
        1, 99, 1, 0, 0x0000,                           // A0016 除霜解除回数を設定。
        0, 999, 35, 0, 0x0000,                         // A0017 加熱「弱」のON時間を設定。
        0, 999, 25, 0, 0x0000,                         // A0018 加熱「弱」のOFF時間を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0019 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0020 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0021 予約
        0, 999, 60, 0, 0x0000,                         // A0022 冷凍・冷蔵モード加熱2動作時、FAN1 ON周期時間を設定。(切替り1秒含む)
        0, 999, 900, 0, 0x0000,                        // A0023 冷凍・冷蔵モード加熱2動作時、FAN2 ON周期時間を設定。(切替り1秒含む)
        0, 999, 6, 0, 0x0000,                          // A0024 ドレンホースヒータON開始時刻を設定。(除霜開始直前の時間)
        -32768, 32767, 0, 0, 0x0001,                   // A0025 予約
        0, 999, 10, 0, 0x0000,                         // A0026 MCチャタリング監視時間を設定。
        0, 999, 10, 0, 0x0000,                         // A0027 MCチャタリング監視時間内のON/OFF回数を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0028 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0029 予約
        1, 999, 2, 1, 0x0000,                          // A0030 加熱「強」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
        1, 999, 20, 1, 0x0000,                         // A0031 加熱「強」で庫内温度設定に対して加熱出力がONする温度差を設定。(メモリ3の冷凍・冷蔵モードのみ)
        0, 99, 5, 0, 0x0000,                           // A0032 冷凍機起動時のGA出力繰り返し回数を設定。
        1, 999, 5, 1, 0x0000,                          // A0033 庫内温度設定に対して冷却信号がOFFする温度差を設定。
        1, 999, 5, 1, 0x0000,                          // A0034 庫内温度設定に対して冷却信号がONする温度差を設定。
        0, 99, 30, 0, 0x0000,                          // A0035 冷凍機起動時のGA出力ON時間を設定
        0, 99, 10, 0, 0x0000,                          // A0036 冷凍機起動時のGA出力OFF時間を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0037 予約
        0, 99, 20, 0, 0x0000,                          // A0038 GA出力OFF後M1出力(CPC)がOFFするまでの時間を設定。
        0, 1, 0, 0, 0x0000,                            // A0039 SV2出力インチング動作(電源投入時)の有効/無効を選択。
        0, 1, 0, 0, 0x0000,                            // A0040 SV2出力インチング動作(除霜終了時)の有効/無効を選択。
        1, 999, 150, 1, 0x0000,                        // A0041 除霜ヒータOFF条件温度差設定(庫内)
        1, 999, 10, 1, 0x0000,                         // A0042 除霜ヒータOFF条件温度差設定(庫内)に対するディファレンシャル設定
        -32768, 32767, 0, 0, 0x0000,                   // A0043 A0043
        -32768, 32767, 0, 0, 0x0000,                   // A0044 A0044
        -32768, 32767, 0, 0, 0x0000,                   // A0045 A0045
        0, 99, 10, 0, 0x0000,                          // A0046 異常「4」発生カウント数を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0047 予約
        -300, 500, -100, 1, 0x0000,                    // A0048 SV4出力がOFFする温度を設定。
        1, 999, 5, 1, 0x0000,                          // A0049 SV4出力がONする温度差を設定。(A0048に対して)
        -32768, 32767, 0, 0, 0x0001,                   // A0050 予約
        1, 999, 2, 1, 0x0000,                          // A0051 加熱「弱」で加熱出力動作スキマを設定。(メモリ3の冷凍・冷蔵モードのみ)
        1, 999, 5, 1, 0x0000,                          // A0052 加熱「弱」で庫内温度設定に対して加熱出力がONする温度差を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0053 予約
        0, 999, 1, 0, 0x0000,                          // A0054 水切り時間を設定。
        0, 999, 30, 0, 0x0000,                         // A0055 加熱2終了時のFAN1の遅延時間を設定。(メモリ3の冷凍・冷蔵モードのみ)
        0, 999, 15, 0, 0x0000,                         // A0056 冷凍・冷蔵モード冷却信号ON時、FAN2 ON時間を設定。(切替り1秒含む)
        0, 999, 3, 0, 0x0000,                          // A0057 冷凍・冷蔵モード冷却信号ON時、FAN1 ON時間を設定。(切替り1秒含む)
        -300, 500, 80, 1, 0x0000,                      // A0058 除霜ヒータOFF温度設定。(外部)
        1, 999, 5, 1, 0x0000,                          // A0059 除霜ヒータOFF温度設定(外部)に対するディファレンシャルを設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0060 予約
        0, 99, 10, 0, 0x0000,                          // A0061 除霜時間(庫内温度「中高」用)を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0062 予約
        -300, 500, 50, 1, 0x0000,                      // A0063 ドアヒータ温度設定値を設定。
        -300, 500, 0, 1, 0x0000,                       // A0064 庫内温度センサ補正値を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0065 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0066 予約
        0, 999, 240, 0, 0x0000,                        // A0067 冷却不良待ち時間を設定。
        -298, 500, 50, 1, 0x0000,                      // A0068 除霜時間設定用庫内温度を設定。(高位)
        -299, 499, -30, 1, 0x0000,                     // A0069 除霜時間設定用庫内温度を設定。(中位)
        -300, 498, -150, 1, 0x0000,                    // A0070 除霜時間設定用庫内温度を設定。(低位)
        -32768, 32767, 0, 0, 0x0001,                   // A0071 予約
        -300, 500, 50, 1, 0x0000,                      // A0072 メモリ3の冷凍・冷蔵モード時、DHH出力を常時ONする温度を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0073 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0074 予約
        0, 99, 10, 1, 0x0000,                          // A0075 切替り時のブザーON時間を設定。(自動切換運転時)
        0, 99, 10, 1, 0x0000,                          // A0076 切替り時のブザーOFF時間を設定。(自動切換運転時)
        0, 99, 5, 0, 0x0000,                           // A0077 切替り時のブザー回数を設定。(自動切換運転時)
        -32768, 32767, 0, 0, 0x0001,                   // A0078 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0079 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0080 予約
        0, 99, 5, 0, 0x0000,                           // A0081 点検「L」発生時、冷却動作再確認時間(A0001)による出力回数を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0082 予約
        0, 99, 10, 0, 0x0000,                          // A0083 運転開始時、制御開始するまでのウエイト時間を設定。
        0, 99, 3, 0, 0x0000,                           // A0084 冷却用制御信号M1出力(CPC)がOFF後、ONしない時間を設定。
        -32768, 32767, 0, 0, 0x0001,                   // A0085 予約
        2, 3, 2, 0, 0x0000,                            // A0086 フリーザー/ショックフリーザーを選択。
        1, 1, 1, 0, 0x0000,                            // A0087 冷凍機有(固定値)
        0, 999, 0, 0, 0x0000,                          // A0088 除霜監視時間を設定する。
        -32768, 32767, 0, 0, 0x0001,                   // A0089 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0090 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0091 予約
        0, 1, 1, 0, 0x0000,                            // A0092 冷凍機運転信号(MC)の判定タイプ(a接点/b接点)を選択。
        0, 9999, 0, 0, 0x0000,                         // A0093 CPUリセット累積回数(設定不可)。
        -32768, 32767, 0, 0, 0x0001,                   // A0094 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0095 予約
        0, 99, 3, 0, 0x0000,                           // A0096 SV3の緊急冷却ON時間を設定。
        0, 99, 15, 0, 0x0000,                          // A0097 SV3の緊急冷却OFF時間を設定。
        0, 95, 1, 0, 0x0000,                           // A0098 通信機器番号
        0, 2, 1, 0, 0x0000,                            // A0099 通信速度
        0, 2, 1, 0, 0x0000,                            // A0100 通信パリティビット
        0, 1, 0, 0, 0x0000,                            // A0101 通信ストップビット
        -32768, 32767, 0, 0, 0x0001,                   // A0102 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0103 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0104 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0105 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0106 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0107 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0108 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0109 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0110 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0111 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0112 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0113 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0114 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0115 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0116 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0117 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0118 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0119 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0120 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0121 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0122 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0123 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0124 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0125 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0126 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0127 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0128 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0129 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0130 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0131 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0132 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0133 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0134 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0135 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0136 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0137 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0138 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0139 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0140 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0141 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0142 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0143 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0144 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0145 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0146 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0147 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0148 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0149 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0150 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0151 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0152 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0153 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0154 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0155 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0156 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0157 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0158 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0159 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0160 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0161 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0162 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0163 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0164 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0165 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0166 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0167 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0168 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0169 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0170 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0171 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0172 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0173 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0174 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0175 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0176 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0177 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0178 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0179 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0180 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0181 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0182 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0183 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0184 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0185 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0186 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0187 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0188 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0189 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0190 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0191 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0192 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0193 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0194 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0195 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0196 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0197 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0198 予約
        -32768, 32767, 0, 0, 0x0001,                   // A0199 予約
        0, 1, 1, 0, 0x0000,                            // A0200 外部温度センサ1の有効/無効を選択。
        -32768, 32767, 0, 0, 0x0000,                   // A0201 予約(外部温度センサ2の有効/無効を選択。)
        -32768, 32767, 0, 0, 0x0000,                   // A0202 予約(外部温度センサ3の有効/無効を選択。)
        0, 2, 2, 0, 0x0000,                            // A0203 外部温度センサ1入力種類を選択。
        -32768, 32767, 0, 0, 0x0000,                   // A0204 予約(外部温度センサ2入力種類を選択。)
        -32768, 32767, 0, 0, 0x0000,                   // A0205 予約(外部温度センサ3入力種類を選択。)
        -500, 999, -500, 1, 0x0000,                    // A0206 温度表示範囲下限値を設定。
        -499, 1000, 1000, 1, 0x0000,                   // A0207 温度表示範囲上限値を設定。
        -400, 899, -250, 1, 0x0000,                    // A0208 温度設定範囲下限値を設定。
        -399, 900, 150, 1, 0x0000,                     // A0209 温度設定範囲上限値を設定。
        -500, 999, -500, 1, 0x0000,                    // A0210 温度表示範囲下限値を設定。
        -499, 1000, 1000, 1, 0x0000,                   // A0211 温度表示範囲上限値を設定。
        -400, 899, -250, 1, 0x0000,                    // A0212 温度設定範囲下限値を設定。
        -399, 900, 150, 1, 0x0000,                     // A0213 温度設定範囲上限値を設定。
        -500, 999, -500, 1, 0x0000,                    // A0214 温度表示範囲下限値を設定。
        -499, 1000, 1000, 1, 0x0000,                   // A0215 温度表示範囲上限値を設定。
        -400, 899, -250, 1, 0x0000,                    // A0216 温度設定範囲下限値を設定。
        -399, 900, 150, 1, 0x0000,                     // A0217 温度設定範囲上限値を設定。
        0, 0, 0, 0, 0x0001                             /*  PMAX Area distinction dummy phase */
};

const int16_t DATA_TBL_OTHER[] =
    {
        /*   MIN    MAX  DEFAULT      DP  DT1: B0=予約(not use)  */
        /* Group  Other Setting Phase */
        0, 9, 0, 0, 0x0000,       //  休日日数
        0, 1, 0, 0, 0x0000,       //  加熱動作有効/無効選択
        -500, 1000, 0, 1, 0x0000,  //  メモリ1　冷凍温度設定
        -500, 1000, 0, 1, 0x0000,  //  メモリ1　冷凍・冷蔵温度設定
        0, 1439, 0, 0, 0x0000,    //  メモリ1　切替り時刻設定
        0, 1, 0, 0, 0x0000,       //  除霜方式
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 1
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 2
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 3
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 4
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 5
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 6
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 7
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 8
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 9
        0, 1439, 0, 0, 0x0000,    //  除霜開始時刻 10
        0, 0, 0, 0, 0x0000,       //  電源断時の運転状態
        0, 0, 0, 0, 0x0000,       //  電源断時の運転モード状態（手動）
        0, 0, 0, 0, 0x0000,       //  電源断時のcf4モード状態（手動加湿）
        0, 0, 0, 0, 0x0000,       //  RCT入力ON回数
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  dummy
        0, 0, 0, 0, 0x0001,       //  PH_DUMMY,    Area distinction dummy phase. */
        0, 0, PASSDT3, 0, 0x0001, //  ﾒﾓﾘｰ ｺﾝﾄﾛｰﾙ ﾁｴﾂｸ.３ (55AAH)  
        0, 0, 0, 0, 0x0001        //  PH_DM_LAST Area distinction dummy phase. This is last phase. */
};

int16_t *data_tbl_addr_base[] = {
    (int16_t *)&DATA_TBL_PARA,
    (int16_t *)&dummy,
    (int16_t *)&DATA_TBL_OTHER};
int16_t *data_tbl_sram_base[] = {
    (int16_t *)&SET_PARA.setpara,
    (int16_t *)&SET_PARA.nerrcode01,
    (int16_t *)&SET_PARA.dummy};
WORD data_tbl_phase_base[] = {
    PH_DATA0,
    PH_CHECKD01NO,
    PH_NUMYASUMI};
WORD data_tbl_eep_base[] = {
    EPARADATA0,
    NECHECKD01NO,
    NEHOLYDAY};

WORD get_eep_para(WORD phase)
{
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    return data_tbl_eep_base[DTGR_PARA] + (phase - data_tbl_phase_base[DTGR_PARA]);
}
/* read parameter data */
int16_t get_para(WORD phase)
{
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    if (phase >= PH_PMAX)
    {
        return 0;
    }
    // return SET_PARA.setpara[phase-data_tbl_phase_base[DTGR_PARA]];
    return *((int16_t *)(data_tbl_sram_base[DTGR_PARA] + (phase - data_tbl_phase_base[DTGR_PARA])));
}
/* write parameter data. (write to SRAM and EEPROM) */
void set_para(WORD phase, int16_t data)
{
    // int16_t* p;
    // WORD offset;

    // p = data_tbl_sram_base[DTGR_PARA];
    // offset = phase - data_tbl_phase_base[DTGR_PARA];
    // p += offset;
    // *p = data;
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    if (phase >= PH_PMAX)
    {
        return;
    }
    *((int16_t *)(data_tbl_sram_base[DTGR_PARA] + (phase - data_tbl_phase_base[DTGR_PARA]))) = data;
    put_fram2(data_tbl_eep_base[DTGR_PARA] + (phase - data_tbl_phase_base[DTGR_PARA]), data);
}

WORD get_eep_err_rireki(WORD phase)
{
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    return data_tbl_eep_base[DTGR_ERR_RIREKI] + (phase - data_tbl_phase_base[DTGR_ERR_RIREKI]);
}
/* read 異常履歴 data */
int16_t get_err_rireki(WORD phase)
{
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    // return SET_PARA.setpara[phase-data_tbl_phase_base[DTGR_PARA]];
    return *((int16_t *)(data_tbl_sram_base[DTGR_ERR_RIREKI] + (phase - data_tbl_phase_base[DTGR_ERR_RIREKI])));
}
void set_err_rireki(WORD phase, int16_t data)
{
    // #ifdef __DEBUG_MODE__
    // debug_phase_access_check_para(phase);
    // #endif
    *((int16_t *)(data_tbl_sram_base[DTGR_ERR_RIREKI] + (phase - data_tbl_phase_base[DTGR_ERR_RIREKI]))) = data;
    put_fram2(data_tbl_eep_base[DTGR_ERR_RIREKI] + (phase - data_tbl_phase_base[DTGR_ERR_RIREKI]), data);
}

WORD get_eep_other(WORD phase)
{
    // #ifdef __DEBUG_MODE__
    //     debug_phase_access_check_other(phase);
    // #endif
    return data_tbl_eep_base[DTGR_OTHR] + phase - data_tbl_phase_base[DTGR_OTHR];
}
int16_t get_other(WORD phase)
{
    // int16_t* p;
    // WORD offset;

    // #ifdef __DEBUG_MODE__
    //     debug_phase_access_check_other(phase);
    // #endif

    // p = data_tbl_sram_base[DTGR_OTHR];
    // offset = phase - data_tbl_phase_base[DTGR_OTHR];
    // p += offset;
    // return *p;
    return *((int16_t *)data_tbl_sram_base[DTGR_OTHR] + phase - data_tbl_phase_base[DTGR_OTHR]);
}
void set_other(WORD phase, int16_t data)
{
    // int16_t* p;
    // WORD offset;

    // #ifdef __DEBUG_MODE__
    //     debug_phase_access_check_other(phase);
    // #endif

    // p = data_tbl_sram_base[DTGR_OTHR];
    // offset = phase - data_tbl_phase_base[DTGR_OTHR];
    // p += offset;
    // *p = data;
    *((int16_t *)data_tbl_sram_base[DTGR_OTHR] + phase - data_tbl_phase_base[DTGR_OTHR]) = data;
    put_fram2(data_tbl_eep_base[DTGR_OTHR] + phase - data_tbl_phase_base[DTGR_OTHR], data);
}

WORD search_gr(WORD phase)
{
    int16_t cn;

    if (phase > PH_DM_LAST)
    {
        log_data.data_ex.bitms.data_tbl_phase_exception = 1;
        log_data.exception_phase = phase;
    }

    for (cn = DTGR_MAX - 1; cn >= 0; cn--)
    {
        if (phase >= data_tbl_phase_base[cn])
        {
            return cn;
        }
    }
    return DTGR_OTHR;
}

int16_t get_data(WORD phase)
{

    switch (search_gr(phase))
    {
    case DTGR_PARA:
        return get_para(phase);
    case DTGR_ERR_RIREKI:
        return get_err_rireki(phase);
    case DTGR_OTHR:
        return get_other(phase);
    default:
        /* exception */
        log_data.data_ex.bitms.data_tbl_phase_exception = 1;
        log_data.exception_phase = phase;
        return 0;
    }
}

void set_data(WORD phase, int16_t data)
{

    switch (search_gr(phase))
    {
    case DTGR_PARA:
        set_para(phase, data);
        break;
    case DTGR_ERR_RIREKI:
        set_err_rireki(phase, data);
        break;
    case DTGR_OTHR:
        set_other(phase, data);
        break;
    default:
        /* exception */
        log_data.data_ex.bitms.data_tbl_phase_exception = 1;
        log_data.exception_phase = phase;
    }
}

WORD get_eep_addr(WORD phase)
{
    switch (search_gr(phase))
    {
    case DTGR_PARA:
        return get_eep_para(phase);
    case DTGR_ERR_RIREKI:
        return get_eep_err_rireki(phase);
    case DTGR_OTHR:
        return get_eep_other(phase);
    default:
        /* exception */
        log_data.data_ex.bitms.data_tbl_phase_exception = 1;
        log_data.exception_phase = phase;
        return CNTRL3;
    }
}

int16_t *get_table_addr(WORD phase)
{
    int16_t *pt;
    WORD grid;

    grid = search_gr(phase);
    pt = data_tbl_addr_base[grid];
    pt += (phase - data_tbl_phase_base[grid]) * DTID_NUMBERS;
    return pt;
}
int16_t get_min(WORD phase)
{
    int16_t *pt;

    pt = get_table_addr(phase);
    switch (phase)
    {
    case PH_DATA68:
        return SET_PARA.setpara[PH_DATA69] + 10;
    case PH_DATA69:
        return SET_PARA.setpara[PH_DATA70] + 10;
    case PH_DATA6:
    case PH_DATA14:
    {
        if (INPUT_ADC.rtemp[CH1] >= SET_PARA.setpara[PH_DATA68])
        {
            return SET_PARA.setpara[PH_DATA7] + SET_PARA.setpara[PH_DATA24];
        }
        else if (INPUT_ADC.rtemp[CH1] >= SET_PARA.setpara[PH_DATA69])
        {
            return SET_PARA.setpara[PH_DATA61] + SET_PARA.setpara[PH_DATA24];
        }
        else if (INPUT_ADC.rtemp[CH1] >= SET_PARA.setpara[PH_DATA70])
        {
            return SET_PARA.setpara[PH_DATA8] + SET_PARA.setpara[PH_DATA24];
        }
        else
        {
            return SET_PARA.setpara[PH_DATA9] + SET_PARA.setpara[PH_DATA24];
        }
    }
    /* 庫内温度設定値はモードにより異なるため、別処理 */
    default:
        return *(pt + DTID_SET_MIN);
    }
}
int16_t get_max(WORD phase)
{
    int16_t *pt;

    pt = get_table_addr(phase);
    switch (phase)
    {
    case PH_DATA69:
        return SET_PARA.setpara[PH_DATA68] - 10;
    case PH_DATA70:
        return SET_PARA.setpara[PH_DATA69] - 10;
    default:
        return *(pt + DTID_SET_MAX);
    }
}
int16_t get_default(WORD phase)
{
    int16_t *pt;

    pt = get_table_addr(phase);
    return *(pt + DTID_DEFAULT);
}
BOOL is_yoyaku(WORD phase)
{
    int16_t *pt;
    int16_t dt;

    pt = get_table_addr(phase);
    dt = *(pt + DTID_DATA1);

    if (dt & B0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int16_t get_max_day()
{
    int daysInMonth;
    if (SET_TIME.setmonth == 2) {
        if ((SET_TIME.setyear % 4 == 0 && SET_TIME.setyear % 100 != 0)) {
            daysInMonth = 29; 
        } else {
            daysInMonth = 28; 
        }
    } else if (SET_TIME.setmonth == 4 || SET_TIME.setmonth == 6 || SET_TIME.setmonth == 9 || SET_TIME.setmonth == 11) {
        daysInMonth = 30; 
    } else {
        daysInMonth = 31; 
    }
    return daysInMonth;
}
BOOL gaibu1_is_enable(void) { return SET_PARA.setpara[PH_DATA200] ? (1) : (0); }
BOOL gaibu2_is_enable(void) { return SET_PARA.setpara[PH_DATA201] ? (1) : (0); }
BOOL gaibu3_is_enable(void) { return SET_PARA.setpara[PH_DATA202] ? (1) : (0); }
/* Check the valid status of various temperature inputs */
BOOL input_enable(BYTE ch)
{
    switch (ch)
    {
    case CH_MARUCHI1:
        return (gaibu1_is_enable()) ? (1) : (0);
    case CH_MARUCHI2:
        return (gaibu2_is_enable()) ? (1) : (0);
    case CH_MARUCHI3:
        return (gaibu3_is_enable()) ? (1) : (0);
    default:
        return true;
    }
}