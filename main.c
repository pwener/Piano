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

void
main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= (PIN_A | PIN_B | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G);
	P1OUT = 0;
	P2OUT = 0;

	P2DIR |= (PIN_0 | PIN_1 | PIN_2 | PIN_3);
	P2OUT = 0;

	for (;;) {
	}

	return 0;
}
