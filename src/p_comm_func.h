/*
 * p_comm_func.h
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#ifndef P_COMM_FUNC_H_
#define P_COMM_FUNC_H_
//#include "p_mainh.h"
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void rdcomm(void);
void rd_time(void);
void rdyaku(void);
void rdnone(void);
void rd_prs(void);
void rd_ver(void);
void rd_rom(void);
void rd_opuse(void);
void rd_settype(void);


void rd_pv1(void);
void rd_pv2(void);
void rd_pv3(void);
void rd_pv4(void);
void rd_pv5(void);
void rd_ttemp1(void);
void rd_ttemp2(void);

void wrcomm(void);
void wrnone(void);
void wrnak3(void);
void wrnak4(void);
void wrnak5(void);
void wrnone(void);
void wryaku(void);
void wr_prs(void);

#endif /* P_COMM_FUNC_H_ */
