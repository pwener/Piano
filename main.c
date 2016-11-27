#include <msp430g2553.h>

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

#define BTN BIT3

// Frequency of each notes
#define C_NOTE 261
#define D_NOTE 294
#define E_NOTE 329
#define F_NOTE 349
#define G_NOTE 391
#define A_NOTE 440
#define B_NOTE 466
#define CMajor_NOTE 522

// Quantity of notes
#define LIMIT 8

const static int notes[LIMIT] = {C_NOTE, D_NOTE, E_NOTE, F_NOTE, G_NOTE, A_NOTE, B_NOTE, CMajor_NOTE};

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
 * Code based on: http://processors.wiki.ti.com/index.php/Playing_The_Imperial_March
 * This function generates the square wave that makes the piezo
 * speaker sound at a determinated frequency.
 *
 * @duration milliseconds metric
 */
void beep(unsigned int note, unsigned int duration) {
    int i;
    // delay = 1000/c * 1/t
    long delay = (long)(10000/note);  // This is the semiperiod of each note.
    // duration is divided by 20xdelay
    long time = (long)((duration*100)/(delay*2));  //This is how much time we need to spend on the note.
    for (i=0; i<time; i++) {
        P1OUT |= BIT2;     //Set P1.2...
        delay_us(delay);   //...for a semiperiod...
        P1OUT &= ~BIT2;    //...then reset it...
        delay_us(delay);   //...for the other semiperiod.
    }
    delay_ms(500); // Add a little delay to separate the single notes
}

void main(void) {
	WDTCTL = WDTPW + WDTHOLD; // disable WDT
	P1IE |= BTN; // P1.3 interrupt enabled
	P1IES |= BIT3; // P1.3 Hi/lo edge
	P1IFG &= ~BTN; // P1.3 IFG cleared
	P1REN |= BTN; // Enable resistor on BTN

	P1DIR |= BIT2;
	P1DIR |= (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G);
	P1OUT = 0;
	P2OUT = 0;

	P2DIR |= (PIN_0 | PIN_1 | PIN_2 | PIN_3);
	P2OUT = 0;

	BCSCTL1 = CALBC1_1MHZ; // configure time A source clk
	DCOCTL = CALDCO_1MHZ; // configure digital oscilator clk

	TACTL = TASSEL_2 + MC_3 + ID_3; // configure Timer A
	TACCR0 = 10;
	_BIS_SR(LPM4_bits+GIE);

	__enable_interrupt(); // enable all interrupts

	while(1);
}

/*
 * Syntax of interruptions used in code composer
 */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
	timer_count = (TAR % LIMIT); // found a value between 0 to LIMIT

 	beep(notes[timer_count], 500); // play an random note

 	/*
 	 * Above instructions should be runned after any logic
	 * According documentation, if this flags are not setted to 0,
	 * the interrupts stay peding.
	 */
	P1IFG &= ~BTN; // P1.3 IFG cleared
}
