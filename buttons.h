/* 
 * File:   buttons.h
 * Author: Stefano
 *
 *      VERSIONE    2.00
 *  
 *      Questa libreria gestisce i bottoni collegati direttamente ai pin di input tramite resistenze di PULL UP
 *      L'interrupt viene gestito tramite una resistenza di PULL UP e vari diodi collegati con anodo al pin di INT
 *          e catodo collegato al pulsante.
 *          VDD------               VDD------               VDD------
 *                  |                       |                       |
 *                  |                       |                       |
 *                  R0                      R1                      RI
 *                  |                       |                       |
 *                  |   D0                  |   D1                  |
 *          BTN_ENT --+--|<|--INT     BTN_DWN --+--|<|--INT     INT------
 *                  |                       |
 *                  |                       |                       
 *                  \  SW0                  \  SW1
 *                   \                       \
 *                  |                       |
 *                  |                       |                       
 *          VSS------               VSS------
 * 
 *      Per usare gli interrupt tramite la porta B, su questa non possono essere
 *          usati i pin da RB4 a RB7 per altri dispositivi.
 * 
 * Created on 3 luglio 2015, 13.53
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

    #include "project.h"

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

    void btn_SendSignals();
    void btn_RecvSignals();

//  -------------------------------------------------------------------------------------------
    
    #define BTN_ENT             C_PORTBbits.BTNENT
    #define BTN_DWN             C_PORTBbits.BTNDWN
    #define BTN_UP              C_PORTBbits.BTNUP

    #define BTN_BTNS            C_PORTBbits.BTNS

    #define BTN_ENT_shadow      SR_PORTBbits.BTNENT
    #define BTN_DWN_shadow      SR_PORTBbits.BTNDWN
    #define BTN_UP_shadow       SR_PORTBbits.BTNUP
    #define BTN_BTNS_shadow     SR_PORTBbits.BTNS

    #define BTN_BTNS_HI         BTN_BTNS_shadow=0b111
    #define BTN_BTNS_LO         BTN_BTNS_shadow=0b000
    
    #define BTN_ENT_TRIS        C_TRISBbits.BTNENT
    #define BTN_DWN_TRIS        C_TRISBbits.BTNDWN
    #define BTN_UP_TRIS         C_TRISBbits.BTNUP
    #define BTN_BTNS_TRIS       C_TRISBbits.BTNS

//    #define BTN_INT_TRIS        C_TRISBbits.BTN_INTR

    //  -----------------------------------------------------------------------
    
    #define BTN_DTCH_BTNS       BTN_BTNS_TRIS=0b111
    #define BTN_DTCH_INT        BTN_INT_TRIS=1

//------------------------------------------------------------------------------

    /*  Questi valori vanno impostati sulla configurazione di SR_A_BTNbits.BTNS
     *      Il pin premuto è quello che viene portato a 0 tramite lo switch.
     *      Con questa configurazione circuitale sono possibili combinazioni di pulsanti premuti
     */
#define BTN_ALL_FREE    0b111
#define BTN_ENT_PRESS   0b011
#define BTN_DWN_PRESS   0b101
#define BTN__UP_PRESS   0b110
#define BTN__10_PRESS   0b001
#define BTN__21_PRESS   0b100
#define BTN__20_PRESS   0b010
#define BTN__10_PRESS   0b000

#define BTN_ENT_PRESSED 0b100
#define BTN_DWN_PRESSED 0b010
#define BTN__UP_PRESSED 0b001

    
//------------------------------------------------------------------------------

    //  Funzioni alto livello
    
    #define btn_pause()     __delay_ms(100)

    void            btn_init();
    unsigned char   wait_button();
    
#endif	/* BUTTONS_H */

