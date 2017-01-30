/*
 * File:   Source.c
 * Author: nicholasvu
 *
 * Created on January 18, 2017, 7:51 PM
 */



#include <stdint.h> 
#include <p33FJ06GS101A.h>
#include <xc.h>
#include <libpic30.h>	/* __delay32() */
#include <stdio.h>
#include <stdlib.h>

#define FCY 3686400UL 

/*
 * FAST RC DIV N, O/P ON CLKO (PIN 7).
 *
 * FOSC = 7,372,800 Hz
 * FCY  = 7,372,800 / 2
 */

/* ICSP I/O Data I/O */
#define ICSPIO_LATDAT  (LATBbits.LATB3)
#define ICSPIO_PORTDAT (PORTBbits.RB3)
#define ICSPIO_TRISDAT (TRISBbits.TRISB3)

/* ICSP I/O Clock Input */
#define ICSPIO_LATCLK  (LATBbits.LATB4)
#define ICSPIO_PORTCLK (PORTBbits.RB4)
#define ICSPIO_TRISCLK (TRISBbits.TRISB4)



#define FICD_RESERVED (0xFFEF) /* B4 = 0 */
_FICD(JTAGEN_OFF & FICD_RESERVED & ICS_PGD1)
_FWDT(FWDTEN_OFF & PLLKEN_OFF & WDTPRE_PR128 & WDTPOST_PS32768)
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_OFF & POSCMD_NONE)
_FOSCSEL(IESO_OFF & FNOSC_FRCDIVN)
_FGS(GCP_OFF & GWRP_OFF)

/*
 * Init I/O
 */

static inline void
init_io(void)
{
	/* ADC Digital Mode */
	ADPCFG = 0xFFFF;

	/* Reset O/P */
	LATA = 0;
	LATB = 0;

	/* O/D Off */
	ODCA = 0;
	ODCB = 0;

	/* RA0 O/P */
	TRISAbits.TRISA0 = 0;
}

int main(void)
{
	static uint8_t arg;

	/* Init Clock */
	CLKDIVbits.FRCDIV = 0; /* 3.68Mhz (divide by 1) */

	/* Init I/O */
	init_io();

	/* Init ICSP I/O */
	init_icspio();

	/* ICSP I/O */
	while (1) {
		switch (icspio_common()) {
		default:icspio_err = icspio_sendbyte(NAK);
			continue;

		case CMD_LED:
			icspio_err = icspio_sendbyte(ACK);
			if (icspio_err)
				continue;
			icspio_err = icspio_getbyte(&arg);
			if (icspio_err)
				continue;
			LATA = arg;
			break; 
		case CMD_SWITCH:
			icspio_err = icspio_sendbyte(ACK);
			if (icspio_err)
				continue;
			icspio_err = icspio_sendbyte(PORTB);
			if (icspio_err)
				continue;
		}
		icspio_err = icspio_sendbyte(icspio_checksum);
	}
}