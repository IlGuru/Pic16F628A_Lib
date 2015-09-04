/* 
 * File:   pic_eeprom.c
 * Author: Stefano
 *
 * Created on 10 luglio 2015, 20.05
 */

    #include "pic_eeprom.h"

    unsigned char pic_eeprom_read( unsigned char v_addr ) {
        EEADR           = v_addr;
        EECON1bits.RD   = 1;

        return EEDATA;
    }

    void pic_eeprom_write( unsigned char v_addr, unsigned char v_data ) {
        //  -------
        EEADR           = v_addr;
        EEDATA          = v_data;

        //  -------
        EECON1bits.WREN = 1;
        EECON2          = 0x55;
        EECON2          = 0xAA;
        EECON1bits.WR   = 1;
    }
