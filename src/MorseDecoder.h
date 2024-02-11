//
// Created by dfl on 11.02.24.
//

#ifndef MORSEDECODER_H
#define MORSEDECODER_H
#include <ctime>
#include <MorseDecoder.h>
#include <vector>


enum Status
{
    OFF,
    ON
};

struct Event
{
    time_t instant;
    Status status;
};

enum class Symbol
{
    DIT,
    DAH,
    PAUSE,
    PAUSE_LONG,
    NONE
};

#define MORSE_CODE_MAX_LEN 5

struct MorseCodePoint
{
    char c;
    Symbol symbols[MORSE_CODE_MAX_LEN];
};

#define MORSE_CODE_TABLE_SIZE 36

extern MorseCodePoint MORSE_CODE_TABLE[];


char symbol_to_char(Symbol symbol);

using OnSymbolCb = void (*)(Symbol);
using OnCharCb = void (*)(char);

class MorseDecoder
{
private:
    std::vector<Symbol> symbol_buffer;
    OnSymbolCb on_symbol;
    OnCharCb on_char;
    time_t dit_duration = 120;

    time_t dit_dah_threshold()
    {
        return (get_dah_duration() - get_dit_duration()) / 2 + get_dit_duration();
    }

    Symbol parse_symbol(Status status, time_t duration)
    {
        if (status == Status::ON)
        {
            if (duration < dit_dah_threshold())
            {
                return Symbol::DIT;
            }
            else
            {
                return Symbol::DAH;
            }
        }
        else if (status == Status::OFF)
        {
            if (duration < get_dit_duration())
            {
                return Symbol::NONE;
            }
            else if (duration < dit_dah_threshold())
            {
                return Symbol::PAUSE;
            }
            else
            {
                return Symbol::PAUSE_LONG;
            }
        }
        return Symbol::NONE;
    }

    char parse_char(std::vector<Symbol> symbol_buffer)
    {
        if (symbol_buffer.size() > MORSE_CODE_MAX_LEN)
        {
            return 0;
        }
        for (int i = 0; i < MORSE_CODE_TABLE_SIZE; i++)
        {
            MorseCodePoint code_point = MORSE_CODE_TABLE[i];
            bool matches = code_point.symbols[symbol_buffer.size()] == Symbol::NONE;
            for (unsigned int j = 0; j < symbol_buffer.size() && matches; j++)
            {
                matches &= symbol_buffer[j] == code_point.symbols[j];
            }
            if (matches)
            {
                return code_point.c;
            }
        }
        return 0;
    }

public:
    explicit MorseDecoder(OnSymbolCb on_symbol, OnCharCb on_char) : on_symbol(on_symbol), on_char(on_char)
    {
    }

    time_t get_dah_duration()
    {
        return dit_duration * 3;
    }

    time_t get_dit_duration()
    {
        return dit_duration;
    }

    time_t get_timeout()
    {
        return get_dah_duration() * 2;
    }

    void update()
    {
    }

    void pressed(time_t duration)
    {
        Symbol symbol = parse_symbol(Status::ON, duration);
        if (symbol != Symbol::NONE)
        {
            symbol_buffer.push_back(symbol);
            on_symbol(symbol);
        }
    }

    void released(time_t duration)
    {
        Symbol symbol = parse_symbol(Status::OFF, duration);
        if (symbol != Symbol::NONE)
        {
            char c = parse_char(symbol_buffer);
            symbol_buffer.clear();
            on_symbol(symbol);
            if (c != 0)
            {
                on_char(c);
            }
        }
    }

    void timeout()
    {
        char c = parse_char(symbol_buffer);
        symbol_buffer.clear();
        if (c != 0)
        {
            on_char(c);
        }
    }
};

#endif //MORSEDECODER_H
