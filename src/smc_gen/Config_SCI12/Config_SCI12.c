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
* File Name        : Config_SCI12.c
* Component Version: 1.12.0
* Device(s)        : R5F51135AxFP
* Description      : This file implements device driver for Config_SCI12.
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
#include "Config_SCI12.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_sci12_tx_address;                /* SCI12 transmit buffer address */
volatile uint16_t  g_sci12_tx_count;                   /* SCI12 transmit data number */
volatile uint8_t * gp_sci12_rx_address;                /* SCI12 receive buffer address */
volatile uint16_t  g_sci12_rx_count;                   /* SCI12 receive data number */
volatile uint16_t  g_sci12_rx_length;                  /* SCI12 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Create
* Description  : This function initializes the SCI12 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI12_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI12) = 0U;

    /* Set interrupt priority */
    IPR(SCI12,TXI12) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI12.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI12.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI12.SIMR1.BIT.IICM = 0U;
    SCI12.SPMR.BYTE = _00_SCI_RTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI12.SMR.BYTE = _01_SCI_CLOCK_PCLK_4 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_STOP_1 | _00_SCI_PARITY_EVEN | 
                     _20_SCI_PARITY_ENABLE | _00_SCI_DATA_LENGTH_8 | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI12.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST | _72_SCI_SCMR_DEFAULT;
    SCI12.SEMR.BYTE = _00_SCI_16_BASE_CLOCK | _00_SCI_NOISE_FILTER_DISABLE | _00_SCI_LOW_LEVEL_START_BIT;

    /* Set bit rate */
    SCI12.BRR = 0x0CU;

    /* Set RXD12 pin */
    MPC.P11PFS.BYTE = 0x0CU;
    PORT1.PMR.BYTE |= 0x02U;

    /* Set TXD12 pin */
    MPC.P10PFS.BYTE = 0x0CU;
    PORT1.PODR.BYTE |= 0x01U;
    PORT1.PDR.BYTE |= 0x01U;

    R_Config_SCI12_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Start
* Description  : This function starts the SCI12 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI12_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI12,TXI12) = 0U;
    IR(SCI12,RXI12) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI12,TXI12) = 1U;
    IEN(SCI12,TEI12) = 1U;
    IEN(SCI12,RXI12) = 1U;
    IEN(SCI12,ERI12) = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Stop
* Description  : This function stops the SCI12 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI12_Stop(void)
{
    /* Set TXD12 pin */
    PORT1.PMR.BYTE &= 0xFEU;

    /* Disable serial transmit */
    SCI12.SCR.BIT.TE = 0U;

    /* Disable serial receive */
    SCI12.SCR.BIT.RE = 0U;

    /* Disable SCI interrupt */
    SCI12.SCR.BIT.TIE = 0U;
    SCI12.SCR.BIT.RIE = 0U;
    IEN(SCI12,TXI12) = 0U;
    IEN(SCI12,TEI12) = 0U;
    IR(SCI12,TXI12) = 0U;
    IEN(SCI12,RXI12) = 0U;
    IR(SCI12,RXI12) = 0U;
    IEN(SCI12,ERI12) = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Serial_Receive
* Description  : This function receives SCI12 data
* Arguments    : rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DMAC/DTC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI12_Serial_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > rx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_sci12_rx_count = 0U;
        g_sci12_rx_length = rx_num;
        gp_sci12_rx_address = rx_buf;
        SCI12.SCR.BIT.RIE = 1U;
        SCI12.SCR.BIT.RE = 1U;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Serial_Send
* Description  : This function transmits SCI12 data
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DMAC/DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR or MD_ERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI12_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > tx_num)
    {
        status = MD_ARGERROR;
    }
    else if (0U == IEN(SCI12, TXI12))
    {
        status = MD_ERROR;
    }
    else
    {
        gp_sci12_tx_address = tx_buf;
        g_sci12_tx_count = tx_num;
        IEN(SCI12, TXI12) = 0U;
        SCI12.SCR.BYTE |= 0xA0U;

        /* Set TXD12 pin */
        PORT1.PMR.BYTE |= 0x01U;
        IEN(SCI12, TXI12) = 1U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
