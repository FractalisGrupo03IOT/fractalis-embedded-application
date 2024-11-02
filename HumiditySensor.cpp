#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(uint8_t pin) : sensorPin(pin) {}

void HumiditySensor::begin() {
  pinMode(sensorPin, INPUT);
}

float HumiditySensor::readHumidity() {
  int analogValue = analogRead(sensorPin);
  float voltage = analogValue * (3.3 / 4095.0);
  float humidity = voltage * (100.0 / 3.3);
  return humidity;
}