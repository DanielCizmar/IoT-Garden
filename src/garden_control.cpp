#include "garden_control.h"
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

BH1750 lightMeter(0x23);
Adafruit_BME280 bme;

void initSensors() {
    Wire.begin();
    
    // TODO: Check if the sensors are connected and initialized properly
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
    bme.begin(0x76); 
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

float readTemperature() {
    return bme.readTemperature();
}

float readPressure() {
    return bme.readPressure() / 100.0F; // Convert Pa to hPa
}  

float readHumidity() {
    return bme.readHumidity();
}

void displayTemperature() {
    if (Serial.available()) {
        float temperature = readTemperature();
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
    }  
}

void displayPressure() {
    if (Serial.available()) {
        float pressure = readPressure();
        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");
    }
}

void displayHumidity() {
    if (Serial.available()) {
        float humidity = readHumidity();
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
}

void displayBME280Data() {
    displayTemperature();
    displayPressure();
    displayHumidity();
}