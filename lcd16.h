/*
 *  Created on: Dec 1, 2011
 *      Author: Gaurav www.circuitvalley.com
 *
 *  Modified by: Phelipe Wener
 *
 *	Table of inputs to this lib work:
 *	VSS - GND
 *	VDD - 5V with potentiometer
 *	VO - GND
 *	RS - P1.7
 *	RW - GND
 *	E - P1.6
 *	D4 - P1.0
 *	D5 - P1.1
 *	D6 - P1.2
 *	D7 - P1.3
 *	A - 5v
 *	K - GND
 */
#ifndef LCD16_H_
#define LCD16_H_

#include <msp430g2553.h>

#define  EN BIT6
#define  RS BIT7

void waitlcd(unsigned int x);

void enable_lcd_write(void);
void integerToLcd(int integer);
void lcdData(unsigned char l);
void prints(char *s);
void gotoXy(unsigned char x, unsigned char y);

#endif
