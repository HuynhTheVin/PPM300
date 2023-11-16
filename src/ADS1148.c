/*
 * ADS1148.c
 *
 *  Created on: 2023/06/19
 *      Author: VINH-NT
 */

/******************************************************************************
 * @file    ADS1148.c
 * @author  Shinko-technos by V.Q.VINH
 * @version V1.0.0
 * @date    2019.08.08
 * @brief   TI ADS1148(16bit)/1248(24bit)
 *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#define EXTERN extern
#include "PPM.h"
#include "ADS1148.h"

/* Private define ------------------------------------------------------------*/
#define SET_ADC_RATE ADC_RATE_100MS // Conversion speed setting
#define ADC_SAMPLE 50
#define ADC_STAR_TI_8 8
#define ADC_ALARM_TIM 2000

const int16_t SAMP_MIN_TIM_TBL[] = {
    /* TvOMINÔťč(ń}25) */
    150, /* ADC_RATE_200MS    0x00 */
    75,  /* ADC_RATE_100MS    0x01 */
    37,  /* ADC_RATE_50MS     0x02 */
    19,  /* ADC_RATE_25MS     0x03 */
    9,   /* ADC_RATE_15MS     0x04 */
    5,   /* ADC_RATE_7MS      0x05 */
    2,   /* ADC_RATE_4MS      0x06 */
    2,   /* ADC_RATE_2MS      0x07 */
    1,   /* ADC_RATE_1MS      0x08 */
    0    /* ADC_RATE_0MS      0x09 */
};
const int16_t SAMP_MAX_TIM_TBL[] = {
    /* TvOMANÔťč(ń}25) */
    250, /* ADC_RATE_200MS    0x00 */
    125, /* ADC_RATE_100MS    0x01 */
    62,  /* ADC_RATE_50MS     0x02 */
    31,  /* ADC_RATE_25MS     0x03 */
    16,  /* ADC_RATE_15MS     0x04 */
    8,   /* ADC_RATE_7MS      0x05 */
    4,   /* ADC_RATE_4MS      0x06 */
    2,   /* ADC_RATE_2MS      0x07 */
    1,   /* ADC_RATE_1MS      0x08 */
    1    /* ADC_RATE_0MS      0x09 */
};
const BYTE IN_PLX2[] = {
    PLX2_INPUT,     /* 0 庫内入力(sensin0)     */
    PLX2_INPUT,     /* 1 庫内入力(sensin0b)    */
    PLX2_INPUT,     /* 2 マルチ入力1(sensin2)  */
    PLX2_INPUT,     /* 3 マルチ入力1(sensinb2) */
    PLX2_INPUT,     /* 4 マルチ入力2(sensin3)  */
    PLX2_INPUT,     /* 5 マルチ入力2(sensinb3) */
    PLX2_INPUT,   /* 6 マルチ入力3(sensin4)  */
    PLX2_INPUT,   /* 7 マルチ入力3(sensinb4) */
    PLX2_SHITUDO, /* 8 湿度入力(sensin1)     */
    PLX2_TTEMP1,  /* 9 端子温度1              */
    PLX2_TTEMP2,  /* 10 端子温度2           */
    PLX2_REFS1,    /* 11 基準スパン1           */
    PLX2_REFS2,    /* 12 基準スパン2           */
    PLX2_REFZ     /*13 基準ゼロ              */
};
const BYTE IN_PGA[] = {
    ADCPGA_128,     /* 0 庫内入力(sensin0)     */
    ADCPGA_128,     /* 1 庫内入力(sensin0b)    */
    ADCPGA_128,     /* 2 マルチ入力1(sensin2)  */
    ADCPGA_128,     /* 3 マルチ入力1(sensinb2) */
    ADCPGA_128,     /* 4 マルチ入力2(sensin3)  */
    ADCPGA_128,     /* 5 マルチ入力2(sensinb3) */
    ADCPGA_128, /* 6 マルチ入力3(sensin4)  */
    ADCPGA_128, /* 7 マルチ入力3(sensinb4) */
    ADCPGA_128, /* 8 湿度入力(sensin1)     */
    ADCPGA_128, /* 9 端子温度1             */
    ADCPGA_128, /* 10 端子温度2            */
    ADCPGA_128, /* 11 基準スパン1        */
    ADCPGA_128, /* 12 基準スパン2       */
    ADCPGA_128  /*13 基準ゼロ              */
};
/* Exported functions ------------------------------------------------------- */
// #pragma optimize = none
void Delay2(long nCount)
{
    for (; nCount != 0; nCount--)
        ;
}
/* ADC1 */
// #pragma optimize = none
void ADS1148_A1ston(void) // ADS1148 START -> L
{
    IO_ADC1_START_ON;
    IO_ADC1_START_ON;
}
// #pragma optimize = none
void ADS1148_A1stoff(void) // ADS1148 START -> H
{
    IO_ADC1_START_OFF;
    IO_ADC1_START_OFF;
}
// #pragma optimize = none
void ADS1148_A1skon(void) // ADS1148 SCLK-> H
{
    IO_ADC1_CLK_ON;
    IO_ADC1_CLK_ON;
    IO_ADC1_CLK_ON;
}
// #pragma optimize = none
void ADS1148_A1skoff(void) // ADS1148 SCLK-> L
{
    IO_ADC1_CLK_OFF;
    IO_ADC1_CLK_OFF;
}
// #pragma optimize = none
void ADS1148_A1dion(void) // ADS1148 DIN-> H
{
    IO_ADC1_DIN_ON;
    IO_ADC1_DIN_ON;
}
// #pragma optimize = none
void ADS1148_A1dioff(void) // ADS1148 DIN-> L
{
    IO_ADC1_DIN_OFF;
    IO_ADC1_DIN_OFF;
}
// #pragma optimize = none
void ADS1148_A1csoff(void) // CS -> H
{
    IO_ADC1_CS_OFF;
    IO_ADC1_CS_OFF;
}
// #pragma optimize = none
void ADS1148_A1cson(void) // CS -> L
{
    IO_ADC1_CS_ON;
    IO_ADC1_CS_ON;
}
int ADS1148_A1doHIGH(void)
{
    if (IO_ADC1_DOUT_ONQ)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

BYTE ADS1148_A1read8(BYTE cmdt) // ADC1 Read 8bits
{
    BYTE i, data;

    data = 0;
    for (i = 0; i < 8; i++)
    {
        ADS1148_A1skon(); // ADS1148 SCLK-> H
                          // write
        if (cmdt & 0x80)
        {
            ADS1148_A1dion(); // ADS1148 DIN-> H
        }
        else
        {
            ADS1148_A1dioff(); // ADS1148 DIN-> L
        }
        cmdt <<= 1;
        // read
        data <<= 1;
        if (ADS1148_A1doHIGH() == 1)
        {              // DOUT = 1
            data |= 1; // Make data
        }
        ADS1148_A1skoff(); // ADS1148 SCLK-> L
    }
    ADS1148_A1dion(); // ADS1148 DIN-> H  NOP=0xFF  dummy
    return data;
}

void ADS1148_A1out8(BYTE cmdt) /* ADC1 Wrtie 8bits */
{
    BYTE i;

    for (i = 0; i < 8; i++)
    {
        IO_ADC1_CLK_ON;
        if (cmdt & 0x80)
        {
            IO_ADC1_DIN_ON; // ADS1148 DIN-> H
        }
        else
        {
            IO_ADC1_DIN_OFF; // ADS1148 DIN-> L
        }
        cmdt <<= 1;
        IO_ADC1_CLK_OFF;
    }
    IO_ADC1_DIN_ON; // ADS1148 DIN-> H
}

/***************************************************************************************
    ADS1148 Initilize
    NOP  0xFF   If there is no data to write, access with NOP instruction (DIN=1)
    ADD  REG
     00  MUX0   00000001 Input AIN0,AIN1 [Differential]
     01  VBIAS  00000000 (AVDD+AVSS)/2 Set AINx to 1 when applying bias
     02  MUX1   00000000  Internal reference is always OFF,RFE0
     03  SYS0   00000111    PGA=1 640SPS(Conversion time: ~2ms)
     0A  IDAC0  00001000 DOUT/DRDY Mode (H¨L change at the end of conversion)
 ***************************************************************************************/
const BYTE ADS1148inittbl1[] = {
    /* Initialization table1 */
    0x4A, // Command1 (WREG)
    0x00, // Command2 The number of data (n-1)
    0x08  // IDAC0    DOUT/DRDY Mode
};
const BYTE ADS1148inittbl0[] = {
    /* Initialization table0 */
    0x40, // Command1 (WREG)
    0x03, // Command2                 The number of data (n-1)
    0x07, // MUX0                     A0(+)A7(-) */
    0x00, // VBIAS                    1/2oCAXOFF
    0x00, // MUX1                     Internal reference is always OFF,RFE0
    0x01  // SYS0                     PGA*1 640SPS(tCONV~2ms) START Pin Conversion Times
    //   0x00     //SYS0                     PGA*1   5SPS(200ms)
};

void adc_spi_reset(void)
{
    // ADS1148A SPI Reset
    ADS1148_A1dion();  // DIN-> H  NOP=0xFF(dummy High)
    ADS1148_A1skoff(); // SK -> L
    ADS1148_A1csoff(); // CS -> H
    Delay2(300);       // Wait
    ADS1148_A1cson();  // CS -> L
    Delay2(300);       // Wait
}

void initADS1148A(void) /* ADC Initialization */
{
    BYTE i;

    // ADS1148A SPI Reset
    adc_spi_reset();

    ADS1148_A1stoff(); // START -> H
    Delay2(300);
    // command WREG
    for (i = 0; i < sizeof(ADS1148inittbl0); i++)
    {
        ADS1148_A1out8(ADS1148inittbl0[i]);
    }
    // command WREG
    for (i = 0; i < sizeof(ADS1148inittbl1); i++)
    {
        ADS1148_A1out8(ADS1148inittbl1[i]);
    }
    ADS1148_A1ston();           // START -> L
    INPUT_ADC.adc_set_sumi = 1; // ADC Initialized
    INPUT_ADC.adc_error = 0;
    // wdtadc = ADC_ALARM_TIM; /* wdt counter reset 2b */
}

void adc_reset(void)
{
    adc_spi_reset();
    ADS1148_A1stoff();            // START -> H
    ADS1148_A1out8(ADCCMD_RESET); // RESET
    ADS1148_A1ston();             // START -> L
    Delay2(600);

    /* !! */
    /* must wait 0.6ms  to continous send next command */
}

void adc1read1148(void) /* AD Read conversion result  */
{
    /* 16bit ADC 1148 */
    long data = 0;
    BYTE i;

    IO_ADC1_DIN_ON;
    data = 0;
    for (i = 0; i < 16; i++)
    {
        // IO_ADC1_CLK_ON;
        ADS1148_A1skon();
        data <<= 1;
        if (IO_ADC1_DOUT_ONQ)
        {
            data |= 1;
        }
        IO_ADC1_CLK_OFF;
    }

    ADS1148_A1out8(0xff); /* NOP */

    if (data & B15)
    { // Negative convert
        data |= 0xFFFF0000;
    }
    INPUT_ADC.adt = data; // Saving the captured value
}
void adc1read1248(void) /* AD Read conversion result */
{
    /* 24bit ADC 1248 */
    long data = 0;
    BYTE i;

    IO_ADC1_DIN_ON;
    data = 0;
    for (i = 0; i < 24; i++)
    {
        // IO_ADC1_CLK_ON;
        ADS1148_A1skon();
        data <<= 1;
        if (IO_ADC1_DOUT_ONQ)
        {
            data |= 1;
        }
        IO_ADC1_CLK_OFF;
    }

    ADS1148_A1out8(0xff); /* NOP to DRY ON */

    if (data & B23)
    { // Negative convert
        data |= 0xFF000000;
    }
    INPUT_ADC.adt = data; // Saving the captured value
}
/* Select chanel */
/* ADCR_MUX0 */
/* B7.6    00:  Burnout current source off 0/0.2/2/10uA (disable)  */
/* B5.4.3  dt:  Positive input channel selection bits.          */
/* B2.1.0  111: Negative input channel selection bits.  (AIN7)  */
/*  */
void ADS1148A_PLX(BYTE dt)
{ /* Channel settings */

    ADS1148_A1out8(ADCCMD_WREG | ADCR_MUX0); // Command
    ADS1148_A1out8(0x00);                    // The number of data
    ADS1148_A1out8(dt);                      // data
}
/* dt = 0: input       */
/* dt = 1: offset */
void ADS1148_A1MUX1(BYTE dt)
{ /* OFSSET */
    BYTE d;

    d = 0x38; /* Internal VREF always On */
              /* VREF conectto REF0      */
    if (dt)
    {
        d |= B0; /* offset measurement  */
    }
    ADS1148_A1out8(ADCCMD_WREG | ADCR_MUX1); // Command
    ADS1148_A1out8(0x00);                    // The number of data
    ADS1148_A1out8(d);                       // data
}

/* ADCR_SYS0 */
/* Set GainAsample rate */
/* B7: 0              */
/* B6.5.4: Gain */
/* B3`0:  sample rate   */
void ADS1148_A1PGA(BYTE dt)
{

    ADS1148_A1out8(ADCCMD_WREG | ADCR_SYS0); // Command
    ADS1148_A1out8(0x00);                    // The number of data
    ADS1148_A1out8(dt | SET_ADC_RATE);       // data + sample rate (xxms)
}
void ADS1148_start(BYTE plx, BYTE gain)
{

    plx <<= 3;
    plx += 0x07;       /* Negative: AIN7 */
    ADS1148_A1stoff(); // START -> H
                       //* ADS1148A_PGA(adgain);
    ADS1148A_PLX(plx);
    ADS1148_A1PGA(gain);
    ADS1148_A1ston(); // CS -> L
}

/*-------------------------------------------------------------------------------*/

#define AD_SPAN 1 /* ajs が 20000 倍値の為に簡略化 Kレンジ 20mVスパン*/
#define ADT_SPAN 1
#define LINEBITS (tdiv * minbit)
#define RTSPAN 5000

BYTE chk_dpoint(void)
{
    if (INPUT_ADC.linech == CH_KONAI)
    {
        return 1; /* Pt100 小数点付き */
    }
    else if (INPUT_ADC.linech == CH_SHITUDO)
    {
        return 0; /* DC01V1 湿度小数点なし */
    }
    else
    { /* マルチ入力 */
        return 1; /* 小数点付き */
    }
}
long max1(long a, long b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
long min1(long a, long b)
{
    if (a > b)
    {
        return b;
    }
    else
    {
        return a;
    }
}
void vfsel_KONAIA(void)
{ /* 庫内温度入力 */
    inputnextch(INPH_KONAIA, PLX1_KONAIA);
}
void vfsel_KONAIB(void)
{ /* 庫内入力INB */
    inputnextch(INPH_KONAIB, PLX1_KONAIB);
}
void vfsel_SHITUDO(void)
{ /* 湿度入力 */
    inputnextch(INPH_SHITUDO, PLX1_NONE);
}
void vfsel_MARUCHI1A(void)
{ /* マルチ入力1 */
    inputnextch(INPH_MARUCHI1A, PLX1_MARUCHI1A);
}
void vfsel_MARUCHI2A(void)
{ /* マルチ入力2 */
    inputnextch(INPH_MARUCHI2A, PLX1_MARUCHI2A);
}
void vfsel_MARUCHI3A(void)
{ /*マルチ入力3 */
    inputnextch(INPH_MARUCHI3A, PLX1_MARUCHI3A);
}
void vfsel_INPU_REFZ1(void)
{ /* 基準電圧入力 */
    if (INPUT_ADC.cfadc1.bitms.kijunZero_Span == 1)
    {
        inputnextch(INPH_REFS1, PLX1_NONE);
        // INPUT_ADC.cfadc1.bitms.kijunZero_Span = 0; /* 切り替え */
    }
    else
    {
        inputnextch(INPH_REFZ, PLX1_NONE);
        // INPUT_ADC.cfadc1.bitms.kijunZero_Span = 1; /* 切り替え */
    }
    
}
void vfsel_INPU_REFZ2(void)
{ /* 基準電圧入力 */
    if (INPUT_ADC.cfadc1.bitms.kijunZero_Span == 1)
    {
        inputnextch(INPH_REFS2, PLX1_NONE);
        INPUT_ADC.cfadc1.bitms.kijunZero_Span = 0; /* 切り替え */
    }
    else
    {
        inputnextch(INPH_REFZ, PLX1_NONE);
        INPUT_ADC.cfadc1.bitms.kijunZero_Span = 1; /* 切り替え */
    }
    
}
void vfsel_MARUCHI1B(void)
{ /* マルチ入力1INB*/
    inputnextch(INPH_MARUCHI1B, PLX1_MARUCHI1B);

    INPUT_ADC.sensinb[CH_MARUCHI1] = 0;
}
void vfsel_MARUCHI2B(void)
{ /*マルチ入力2INB*/
    inputnextch(INPH_MARUCHI2B, PLX1_MARUCHI2B);
}
void vfsel_MARUCHI3B(void)
{ /*マルチ入力3INB*/
    inputnextch(INPH_MARUCHI3B, PLX1_MARUCHI3B);
}
void vfsel_TTEMP1(void)
{ /*端子温度*/
    inputnextch(INPH_TTEMP1, PLX1_NONE);
}
void vfsel_TTEMP2(void)
{ /*端子温度*/
    inputnextch(INPH_TTEMP2, PLX1_NONE);
}

/* IN1 ¨ T/INB ¨IN2 ¨ Z/S ¨ IN3 ¨ T/INB ¨ IN4 ¨ T/INB */
const FTBLV vfselfunc[] = {
    vfsel_KONAIA, vfsel_KONAIB, vfsel_SHITUDO, vfsel_INPU_REFZ1,
    vfsel_INPU_REFZ2,
    vfsel_MARUCHI1A, vfsel_MARUCHI1B, vfsel_MARUCHI2A, vfsel_MARUCHI2B, vfsel_MARUCHI3A, vfsel_MARUCHI3B,
    vfsel_TTEMP1, vfsel_TTEMP2};

void mplset(void)
{

    if (TIMDT.iw)
    {
        INPUT_ADC.adtcn = (INPUT_ADC.adtcn >= (sizeof(vfselfunc)/4-1)) ? (0) : (INPUT_ADC.adtcn + 1);
        TIMDT.iw--;
    }
    else
    {
        INPUT_ADC.adtcn = (INPUT_ADC.adtcn >= (sizeof(vfselfunc)/4-1)) ? (0) : (INPUT_ADC.adtcn + 1);
    }
    if (TIMDT.iw)
    {
        (*vfselfunc[INPUT_ADC.adtcn])();
    }
    else
    {
        (*vfselfunc[INPUT_ADC.adtcn])();
    }
}

long vfrd_datasub(long *p)
{ /* ADC変換データを保存する */
    TINY i;
    long *pt1;
    long dt = 0;

    if (TIMDT.iw)
    {
        for (i = 0; i < HEIKIN1; i++)
        {
            *p++ = INPUT_ADC.adt;
        }
        return INPUT_ADC.adt;
    }
    else
    {
        p += HEIKIN1 - 1;
        pt1 = p - 1;
        for (i = 0; i < HEIKIN1 - 1; i++)
        {
            *p = *pt1;
            dt += *p;
            p--;
            pt1--;
        }
        *p = INPUT_ADC.adt;
        dt += INPUT_ADC.adt;
        return dt / HEIKIN1;
    }
}

void vfrd_KONAIA(void)
{ /* 庫内温度入力 */
    //* sensin[CH_KONAI] = vfrd_datasub((long *)&sensinH1[CH_KONAI][0]);
    INPUT_ADC.sensin[CH_KONAI] = INPUT_ADC.adt;
    INPUT_ADC.cfadc1.bitms.konai_in_cal_request = 1; /* リニアライズ要求 */
}
void vfrd_KONAIB(void)
{ /* 庫内温度INB入力 */
    INPUT_ADC.sensinb[CH_KONAI] = vfrd_datasub((long *)&INPUT_ADC.sensinbH1[CH_KONAI][0]);
    //* sensinb[CH_KONAI] = adt;
}
void vfrd_SHITUDO(void)
{ /* 湿度入力 */
    //* sensin[CH_SHITUDO] = vfrd_datasub((long *)&sensinH1[CH_SHITUDO][0]);
    INPUT_ADC.sensin[CH_SHITUDO] = INPUT_ADC.adt;
    INPUT_ADC.cfadc1.bitms.shitsudo_in_cal_request = 1; /* リニアライズ要求 */
}
void vfrd_MARUCHI1A(void)
{ /* マルチ1入力*/
    //* sensin[CH_MARUCHI1] = vfrd_datasub((long *)&sensinH1[CH_MARUCHI1][0]);
    INPUT_ADC.sensin[CH_MARUCHI1] = INPUT_ADC.adt;
    INPUT_ADC.cfadc1.bitms.manuchi1_in_cal_request = 1; /* リニアライズ要求 */
}
void vfrd_MARUCHI1B(void)
{ /*マルチ1INB入力 */
    INPUT_ADC.sensinb[CH_MARUCHI1] = vfrd_datasub((long *)&INPUT_ADC.sensinbH1[CH_MARUCHI1][0]);
    //* sensinb[CH_MARUCHI1] = adt;
}
void vfrd_MARUCHI2A(void)
{ /*マルチ2入力 */
    //* sensin[CH_MARUCHI2] = vfrd_datasub((long *)&sensinH1[CH_MARUCHI2][0]);
    INPUT_ADC.sensin[CH_MARUCHI2] = INPUT_ADC.adt;
    INPUT_ADC.cfadc1.bitms.manuchi2_in_cal_request = 1; /* リニアライズ要求 */
}
void vfrd_MARUCHI2B(void)
{ /*マルチ2INB入力 */
    INPUT_ADC.sensinb[CH_MARUCHI2] = vfrd_datasub((long *)&INPUT_ADC.sensinbH1[CH_MARUCHI2][0]);
    //* sensinb[CH_MARUCHI2] = adt;
}
void vfrd_MARUCHI3A(void)
{ /* マルチ3入力 */
    //* sensin[CH_MARUCHI3] = vfrd_datasub((long *)&sensinH1[CH_MARUCHI3][0]);
    INPUT_ADC.sensin[CH_MARUCHI3] = INPUT_ADC.adt;
    INPUT_ADC.cfadc1.bitms.manuchi3_in_cal_request = 1; /* リニアライズ要求 */
}
void vfrd_MARUCHI3B(void)
{ /*マルチ3INB入力 */
    INPUT_ADC.sensinb[CH_MARUCHI3] = vfrd_datasub((long *)&INPUT_ADC.sensinbH1[CH_MARUCHI3][0]);
    //* sensinb[CH_MARUCHI3] = adt;
}
void vfrd_TTEMP1(void)
{ /* 端子温度1入力*/
    INPUT_ADC.termt1 = vfrd_datasub((long *)&INPUT_ADC.termt1H1[0]);
    //* termt1 = adt;
}
void vfrd_TTEMP2(void)
{ /* 端子温度w入力 */
    INPUT_ADC.termt2 = vfrd_datasub((long *)&INPUT_ADC.termt2H1[0]);
    //* termt2 = adt;
}
void vfrd_REFS1(void)
{ /* 基準電圧スパン1入力 */
    INPUT_ADC.ref_s1 = vfrd_datasub((long *)&INPUT_ADC.ref_s1H1[0]);
    //* ref_s = adt;
}
void vfrd_REFS2(void)
{ /* 基準電圧スパン2入力 */
    INPUT_ADC.ref_s2 = vfrd_datasub((long *)&INPUT_ADC.ref_s2H1[0]);
    //* ref_s = adt;
}
void vfrd_REFZ1(void)
{ /*基準電圧ゼロ入力*/
    INPUT_ADC.ref_z1 = vfrd_datasub((long *)&INPUT_ADC.ref_z1H1[0]);
    //* ref_z = adt;
}
void vfrd_REFZ2(void)
{ /*基準電圧ゼロ入力*/
    INPUT_ADC.ref_z2 = vfrd_datasub((long *)&INPUT_ADC.ref_z2H1[0]);
    //* ref_z = adt;
}

const FTBLV vfrdfunc[] = {/* 各入力ADC変換結果保存 */
                          vfrd_KONAIA, vfrd_KONAIB, vfrd_MARUCHI1A, vfrd_MARUCHI1B, vfrd_MARUCHI2A,
                          vfrd_MARUCHI2B, vfrd_MARUCHI3A, vfrd_MARUCHI3B, vfrd_SHITUDO, vfrd_TTEMP1, vfrd_TTEMP2,
                          vfrd_REFS1, vfrd_REFS2, vfrd_REFZ1, vfrd_REFZ2};

void adcprd(void)
{
    (*vfrdfunc[INPUT_ADC.adcphase])();
}

void ShiftData(BYTE da)
{ /* プレクサ選択の74VHC164シフトIC伝送` */
    switch (da)
    {
    case PLX1_KONAIA:
        IO_A_ON;
        IO_B_ON;
        IO_C_ON;
        break;
    case PLX1_KONAIB:
        IO_A_OFF;
        IO_B_ON;
        IO_C_ON;
        break;
    case PLX1_MARUCHI1A:
        IO_A_ON;
        IO_B_OFF;
        IO_C_ON;
        break;
    case PLX1_MARUCHI1B:
        IO_A_OFF;
        IO_B_OFF;
        IO_C_ON;
        break;
    case PLX1_MARUCHI2A:
        IO_A_ON;
        IO_B_ON;
        IO_C_OFF;
        break;
    case PLX1_MARUCHI2B:
        IO_A_OFF;
        IO_B_ON;
        IO_C_OFF;
        break;
    case PLX1_MARUCHI3A:
        IO_A_ON;
        IO_B_OFF;
        IO_C_OFF;
        break;
    case PLX1_MARUCHI3B:
        IO_A_OFF;
        IO_B_OFF;
        IO_C_OFF;
        break;
    default:
        break;
    }
}

void inputnextch(BYTE ph, BYTE plx1)
{                          /* チャンネル変更、プレクサ切り替え、ADCを書き込み */
    BYTE gtd = ADCPGA_128; /* ゲイン1 */
    BYTE plx2 = PLX2_INPUT;

    plx2 = IN_PLX2[ph]; /* ADC内臓プレクサ */
                        //* gtd  = IN_PGA[ph]; /* ADC内臓ゲイン   */
    INPUT_ADC.adcphase = ph;
    switch (ph)
    {
    case INPH_KONAIA:
        gtd = ADCPGA_08; /* ゲイン2 */
        break;
    case INPH_MARUCHI1A:
        if (INPUT_ADC.wksens[CH_M1] == PT100)
        {
            gtd = ADCPGA_08; /* ゲイン2 */
            IO_Pt2_ON;
        }
        else
        {
             IO_Pt2_OFF;
        }
        break;
    case INPH_MARUCHI2A:
        if (INPUT_ADC.wksens[CH_M2] == PT100)
        {
            gtd = ADCPGA_08; /* ゲイン2 */
            IO_Pt3_ON;
        }
        else
        {
            IO_Pt3_OFF;
        }
        break;
    case INPH_MARUCHI3A:
        if (INPUT_ADC.wksens[CH_M3] == PT100)
        {
            gtd = ADCPGA_08; /* ゲイン2 */
            IO_Pt4_ON;
        }
        else
        {
            IO_Pt4_OFF;
        }
        break;
    case INPH_REFS2:
        gtd = ADCPGA_08; /* ゲイン2 */
        break;
    }
    ShiftData(plx1);          /* プレクサ選択    */
    ADS1148_start(plx2, gtd); /* ADCセット       */
}

/* 1ms */
void adc(void)
{
    // BYTE n;

    if (TIMDT.t125m == 0)
    {                                          /*チャンネル変更 */
        mplset();                              /* チャネル選択                   */
        INPUT_ADC.cfadc2.bitms.ADC_henkan = 0; /* 変換済みフラグクリア            */
    }
    else if (TIMDT.t125m == 10)
    {                      /* ハード安定時間待ち。ADC変換開始 */
        ADS1148_A1stoff(); /* START -> H                      */
        INPUT_ADC.adt = 0; /* ADC値初期化                     */
    }
    else if (TIMDT.t125m == 11)
    {
        ADS1148_A1ston(); /* START -> L                      */
    }
    else if (TIMDT.t125m > 50)
    { /* DAC変換待ち                     */
        if (INPUT_ADC.cfadc2.bitms.ADC_henkan == 0)
        { /* 変換待ち                        */
            if (IO_ADC1_DOUT_OFFQ)
            {                                          /* ADC変換済み                     */
                adc1read1148();                        /* ADC変換結果の読取り             */
                adcprd();                              /* 取込み値の保存                  */
                INPUT_ADC.cfadc2.bitms.ADC_henkan = 1; /* ADC変換済みセット               */
            }
        }
    }
    //* t125m = (t125m >= INT1000/8) ? (0) : (t125m + 1);  /* 125msÇ */
    if (TIMDT.t125m >= INT1000 / 8)
    {
        TIMDT.t125m = 0;
        INPUT_ADC.cfadc2.bitms.ADC_125ms = 1; /* 入力換算要求  */
    }
    else
    {
        TIMDT.t125m++;
    }
}


