//
// Created by sinnable on 6/19/20.
//

#ifndef UNTITLED_RANDOM_H
#define UNTITLED_RANDOM_H
#include "global.h"
#include <time.h>

extern double random_real(double lower, double higher);
extern void advance_random ();
extern void warmup_random (double seed);
extern void randomize ();
extern double randomperc ();
extern int rnd (int low, int high);
extern double rndreal (double low, double high);


#endif //UNTITLED_RANDOM_H
