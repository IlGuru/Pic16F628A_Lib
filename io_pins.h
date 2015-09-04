/* 
 * File:   io.h
 * Author: Stefano
 *      
 * 
 *      Versione    2.0
 * 
 * 
 * Created on 6 luglio 2015, 22.29
 */

#ifndef IO_PINS_H
#define	IO_PINS_H

#include "project.h"

//  -------------------------------------------------------------------------------------------

    #define iopins_pause()     __delay_ms(250)

//------------------------------------------------------------------------------

    void    iopins_SendSignals();

//  -------------------------------------------------------------------------------------------

    #define IO_BACKLIGHT            C_PORTBbits.BACKLIGHT

    #define IO_BACKLIGHT_shadow     SR_PORTBbits.BACKLIGHT

    #define IO_BACKLIGHT_TRIS       C_TRISBbits.BACKLIGHT

    #define IO_ATCH_BACKLIGHT       IO_BACKLIGHT_TRIS=0
    #define IO_DTCH_BACKLIGHT       IO_BACKLIGHT_TRIS=1
    #define IO_HI_BACKLIGHT         IO_BACKLIGHT_shadow=1
    #define IO_LO_BACKLIGHT         IO_BACKLIGHT_shadow=0
    #define IO_IS_HI_BACKLIGHT      IO_BACKLIGHT_TRIS==1
    #define IO_IS_LO_BACKLIGHT      IO_BACKLIGHT_TRIS==0

//  ---------------------------------------------------------------------------------
//  ---------------------------------------------------------------------------------
    
    void    iopins_SendSignals();
    void    iopins_init();
    
    void    iopins_set_backlight( unsigned char v_val );
    
//  ---------------------------------------------------------------------------------
//  ---------------------------------------------------------------------------------


#endif	/* IO_PINS_H */

