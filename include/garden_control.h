#ifndef GARDEN_CONTROL_H
#define GARDEN_CONTROL_H

#define SOIL_MOISTURE_PIN 16

// Initializes the sensors used in the garden control system.
void initSensors();

/** * Reads the soil moisture level.
 * 
 * This function reads the analog value from the SOIL_MOISTURE_PIN pin and returns it.
 * * @return The analog value read from the pin, representing the soil moisture level from 0 to 100.
 * */
int readSoilMoisture();

// Displays the soil moisture level on the LCD..
void displaySoilMoisture();

/** * Reads the light intensity.
 * 
 * This function reads the analog value from the light sensor pin and returns it.
 * @return The analog value read from the light sensor pin, representing the light intensity.
 * 
 * Približné hodnoty v luxoch:
 * Noc: < 0.2
 * Zamračené, v interiéri: ~100
 * Zamračené, v exteriéri: ~1000
 * Slnečno, v interiéri: ~1000
 * Slnečno v exteriéri: 10 000 – 100 000
 */
float readLightIntensity();

// Displays the light intensity.
void displayLightIntensity();

float readTemperature();

float readPressure();

float readHumidity();

void displayTemperature();

void displayPressure();

void displayHumidity();

void displayBME280Data();

#endif