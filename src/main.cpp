#include <Arduino.h>
#include "garden_control.h"
#include <Adafruit_NeoPixel.h>

// https://www.nextpcb.com/blog/ultimate-guide-to-connecting-led-light-strips-to-arduino
// https://lastminuteengineers.com/esp32-wled-tutorial/

// Define pin and number of LEDs
#define LED_PIN 5        // Pin connected to the LED strip
#define NUM_LEDS 30      // Number of LEDs in your strip

// Create NeoPixel object
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Generate rainbow colors
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
// Rainbow cycle across entire strip
void rainbowCycle(int wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 256 / strip.numPixels() + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}



void setup() {
  
  Serial.begin(9600);
  initSensors();

  strip.begin();           // Initialize NeoPixel
  strip.show();            // Turn OFF all LEDs at startup
  strip.setBrightness(50); // Brightness (0-255)
}

void loop() {
  /*displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  Serial.println("----------------------");
  delay(2000);*/
  rainbowCycle(10);
}
