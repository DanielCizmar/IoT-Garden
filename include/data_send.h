#ifndef DATA_SEND_H
#define DATA_SEND_H

#include "garden_control.h"

#if defined(ESP32)
  #include <WiFiMulti.h>
  extern WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
  #elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif
  
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
  
// WiFi AP SSID
#define WIFI_SSID "Mariana smart"
// WiFi password
#define WIFI_PASSWORD "95181394"
  
#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "uJdenT4lK2AuTLUJuZfy6Cs1mk6S9Lbfw9Iybu9MqJ5Tz-9R_Xl0t7A23j0azagYUdagnv4FCA-dIl_C9aUtFA=="
#define INFLUXDB_ORG "ea4d92235ee20b80"
#define INFLUXDB_BUCKET "TestBucket"
  
// Time zone info
#define TZ_INFO "UTC2"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
extern InfluxDBClient client;
extern Point lightIntensityPoint;
extern Point temperaturePoint;
extern Point pressurePoint;
extern Point humidityPoint;
extern Point soilMoisturePoint;
extern Point stripBrightnessPoint;

#define LED_PIN 4
#define LOCATION "Garden"

void setupWifi();

void createTags(Point, String, String, String);

void createAndSendFields(Point, String, float);

void sendPoint();

#endif