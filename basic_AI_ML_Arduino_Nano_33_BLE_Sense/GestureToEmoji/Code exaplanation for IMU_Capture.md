# **The code explanation of the IMU_Capture.ino sketch :**

## **Objective:**

The objective of the code is to harness the capabilities of the **Arduino Nano 33 BLE Sense** microcontroller, along with the **BMI270 accelerometer and BMM150 magnetometer** sensors, to develop a robust motion detection system. By monitoring changes in acceleration and gyroscope readings, the system identifies significant motion events. It employs a threshold-based logic to detect motion intensity, ensuring that only substantial movements trigger data capture. 

Once motion is detected, the system continuously captures sensor data and outputs it in CSV format over the serial port. This structured output facilitates easy parsing and analysis, making the system adaptable for various applications such as activity tracking, gesture recognition, or motion-triggered events in IoT scenarios. Overall, the code aims to provide a versatile and reliable solution for motion detection, leveraging the Arduino platform and IMU sensors to meet the needs of diverse projects and applications.

## **Step-by-Step Explanation:**

- ### Initialization:
  - Serial communication is initiated with a `baud rate of 9600`.
  - The code waits for the serial port to become available.
  - The IMU (Inertial Measurement Unit) sensor module is initialized using the `IMU.begin()` function. If initialization fails, the code enters an infinite loop, indicating an error.
- ### Main Loop:
  - The main loop continuously runs and monitors the sensor data for significant motion events.
- ### Motion Detection:
  - The code waits for a predefined number of acceleration samples (`numSamples`) that exceed a specified threshold value (`accelerationThreshold`). This threshold represents significant motion, such as sudden acceleration changes.
  - Once significant motion is detected, the system proceeds to capture sensor data.
- ### Data Capture:
  - Within the loop, the code checks if new acceleration and gyroscope data are available from the IMU sensor module.
  - Upon availability, it reads the acceleration and gyroscope data using the `IMU.readAcceleration()` and `IMU.readGyroscope()` functions.
  - For each sample, the code prints the data in CSV format over the serial port. The data includes **acceleration along the X, Y, and Z axes** (`aX`, `aY`, `aZ`), as well as **gyroscope readings along the X, Y, and Z axes** (`gX`, `gY`, `gZ`).
  - Once all samples are read, an empty line is printed to separate the data sets.
- ### Significant Motion Detection Logic:
  - The significant motion detection logic is based on the sum of the absolute values of the acceleration components (`aSum`). If this sum exceeds the defined threshold (`accelerationThreshold`), it indicates significant motion, and the system starts capturing sensor data.

Overall, the code facilitates motion detection by monitoring acceleration and gyroscope data from the IMU sensor module. When significant motion is detected, it captures and outputs the sensor data for further analysis or application-specific tasks.

## **Code:**
```c
#include <Arduino_BMI270_BMM150.h>

const float accelerationThreshold = 2.5; // threshold of significant in G's
const int numSamples = 119;

int samplesRead = numSamples;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // wait for significant motion
  while (samplesRead == numSamples) {
    if (IMU.accelerationAvailable()) {
      // read the acceleration data
      IMU.readAcceleration(aX, aY, aZ);

      // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
    }
  }

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {
    // check if both new acceleration and gyroscope data is
    // available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      samplesRead++;

      // print the data in CSV format
      Serial.print(aX, 3);
      Serial.print(',');
      Serial.print(aY, 3);
      Serial.print(',');
      Serial.print(aZ, 3);
      Serial.print(',');
      Serial.print(gX, 3);
      Serial.print(',');
      Serial.print(gY, 3);
      Serial.print(',');
      Serial.print(gZ, 3);
      Serial.println();

      if (samplesRead == numSamples) {
        // add an empty line if it's the last sample
        Serial.println();
      }
    }
  }
}
```