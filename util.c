#include "util.h"

/*
 * Update score into LCD
 */
void update_score() {
	enable_lcd_write();
	gotoXy(0,0);
	prints("Score:");
	integerToLcd(score);
	gotoXy(0,1);
	prints("Erros:");
	integerToLcd(errors);
}

/*
 * This two functions stop the main thread for a certain number of milli (10^-3).
 */
void delay_ms(unsigned int ms ) {
	unsigned int i;
    for (i = 0; i<= ms; i++) {
    	__delay_cycles(500);
    }
}

/*
 * Stop for microseconds (10^-6)
 */
void delay_us(unsigned int us ) {
    unsigned int i;
    for (i = 0; i<= us/2; i++) {
    	__delay_cycles(1);
    }
}

/*
 * Enable BTN(P1.3)
 */
void enable_btn() {
	P2DIR &= ~(BIT0 | BIT1 | BIT2);
	P2IE |= (BIT0 | BIT1 | BIT2); // P2.x interrupt enabled
	P2IFG &= ~(BIT0 | BIT1 | BIT2); // P2.x IFG cleared
	P2IES &= ~(BIT0 | BIT1 | BIT2); // P1.3 Hi/lo edge
}

/**
 * Convert btn coded with binary to decimal value
 */
int note_played() {
	int note = 0;
	int bit_set[3] = {0, 0, 0};
	int x = 600;
	while(x) {
		if ((BIT0 & P2IN) && (bit_set[0] == 0)) {
			note+=1;
			bit_set[0] = 1;
		}
		if ((BIT1 & P2IN) && (bit_set[1] == 0)) {
			note+=2;
			bit_set[1] = 1;
		}
		if ((BIT2 & P2IN) && (bit_set[2] == 0)) {
			note+=4;
			bit_set[2] = 1;
		}
		x--;
	}

	return note-1;
}

/**
 * Lower power mode is set with 0 to SMLK and ACLK stay working
 */
void configure_timer_a() {
	BCSCTL1 = CALBC1_1MHZ; // configure time A source clk
	DCOCTL = CALDCO_1MHZ; // configure digital oscilator clk

	TACTL = TASSEL_2 + MC_3 + ID_3; // configure Timer A
	TACCR0 = 8; // count until LIMIT

	_BIS_SR(LPM0_bits+GIE); // activate Lower Power mode and interruptions
}
