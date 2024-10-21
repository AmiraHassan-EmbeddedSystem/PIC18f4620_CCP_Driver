/* 
 * File:   ccp1.h
 * Author: ah427
 *
 * Created on 01 ??????, 2024, 03:12 ?
 */

#ifndef CCP1_H
#define	CCP1_H

/* SECTION: Include */
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ccp_cfg.h"
#include "../INTERRUPT/internal_interrupt.h"

/* SECTION: Macro Declarations */
#define CCP_MODULE_DISABLLE                        ((uint8)0x00)
#define CCP_CAPTURE_1_FALLING                      ((uint8)0x04)
#define CCP_CAPTURE_1_RISING                       ((uint8)0x05)
#define CCP_CAPTURE_4_RISING                       ((uint8)0x06)
#define CCP_CAPTURE_16_RISING                      ((uint8)0x07)
#define CCP_COMPARE_TOGGLE_OUTPUT                  ((uint8)0x02)
#define CCP_COMPARE_INITIALIZE_PIN_HIGH             ((uint8)0x08)
#define CCP_COMPARE_INITIALIZE_PIN_LOW              ((uint8)0x09) 
#define CCP_COMPARE_GENERATE_SW_INTERRUPT          ((uint8)0x0A) 
#define CCP_COMPARE_TRIGGER_SPECIAL_EVENT          ((uint8)0x0B)
#define CCP_PWM_MODE                               ((uint8)0x0C)

#define CCP_CAPTURE_READY                          0x01
#define CCP_CAPTURE_NOT_READY                      0x00

#define CCP_COMPARE_READY                          0x01
#define CCP_COMPARE_NOT_READY                      0x00

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        2
#define CCP_TIMER2_PRESCALER_DIV_BY_16       3


/* SECTION: Macro Function Declarations */
#define CCP1_SELECT_MODE(_CONFIG)                   (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SELECT_MODE(_CONFIG)                   (CCP2CONbits.CCP2M = _CONFIG)



/* SECTION: Data Type Declarations */
typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED,
}ccp_mode_t;

/*
  @Summary      Defines the values to convert from 16bit to two 8 bit and vice versa
  @Description  Used to get two 8 bit values from 16bit also two 8 bit value are combine to get 16bit.
*/
typedef union{
    struct{
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16bit;
    };
}ccp_reg_t;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST,
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3,        
}ccp_timer_select_t;

typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    pin_config_t pin;
    
#if CCP1_CFG_CHOOSE_MODE == CCP_CFG_CAPTURE_SELECTED || CCP2_CFG_CHOOSE_MODE == CCP_CFG_CAPTURE_SELECTED || CCP1_CFG_CHOOSE_MODE == CCP_CFG_COMPARE_SELECTED || CCP2_CFG_CHOOSE_MODE == CCP_CFG_COMPARE_SELECTED
    uint8 ccp_mode_variant;
    ccp_timer_select_t ccp_timer_select;
#endif
    
    #ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        void (*CCP1_InterruptHandler)(void);
        #ifdef INTERRUPT_PRIORITY_LEVELS
            interrupt_priority ccp1_priority;
        #endif
    #endif

    #ifdef CCP2_INTERRUPT_FEATURE_ENABLE
        void (*CCP2_InterruptHandler)(void);
        #ifdef INTERRUPT_PRIORITY_LEVELS
            interrupt_priority ccp2_priority;
        #endif
    #endif

    #if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED || CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
        uint32 PWM_Frequency;
        uint8 timer2_postcaler_value: 4;
        uint8 timer2_prescaler_value:2;
    #endif

    
 
}ccp_t;


/* SECTION: Interface Function Declarations */
Std_ReturnType CCP_Init(const ccp_t *ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t *ccp_obj);


#if CCP1_CFG_CHOOSE_MODE ==  CCP1_CFG_CAPTURE_SELECTED || CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_CAPTURE_SELECTED
Std_ReturnType CCP1_Is_CaptureDataReady(uint8 *capture_status);
Std_ReturnType CCP1_CaptureReadValue(uint16 *read_capture);   

#endif

#if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_COMPARE_SELECTED || CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_COMPARE_SELECTED
Std_ReturnType CCP_Is_CaptureDataReady(const ccp_t *ccp_obj, uint8 *capture_status);
Std_ReturnType CCP_CompleteModeSetValue(const ccp_t *ccp_obj, uint16 compare_value); 
#endif

#if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED || CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
Std_ReturnType CCP_PWM_SetDuty(const ccp_t *ccp_obj, const uint8 duty);
Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj);


#endif



#endif	/* CCP1_H */

