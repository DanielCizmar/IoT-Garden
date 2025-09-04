#include "led_strip.h"
#include <Adafruit_NeoPixel.h>

// https://www.nextpcb.com/blog/ultimate-guide-to-connecting-led-light-strips-to-arduino
// https://lastminuteengineers.com/esp32-wled-tutorial/

Adafruit_NeoPixel strip(NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

void setupLEDStrip() {
    
    strip.begin();
    strip.show();
    strip.clear();
    strip.show();
    strip.setBrightness(50);
}

void setWhiteColor() {
    
    for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(220, 220, 220));
    }
    strip.show();
}

void noColor() {
    strip.clear();
    strip.show();
}