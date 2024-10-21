/* 
 * File:   interrupt_gen_cfg.h
 * Author: Amira Hassan
 *
 * Created on  19 / 9 / 2024, 6:33 am
 * 
 * Description: This file contains the general configuration macros for enabling
 *              and managing various interrupt features in the project. It allows 
 *              the user to configure interrupt priorities, ADC interrupt handling.
 *  
 */ 

#ifndef INTERRUPT_GEN_CFG_H
#define	INTERRUPT_GEN_CFG_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"

/* SECTION: Macro Declarations */

//#define INTERRUPT_PRIORITY_LEVELS                        
//#define TIMER0_INTERRUPT_FEATURE_ENABLE
//#define TIMER1_INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE




#endif	/* INTERRUPT_GEN_CFG_H */

