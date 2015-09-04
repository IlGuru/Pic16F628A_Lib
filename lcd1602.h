/* 
 * File:   LCD1602.h
 * Author: Stefano
 *
 *      VERSIONE    2.00
 *  
 * Created on 3 luglio 2015, 13.53
 */

#ifndef LCD1602_H
#define	LCD1602_H

    #include "project.h"

//------------------------------------------------------------------------------

    #define lcd_delay()     __delay_us(330)     //  Testato, a 250 non funziona

//    #define LCD_MODE_8BIT 
    #define LCD_MODE_4BIT

//  -------------------------------------------------------------------------------------------

    #define LCD1602_DB4         C_PORTAbits.DB4
    #define LCD1602_DB5         C_PORTAbits.DB5
    #define LCD1602_DB6         C_PORTAbits.DB6
    #define LCD1602_DB7         C_PORTAbits.DB7
#ifdef LCD_READ_FUNCTIONS
    #define LCD1602_RW          C_PORTAbits.RW
#endif
    #define LCD1602_RS          C_PORTAbits.RS
    #define LCD1602_E           C_PORTAbits.E

    #define LCD1602_DB4shadow   SR_PORTAbits.DB4
    #define LCD1602_DB5shadow   SR_PORTAbits.DB5
    #define LCD1602_DB6shadow   SR_PORTAbits.DB6
    #define LCD1602_DB7shadow   SR_PORTAbits.DB7
#ifdef LCD_READ_FUNCTIONS
    #define LCD1602_RW_shadow   SR_PORTAbits.RW
#endif
    #define LCD1602_RS_shadow   SR_PORTAbits.RS
    #define LCD1602_E__shadow   SR_PORTAbits.E

    #define LCD1602_DB4_TRIS    C_TRISAbits.DB4
    #define LCD1602_DB5_TRIS    C_TRISAbits.DB5
    #define LCD1602_DB6_TRIS    C_TRISAbits.DB6
    #define LCD1602_DB7_TRIS    C_TRISAbits.DB7
#ifdef LCD_READ_FUNCTIONS
    #define LCD1602_RW__TRIS    C_TRISAbits.RW
#endif
    #define LCD1602_RS__TRIS    C_TRISAbits.RS
    #define LCD1602_E___TRIS    C_TRISAbits.E

    #define LCD1602_DATA_shadow SR_PORTAbits.DATA
    #define LCD1602_DATA_TRIS   C_TRISAbits.DATA

    //  -----------------------------------------------------------------------
    
#ifdef LCD_READ_FUNCTIONS
    #define LCD1602_ATCH_RW     LCD1602_RW__TRIS=0     // SDA secondo bit va input, SCL primo bit rimane output (2)
    #define LCD1602_DTCH_RW     LCD1602_RW__TRIS=1
    #define LCD1602_HI_RW       LCD1602_RW_shadow=1
    #define LCD1602_LO_RW       LCD1602_RW_shadow=0
