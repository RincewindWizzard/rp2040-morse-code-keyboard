//
// Created by dfl on 11.02.24.
//
#include "MorseDecoder.h"

MorseCodePoint MORSE_CODE_TABLE[MORSE_CODE_TABLE_SIZE] = {
    {'1', {Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::DAH}},
    {'2', {Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::DAH}},
    {'3', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::DAH}},
    {'4', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DAH}},
    {'5', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DIT}},
    {'6', {Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DIT}},
    {'7', {Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::DIT}},
    {'8', {Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::DIT}},
    {'9', {Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::DIT}},
    {'a', {Symbol::DIT, Symbol::DAH, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'b', {Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::NONE}},
    {'c', {Symbol::DAH, Symbol::DIT, Symbol::DAH, Symbol::DIT, Symbol::NONE}},
    {'d', {Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::NONE, Symbol::NONE}},
    {'e', {Symbol::DIT, Symbol::NONE, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'f', {Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::DIT, Symbol::NONE}},
    {'g', {Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::NONE, Symbol::NONE}},
    {'h', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::NONE}},
    {'i', {Symbol::DIT, Symbol::DIT, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'j', {Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::NONE}},
    {'k', {Symbol::DAH, Symbol::DIT, Symbol::DAH, Symbol::NONE, Symbol::NONE}},
    {'l', {Symbol::DIT, Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::NONE}},
    {'m', {Symbol::DAH, Symbol::DAH, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'n', {Symbol::DAH, Symbol::DIT, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'o', {Symbol::DAH, Symbol::DAH, Symbol::DAH, Symbol::NONE, Symbol::NONE}},
    {'p', {Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::NONE}},
    {'q', {Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::DAH, Symbol::NONE}},
    {'r', {Symbol::DIT, Symbol::DAH, Symbol::DIT, Symbol::NONE, Symbol::NONE}},
    {'s', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::NONE, Symbol::NONE}},
    {'t', {Symbol::DAH, Symbol::NONE, Symbol::NONE, Symbol::NONE, Symbol::NONE}},
    {'u', {Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::NONE, Symbol::NONE}},
    {'v', {Symbol::DIT, Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::NONE}},
    {'w', {Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::NONE, Symbol::NONE}},
    {'x', {Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::DAH, Symbol::NONE}},
    {'y', {Symbol::DAH, Symbol::DIT, Symbol::DAH, Symbol::DAH, Symbol::NONE}},
    {'z', {Symbol::DAH, Symbol::DAH, Symbol::DIT, Symbol::DIT, Symbol::NONE}},
};

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
