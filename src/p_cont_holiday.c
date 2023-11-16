/*
 * p_cont_holiday.c
 *
 *  Created on: 2023/07/04
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.H"
#include "p_cont_holiday.h"


/**************
 * 休日運転制御
 **************/
void control_holiday(void)
{
    switch (KEY_MODE.flg_mode)
    {
    case UNTENMD:
        unten_holiday(); /* 休日運転動作 */
        break;
    default:
        break;
    }
}
void unten_holiday(void)
{
    int min_realtime;
    min_realtime = convert_min(SET_TIME.sethour, SET_TIME.setmin);/* 分単位に時刻変換　*/
    if(CONTROL.holiday_num != 0)
    {
        KEY_MODE.flg_rmode = REITOMD; /* 冷凍運転モード　*/
              
        if(SET_PARA.mem1time == min_realtime)
        {
            if(--CONTROL.holiday_num == 0)
            {
                CNT_STAT.cfholiday_flg.bitms.reitou_unten_holiday0 = 1;
            }
        }
    }
    else
    {
        switch (CNT_STAT.cfholiday_flg.bitms.reitou_unten_holiday0)
        {
        case 1:
            KEY_MODE.flg_rmode = REITOMD; /* 冷凍運転モード　*/  
            if(SET_PARA.mem1time == min_realtime)
            {
                CNT_STAT.cfholiday_flg.bitms.reitou_unten_holiday0 = 0;
                KEY_MODE.flg_rmode = REITOZOUMD;
                start_reitouzou_unten();/* 冷凍冷蔵運転初期動作 */
            }    
            break;      
        default:
            KEY_MODE.flg_rmode = REITOZOUMD;
            CNT_STAT.cfholiday_flg.bitms.reitou_unten_holiday0 = 0;
            break;
        }      
    }
}
int convert_min(int hour, int minute)
{
    return hour*60 + minute;
}
