//
// Created by dfl on 11.02.24.
//


#ifndef DEBUG_H
#define DEBUG_H
#include <Adafruit_NeoPixel.h>

class DebugLED
{
private:
    Adafruit_NeoPixel* pixels;

public:
    DebugLED(Adafruit_NeoPixel* pixels) : pixels(pixels)
    {
    }

    void blink(uint32_t color, time_t interval, uint32_t n)
    {
        for (uint32_t i = 0; i < n; ++i)
        {
            pixels->setPixelColor(0, color);
            pixels->show();
            delay(interval);

            clear();
            delay(interval);
        }
    }

    void okay()
    {
        blink(Adafruit_NeoPixel::Color(0, 255, 0), 300, 3);
    }

    void info()
    {
        blink(Adafruit_NeoPixel::Color(0, 0, 255), 300, 3);
    }

    void error()
    {
        blink(Adafruit_NeoPixel::Color(255, 0, 0), 300, 3);
    }

    void set_error()
    {
        pixels->setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
        pixels->show();
    }

    void clear()
    {
        pixels->setPixelColor(0, Adafruit_NeoPixel::Color(0, 0, 0));
        pixels->show();
    }
};


#endif //DEBUG_H
