/* 
 * File:   pic_eeprom.h
 * Author: Stefano
 *
 * Created on 10 luglio 2015, 20.05
 */

#ifndef PIC_EEPROM_H
#define	PIC_EEPROM_H

    #include "project.h"

    unsigned char pic_eeprom_read( unsigned char v_addr );

    void pic_eeprom_write( unsigned char v_addr, unsigned char v_data );

#endif	/* PIC_EEPROM_H */

