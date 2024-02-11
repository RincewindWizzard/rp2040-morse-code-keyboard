#include <Arduino.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include "Debug.h"
#include "USBKeyboard.h"


constexpr int MORSE_KEY_PIN = 29;
Bounce2::Button button = Bounce2::Button();
Adafruit_NeoPixel pixels(1, 16, NEO_GRB + NEO_KHZ800);

Debug debug(&pixels);

USBKeyboard keyboard;

void setup()
{
    button.attach(MORSE_KEY_PIN, INPUT_PULLUP);
    button.interval(5);
    button.setPressedState(LOW);

    pixels.begin();
    pixels.show();


    Serial.begin(9600);
    Serial.println("Interrupt Example");
    debug.okay();
}


void loop()
{
    button.update();
    // debug.okay();
    if (button.pressed())
    {
        // keyboard.printf("Hallo");
        debug.info();
    }
}


// void loop()
// {
//     input_morse_key();
//
//     // for (const auto& symbol : symbols)
//     // {
//     //     Serial.print(toString(symbol));
//     // }
//     // Serial.println("");
// }

// void input_morse_key()
// {
//     button.update();
//     if (button.released())
//     {
//         on_event({
//             button.previousDuration(),
//             HIGH
//         });
//     }
//
//     if (button.pressed())
//     {
//         on_event({
//             button.previousDuration(),
//             LOW
//         });
//     }
// }
//
// void on_event(Event event)
// {
//     MorseSymbol symbol = parse_morse_symbol(event);
//     if (symbol != None)
//     {
//         Serial.print(toString(symbol));
//         symbols.push_back(symbol);
//         digitalWrite(led, event.status);
//     }
// }
