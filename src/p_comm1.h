/*
 * p_comm1.h
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#ifndef P_COMM1_H_
#define P_COMM1_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void start_uart1(void);
void rx1_rtu(uint8_t dt);
void tx1_rtu(void);
void rtu1_35(void);
void uart1_tx_start(void);

#endif /* P_COMM1_H_ */
