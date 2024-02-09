#include <Arduino.h>
#include "main.h"

const int led = 2;
const int MORSE_KEY_PIN = 29;
const int DEBOUNCE_THRESHOLD = 50; // milliseconds

volatile Event last_event = {0, LOW};




void interruptServiceRoutine();

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(MORSE_KEY_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(MORSE_KEY_PIN), interruptServiceRoutine, CHANGE);


    Serial.begin(9600);
    Serial.println("Interrupt Example");
}

void loop()
{
    unsigned long last_update = 0;

    while (true)
    {
        while (last_event.instant == last_update);
        digitalWrite(led, !last_event.status);
        Serial.print(last_event.instant);
        Serial.print("\t");
        Serial.println(last_event.instant-last_update);
        last_update = last_event.instant;
    }
}


void interruptServiceRoutine()
{
    unsigned long now = millis();
    if (now - last_event.instant > DEBOUNCE_THRESHOLD)
    {
        last_event.instant = now;
        last_event.status = digitalRead(MORSE_KEY_PIN);
    }
}
