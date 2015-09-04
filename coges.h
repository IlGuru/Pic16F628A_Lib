/* 
 * File:   coges.h
 * Author: Stefano
 *
 *      Versione 1.0
 * 
 * Created on 8 luglio 2015, 17.19
 */

#ifndef COGES_H
#define	COGES_H

#include "project.h"

void coges_money_code( unsigned short long val, unsigned char v_addr, unsigned char * v_out );
void coges_money_value( unsigned char * v_code, unsigned short long * v_out );
void coges_val_to_string( unsigned short long v_cred_hex, unsigned char * v_out );

#endif	/* COGES_H */

