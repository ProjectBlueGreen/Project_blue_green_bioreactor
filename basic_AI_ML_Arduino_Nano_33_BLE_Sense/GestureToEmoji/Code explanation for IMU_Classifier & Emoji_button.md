# **The code explanation of the IMU_classifier.ino and Emoji_button.ino sketch:**

## **Objective:**

The objective of the code is to create a gesture recognition system using an **Arduino Nano 33 BLE Sense** microcontroller equipped with the **BMI270 accelerometer** and **BMM150 magnetometer** sensors. The system detects and classifies gestures based on motion data collected from the sensors. It utilizes a TensorFlow Lite model to perform inference and identify gestures, providing real-time feedback over the serial port.

## **Step-by-Step Explanation:**

- ### Initialization:

  - Serial communication is initialized with a `baud rate of 9600`, enabling communication with an external device for data output.
  - The `BMI270 accelerometer` and `BMM150 magnetometer` sensors are initialized using the IMU library.
- ### Print Sensor Sample Rates:

  - The code prints the sample rates of the accelerometer and gyroscope sensors over the serial port. This information helps in understanding the timing and frequency of sensor data acquisition.

- ### TensorFlow Lite Model Initialization:

  - The TensorFlow Lite model is loaded into memory using the `tflite::GetModel()` function. This model is stored as a byte array and represents a trained machine learning model capable of recognizing gestures.
- ### Interpreter Creation and Memory Allocation:

  - A TensorFlow Lite interpreter is created to run the loaded model. It is initialized with the model, an operations resolver, and a memory buffer (`tensorArena`) for storing intermediate data during inference. Memory is allocated for input and output tensors of the model.

- ### Main Loop for Gesture Recognition:

  - The main loop continuously monitors sensor data for gesture recognition.
  - It waits for a predefined number of acceleration samples to exceed a specified threshold (`accelerationThreshold`). This threshold indicates significant motion, triggering the gesture recognition process.

- ### Data Capture and Normalization:

  - Once significant motion is detected, the loop captures acceleration and gyroscope data from the IMU sensors.
  - The captured data is normalized between 0 and 1 and stored in the input tensor of the TensorFlow Lite model. This ensures that the input data is within the expected range for the model.

- ### Inference and Gesture Classification:

  - After capturing the required number of samples, the code invokes the TensorFlow Lite interpreter to perform inference.
  - The output tensor of the model contains probabilities or confidence scores for each gesture class.
  - The code prints the classification results over the serial port, indicating the predicted gesture and its corresponding confidence score.

Overall, the code facilitates real-time gesture recognition using sensor data from the Arduino Nano 33 BLE Sense microcontroller and TensorFlow Lite machine learning model, demonstrating the potential of embedded machine learning for interactive applications.

