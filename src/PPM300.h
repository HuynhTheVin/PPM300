/*
 * PPM300.h
 *
 *  Created on: 2023/05/29
 *      Author: VINH-NT
 */

#ifndef PPM300_H_
#define PPM300_H_

#include "p_mainh.h"
// #include "PPM.h"
/* system and adjust data */
struct AJUST_TYPE
{
    uint16_t systemid0; // 開発番号
    uint16_t systemid1; // 開発番号(-上位:xx-下位:xx)
    uint16_t systemid2; // MP番号
    uint16_t systemid3; // MP番号
    uint16_t system0;   // 工場生産製品情報
    uint16_t system1;   // 工場生産製品情報
    uint16_t system2;   // 工場生産製品情報
    uint16_t system3;   // 工場生産製品情報
    uint16_t system4;   // 工場生産製品情報
    uint16_t system5;   // 工場生産製品情報
    uint16_t opuse;     // オプション機能指定
    uint16_t settype;   // 型名指定
                        /* 庫内温度入力 */
    long ptaj1z;        /* 抵抗体式入力ゼロ調整値        */
    long ptaj1s;        /*             スパン調整0値     */
    long offset1;       /*         ０℃入力時のオフセット*/
    long ajref1;        /* 調整 時の ゲインのゼロ入力    */
                        /* 湿度入力 */
    long dcvaj2z;       /* 電圧入力ゼロ調整値 0～1V      */
    long dcvaj2s;       /*             スパン調整値      */
    long dcvof2s;       /*           0V入力時のオフセット*/
    /*陞溷､慚夊ｲゑｽｩ陟趣ｽｦ1,2,3*/
    long tcajz[MMAXCH];  /* 熱電対式入力ゼロ調整値        */
    long tcajs[MMAXCH];  /*             スパン調整値      */
    long ajtz[MMAXCH];   /*         端子温度1ゼロ調整値   */
    long ptajz[MMAXCH];  /* 抵抗体式入力ゼロ調整値        */
    long ptajs[MMAXCH];  /*             スパン調整0値     */
    long offset[MMAXCH]; /*         ０℃入力時のオフセット*/
    long ajref[MMAXCH];  /* 調整 時の ゲインのゼロ入力    */
    uint16_t antajz[2];  /* 伝送出力ゼロ調整              */
    uint16_t antajs[2];  /* 伝送出力スパン調整            */
};
struct SET_DATA_TYPE
{
    /* parameter. A0000 to A0209. @see SET_PHASE. */
    int16_t setpara[PH_DATAMAX];
    WORD pass2; /* dummy to match the order with eeprom */
#define ecode_max 20
#define tstart_max 10
    int16_t nerrcode01[ecode_max];      /*  点検履歴  点検番号             */
    int16_t nerrcode02[ecode_max];      /*  点検履歴  西暦                 */
    int16_t nerrcode03[ecode_max];      /*  点検履歴  月日                */
    int16_t nerrcode04[ecode_max];      /*  点検履歴  時刻 分                 */
    long rycnt[16];                     /* リレーON累積回数               */
    int dummy;                          /* 休日日数                         使用しない*/
                                        /* 0～9                 */
    int16_t kanetu;                     /*  加熱動作有効/無効選択                  */
    int16_t mem1reitou;                 /* メモリ1　冷凍温度設定        */
    int16_t mem1reitouzou;              /* メモリ1　冷凍・冷蔵温度設定   */
    int16_t mem1time;                   /* メモリ1　切替り時刻設定      */
    int16_t josouhoushiki;              /* 除霜方式                    */
    int16_t josoustarttime[tstart_max]; /* 除霜開始時刻 1~10  */

