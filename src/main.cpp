#include <Arduino.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include "DebugLED.h"
#include "USBKeyboard.h"
#include "MorseDecoder.h"


constexpr int MORSE_KEY_PIN = 29;
Bounce2::Button button = Bounce2::Button();
Adafruit_NeoPixel pixels(1, 16, NEO_GRB + NEO_KHZ800);

DebugLED debug(&pixels);

USBKeyboard keyboard;

void on_char(char c);
void on_symbol(Symbol symbol);
void on_fail();

MorseDecoder morse_decoder(&on_symbol, &on_char, &on_fail);

void setup()
{
    button.attach(MORSE_KEY_PIN, INPUT_PULLUP);
    button.interval(5);
    button.setPressedState(HIGH);

    pixels.begin();
    pixels.show();


    Serial.begin(9600);
    Serial.println("Interrupt Example");
    debug.okay();
}


void loop()
{
    button.update();
    morse_decoder.update();
    // debug.okay();
    if (button.pressed())
    {
        debug.clear();
        morse_decoder.released(button.previousDuration());
    }
    if (button.released())
    {
        debug.clear();
        morse_decoder.pressed(button.previousDuration());
    }
    if (!button.isPressed() && button.currentDuration() > morse_decoder.get_timeout())
    {
        morse_decoder.timeout();
    }
}

void on_symbol(Symbol symbol)
{
    Serial.print(symbol_to_char(symbol));
}

void on_char(char c)
{
    // qwerty, dont ask me....
    if(c == 'y')
    {
        c = 'z';
    }
    if(c == 'z')
    {
        c = 'y';
    }
    //-----------------------

    if (c != '\t')
    {
        keyboard.printf("%c", c);
    }
    else
    {
        keyboard.printf("  ");
    }
}

void on_fail()
{
    debug.set_error();
}
