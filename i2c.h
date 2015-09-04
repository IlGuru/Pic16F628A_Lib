/* 
 * File:   i2c.h
 * Author: sbusnelli
 *
 * Created on 2 aprile 2014, 18.28
 *
 *      VERSIONE    2.00
 *  
 *      Ho rimosso molte delle funzioni di basso livello includendo il codice nelle funzioni che le utilizzano
 *          Tutto ciò per ridurre le chiamate ed utilizzare di meno la Stack del Pic
 *
 *      La libreria i2c è testata e funzionante.
 *
 *      Tra diverse letture e scritture di uno slave, può essere necessario una pausa,
 *          per questo c'è la funzione i2c_Pause()
 *
 *      Altre due funzioni di pausa sono
 *              i2c_Delay()
 *              i2c_DelayAck()
 *          entrambe impostate ad .5 ms. Ho testato con valori inferiori, ma a volte non funziona
 *          Con queste impostazioni:
 *              i2c_read_bit_ack    impiega 3*i2c_DelayAck  = 1.5 ms
 *              i2c_send_bit0       impiega 3*i2c_Delay     = 1.5 ms
 *              i2c_send_bit0       impiega 3*i2c_Delay     = 1.5 ms
 *              i2c_send_start      impiega 3*i2c_Delay     = 1.5 ms
 *              i2c_send_stop       impiega 3*i2c_Delay     = 1.5 ms
 *
 */

#ifndef I2C_H
#define	I2C_H

#include "project.h"

//  -------------------------------------------------------------------------------------------

    #define i2c_Pause()     __delay_ms(5)
    #define i2c_Delay()     __delay_us(500)
    #define i2c_DelayAck()  __delay_us(500)

//------------------------------------------------------------------------------

//    #define i2c_SendSignals()   PORTA = SR_PORTA
    #define i2c_SendSignals()   PORTB = SR_PORTB

//  -------------------------------------------------------------------------------------------

    #define I2C_SCL         C_PORTBbits.SCL
    #define I2C_SDA         C_PORTBbits.SDA
#ifdef I2C_DEBUG
    #define I2C_DBG         PORTBbits.RB3
#endif

    #define I2C_SCLshadow   SR_PORTBbits.SCL
    #define I2C_SDAshadow   SR_PORTBbits.SDA
#ifdef I2C_DEBUG
    #define I2C_DBGshadow   SR_PORTBbits.DBG
#endif
    #define I2C_BUSshadow   SR_PORTBbits.BUS
    #define I2C_SCL_TRIS    C_TRISBbits.SCL
    #define I2C_SDA_TRIS    C_TRISBbits.SDA
#ifdef I2C_DEBUG
    #define I2C_DBG_TRIS    C_TRISBbits.DBG
#endif
    #define I2C_BUS_TRIS    C_TRISBbits.BUS

/*
    #define I2C_IS_SDA_DTCH    ( I2C_SDA_TRIS==1 )
    #define I2C_IS_SDA_ATCH    ( I2C_SDA_TRIS==0 )
    #define I2C_IS_SDA_ON      ( I2C_SDAshadow==1 )
    #define I2C_IS_SDA_OFF     ( I2C_SDAshadow==0 )

    #define I2C_IS_SCL_DTCH    ( I2C_SCL_TRIS==1 )
    #define I2C_IS_SCL_ATCH    ( I2C_SCL_TRIS==0 )
    #define I2C_IS_SCL_ON      ( I2C_SCLshadow==1 )
    #define I2C_IS_SCL_OFF     ( I2C_SCLshadow==0 )
*/

    #define I2C_ATCH_BUS    I2C_BUS_TRIS=0
    #define I2C_DTCH_BUS    I2C_BUS_TRIS=3
    #define I2C_ACK_BUS     I2C_BUS_TRIS=2     // SDA secondo bit va input, SCL primo bit rimane output (2)
    #define I2C_HI_BUS      I2C_BUSshadow=3
    #define I2C_LO_BUS      I2C_BUSshadow=0

    #define I2C_ATCH_SDA    I2C_SDA_TRIS=0
    #define I2C_DTCH_SDA    I2C_SDA_TRIS=1
    #define I2C_HI_SDA      I2C_SDAshadow=1
    #define I2C_LO_SDA      I2C_SDAshadow=0

    #define I2C_ATCH_SCL    I2C_SCL_TRIS=0
    #define I2C_DTCH_SCL    I2C_SCL_TRIS=1
    #define I2C_HI_SCL      I2C_SCLshadow=1
    #define I2C_LO_SCL      I2C_SCLshadow=0

#ifdef I2C_DEBUG
    #define I2C_ATCH_DBG    I2C_DBG_TRIS=0
    #define I2C_DTCH_DBG    I2C_DBG_TRIS=1
    #define I2C_HI_DBG      I2C_DBGshadow=1
    #define I2C_LO_DBG      I2C_DBGshadow=0
#endif

//  ---------------------------------------------------------------------------------
//  ---------------------------------------------------------------------------------
    
    //  ---------------------------------------------------------------------------------
    //  Inizializzazione

    //  i2c
    #define i2c()   i2c_Detatch()

    //  ---------------------------------------------------------------------------------
    //  Gestione Bus I2C

    void i2c_Detatch();

    //  ---------------------------------------------------------------------------------
    //  Comandi I2C

    void i2c_send_start();

    void i2c_send_stop();

    void i2c_send_bit0( unsigned char v_bit );

    void i2c_send_bit1( unsigned char v_byte, unsigned char v_pos );

    #define i2c_send_ack()      i2c_send_bit0( 0 )
    #define i2c_send_nack()     i2c_send_bit0( 1 )

    unsigned char i2c_read_bit_ack();
    
//  ---------------------------------------------------------------------------------
//  ---------------------------------------------------------------------------------

#endif	/* I2C_H */