    int16_t setmode;  /*  ﾌﾗｸﾞﾓｰﾄﾞ保存状態               */
    int16_t setrunmd; /*  運転ﾓｰﾄﾞ保存状態(手動)         */
    int16_t setcf4md; /*  cf4保存状態(手動加湿)          */
    int16_t rctcunt;  /* RCT入力ON回数 */
    WORD yobi[9];     /* dummy */
};
struct CON_STATUS_TYPE
{
    union UIN_STATUS
    { /* input status */
        BYTE data;
        struct
        {
            BYTE hold : 4; /* B0toB3 保持 */
            BYTE alm : 4;  /* B4toB7  */
        } nib;
        struct
        {
            BYTE e_h_scale_under : 1; /* B0 アンダスケール(保持) (dummy) */
            BYTE e_h_scale_over : 1;  /* B1 オーバスケール(保持) (dummy) */
            BYTE e_h_under : 1;       /* B2 入力下限異常(保持) */
            BYTE e_h_over : 1;        /* B3 入力上限異常(保持) */
            BYTE e_scale_under : 1;   /* B4 アンダスケール (dummy) */
            BYTE e_scale_over : 1;    /* B5 オーバスケール (dummy) */
            BYTE e_under : 1;         /* B6 入力下限異常 */
            BYTE e_over : 1;          /* B7 入力上限異常 */
        } bitms;
    } halmf[MMAXINPUT]; /* input alarm */
    union UC_STATUS
    { /* 制御フラグ */
        WORD data;
        struct
        {
            WORD untenchu : 1; /* B1 運転制御          0:停止         1:開始       */
        } bitms;
        struct
        {
            WORD rcf1 : 8;
            WORD rcf2 : 8;
        } bytems;

    } con_flg, con_sflg; /* control status rcf1/rcf2 */
    union UE_ALARM1
    { /* 異常フラグ1 */
        WORD data;
        struct
        {
            WORD : 1;                      // 未使用(常時0)
            WORD al_power_outages : 1;     // B1: 停電告知              0:なし1:異常
            WORD al_kanetsu_defective : 1; // B2: 加熱不良              0:なし1:異常
            WORD al_konai_over : 1;        // B3: 庫内温度センサ断線    0:なし1:異常
            WORD al_kanetsufuse_break : 1; // B4: 加熱温度ヒューズ断(HTF1)     0:なし1:異常
            WORD : 8;                      // B5~12 未使用(常時0)
            WORD al_gaibu1_over : 1;       // B13: 外部温度センサ1断線  0:なし1:異常
            WORD al_gaibu2_over : 1;       // B14: 外部温度センサ2断線  0:なし1:異常
            WORD al_gaibu3_over : 1;       // B15: 外部温度センサ3断線  0:なし1:異常
        } bitms;
    } alarm_flg1; /* Alarm evtalmf1 */

    union UE_ALARM2
    { /* 異常フラグ2 */
        WORD data;
        struct
        {
            WORD al_poor_cool : 1;       // 冷却不良              0:なし1:異常
            WORD al_gaibu1RCT : 1;       // B1: 外部異常信号RCT                0:なし1:異常
            WORD al_gaibu2CPT : 1;       // B2: 外部異常信号CPT              0:なし1:異常
            WORD al_reitou_pressure : 1; // B3: 冷凍機低圧異常        0:なし1:異常
            WORD al_reitou_magnet : 1;   // B4: 冷凍機マグネット異常  0:なし1:異常
            WORD al_reversed_phase : 1;  // B5: 逆相検知              0:なし1:異常
            WORD : 9;                    // B6~14 未使用(常時0)
            WORD al_eeprom : 1;          // B15: 不揮発性メモリ異常    0:なし1:異常
        } bitms;
    } alarm_flg2; /* Alarm evtalmf2 */

    union US_STATUS
    { /* system board フラグ */
        WORD data;
        struct
        {
            WORD e_sys : 1;             /* 0 システム異常 */
            WORD e_eeprom : 1;          /* 1 EEPROMデータ異常 */
            WORD e_hardware_eeprom : 1; /* 2 FRAMハード故障 */
            WORD e_set : 1;             /* 3 設定値異常(yobi) */
            WORD : 12;
        } bitms;
    } sys_flg; /* system status */

