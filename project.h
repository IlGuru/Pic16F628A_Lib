/* 
 * File:   project.h
 * Author: sbusnelli
 *
 *      Versione    2.0
 * 
 * Created on 6 luglio 2015, 15.52
 */

#ifndef PROJECT_H
#define	PROJECT_H

#define _XTAL_FREQ      4000000.0
#include <xc.h>

typedef unsigned char   uchar;

unsigned char       v_buffer[10];  //  Buffer generico di 8 byte per tutti gli usi
unsigned short long v_credito;

#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/*
 *  Per inserire i valori nella eeprom del pic non mi serve il normale programma
 * 
 *      Così lo disabilito per abilitare solo la parte relativa alla lettura
 *      dell'array con i caratteri custom per il display lcd ed alla sua 
 *      copia nella eeprom
 */

#define NORMAL_PROG

//------------------------------------------------------------------------------
//  Switch moduli

//#define E_LED
#define E_BUTTON
#define E_I2C
#define E_24C02
//#define E_INTERRUPT
#define E_LCD
#define E_IO
#define E_COGES

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#ifdef E_I2C

    /*  Per il debug tramite oscilloscopio,  utilizzo un pin per segnalare 
     *      l'inizio, la fine di funzioni i2c fondamentali
     *      i bit ACK letti ecc...
     *      Va letto in parallelo con SCL ed SDA
    */

    //#define I2C_DEBUG_BUS
    //#define I2C_DEBUG_START_STOP
    //#define I2C_DEBUG_ACK
    #if defined I2C_DEBUG_BUS | defined I2C_DEBUG_START_STOP | defined I2C_DEBUG_ACK
        #define I2C_DEBUG 
    #endif

#endif


#ifdef E_LCD

    //  -------------------------
    /*  Abilita le funzioni che necessitano di RW=1
     *      Se si può fare a meno di questa, si può salvare un pin di I/O da collegare al display
     *      e si può collegare il pin RW del display fisso a GND.
     */

    #define LCD_READ_FUNCTIONS

#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#if defined E_LCD & defined LCD_READ_FUNCTIONS

    #define E_CUSTOM_CHARSET
    #ifdef E_CUSTOM_CHARSET

        #define CUSTOM_CHARS            5
        #define E_CUSTOM_CHARSET_EURO   '\1'
        #define E_CUSTOM_CHARSET_DOWN   '\2'
        #define E_CUSTOM_CHARSET_UP     '\3'
        #define E_CUSTOM_CHARSET_ENTER  '\4'

        #ifndef NORMAL_PROG

            const unsigned char   a_custom_chars[8*CUSTOM_CHARS] = { 
                0x00000000, 
                0x00000000,
                0x00000000,
                0x00000000,
                0x00000000,
                0x00000000,
                0x00000000,
                0x00000000,

                0b00001110, 
                0b00010001, 
                0b00011100, 
                0b00010000, 
                0b00011100, 
                0b00010001, 
                0b00001110,    
                0b00000000,    

                0b00001110, 
                0b00001010, 
                0b00001010, 
                0b00001010, 
                0b00011011, 
                0b00001010, 
                0b00000100, 
                0b00000000,

                0b00000100, 
                0b00001010, 
                0b00011011, 
                0b00001010, 
                0b00001010, 
                0b00001010, 
                0b00001110, 
                0b00000000,

                0b00000000, 
                0b00000000, 
                0b00000000, 
                0b00000000, 
                0b00011111, 
                0b00010001, 
                0b00011111, 
                0b00000000    
            };

        #endif

    #endif

#endif


#define STORE_BACKLIGHT_SETTING 0x78
            
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#ifdef E_LED & !defined LED_H
    #include "leds.h"
#endif
#ifdef E_BUTTON & !defined BUTTONS_H
    #include "buttons.h"
#endif
#ifdef E_I2C & !defined I2C_H
    #include "i2c.h"
#endif
#ifdef E_24C02 & !defined M24C02_H
    #include "m24c02.h"
#endif
#ifdef E_LCD & !defined LCD1602_H
    #include "lcd1602.h"
#endif
#ifdef E_IO & !defined IO_PINS_H
    #include "io_pins.h"
#endif
#if defined E_COGES & !defined COGES_H
    #include "coges.h"
#endif

#include "main_menu.h"
#include "pic_eeprom.h"



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//  Registri Shadow Porte A e B
//      bitfield definitions

