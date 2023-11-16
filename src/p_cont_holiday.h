/*
 * p_cont_holiday.h
 *
 *  Created on: 2023/07/04
 *      Author: VINH-NT
 */

#ifndef P_CONT_HOLIDAY_H_
#define P_CONT_HOLIDAY_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void control_holiday(void);
void unten_holiday(void);
int convert_min(int hour, int minute);
#endif /* P_CONT_HOLIDAY_H_ */