    union UCF2_STATUS
    { /* Control Flag 2                           */
        BYTE data;
        struct
        {
            BYTE non_volatile_memory_error_flag : 1;          /* B0  不揮発メモリ異常フラグ      0:正常       1:異常      */
            BYTE parameter_setting_mode_set_value_change : 1; /* B1  ﾊﾟﾗﾒｰﾀ設定ﾓｰﾄﾞ設定値変更　　0:項目       1:データ    */
            BYTE current_time_capture_flag : 1;               /* B2  現在時刻取り込みフラグ      0:待機       1:取り込み  */
            BYTE time_setting_flag : 1;                       /* B3  時間設定中フラグ            0:待機       1:設定中    */
            BYTE retention_flag : 1;                          /* B4  保持フラグ　　　　　　　　　0:通常       1:保持      */
            BYTE external_input_RCT_previous_state : 1;       /* B5  外部入力RCT前回の状態       0:開状態     1:閉状態    */
            BYTE data_clear_enable : 1;                       /* B6  データクリア許可            0:不許可     1:許可      */
            BYTE enable_data_clear_after_number_of_sets : 1;  /* B7 : ｾｯﾄ数以降データクリア許可   0:不許可     1:許可      */
        } bitms;
    } cf2_flg; /* Control Flag 2                           */

    union UCF3_STATUS
    {
        BYTE data;
        struct
        {
            BYTE rtc_RX4571_power_drop_error : 1;        /* B0  RTC-RX4571電源低下異常フラグ  0:正常     1:異常        */
            BYTE current_time_not_set : 1;               /* B1  現在時刻未設定              0:正常     1:未設定      */
            BYTE elapsed_time_speed : 2;                 /* B2  経過時間スピード　　　　　　0:通常                   */
                                                         /*                             1:60倍速 2:600倍速   */
            BYTE key_buzzer_flag : 1;                    /* B4  キーブザーフラグ 1：時間セット不許可 0：時間セット許可 */
            BYTE cooling_heating_process : 1;            /* B5  冷却/加熱工程               0:冷却工程     1:加熱工程*/
            BYTE main_task_request_flag : 1;             /* B6  メインタスクリクエストフラグ 0:無し 1:要求有り       */
            BYTE external_input_float_switch_status : 1; /* B7  外部入力フロートスイッチ状態 0:OFF       1:ON        */

        } bitms;
    } cf3_flg; /* RTC_RX4571 Control Flag 3  */

    union UCFKANETU_STATUS
    {
        BYTE data;
        struct
        {
            BYTE heating_active : 1;                /* B0  加熱動作              0:無効 1:有効  */
            BYTE H1_start_enable : 1;               /* B1  H1,H2出力動作開始許可 0:不許可(停止)         1:許可  */
            BYTE heating_operation_weak_strong : 1; /* B2  加熱運転  弱/強       0:弱運転               1:強運転*/
            BYTE H1_out_status : 1;                 /* B3  出力状態              0:OFF                  1:ON    */
            BYTE : 4;                               /* B4~7  Reserve                                              */
        } bitms;
    } cfkanetu_flg; /* 加熱運転ステータスフラグ    */
    union UCF5_STATUS
    {
        BYTE data;
        struct
        {
            BYTE joso_unten : 1;               /* B0  除霜運転    0:待機    1:運転中*/
            BYTE joso_cycle_clear_counter : 1; /* B1  除霜ｻｲｸﾙｸﾘｱｶｳﾝﾀ  0:減算停止    1:減算  */
            BYTE joso_realtime_clear : 1;      /* B1  除霜t-ON  0:停止    1:開始  */
            BYTE : 3;                          /* B2~4  Reserve                                              */
            BYTE shudou_joso_start : 1;        /* B5 手動除霜開始　0:停止　1:開始　*/
            BYTE H1_OFF_condition1 : 1;        /* B6  ヒータOFF条件1ﾞ    0:条件　1待機    1:条件1でOFF  */
            BYTE DHH_OFF_condition : 1;        /* B7  DHH条件OFF遅延タイマー　0:条件ON   1:条件OFF */

        } bitms;
    } cfjoso_flg; /* 除霜運転ステータスフラグ    */

    union UCF6_STATUS
    {
        BYTE data;
        struct
        {
            BYTE reitou_unten_holiday0 : 1; /* B0 冷凍運転中、休日数　0:休日!=0　1:休日数=0*/
        } bitms;
    } cfholiday_flg; /* 休日運転ステータスフラグ    */

