#include "buttons.h"

//    void btn_SendSignals() {
//        PORTA = SR_PORTA;
//    }
//    void btn_RecvSignals() {
//        SR_PORTA = PORTA;
//    }

    void btn_SendSignals() {
        PORTB = SR_PORTB;
    }
    void btn_RecvSignals() {
        SR_PORTB = PORTB;
    }

//    void btn_SendSignals() {
//        PORTA = SR_PORTA;
//        PORTB = SR_PORTB;
//    }
//    void btn_RecvSignals() {
//        SR_PORTA = PORTA;
//        SR_PORTB = PORTB;
//    }

    void    btn_init()  {

//        BTN_BTNS_HI;
//        PORTB = BTN_BTNS_shadow;
//        BTN_DTCH_BTNS;
////        BTN_DTCH_INT;

        BTN_BTNS_HI;
        PORTB = BTN_BTNS_shadow;
        BTN_DTCH_BTNS;
//        BTN_DTCH_INT;
                
    }
    
    unsigned char   wait_button() {
        unsigned char   v_pulsanti = BTN_ALL_FREE;
        
        while ( BTN_BTNS == BTN_ALL_FREE ) {
            btn_pause();
        };

        btn_pause();
        v_pulsanti = BTN_BTNS;
        
//        do {
//            btn_pause();
//        } while ( BTN_BTNS != BTN_ALL_FREE );

        return v_pulsanti;
    }