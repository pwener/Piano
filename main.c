#include <msp430g2553.h>
// Pinos da porta P1
#define PIN_A BIT0
#define PIN_B BIT1
#define PIN_C BIT2
#define PIN_D BIT3
#define PIN_E BIT4
#define PIN_F BIT5
#define PIN_G BIT6
// Pinos da porta P2
#define PIN_0 BIT0
#define PIN_1 BIT1
#define PIN_2 BIT2
#define PIN_3 BIT3

#define BTN BIT3

#define LIMIT 8

unsigned int timer_count = 0;

int bcd[] = {
		PIN_G,
		~(PIN_B | PIN_C),
		PIN_C | PIN_F,
		PIN_E | PIN_F,
		PIN_A | PIN_D | PIN_E,
		PIN_B | PIN_E,
		PIN_A | PIN_B,
		~(PIN_A | PIN_B | PIN_C),
		0,
		PIN_D | PIN_E
};

void main(void) {
	WDTCTL = WDTPW + WDTHOLD;
	P1IE |= BTN; // P1.3 interrupt enabled
  P1IFG &= ~BTN; // P1.3 IFG cleared
  P1REN |= BTN; // Enable resistor on BTN

	P1DIR |= (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G);
	P1OUT = 0;
	P2OUT = 0;

	P2DIR |= (PIN_0 | PIN_1 | PIN_2 | PIN_3);
	P2OUT = 0;

	TACTL = TASSEL_2 + MC_2; // configure Timer A
	_BIS_SR(LPM4_bits+GIE);

__enable_interrupt(); // enable all interrupts

	while(1);

	return 0;
}

/*
 * Syntax of interruptions used in code composer
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	timer_count = (TAR % LIMIT); // found a value between 0 to LIMIT
	/*
	 * According documentation, if this flags are not setted to 0,
	 * the interrupts stay peding.
	 */
 	P1IFG &= ~BTN; // P1.3 IFG cleared
}