    union UCF7_STATUS
    {
        BYTE data;
        struct
        {
            BYTE reikyaku_condition : 1;         /* B0 冷却条件　0:不成立(冷却動作停止）1:成立　*/
            BYTE CPC_out_cont_off : 1;           /* B1 (CPC)出力強制OFF 0:ON可能 1:OFF(継続)　*/
            BYTE SV2_initial_op : 1;             /* B2 SV2初期動作 0:未実行 1:実行済み */
            BYTE SV2_out_status : 1;             /* B3 SV2出力状態 0:OFF 1:ON */
            BYTE SV3_out_status : 1;             /* B4 SV3出力状態 0:OFF 1:ON */
            BYTE SV2_initial_op_request_flg : 1; /* B5 SV2初期動作ﾃﾞｰﾀ要求ﾌﾗｸﾞ  0:未処理 1:要求  */
        } bitms;
    } cfreikyaku_flg; /* 冷却運転ステータスフラグ    */

    union UCF8_STATUS
    {
        BYTE data;
        struct
        {
            BYTE fan1_out_status : 1;         /* B0  FAN1出力              0:OFF                  1:強制ON*/
            BYTE fan2_out_status : 1;         /* B1  FAN2出力状態          0:OFF                  1:ON    */
            BYTE fan1_waittime_off : 1;       /* B2 加熱2信号終了時FAN1遅延時間　0:OFF　　1:ON */
            BYTE fan1_ontime_reikyaku_on : 1; /* A0055遅延時間中、冷却信号ON　0:冷却信号OFF　1:冷却信号ON */
        } bitms;
    } cffan_flg; /* FAN出力ステータスフラグ    */

    union UCF9_STATUS
    {
        BYTE data;
        struct
        {
            BYTE reikyaku_furyou : 1; /* B0  冷却不良状態  0:正常    1:発生         */
            BYTE power_outages : 1;   /* B1　停電告知状態　0:正常　1:停電 */
        } bitms;
    } tenken_flg; /* 点検ステータスフラグ    */

    union UOUT
    {
        long data;
        struct
        {
            BYTE out_DHH : 1;  /* ドレンホースヒータ出力 */
            BYTE out_DH : 1;   /* ドアヒータ出力 */
            BYTE out_FAN1 : 1; /* ファン制御出力1 */
            BYTE out_FAN2 : 1; /* ファン制御出力2 */
            BYTE out_FAN3 : 1; /* ファン制御出力3 */
            BYTE out_TA : 1;   /* 警報出力 */
            BYTE out_SPSV : 1; /* 給水出力 */
            BYTE out_SV2 : 1;  /* 冷媒GA出力 */
            BYTE out_SV3 : 1;  /* 緊急水冷出力 */
            BYTE out_SV4 : 1;  /* 冷媒BY出力 */
            BYTE out_CPC : 1;  /* 冷凍機制御信号出力 */
            BYTE out_ARSV : 1; /* エア抜き出力 */
            BYTE out_HG : 1;   /* 加熱保護リレー制御信号出力  */
            BYTE out_MT1 : 1;  /* ダンバーモーター出力1 */
            BYTE out_MT2 : 1;  /* ダンバーモーター出力2 */
            BYTE out_MT3 : 1;  /* ダンバーモーター出力3 */

            BYTE out_LA : 1;   /* 庫内照明出力 */
            BYTE out_H1 : 1;   /* H1出力 */
            BYTE out_H2 : 1;   /* H2出力 */
            BYTE out_H3 : 1;   /* H3出力  */
            BYTE out_H4 : 1;   /* H4出力  */
            BYTE out_OVN : 1;  /* オーブン指令出力 */
            BYTE out_WG : 1;   /* 加湿保護リレー制御信号出力  */
            BYTE out_JOSO : 1; /* 除霜ヒータ出力 */
            BYTE out_yobi : 1; /* 予備出力  */
            BYTE out_buzz : 1; /*  ﾌﾞｻﾞｰ */
            BYTE in_buzz : 1;  /*  内部ブザー */

        } bitms;
        struct
        {
            long out1 : 16;
            long out2 : 16;
        } bytems;
    } out_put, out_put_previous, com_out;
};

