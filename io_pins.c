#include "io_pins.h"

void    iopins_SendSignals() {
//    C_PORTA = SR_PORTA;
    C_PORTB = SR_PORTB;
}

void    iopins_init() {
    
    IO_LO_BACKLIGHT;
    iopins_SendSignals();
    IO_ATCH_BACKLIGHT;
    
    iopins_pause();
    
}

void iopins_set_backlight( unsigned char v_val ) {

    IO_BACKLIGHT_shadow = v_val;
    iopins_SendSignals();
    IO_BACKLIGHT_TRIS   = v_val;

}

