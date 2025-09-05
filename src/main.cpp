#include <Arduino.h>
#include "garden_control.h"
#include "led_strip.h"

void setup() {

  Serial.begin(9600);
  initSensors();
  setupLEDStrip();
  setWhiteColor();
}

void loop() {
  displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  Serial.println("----------------------");
  delay(2000);
}
