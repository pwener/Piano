#include <msp430g2553.h>
#include "lcd16.h"
#include "util.h"
#include "music.h"

unsigned int sorted_note = 0;  // note sorted between 0, 6
unsigned int score = 0; // points scored
unsigned int errors = 0; // errors scored
unsigned int is_running = 0; // if game is running, change to 1

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; // disable WDT

	enable_lcd_write();
	prints("Vamos começar?");
	gotoXy(0,1); // go to second line
	prints("  tecle algo!");

	enable_btn(); // now P2.x is able to catch an interruption

	configure_timer_a();

	__enable_interrupt(); // enable all interrupts, if we need others
}

/*
 * Syntax of interruptions used into code composer.
 * The logic in follow runs the game after each p2.x click.
 */
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
	int note = note_played();

	if(!is_running) {
		// game initiate
		is_running = 1;
	} else {
		if(note == sorted_note) {
			score++;
		} else {
			errors++;
		}
	}

	sorted_note = (TAR % LIMIT); // found a value between 0 to LIMIT

	beep(notes[sorted_note], 500); // play the random note

	update_score(); // update display score

	enable_btn(); // wait again the interruptions

 	/*
 	 * Above instructions should be runned after any logic
	 * According documentation, if this flags are not setted to 0,
	 * the interrupts stay peding.
	 */
	P2IFG &= ~(BIT0 + BIT1 + BIT2); // P2.x IFG cleared
}
