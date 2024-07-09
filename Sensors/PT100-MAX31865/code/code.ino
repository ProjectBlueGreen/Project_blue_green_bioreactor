#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 max31865 = Adafruit_MAX31865(D8, D7, D6, D5);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);
  Serial.println("Starting MAX31865 Test");

  if (!max31865.begin(MAX31865_2WIRE)) {
    Serial.println("Could not initialize MAX31865. Check wiring.");
    while (1) delay(10);
  } else {
    Serial.println("MAX31865 initialized successfully.");
  }
}

void loop() {
  uint16_t rtd = max31865.readRTD();
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("RTD value: "); Serial.println(rtd);
  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  Serial.print("Temperature = "); Serial.println(max31865.temperature(RNOMINAL, RREF));

  delay(1000);
}
