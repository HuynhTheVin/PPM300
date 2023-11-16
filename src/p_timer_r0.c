/*
 * p_timer_r0.c
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.h"
#include "p_timer_r0.h"

void start_timer_r0(void){
	R_Config_TMR0_Start();
}
