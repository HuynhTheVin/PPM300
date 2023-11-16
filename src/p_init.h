/*
 * p_init.h
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#ifndef P_INIT_H_
#define P_INIT_H_

#include "p_mainh.h"
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

#define HUM_DT_MAX 30

void clrprog_para(BOOL rdram);
void clrprog_pro(BOOL rdram);
void clrprog_all(void);
void clrprog(void);
void adjsave(void);
void sysClear(void);
void data_clr(BYTE clrmd);
void clerachk(void);
void clr_p01(void);
void clr_pd6(void);
void freeFramClr(void);
enum CLR_MODE{
    CLR_ALL,    /* All*/
    CLR_PRO,   /*Program*/
    CLR_PARA,    /* エンジニアリング */
    CLR_RIREKI,   /* 履歴 */
    CLR_NONE,   /* dummy */
};
enum CLR_OPTION{
    CLR_NOT_READ_FRAM, /* クリア後SRAM更新しない */
    CLR_READ_FRAM  /* クリア後SRAM更新する */
};


#endif /* P_INIT_H_ */
