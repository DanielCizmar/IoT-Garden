#include <Arduino.h>
#include "garden_control.h"

// https://www.nextpcb.com/blog/ultimate-guide-to-connecting-led-light-strips-to-arduino
// https://lastminuteengineers.com/esp32-wled-tutorial/


void setup() {
  Serial.begin(9600);
  initSensors();


}

void loop() {
  displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  Serial.println("----------------------");
  delay(2000);
}
