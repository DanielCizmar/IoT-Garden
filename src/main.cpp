#include <Arduino.h>
#include "garden_control.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  initSensors();
  
  displaySoilMoisture();
  displayLightIntensity();
  delay(1000);
  
}
