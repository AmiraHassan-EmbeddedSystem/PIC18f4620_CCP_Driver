/* 
 * File:   internal_interrupt.h
 * Author: Amira Hassan
 * 
 * Created on 19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains the initialization and handling functions 
 *              for internal interrupts using the Hardware Abstraction Layer (HAL).
 *              Internal interrupts are triggered by internal peripherals such as timers,
 *              ADCs, or communication modules (e.g., UART, SPI) to handle specific events 
 *              (e.g., timer overflow, data reception).
 *             
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H

/* SECTION: Include */
#include "manage_interrupt.h"

/* SECTION: Macro Declarations */

 /*TIMER0_INTERRUPT*/
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE
    #define TIMER0_INTERRUPT_ENABLE()   (INTCONbits.TMR0IE = 1)
    #define TIMER0_INTERRUPT_DISABLE()   (INTCONbits.TMR0IE = 0)
    #define TIMER0_INTERRUPT_CLEAR_FLAG()   (INTCONbits.TMR0IF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS
    #define TIMER0_INTERRUPT_HIGH_PRIORITY()   (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_LOW_PRIORITY()   (INTCON2bits.TMR0IP = 0)
#endif
#endif

 /*TIMER1_INTERRUPT*/
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE
    #define TIMER1_INTERRUPT_ENABLE()   (PIE1bits.TMR1IE = 1)
    #define TIMER1_INTERRUPT_DISABLE()   (PIE1bits.TMR1IE = 0)
    #define TIMER1_INTERRUPT_CLEAR_FLAG()   (PIR1bits.TMR1IF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS
    #define TIMER1_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.TMR1IP = 1)
    #define TIMER1_INTERRUPT_LOW_PRIORITY()   (IPR1bits.TMR1IP = 0)
#endif
#endif


 /*TIMER2_INTERRUPT*/
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptDisable()         (PIE1bits.TMR2IE = 0)
/* This routine sets the interrupt enable for the TIMER2 Module */
#define TIMER2_InterruptEnable()          (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the TIMER2 Module */
#define TIMER2_InterruptFlagClear()       (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the TIMER2 Module Interrupt Priority to be High priority */
#define TIMER2_HighPrioritySet()          (IPR1bits.TMR2IP = 1)
/* This routine set the TIMER2 Module Interrupt Priority to be Low priority */
#define TIMER2_LowPrioritySet()           (IPR1bits.TMR2IP = 0)
#endif
#endif


 /*TIMER3_INTERRUPT*/
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    #define TIMER3_INTERRUPT_ENABLE()   (PIE2bits.TMR3IE = 1)
    #define TIMER3_INTERRUPT_DISABLE()   (PIE2bits.TMR3IE = 0)
    #define TIMER3_INTERRUPT_CLEAR_FLAG()   (PIR2bits.TMR3IF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS
    #define TIMER3_INTERRUPT_HIGH_PRIORITY()   (IPR2bits.TMR3IP = 1)
    #define TIMER3_INTERRUPT_LOW_PRIORITY()   (IPR2bits.TMR3IP = 0)
#endif
#endif


 /*CCP1_INTERRUPT*/
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    /* This routine clears the interrupt enable for the CCP1 Module */
    #define CCP1_INTERRUPT_DISABLE()         (PIE1bits.CCP1IE = 0)
    /* This routine sets the interrupt enable for the CCP1 Module */
    #define CCP1_INTERRUPT_ENABLE()          (PIE1bits.CCP1IE = 1)
    /* This routine clears the interrupt flag for the CCP1 Module */
    #define CCP1_INTERRUPT_CLEAR_FLAG()       (PIR1bits.CCP1IF = 0)
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        /* This routine set the CCP1 Module Interrupt Priority to be High priority */
        #define CCP1_HighPrioritySet()          (IPR1bits.CCP1IP = 1)
        /* This routine set the CCP1 Module Interrupt Priority to be Low priority */
        #define CCP1_LowPrioritySet()           (IPR1bits.CCP1IP = 0)
    #endif
#endif

 /*CCP2_INTERRUPT*/
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
    /* This routine clears the interrupt enable for the CCP1 Module */
    #define CCP2_INTERRUPT_DISABLE()         (PIE2bits.CCP2IE = 0)
    /* This routine sets the interrupt enable for the CCP1 Module */
    #define CCP2_INTERRUPT_ENABLE()          (PIE2bits.CCP2IE = 1)
    /* This routine clears the interrupt flag for the CCP1 Module */
    #define CCP2_INTERRUPT_CLEAR_FLAG()       (PIR2bits.CCP2IF = 0)
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        /* This routine set the CCP1 Module Interrupt Priority to be High priority */
        #define CCP2_HighPrioritySet()          (IPR2bits.CCP2IP = 1)
        /* This routine set the CCP1 Module Interrupt Priority to be Low priority */
        #define CCP2_LowPrioritySet()           (IPR2bits.CCP2IP = 0)
    #endif
#endif

#endif	/* INTERNAL_INTERRUPT_H */

