/*
 * p_prototype.h
 *
 *  Created on: 2023/06/12
 *      Author: VINH-NT
 */

#ifndef P_PROTOTYPE_H_
#define P_PROTOTYPE_H_

#include "p_mainh.h"
int cscalsub2(int t);
void nextmodeclr(BYTE mode);
void iniram();
void rdsram();
void set_output();
void scomu();
void rd_rtc();
void wr_rtc(BYTE f,BYTE da);
#endif /* P_PROTOTYPE_H_ */
