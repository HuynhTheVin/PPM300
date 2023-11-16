/*
 * ADS1148.h
 *
 *  Created on: 2023/06/19
 *      Author: VINH-NT
 */

#ifndef ADS1148_H_
#define ADS1148_H_


/******************************************************************************
 * @file    ADS1148.H
 * @author  Shinko-technos
 * @version V1.0.0
 * @date    2014.07.10
 * @brief   ADS1148(16bit)/1248(24bit)
 *****************************************************************************/
void adc(void);
void initADS1148A();

/*** 関数プロトタイプ ***/
int cscalsub2(int t);  /* 分解能倍 */
void Delay2(long nCount);
void inputnextch(BYTE ph, BYTE plx1);
void ADS1148A_PLX(BYTE);
void ADS1148A_PGA(BYTE);
void ADS1148_start(BYTE plx, BYTE gain);

/* ADC Port */

#define IO_ADC1_CS_ON PORT2.PODR.BIT.B5 = 0
#define IO_ADC1_CS_OFF PORT2.PODR.BIT.B5 = 1

#define IO_ADC1_START_ON PORT2.PODR.BIT.B4 = 0
#define IO_ADC1_START_OFF PORT2.PODR.BIT.B4 = 1

#define IO_ADC1_CLK_ON PORTJ.PODR.BIT.B0 = 1
#define IO_ADC1_CLK_OFF PORTJ.PODR.BIT.B0 = 0

#define IO_ADC1_DIN_ON PORT0.PODR.BIT.B2 = 1
#define IO_ADC1_DIN_OFF PORT0.PODR.BIT.B2 = 0

#define IO_ADC1_DOUT_ONQ (PORTJ.PIDR.BIT.B3 == 1)  /* In */
#define IO_ADC1_DOUT_OFFQ (PORTJ.PIDR.BIT.B3 == 0) /* In */

/* シフトレジスタIC */
#define IO_A_ON PORT0.PODR.BIT.B4 = 0
#define IO_A_OFF PORT0.PODR.BIT.B4 = 1

#define IO_B_ON PORT2.PODR.BIT.B3 = 0
#define IO_B_OFF PORT2.PODR.BIT.B3 = 1

#define IO_C_ON PORTC.PODR.BIT.B0 = 0
#define IO_C_OFF PORTC.PODR.BIT.B0 = 1

/*シフトレジスタ Pt2,Pt3,Pt4*/
#define IO_Pt2_ON PORT1.PODR.BIT.B7 = 0
#define IO_Pt2_OFF PORT1.PODR.BIT.B7 = 1

#define IO_Pt3_ON PORT1.PODR.BIT.B3 = 0
#define IO_Pt3_OFF PORT1.PODR.BIT.B3 = 1

#define IO_Pt4_ON PORT1.PODR.BIT.B2 = 0
#define IO_Pt4_OFF PORT1.PODR.BIT.B2 = 1

/* ADC1148 register */
#define ADCR_MUX0 0x00
#define ADCR_VBIAS 0x01
#define ADCR_MUX1 0x02
#define ADCR_SYS0 0x03
#define ADCR_OFC0 0x04
#define ADCR_OFC1 0x05
#define ADCR_OFC2 0x06
#define ADCR_FSC0 0x07
#define ADCR_FSC1 0x08
#define ADCR_FSC2 0x09
#define ADCR_IDAC0 0x0A
#define ADCR_IDAC1 0x0B
#define ADCR_GPIOCFG 0x0C
#define ADCR_GPIODIR 0x0D
#define ADCR_GPIODAT 0x0E

/* ADC1148 Command */
#define ADCCMD_WAKEUP 0x00   /* Exit sleep mode 0000 000x (00h, 01h)                    */
#define ADCCMD_SLEEP 0x02    /* Enter sleep mode 0000 001x (02h, 03h)                   */
#define ADCCMD_SYNC 0x04     /* Synchronize the A/D conversion 0000 010x (04h, 05h)     */
#define ADCCMD_RESET 0x06    /* Reset to power-up values 0000 011x (06h, 07h)           */
#define ADCCMD_NOP 0xFF      /* No operation 1111 1111 (FFh)                            */
#define ADCCMD_RDATA 0x12    /* Read data once 0001 001x (12h, 13h)                     */
#define ADCCMD_RDATAC 0x14   /* Read data continuously 0001 010x (14h, 15h)             */
#define ADCCMD_SDATAC 0x16   /* Stop reading data continuously 0001 011x (16h, 17h)     */
#define ADCCMD_RREG 0x20     /* Read from register rrrr 0010 rrrr (2xh)      0000_nnnn  */
#define ADCCMD_WREG 0x40     /* Write to register rrrr 0100 rrrr (4xh)       0000_nnnn  */
#define ADCCMD_SYSOCAL 0x60  /* System offset calibration 0110 0000 (60h)               */
#define ADCCMD_SYSGCAL 0x61  /* System gain calibration 0110 0001 (61h)                 */
#define ADCCMD_SELFOCAL 0x62 /* Self offset calibration 0110 0010 (62h)                 */

