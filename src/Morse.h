//
// Created by dfl on 09.02.24.
//

#ifndef MORSE_H
#define MORSE_H
#include "main.h"

const int DIT_LEN = 100;
const int DAH_LEN = 3 * DIT_LEN;
const int PAUSE_SHORT_LEN = DIT_LEN;
const int PAUSE_LONG_LEN = DAH_LEN;

enum MorseSymbol
{
    DIT,
    DAH,
    PAUSE_SHORT,
    PAUSE_LONG,
    None
};

MorseSymbol parse_morse_symbol(Event event);
String toString(MorseSymbol symbol);

class Morse
{
private:
};


#endif //MORSE_H
