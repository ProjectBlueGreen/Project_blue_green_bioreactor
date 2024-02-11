// Modified by Nitin Pal
// This code is compatible with windows feel free to use and modify the below code.

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