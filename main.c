#include <msp430g2553.h>
#include "lcd16.h"
#include "util.h"
#include "music.h"

// P2 pins
#define PIN_0 BIT0
#define PIN_1 BIT1
#define PIN_2 BIT2
#define PIN_3 BIT3

unsigned int sorted_note = 0;
unsigned int score = 0;
unsigned int errors = 0;
unsigned int is_running = 0;

void update_score() {
	enable_lcd_write();

	// prints a unique line
	gotoXy(0,0);
	prints("Score:");
	integerToLcd(score);
	gotoXy(0,1);
	prints("Erros:");
	integerToLcd(errors);
}

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; // disable WDT

	enable_lcd_write();
	prints("Vamos começar?");
	gotoXy(0,1);
	prints("  tecle algo!");

	enable_btn();

	configure_timer_a();

	__enable_interrupt(); // enable all interrupts
}

/*
 * Syntax of interruptions used in code composer
 */
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
	int note = note_played();

	if(!is_running) {
		is_running = 1;
		// game initiate
	} else {
		if(note == sorted_note) {
			score++;
		} else {
			errors++;
		}
	}

	sorted_note = (TAR % LIMIT); // found a value between 0 to LIMIT

	beep(notes[sorted_note], 500); // play an random note

	update_score();

	enable_btn();
 	/*
 	 * Above instructions should be runned after any logic
	 * According documentation, if this flags are not setted to 0,
	 * the interrupts stay peding.
	 */
	P2IFG &= ~(BIT0 + BIT1 + BIT2); // P2.x IFG cleared
}
