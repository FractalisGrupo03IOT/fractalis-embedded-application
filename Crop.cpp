#include "Crop.h"

Crop::Crop(int id, uint8_t tempPin, uint8_t humPin, uint8_t sunPin, uint8_t lcdAddr)
  : cropId(id), tempSensor(tempPin), humSensor(humPin), sunSensor(sunPin), lcd(lcdAddr, 16, 2) {}

void Crop::begin() {
  tempSensor.begin();
  humSensor.begin();
  sunSensor.begin();
  lcd.init();
  lcd.backlight();
}

void Crop::updateSensors() {
  temperature = tempSensor.readTemperature();
  humidity = humSensor.readHumidity();
  sunlight = sunSensor.readSunlight();
}

void Crop::displayData() {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C  ");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

  lcd.setCursor(8, 1);
  lcd.print("Sun: ");
  lcd.print(sunlight);
  lcd.print(" UV");
}

int Crop::getCropId() {
  return cropId;
}

float Crop::getTemperature() {
  return temperature;
}

float Crop::getHumidity() {
  return humidity;
}

float Crop::getSunlight() {
  return sunlight;
}
