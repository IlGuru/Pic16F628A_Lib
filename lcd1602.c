/* 
 * File:   lcd1602.c
 * Author: Stefano
 *
 * Created on 3 luglio 2015, 14.28
 */

#include "lcd1602.h"

    #define lcd_SendSignals()   PORTA = SR_PORTA
    #define lcd_RecvSignals()   SR_PORTA = PORTA;
//    #define lcd_SendSignals()   PORTB = SR_PORTB
//    #define lcd_RecvSignals()   SR_PORTB = PORTB;

//    void lcd_SendSignals()   {   
//        PORTA = SR_PORTA;       
//        PORTB = SR_PORTB;       
//    }
//    void lcd_RecvSignals()   {   
//        SR_PORTA = PORTA;       
//        SR_PORTB = PORTB;       
//    }

void    lcd_pulse() {
        LCD1602_DTCH_E;               
        lcd_delay();

        LCD1602_LO_E;                 
        lcd_SendSignals();          
        LCD1602_ATCH_E;    
        lcd_delay();
}

void    lcd_pin_lo() {
#ifdef LCD_READ_FUNCTIONS
        LCD1602_LO_RW;                 
#endif
        LCD1602_LO_RS;                 
        LCD1602_LO_E;
        
        LCD1602_LO_DATA;                 
        lcd_SendSignals();
        
#ifdef LCD_READ_FUNCTIONS
        LCD1602_ATCH_RW;    
#endif
        LCD1602_ATCH_RS;    
        LCD1602_ATCH_E;
        
        LCD1602_ATCH_DATA;    
        lcd_delay();
}

void    lcd_command( unsigned char RW, unsigned char RS, unsigned char data ) {
    //  Bit0=RW, Bit1=RS, Bit2=E
#ifdef LCD_MODE_4BIT
    unsigned char   v_nibble = 0x00;
    signed char     v_ind    = 0x00;
#endif
    
    //      Accetto il valore di RS ed RW ma porto E a LO
#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW_shadow   = RW;                 
#endif
        LCD1602_RS_shadow   = RS;                 
        LCD1602_E__shadow   = 0;                 
        lcd_SendSignals();          

#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW__TRIS    = RW;                 
#endif
        LCD1602_RS__TRIS   = RS;                 
        LCD1602_E___TRIS   = 0;                 

        lcd_delay();
    
#ifdef LCD_MODE_8BIT

        //  Dato di 8 bit

            LCD1602_DATA_shadow = data;                 
            lcd_SendSignals();          
            LCD1602_DATA_TRIS   = data;
            lcd_delay();
    
        //  Impulso E
            lcd_pulse();

#endif
    
#ifdef LCD_MODE_4BIT

            for ( v_ind=0x04; v_ind>=0x00; v_ind-=4 ) {
                v_nibble = ( data >> v_ind ) & 0b00001111;

            //  Nibble  ( prima nibble alto, poi nibble basso )
                LCD1602_DATA_shadow = v_nibble;                 
                lcd_SendSignals();          
                LCD1602_DATA_TRIS   = v_nibble;
                lcd_delay();

            //  Impulso E
                lcd_pulse();
            }
            
#endif
    
        lcd_pin_lo();
        
}

void    lcd_clear_display() {
    
    lcd_command( 0, 0, 0b00000001 );

}

void    lcd_cursor_at_home() {
    
    lcd_command( 0, 0, 0b00000010 );

}

void    lcd_entry_mode_set( unsigned char ID, unsigned char S) {
    
    lcd_command( 0, 0, 0b00000100 | (ID<<1) | S );

}

void    lcd_display_onoff_control( unsigned char D, unsigned char C, unsigned char B ) {

    lcd_command( 0, 0, 0b00001000 | (D<<2) | (C<<1) | B );

}

void    lcd_cursor_display_shift( unsigned char SC, unsigned char RL ) {
    //  Moves cursor or shifts the display w/o changing DD RAM contents
    lcd_command( 0, 0, 0b00010000 | (SC<<3) | (RL<<2) );

}

