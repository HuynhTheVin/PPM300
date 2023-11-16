/*
 * p_comm12.h
 *
 *  Created on: 2023/06/22
 *      Author: VINH-NT
 */

#ifndef P_COMM12_H_
#define P_COMM12_H_

//#include "s_mainh.h"
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void start_uart12(void);
void rx12_shinko(uint8_t dt);
void tx12_shinko(void);
void rx12_rtu(uint8_t dt);
void tx12_rtu(void);
void rtu12_35(void);
void uart12_tx_start(void);



#endif /* P_COMM12_H_ */