typedef union {
    struct {
        //  RA0 va bene come I/O
        unsigned bit0                   :1;     
        //  RA1 va bene come I/O
        unsigned bit1                   :1;     
        //  RA2 va bene come I/O
        unsigned bit2                   :1;     
        //  RA3 va bene come I/O
        unsigned bit3                   :1;     
        //  RA4 va bene come I/O ma obbligo di pull-up esterno
        unsigned bit4                   :1;     
        //  RA5 SOLO INPUT, non si può usare per il bus
        unsigned bit5                   :1;     
        //  RA6 va bene come I/O
        unsigned bit6                   :1;     
        //  RA7 va bene come I/O
        unsigned bit7                   :1;     
    };
    struct {
        unsigned E                      :1;     //  RA0
        unsigned DB4                    :1;     //  RA1
        unsigned DB5                    :1;     //  RA2
        unsigned DB6                    :1;     //  RA3
        unsigned DB7                    :1;     //  RA4
        unsigned                        :1;     //  RA5
        unsigned RS                     :1;     //  RA6
#ifdef LCD_READ_FUNCTIONS
        unsigned RW                     :1;     //  RA7
#else
        unsigned                        :1;
#endif        
    };
    struct {
        unsigned                        :1;
        unsigned DATA                   :4;
        unsigned                        :3;
    };
} SR_PORTA_t;

typedef union {
    struct {
        //  RB0 va bene come I/O e come INTERRUPT
        unsigned bit0                   :1;     
        //  RB1 va bene come I/O
        unsigned bit1                   :1;     
        //  RB2 va bene come I/O
        unsigned bit2                   :1;     
        //  RB3 va bene come I/O
        unsigned bit3                   :1;     
        //  RB4 va bene come I/O e come INTERRUPT
        unsigned bit4                   :1;     
        //  RB5 va bene come I/O e come INTERRUPT
        unsigned bit5                   :1;     
        //  RB6 va bene come I/O e come INTERRUPT
        unsigned bit6                   :1;     
        //  RB7 va bene come I/O e come INTERRUPT
        unsigned bit7                   :1;     
    };
#ifdef I2C_DEBUG
    struct {
        unsigned                        :1;
        unsigned SCL                    :1;
        unsigned SDA                    :1;
        unsigned DBG                    :1;     //  Attenzione che adesso c'è BACKLIGHT
        unsigned                        :4;
    };
#else
    struct {
        unsigned                        :1; //  RB0
        unsigned                        :1; //  RB1
        unsigned SCL                    :1; //  RB2
        unsigned SDA                    :1; //  RB3
        unsigned BTNUP                  :1; //  RB4
        unsigned BTNDWN                 :1; //  RB5
        unsigned BTNENT                 :1; //  RB6
        unsigned BACKLIGHT              :1; //  RB7
    };
#endif  /* I2C_DEBUG */
    struct {
        unsigned                        :1; //  RB0
        unsigned                        :1; //  RB1
        unsigned BUS                    :2; //  RB2-3
        unsigned BTNS                   :3; //  RB4-5-6
        unsigned                        :1; //  RB7
    };
} SR_PORTB_t;

/*
 *  CUSTOM PORTA   -> 0x05
 *  CUSTOM PORTB   -> 0x06
 */
    #define C_PORTA_ADDR 0x0005
    #define C_PORTB_ADDR 0x0006

    extern volatile unsigned char   C_PORTA @ C_PORTA_ADDR;
    extern volatile unsigned char   C_PORTB @ C_PORTB_ADDR;
    #ifndef _LIB_BUILD
        asm("C_PORTA equ 05h");
        asm("C_PORTB equ 06h");
    #endif
    extern volatile SR_PORTA_t C_PORTAbits @ C_PORTA_ADDR;
    extern volatile SR_PORTB_t C_PORTBbits @ C_PORTB_ADDR;

/*
 *  SHADOW_PORTA   -> 0x6E
 *  SHADOW_PORTB   -> 0x6F
 */
    #define SR_PORTA_ADDR 0x00EE
    #define SR_PORTB_ADDR 0x00EF

    extern volatile unsigned char   SR_PORTA @ SR_PORTA_ADDR;
    extern volatile unsigned char   SR_PORTB @ SR_PORTB_ADDR;
    #ifndef _LIB_BUILD
        asm("SR_PORTA equ 00EEh");
        asm("SR_PORTB equ 00EFh");
    #endif
    extern volatile SR_PORTA_t SR_PORTAbits @ SR_PORTA_ADDR;
    extern volatile SR_PORTB_t SR_PORTBbits @ SR_PORTB_ADDR;

/*
 *  CUSTOM TRISA   -> 0x85
 *  CUSTOM TRISB   -> 0x86
 */
    #define SR_TRISA_ADDR 0x0085
    #define SR_TRISB_ADDR 0x0086

    extern volatile unsigned char   C_TRISA @ SR_TRISA_ADDR;
    extern volatile unsigned char   C_TRISB @ SR_TRISB_ADDR;
    #ifndef _LIB_BUILD
        asm("C_TRISA equ 85h");
        asm("C_TRISB equ 86h");
    #endif
    extern volatile SR_PORTA_t C_TRISAbits @ SR_TRISA_ADDR;
    extern volatile SR_PORTB_t C_TRISBbits @ SR_TRISB_ADDR;

#endif	/* PROJECT_H */