#ifdef LCD_MODE_4BIT
void    lcd_function_set_8bit() {
    //  Imposta la modalità a 4 bit

    //  Bit0=RW, Bit1=RS, Bit2=E
#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW_shadow   = 0;                 
#endif
        LCD1602_RS_shadow   = 0;                 
        LCD1602_E__shadow   = 0;                 
        lcd_SendSignals();          
        
#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW__TRIS    = 0;                 
#endif
        LCD1602_RS__TRIS    = 0;                 
        LCD1602_E___TRIS    = 0;                 
        lcd_delay();
    
    //  Nibble alto
        LCD1602_DATA_shadow = 0b0011;                 
        lcd_SendSignals();          
        LCD1602_DATA_TRIS   = 0b0011;
        lcd_delay();
    
    //  Impulso E
        lcd_pulse();

        lcd_pin_lo();
}
void    lcd_function_set_4bit() {
    //  Imposta la modalità a 4 bit

    //  Bit0=RW, Bit1=RS, Bit2=E
#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW_shadow   = 0;                 
#endif
        LCD1602_RS_shadow   = 0;                 
        LCD1602_E__shadow   = 0;                 
        lcd_SendSignals();          
        
#ifdef LCD_READ_FUNCTIONS
        LCD1602_RW__TRIS    = 0;                 
#endif
        LCD1602_RS__TRIS    = 0;                 
        LCD1602_E___TRIS    = 0;                 
        lcd_delay();
    
    //  Nibble alto
        LCD1602_DATA_shadow = 0b0010;                 
        lcd_SendSignals();          
        LCD1602_DATA_TRIS   = 0b0010;
        lcd_delay();
    
    //  Impulso E
        lcd_pulse();

        lcd_pin_lo();
}
#endif  /* LCD_MODE_4BIT */

void    lcd_function_set( unsigned char DL, unsigned char N, unsigned char F ) {
    //  Sets data bus length (DL), # of display lines (N), and character fonts (F).
    lcd_command( 0, 0, 0b00100000 | (DL<<4) | (N<<3) | (F<<2) );

}

void    lcd_set_cg_ram_addr( unsigned char ram_addr ) {

    lcd_command( 0, 0, 0b01000000 | (ram_addr & 0b00111111) );

}

void    lcd_set_dd_ram_addr( unsigned char ram_addr ) {

    lcd_command( 0, 0, 0b10000000 | (ram_addr & 0b01111111) );

}

void    lcd_write_data( unsigned char data ) {

    lcd_command( 0, 1, data );

}

#ifdef LCD_READ_FUNCTIONS

void    lcd_busyflag_addrread( unsigned char *data ) {

#ifdef LCD_MODE_4BIT
    signed char v_ind = 0x00;
#endif
    
    //  Imposto il bus dati come input
        LCD1602_DTCH_DATA;    
    
    //  RW=1, RS=0, E=0
        LCD1602_RW_shadow   = 1;                 
        LCD1602_RS_shadow   = 0;                 
        LCD1602_E__shadow   = 0;                 
        lcd_SendSignals();          
        
        LCD1602_RW__TRIS    = 1;                 
        LCD1602_RS__TRIS    = 0;                 
        LCD1602_E___TRIS    = 0;                 
        lcd_delay();

#ifdef LCD_MODE_8BIT

    //  E=1
        LCD1602_DTCH_E;               
        lcd_delay();

    //  Leggo byte
        lcd_RecvSignals();
        *data = SR_B_LCD1602bits.DATA;
        
    //  E=0
        LCD1602_LO_E;                 
        lcd_SendSignals();          
        LCD1602_ATCH_E;    
        lcd_delay();        

#endif  /* LCD_MODE_4BIT */

#ifdef LCD_MODE_4BIT

        for ( v_ind=0x04; v_ind>=0x00; v_ind-=0x04 ) {
        //  E=1
            LCD1602_DTCH_E;               
            lcd_delay();

        //  Leggo nibble basso
            lcd_RecvSignals();
            *data = LCD1602_DATA_shadow;
            *data = *data << v_ind;

        //  E=0
            LCD1602_LO_E;                 
            lcd_SendSignals();          
            LCD1602_ATCH_E;    
            lcd_delay();        
        }
//    //  E=1
//        LCD1602_DTCH_E;               
//        lcd_delay();
//
//    //  Leggo nibble basso
//        lcd_RecvSignals();
//        *data = LCD1602_DATA_shadow;
//        *data = *data << 4;
//        
//    //  E=0
//        LCD1602_LO_E;                 
//        lcd_SendSignals();          
//        LCD1602_ATCH_E;    
//        lcd_delay();        
//
//    //  E=1
//        LCD1602_DTCH_E;               
//        lcd_delay();
//
//    //  Leggo nibble alto
//        lcd_RecvSignals();
//        *data |= LCD1602_DATA_shadow;
//        
//    //  E=0
//        LCD1602_LO_E;                 
//        lcd_SendSignals();          
//        LCD1602_ATCH_E;    
//        lcd_delay();        

#endif  /* LCD_MODE_4BIT */

}

