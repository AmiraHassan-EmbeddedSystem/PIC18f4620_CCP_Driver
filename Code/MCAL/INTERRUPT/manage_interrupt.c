#include "manage_interrupt.h"

#ifdef INTERRUPT_PRIORITY_LEVELS
void __interrupt() InterruptManagerHigh(void)
{
//    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
//        ISR_TMR0();
//    }
//    
//    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
//        ISR_TMR1();
//    }
//    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        ISR_TMR2();
    }

    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) &&(INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        ISR_TMR3();
    }
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
}
#else
//void __interrupt(low_priority) InterruptManagerLow(void)
//{  
////    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
////        ISR_TMR0();
////    }
////    
////    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
////        ISR_TMR1();
////    }
////    
//    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
//        ISR_TMR2();
//    }
//    
//    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) &&(INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
//        ISR_TMR3();
//    }
//    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) &&(INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
//        CCP1_ISR();
//    }
//    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
//        CCP2_ISR();
//    }
//}
//
//#else

void __interrupt() InterruptManager(void)
{   
//    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) &&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
//        ISR_TMR0();
//    }
//    
//    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
//        ISR_TMR1();
//    }
//    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) &&(INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        ISR_TMR2();
    }
    
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) &&(INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        ISR_TMR3();
    }
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        ISR_CCP1();
    }
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        ISR_CCP2();
    }
}
#endif
