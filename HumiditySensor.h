#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#include <Arduino.h>

class HumiditySensor {
  public:
    HumiditySensor(uint8_t pin);
    void begin();
    float readHumidity();
    
  private:
    uint8_t sensorPin;
};

#endif