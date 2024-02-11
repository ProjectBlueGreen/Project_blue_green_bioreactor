# **Gesture to Emoji Steps Documentation**

## **Overview:**

In this tutorial, we will guide you through the process of creating a custom gesture recognition system for Arduino using TensorFlow in Colab. This comprehensive guide will help you understand and implement the fundamentals of TinyML, using the **Arduino Nano 33 BLE Sense board** along with the **Arduino\_BMI270\_BMM150** and **Arduino\_TensorFlowLite** libraries.

## **Reference:**

1. Check [Youtube Tutorial](https://www.youtube.com/watch?v=xBW-lFY2c1k&list=PL3E6XmqhhLBHXX2fG2dVER-LOq_7nl9p6&index=17)
2. Check [Github Repository](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/tree/master/GestureToEmoji)

## STEP 1: Arduino IDE Setup

- Open the Arduino IDE application on your computer.
- Choose the board: `Tools -> Board -> Arduino Nano 33 BLE`
- Choose the port: `Tools -> Port -> COM3 (Arduino Nano 33 BLE)` **Note that the actual port may be different on your computer**.
- To test IMU sensor, Open the **Simple Accelerometer** sketch using `File -> Examples -> Arduino_LSM9DS1 -> SimpleAccelerometer`, Upload the sketch to the board using the `Sketch -> Upload` menu or the right arrow button from the toolbar.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/c512acc2-f9bd-4ad7-8486-63eb7dabe1fd)


- Open the Serial Monitor: `Tools -> Serial Monitor` to view the text output.
- Open the Serial Plotter: `Tools -> Serial Plotter` to view the output on a graph.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/d63e5261-92d6-4e69-94b8-f37ed440cb50)


- Similarly, you can open a **SimpleGyroscope** sketch and you will get a Gyroscope result on the serial monitor.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/847263f9-92b9-4f70-9bbf-9cde2791b0e4)


## STEP 2: ArduinoSketches File Setup

- Go to [this repository](https://github.com/palnitin24/GestureToEmoji_ArduinoSketches) either download this in a zip file or directly git clone it to the specified directory
- Go to `\Documents\Arduino\libraries` and now extract and paste the downloaded ArduinoSketches file

## STEP 3: Capture the IMU Data

- Open `ArduinoSketches\IMU_Capture\IMU_Capture.ino` in the Arduino IDE. **Note that this sketch may not open directly from Arduino IDE**, so the advisable option is to manually go to this directory `\Documents\Arduino\libraries\ArduinoSketches\IMU_Capture` and open `IMU_Capture.ino` sketch.
- Compile the sketch and upload it to the board: `Sketch -> Upload`
- Press the reset button on the board
- Open the Serial Monitor: `Tools -> Serial Monitor` and keep **newLine** to `Both NL & CR` and **baud rate** to `9600 baud`
- Make a punch gesture with the board in your hand - you should see the sensor data log in the Serial Monitor

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/edfca63c-b7c6-4bd8-8816-2054fd220efe)


- Repeat 10 times to gather more data
- Copy and paste the data from the serial output to new text file called `punch.csv` using your favorite text editor (eg. Notepad)
- Close the Serial Monitor
- Press the reset button on the board
- Open the Serial Monitor: `Tools -> Serial Monitor`
- Make a flex gesture with the board in your hand similar to like you did for punch gesture
- Repeat 10 times to gather more data
- Copy and paste the serial output to new text file `flex.csv`using your favorite text editor

## STEP 4: Training the captured Data using Tensorflow in google colab

- Open [this notebook in google colab]

- ![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/5ca528d9-f8dc-45db-87e2-a87d9a0c957c)

- **Note that Some of you might see an error about 3rd party cookies**.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/54cc5174-b1a5-474e-afe6-38eefed79e17)

- If you find some error in the colab notebook code then refer this google colab notebook: [GestureToEmoji\_arduino\_tinyml\_workshop.ipynb](https://colab.research.google.com/drive/1DYw_duH0RqHkklAlh0LHSBwvMzx5QN-o#scrollTo=1eSkHZaLzMId)
- You will get these two files after running all the cells of the colab notebook. Download these two files.

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/84930bfc-c0dc-43a1-b712-854daab3cba6)


## STEP 5: Classifying the IMU Data

- Go to `\Documents\Arduino\libraries\ArduinoSketches\IMU_Classifier` and open `IMU_Classifier.ino` sketch in the Arduino IDE.
- Switch to the `model.h` tab which will be next to `IMU_classifier.ino` sketch

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/dcc927a3-c66d-411a-adcc-903d95b9a85c)


- Replace the contents of `model.h` with the version you downloaded from Google Colab
- Upload the sketch: `Sketch -> Upload`
- Open the Serial Monitor: `Tools -> Serial Monitor`
- Press the reset button, and perform a gesture (Punch or Flex gesture)
- The confidence of each gesture will be printed to the Serial Monitor (Close to 0 -> low confidence & Close to 1 -> high confidence)

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/b755cde4-c367-491d-8f83-d5c500bfbfe5)


## STEP 6: Gesture Emoji (👊 and 💪)

- The **Emoji_Button** example, `ArduinoSketchs/Emoji_Button/Emoji_Button.ino` , shows how to create a USB keyboard that prints an emoji character. (**This only works on Windows**, to find the workable code on Linux and macOS refer- [this Link](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/blob/master/GestureToEmoji/ArduinoSketches/Emoji_Button/Emoji_Button.ino))
- You can change the gesture threshold which is located in `imu_classifier_constants.h` tab
- Also you can see the `model.h` file which is the same file you used for gesture classifier
- Upload the sketch: `Sketch -> Upload`
- Open the Serial Monitor: `Tools -> Serial Monitor` and keep **newline** to `Both NL & CR` and **baud rate** to `9600 baud`
- Press the reset button, and perform a gesture (Punch or Flex gesture)

![image](https://github.com/ProjectBlueGreen/project_blue_green_software/assets/159428457/0056aa7c-6b91-487a-a8eb-bdda83b74ef1)

