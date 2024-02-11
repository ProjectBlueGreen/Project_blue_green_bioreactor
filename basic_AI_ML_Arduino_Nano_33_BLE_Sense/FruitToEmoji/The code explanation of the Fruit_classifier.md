# **The code explanation of the Fruit_classifier.ino sketch :**


## **Objective:**

The objective of the code is to perform real-time object classification using a pre-trained TensorFlow Lite model on an **Arduino Nano 33 BLE Sense** microcontroller. By leveraging the built-in **APDS9960 RGB color sensor** and proximity sensor, the code captures essential data about the surrounding environment, including color intensity and object proximity. After preprocessing the sensor data to ensure compatibility with the model's input requirements, the code feeds it into the TensorFlow Lite model for inference. 
The model, trained on a dataset containing images of fruits, predicts the type of fruit based on the input data, yielding classification results with corresponding confidence scores. These results are then printed, allowing users to identify detected objects and their respective likelihoods. Overall, the code enables applications such as fruit recognition or object detection in real-world scenarios where computational resources are limited, showcasing the potential of deploying machine learning models on resource-constrained devices like microcontrollers.

## **Code:** 
```c
#include <TensorFlowLite.h>

#include <tensorflow/lite/micro/all\_ops\_resolver.h>

#include <tensorflow/lite/micro/debug\_log.h>

#include <tensorflow/lite/micro/micro\_error\_reporter.h>

#include <tensorflow/lite/micro/micro\_interpreter.h>

#include <tensorflow/lite/schema/schema\_generated.h>

#include <tensorflow/lite/version.h>

#include <Arduino\_APDS9960.h>

#include "model.h" // Include the header file containing the TensorFlow Lite model

// Global variables for TensorFlow Lite (Micro)

tflite::MicroErrorReporter tflErrorReporter;

tflite::AllOpsResolver tflOpsResolver;

const tflite::Model\* tflModel = nullptr;

tflite::MicroInterpreter\* tflInterpreter = nullptr;

TfLiteTensor\* tflInputTensor = nullptr;

TfLiteTensor\* tflOutputTensor = nullptr;

// Create a static memory buffer for TensorFlow Lite Micro

constexpr int tensorArenaSize = 8 \* 1024;

uint8\_t tensorArena[tensorArenaSize];

// Array to map gesture index to a name

const char\* CLASSES[] = {

    "Apple", // u8"\U0001F34E", // Apple

    "Banana", // u8"\U0001F34C", // Banana

    "Orange" // u8"\U0001F34A" // Orange

};

#define NUM\_CLASSES (sizeof(CLASSES) / sizeof(CLASSES[0]))

void setup() {

    Serial.begin(9600);

    while (!Serial) {};

    Serial.println("Object classification using RGB color sensor");

    Serial.println("--------------------------------------------");

    Serial.println("Arduino Nano 33 BLE Sense running TensorFlow Lite Micro");

    Serial.println("");

    if (!APDS.begin()) {

        Serial.println("Error initializing APDS9960 sensor.");

        // Consider adding additional error handling here

    }

    // Get the TFL representation of the model byte array

    tflModel = tflite::GetModel(model);

    if (tflModel->version() != TFLITE\_SCHEMA\_VERSION) {

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

}

void loop() {

    int r, g, b, p, c;

    float sum;

    // Check if both color and proximity data are available to sample

    while (!APDS.colorAvailable() || !APDS.proximityAvailable()) {}

    // Read the color and proximity sensor

    APDS.readColor(r, g, b, c);

    p = APDS.readProximity();

    sum = r + g + b;

    // Check if there's an object close and well-illuminated enough

    if (p == 0 && c > 10 && sum > 0) {

        float redRatio = r / sum;

        float greenRatio = g / sum;

        float blueRatio = b / sum;

        // Input sensor data to the model

        tflInputTensor->data.f[0] = redRatio;

        tflInputTensor->data.f[1] = greenRatio;

        tflInputTensor->data.f[2] = blueRatio;

        // Run inferencing

        TfLiteStatus invokeStatus = tflInterpreter->Invoke();

        if (invokeStatus != kTfLiteOk) {

            Serial.println("Invoke failed!");

            while (1);

            return;

    }

    // Output results

    for (int i = 0; i < NUM\_CLASSES; i++) {

        Serial.print(CLASSES[i]);

        Serial.print(" ");

        Serial.print(int(tflOutputTensor->data.f[i] \* 100));

        Serial.print("%\n");

    }

        Serial.println();

        // Wait for the object to be moved away

        while (!APDS.proximityAvailable() || (APDS.readProximity() == 0)) {}

    }

}
```


## **Step-by-Step Explanation:**

### Include necessary libraries:

- `TensorFlowLite.h`: Header file for TensorFlow Lite.

- Other TensorFlow Lite library headers for resolver, error reporting, interpreter, debug logging, schema, and version.

- `Arduino_APDS9960.h`: Header file for the APDS9960 sensor library.

- `model.h`: Header file containing the TensorFlow Lite model.

### Define global variables:

- `tflErrorReporter`: Error reporter object for TensorFlow Lite.

- `tflOpsResolver`: Resolver object containing all the TensorFlow Lite operators.

- `tflModel`: Pointer to the TensorFlow Lite model.

- `tflInterpreter`: Pointer to the TensorFlow Lite interpreter.

- `tflInputTensor` and `tflOutputTensor`: Pointers to the input and output tensors of the TensorFlow Lite model.

- `tensorArenaSize` and `tensorArena`: Static memory buffer for TensorFlow Lite.

- `CLASSES`: Array mapping gesture index to a name.

- `NUM_CLASSES`: Number of classes.

### Setup function:

- Begin serial communication.

- Initialize the `APDS9960` sensor.

- Get the TensorFlow Lite representation of the model.

- Create a TensorFlow Lite interpreter with the model, resolver, and memory buffer.

- Allocate memory for input and output tensors.

- Get pointers for input and output tensors.

### Loop function:

- Read color and proximity sensor data from `APDS9960`.

- Check if data is available.

- Calculate color ratios (`red`, `green`, `blue`) and `sum`.

- Check if an object is close and well-illuminated.

- If conditions are met, input sensor data to the model.

- Run inference.

- Print classification results.

- Wait for the object to be moved away before continuing the loop.

- Overall, this code continuously reads sensor data, performs inference using a TensorFlow Lite model, and prints the classification results when an object is detected.


