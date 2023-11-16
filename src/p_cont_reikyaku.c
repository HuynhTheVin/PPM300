/*
 * p_cont_reikyaku.c
 *
 *  Created on: 2023/07/04
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_cont_reikyaku.h"
/**************
 * 冷却動作
 *************/
void control_reikyaku(void)
{
    int hys1, hys2, hys5;
    int sv, pv;
    WORD ontim, offtim;

    /*ｳｫｰﾑｱｯﾌﾟ中とFRAM ERRERと電源投入後A0041秒間は処理しない */
    if ((TIMDT.iw) || (CNT_STAT.sys_flg.bitms.e_eeprom) || (TIMDT.ta0083) || (KEY_MODE.flg_mode == SELFMD))
    {
        return;
    }
    if ((KEY_MODE.flg_mode >= STANDBYMD) || (CONTROL.cf4_flg.bitms.al_gaibu2CPT))
    {
        CNT_STAT.out_put.bitms.out_SV2 = 0;
        CNT_STAT.out_put.bitms.out_SV3 = 0;
        CNT_STAT.out_put.bitms.out_SV4 = 0;
        TIMDT.errtim3 = 0; /* 冷却不良計測ﾀｲﾏｰｸﾘｱ */
        if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition)
        {
            CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 0; /* 冷却条件不成立 */
            CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off = 1;   /* M1(CPC)出力強制OFF */
            TIMDT.m1offtim = SET_PARA.setpara[PH_DATA38];         /* M1出力OFF遅延ﾀｲﾏｰ 時間ｾｯﾄ A0038*/
            TIMDT.cunton_off[cooling] = 1;                        /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
        }
        return;
    }
    pv = (int)INPUT_ADC.rtempc[CH1];    /* PV */
    sv = cscalsub2(CONTROL.rundata[0]); /* SV */
    hys1 = SET_PARA.setpara[PH_DATA33];
    hys2 = SET_PARA.setpara[PH_DATA34];
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        /*冷却不良チェック*/
        hys5 = cscalsub2(SET_PARA.setpara[PH_DATA34]);
        if ((pv <= (sv + hys5)) || (CNT_STAT.alarm_flg1.bitms.al_konai_over == 1))/* 冷却不良発声しない　+　点検A発生中*/
        {
            TIMDT.errtim3 = 0; /* 冷却不良計測ﾀｲﾏｰｸﾘｱ */
        }
        /* 冷却信号判定データセット*/
        hys1 = cscalsub2(SET_PARA.setpara[PH_DATA33]); /* A0033 */
        hys2 = cscalsub2(SET_PARA.setpara[PH_DATA34]); /* A0034 */

        if(CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)/*　点検A発生しない場合　*/
        {
            /* 冷却条件ﾁｪｯｸ */
            if ((sv + hys2 <= pv) && (CNT_STAT.cfjoso_flg.bitms.joso_unten != 1))
            {                                                         /* 温度条件と除霜運転停止中 */
                CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 1; /* 冷却条件成立(冷却信号ON) */
                TIMDT.m1ontim = 1;                                    /* 冷却運転 冷却信号ON後M1出力がONになるまでの時間ｾｯﾄ*/
            }
            else
            {
                if ((sv - hys1 >= pv) || (CNT_STAT.cfjoso_flg.bitms.joso_unten)||(CNT_STAT.cfkanetu_flg.bitms.H1_start_enable))
                { /* 温度条件と除霜運転中は冷却停止 */
                    if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition)
                    {
                        CNT_STAT.out_put.bitms.out_SV2 = 0;                   /* SV2(GA)　OFF */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;     /* SV2出力状態　OFF */
                        CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 0; /* 冷却条件不成立 */
                        if (CNT_STAT.out_put.bitms.out_CPC)
                        {                                                       /* M1(CPC)出力ONだったら */
                            CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off = 1; /* M1(CPC)出力強制OFF    */
                            TIMDT.m1offtim = SET_PARA.setpara[PH_DATA38];       /* M1出力OFF遅延ﾀｲﾏｰ 時間ｾｯﾄ A0038*/
                        }
                        else
                        {
                            TIMDT.m1waittim = SET_PARA.setpara[PH_DATA84] * 60; /* M1出力がOFF後OFF継続する時間ｾｯﾄ A0084*/
                        }
                    }
                    else
                    {
                        if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op != 1)
                        { /* SV2初期動作未実行済なら */
                            switch (CNT_STAT.cfjoso_flg.bitms.joso_unten)
                            {
                            case 1:
                                if (SET_PARA.setpara[PH_DATA40])
                                {                                                                 /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                                }
                                else
                                {
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* SV2ｻｲｸﾙなし             */
                                }
                                break;
                            default:
                                if (SET_PARA.setpara[PH_DATA39])
                                {                                                                 /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                                }
                                else
                                {
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* SV2ｻｲｸﾙなし             */
                                }
                                break;
                            }

                            // cfstat2 |= B7;           /* SV2ｻｲｸﾙ動作開始         */
                        }
                    }
                }
            }   
        }
        else/*　点検A発生する場合　*/
        {
            ontim = SET_PARA.setpara[PH_DATA2] * 20;
            offtim = SET_PARA.setpara[PH_DATA3] * 20;  
            CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off = 0;
            if (TIMDT.cunton_off[CPC])
            {
                if (--TIMDT.cunton_off[CPC] == 0)
                {
                    if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition)
                    { /* 出力ONだったら */
                        if (offtim)
                        { /* OFF時間が0設定の場合常時ON */
                            TIMDT.cunton_off[CPC] = offtim;
                            CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 0;
                            CNT_STAT.out_put.bitms.out_CPC = 0; /* M1(CPC)　ON  */
                        }
                        else
                        {
                            TIMDT.cunton_off[CPC] = ontim;
                            CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 1;
                            CNT_STAT.out_put.bitms.out_CPC = 1; /* M1(CPC)　ON  */
                        }
                    }
                    else
                    { /* 出力OFFだったら */
                        TIMDT.cunton_off[CPC] = ontim;
                        CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition = 1;
                        CNT_STAT.out_put.bitms.out_CPC = 1; /* M1(CPC)　ON  */
                    }
                }
            }
            if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op != 1)
            { /* SV2初期動作未実行済なら */
                switch (CNT_STAT.cfjoso_flg.bitms.joso_unten)
                {
                case 1:
                    if (SET_PARA.setpara[PH_DATA40])
                    {                                                                 /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                    }
                    else
                    {
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* SV2ｻｲｸﾙなし             */
                    }
                    break;
                default:
                    if (SET_PARA.setpara[PH_DATA39])
                    {                                                                 /* SV2出力インチング動作(除霜終了時) 1:有効/ 0:無効 */
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 1; /* SV2ｻｲｸﾙ動作開始         */
                    }
                    else
                    {
                        CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* SV2ｻｲｸﾙなし             */
                    }
                    break;
                }
            }
        }
        if (CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off)
        {                                  /* M1(CPC)出力強制OFFなら */
            TIMDT.cunton_off[cooling] = 1; /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
            return;
        }
        /* 冷却動作(SV2(GA)出力制御) */
        if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op)
        { /* SV2初期動作実行済みなら */
            if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition)
            {

                CNT_STAT.out_put.bitms.out_SV2 = 1; /* SV2(GA)　ON */
                CNT_STAT.out_put.bitms.out_CPC = 1; /* M1(CPC)　ON  */
            }
            else
            {
                CNT_STAT.out_put.bitms.out_SV2 = 0; /* SV2(GA)　OFF */
            }
        }
        else
        { /* SV2初期動作  */
            if (CNT_STAT.cfreikyaku_flg.bitms.reikyaku_condition)
            {                                                 /* ON-OFF時間をｾｯﾄ */
                ontim = SET_PARA.setpara[PH_DATA35] * 20; /* A0035 */ /* 50ms毎の処理なので20倍する */
                offtim = SET_PARA.setpara[PH_DATA36] * 20;            /* A0036 */

                /* 初期動作実行開始用ﾃﾞｰﾀ要求処理 */
                if (CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg)
                {
                    TIMDT.cunton_off[cooling] = 1;                                /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
                    TIMDT.cuntcycle[cooling] = SET_PARA.setpara[PH_DATA32] + 1;   /* ON-OFF繰り返し回数 A0179 */
                    CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op_request_flg = 0; /* 開始用ﾃﾞｰﾀ要求ﾌﾗｸﾞｸﾘｱ */
                }
                if (TIMDT.cunton_off[cooling])
                {
                    if (--TIMDT.cunton_off[cooling] == 0)
                    {
                        if (TIMDT.cuntcycle[cooling] == 0)
                        {
                            CNT_STAT.cfreikyaku_flg.bitms.SV2_initial_op = 1; /* 初期動作実行済み */
                        }
                        else
                        {
                            if (CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status)
                            { /* 出力ONだったら */
                                if (offtim)
                                { /* OFF時間が0設定の場合常時ON */
                                    TIMDT.cunton_off[cooling] = offtim;
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 0;
                                    CNT_STAT.out_put.bitms.out_SV2 = 0; /* SV2(GA)　OFF */
                                }
                                else
                                {
                                    TIMDT.cunton_off[cooling] = ontim;
                                    CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 1;
                                    CNT_STAT.out_put.bitms.out_SV2 = 1; /* SV2(GA)　ON */
                                    CNT_STAT.out_put.bitms.out_CPC = 1; /* M1(CPC)　ON  */
                                    if (TIMDT.cuntcycle[cooling])
                                    {
                                        if (--TIMDT.cuntcycle[cooling] == 0)
                                        { /* 繰り返しｶｳﾝﾀｰ減算 */
                                            TIMDT.cunton_off[cooling] = 1;
                                        }
                                    }
                                }
                            }
                            else
                            { /* 出力OFFだったら */
                                TIMDT.cunton_off[cooling] = ontim;
                                CNT_STAT.cfreikyaku_flg.bitms.SV2_out_status = 1;
                                CNT_STAT.out_put.bitms.out_SV2 = 1; /* SV2(GA)　ON */
                                CNT_STAT.out_put.bitms.out_CPC = 1; /* M1(CPC)　ON  */
                                if (TIMDT.cuntcycle[cooling])
                                {
                                    if (--TIMDT.cuntcycle[cooling] == 0)
                                    { /* 繰り返しｶｳﾝﾀｰ減算 */
                                        TIMDT.cunton_off[cooling] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                CNT_STAT.out_put.bitms.out_SV2 = 0; /* SV2(GA)　OFF */
            }
        }
    }
}
void control_SV3_4(void)
{
    int pv, sv;
    int sv105, sv106;
    WORD dhontim, dhofftim;
    int hys1;
    WORD ontim, offtim;
    /*ｳｫｰﾑｱｯﾌﾟ中とFRAM ERRERと電源投入後A0041秒間は処理しない */
    if ((TIMDT.iw) || (CNT_STAT.sys_flg.bitms.e_eeprom) || (TIMDT.ta0083) || (KEY_MODE.flg_mode == SELFMD))
    {
        return;
    }
    if (KEY_MODE.flg_mode >= STANDBYMD)
    {
        CNT_STAT.out_put.bitms.out_DHH = 0; /* DHH出力 OFF */
        CNT_STAT.out_put.bitms.out_DH = 0;  /* DH出力 OFF */
        CNT_STAT.out_put.bitms.out_SV3 = 0; /* SV3(緊急水冷)出力　OFF */
        CNT_STAT.out_put.bitms.out_OVN = 0; /* ｵｰﾌﾞﾝ出力 OFF */
        TIMDT.dhtim = 1;                    /* ﾄﾞｱﾋｰﾀON-OFF起動用 */
        return;
    }
    /* DHH ﾄﾞﾚﾝﾎｰｽﾋｰﾀ制御 */
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        if(CNT_STAT.cfjoso_flg.bitms.shudou_joso_start !=1 )/* 手動除霜 */
        {
            CNT_STAT.out_put.bitms.out_DHH = 0; /* DHH出力 OFF */
            if (CNT_STAT.cfjoso_flg.bitms.joso_unten)
            {
                CNT_STAT.out_put.bitms.out_DHH = 1;              /* DHH出力 ON */
                CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition = 1; /* DHH条件OFF遅延タイマー   ON　*/
            }
            else
            {
                switch (SET_PARA.josouhoushiki)
                {
                case 0:/* 除霜ｻｲｸﾙ時間ｶｳﾝﾄｸﾘｱ処理*/
                    if (CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition)
                    {
                        CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition = 0; /* DHH条件OFF遅延タイマー  OFF　*/
                        TIMDT.dhhofftime = SET_PARA.setpara[PH_DATA54];  /*DHH OFF遅延タイマー　A0054　*/
                    }    
                    if(TIMDT.dhhofftime == 0)
                    {
                        if (TIMDT.defrosttim <= SET_PARA.setpara[PH_DATA24])
                        {
                            CNT_STAT.out_put.bitms.out_DHH = 1; /* DHH出力 ON */
                        }
                    }
                    break;
                default:/* 除霜方式 t-ON 処理*/
                    if (CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition)
                    {
                        CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition = 0; /* DHH条件OFF遅延タイマー  OFF　*/
                        TIMDT.dhhofftime = SET_PARA.setpara[PH_DATA54];  /*DHH OFF遅延タイマー　A0054　*/
                    }   
                    break;
                }   
            }
        }
        else
        {
            CNT_STAT.out_put.bitms.out_DHH = 0; /* DHH出力 OFF */
            if (CNT_STAT.cfjoso_flg.bitms.joso_unten)
            {
                CNT_STAT.out_put.bitms.out_DHH = 1;              /* DHH出力 ON */
                CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition = 1; /* DHH条件OFF遅延タイマー   ON　*/
            }
            else
            {
                if (CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition)
                {
                    CNT_STAT.cfjoso_flg.bitms.DHH_OFF_condition = 0; /* DHH条件OFF遅延タイマー  OFF　*/
                    TIMDT.dhhofftime = SET_PARA.setpara[PH_DATA54];  /*DHH OFF遅延タイマー　A0054　*/
                }    
                if(TIMDT.dhhofftime == 0)
                {
                    if (TIMDT.defshudotim <= SET_PARA.setpara[PH_DATA24])
                    {
                        CNT_STAT.out_put.bitms.out_DHH = 1; /* DHH出力 ON */
                    }
                }
            }
        }
    }
    else
    {
        CNT_STAT.out_put.bitms.out_DHH = 0; /* DHH出力 ON */
    }
    /* SV3(緊急水冷)制御 */
    if ((CNT_STAT.out_put.bitms.out_CPC == 1) && (CONTROL.cf4_flg.bitms.al_gaibu2CPT != 1))
    { /* M1(CPC)出力がONなら CPT OFF */
        if (CNT_STAT.cf2_flg.bitms.external_input_RCT_previous_state != 1)
        { /* 前回開状態 */
            if (KEY_MODE.extcomm.bitms.RCT)
            { /* 今回閉状態*/
                if (SET_PARA.setpara[PH_DATA46])
                { /* A0046が0なら判定しない */
                    if (++SET_PARA.rctcunt > SET_PARA.setpara[PH_DATA46])
                    {
                        SET_PARA.rctcunt = SET_PARA.setpara[PH_DATA46]; /* 最大値でﾘﾐｯﾄしておく */
                    }
                    put_fram2(NERCTCUNT, SET_PARA.rctcunt); /* to fram2 save */
                    if (SET_PARA.rctcunt >= SET_PARA.setpara[PH_DATA46])
                    { /* 点検表示｢4｣のﾁｪｯｸ*/
                        if (CNT_STAT.alarm_flg2.bitms.al_gaibu1RCT != 1)
                        {
                            CNT_STAT.alarm_flg2.bitms.al_gaibu1RCT = B1; /* ｴﾗｰﾌﾗｸﾞ点検4ｾｯﾄ */
                            checksave(4);                                /* RCT異常*/
                        }
                    }
                }
            }
        }
        if (KEY_MODE.extcomm.bitms.RCT)
        {
            CNT_STAT.cf2_flg.bitms.external_input_RCT_previous_state = 1; /* 前回用にﾋﾞｯﾄｾｯﾄ　閉状態 */
        }
        else
        {
            CNT_STAT.cf2_flg.bitms.external_input_RCT_previous_state = 0; /* 前回用にﾋﾞｯﾄﾘｾｯﾄ　開状態 */
            TIMDT.cunton_off[sv3ch] = 1;                                  /* ｶｳﾝﾀｰを起動させる為に、常時１をセットしておく */
        }

        if (CNT_STAT.cf2_flg.bitms.external_input_RCT_previous_state)
        {
            ontim = SET_PARA.setpara[PH_DATA96] * 20; /* A0096 */ /* 50ms毎の処理なので4倍する */
            offtim = SET_PARA.setpara[PH_DATA97] * 20;            /* A0097 */
            if (TIMDT.cunton_off[sv3ch])
            {
                if (--TIMDT.cunton_off[sv3ch] == 0)
                {
                    if (CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status)
                    { /* 出力ONだったら */
                        if (offtim)
                        { /* OFF時間が0設定の場合常時ON　20040701 V1.10*/
                            TIMDT.cunton_off[sv3ch] = offtim;
                            CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status = 0;
                            CNT_STAT.out_put.bitms.out_SV3 = 0; /* SV3(緊急水冷)出力　OFF */
                        }
                        else
                        {
                            TIMDT.cunton_off[sv3ch] = ontim;
                            CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status = 1;
                            CNT_STAT.out_put.bitms.out_SV3 = 1; /* SV3(緊急水冷)出力　ON  */
                        }
                    }
                    else
                    { /* 出力OFFだったら */
                        TIMDT.cunton_off[sv3ch] = ontim;
                        CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status = 1;
                        CNT_STAT.out_put.bitms.out_SV3 = 1; /* SV3(緊急水冷)出力　ON  */
                    }
                }
            }
        }
        else
        {
            CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status = 0;
            CNT_STAT.out_put.bitms.out_SV3 = 0; /* SV3(緊急水冷)出力　OFF */
        }
    }
    else
    {
        CNT_STAT.cfreikyaku_flg.bitms.SV3_out_status = 0;
        CNT_STAT.out_put.bitms.out_SV3 = 0; /* SV3(緊急水冷)出力　OFF */
    }
    if ((KEY_MODE.flg_mode == UNTENMD) && (CONTROL.cf4_flg.bitms.al_gaibu2CPT != 1))
    {
        if (CNT_STAT.cfjoso_flg.bitms.joso_unten)
        {                                       /* 除霜中はSV4 OFF */
            CNT_STAT.out_put.bitms.out_SV4 = 0; /* SV4(BY)出力 OFF */
        }
        else
        {
            pv = (int)INPUT_ADC.rtempc[CH1];               /* PV          */
            sv = cscalsub2(SET_PARA.setpara[PH_DATA48]);   /* SV = A0048  */
            hys1 = cscalsub2(SET_PARA.setpara[PH_DATA49]); /* hys = A0190 */

            if (sv >= pv)
            {
                CNT_STAT.out_put.bitms.out_SV4 = 0; /* SV4(BY)出力 OFF */
            }
            else
            {
                if (sv + hys1 <= pv)
                {
                    CNT_STAT.out_put.bitms.out_SV4 = 1; /* SV4(BY)出力 ON */
                }
            }
        }
    }
    else
    {
        CNT_STAT.out_put.bitms.out_SV4 = 0; /* SV4(BY)出力 OFF */
    }
    /* DH ﾄﾞｱﾋｰﾀ制御 */
    if (KEY_MODE.flg_mode == UNTENMD)
    {
        pv = (int)INPUT_ADC.rtempc[CH1];             /* PV             */
        sv = cscalsub2(SET_PARA.setpara[PH_DATA63]); /* SV = A0063     */
        hys1 = cscalsub2(0x05);                      /* hysは0.5℃固定 */
        if (sv >= pv)
        {
            CNT_STAT.out_put.bitms.out_DH = 1; /* DH出力 ON */
        }
        else
        {
            if (sv + hys1 <= pv)
            {
            }
        }
    }
    else
    {
        CNT_STAT.out_put.bitms.out_DH = 0; /* DH出力 OFF */
    }
}
