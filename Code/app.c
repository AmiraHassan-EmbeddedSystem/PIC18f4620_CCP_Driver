/*
 * File:   app.c
 * Author: ah427
 *
 * Created on 01 ??????, 2024, 04:07 ?
 */


#include "app.h"


void ccp2_interruptHandler(void);

ccp_t ccp2_obj = {
    .CCP2_InterruptHandler = ccp2_interruptHandler,
    .ccp_inst = CCP2_INST,
    .ccp_mode = CCP_COMPARE_MODE_SELECTED,
    .ccp_mode_variant = CCP_COMPARE_INITIALIZE_PIN_LOW,
    .pin.Direction = GPIO_OUTPUT,
    .pin.Port = GPIO_PORTC,
    .pin.Pin = GPIO_PIN1,
    .ccp_timer_select = CCP1_CCP2_TIMER3,
};

Timer3_t tmr3;
volatile uint8 flag_ccp_interrupt = 0;


int main() {
    

    CCP_CompleteModeSetValue(&ccp2_obj, 37500);  
    CCP_Init(&ccp2_obj);
    
    tmr3.Timer3_InterruptHandler = NULL;
    tmr3.timer3_mood =  TIMER3_TIMER_MOOD_CFG;
    tmr3.timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1;
    tmr3.timer3_preload_value = 0;
    tmr3.timer3_reg_mood = TIMER3_RW_REG_16BIT_MOOD;
            
            
    Timer3_Init(&tmr3);
    
    while(1){
        
    }
    return 0;
}

void app_intialize(void)
{

}   

void ccp2_interruptHandler(void){
    Timer3_Write(&tmr3, 0);
    flag_ccp_interrupt++;
    if(1 == flag_ccp_interrupt){
        CCP_CompleteModeSetValue(&ccp2_obj, 37500);
        CCP2_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_HIGH);
    }
    else if(2 == flag_ccp_interrupt){
        CCP_CompleteModeSetValue(&ccp2_obj, 12500);
        CCP2_SELECT_MODE(CCP_COMPARE_INITIALIZE_PIN_LOW);
        flag_ccp_interrupt = 0;
    }
}






















// ----------- Capture Mood --------------
//uint16 second_capture = 0;
//volatile uint8 ccp1_second_capture_flag = 0;
//
//volatile uint32 timer3_overflow = 0, total_period_microSecond = 0;
//uint32 freq = 0;
//
//void ccp1_interruptHandler(void);
//void timer3_interruptHandler(void);
//
//ccp_t ccp1_obj = {
//    .CCP1_InterruptHandler = ccp1_interruptHandler,
//    .ccp_inst = CCP1_INST,
//    .ccp_mode = CCP_CAPTURE_MODE_SELECTED,
//    .ccp_mode_variant = CCP_CAPTURE_1_RISING,
//    .pin.Direction = GPIO_INPUT,
//    .pin.Port = GPIO_PORTC,
//    .pin.Pin = GPIO_PIN2,
//    .ccp_capture_timer_select = CCP1_CCP2_TIMER3,
//};
//
//
//Timer3_t tmr3 = {
//    .Timer3_InterruptHandler = timer3_interruptHandler,
//    .timer3_mood =  TIMER3_TIMER_MOOD_CFG,
//    .timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1,
//    .timer3_preload_value = 0,
//    .timer3_reg_mood = TIMER3_RW_REG_8BIT_MOOD,
//};
//
//
//
//void app_intialize(void);
//int main() {
//    
//    app_intialize();
//    while(1)
//    {
//        if(ccp1_second_capture_flag == 2){
//            total_period_microSecond = (timer3_overflow * 65535) + second_capture;
//            freq = (uint32)(1 / (total_period_microSecond / 1000000.0));
//            ccp1_second_capture_flag = 0;
//        }
//    }
//    return 0;
//}
//
//void app_intialize(void)
//{
//    CCP_Init(&ccp1_obj);
//    Timer3_Init(&tmr3);
//}   
//
//void ccp1_interruptHandler(void){
//    static uint8 ccp1_interrupt_flag = 0;
//    
//    ccp1_interrupt_flag++;
//    ccp1_second_capture_flag++;
//    
//    if(ccp1_interrupt_flag == 1){
//        Timer3_Write(&tmr3, 0);
//    }
//    else if(ccp1_interrupt_flag == 2){
//        timer3_overflow = 0;
//        ccp1_interrupt_flag = 0;
//        CCP1_CaptureReadValue(&second_capture);
//    }
//    else{
//        
//    }
//}
//
//void timer3_interruptHandler(void){
//    timer3_overflow++;
//}