/*
 * p_self.h
 *
 *  Created on: 2023/07/20
 *      Author: VINH-NT
 */

#ifndef P_SELF_H_
#define P_SELF_H_
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

#define SELF_OUT_NUMBER 29

void set_self_out(void);
void auto_self_output(void);
void self_250ms(void);
void set_self_out_auto(void);
void set_self_out_set(void);
void selfchk(void);
struct SELF_TYPE{
    uint16_t self_mode1;
    uint16_t self_mode2;
    uint16_t self_mode3;
    uint16_t self_cnt;
};
enum ESELFMD{
    SELFMD1_SET_OUT,  /* 出力を番号で指定 */
    SELFMD1_SET_BOUT, /* 出力をBit単位で指定 */
    SELFMD1_AUTO_OUT  /* 出力自動順次にON */
};
#endif /* P_SELF_H_ */
