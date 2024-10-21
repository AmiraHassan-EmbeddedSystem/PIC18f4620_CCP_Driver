#include "ccp.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    static void (*CCP1_InterruptHandler)(void) = NULL;
#endif
    
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
    static void (*CCP2_InterruptHandler)(void) = NULL;
#endif
    
static void inline CCP1_Interrupt_Config(const ccp_t *ccp1_obj);
static void inline CCP2_Interrupt_Config(const ccp_t *ccp2_obj);

static Std_ReturnType CCP1_Init(const ccp_t *ccp1_obj);
static Std_ReturnType CCP2_Init(const ccp_t *ccp2_obj);

static void inline CCP_select_timer(const ccp_t *ccp_obj);


Std_ReturnType CCP_Init(const ccp_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            ret |= CCP1_Init(ccp_obj);
            CCP1_Interrupt_Config(ccp_obj);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            ret |= CCP2_Init(ccp_obj);
            CCP2_Interrupt_Config(ccp_obj);
        }
        else{
            ret = E_NOT_OK;
        }
        
        ret |= gpio_pin_initialize(&(ccp_obj->pin)); 
    }
    return ret;
}


Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            CCP1_SELECT_MODE(CCP_MODULE_DISABLLE);
            #ifdef CCP1_INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
            #endif
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLLE);
            #ifdef CCP2_INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
            #endif
        }
        
        ret = E_OK;
    }
    return ret;
}



#if CCP_CFG_CHOOSE_MODE ==  CCP1_CFG_CAPTURE_SELECTED || CCP_CFG_CHOOSE_MODE ==  CCP2_CFG_CAPTURE_SELECTED
Std_ReturnType CCP_Is_CaptureDataReady(const ccp_t *ccp_obj, uint8 *capture_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj || NULL == capture_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *capture_status = CCP_CAPTURE_NOT_READY;
            }
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}


Std_ReturnType CCP_CompleteModeSetValue(const ccp_t *ccp_obj, uint16 compare_value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        ccp_reg_t capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
        capture_temp_value.ccpr_16bit = compare_value;
        
        if(CCP1_INST == ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;
        }
        ret = E_OK;
    }
    return ret;
}
#endif


#if CCP1_CFG_CHOOSE_MODE ==  CCP1_CFG_COMPARE_SELECTED
Std_ReturnType CCP1_IsCompareComplete(uint8 *compare_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == compare_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            *compare_status = CCP_COMPARE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *compare_status = CCP_COMPARE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}


Std_ReturnType CCP1_CompleteModeSetValue(uint16 compare_value){
    Std_ReturnType ret = E_NOT_OK;
    ccp_reg_t capture_temp_value = {.ccpr_low = 0, .ccpr_high = 0};
    capture_temp_value.ccpr_16bit = compare_value;
    CCPR1L = capture_temp_value.ccpr_low;
    CCPR1H = capture_temp_value.ccpr_high;
    
    ret = E_OK;
    return ret;
}

#endif

#if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED || CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
Std_ReturnType CCP_PWM_SetDuty(const ccp_t *ccp_obj, uint8 duty){
    Std_ReturnType ret = E_NOT_OK;
    uint16 duty_temp = 0;
    duty_temp = (uint16)((PR2 + 1) * (duty / 100.0) * 4.0);
    if(CCP1_INST == ccp_obj->ccp_inst){
        CCP1CONbits.DC1B = (uint8)(duty_temp & 0x0003);
        CCPR1L = (uint8)(duty_temp >> 2);
    }
    else if(CCP2_INST == ccp_obj->ccp_inst){
        CCP2CONbits.DC2B = (uint8)(duty_temp & 0x0003);
        CCPR2L = (uint8)(duty_temp >> 2);
    }
    else{
        /*Nothing*/
    }
    
    ret = E_OK;
    return ret;
}

Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj){
     Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == ccp_obj->ccp_inst){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLLE);
        }
        else if(CCP2_INST == ccp_obj->ccp_inst){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLLE);
        }
        else{
            /*Nothing*/
        }
            
        ret = E_OK;
    }
    return ret;
}
#endif

