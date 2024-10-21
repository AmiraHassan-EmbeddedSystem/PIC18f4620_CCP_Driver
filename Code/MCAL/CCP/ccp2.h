/* 
 * File:   ccp2.h
 * Author: ah427
 *
 * Created on 18 ??????, 2024, 01:47 ?
 */

#ifndef CCP2_H
#define	CCP2_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"
#include "ccp_cfg.h"

/* SECTION: Macro Function Declarations */
#define CCP2_SELECT_MODE(_CONFIG)             (CCP2CONbits.CCP2M = _CONFIG)



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

typedef struct{
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp1_mode_variant;
    pin_config_t pin;
    
    #ifdef CCP1_INTERRUPT_FEATURE_ENABLE
        void (*CCP1_InterruptHandler)(void);
        #ifdef INTERRUPT_PRIORITY_LEVELS
            interrupt_priority ccp1_priority;
        #endif
    #endif

    #if CCP1_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
        uint32 PWM_Frequency;
        uint8 timer2_postcaler_value: 4;
        uint8 timer2_prescaler_value:2;
    #endif
}ccp_t;

/* SECTION: Interface Function Declarations */
Std_ReturnType CCP2_Init(const ccp_t *ccp1_obj);
Std_ReturnType CCP2_DeInit(const ccp_t *ccp1_obj);


#if CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_CAPTURE_SELECTED
Std_ReturnType CCP2_Is_CaptureDataReady(uint8 *capture_status);
Std_ReturnType CCP2_CaptureReadValue(uint16 *read_capture);   

#endif

#if CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_COMPARE_SELECTED
Std_ReturnType CCP2_IsCompareComplete(uint8 *compare_status);
Std_ReturnType CCP2_CompleteModeSetValue(uint16 compare_value); 
#endif

#if CCP2_CFG_CHOOSE_MODE ==  CCP_CFG_PWM_MODULE_SELECTED
Std_ReturnType CCP2_PWM_SetDuty(const ccp_t *ccp_obj, const uint8 duty);
Std_ReturnType CCP2_PWM_Start(const ccp_t *ccp_obj);
Std_ReturnType CCP2_PWM_Stop(const ccp_t *ccp_obj);


#endif

#endif	/* CCP2_H */

