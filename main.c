#include <msp430g2553.h>
#include "lcd16.h"
#include "util.h"
#include "music.h"

// P1 pins
#define PIN_A BIT0
#define PIN_B BIT1
#define PIN_C BIT2
#define PIN_D BIT3
#define PIN_E BIT4
#define PIN_F BIT5
#define PIN_G BIT6
// P2 pins
#define PIN_0 BIT0
#define PIN_1 BIT1
#define PIN_2 BIT2
#define PIN_3 BIT3

unsigned int timer_count = 0;
unsigned int score = 0;
unsigned int errors = 0;

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

void update_score() {
	enable_lcd_write();
	prints("Score:");
	integerToLcd(score);
	prints(" | ");
	prints("Er:");
	integerToLcd(errors);
	gotoXy(0,1);
	prints("Tecle a nota");
}

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; // disable WDT

	enable_lcd_write();
	prints("Vamos começar?");
	gotoXy(0,1);
	prints("Tecle algo!");

	enable_btn();

	P2DIR |= BIT0;
//	P1DIR |= (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G);
//	P1OUT = 0;
//	P2OUT = 0;
//
//	P2DIR |= (PIN_0 | PIN_1 | PIN_2 | PIN_3);
//	P2OUT = 0;

	configure_timer_a();


	__enable_interrupt(); // enable all interrupts
}

/*
 * Syntax of interruptions used in code composer
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	timer_count = (TAR % LIMIT); // found a value between 0 to LIMIT

	beep(notes[timer_count], 500); // play an random note

	score++;

	update_score();

	enable_btn();
 	/*
 	 * Above instructions should be runned after any logic
	 * According documentation, if this flags are not setted to 0,
	 * the interrupts stay peding.
	 */
	P1IFG &= ~BTN; // P1.3 IFG cleared
}