static Std_ReturnType CCP1_Init(const ccp_t *ccp1_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp1_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP_CAPTURE_MODE_SELECTED == ccp1_obj->ccp_mode){
            CCP1_SELECT_MODE(CCP_MODULE_DISABLLE);
            switch(ccp1_obj->ccp_mode_variant){
                case CCP_CAPTURE_1_FALLING:
                    CCP1_SELECT_MODE(CCP_CAPTURE_1_FALLING);
                    break;
                case CCP_CAPTURE_1_RISING:
                    CCP1_SELECT_MODE(CCP_CAPTURE_1_RISING);
                    break;
                case CCP_CAPTURE_4_RISING:
                    CCP1_SELECT_MODE(CCP_CAPTURE_4_RISING);
                    break;
                case CCP_CAPTURE_16_RISING:
                    CCP1_SELECT_MODE(CCP_CAPTURE_16_RISING);
                    break;
                default:
                    ret = E_NOT_OK;
            }
            CCP_select_timer(ccp1_obj);
        }
        else if(CCP_COMPARE_MODE_SELECTED == ccp1_obj->ccp_mode){
            switch(ccp1_obj->ccp_mode_variant){
                case CCP_COMPARE_TOGGLE_OUTPUT:
                    CCP1_SELECT_MODE(CCP_COMPARE_TOGGLE_OUTPUT);
                    break;
                case CCP_COMPARE_INITIALIZE_PIN_LOW:
                    CCP1_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_LOW);
                    break;
                case CCP_COMPARE_INITIALIZE_PIN_HIGH:
                    CCP1_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_HIGH);
                    break;
                case CCP_COMPARE_GENERATE_SW_INTERRUPT:
                    CCP1_SELECT_MODE(CCP_COMPARE_GENERATE_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_TRIGGER_SPECIAL_EVENT:
                    CCP1_SELECT_MODE(CCP_COMPARE_TRIGGER_SPECIAL_EVENT);
                    break;
                default:
                    ret = E_NOT_OK;
            }    
            CCP_select_timer(ccp1_obj);
        }
        else if(CCP_PWM_MODE_SELECTED == ccp1_obj->ccp_mode){
            #if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
            PR2 = (uint8)((_XTAL_FREQ / ( ccp1_obj->PWM_Frequency * 4.0 * 
                                    ccp1_obj->timer2_prescaler_value * ccp1_obj->timer2_postcaler_value)) -1);
            CCP1_SELECT_MODE(CCP_PWM_MODE);
            
            #endif
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType CCP2_Init(const ccp_t *ccp2_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == ccp2_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP_CAPTURE_MODE_SELECTED == ccp2_obj->ccp_mode){
            CCP2_SELECT_MODE(CCP_MODULE_DISABLLE);
            switch(ccp2_obj->ccp_mode_variant){
                case CCP_CAPTURE_1_FALLING:
                    CCP2_SELECT_MODE(CCP_CAPTURE_1_FALLING);
                    break;
                case CCP_CAPTURE_1_RISING:
                    CCP2_SELECT_MODE(CCP_CAPTURE_1_RISING);
                    break;
                case CCP_CAPTURE_4_RISING:
                    CCP2_SELECT_MODE(CCP_CAPTURE_4_RISING);
                    break;
                case CCP_CAPTURE_16_RISING:
                    CCP2_SELECT_MODE(CCP_CAPTURE_16_RISING);
                    break;
                default:
                    ret = E_NOT_OK;
            }
        } 
        else if(CCP_COMPARE_MODE_SELECTED == ccp2_obj->ccp_mode){
            switch(ccp2_obj->ccp_mode_variant){
                case CCP_COMPARE_TOGGLE_OUTPUT:
                    CCP2_SELECT_MODE(CCP_COMPARE_TOGGLE_OUTPUT);
                    break;
                case CCP_COMPARE_INITIALIZE_PIN_LOW:
                    CCP2_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_LOW);
                    break;
                case CCP_COMPARE_INITIALIZE_PIN_HIGH:
                    CCP2_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_HIGH);
                    break;
                case CCP_COMPARE_GENERATE_SW_INTERRUPT:
                    CCP2_SELECT_MODE(CCP_COMPARE_GENERATE_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_TRIGGER_SPECIAL_EVENT:
                    CCP2_SELECT_MODE(CCP_COMPARE_TRIGGER_SPECIAL_EVENT);
                    break;
                default:
                    ret = E_NOT_OK;
            } 
            CCP_select_timer(ccp2_obj);
        }
        else if(CCP_PWM_MODE_SELECTED == ccp2_obj->ccp_mode){
            #if CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
            PR2 = (uint8)((_XTAL_FREQ / ( ccp2_obj->PWM_Frequency * 4.0 * 
                                    ccp2_obj->timer2_prescaler_value * ccp2_obj->timer2_postcaler_value)) -1);
            CCP2_SELECT_MODE(CCP_PWM_MODE);
            CCP_select_timer(ccp2_obj);
            #endif
        }
        else{
            ret = E_NOT_OK;
        }
    }
    return ret;
}


static void inline CCP1_Interrupt_Config(const ccp_t *ccp1_obj)
{
    #ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
        CCP1_InterruptHandler = ccp1_obj->CCP1_InterruptHandler;
        #ifdef INTERRUPT_PRIORITY_LEVELS
            Interrupt_priorityLevelEnable();
            if(HIGH_PRIORITY == ccp1_obj->ccp1_priority){
                Interrupt_HighPriorityEnable();
                CCP1_HighPrioritySet();
            }
            else if(LOW_PRIORITY == ccp1_obj->ccp1_priority){
                Interrupt_LowPriorityEnable();
                CCP1_LowPrioritySet();
            }
        #else
            Interrupt_globalInterruptEnable();
            Interrupt_prepheralInterruptEnable();
        #endif
    #endif       
}

static void inline CCP2_Interrupt_Config(const ccp_t *ccp2_obj)
{
    #ifdef CCP2_INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
        CCP2_InterruptHandler = ccp2_obj->CCP2_InterruptHandler;
        #ifdef INTERRUPT_PRIORITY_LEVELS
            Interrupt_priorityLevelEnable();
            if(HIGH_PRIORITY == ccp2_obj->ccp2_priority){
                Interrupt_HighPriorityEnable();
                CCP2_HighPrioritySet();
            }
            else if(LOW_PRIORITY == ccp2_obj->ccp2_priority){
                Interrupt_LowPriorityEnable();
                CCP2_LowPrioritySet();
            }
        #else
            Interrupt_globalInterruptEnable();
            Interrupt_prepheralInterruptEnable();
        #endif
    #endif      
}        

static void inline CCP_select_timer(const ccp_t *ccp_obj){
    if(CCP1_CCP2_TIMER3 == ccp_obj->ccp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp_obj->ccp_timer_select){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == ccp_obj->ccp_timer_select){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{
        /*Nothing*/
    }
}


void ISR_CCP1(void){
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /*Nothing*/}
#endif
}

void ISR_CCP2(void){
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /*Nothing*/}
#endif
}
