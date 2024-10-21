/* 
 * File:   mcal_tmr3.h
 * Author: ah427
 *
 * Created on 30 ??????, 2024, 09:51 ?
 */

#ifndef MCAL_TMR3_H
#define	MCAL_TMR3_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"
#include "../INTERRUPT/internal_interrupt.h"

/* SECTION: Macro Declarations */
#define TIMER3_TIMER_MOOD_CFG     0
#define TIMER3_COUNTER_MOOD_CFG   1

#define TIMER3_ASYNC_COUNTER_MOOD_CFG   1
#define TIMER3_SYNC_COUNTER_MOOD_CFG    0

#define TIMER3_OSCILLATOR_ENABLE    0
#define TIMER3_OSCILLATOR_DISABLE   1

#define TIMER3_PRESCALER_DIV_BY_1   0
#define TIMER3_PRESCALER_DIV_BY_2   1
#define TIMER3_PRESCALER_DIV_BY_4   2
#define TIMER3_PRESCALER_DIV_BY_8   3

#define TIMER3_RW_REG_8BIT_MOOD     0
#define TIMER3_RW_REG_16BIT_MOOD     1


/* SECTION: Macro Function Declarations */
#define TIMER3_ENABLE()      (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE()     (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MOOD_ENABLE()   (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MOOD_ENABLE() (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MOOD() (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MOOD() (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_)   (T3CONbits.T3CKPS = _PRESCALER_)

#define TIMER3_RW_REG_8BIT_ENABLE()     (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_ENABLE()     (T3CONbits.RD16 = 1)


/* SECTION: Data Type Declarations */



typedef struct{
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    void (*Timer3_InterruptHandler)(void);
    #ifdef INTERRUPT_PRIORITY_LEVELS 
        interrupt_priority priority;
    #endif
#endif
    uint16 timer3_preload_value;
    uint8 timer3_prescaler_value:2; 
    uint8 timer3_mood:1; // timer || counter
    uint8 timer3_counter_mood:1; // Sync || Async
    uint8 timer3_reg_mood:1; // 8bit || 16bit
    uint8 timer3_reseved:3; 
}Timer3_t;


/* SECTION: Interface Function Declarations */
Std_ReturnType Timer3_Init(const Timer3_t *_tmr);
Std_ReturnType Timer3_DeInit(const Timer3_t *_tmr);
Std_ReturnType Timer3_Read(const Timer3_t *_tmr, uint16 *value);
Std_ReturnType Timer3_Write(const Timer3_t *_tmr, uint16 value);

#endif	/* MCAL_TMR3_H */

