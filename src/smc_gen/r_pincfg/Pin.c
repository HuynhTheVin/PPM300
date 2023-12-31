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
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Pin.c
* Version          : 1.0.2
* Device(s)        : R5F51135AxFP
* Description      : This file implements SMC pin code generation.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Pins_Create(void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set MTIOC0B pin */
    MPC.P15PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x20U;

    /* Set MTIOC0C pin */
    MPC.P32PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x04U;

    /* Set RXD0 pin */
    MPC.P21PFS.BYTE = 0x0AU;
    PORT2.PMR.BYTE |= 0x02U;

    /* Set RXD1 pin */
    MPC.P30PFS.BYTE = 0x0AU;
    PORT3.PMR.BYTE |= 0x01U;

    /* Set RXD5 pin */
    MPC.PC2PFS.BYTE = 0x0AU;
    PORTC.PMR.BYTE |= 0x04U;

    /* Set RXD12 pin */
    MPC.P11PFS.BYTE = 0x0CU;
    PORT1.PMR.BYTE |= 0x02U;

    /* Set SCL0 pin */
    MPC.PB0PFS.BYTE = 0x0FU;
    PORTB.PMR.BYTE |= 0x01U;

    /* Set SDA0 pin */
    MPC.PA6PFS.BYTE = 0x0FU;
    PORTA.PMR.BYTE |= 0x40U;

    /* Set TXD0 pin */
    PORT2.PODR.BYTE |= 0x01U;
    MPC.P20PFS.BYTE = 0x0AU;
    PORT2.PDR.BYTE |= 0x01U;
    // PORT2.PMR.BIT.B0 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD1 pin */
    PORT2.PODR.BYTE |= 0x40U;
    MPC.P26PFS.BYTE = 0x0AU;
    PORT2.PDR.BYTE |= 0x40U;
    // PORT2.PMR.BIT.B6 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD5 pin */
    PORTC.PODR.BYTE |= 0x08U;
    MPC.PC3PFS.BYTE = 0x0AU;
    PORTC.PDR.BYTE |= 0x08U;
    // PORTC.PMR.BIT.B3 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set TXD12 pin */
    PORT1.PODR.BYTE |= 0x01U;
    MPC.P10PFS.BYTE = 0x0CU;
    PORT1.PDR.BYTE |= 0x01U;
    // PORT1.PMR.BIT.B0 = 1U; // Please set the PMR bit after TE bit is set to 1.

    /* Set USB0_VBUSEN pin */
    MPC.P16PFS.BYTE = 0x11U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

