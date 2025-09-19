#include <Arduino.h>
#include "garden_control.h"
#include "led_strip.h"
#include "data_send.h"

// Declare Data point 
Point sensor("wifi_status");
Point lightIntensityPoint("light_intensity");

void setup() {

  Serial.begin(9600);

  setupWifi();
 
  // ???????????????????????????????????????????????????????????????????????????????????????????
 sensor.addTag("device", DEVICE);
 sensor.addTag("SSID", WiFi.SSID());
  lightIntensityPoint.addTag("device", DEVICE);
  lightIntensityPoint.addTag("sensor", "GY-302");

  initSensors();
  setupLEDStrip();
  setWhiteColor();
}

void loop() {
  //
  
  // Clear fields for reusing the point. Tags will remain the same as set above.
    sensor.clearFields();
  
    // Store measured value into point
    // Report RSSI of currently connected network
    sensor.addField("rssi", WiFi.RSSI());
  
    // Print what are we exactly writing
    Serial.print("Writing: ");
    Serial.println(sensor.toLineProtocol());
  
    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }
  
    // Write point
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  //
    // Clear fields for reusing the point. Tags will remain the same as set above.
    lightIntensityPoint.clearFields();
  
    // Store measured value into point
    // Report RSSI of currently connected network
    lightIntensityPoint.addField("light_intensity", readLightIntensity());
  
    // Print what are we exactly writing
    Serial.print("Writing: ");
    Serial.println(lightIntensityPoint.toLineProtocol());
  
    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }
  
    // Write point
    if (!client.writePoint(lightIntensityPoint)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  
    Serial.println("Waiting 1 second");
    delay(1000);

  //

  
  displaySoilMoisture();
  displayLightIntensity();
  displayBME280Data();
  setBrightnessFromPot();
  Serial.print("Brightness: ");
  Serial.println(analogRead(POT_PIN));
  Serial.println("----------------------");
  delay(100);
}
