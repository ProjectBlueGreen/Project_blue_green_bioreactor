# **Fruit identification using Arduino and TensorFlow**

## **Overview**
In this Document we are going to walk through an even simpler end-to-end tutorial using the TensorFlow Lite Micro library and the [Arduino Nano 33 BLE Sense](https://store.arduino.cc/arduino-nano-33-ble-sense?utm_source=blog&utm_campaign=ai&utm_content=fruit_identification)’s colorimeter and proximity sensor to classify objects. To do this, we will be running a small neural network on the board itself.

In this tutorial when the object is close enough we sample the color – the onboard RGB sensor can be viewed as a 1-pixel color camera. While this method has limitations it provides us a quick way of classifying objects only using a small amount of resources. Note that you could indeed run a complete [CNN-based vision model](http://cs231n.github.io/convolutional-networks/) on-device. As this particular Arduino board includes an onboard colorimeter, we thought it’d be fun and instructive to demonstrate in this way to start with.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/9391d47b-584d-4b88-be90-3155fdf2f2ad)![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/dbc324a1-fa83-4716-80fa-8a89c115da25)


## **Reference**
1. Check [Youtube Tutorial](https://www.youtube.com/watch?v=xBW-lFY2c1k&list=PL3E6XmqhhLBHXX2fG2dVER-LOq_7nl9p6&index=17)
2. Check [Github Repository](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/tree/master/GestureToEmoji)

## **About the Arduino board**
The [Arduino Nano 33 BLE Sense](https://store.arduino.cc/arduino-nano-33-ble-sense?utm_source=blog&utm_campaign=ai&utm_content=fruit_identification) board we’re using here has an Arm Cortex-M4 microcontroller running mbedOS and a ton of onboard sensors – digital microphone, accelerometer, gyroscope, temperature, humidity, pressure, light, color, and proximity.While tiny by cloud or mobile standards the microcontroller is powerful enough to run TensorFlow Lite Micro models and classify sensor data from the onboard sensors.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/211719b5-91b6-4f06-a27e-1c8b599ae2fb)


## STEP 1: Arduino IDE Setup

- Open the Arduino IDE application on your computer.
- Choose the board: `Tools -> Board -> Arduino Nano 33 BLE`
- Choose the port: `Tools -> Port -> COM3 (Arduino Nano 33 BLE)` **Note that the actual port may be different on your computer**.


## STEP 2: Capturing data in CSV files for each object 

For each fruit we want to classify we will capture some color data. By doing a quick capture with only one example per class we will not train a generalized model, but we can still get a quick proof of concept working with the objects you have to hand!

**We are sampling an apple:**

- Reset the board using the small white button on top.
  - Keep your finger away from the sensor, unless you want to sample it!
  - The Monitor in Arduino Create will say `‘Serial Port Unavailable’` for a minute
- You should then see `Red, Green, and Blue` appear at the top of the serial monitor
- Put the front of the board to the apple. 
  - The board will only sample when it detects an object is close to the sensor and is sufficiently illuminated (turn the lights on or be near a window)
- Move the board around the surface of the object to capture color variations
- You will see the RGB color values appear in the serial monitor as comma separated data. 
- Capture a few seconds of samples from the object
- Copy and paste this log data from the Monitor to a text editor
- Save your file as `apple.csv`
- Reset the board using the small white button on top.
- Do this a few more times, capturing other objects (e.g. `banana.csv`, `orange.csv`). 

## STEP 3: Training the model
We will now use Colab to train an ML model using the data you just captured in the previous section.

- First open the FruitToEmoji Jupyter Notebook in [colab]
- ![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/17f38b14-3fe1-45df-a58e-f09543434efa)

- Follow the instructions in the colab
  - You will be uploading your `.csv` files 
  - Parsing and preparing the data
  - Training a model using `Keras`
  - Outputting TensorFlowLite Micro model
  - Downloading this to run the classifier on the Arduino 

- With that done you will have downloaded `model.h` to run on your Arduino board to classify objects!
### 
###

## STEP 4: Classifying the Fruit color

- Copy the contents of the file that you downloaded from Google Colab.
- Create a new tab on Arduino ide and name it `model.h`.
- Replace the contents of **model.h** with the version you downloaded from Google Colab

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/89443776-c3fc-417f-b098-a42738bd4e87)


![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/abdeb2cc-5d46-4a50-b6e7-f0ab0d75de6b)


- Upload the sketch: `Sketch -> Upload`
- Open the Serial Monitor: `Tools -> Serial Monitor`
- Press the reset button on the Arduino, and bring the fruit  that is to be identified in front of the color sensor 
- The output of the fruit detected will be presented in percentage format in the serial monitor 

  ![](Aspose.Words.20c74418-a7d9-4068-a474-ca3a2c61a20c.007.png)![](Aspose.Words.20c74418-a7d9-4068-a474-ca3a2c61a20c.008.png)
