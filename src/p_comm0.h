/*
 * p_comm0.h
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#ifndef P_COMM0_H_
#define P_COMM0_H_

#include "p_type_define.h"
#include "r_cg_macrodriver.h"
#include "p_mainh.h"
void start_uart0(void);
void rx0_shinko(uint8_t dt);
void tx0_shinko(void);
void rx0_rtu(uint8_t dt);
void tx0_rtu(void);
void rtu0_35(void);
void uart0_tx_start(void);

#endif /* P_COMM0_H_ */
