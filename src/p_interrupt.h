/*
 * p_interrupt.h
 *
 *  Created on: 2023/06/05
 *      Author: VINH-NT
 */

#ifndef P_INTERRUPT_H_
#define P_INTERRUPT_H_

void timer_cmt0_interrupt(void);  // CMTO Interrupt
void tmr0_interrupt(void);        // Timer R0 Interrupt
void SCI0_tx_interrupt(void);     // SCI0 TX Interrupt
void SCI0_rx_interrupt(void);     // SCI0 RX Interrupt
void SCI1_tx_interrupt(void);     // SCI1 TX Interrupt
void SCI1_rx_interrupt(void);     // SCI1 RX Interrupt
void SCI5_tx_interrupt(void);     // SCI5 TX Interrupt
void SCI5_rx_interrupt(void);     // SCI5 RX Interrupt
void SCI12_tx_interrupt(void);     // SCI12 TX Interrupt
void SCI12_rx_interrupt(void);     // SCI12 RX Interrupt

#endif /* P_INTERRUPT_H_ */
