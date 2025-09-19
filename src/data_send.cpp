#include "data_send.h"

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
WiFiMulti wifiMulti;
Point lightIntensityPoint("light_intensity");
Point temperaturePoint("temperature");
Point pressurePoint("pressure");
Point humidityPoint("humidity");
Point soilMoisturePoint("soil_moisture");
Point stripBrightnessPoint("strip_brightness");

void setupWifi() {
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
    
    Serial.print("Connecting to wifi");
    while (wifiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Accurate time is necessary for certificate validation and writing in batches
    // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
    // Syncing progress and the time will be printed to Serial.
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
    
    
    // Check server connection
    if (client.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(client.getServerUrl());
        digitalWrite(LED_PIN, HIGH); // Turn on the LED to indicate successful connection
    } else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }
}

void createTags(Point point, String device, String sensor, String location) {
    point.addTag("device", device);
    point.addTag("sensor", sensor);
    point.addTag("location", location);
}

void createAndSendFields(Point point, String fieldName, float value) {
    // Clear fields for reusing the point. Tags will remain the same as set above.
    point.clearFields();
    
    point.addField(fieldName, value);

    // Print what are we exactly writing
    Serial.print("Writing: ");
    Serial.println(point.toLineProtocol());
  
    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }
  
    // Write point
    if (!client.writePoint(point)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }
  
    Serial.println("Waiting 1 second");
    delay(100);
}

void sendPoint() {

}