/*
 * p_math.c
 *
 *  Created on: 2023/06/26
 *      Author: VINH-NT
 */

#define EXTERN extern
#include "PPM.h"
#include "p_math.h"


/* Find the minimum */
int16_t min_i16(int16_t x,int16_t y){
    return (x >= y) ? (y) : (x); 
}
/* Find the minimum */
long mini_i32(long x,long y){
    return (x >= y) ? (y) : (x); 
}
/* Find the minimum */
float min_f(float x,float y){
    return (x >= y) ? (y) : (x); 
}
/* Find the minimum */
double min_d(double x,double y){
    return (x >= y) ? (y) : (x); 
}
/* Find the maximum */
int16_t max_i16(int16_t x,int16_t y){
    return (x >= y) ? (x) : (y); 
}
/* Find the maximum */
long maxi_i32(long x,long y){
    return (x >= y) ? (x) : (y); 
}
/* Find the maximum */
float max_f(float x,float y){
    return (x >= y) ? (x) : (y); 
}
/* Find the maximum */
double max_d(double x,double y){
    return (x >= y) ? (x) : (y); 
}
/* absolute value */
long ulabs(long x){
    if (x<0){return -x;}
    return x;
}
/* absolute value */
int16_t uiabs(int16_t x){
    if (x<0){return -x;}
    return x;
}
/* Check if within range */
BOOL limit_check(int16_t min_value, int16_t max_value, int16_t value){
    if(min_value>max_value){return 0;}
    if(value<min_value){return 0;}
    if(value>max_value){return 0;}
    return 1;
}
/* Check if within range */
BOOL limit_wcheck(WORD min_value, WORD max_value, WORD value){
    if(min_value>max_value){return 0;}
    if(value<min_value){return 0;}
    if(value>max_value){return 0;}
    return 1;
}
/* Check if within range */
BOOL limit_lcheck(long min_value, long max_value, long value){
    if(min_value>max_value){return 0;}
    if(value<min_value){return 0;}
    if(value>max_value){return 0;}
    return 1;
}
/* Check if within range and limit it */
int16_t make_limit(int16_t v1, int16_t v2, int16_t value){
    int16_t min_value,max_value;
    
    if(v1<v2){
        min_value = v1;max_value=v2;
    }else{
        min_value = v2;max_value=v1;
    }
    if(value<min_value){return min_value;}
    if(value>max_value){return max_value;}
    return value;
}
int16_t convert_long2int16(long value){/* long --> int16 */
    if(value>INT16_MAX){return INT16_MAX;}
    if(value<INT16_MIN){return INT16_MIN;}
    return value;
}
long convert_double2long(double value){/* double --> long Rounding */
    double dtemp = value;
    if(dtemp>0){dtemp+=0.5;}
    if(dtemp<0){dtemp-=0.5;}
    return (long)dtemp;
}
int16_t convert_double2int16(double value){/* double --> int16 Rounding */
    double dtemp = value;
    if(dtemp>0){dtemp+=0.5;}
    if(dtemp<0){dtemp-=0.5;}
    if(dtemp>(int16_t)INT16_MAX){return (int16_t)INT16_MAX;}
    if(dtemp<(int16_t)INT16_MIN){return (int16_t)INT16_MIN;}
    return (int16_t)dtemp;
}

int16_t rdown_double2int16(double value){
    if(value>(int16_t)INT16_MAX){return (int16_t)INT16_MAX;}
    if(value<(int16_t)INT16_MIN){return (int16_t)INT16_MIN;}
    return (int16_t)value;
}

#ifdef __DEBUG__
    #define  TEST_FALSE 0
    #define  TEST_TRUE  1
    BOOL test_rdown_f2i16(void){
        if(rdown_double2int16(0.0) != 0){return TEST_FALSE;}
        if(rdown_double2int16(0.1) != 0){return TEST_FALSE;}
        if(rdown_double2int16(0.2) != 0){return TEST_FALSE;}
        if(rdown_double2int16(0.5) != 0){return TEST_FALSE;}
        if(rdown_double2int16(0.9) != 0){return TEST_FALSE;}
        if(rdown_double2int16(-0.1) != 0){return TEST_FALSE;}
        if(rdown_double2int16(-0.2) != 0){return TEST_FALSE;}
        if(rdown_double2int16(-0.5) != 0){return TEST_FALSE;}
        if(rdown_double2int16(-0.9) != 0){return TEST_FALSE;}

        if(rdown_double2int16(INT16_MAX) != INT16_MAX){return TEST_FALSE;}
        if(rdown_double2int16(INT16_MIN) != INT16_MIN){return TEST_FALSE;}
        if(rdown_double2int16(INT16_MAX+1) != INT16_MAX){return TEST_FALSE;}
        if(rdown_double2int16(INT16_MIN-1) != INT16_MIN){return TEST_FALSE;}

        if(rdown_double2int16(200.0) != 200){return TEST_FALSE;}
        if(rdown_double2int16(-200.0) != -200){return TEST_FALSE;}
        if(rdown_double2int16(200.9) != 200){return TEST_FALSE;}
        if(rdown_double2int16(-200.9) != -200){return TEST_FALSE;}

        return TEST_TRUE;
    }

#endif

