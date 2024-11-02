#include "SunlightSensor.h"

SunlightSensor::SunlightSensor(uint8_t pin) : sensorPin(pin) {}

void SunlightSensor::begin() {
  pinMode(sensorPin, INPUT);
}

float SunlightSensor::readSunlight() {
  float ldrValue = analogRead(sensorPin);
  float normalizedValue = 32 + (4063 - ldrValue);
  float uvIntensity = map(normalizedValue, 32, 4063, 0, 5000);
  return uvIntensity;
}