/* ADC1148 gain */
#define ADCPGA_01 0x00
#define ADCPGA_02 0x10
#define ADCPGA_04 0x20
#define ADCPGA_08 0x30
#define ADCPGA_16 0x40
#define ADCPGA_32 0x50
#define ADCPGA_64 0x60
#define ADCPGA_128 0x70

/* ADC1148 sample time fOSC = 4.096MHz */
#define ADC_RATE_200MS 0x00 // 199.258
#define ADC_RATE_100MS 0x01 // 99.633
#define ADC_RATE_50MS 0x02  // 49.820
#define ADC_RATE_25MS 0x03  // 24.920
#define ADC_RATE_15MS 0x04  // 12.467
#define ADC_RATE_7MS 0x05   // 6.241
#define ADC_RATE_4MS 0x06   // 3.124
#define ADC_RATE_2MS 0x07   // 1.569
#define ADC_RATE_1MS 0x08   // 1.014
#define ADC_RATE_0MS 0x09   // 0.514

/* MUX */
#define ADC_AIN0 0
#define ADC_AIN1 1
#define ADC_AIN2 2
#define ADC_AIN3 3
#define ADC_AIN4 4
#define ADC_AIN5 5
#define ADC_AIN6 6
#define ADC_AIN7 7

/* Burnout */
#define ADC_BURNOUT_OFF 0x00  /* burnout current off */
#define ADC_BURNOUT_00_5 0x40 /*  0.5 uA */
#define ADC_BURNOUT_02_0 0x80 /*  2.0 uA */
#define ADC_BURNOUT_10_0 0xC0 /* 10.0 uA */

// #define __ADCTYPE__ 1248 /* ADS1248 */
#define __ADCTYPE__ 1148 /* ADS1148 */

enum IN_PHASE
{                 /* 入力端子順定義 */
    INPH_KONAIA,     /* 0 庫内入力(sensin0)     */
    INPH_KONAIB,     /* 1 庫内入力(sensin0b)    */
    INPH_MARUCHI1A,  /* 2 マルチ入力1(sensin2)  */
    INPH_MARUCHI1B,  /* 3 マルチ入力1(sensinb2) */
    INPH_MARUCHI2A,  /* 4 マルチ入力2(sensin3)  */
    INPH_MARUCHI2B,  /* 5 マルチ入力2(sensinb3) */
    INPH_MARUCHI3A,  /* 6 マルチ入力3(sensin4)  */
    INPH_MARUCHI3B,  /* 7 マルチ入力3(sensinb4) */
    INPH_SHITUDO,    /* 8 湿度入力(sensin1)     */
    INPH_TTEMP1,     /* 9 端子温度1             */
    INPH_TTEMP2,     /* 10 端子温度2             */
    INPH_REFS1,       /* 11 基準スパン1            */
    INPH_REFS2,       /* 12 基準スパン2           */
    INPH_REFZ        /*13 基準ゼロ              */
};

enum PLX1
{/* 一次プレクサ順番定義 */
  PLX1_KONAIA,    /* 0 庫内入力(sensin0)     */
  PLX1_KONAIB,    /* 1 庫内入力(sensin0b)    */
  PLX1_MARUCHI1A, /* 2 マルチ入力1(sensin2)  */
  PLX1_MARUCHI1B, /* 3 マルチ入力1(sensinb2) */
  PLX1_MARUCHI2A, /* 4 マルチ入力2(sensin3)  */
  PLX1_MARUCHI2B, /* 5 マルチ入力2(sensinb3) */
  PLX1_MARUCHI3A, /* 6 マルチ入力3(sensin4)  */
  PLX1_MARUCHI3B, /* 7 マルチ入力3(sensinb4) */
  PLX1_NONE       /* 8 未使用 */
};
/* ADC内臓入力端子順 */
enum PLX2
{
  PLX2_INPUT,   /* AIN0 入力 */
  PLX2_SHITUDO, /* AIN1 湿度入力(sensin1)     */
  PLX2_TTEMP1,  /* AIN2 マルチ入力1の端子温度  */
  PLX2_TTEMP2,  /* AIN3 マルチ入力2の端子温度 */
  PLX2_REFS1,    /* AIN4 基準電圧スパン1        */
  PLX2_REFS2,    /* AIN5 基準電圧スパン2        */
  PLX2_REFZ     /* AIN6 基準電圧ゼロ          */
};
/* 入力端子順定義に対してADC内臓入力端子 */



#endif /* _ADS1148_H */

