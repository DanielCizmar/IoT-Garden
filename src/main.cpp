#include <Arduino.h>
#include "garden_control.h"
#include "led_strip.h"

void setup() {

  Serial.begin(115200);
  initSensors();
  setupLEDStrip();
  setWhiteColor();
}

void loop() {
  displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  setBrightnessFromPot();
  Serial.print("Brightness: ");
  Serial.println(analogRead(POT_PIN));
  Serial.println("----------------------");
  delay(100);
}
