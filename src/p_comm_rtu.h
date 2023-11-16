/*
 * p_comm_rtu.h
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#ifndef P_COMM_RTU_H_
#define P_COMM_RTU_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void mksendt_rtu(char *ap ,uint16_t cdt);
uint16_t getdt_rtu(uint8_t n);
void scomu_rtu(void);


#endif /* P_COMM_RTU_H_ */