void    lcd_read_data( unsigned char *data ) {

#ifdef LCD_MODE_4BIT
    signed char v_ind = 0x00;
#endif
    
    //  Imposto il bus dati come input
        LCD1602_DTCH_DATA;    
    
    //  RW=1, RS=1, E=0
        LCD1602_RW_shadow   = 1;                 
        LCD1602_RS_shadow   = 1;                 
        LCD1602_E__shadow   = 0;                 
        lcd_SendSignals();          
        
        LCD1602_RW__TRIS    = 1;                 
        LCD1602_RS__TRIS    = 1;                 
        LCD1602_E___TRIS    = 0;                 
        lcd_delay();

#ifdef LCD_MODE_8BIT

    //  E=1
        LCD1602_DTCH_E;               
        lcd_delay();

    //  Leggo byte
        lcd_RecvSignals();
        *data = SR_B_LCD1602bits.DATA;
        
    //  E=0
        LCD1602_LO_E;                 
        lcd_SendSignals();          
        LCD1602_ATCH_E;    
        lcd_delay();        

#endif  /* LCD_MODE_4BIT */

#ifdef LCD_MODE_4BIT

        for ( v_ind=0x04; v_ind>=0x00; v_ind-=0x04 ) {
        //  E=1
            LCD1602_DTCH_E;               
            lcd_delay();

        //  Leggo nibble basso
            lcd_RecvSignals();
            *data = LCD1602_DATA_shadow;
            *data = *data << v_ind;

        //  E=0
            LCD1602_LO_E;                 
            lcd_SendSignals();          
            LCD1602_ATCH_E;    
            lcd_delay();        
        }

#endif        
//    //  E=1
//        LCD1602_DTCH_E;               
//        lcd_delay();
//
//    //  Leggo nibble basso
//        lcd_RecvSignals();
//        *data = LCD1602_DATA_shadow;
//        *data = *data << 4;
//        
//    //  E=0
//        LCD1602_LO_E;                 
//        lcd_SendSignals();          
//        LCD1602_ATCH_E;    
//        lcd_delay();        
//
//    //  E=1
//        LCD1602_DTCH_E;               
//        lcd_delay();
//
//    //  Leggo nibble alto
//        lcd_RecvSignals();
//        *data |= LCD1602_DATA_shadow;
//        
//    //  E=0
//        LCD1602_LO_E;                 
//        lcd_SendSignals();          
//        LCD1602_ATCH_E;    
//        lcd_delay();        

}

#endif

//  ----------------------------------------------------------------------------

    //  Funzioni alto livello
    
