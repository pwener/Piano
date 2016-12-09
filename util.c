#include "util.h"

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
	P1DIR &= ~BTN;
	P1OUT |= BTN;
	P1IE |= BTN; // P1.3 interrupt enabled
	P1IES |= BTN; // P1.3 Hi/lo edge
	P1IFG &= ~BTN; // P1.3 IFG cleared
	P1REN |= BTN; // Enable resistor on BTN
}

void configure_timer_a() {
	BCSCTL1 = CALBC1_1MHZ; // configure time A source clk
	DCOCTL = CALDCO_1MHZ; // configure digital oscilator clk

	TACTL = TASSEL_2 + MC_3 + ID_3; // configure Timer A
	TACCR0 = 8; // count until LIMIT

	_BIS_SR(LPM4_bits+GIE);
}
