#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>

class TemperatureSensor {
  public:
    TemperatureSensor(uint8_t pin);
    void begin();
    float readTemperature();
    
  private:
    uint8_t sensorPin;
};

#endif