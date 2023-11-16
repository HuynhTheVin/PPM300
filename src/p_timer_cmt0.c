/*
 * p_timer_cmt0.c
 *
 *  Created on: 2023/06/12
 *      Author: VINH-NT
 */
#define EXTERN extern
#include "PPM.h"
#include "p_timer_cmt0.h"

void start_timer_cmt0(void)
{
	R_Config_CMT0_Start();
}
/**
 * @brief 1分タイマ処理
 *
 */
void systm1min(void)
{
	/* 除霜ﾀｲﾏｰ減算 */
	if (TIMDT.defrosttim)
	{
		--TIMDT.defrosttim;
	}
	/* 除霜ﾀｲﾏｰ減算 */
	if (TIMDT.deftONtim)
	{
		--TIMDT.deftONtim;
	}

	/* 手動除霜開始時、DHH ONタイマー 減算*/
	if (TIMDT.dhhontime)
	{
		if (--TIMDT.dhhontime == 0)
		{
			CNT_STAT.cfjoso_flg.bitms.joso_unten = 1;
		}
	}
	/* 手動除霜解除時(CYCL)、A0014　1サイクル時間減算 */
	if (TIMDT.defshudotim)
	{
		if (--TIMDT.defshudotim == 0)
		{
			CNT_STAT.cfjoso_flg.bitms.shudou_joso_start = 0;	 /* 手動除霜停止　OFF */
			TIMDT.defrosttim = SET_PARA.setpara[PH_DATA6];		 /* A0006        */
			TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60; /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
			TIMDT.t60s = INTCLK1M;								 /* 1分ﾀｲﾏｰ初期化 */
		}
	}
	if (--TIMDT.t10m == 0)
	{
		TIMDT.t10m = 10; /* 10分　*/
						 /*　10分　処理code　*/
	}
}
/**
 * @brief 1秒タイマ処理
 *
 */
void systm1sec(void)
{
	if (TIMDT.t60s)
	{
		if (--TIMDT.t60s == 0)
		{
			TIMDT.t60s = INTCLK1M;
			systm1min();
		}
	}
	/* 除霜ｻｲｸﾙﾀｲﾏｰ減算 */
	if (CNT_STAT.cfjoso_flg.bitms.joso_cycle_clear_counter)
	{
		if (TIMDT.defrclrtim)
		{
			if (--TIMDT.defrclrtim == 0)
			{

				TIMDT.defrosttim = SET_PARA.setpara[PH_DATA6];		 /* A0006        */
				TIMDT.defrclrtim = SET_PARA.setpara[PH_DATA11] * 60; /* A0011 除霜ｻｲｸﾙ時間ﾀｲﾏｰｸﾘｱ*/
				TIMDT.t60s = INTCLK1M;								 /* 1分ﾀｲﾏｰ初期化 */
				CNT_STAT.out_put.bitms.out_DHH = 0;					 /* DHH出力 OFF   */
			}
		}
	}
	/* 冷却運転 M1出力OFF後M1がONにならない時間ﾀｲﾏｰ */
	if (TIMDT.m1waittim)
	{
		if (--TIMDT.m1waittim == 0)
		{
			CNT_STAT.cfreikyaku_flg.bitms.CPC_out_cont_off = 0; /* M1(CPC)出力強制OFF 解除*/
		}
	}
	/* 冷却運転 冷却信号ON後M1出力がONになるまでの時間ﾀｲﾏｰ */
	if (TIMDT.m1ontim)
	{
		--TIMDT.m1ontim;
	}
	/* M1(CPC)出力OFF遅延ﾀｲﾏｰ処理 冷却動作 */
	if (TIMDT.m1offtim)
	{
		if (--TIMDT.m1offtim == 0)
		{
			CNT_STAT.out_put.bitms.out_CPC = 0;					/* CPC(M1)出力 OFF*/
			TIMDT.m1waittim = SET_PARA.setpara[PH_DATA84] * 60; /* 冷却用制御信号M1出力(CPC)がOFF後、ONしない時間設定 */
		}
	}
	else
	{
		if (KEY_MODE.flg_mode == STANDBYMD)
		{										/* CPCがスタンバイ時にONのままになる情報より、強制OFFを入れる*/
			CNT_STAT.out_put.bitms.out_CPC = 1; /* CPC(M1)出力 OFF*/
		}
	}
	if (TIMDT.dhhofftime)
	{
		if (--TIMDT.dhhofftime == 0)
		{
			CNT_STAT.out_put.bitms.out_DHH = 0; /* DHH出力　OFF */
		}
	}
	if (TIMDT.fan1ontim)
	{
		if (--TIMDT.fan1ontim == 0)
		{
		}
	}
	/* 冷却不良チェック */
	if(CNT_STAT.alarm_flg1.bitms.al_konai_over != 1)
	{
		if (SET_PARA.setpara[PH_DATA12] != 0)/* 冷却不良監視の有効／無効選択（A0012）の有効の場合 */
		{
			if (++TIMDT.errtim3 >= SET_PARA.setpara[PH_DATA67] * 60)
			{
				CNT_STAT.tenken_flg.bitms.reikyaku_furyou = 1;	/* 冷却不良発生 */
				TIMDT.errtim3 = SET_PARA.setpara[PH_DATA67] * 60; /* ﾀｲﾏｰ加算max */
			}
			else
			{
				CNT_STAT.tenken_flg.bitms.reikyaku_furyou = 0; /* 冷却正常 */
			}
		}
	}
}
/**
 * @brief 250ミリ秒タイマ処理
 *
 */
void systm250msec(void)
{
	/* 250処理 */
	TIMDT.ticks++;

	if (TIMDT.iw)
	{
		if (--TIMDT.iw == 0)
		{
			switch (get_fram2(NEMODE))
			{
			case UNTENMD:					 /* 運転モード */
				KEY_MODE.flg_mode = UNTENMD; /*　再電源後、現在モード　*/
				switch (get_fram2(NECF4MD))
				{
				case REITOMD:
				case REITOZOUMD:
					/* code */
					KEY_MODE.flg_rmode = get_fram2(NECF4MD);		 /*　再電源後、現在運転モード　*/
					TIMDT.ta0083 = get_data(PH_DATA83) * 1000 / 250; /* A0083 */
					break;
				default:
					break;
				}
				break;
			default:
				KEY_MODE.flg_mode = STANDBYMD; /*　再電源後、現在モード　*/
				break;
			}
		}
		fact_out_off(); /* 出力OFF　*/
		make_IO_out(0);
	}

	if (TIMDT.iw3s)
	{
		TIMDT.iw3s--;
	}

	if (TIMDT.iws)
	{
		TIMDT.iws--;
	}
	/* 電源投入時、制御開始するまでのウェイト時間 */
	if (TIMDT.ta0083)
	{
		if (--TIMDT.ta0083 == 0)
		{
			ie_KEYSTART();
		}
		fact_out_off(); /* 出力状態OFF　*/
		make_IO_out(0); /* 出力OFF */
	}
	/* FAN1とFAN2の切り替え時、１秒間タイムラグを取る */
	if (TIMDT.fan1wait1st)
	{
		if (--TIMDT.fan1wait1st == 0)
		{
			CNT_STAT.out_put.bitms.out_FAN1 = 1;
		}
	}
	if (TIMDT.fan2wait1st)
	{
		if (--TIMDT.fan2wait1st == 0)
		{
			CNT_STAT.out_put.bitms.out_FAN2 = 1;
		}
	}
}
