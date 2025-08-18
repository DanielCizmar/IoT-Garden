#include "garden_control.h"
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter(0x23);

void initSensors() {
    Wire.begin();
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
}

int readSoilMoisture() {
    int moistureValue = analogRead(SOIL_MOISTURE_PIN);
    return map(moistureValue, 0, 4095, 100, 0);
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
float readLightIntensity() {
    float lux = lightMeter.readLightLevel();
    if (lux < 0) {
        Serial.println("Error reading light intensity");
        return 0;
    }
    return lux;
}

void displayLightIntensity() {
    if (Serial.available()) {
        float lightIntensity = readLightIntensity();
        Serial.print("Light Intensity: ");
        Serial.print(lightIntensity);
        Serial.println(" lux");
    }
}