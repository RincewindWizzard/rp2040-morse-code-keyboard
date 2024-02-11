//
// Created by dfl on 11.02.24.
//

#ifndef MORSEDECODER_H
#define MORSEDECODER_H
#include <ctime>
#include <string>

enum Status
{
    RELEASED,
    PRESSED
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
    PAUSE_LONG
};

char symbol_to_char(Symbol symbol);

using OnSymbolCb = void (*)(Symbol);
using OnCharCb = void (*)(char);

class MorseDecoder
{
private:
    Event last_event =
    {
        0,
        RELEASED
    };
    OnSymbolCb on_symbol;
    OnCharCb on_char;

public:
    explicit MorseDecoder(OnSymbolCb on_symbol, OnCharCb on_char) : on_symbol(on_symbol), on_char(on_char)
    {
    }


    void update()
    {
    }

    void pressed(time_t duration)
    {
        on_symbol(Symbol::DIT);
        on_char('$');
    }

    void released(time_t duration)
    {
    }
};

#endif //MORSEDECODER_H
