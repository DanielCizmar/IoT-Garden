#include "garden_control.h"
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

int readSoilMoisture() {
    int moistureValue = analogRead(SOIL_MOISTURE_PIN);
    return map(moistureValue, 0, 4095, 0, 100);
}

void displaySoilMoisture() {
    if (Serial.available()) {
        int moisture = readSoilMoisture();
        Serial.print("Soil Moisture: ");
        Serial.print(moisture);
        Serial.println("%");
    }
}

// TODO: Implement the light sensor reading and display functions