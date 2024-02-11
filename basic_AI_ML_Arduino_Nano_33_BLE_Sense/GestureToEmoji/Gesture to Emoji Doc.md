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

![](RackMultipart20240209-1-z2j864_html_d9833fbddc960b53.jpg)

- Open the Serial Monitor: `Tools -> Serial Monitor` to view the text output.
- Open the Serial Plotter: `Tools -> Serial Plotter` to view the output on a graph.

![](RackMultipart20240209-1-z2j864_html_3d28b9b4140ec90.jpg)

- Similarly, you can open a **SimpleGyroscope** sketch and you will get a Gyroscope result on the serial monitor.

![](RackMultipart20240209-1-z2j864_html_ae57832e40554417.jpg)

## STEP 2: ArduinoSketches File Setup

- Go to [this repository](https://github.com/palnitin24/GestureToEmoji_ArduinoSketches) either download this in a zip file or directly git clone it to the specified directory
- Go to `\Documents\Arduino\libraries` and now extract and paste the downloaded ArduinoSketches file

## STEP 3: Capture the IMU Data

- Open `ArduinoSketches\IMU_Capture\IMU_Capture.ino` in the Arduino IDE. **Note that this sketch may not open directly from Arduino IDE**, so the advisable option is to manually go to this directory `\Documents\Arduino\libraries\ArduinoSketches\IMU_Capture` and open `IMU_Capture.ino` sketch.
- Compile the sketch and upload it to the board: `Sketch -> Upload`
- Press the reset button on the board
- Open the Serial Monitor: `Tools -> Serial Monitor` and keep **newLine** to `Both NL & CR` and **baud rate** to `9600 baud`
- Make a punch gesture with the board in your hand - you should see the sensor data log in the Serial Monitor

![](RackMultipart20240209-1-z2j864_html_b29d80e19156058f.png)

- Repeat 10 times to gather more data
- Copy and paste the data from the serial output to new text file called `punch.csv` using your favorite text editor (eg. Notepad)
- Close the Serial Monitor
- Press the reset button on the board
- Open the Serial Monitor: `Tools -> Serial Monitor`
- Make a flex gesture with the board in your hand similar to like you did for punch gesture
- Repeat 10 times to gather more data
- Copy and paste the serial output to new text file `flex.csv`using your favorite text editor

## STEP 4: Training the captured Data using Tensorflow in google colab

- Open [this notebook in google colab](https://colab.research.google.com/github/arduino/ArduinoTensorFlowLiteTutorials/blob/master/GestureToEmoji/arduino_tinyml_workshop.ipynb)
- **Note that Some of you might see an error about 3rd party cookies**.

![](RackMultipart20240209-1-z2j864_html_3e9250e324920d1c.png)

- You can enable 3rd party cookies, or better yet, add an exception for `[\*.]googleusercontent.com`

![](RackMultipart20240209-1-z2j864_html_5b4dc8a4194c6cc1.png)

- If you find some error in the colab notebook code then refer this google colab notebook: [GestureToEmoji\_arduino\_tinyml\_workshop.ipynb](https://colab.research.google.com/drive/1DYw_duH0RqHkklAlh0LHSBwvMzx5QN-o#scrollTo=1eSkHZaLzMId)
- You will get these two files after running all the cells of the colab notebook. Download these two files.

![](RackMultipart20240209-1-z2j864_html_87d4f6f2965c754f.png)

## STEP 5: Classifying the IMU Data

- Go to `\Documents\Arduino\libraries\ArduinoSketches\IMU_Classifier` and open `IMU_Classifier.ino` sketch in the Arduino IDE.
- Switch to the `model.h` tab which will be next to `IMU_classifier.ino` sketch

![](RackMultipart20240209-1-z2j864_html_2e2783521b5280d1.png)

- Replace the contents of `model.h` with the version you downloaded from Google Colab
- Upload the sketch: `Sketch -> Upload`
- Open the Serial Monitor: `Tools -> Serial Monitor`
- Press the reset button, and perform a gesture (Punch or Flex gesture)
- The confidence of each gesture will be printed to the Serial Monitor (Close to 0 -> low confidence & Close to 1 -> high confidence)

![](RackMultipart20240209-1-z2j864_html_2c92a35ec9c8c91b.png)

## STEP 6: Gesture Emoji (👊 and 💪)

- The **Emoji_Button** example, `ArduinoSketchs/Emoji_Button/Emoji_Button.ino` , shows how to create a USB keyboard that prints an emoji character. (**This only works on Windows**, to find the workable code on Linux and macOS refer- [this Link](https://github.com/arduino/ArduinoTensorFlowLiteTutorials/blob/master/GestureToEmoji/ArduinoSketches/Emoji_Button/Emoji_Button.ino))
- You can change the gesture threshold which is located in `imu_classifier_constants.h` tab
- Also you can see the `model.h` file which is the same file you used for gesture classifier
- Upload the sketch: `Sketch -> Upload`
- Open the Serial Monitor: `Tools -> Serial Monitor` and keep **newline** to `Both NL & CR` and **baud rate** to `9600 baud`
- Press the reset button, and perform a gesture (Punch or Flex gesture)

![](RackMultipart20240209-1-z2j864_html_59838a9656b28c31.png)