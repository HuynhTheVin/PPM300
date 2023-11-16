/*
 * p_cont.h
 *
 *  Created on: 2023/06/21
 *      Author: VINH-NT
 */

#ifndef P_CONT_H_
#define P_CONT_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"
#include "p_mainh.h"
#include "PPM300.h"
void make_IO_out(BYTE bzzcnt);
void control1(void);
bool checkRealTime(int hour, int minute);
void josoCYCL(int sv, int pv, BYTE d);
void josotON(int pv,BYTE d);
void turnof_all_output(void);
void set_output(void);
#endif /* P_CONT_H_ */
