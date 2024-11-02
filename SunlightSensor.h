#ifndef SUNLIGHT_SENSOR_H
#define SUNLIGHT_SENSOR_H

#include <Arduino.h>

class SunlightSensor {
  public:
    SunlightSensor(uint8_t pin);
    void begin();
    float readSunlight();

  private:
    uint8_t sensorPin;
};

#endif