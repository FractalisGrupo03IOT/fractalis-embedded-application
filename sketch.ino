#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include "Crop.h"

// Configura las credenciales de WiFi
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

#define DOMAIN "https://fractalies-edge-server.onrender.com/api/v1/crop/links"

// Pines de los sensores
#define TEMP_SENSOR_PIN 34
#define HUM_SENSOR_PIN 33
#define SUN_SENSOR_PIN 32
#define SERVO_PIN 25
#define I2C_ADDR 0x27

Crop crop(4, TEMP_SENSOR_PIN, HUM_SENSOR_PIN, SUN_SENSOR_PIN, I2C_ADDR);
Servo myServo;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  // Conectar al WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  crop.begin();
  myServo.attach(SERVO_PIN);
}

void loop() {
  crop.updateSensors();
  crop.displayData();

  float humidity = crop.getHumidity();
  if (humidity < 30) {
    myServo.write(90);
    Serial.println("Servo activado: 90 grados (Humedad baja)");
  } else if (humidity > 70) {
    myServo.write(0);
    Serial.println("Servo desactivado: 0 grados (Humedad alta)");
  }

  if (WiFi.status() == WL_CONNECTED) {
    // Verificar si el Crop ID es válido
    int cropId = crop.getCropId();
    if (cropId > 0) { // Asegura que el ID es válido
      sendTemperatureData(cropId, static_cast<int>(crop.getTemperature()));
      sendHumidityData(cropId, static_cast<int>(crop.getHumidity()));
      sendSunlightData(cropId, static_cast<int>(crop.getSunlight()));
    } else {
      Serial.println("Error: cropCloudId inválido.");
    }
  } else {
    Serial.println("WiFi desconectado");
  }

  delay(30000);
}

void sendTemperatureData(int cropId, int temperature) {
  HTTPClient http;
  String url = String(DOMAIN) + "/temperature";
  Serial.print("Enviando datos de temperatura a: ");
  Serial.println(url);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["cropCloudId"] = cropId;
  jsonDoc["temperature"] = temperature;

  String requestBody;
  serializeJson(jsonDoc, requestBody);
  Serial.print("Cuerpo de la solicitud (Temperature): ");
  Serial.println(requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode == 201 || httpResponseCode == 200) {
    Serial.print("Código de respuesta HTTP (Temperature): ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error en la solicitud (Temperature): ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendHumidityData(int cropId, int humidity) {
  HTTPClient http;
  String url = String(DOMAIN) + "/humidity";
  Serial.print("Enviando datos de humedad a: ");
  Serial.println(url);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["cropCloudId"] = cropId;
  jsonDoc["humidity"] = humidity;

  String requestBody;
  serializeJson(jsonDoc, requestBody);
  Serial.print("Cuerpo de la solicitud (Humidity): ");
  Serial.println(requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode == 201 || httpResponseCode == 200) {
    Serial.print("Código de respuesta HTTP (Humidity): ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error en la solicitud (Humidity): ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendSunlightData(int cropId, int sunlight) {
  HTTPClient http;
  String url = String(DOMAIN) + "/sunlight";
  Serial.print("Enviando datos de luz solar a: ");
  Serial.println(url);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["cropCloudId"] = cropId;
  jsonDoc["sunlight"] = sunlight;

  String requestBody;
  serializeJson(jsonDoc, requestBody);
  Serial.print("Cuerpo de la solicitud (Sunlight): ");
  Serial.println(requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode == 201 || httpResponseCode == 200) {
    Serial.print("Código de respuesta HTTP (Sunlight): ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error en la solicitud (Sunlight): ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
