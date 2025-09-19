#include <Arduino.h>
#include "garden_control.h"
#include "led_strip.h"
#include "data_send.h"

void setup() {
  
  Serial.begin(9600);
  initSensors();
  setupLEDStrip();
  setWhiteColor();
  
  setupWifi();
  
  createTags(lightIntensityPoint, DEVICE, SENSOR1, LOCATION);
  createTags(temperaturePoint, DEVICE, SENSOR2, LOCATION);
  createTags(pressurePoint, DEVICE, SENSOR2, LOCATION);
  createTags(humidityPoint, DEVICE, SENSOR2, LOCATION);
  createTags(soilMoisturePoint, DEVICE, SENSOR3, LOCATION);
  createTags(stripBrightnessPoint, DEVICE, "LED_STRIP", LOCATION);
}

void loop() {

  createAndSendFields(lightIntensityPoint, "light_intensity", readLightIntensity());
  createAndSendFields(temperaturePoint, "temperature", readTemperature());
  createAndSendFields(pressurePoint, "pressure", readPressure());
  createAndSendFields(humidityPoint, "humidity", readHumidity());
  createAndSendFields(soilMoisturePoint, "soil_moisture", readSoilMoisture());
  createAndSendFields(stripBrightnessPoint, "strip_brightness", getBrightnessFromPot());
  
  displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  setBrightnessFromPot();
  Serial.print("Brightness: ");
  Serial.println(analogRead(POT_PIN));
  Serial.println("----------------------");
  delay(100);
}
