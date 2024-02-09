//
// Created by dfl on 09.02.24.
//

#include "Morse.h"
#include "main.h"

MorseSymbol parse_morse_symbol(Event event)
{

    if (event.status == HIGH)
    {
        int threshold = (DAH_LEN - DIT_LEN) / 2 + DIT_LEN;
        if (event.duration < threshold)
        {
            return DIT;
        }
        else
        {
            return DAH;
        }
    }
    else
    {
        int threshold = (PAUSE_LONG_LEN - PAUSE_SHORT_LEN) / 2 + PAUSE_SHORT_LEN;
        if (event.duration < PAUSE_SHORT_LEN)
        {
            return None;
        }
        else if (event.duration < threshold)
        {
            return None;
        }
        else
        {
            return PAUSE_LONG;
        }
    }
    return DIT;
}

String toString(MorseSymbol symbol)
{
    switch (symbol)
    {
    case DIT: return ".";
    case DAH: return "-";
    case PAUSE_SHORT: return " ";
    case PAUSE_LONG: return "  ";
    }
}
