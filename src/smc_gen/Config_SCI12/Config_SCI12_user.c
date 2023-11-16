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
* File Name        : Config_SCI12_user.c
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
#define EXTERN extern
#include "../../PPM.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_sci12_tx_address;                /* SCI12 transmit buffer address */
extern volatile uint16_t  g_sci12_tx_count;                   /* SCI12 transmit data number */
extern volatile uint8_t * gp_sci12_rx_address;                /* SCI12 receive buffer address */
extern volatile uint16_t  g_sci12_rx_count;                   /* SCI12 receive data number */
extern volatile uint16_t  g_sci12_rx_length;                  /* SCI12 receive data length */
/* Start user code for global. Do not edit comment generated here */
void SCI12_tx_interrupt(void);
void SCI12_rx_interrupt(void); 
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI12_Create_UserInit
* Description  : This function adds user code after initializing the SCI12 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI12_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_transmit_interrupt
* Description  : This function is TXI12 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_SCI12_TXI12
#pragma interrupt r_Config_SCI12_transmit_interrupt(vect=VECT(SCI12,TXI12),fint)
#else
#pragma interrupt r_Config_SCI12_transmit_interrupt(vect=VECT(SCI12,TXI12))
#endif
static void r_Config_SCI12_transmit_interrupt(void)
{
    if (0U < g_sci12_tx_count)
    {
        SCI12.TDR = *gp_sci12_tx_address;
        gp_sci12_tx_address++;
        g_sci12_tx_count--;
    }
    else
    {
        SCI12.SCR.BIT.TIE = 0U;
        SCI12.SCR.BIT.TEIE = 1U;
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_transmitend_interrupt
* Description  : This function is TEI12 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_SCI12_TEI12
#pragma interrupt r_Config_SCI12_transmitend_interrupt(vect=VECT(SCI12,TEI12),fint)
#else
#pragma interrupt r_Config_SCI12_transmitend_interrupt(vect=VECT(SCI12,TEI12))
#endif
static void r_Config_SCI12_transmitend_interrupt(void)
{
    /* Set TXD12 pin */
    PORT1.PMR.BYTE &= 0xFEU;

    SCI12.SCR.BIT.TIE = 0U;
    SCI12.SCR.BIT.TE = 0U;
    SCI12.SCR.BIT.TEIE = 0U;

    r_Config_SCI12_callback_transmitend();
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_receive_interrupt
* Description  : This function is RXI12 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_SCI12_RXI12
#pragma interrupt r_Config_SCI12_receive_interrupt(vect=VECT(SCI12,RXI12),fint)
#else
#pragma interrupt r_Config_SCI12_receive_interrupt(vect=VECT(SCI12,RXI12))
#endif
static void r_Config_SCI12_receive_interrupt(void)
{
    if (g_sci12_rx_length > g_sci12_rx_count)
    {
        *gp_sci12_rx_address = SCI12.RDR;
        gp_sci12_rx_address++;
        g_sci12_rx_count++;
    }

    if (g_sci12_rx_length <= g_sci12_rx_count)
    {
        /* All data received */
        SCI12.SCR.BIT.RIE = 0U;
        SCI12.SCR.BIT.RE = 0U;
        r_Config_SCI12_callback_receiveend();
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_receiveerror_interrupt
* Description  : This function is ERI12 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_SCI12_ERI12
#pragma interrupt r_Config_SCI12_receiveerror_interrupt(vect=VECT(SCI12,ERI12),fint)
#else
#pragma interrupt r_Config_SCI12_receiveerror_interrupt(vect=VECT(SCI12,ERI12))
#endif
static void r_Config_SCI12_receiveerror_interrupt(void)
{
    uint8_t err_type;

    r_Config_SCI12_callback_receiveerror();

    /* Clear overrun, framing and parity error flags */
    err_type = SCI12.SSR.BYTE;
    err_type &= 0xC7U;
    err_type |= 0xC0U;
    SCI12.SSR.BYTE = err_type;
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_callback_transmitend
* Description  : This function is a callback function when SCI12 finishes transmission
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI12_callback_transmitend(void)
{
    /* Start user code for r_Config_SCI12_callback_transmitend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_callback_receiveend
* Description  : This function is a callback function when SCI12 finishes reception
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI12_callback_receiveend(void)
{
    /* Start user code for r_Config_SCI12_callback_receiveend. Do not edit comment generated here */
     // If RS-485 interface, turn off RS-485 drive here. 
     PORT1.PMR.BYTE |= 0x01U;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI12_callback_receiveerror
* Description  : This function is a callback function when SCI12 reception encounters error
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI12_callback_receiveerror(void)
{
    /* Start user code for r_Config_SCI12_callback_receiveerror. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