/* ADC INPUT DATA */
struct INPUT_TYPE
{
    BYTE adtcn;    /* ADC 入力取込フェーズカウンタ     */
    BYTE adth1cn;  /* ADC一次平均サンプリングカウンタ */
    BYTE linech;   /* 変換処理CH 0:CH1 1:CH2  2:CH3  3:CH4 4:CH5 */
    BYTE adcphase; /* ADCチャネル選択フェース */
    long adt;      /* 今回の二重積分取込値             */

    long ref_z1;         /* ゼロ基準入力値                   */
    long ref_z2;         /* ゼロ基準入力値                   */
    long ref_s1;         /* スパン基準入力値                 */
    long ref_s2;         /* スパン基準入力値                 */
    long sensin[MAXCH];  /* センサ入力値                     */
    long sensinb[MAXCH]; /* 抵抗体入力オフセット             */
    long termt1;         /* 端子温度入力値1                  */
    long termt2;         /* 端子温度入力値2                  */
    long rtemp[MAXCH];   /* 測定温度内部分解能倍値 表示分解能の1/10又は1/2  ﾟC又はﾟF*/
    int ttemp1;          /* 端子温度1 内部分解能倍値 xx.xx   */
    int ttemp2;          /* 端子温度2 内部分解能倍値 xx.xx   */
    int rtempdp[MAXCH];  /* 表示用に変換した測定温度         */
    long rtempc[MAXCH];  /* 測定温度内部分解能倍値 表示分解能の1/10又は1/2 ﾟC*/

/* 一次移動平均ワーク */
#define HEIKIN1 4
    long sensinH1[MAXCH][HEIKIN1];  /* センサ入力値                     */
    long sensinbH1[MAXCH][HEIKIN1]; /* 抵抗体入力オフセット             */
    long ref_z1H1[HEIKIN1];         /* ゼロ基準入力値                   */
    long ref_z2H1[HEIKIN1];         /* ゼロ基準入力値                   */
    long ref_s1H1[HEIKIN1];         /* スパン基準入力値                 */
    long ref_s2H1[HEIKIN1];         /* スパン基準入力値                 */
    long termt1H1[HEIKIN1];         /* 端子温度入力値1                  */
    long termt2H1[HEIKIN1];         /* 端子温度入力値2                  */

    /* PVフィルタワーク */
    float pvf[MAXCH];   /* PV Filter 演算ワーク */
    float pvfw1[MAXCH]; /* PV Filter 演算ワーク */
    float pvfw2[MAXCH]; /* PV Filter 演算ワーク */

    int tdiv[MAXCH];   /* テーブルデータの分解能           */
    int r_span[MAXCH]; /* 入力レンジの最大値               */
    int r_min[MAXCH];  /* 入力レンジの最小値               */
    int r_scal[MAXCH]; /* 入力レンジの有効巾(r_span-r_min) */
    int minbit[MAXCH]; /* 表示分解能                       */

    int wksens[MMAXCH]; /* マルチ入力レンジ選択             */
    WORD pwmo[2];       /* PWM出力                          */

    //* 過去5回の取込値､平均処理用
    long adtheikin1[20]; /* ADC1取込値サンプリング内平均用   */

    BOOL adc_error;          /* ADC error flag */
    BOOL adc_latch_error;    /* ADC error flag(latch) */
    BOOL adc_set_sumi;       /* ADC Initialized flag */
    int16_t adc_ref_er_cnt;  /* ADC Conver value error decision time */
    int16_t adc_samp_er_cnt; /* ADC Conver time error decision time */
    int16_t adc_reset_dly;   /* ADC init delay */
    int16_t adc_sample_tim;  /* ADC Conver time(ms) */
    union
    {
        WORD data;
        struct
        {
            WORD konai_in_cal_request : 1;     /* B0: 庫内温度入力演算要求         0:無し     1:有り    */
            WORD shitsudo_in_cal_request : 1;  /* B1: 湿度入力演算要求             0:無し     1:有り    */
            WORD manuchi1_in_cal_request : 1;  /* B2: マルチ入力1演算要求          0:無し     1:有り    */
            WORD manuchi2_in_cal_request : 1;  /* B3: マルチ入力2演算要求          0:無し     1:有り    */
            WORD manuchi3_in_cal_request : 1;  /* B4: マルチ入力3演算要求          0:無し     1:有り    */
            WORD konai_INB_tanshi_ondo : 1;    /* B5: 庫内入力のINB/端子温度       0:INB      1:予約    */
            WORD kijunZero_Span : 1;           /* B6: 基準ゼロ/スパン              0:ゼロ     1:スパン  */
            WORD manuchi1_INB_tanshi_ondo : 1; /* B7: マルチ入力1のINB/端子温度    0:INB      1:端子    */
            WORD manuchi2_INB_tanshi_ondo : 1; /* B8: マルチ入力2のINB/端子温度    0:INB      1:端子    */
            WORD manuchi3_INB_tanshi_ondo : 1; /* B9: マルチ入力3のINB/端子温度    0:INB      1:端子    */
            WORD : 6;
        } bitms;
    } cfadc1;

