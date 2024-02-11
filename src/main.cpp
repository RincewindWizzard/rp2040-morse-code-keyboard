#include <Arduino.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include "Debug.h"
#include "USBKeyboard.h"
#include "MorseDecoder.h"


constexpr int MORSE_KEY_PIN = 29;
Bounce2::Button button = Bounce2::Button();
Adafruit_NeoPixel pixels(1, 16, NEO_GRB + NEO_KHZ800);

Debug debug(&pixels);

USBKeyboard keyboard;

void on_char(char c);
void on_symbol(Symbol symbol);
MorseDecoder morse_decoder(&on_symbol, &on_char);

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

    // keyboard.printf("Hallo");
}


void loop()
{
    button.update();
    morse_decoder.update();
    // debug.okay();
    if (button.pressed())
    {
        morse_decoder.released(button.previousDuration());
    }
    if (button.released())
    {
        morse_decoder.pressed(button.previousDuration());
    }
}

void on_symbol(Symbol symbol)
{
    Serial.print(symbol_to_char(symbol));
}

void on_char(char c)
{
    if(c != '\t')
    {
        Serial.print(c);
    }
    else
    {
        Serial.print("  ");
    }
}