#ifdef LCD_MODE_4BIT
void lcd_init() {

    //  Inizializzo i pin tutti LO
        lcd_pin_lo();

    //  Comandi inizializzazione
        
        __delay_ms(16);
        lcd_function_set_8bit();
        __delay_ms(5);
        lcd_function_set_8bit();
        __delay_ms(5);
        lcd_function_set_8bit();
        __delay_us(200);
        
        lcd_function_set_4bit();
        lcd_function_set( LCD_DL_4_BITS, LCD_N_2_LINE, LCD_F_5x7 );
        lcd_display_onoff_control( LCD_D_DISP_OFF, LCD_C_CURS_ON, LCD_B_BLINK_OFF );
        lcd_clear_display();
        lcd_entry_mode_set( LCD_ID_INC, LCD_S_NSHIFTED );

        lcd_display_onoff_control( LCD_D_DISP_ON, LCD_C_CURS_ON, LCD_B_BLINK_OFF );
        lcd_set_dd_ram_addr( 0x00 );
        lcd_delay();
}
#endif  /* LCD_MODE_4BIT */

#ifdef LCD_MODE_8BIT
void lcd_init() {
    
    //  Inizializzo i pin tutti LO
        lcd_pin_lo();

    //  Comandi inizializzazione
        
        __delay_ms(16);
        lcd_function_set( LCD_DL_8_BITS, LCD_N_2_LINE, LCD_F_5x7 );
        __delay_ms(5);
        lcd_function_set( LCD_DL_8_BITS, LCD_N_2_LINE, LCD_F_5x7 );
        __delay_ms(5);
        lcd_function_set( LCD_DL_8_BITS, LCD_N_2_LINE, LCD_F_5x7 );
        __delay_us(200);
        
        lcd_function_set_4bit();
        lcd_function_set( LCD_DL_8_BITS, LCD_N_2_LINE, LCD_F_5x7 );
        lcd_display_onoff_control( LCD_D_DISP_OFF, LCD_C_CURS_ON, LCD_B_BLINK_OFF );
        lcd_clear_display();
        lcd_entry_mode_set( LCD_ID_INC, LCD_S_NSHIFTED );

        lcd_display_onoff_control( LCD_D_DISP_ON, LCD_C_CURS_ON, LCD_B_BLINK_OFF );
        lcd_set_dd_ram_addr( 0x00 );
        lcd_delay();

}
#endif  /* LCD_MODE_4BIT */

void lcd_goto_home() {
    lcd_set_dd_ram_addr( 0x00 );
}

void lcd_goto_xy( unsigned char v_col, unsigned char v_row ) {
    
    lcd_set_dd_ram_addr( (v_row-1)*0x40 + (v_col-1) );

}


void lcd_print_s( unsigned char * message ){	// Write message to LCD (C string type)
    while (*message){                           // Look for end of string
        lcd_write_data(*message++);
    }
}

void lcd_print_hex( unsigned char v_read ) {

    const char *txt = "0123456789ABCDEF";
    unsigned char v_data;
    
    v_data = v_read >> 4;
    lcd_write_data( *(txt + v_data ) );
    v_data = v_read & 0x0F;
    lcd_write_data( *(txt + v_data ) );

}

//------------------------------------------------------------------------------


//void lcd_set_char( unsigned char v_num_char, const unsigned char * v_bits ) {
//    //  v_num_char  numero dki caratteri da programmare ( 0..7 )
//    //  v_bits  buffer di 8 byte contenente i bit con cui disegnare il carattere
//    
//    unsigned char v_char    = 0x00;
//    unsigned char v_ind     = 0x00;
//    
//    lcd_set_cg_ram_addr( 0x00 );
//    
//    for ( v_char=0x00; v_char<v_num_char; v_char++ ) {
//        for ( v_ind=0x00; v_ind<0x08; v_ind++ ) {
//            lcd_write_data( ( *(v_bits+v_ind+(8*v_char)) & 0b00011111 ) );
//        }
//    }
//    
//    
//}

#ifdef E_CUSTOM_CHARSET

void lcd_set_char() {
    
    unsigned char v_char    = 0x00;
    unsigned char v_ind     = 0x00;
    
    lcd_set_cg_ram_addr( 0x00 );
    
    for ( v_char=0x00; v_char<CUSTOM_CHARS; v_char++ ) {
        for ( v_ind=0x00; v_ind<0x08; v_ind++ ) {
            lcd_write_data( pic_eeprom_read( (v_char*8)+v_ind ) );
        }
    }
        
}
#endif