/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_PORT.c
* Component Version: 2.4.1
* Device(s)        : R5F51135AxFP
* Description      : This file implements device driver for Config_PORT.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_PORT_Create(void)
{
    /* Set PORT0 registers */
    PORT0.PODR.BYTE = _04_Pm2_OUTPUT_1 | _00_Pm4_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORT0.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT;
    PORT0.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT0.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT0.PDR.BYTE = _04_Pm2_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT | _6B_PDR0_DEFAULT;

    /* Set PORT1 registers */
    PORT1.PODR.BYTE = _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORT1.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT1.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT1.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT1.PDR.BYTE = _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT;

    /* Set PORT2 registers */
    PORT2.PODR.BYTE = _04_Pm2_OUTPUT_1 | _00_Pm3_OUTPUT_0 | _10_Pm4_OUTPUT_1 | _20_Pm5_OUTPUT_1 | _00_Pm7_OUTPUT_0;
    PORT2.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT2.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT2.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT2.PDR.BYTE = _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | 
                     _80_Pm7_MODE_OUTPUT;

    /* Set PORT3 registers */
    PORT3.PODR.BYTE = _00_Pm1_OUTPUT_0;
    PORT3.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT;
    PORT3.PMR.BYTE = _00_Pm1_PIN_GPIO;
    PORT3.PDR.BYTE = _02_Pm1_MODE_OUTPUT | _D8_PDR3_DEFAULT;

    /* Set PORT5 registers */
    PORT5.PODR.BYTE = _08_Pm3_OUTPUT_1 | _00_Pm6_OUTPUT_0;
    PORT5.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT5.ODR1.BYTE = _00_Pm6_CMOS_OUTPUT;
    PORT5.PCR.BYTE = _00_Pm4_PULLUP_OFF | _00_Pm5_PULLUP_OFF;
    PORT5.PMR.BYTE = _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORT5.PDR.BYTE = _08_Pm3_MODE_OUTPUT | _00_Pm4_MODE_INPUT | _00_Pm5_MODE_INPUT | _40_Pm6_MODE_OUTPUT | 
                     _80_PDR5_DEFAULT;

    /* Set PORTA registers */
    PORTA.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORTA.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTA.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTA.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORTA.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT;

    /* Set PORTB registers */
    PORTB.PODR.BYTE = _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0 | 
                      _00_Pm6_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORTB.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTB.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTB.PMR.BYTE = _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | 
                     _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORTB.PDR.BYTE = _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | 
                     _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT;

    /* Set PORTC registers */
    PORTC.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORTC.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTC.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORTC.PCR.BYTE = _00_Pm7_PULLUP_OFF;
    PORTC.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO | 
                     _00_Pm7_PIN_GPIO;
    PORTC.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | 
                     _40_Pm6_MODE_OUTPUT | _00_Pm7_MODE_INPUT;

    /* Set PORTD registers */
    PORTD.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm2_OUTPUT_0;
    PORTD.PCR.BYTE = _00_Pm1_PULLUP_OFF | _00_Pm3_PULLUP_OFF | _00_Pm4_PULLUP_OFF;
    PORTD.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO;
    PORTD.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _00_Pm1_MODE_INPUT | _04_Pm2_MODE_OUTPUT | _00_Pm3_MODE_INPUT | 
                     _00_Pm4_MODE_INPUT | _E0_PDRD_DEFAULT;

    /* Set PORTE registers */
    PORTE.PODR.BYTE = _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0;
    PORTE.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTE.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT;
    PORTE.PCR.BYTE = _00_Pm0_PULLUP_OFF | _00_Pm1_PULLUP_OFF | _00_Pm6_PULLUP_OFF | _00_Pm7_PULLUP_OFF;
    PORTE.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORTE.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _00_Pm6_MODE_INPUT | _00_Pm7_MODE_INPUT;

    /* Set PORTF registers */
    PORTF.PODR.BYTE = _00_Pm6_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORTF.PMR.BYTE = _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORTF.PDR.BYTE = _40_Pm6_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT | _3F_PDRF_DEFAULT;

    /* Set PORTJ registers */
    PORTJ.PODR.BYTE = _01_Pm0_OUTPUT_1 | _00_Pm2_OUTPUT_0;
    PORTJ.PCR.BYTE = _08_Pm3_PULLUP_ON;
    PORTJ.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO;
    PORTJ.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _00_Pm3_MODE_INPUT | _32_PDRJ_DEFAULT;

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
