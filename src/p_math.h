/*
 * p_math.h
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#ifndef P_MATH_H_
#define P_MATH_H_

#include "p_mainh.h"
#include "stdint.h"

int16_t min_i16(int16_t x,int16_t y);
long mini_i32(long x,long y);
float min_f(float x,float y);
double min_d(double x,double y);

int16_t max_i16(int16_t x,int16_t y);;
long maxi_i32(long x,long y);
float max_f(float x,float y);
double max_d(double x,double y);

long ulabs(long x);
int16_t uiabs(int16_t x);

BOOL limit_check(int16_t min_value, int16_t max_value, int16_t value);
BOOL limit_wcheck(WORD min_value, WORD max_value, WORD value);
BOOL limit_lcheck(long min_value, long max_value, long value);
int16_t make_limit(int16_t v1, int16_t v2, int16_t value);
int16_t convert_long2int16(long value);
long convert_double2long(double value);
int16_t convert_double2int16(double value);
int16_t rdown_double2int16(double value);

#ifdef __DEBUG__
    BOOL test_rdown_f2i16(void);
#endif


#endif /* P_MATH_H_ */
