#include "PluggableUSBHID.h"
#include "USBMouse.h"
#include <Arduino_LSM9DS1.h>

USBMouse mouse;

void setup() {
  IMU.begin();
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    mouse.move(x, y);
  }
}