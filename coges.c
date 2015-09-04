#include "coges.h"

void byte_code( unsigned char * v_cs, unsigned char * v_cr, unsigned char * v_out ) {
    
    signed char v_ind = 0x00;

    /*  Inserisco in v_out 2 bit alla volta, per questo effettuo vari shift left di 2 bit
     *      I primi sono i 2 bit meno significativi del checksum, dopo averli inseriti shifto 
     *          il checksum 2 bit a destra in modo tale che alla prossima chiamata di byte_code
     *          i 2 bit meno significativi saranno ancora quelli da inserire.
     *      Poi eseguo in ciclo sui tre byte che compongono il dato a 24bit, partendo dal più
     *          significativo *(v_cr + 2) al meno significativo *(v_cr + 0)
     *          Per ciascun byte inserisco con lo stesso sistema utilizzato per il checksum i due bit 
     *          meno significativi
     * 
     *      In pratica lavorando con 2 bit alla volta, sto effettuando concatenazioni di valori in base 4
     */
    
    *v_out = 0x00;
    *v_out  = *v_out | ( *v_cs & 0b11 );
    *v_cs = *v_cs >> 2;
    
    for ( v_ind=2; v_ind>=0; v_ind--) {
        *v_out          = (*v_out << 2) | ( *(v_cr + v_ind) & 0b11 );
        *(v_cr + v_ind) = *(v_cr + v_ind) >> 2;
    }    
}

void coges_money_code( unsigned short long v_cred, unsigned char v_addr, unsigned char * v_out ) {

    /*  Genera il codice di 4 byte dal credito impostato e dall'indirizzo di memoria
     * 
     * 
     *  v_out è il primo elemento di un array di 4 byte in cui verrà inserito il codice coges.
     *      Il primo elemento dell'array è il primo codice, il quarto è l'ultimo codice.
     * 
     *  v_cred è il dato a 24bit contenente il valore esadecimale del credito da codificare
     * 
     *  v_addr è l'indirizzo di memoria in cui verrà inserito il primo elemento dell'arrat
     *      con il codice.
     *
     */
    signed char         v_ind       = 0x00;
    unsigned char       v_checksum  = 0x00;
    unsigned short long v_24b       = 0x000000;

    /*  Il checksum si calcola sommando all'indirizzo in cui è memorizzato il dato a 24bit
     *      tutti e 6 i nibbles che compongono il dato.
     *      Il valore ottenuto viene poi complementato a 1 e prelevati solo gli 8 bit meno significativi.
     */
    v_24b       = v_cred;
    v_checksum  = v_addr;
    for ( v_ind=0; v_ind<6; v_ind++ ) {
        v_checksum  = v_checksum + (v_24b & 0x0F);
        v_24b       = v_24b >> 4;
    };
    v_checksum = ~v_checksum;
    v_checksum = v_checksum & 0xFF;
    
    /*  Il codice di 4 byte viene dipende dal dato a 24bit e dal checksum.
     *      Per crearlo passo alla funzione byte_code, il valore del checksum
     *      e ciascuno dei tre byte che compongono il dato a 24bit partendo dal byte meno significativo.
     *      Con questi dati compogno ciascuno dei 4 byte del codice da inserire partendo dal byte 
     *      meno significativo che verrà inserito nell'ultimo posto dell' array v_out che è stato passato
     *      a coges_money_code.
     */
    v_24b       = v_cred;
    for ( v_ind=3; v_ind>=0; v_ind-- )
        byte_code( &v_checksum, (( unsigned char * ) &v_24b), v_out + v_ind );    
    
    return;
    
}

void coges_money_value( unsigned char * v_code, unsigned short long * v_out ) {
    
    /*      Legge il valore del credito a 24bit dal codice di 4 byte.
     * 
     *      v_code è l'array di 4 byte contenente il codice
     */
    
    signed char     v_ind   = 0x00;
    unsigned char   v_byte  = 0x00;

    *v_out = 0;
    for ( v_ind=0x04; v_ind>=0; v_ind-=2 ) {        //  Solo i 6 bit bassi, a 2 a 2 : B=xxAABBCC
        for ( v_byte=0; v_byte<4; v_byte++ ) {      //  Tutti e 4 i byte
            *v_out = *v_out << 2;
//            *v_out = *v_out | ( ( (*(v_code + v_byte)) & ( 0b11 << v_ind) ) ) >> v_ind;
            *v_out = *v_out | ( ( (*(v_code + v_byte)) >> v_ind ) & 0b11 );
        }
    }

}

void coges_val_to_string( unsigned short long v_cred_hex, unsigned char * v_out ) {

    //  Funzione ultoa copiata e taroccata
	unsigned short long	v;
	char                c;
	char                v_ind = 0x00;

	v = v_cred_hex;
	do {
		v /= 10;
		v_out++;
	} while(v != 0);
    v_out += 2;     //  Faccio spazio per la virgola e la moneta
	*v_out-- = '\0';
#ifdef E_CUSTOM_CHARSET
	*v_out-- = E_CUSTOM_CHARSET_EURO;
#else
	*v_out-- = 'E';
#endif    
	do {
        if (v_ind==2) {
            *v_out-- = '.';
            v_ind++;
        }
		c = v_cred_hex % 10;
		v_cred_hex /= 10;
		if(c >= 10)
			c += 'A'-'0'-10;
		c += '0';
		*v_out-- = c;
        v_ind += 1;
	} while(v_cred_hex != 0);
    
}