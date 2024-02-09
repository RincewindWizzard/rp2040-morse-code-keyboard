//
// Created by dfl on 09.02.24.
//

#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>

const int led = 2;
const int MORSE_KEY_PIN = 29;

struct Event
{
    unsigned long duration;
    PinStatus status;
};

void input_morse_key();
void on_event(Event event);
#endif //MAIN_H
