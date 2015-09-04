/* 
 * File:   24c02.h
 * Author: sbusnelli
 *
 *      Versione    1.3
 * 
 *      Implementa tutte le funzioni di lettura e scrittura.
 *      Gli errori sono gestiti
 *      Gli errori possono essere visualizzati tramite stringhe di testo
 *  
 * 
 * Created on 4 aprile 2014, 15.28
 */

#ifndef M24C02_H
#define	M24C02_H

//  ----------------------------------------------------------------------------

    #include "i2c.h"

//  ----------------------------------------------------------------------------

    uchar p_24c02_error;

/*  Scelgo se visualizzare la funzione di visualizzazione degli erroti.
 *      Per ragioni di spazio.
*/
//    #define M24C02_M24C02_ERR_SHOW

    #define M24C02_REC_ACK             0x00
    #define M24C02_REC_NACK            0x01
    #define M24C02_REC_ERR             0x02

    #define M24C02_ERR_OK              0x00
    #define M24C02_ERR_GENERICO        0x01
    #define M24C02_ERR_CONTROL_BYTE    0x02
    #define M24C02_ERR_WORD_ADDRESS    0x03
    #define M24C02_ERR_DATA            0x04

#ifdef M24C02_M24C02_ERR_SHOW
    #define M24C02_ERR_GENERICO_S      "E: Generic\0"
    #define M24C02_ERR_CONTROL_BYTE_S  "E: Cntrl byte\0"
    #define M24C02_ERR_WORD_ADDRESS_S  "E: Word addr\0"
    #define M24C02_ERR_DATA_S          "E: Dati\0"
#endif

//  ----------------------------------------------------------------------------

    //	---------------------------------------------------------------------------------
    //	---------------------------------------------------------------------------------

    #define m24c02_end_read()	i2c_send_stop()
    #define m24c02_end_write()	i2c_send_stop()

    //	---------------------------------------------------------------------------------
    //	---------------------------------------------------------------------------------

    //	Lettura

    void m24c02_sequential_current_read( unsigned char v_device, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err );

    void m24c02_sequential_random_read( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err );

    unsigned char m24c02_current_address_read( unsigned char v_device, unsigned char *p_err );

    unsigned char m24c02_random_address_read( unsigned char v_device, unsigned char v_addr, unsigned char *p_err );
    
    //	Scrittura

    void m24c02_multibyte_write( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err );

    void m24c02_byte_write( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char *p_err );

    //	---------------------------------------------------------------------------------

//  void m24c02_byte_write_check( unsigned char v_device, unsigned char v_addr, unsigned char v_data, unsigned char *p_err );
    
#ifdef M24C02_M24C02_ERR_SHOW
    const unsigned char * m24c02_error_msg( unsigned char *p_err );
#endif

//  ----------------------------------------------------------------------------

#endif	/* M24C02_H */

