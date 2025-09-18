#ifndef LED_STRIP_CPP
#define LED_STRIP_CPP

#define LED_STRIP_PIN 5
#define NUM_LEDS 30 // Number of LEDs on strip
#define POT_PIN 34

void setupLEDStrip();

void setWhiteColor();

void setBrightnessFromPot();

void noColor();

#endif