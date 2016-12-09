/*
 * music.c
 *
 *  Created on: 07/12/2016
 *      Author: Wener
 */
#include "music.h"

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
        P2OUT |= BIT0;     //Set P2.1...
        delay_us(delay);   //...for a semiperiod...
        P2OUT &= ~BIT0;    //...then reset it...
        delay_us(delay);   //...for the other semiperiod.
    }
    delay_ms(500); // Add a little delay to separate the single notes
}
