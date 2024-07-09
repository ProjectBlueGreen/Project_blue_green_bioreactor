# PT100-MAX31865_temperature_sensor

# ESP8266 with MAX31865 and PT100 Temperature Logging

This project demonstrates how to use an ESP8266 microcontroller with a MAX31865 amplifier to read temperature data from a PT100 sensor. The data is logged and displayed using the Serial Monitor.

![Progress Badge](https://badgen.net/badge/progress/DONE/green?icon=github)

## Hardware Required

- ESP8266
- MAX31865 (2/3/4-wire configuration)
- PT100 sensor
- Jumper wires

## Wiring

### MAX31865 to PT100 (Two Wires)
- Connect one wire of the PT100 to `RTD+` on the MAX31865.
- Connect the other wire of the PT100 to `RTD-` on the MAX31865.
- Connect a jumper between `RTD-` and `F-`.

### MAX31865 to ESP8266
- `VIN` to `3.3V/5V` on the ESP8266
- `GND` to `GND` on the ESP8266
- `CLK` to `D5` on the ESP8266
- `SDO` to `D6` on the ESP8266
- `SDI` to `D7` on the ESP8266
- `CS` to `D8` on the ESP8266

## Software Setup

1. Install the Adafruit MAX31865 library:
   - Open the Arduino IDE
   - Go to Sketch -> Include Library -> Manage Libraries...
   - Search for "Adafruit MAX31865" and install it
