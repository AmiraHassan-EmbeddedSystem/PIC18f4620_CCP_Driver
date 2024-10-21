#include "mcal_tmr3.h"

#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
    static void (*Tmr3_InterruptHandler)(void) = NULL;
#endif
    
uint16 tmr3_preload_data = 0;

static inline void timer3_mood_select(const Timer3_t *_tmr);

Std_ReturnType Timer3_Init(const Timer3_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_DISABLE();
        TIMER3_PRESCALER_SELECT(_tmr->timer3_prescaler_value);
        timer3_mood_select(_tmr);
        TMR3H = _tmr->timer3_preload_value >> 8;
        TMR3L = (uint8)(_tmr->timer3_preload_value); 
        tmr3_preload_data = _tmr->timer3_preload_value;
        
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        Tmr3_InterruptHandler = _tmr->Timer3_InterruptHandler;
#ifdef INTERRUPT_PRIORITY_LEVELS
        Interrupt_priorityLevelEnable();
        if(HIGH_PRIORITY == _tmr->priority){
            Interrupt_HighPriorityEnable();
            TIMER3_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == _tmr->priority){
            Interrupt_LowPriorityEnable();
            TIMER3_INTERRUPT_LOW_PRIORITY();
        }
        else{
            /*Nothing*/
        }
#else
        Interrupt_globalInterruptEnable();
        Interrupt_prepheralInterruptEnable();
#endif   
#endif
        
        TIMER3_ENABLE();
        ret = E_OK; 
    }
    return ret;
}



Std_ReturnType Timer3_DeInit(const Timer3_t *_tmr)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK; 
        TIMER3_DISABLE();
        #ifdef TIMER3_INTERRUPT_FEATURE_ENABLE
            TIMER3_INTERRUPT_DISABLE();
        #endif
    }
    return ret;
}



Std_ReturnType Timer3_Read(const Timer3_t *_tmr, uint16 *value)
{
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _tmr) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        uint8 tmr_low = 0, tmr_high = 0;
        tmr_low = TMR0L;
        tmr_high = TMR0H;
        *value = (uint16)((tmr_high << 8) + (tmr_low));
        ret = E_OK; 
    }
    return ret;
}


Std_ReturnType Timer3_Write(const Timer3_t *_tmr, uint16 value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _tmr){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (value) >> 8;
        TMR3L = (uint8)(value); 
        ret = E_OK; 
    }
    return ret;
}




static inline void timer3_mood_select(const Timer3_t *_tmr)
{
    if(TIMER3_TIMER_MOOD_CFG == _tmr->timer3_mood){
        TIMER3_TIMER_MOOD_ENABLE();
        }
    else if(TIMER3_COUNTER_MOOD_CFG == _tmr->timer3_mood){
        TIMER3_COUNTER_MOOD_ENABLE();
        if(TIMER3_ASYNC_COUNTER_MOOD_CFG == _tmr->timer3_counter_mood){
            TIMER3_ASYNC_COUNTER_MOOD();
        }
        else if(TIMER3_SYNC_COUNTER_MOOD_CFG == _tmr->timer3_counter_mood){
            TIMER3_SYNC_COUNTER_MOOD();
        }
        else{
            /*Nothing*/
        }
    }
    else{
        /*Nothing*/
    }
}
   
void ISR_TMR3(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = (tmr3_preload_data) >> 8;
    TMR3L = (uint8)(tmr3_preload_data);
    if(Tmr3_InterruptHandler){
        Tmr3_InterruptHandler();
    }
}