    union
    {
        BYTE data;
        struct
        {
            BYTE ADC_henkan : 1;      /* B0: ADC変換済み                  0:無し     1:有り    */
            BYTE : 5;                 /* B1~5: Reserve                      0:無し     1:有り    */
            BYTE ADC_125ms : 1;       /*B6: 125msADC                     0:無し     1:有り    */
            BYTE ADC_initialized : 1; /* B7: ADC初期化済み                0:無し     1:有り    */
        } bitms;
    } cfadc2;

    union
    { /* This is an interrupt-only flag. Only set by interrupt */
        BYTE data;
        struct
        {
            BYTE convert_sumi : 1; /* Converted */
        } bitms;
    } i_flg1;

    union
    { /* This is the flag to be processed by the main. Do not set by interrupt */
        BYTE data;
        struct
        {
            BYTE dumy : 1;
        } bitms;
    } m_flg1;

    union
    { /* This is the flag to be processed by the main. Do not set by interrupt */
        BYTE data;
        struct
        {
            /* 温度換算は2回のカウント値で平均する。 */
            BYTE temp_conver : 1; /* B0 温度換算 0: カウント値保存、1：温度換算 */
        } bitms;
    } m_flg_ch[MAXCH];
};

struct SET_RTCTIME
{
    int setyear;  /* 1 年                           */
    int setmonth; /* 2 月                           */
    int setday;   /* 3 日                           */
    int setweek;  /* 4 曜日                         */
    int sethour;  /* 5 時                           */
    int setmin;   /* 6 分                           */
    int setsec;   /* 7 秒                           */
    int nowtim;   /* 現在時間(早出遅出含む)         */
};
/* 現在値　*/
struct RUN_DATA_TYPE
{
    union UUNTEN_MODE ckrun_md; /* 運転モード */
    int16_t ckrun_sv1;          /* 庫内温度設定 */
    int16_t ckrun_memory;       /* 現在のメモリ番号 */
    int16_t ckrun_sv2;          /* 庫内湿度設定値 */
};
struct KEY_TYPE
{
    /* @see RUNMD enum for more information */
    BYTE flg_rmode; /* 運転モード */
    BYTE flg_mode;  /* 状態モードフラグ (システム)           */

    char flg_smode1; /* sub mode flag1 */
    BYTE flg_smode2; /* sub mode flag2 */

    int16_t udbuff; /* 数値入力バッファ */
    int16_t uplimt; /* 数値入力上限リミット値 */
    int16_t dwlimt; /* 数値入力下限リミット値 */

    union UEVTI extcat1; /* 外部操作信号チャタリング */
    union UEVTI extcat2; /* 外部操作信号チャタリング */
    union UEVTI extcomm; /* 外部操作信号 */
                         //    union UEVTI oextcomm;   /* 外部操作信号(前回判定時) */
                         //
    union UDSWI swcat1;  /* SW信号チャタリング */
    union UDSWI swcat2;  /* SW外部操作信号チャタリング */
    union UDSWI swcomm;  /* SW外部操作信号 */

    BYTE krditv; /* digital external input  capture timer. */

    int16_t udtmp;       /* ジョグ用数値入力バッファ */
    int16_t udtim;       /* ジョグ用数値入力バッファ */
    int16_t udsin;       /* ジョグ用数値入力バッファ */
    int16_t encoder_cnt; /* ロータリエンコーダカウンタ */

