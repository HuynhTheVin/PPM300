/*
 * Datatbl.h
 *
 *  Created on: 2023/06/23
 *      Author: VINH-NT
 */

#ifndef DATATBL_H_
#define DATATBL_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

WORD get_eep_para(WORD phase);
int16_t get_para(WORD phase);
void set_para(WORD phase, int16_t data);

WORD get_eep_err_rireki(WORD phase);
int16_t get_err_rireki(WORD phase);
void set_err_rireki(WORD phase, int16_t data);

WORD get_eep_other(WORD phase);
int16_t get_other(WORD phase);
void set_other(WORD phase, int16_t data);

int16_t get_data(WORD phase);
void set_data(WORD phase, int16_t data);

WORD get_eep_addr(WORD phase);

int16_t get_min(WORD ph);
int16_t get_max(WORD ph);
int16_t get_default(WORD ph);
BOOL is_yoyaku(WORD phase);
int16_t get_max_day();

BOOL input_enable(BYTE ch);
BOOL gaibu1_is_enable(void);
BOOL gaibu2_is_enable(void);
BOOL gaibu3_is_enable(void);

extern const int16_t DATA_TBL_PARA[];
extern const int16_t DATA_TBL_OTHER[];
extern int16_t* data_tbl_addr_base[];
extern WORD data_tbl_phase_base[];
extern WORD data_tbl_eep_base[];
enum DT_INDEX{  /* データベーステーブルの各種データ順ID */
    DTID_SET_MIN,   /* min */
    DTID_SET_MAX,   /* max */
    DTID_DEFAULT,   /* default */
    DTID_DP,        /* dp */
    DTID_DATA1,     /* data1 */
    DTID_NUMBERS
};
/* データベースグルーブ番号 */
enum DT_GROUP{
    DTGR_PARA,
    DTGR_ERR_RIREKI,
    DTGR_OTHR,
    DTGR_MAX
};

#endif /* DATATBL_H_ */
