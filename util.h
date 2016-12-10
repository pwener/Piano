#ifndef UTIL_H
#define UTIL_H

#include <msp430g2553.h>

#define BTN BIT3

void delay_ms(unsigned int ms );
void delay_us(unsigned int us );
void enable_btn(void);
void configure_timer_a(void);
int note_played(void);

#endif
