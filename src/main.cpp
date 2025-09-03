#include <Arduino.h>
#include "garden_control.h"
#include <Adafruit_NeoPixel.h>

// https://www.nextpcb.com/blog/ultimate-guide-to-connecting-led-light-strips-to-arduino
// https://lastminuteengineers.com/esp32-wled-tutorial/

#define LED_PIN 4   // change this to the GPIO pin you’re using
#define LED_COUNT 30

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t Wheel(uint8_t WheelPos);
void rainbowCycle(uint8_t wait);
void colorWipe(uint32_t color, uint8_t wait);
void theaterChase(uint32_t color, uint8_t wait);

void setup() {
  Serial.begin(9600);
  initSensors();

  strip.begin();           // Initialize strip
  strip.show();            // Turn OFF all LEDs at start
  strip.setBrightness(50); // Adjust brightness (0-255)
}

void loop() {
  /*displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  Serial.println("----------------------");
  delay(2000);*/

  rainbowCycle(5);
}

// Helper function: rainbow colors across all pixels
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value
// The colours are a transition r - g - b - back to r
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}