

#ifndef __ADVALUE_H__
#define __ADVALUE_H__
#include "p_type_define.h"
#include "r_cg_macrodriver.h"

void advalue(void);
void range_chk(void);
void adc_check_error();
int cscalsub2(int t);

enum ADC_PHASE
{
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CH9,
    ADC_RT1,
    ADC_RT2,
    ADC_ZERO,
    ADC_SPAN
};
enum EN_INPUT_CH{/* 入力チャネル */
    CH_KONAI,      /* 庫内温度 */
    CH_SHITUDO,    /* 湿度入力 */
    CH_MARUCHI1,   /* マルチ入力1 */
    CH_MARUCHI2,   /* マルチ入力2 */
    CH_MARUCHI3     /* マルチ入力3 */
};
enum EN_INPUT_MCH{/* 入力チャネル */
    CH_M1,         /* マルチ入力1 */
    CH_M2,         /* マルチ入力2 */
    CH_M3
};
enum srange{
    K200,          /* Kレンジ     */
    J200,          /* Jレンジ     */
    PT100,         /* Pt100レンジ */
    DC01V          /* DC 0～1V    */
};

#endif
