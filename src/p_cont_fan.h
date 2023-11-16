/*
 * p_cont_fan.h
 *
 *  Created on: 2023/07/12
 *      Author: VINH-NT
 */

#ifndef P_CONT_FAN_H_
#define P_CONT_FAN_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void control_FAN(void);
void control_FAN_reitou(void);
void control_FAN_reitouzou(void);
void control_FAN12_ONOFF(int ontim, int offtim);
#endif /* P_CONT_FAN_H_ */
