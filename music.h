#ifndef MUSIC_H
#define MUSIC_H

#include <msp430g2553.h>
#include "util.h"

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
#define LIMIT 7

const static int notes[LIMIT] = {C_NOTE, D_NOTE, E_NOTE, F_NOTE, G_NOTE, A_NOTE, B_NOTE};

void beep(unsigned int note, unsigned int duration);

#endif
