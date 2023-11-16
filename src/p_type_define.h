/*
 * p_type_define.h
 *
 *  Created on: 2023/05/29
 *      Author: VINH-NT
 */

#ifndef P_TYPE_DEFINE_H_
#define P_TYPE_DEFINE_H_

typedef void (*FTBLV)(void);
typedef signed char TINY;    /* -128~128 */
typedef unsigned char BYTE;  /*  0~255    */
typedef unsigned short WORD; /*  0~65535  */
typedef signed char BOOL;    /* TRUE(1) / FALSE(0) */
enum FLG {NG,OK};
enum CHANEL {CH1,CH2,CH3,CH4,CH5};
enum CHANEL2 {heatch,cooling,CPC,sv3ch,fan1,fan2};
/* Event Input */
union UEVTI
{
    WORD data;
    struct EVTIBIT
    {
        BYTE THF1 : 1; /* 0 加熱温度ヒューズ入力（THF1） */
        BYTE THF2 : 1; /* 1 加湿温度ヒューズ入力（THF2）(未実装) */
        BYTE FS : 1;   /* 2 フロートSW入力（FS1）(未実装) */
        BYTE RCT : 1;  /* 3 冷凍機液温異常入力（RCT）*/
        BYTE CPT : 1;  /* 4 冷凍機異常入力（CPT） */
        BYTE n : 1;    /* 5 xxx（n）(未実装)*/
        BYTE yobi : 1; /* 6 予備 */
    } bitms;
    struct
    {
        BYTE evti1;
        BYTE evti2;
    } bytems;
};

/* SW Input */
union UDSWI
{
    BYTE data;
    struct DSWBIT
    {
        BYTE sw1 : 1;
        BYTE sw2 : 1;
        BYTE sw3 : 1;
    } bitms;
};
union UUNTEN_MODE
{
    WORD data;

    /* unten mode(2bit) settings */
    struct
    {
        WORD unten_md : 2; /* 0,1 steam(0)/humidification oven(1)/oven(2) */
        #define STANDBY 0          /* スタンバイ */
        #define RAPID_COOLING 1    /* 急速冷却 */
        #define FROZEN 2           /* 冷凍・冷蔵 */
    } md;
    //     /* access to unten mode (4bit). To access program mode. */
    // struct{
    //     WORD mode:4;  /* Cooking mode. @see below define. */
    //     WORD :4;
    //     WORD :4;
    //     WORD :4;
    // }md;
};
#endif /* P_TYPE_DEFINE_H_ */
