#include "m24c02.h"

//	---------------------------------------------------------------------------------

    void m24c02_send_device_sel( unsigned char v_device, unsigned char v_Rw ) {

        unsigned char i=0x00;
        
/*
        for (i=4; i>0; i--)                         //
            i2c_send_bit1( 0b00001010, (i-1) );     //  Tot. 9 istruzioni LM
*/
        i2c_send_bit0( 1 );                         //
        i2c_send_bit0( 0 );                         //
        i2c_send_bit0( 1 );                         //
        i2c_send_bit0( 0 );                         //  Tot. 8 istruzioni LM

        //  E2, E1, E0
        for (i=3; i>0; i--)                         //
            i2c_send_bit1( v_device, (i-1) );       //  Tot. 9 istruzioni LM
/*
        i2c_send_bit1( v_device, 2 );               //
        i2c_send_bit1( v_device, 1 );               //
        i2c_send_bit1( v_device, 0 );               //  Tot. 11 istruzioni LM
*/        

//        i2c_send_bit1( v_Rw, 0 );                   //  Tot. 3 istruzioni LM

        i2c_send_bit0( v_Rw );                      //  Tot. 1 istruzioni LM

    }

    void m24c02_send_byte ( unsigned char v_data ) {

        unsigned char i=0x00;

        //  Invio da MSB ad LSB
        //  bit7 ... bit 0
        for ( i=8; i>0; i--)
            i2c_send_bit1( v_data, (i-1) );

    }

    void m24c02_read_byte( unsigned char *v_out, unsigned char v_last_byte ) {

        unsigned char x	= 0x00;

        //	Leggo 8 bit da MSB ad LSB
        for ( x=8; x>0; x-- ) {             //	8 bit
            *v_out <<= 1;
            *v_out |= i2c_read_bit_ack();            
        }

        if ( v_last_byte==0 ) {
            i2c_send_ack();				//	Invio Ack
        } else {
            i2c_send_nack();			//	Invio !Ack
        }

    }

//	---------------------------------------------------------------------------------

    void m24c02_set_random_address( unsigned char v_device, unsigned char v_addr, unsigned char *p_err ) {
        
        unsigned char   v_ack   = 0x00;

        *p_err = M24C02_ERR_OK;

        //  Start
        i2c_send_start();                                                   //	Start

        //  Control Byte
        m24c02_send_device_sel( v_device, 0 );                              //	Device Address, 1=Read/0=Write

        v_ack = i2c_read_bit_ack();                                         //	Leggo Ack
        if ( v_ack != M24C02_REC_ACK ) {
            *p_err = M24C02_ERR_CONTROL_BYTE;
            return;
        }

        //  Word Address
        m24c02_send_byte( v_addr );                                         //	Invio addr

        v_ack = i2c_read_bit_ack();                                         //	Leggo Ack
        if ( v_ack != M24C02_REC_ACK ) {
            *p_err = M24C02_ERR_WORD_ADDRESS;
            m24c02_end_read();
            return;
        }
        
    }

//	---------------------------------------------------------------------------------

    //	Lettura
    void m24c02_sequential_current_read( unsigned char v_device, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err ) {
        
        unsigned char   v_ack       = 0x00;
        unsigned char   v_ind       = 0x00;

        *p_err = M24C02_ERR_OK;

        //  Start
        i2c_send_start();                                                   //	Start

        //  Control Byte    ( Dummy Write )
        m24c02_send_device_sel( v_device, 1 );                              //	Device Address, 1=Read/0=Write

        v_ack = i2c_read_bit_ack();                                         //	Leggo Ack

        if ( v_ack != M24C02_REC_ACK ) {
            *p_err = M24C02_ERR_CONTROL_BYTE;
            m24c02_end_read();
            return;
        }

        //  Data
        /*
        for ( v_ind=0; v_ind<v_byte-1; v_ind++ ) {
            *(v_buffer + v_ind)	= m24c02_read_multi_byte(0);                    //	Leggo 8 Bit
        }
        *(v_buffer + v_ind) = m24c02_read_multi_byte(1);                        //	Leggo 8 Bit
        */
        for ( v_ind=0; v_ind<v_byte-1; v_ind++ ) {
            m24c02_read_byte((v_buffer + v_ind), 0);                    //	Leggo 8 Bit
        }
        m24c02_read_byte((v_buffer + v_ind), 1);                        //	Leggo 8 Bit
        
        //  Stop
        m24c02_end_read();

    }

    void m24c02_sequential_random_read( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err ) {
        
        *p_err = M24C02_ERR_OK;

        m24c02_set_random_address( v_device, v_addr, p_err );
        if ( *p_err == M24C02_ERR_OK )
            m24c02_sequential_current_read( v_device, v_buffer, v_byte, p_err );

    }

    unsigned char m24c02_current_address_read( unsigned char v_device, unsigned char *p_err ) {

        unsigned char	v_out	= 0x00;

        m24c02_sequential_current_read( v_device, &v_out, 1, p_err );

        return v_out;

    }

    unsigned char m24c02_random_address_read( unsigned char v_device, unsigned char v_addr, unsigned char *p_err ) {

        unsigned char   v_out	= 0x00;
        
        m24c02_sequential_random_read( v_device, v_addr, &v_out, 1, p_err );

        return v_out;
    }

//	Scrittura

    void m24c02_multibyte_write( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char v_byte, unsigned char *p_err ) {

        unsigned char   v_ack = 0x00;
        unsigned char   v_ind = 0x00;

        *p_err = M24C02_ERR_OK;

        m24c02_set_random_address( v_device, v_addr, p_err );

        for ( v_ind=0; v_ind<v_byte; v_ind++ ) {
            //  Data
            m24c02_send_byte(*(v_buffer + v_ind));          //	Invio dato

            v_ack = i2c_read_bit_ack();                     //	Leggo Ack
            if ( v_ack != M24C02_REC_ACK ) {
                *p_err = M24C02_ERR_DATA;
                m24c02_end_write();
                return;
            }
        }
        
        //  Stop
        m24c02_end_write();

    }

    void m24c02_byte_write( unsigned char v_device, unsigned char v_addr, unsigned char *v_buffer, unsigned char *p_err ) {

        m24c02_multibyte_write( v_device, v_addr, v_buffer, 1, p_err );
        
    }

//	---------------------------------------------------------------------------------

#ifdef M24C02_M24C02_ERR_SHOW
    const unsigned char * m24c02_error_msg( unsigned char *p_err ) {
        switch ( *p_err ) {
            case M24C02_ERR_CONTROL_BYTE:
                return M24C02_ERR_CONTROL_BYTE_S;
            case M24C02_ERR_WORD_ADDRESS:
                return M24C02_ERR_WORD_ADDRESS_S;
            case M24C02_ERR_DATA:
                return M24C02_ERR_DATA_S;
            default:
                return M24C02_ERR_GENERICO_S;
        }
    }
#endif
    
    