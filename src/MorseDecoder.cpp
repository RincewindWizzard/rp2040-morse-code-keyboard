//
// Created by dfl on 11.02.24.
//
#include "MorseDecoder.h"


char symbol_to_char(Symbol symbol)
{
    switch (symbol)
    {
    case Symbol::DIT:
        return '.';
    case Symbol::DAH:
        return '-';
    case Symbol::PAUSE:
        return ' ';
    case Symbol::PAUSE_LONG:
        return '\t';
    default:
        return 0;
    }
}