    union UKEY_CHANGE
    { /* キー変更フラグ */
        WORD data[1];
        struct
        {
            WORD eng : 1;  /* エンジニアリング */
            WORD dirt : 1; /* ダイレクト */
            WORD prog : 1; /* プログラム */
        } bitms;
    } kchange[3]; /* UART 三つ */
    BYTE taskcn;  /* 2msタスクリクエストカウンタ    */
    BYTE taskcn1; /* 10msタスクリクエストカウンタ   */
    BYTE taskcn2; /* 50msタスクリクエストカウンタ   */
};

struct TIME_TYPE
{
#define INTCLK1M 60
#define INTTIM 1000  /* 1秒間の割込み回数                        */
#define INT1000 1000 /* 1秒間の割込み回数                        */
#define INTTIM2 1    /* 桁ドライブ更新間隔                       */
    BYTE iw;
    char iw5;        /* 桁Drive間隔タイマ 1/5000sec毎            */
    BYTE iw2s;       /* Key in 2sec Wait Time        */
    BYTE iw3s;       /* Key in 3sec Wait Time        */
    BYTE iws;        /* Key in 3sec Wait Time        */
    BYTE tk10f;      /* Key ｶｳﾝﾄ ｽﾋﾟｰﾄﾞ 10step       */
    TINY krditv;     /* Key Read Interval timer      */
    BYTE tk500m;     /* Key in 500msec ﾀﾞｳﾝ ｶｳﾝﾀ     */
    int16_t t10m;    /* 10msec ｶｳﾝﾀ                  */
    int16_t t025s;   /* 250msec ｶｳﾝﾀ                 */
    int16_t t125m;   /* ADC 125msec ﾌｪｰｽﾞ ｶｳﾝﾀ       */
    int16_t iw1000m; /* interval timer 1000msec      */
    TINY t60s;       /* 調理１分管理タイマ           */
    TINY t60f;       /* FRAM保存１分管理タイマ       */
    BYTE keybztm;    /* ｷｰﾌﾞｻﾞｰﾀｲﾏ 100ms         */
    WORD enc1000m;   /* エンコーダ1000ms ｶｳﾝﾀ       */
    uint32_t ticks;  /* 通電時間 */
    BOOL m250ms;     /* メイン処理250msタイマ */
    BYTE tim4cntm;   /* 時間進行ｶｳﾝﾀ       */
    BYTE taskcn;     /*  2msタスクリクエストカウンタ    */
    BYTE taskcn1;    /* 10msタスクリクエストカウンタ   */
    BYTE taskcn2;    /* 50msタスクリクエストカウンタ   */
    BYTE tasktm;     /* タスクリクエストタイマ 5msec   */

    WORD powertim;      /*電源投入時、制御開始までウェイト時間*/
    WORD ta0083;        /*運転開始時、制御開始するまでのウエイト時間*/
    WORD cunton_off[6]; /*[0] H1(加熱）ヒータ出力切替えタイマー　*/
                        /*[1] CPC(冷却）SV2冷却出力切替えタイマー　*/
                        /*[2] CPC出力切替えタイマー　*/
                        /*[3] SV3出力切替えタイマー　*/
                        /*[4] FAN1出力切替えタイマー　*/
                        /*[5] FAN2出力切替えタイマー　*/
    WORD cuntcycle[6];  /*[0] H1(加熱）ヒータ出力切替えタイマー　*/
                        /*[1] CPC(冷却）SV2冷却出力切替えタイマー　*/
                        /*[2] CPC出力切替えタイマー　*/
                        /*[3] SV3出力切替えタイマー　*/
                        /*[4] FAN1出力切替えタイマー　*/
                        /*[5] FAN2出力切替えタイマー　*/
    WORD m1offtim;      /* M1(CPC)出力OFF遅延ﾀｲﾏｰ systm1sec()でﾀｲﾑｱｯﾌﾟ処理  A0038sec */
    WORD m1ontim;       /* M1(CPC)出力ON待機ﾀｲﾏｰ  systm1sec()でﾀｲﾑｱｯﾌﾟ処理  A0053sec */
    WORD m1waittim;     /* M1(CPC)出力ON待機ﾀｲﾏｰ  systm1sec()でﾀｲﾑｱｯﾌﾟ処理  A0084sec */
    WORD errtim3;       /* 冷却不良　systm1sec()でﾀｲﾑｱｯﾌﾟ処理 */
    WORD heaterwaittim; /* 加熱ヒータ出力H1は0.5秒間待ってからONする　*/
    WORD dhtim;         /* ドアヒータON-OFFタイマー */
    WORD cpt3stim;      /* CPT異常入力3秒遅延ﾀｲﾏｰ  */
    WORD dhhofftime;    /* DHH出力OFF遅延タイマー　systm1sec()でタイムアップ処理　A0054sec */
    WORD dhhontime;     /* (手動除霜のみ)DHH出力ON待機タイマー　systm1sec()でタイムアップ処理　A0024sec */

