#include "i2c.h"

//  ---------------------------------------------------------------------------------
//  DEBUG
#if defined I2C_DEBUG
    void i2c_dbg() {
        __delay_us(25);

        I2C_LO_DBG;                 //          Se invece è di input imposto il valore 0 nel registro shadow
        i2c_SendSignals();          //              Copio il registro shadow nella porta
        I2C_ATCH_DBG;               //              Imposto il pin come output

        __delay_us(50);

        I2C_DTCH_DBG;               //          Se invece era di output lo imposto come input ed il pull-up imposta il valore 1

        __delay_us(25);
    }

    void i2c_write_dbg( unsigned char v_data ) {
        __delay_us(25);

        if ( v_data == 0 ) {
            
            I2C_LO_DBG;                 
            i2c_SendSignals();          
            I2C_ATCH_DBG;              
            __delay_us(75);

        } else {    
            
            I2C_DTCH_DBG;              
            __delay_us(75);

        }
        __delay_us(25);
    }

#endif


//  ---------------------------------------------------------------------------------
//  Inizializzazione

//  ---------------------------------------------------------------------------------
//  Gestione Bus I2C

    //  i2c_Detatch
    void i2c_Detatch() {
#ifdef I2C_DEBUG
        i2c_dbg();
#endif
        //  Tutti i pin come input
        I2C_DTCH_BUS;
#ifdef I2C_DEBUG
        i2c_dbg();
#endif
    }
    
//  ---------------------------------------------------------------------------------
//  Comandi I2C

    /*
        Start Condition. START is identified by a high to
        low transition of the SDA line while the clock SCL
        is stable in the high state. A START condition must
        precede any command for data transfer. Except
        during a programming cycle, the ST24/25x02 con-
        tinuously monitor the SDA and SCL signals for a
        START condition and will not respond unless one
        is given.
    */
    void i2c_send_start() {

#ifdef I2C_DEBUG_START_STOP
        i2c_dbg();
#endif
//        i2c_bus_release();
            I2C_DTCH_BUS;
            i2c_Delay();

//        i2c_sda( 0 );
            I2C_LO_SDA;                 
            i2c_SendSignals();          
            I2C_ATCH_SDA;               
            i2c_Delay();

//        i2c_scl( 0 );
			I2C_LO_SCL;
			i2c_SendSignals();
			I2C_ATCH_SCL;
            i2c_Delay();

#ifdef I2C_DEBUG_START_STOP
        i2c_dbg();
#endif

    }

    /*
        Stop Condition. STOP is identified by a low to high
        transition of the SDA line while the clock SCL is
        stable in the high state. A STOP condition termi-
        nates communication between the ST24/25x02
        and the bus master. A STOP condition at the end
        of a Read command, after and only after a No
        Acknowledge, forces the standby state. A STOP
        condition at the end of a Write command triggers
        the internal EEPROM write cycle.
    */
    void i2c_send_stop() {

#ifdef I2C_DEBUG_START_STOP
        i2c_dbg();
#endif
//        i2c_bus_low();
            I2C_LO_BUS;
            i2c_SendSignals();
            I2C_ATCH_BUS;
            i2c_Delay();
        
//        i2c_scl( 1 );
			I2C_DTCH_SCL;
            i2c_Delay();

//        i2c_sda( 1 );
            I2C_DTCH_SDA;               
            i2c_Delay();

#ifdef I2C_DEBUG_START_STOP
        i2c_dbg();
#endif

    }

    /*
        Data Input. During data input the ST24/25x02
        sample the SDA bus signal on the rising edge of
        the clock SCL. Note that for correct device opera-
        tion the SDA signal must be stable during the clock
        low to high transition and the data must change
        ONLY when the SCL line is low.
    */
    void i2c_send_bit0( unsigned char v_bit ) {
        //  Invia un bit
        //	24c02 legge sda sul fronte di salita di clk

//        i2c_scl( 0 );			//	the data must change ONLY when the SCL line is low
			I2C_LO_SCL;
			i2c_SendSignals();
			I2C_ATCH_SCL;
            i2c_Delay();

//        i2c_sda( v_bit );               //	SDA signal must be stable during the clock low to high transition
            if ( v_bit==0 ) {               
                  I2C_LO_SDA;                 
                  i2c_SendSignals();          
                  I2C_ATCH_SDA;               
            } else {                          
                  I2C_DTCH_SDA;               
            }

//        i2c_scl( 1 );			//	rising edge of the clock SCL
			I2C_DTCH_SCL;
            i2c_Delay();

    }

    void i2c_send_bit1( unsigned char v_byte, unsigned char v_pos ) {
        //  Invia il v_pos-esimo bit del v_byte
        //	24c02 legge sda sul fronte di salita di clk
        unsigned char v_bit = 0x00;
        
//        i2c_scl( 0 );			//	the data must change ONLY when the SCL line is low
			I2C_LO_SCL;
			i2c_SendSignals();
			I2C_ATCH_SCL;
            i2c_Delay();

//        i2c_sda( (v_byte & (1<<v_pos) ) );
            v_bit = v_byte & (1<<v_pos);
            if ( v_bit == 0 ) {               
                  I2C_LO_SDA;                 
                  i2c_SendSignals();          
                  I2C_ATCH_SDA;               
            } else {                          
                  I2C_DTCH_SDA;               
            }
            i2c_Delay();

//        i2c_scl( 1 );			//	rising edge of the clock SCL
			I2C_DTCH_SCL;
            i2c_Delay();

    }

    /*
        Acknowledge Bit (ACK). An acknowledge signal
        is used to indicate a successfull data transfer. The
        bus transmitter, either master or slave, will release
        the SDA bus after sending 8 bits of data. During the
        9th clock pulse period the receiver pulls the SDA
        bus low to acknowledge the receipt of the 8 bits of
        data.
    */
    unsigned char i2c_read_bit_ack() {

        //  Rilascio SDA, pongo SCL a 0 ed aspetto la risposta dello slave

        unsigned char v_out;

#ifdef I2C_DEBUG_ACK
        i2c_dbg();
#endif

        //  --------------------------------------------------------------------
//        i2c_bus_ack();
        I2C_LO_SCL;         //  Imposto SCL a 0
        i2c_SendSignals();
        I2C_ATCH_SCL;
        
        I2C_DTCH_SDA;       //  Rilascio SDA

        i2c_DelayAck();     //  Attendo che i segnali siano stabili

        //  --------------------------------------------------------------------
        //  Sul fronte di salita Slave imposta SDA alto o basso
        I2C_DTCH_SCL;
        i2c_DelayAck();

        v_out = I2C_SDA;	//	Leggo valore SDA
#ifdef I2C_DEBUG_ACK
        i2c_write_dbg( v_out );
#endif

        //  --------------------------------------------------------------------
        //  Sul fronte di discesa Slave rilascia SDA
        I2C_LO_SCL;         //  Imposto SCL a 0
        i2c_SendSignals();
        I2C_ATCH_SCL;
        i2c_DelayAck();

#ifdef I2C_DEBUG_ACK
        i2c_dbg();
#endif

        return v_out;

    }