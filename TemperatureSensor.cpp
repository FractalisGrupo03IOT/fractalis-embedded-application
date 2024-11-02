#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t pin) : sensorPin(pin) {}

void TemperatureSensor::begin() {
  pinMode(sensorPin, INPUT);
}

float TemperatureSensor::readTemperature() {
  int analogValue = analogRead(sensorPin);
  float voltage = analogValue * (3.3 / 4095.0);
  float temperature = (voltage * 165.0 / 3.3) - 40;
  return temperature;
}