    WORD defrosttim;  /* 除霜ﾀｲﾏｰ　(サイクル)  systm1min()でﾀｲﾑｱｯﾌﾟ処理 */
    WORD deftONtim;   /* 除霜ﾀｲﾏｰ　(t-ON)  systm1min()でﾀｲﾑｱｯﾌﾟ処理 */
    WORD defrclrtim;  /* 除霜ｻｲｸﾙ時間ｸﾘｱﾀｲﾏｰ  systm1sec()でﾀｲﾑｱｯﾌﾟ処理 */
    WORD defshudotim; /* 除霜サイクル時間タイマー（除霜解除、1サイクルのみ）systm1min()でﾀｲﾑｱｯﾌﾟ処理*/

    WORD fan1wait1st; /* FAN1とFAN2の切り替え時、１秒間タイムラグを取る systm250msec()でﾀｲﾑｱｯﾌﾟ処理*/
    WORD fan2wait1st; /* FAN1とFAN2の切り替え時、１秒間タイムラグを取る systm250msec()でﾀｲﾑｱｯﾌﾟ処理*/
    WORD fan1ontim;   /* 加熱2終了のFAN1の遅延時間　systm1sec()でﾀｲﾑｱｯﾌﾟ処理 */
    BYTE bztm;        /* キー操作ブザー音タイマー */
    BYTE bzcnt;       /* キー操作ブザー回数カウンタ */
};

struct CONTROL_TYPE
{
#define mode_max 2 /* 庫内温度設定値, 庫内湿度設定値 */
    BYTE control;
    BYTE cont_kanetu;      /* 加熱動作有効/無効
         /* 運転関係 */
    int rundata[mode_max]; /* 運転中の項目　*/
    int holiday_num;       /*　休日数残り　*/
    /* 除霜ワーク */
    int defrostpv; /* 除霜開始時の庫内温度*/
    BYTE self_md;　/*自己診断状態　0:OFF　1:ON */
    union UCF4_STATUS
    { /* Control Flag 2                           */
        BYTE data;
        struct
        {
            BYTE al_gaibu2CPT : 1; /* B0  外部異常信号CPT　　　　　　 0:正常     1:異常        */
        } bitms;
    } cf4_flg; /* Control Flag 4                           */
    union UCF10_STATUS
    {
        BYTE data;
        struct
        {
            BYTE down_scal_err : 1; /* B0  センサ断線  0:正常    1:発生         */
            BYTE up_scal_err : 1;   /* B1　センサ断線　0:正常　1:停電 */
        } bitms;
    } input_over_flg[5]; /* 点検ステータスフラグ    */
};

union U_BIT16
{
    uint16_t data;
    struct
    {
        BYTE B0 : 1;
        BYTE B1 : 1;
        BYTE B2 : 1;
        BYTE B3 : 1;
        BYTE B4 : 1;
        BYTE B5 : 1;
        BYTE B6 : 1;
        BYTE B7 : 1;
        BYTE B8 : 1;
        BYTE B9 : 1;
        BYTE B10 : 1;
        BYTE B11 : 1;
        BYTE B12 : 1;
        BYTE B13 : 1;
        BYTE B14 : 1;
        BYTE B15 : 1;
    } bitms;
};
#endif /* PPM300_H_ */