#endif

    #define LCD1602_ATCH_RS     LCD1602_RS__TRIS=0
    #define LCD1602_DTCH_RS     LCD1602_RS__TRIS=1
    #define LCD1602_HI_RS       LCD1602_RS_shadow=1
    #define LCD1602_LO_RS       LCD1602_RS_shadow=0

    #define LCD1602_ATCH_E      LCD1602_E___TRIS=0
    #define LCD1602_DTCH_E      LCD1602_E___TRIS=1
    #define LCD1602_HI_E        LCD1602_E__shadow=1
    #define LCD1602_LO_E        LCD1602_E__shadow=0

    #define LCD1602_ATCH_DB4    LCD1602_DB4_TRIS=0
    #define LCD1602_DTCH_DB4    LCD1602_DB4_TRIS=1
    #define LCD1602_HI_DB4      LCD1602_DB4shadow=1
    #define LCD1602_LO_DB4      LCD1602_DB4shadow=0

    #define LCD1602_ATCH_DB5    LCD1602_DB5_TRIS=0
    #define LCD1602_DTCH_DB5    LCD1602_DB5_TRIS=1
    #define LCD1602_HI_DB5      LCD1602_DB5shadow=1
    #define LCD1602_LO_DB5      LCD1602_DB5shadow=0

    #define LCD1602_ATCH_DB6    LCD1602_DB6_TRIS=0
    #define LCD1602_DTCH_DB6    LCD1602_DB6_TRIS=1
    #define LCD1602_HI_DB6      LCD1602_DB6shadow=1
    #define LCD1602_LO_DB6      LCD1602_DB6shadow=0

    #define LCD1602_ATCH_DB7    LCD1602_DB7_TRIS=0
    #define LCD1602_DTCH_DB7    LCD1602_DB7_TRIS=1
    #define LCD1602_HI_DB7      LCD1602_DB7shadow=1
    #define LCD1602_LO_DB7      LCD1602_DB7shadow=0

    #define LCD1602_ATCH_DB7    LCD1602_DB7_TRIS=0
    #define LCD1602_DTCH_DB7    LCD1602_DB7_TRIS=1
    #define LCD1602_HI_DB7      LCD1602_DB7shadow=1
    #define LCD1602_LO_DB7      LCD1602_DB7shadow=0

    #define LCD1602_ATCH_DB7    LCD1602_DB7_TRIS=0
    #define LCD1602_DTCH_DB7    LCD1602_DB7_TRIS=1
    #define LCD1602_HI_DB7      LCD1602_DB7shadow=1
    #define LCD1602_LO_DB7      LCD1602_DB7shadow=0

    #define LCD1602_ATCH_DATA   LCD1602_DATA_TRIS=0b0000
    #define LCD1602_DTCH_DATA   LCD1602_DATA_TRIS=0b1111
    #define LCD1602_HI_DATA     LCD1602_DATA_shadow=0b1111
    #define LCD1602_LO_DATA     LCD1602_DATA_shadow=0b0000

//------------------------------------------------------------------------------

    //  Comandi base display
    
    void    lcd_clear_display();
    void    lcd_cursor_at_home();

    //  -------------------------
    #define LCD_ID_DEC          0
    #define LCD_ID_INC          1

    #define LCD_S_NSHIFTED      0
    #define LCD_S_SHIFTED       1

    void    lcd_entry_mode_set( unsigned char ID, unsigned char S);

    //  -------------------------
    #define LCD_D_DISP_OFF      0
    #define LCD_D_DISP_ON       1

    #define LCD_C_CURS_OFF      0
    #define LCD_C_CURS_ON       1

    #define LCD_B_BLINK_OFF     0
    #define LCD_B_BLINK_ON      1

    void    lcd_display_onoff_control( unsigned char D, unsigned char C, unsigned char B );

    //  -------------------------
    #define LCD_SC_CURS_SHIFT   0
    #define LCD_SC_DISP_SHIFT   1

    #define LCD_RL_SHIFT_LEFT   0
    #define LCD_RL_SHIFT_RIGHT  1

    void    lcd_cursor_display_shift( unsigned char SC, unsigned char RL );

    //  -------------------------
    #define LCD_DL_4_BITS       0
    #define LCD_DL_8_BITS       1

    #define LCD_F_5x7           0
    #define LCD_F_5x10          1

    #define LCD_N_1_LINE        0
    #define LCD_N_2_LINE        1

    void    lcd_function_set( unsigned char DL, unsigned char N, unsigned char F );

    void    lcd_set_cg_ram_addr( unsigned char ram_addr );

    void    lcd_set_dd_ram_addr( unsigned char ram_addr );
    void    lcd_busyflag_addrread( unsigned char *data );
    void    lcd_write_data( unsigned char data );
    void    lcd_read_data( unsigned char *data );
    
//------------------------------------------------------------------------------

    //  Funzioni alto livello
    
    void    lcd_init();
    
    void    lcd_goto_home();
    void    lcd_goto_xy( unsigned char v_col, unsigned char v_row );
    
    void    lcd_print_s( unsigned char * message );
    void    lcd_print_hex( unsigned char v_read );

#ifdef E_CUSTOM_CHARSET    

//    void    lcd_set_char( unsigned char v_char, const unsigned char * v_bits );
    void    lcd_set_char();

#endif
    
#endif	/* LCD1602_H */