## **Emoji_button Code:**
```c
#include <Arduino_BMI270_BMM150.h>
#include <PluggableUSBHID.h>
#include <USBKeyboard.h>
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

// Include the model header file
#include "model.h"

// Include IMU Classifier constants
#include "imu_classifier_constants.h"

const float accelerationThreshold = 2.5; // threshold of significance in G's
const int numSamples = 119; // Declare numSamples globally
float aX, aY, aZ, gX, gY, gZ;

int samplesRead = numSamples;

tflite::MicroErrorReporter tflErrorReporter;
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

const char* GESTURES[] = {
  "punch",
  "flex"
};

#define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))

// Declare global variables
constexpr int tensorArenaSize = 8 * 1024;
uint8_t tensorArena[tensorArenaSize] __attribute__((aligned(16)));

const int buttonPin = 3;

const unsigned long punch = 0xD83D << 16 | 0xDC4A;
const unsigned long bicep = 0xD83D << 16 | 0xDCAA;

USBKeyboard keyboard;

int previousButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize the IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Print out the sample rates of the IMUs
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");

  Serial.println();

  // Get the TFL representation of the model byte array
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  // Create an interpreter to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, nullptr, nullptr);

  // Allocate memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

  // Set up USB keyboard
  pinMode(buttonPin, INPUT_PULLUP);
}

// ... (other includes and constants)

void loop() {
  float aX, aY, aZ, gX, gY, gZ;

  // Check for significant motion
  if (checkForSignificantMotion()) {
    // Run gesture recognition
    runGestureRecognition();
  }
}

bool checkForSignificantMotion() {
  // Check for significant motion
  if (IMU.accelerationAvailable()) {
    // read the acceleration data
    IMU.readAcceleration(aX, aY, aZ);

    // sum up the absolutes
    float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

    // check if it's above the threshold
    if (aSum >= accelerationThreshold) {
      // reset the sample read count
      samplesRead = 0;
      Serial.println("Significant motion detected!");
      return true;
    }
  }

  return false;
}

void runGestureRecognition() {
  // Check if new acceleration AND gyroscope data is available
  while (samplesRead < numSamples) {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      // normalize the IMU data between 0 to 1 and store in the model's
      // input tensor
      tflInputTensor->data.f[samplesRead * 6 + 0] = (aX + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 1] = (aY + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 2] = (aZ + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 3] = (gX + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 4] = (gY + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 5] = (gZ + 2000.0) / 4000.0;

      samplesRead++;

      if (samplesRead == numSamples) {
        // Run inferencing
        TfLiteStatus invokeStatus = tflInterpreter->Invoke();
        if (invokeStatus != kTfLiteOk) {
          Serial.println("Invoke failed!");
          while (1);
          return;
        }

        // Declaring two variables
        float highestConfidence = 0.0;
        String highestGesture = "";

        // Loop through the output tensor values from the model
        for (int i = 0; i < NUM_GESTURES; i++) {
          Serial.print(GESTURES[i]); 
          Serial.print(": "); 
          Serial.println(tflOutputTensor->data.f[i], 6);

          // Check for the highest confidence gesture
          if (tflOutputTensor->data.f[i] > highestConfidence) {
            highestConfidence = tflOutputTensor->data.f[i];
            highestGesture = GESTURES[i];
          }
        }

        Serial.println("Finished looping through gestures");

        if (highestConfidence > GESTURE_THRESHOLD) {
          sendEmoji(highestGesture.c_str());
        }

        //Serial.println("Sent Emoji");
        //Serial.println(samplesRead);
        Serial.print("Chosen gesture: "); 
        Serial.println(highestGesture);
        Serial.println();
      }
    }
  }
}

void sendEmoji(const char* gesture) {
  if (strcmp(gesture, "punch") == 0) {
    Serial.println("\xF0\x9F\x91\x8A"); // Punch emoji hex code
  } else if (strcmp(gesture, "flex") == 0) {
    Serial.println("\xF0\x9F\x92\xAA"); // Flex emoji hex code
  }
}
```

#### **The provided code extends the functionality of the above code by integrating USB keyboard emulation to send emoji characters corresponding to recognized gestures. Here are the main differences between this code and the previous one:**

- ### Additional Libraries:
  - This code includes additional libraries such as `PluggableUSBHID.h` and `USBKeyboard.h` to enable USB keyboard emulation.
- ### USB Keyboard Setup:
  - The setup function now initializes USB keyboard functionality using USBKeyboard object instantiation and setting the button pin (`buttonPin`) as input with pull-up resistor enabled.
- ### Gesture Recognition Loop:
  - The loop function now checks for significant motion using the `checkForSignificantMotion` function. If significant motion is detected, the `runGestureRecognition` function is called to perform gesture recognition.
- ### Gesture Recognition Logic:
  - The `runGestureRecognition` function captures **acceleration** and **gyroscope** data and normalizes it before feeding it into the TensorFlow Lite model for inference, similar to the previous code.
  - Once the required number of samples is collected, the code performs inference and identifies the gesture with the highest confidence level.
  - If the confidence level for the detected gesture exceeds a threshold (`GESTURE_THRESHOLD`), it calls the `sendEmoji` function to send the corresponding emoji character over the serial port.
- ### Send Emoji Function:
  - The `sendEmoji` function sends emoji characters corresponding to recognized gestures using USB keyboard emulation. It translates recognized gestures (e.g., `punch` or `flex`) into emoji characters and sends them over the serial port.

This code extends the gesture recognition system by incorporating USB keyboard emulation to provide visual feedback in the form of emoji characters for recognized gestures, enhancing the user experience and interaction with the system.