#include <Arduino.h>
#include "garden_control.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  displaySoilMoisture();
  delay(1000);

}
