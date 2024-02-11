
# Sensor Library Testing Doc

## Titles :

- [Overview](#overview)
- [Requirements](#requirements)
- [Accessing Accelerometer Data on Nano 33 BLE Sense](#accessing-accelerometer-data-on-nano-33-ble-sense)
- [Controlling the On-Board RGB LED with a Microphone](#controlling-the-on-board-rgb-led-with-a-microphone)
- [Gesture Recognition with the Nano 33 BLE Sense](#gesture-recognition-with-the-nano-33-ble-sense)
- [Access Barometric Pressure Sensor Data on Nano 33 BLE Sense](#access-barometric-pressure-sensor-data-on-nano-33-ble-sense)
- [Reading Temperature & Humidity on Nano 33 BLE Sense](#reading-temperature-and-humidity-on-nano-33-ble-sense)
- [Connecting Nano 33 BLE Devices over Bluetooth](#connecting-nano-33-ble-devices-over-bluetooth)
- [Board Installation for Python Programming](#board-installation-for-python-programming)
- [Conclusion](#conclusion)


## Overview

Assess the accuracy and functionality of Arduino Nano 33 BLE Sense onboard sensors and libraries for IoT applications.

## Requirements 

**Hardware:** Arduino Nano 33 BLE Sense Microcontroller board, PC, Micro USB cable.

**Software:** Arduino IDE

## Accessing Accelerometer Data on Nano 33 BLE Sense

### **The BMI270 and BMM150 Inertial Module**

The IMU system on the Arduino Nano 33 BLE Sense Rev2 is a combination of two modules, the 6-axis BMI270, and the 3-axis BMM150, that together add up to a combined 9-axis IMU system that can measure acceleration, as well as rotation and magnetic fields all in 3D space.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl1.png?raw=true)

<u>(Fig.1 The Arduino Nano 33 BLE Sense Rev2 IMU system.)</u>

### **The BMI270\_BMM150 Library**

The Arduino BMI270\_BMM150 library allows us to use the Arduino Nano 33 BLE Rev2 IMU system without having to go into complicated programming.

The library takes care of the sensor initialization and sets its values as follows:

- **Accelerometer:** range is set at `[-4, +4]g -/+0.122 mg`.
- **Gyroscope:** range is set at `[-2000, +2000] dps +/-70 mdps.`
- **Magnetometer:** range is set at `[-400, +400] uT +/-0.014 uT.`
- **Accelerometer:** Output data rate is fixed at `104 Hz.`
- **Gyroscope:** Output data rate is fixed at `104 Hz.`
- **Magnetometer:** Output data rate is fixed at `20 Hz.`

### **Accelerometer**

An accelerometer is an electromechanical device used to measure acceleration forces. Such forces may be static, like the continuous force of gravity, or, as with many mobile devices, dynamic to sense movement or vibrations.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl2.png?raw=true)

<u>How (Fig.2 The accelerometer works)</u>

In this example, we will use the accelerometer as a "level" that will provide information about the position of the board. With this application, we will be able to read the relative position of the board and the degrees, by tilting the board up, down, left, or right.

**Step 1:** Install the Arduino\_BMI270\_BMM150 library

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl3.png?raw=true)

**Step2:** Connecting the board

Now, connect the Arduino Nano 33 BLE Sense to the computer and make sure that the IDE recognizes it, if so, the board and port should appear.

**Step 3:** Select the Nano 33 BLE Sense board and Port

In the Arduino IDE, go to "Tools" -\> "Board" and select "Arduino Nano 33 BLE."

**Code:** `Accelerometer.ino`

**Circuit Diagram:**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl4.jpg?raw=true)

<u>(Fig. Microcontroller board connected to PC/laptop)</u>

**Results**:

![]
(https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl5.png?raw=true)
## **Controlling the On-Board RGB LED with a Microphone**

**Theory:**

## **MP34DT06JTR Sensor**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl6.png?raw=true)

<u>(Fig. The MP34DT06JTR microphone sensor.)</u>

Microphones are components that convert physical sound into digital data. Microphones are commonly used in mobile terminals, speech recognition systems, or even gaming and virtual reality input devices.

The MP34DT06JTR sensor is an ultra-compact microphone that uses PDM (Pulse-Density Modulation) to represent an analog signal with a binary signal.

The sensor's range of different values are the following:

- Signal-to-noise ratio: `64dB`
- Sensitivity: `-26dBFS ±3dB`
- Temperature range: `-40 to 85°C`

**Procedure:**

**Step 1:** Setting up

Let's start by opening the [Arduino](https://create.arduino.cc/editor) IDE, click on the Libraries tab, search for the PDM FOR MBED library, then in Examples, open the PDMSerialPlotter example.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl7.png?raw=true)

**Step2:** Connecting the board

Now, connect the Arduino Nano 33 BLE Sense to the computer and make sure that the IDE recognizes it, if so, the board and port should appear.

**Step3:** Printing and displaying sound values

Now we will need to modify the code of the example, in order to print the sound values and turn on a different LED based on how noisy the sound is.

Before the setup() there are two types of variables initialized. One is a short variable and the other is a volatile int variable. We use the short type variable to store 16-bit data types as the sampleBuffer[256]. The other, volatile, is a keyword known as a variable qualifier. It is usually used before the datatype of a variable, to modify how the compiler and subsequent program treat the variable. In this case, it directs the compiler to load the variable samplesRead from RAM, not from a storage register.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl8.png?raw=true)

In the setup(), we use the PDM.conReceive() function to configure the data receive callback. Lastly, the PDM.begin() sets the sensor to read data from just one channel and a sample rate of 16 kHz, this statement is inside an if() that will print a message, as a string, in case the sensor has not been properly initialized.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl9.png?raw=true)

Then, in the loop(), let's modify the example code by adding the following portion of code inside the for() loop, after the Serial.println() function.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl10.png?raw=true)

With this portion of the code, we will turn on the RGB LED based on the amount of sound the microphones receive.

**Code:** `micRGB.ino`

**Code Explanation :** This Arduino code utilizes the Pulse Density Modulation (PDM) library to read audio samples from a microphone and control LEDs based on the intensity of the sound. Here's a breakdown of the code:

1. **Library Inclusion:**
 ![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl11.png?raw=true)

This line includes the PDM library, which is used for reading audio samples.

2. **Variable Declaration:**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl12.png?raw=true)

- sampleBuffer: An array to store audio samples, each represented as a 16-bit integer.
- samplesRead: A variable to keep track of the number of audio samples read.

3. **Setup Function:**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl13.png?raw=true)

- Initializes serial communication for debugging purposes.
- Sets up a callback function on PDM data to handle received PDM data.
- Initializes the PDM library with one channel (mono mode) and a 16 kHz sample rate.

4. **Loop Function:**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl14.png?raw=true)

- Checks if there are audio samples available to read.
- Prints each sample to the serial monitor.
- Controls LEDs based on sound intensity thresholds.

5. **PDM Data Callback Function:**

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl15.png?raw=true)

- Called when PDM data is received.
- Queries the number of bytes available.
- Reads PDM data into the sample buffer and calculates the number of samples read.

Overall, this code reads audio samples from a microphone using PDM and adjusts the state of three LEDs based on different sound intensity levels. The LEDs are controlled by turning them on or off in response to specified sound intensity thresholds.

**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**Results**:

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SL_Img/sl17.png?raw=true)

-
## **Gesture Recognition with the Nano 33 BLE Sense**

**Theory**:

The APDS9960 sensor is a multipurpose device that features advanced gesture detection, proximity detection, Digital Ambient Light Sense (ALS) and Color Sense (RGBC).

![](RackMultipart20240210-1-42gde9_html_e6679f8785465ceb.png)

<u>(Fig. The APDSS9960 sensor)</u>

The sensor's gesture detection utilizes four directional photodiodes to sense reflected IR energy (sourced by the integrated LED) to convert physical motion information (i.e. velocity, direction, and distance) into digital information.

**It features:**

- Four separate diodes sensitive to different directions.
- Ambient light rejection.
- Offset compensation.
- Programmable driver for IR LED current.
- 32 dataset storage FIFO.
- Interrupt driven I2C-bus communication.

### **The Library**

### The APDS9960 library allows us to use the sensor available on the board, to read gestures, color, light intensity, and proximity. The library includes some of the following functions:

![](RackMultipart20240210-1-42gde9_html_3627bd2bfc507874.png)

If you want a deeper knowledge of any of the library's functions, you can check the Arduino [reference](https://www.arduino.cc/en/Reference/ArduinoAPDS9960) for this library.

For this tutorial, we will only focus on the gesture readings, which are based on the detection of the movement of the hand over four photodiodes inside the sensor.

**Procedure**:

**Step 1:** **Start by opening the Arduino Web Editor, clicking on the** Libraries **tab, and searching for the APDS9960 library. Then in \>** Examples **, open the** GestureSensor** sketch and once it opens, you can rename it as Gesture&LEDs.

![](RackMultipart20240210-1-42gde9_html_ee415857ee63e4c4.png)

**Step 2:** Connecting the board 

Now, connect the Arduino Nano 33 BLE Sense to the computer and make sure that the Arduino IDE recognizes it, if so, the board and port should appear.

**Step 3:** Blink patterns according to hand gestures

Now we will need to modify the code on the example, to change the color of the RGB LED and the built-in LED respectively according to the direction of our hand gesture.

After including the Arduino\_APDS9960.h library, we will need to configure the specified pins (22, 23, 24, LED\_BUILTIN) at the beginning of the setup() section, to behave as output:

![](RackMultipart20240210-1-42gde9_html_554ef70da597dfcb.png)

and then at the end, we need to turn all the LEDs OFF by adding the following statements

![](RackMultipart20240210-1-42gde9_html_11cc66833c915052.png)

In the loop() section the if() statement is checking that the gesture sensor is available and if it is, it reads for any incoming gesture detection.

Next, in the switch() statement we will add different actions to be performed according to conditions, in this case, the direction of the hand gesture will define those conditions.

If the sensor detects motions (up, down, left, or right) we can add the following code snippets between the **Serial.println()** and the **break;** in each switch case, to activate the red, blue and green colors of the RGB LED and the orange on the built-in LED.

In the GESTURE\_UP case, the RGB LED will glow **red** for a second:

![](RackMultipart20240210-1-42gde9_html_5612da2f25e47771.png)

In the GESTURE\_DOWN case, the RGB LED will glow green for one second:

![](RackMultipart20240210-1-42gde9_html_3006c4183c487ec8.png)

In the GESTURE\_LEFT case, the RGB LED will glow blue for one second:

![](RackMultipart20240210-1-42gde9_html_d15343d567011fbb.png)

Lastly, in the GESTURE\_RIGHT case, the small built-in LED will glow orange for one second:

![](RackMultipart20240210-1-42gde9_html_d0ebd2709ba94d9e.png)

Now the code is complete!

**File Name :** `GestureRGB.ino`

![](RackMultipart20240210-1-42gde9_html_beef9a894231a58f.png)

This line includes the necessary Arduino library for the APDS9960 Gesture Sensor.

![](RackMultipart20240210-1-42gde9_html_f616a2069b5af827.png)

**In the setup() function:**

- Serial communication is initiated with a baud rate of 9600.
- The pin modes for the built-in LED (LED\_BUILTIN) and external RGB LEDs (LEDR, LEDG, LEDB) are set to OUTPUT.
- A while loop waits until a connection is established with the Serial Monitor.
- The APDS9960 sensor is initialized using APDS.begin(). If initialization fails, an error message is printed.
- There is a commented-out line APDS.setGestureSensitivity(80); which can be used to set the sensitivity of gesture detection. The default sensitivity is 80.
- A message is printed to indicate that gesture detection is in progress.
- The RGB LEDs are turned off initially by setting them to HIGH.

![](RackMultipart20240210-1-42gde9_html_7443b4359d8811e4.png) ![](RackMultipart20240210-1-42gde9_html_35b0321498453dae.png)

**In the loop() function:**

- It checks if a gesture is available using APDS.gestureAvailable().
- If a gesture is detected, it reads the gesture using APDS.readGesture().
- A switch statement is used to perform actions based on the detected gesture:


  - If UP is detected, it prints a message to the Serial Monitor, turns on the Red LED (LEDR), waits for 1 second, and then turns it off.
  - If DOWN is detected, it does the same for the Green LED (LEDG).
  - If LEFT is detected, it does the same for the Blue LED (LEDB).
  - If RIGHT is detected, it does the same for the built-in LED (LED\_BUILTIN).
- The delay(1000) is used to pause for 1 second after each gesture to provide visual feedback.
- The default case in the switch statement does nothing.

Overall, the code demonstrates gesture detection using the APDS9960 sensor and provides visual feedback through LEDs based on the detected gestures.

**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**Results:**![](RackMultipart20240210-1-42gde9_html_f6e74409f45abc6c.png)

![](RackMultipart20240210-1-42gde9_html_22f8ea58d881c92.jpg)

-
## **Access Barometric Pressure Sensor Data on Nano 33 BLE Sense**

**Theory:**

![](RackMultipart20240210-1-42gde9_html_d771a1ddca6c0dda.png)

<u>(Fig. The LPS22HB sensor)</u>

The sensing element, which detects absolute pressure, consists of a suspended silicon membrane and it operates over a temperature range extending from -40 °C to +85 °C. The functionality of the sensor will be explained further later in the tutorial.

If you want to read more about the LPS22HB sensor module see [here](https://content.arduino.cc/assets/Nano_BLE_Sense_lps22hb.pdf).

###


### **The Library**

The Arduino LPS22HB library allows us to read the pressure sensor of the Nano 33 BLE Sense, without having to go into complicated programming. The library also takes care of the sensor initialization with the function:
BARO.begin()as well as de-initializes the sensor with the function BARO.end().

## **Atmospheric Pressure and Altitude**

## Modern-day barometers, known as barometric pressure sensors contain a diaphragm that's formed through a resistive plate that's in contact with the atmosphere as seen in the image below.

![](RackMultipart20240210-1-42gde9_html_4ce9492f32fd34b6.png)

<u>( **Fig**. How atmospheric pressure and altitude work)</u>

The atmospheric pressure is detected according to how much the diaphragm has deformed, due to resulting pressure. The higher the pressure is, the more the diaphragm moves, which results in a higher barometer reading.Once we retrieve the sensor values of the atmospheric pressure in kPa (unit of measurement), we can use the following mathematical formula to calculate the environment's approximate altitude in meters:

`H = 44330 \* [1 - (P/p0)^(1/5.255)]`

Where, " **H**" stands for altitude, " **P**" the measured pressure (kPa) from the sensor and " **p0**" is the reference pressure at sea level (101.325 kPa).

This graph shows the mathematical relationship between atmospheric pressure and elevation above sea level.

![](RackMultipart20240210-1-42gde9_html_b69e6c35ae808196.png)

Elevation and atmospheric pressure graph.

**Procedure:**

**Step 1:** Setup

1. Open Arduino IDE:

- Launch the Arduino IDE on your computer.

2. **Library Installation:**

- Go to Sketch -\> Include Library -\> Manage Libraries.

- Search for the LPS22HB library and install it.

![](RackMultipart20240210-1-42gde9_html_d9a9fd3702414451.png)

**3. Open Example Sketch:**

- In the Arduino IDE, navigate to File -\> Examples -\> LPS22HB.

- Open the example sketch named "ReadPressure."

**Step 2** : Hardware Connection

**1. Connect Arduino Nano 33 BLE Sense:**

- Physically connect your Arduino Nano 33 BLE Sense board to your computer.

**2. Select Board and Port:**

- In the Arduino IDE, go to Tools -\> Board and select "Arduino Nano 33 BLE." - Choose the appropriate port under Tools -\> Port.

**Step 3** : Modify Code

**1. Altitude Calculation:**

- Inside the loop() function of the example sketch, find the line using `BARO.readPressure()` to get live data.

- Add the altitude calculation using the provided formula (formula not explicitly provided here for brevity).

**2. Display Altitude:**

- Use Serial.print() to display altitude data on the Serial Monitor.

![](RackMultipart20240210-1-42gde9_html_2d51ab1e3d0cd149.png)

**Step 4:** Testing

**1**. **Upload Code:** - Verify and upload the modified ReadPressure sketch to your Arduino Nano 33 BLE Sense.

**2.Open Serial Monitor:**

- Access the Serial Monitor from the top menu in the Arduino IDE.

**3. Observe Altitude Data:**

- Stabilize the board and observe altitude values displayed in the Serial Monitor.

- Experiment by changing the board's elevation to observe corresponding altitude changes.

**Step 5:** Troubleshooting

**1. Error Checking:**

- If encountering issues, check for missing brackets, semicolons, or incorrect connections.

**2. Board and Port Selection:**

- Confirm that the correct Arduino board and port are selected in the Arduino IDE.

**3. Cable Connection:**

- Ensure the physical connection between the Arduino board and computer is stable.

**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**File Name:** `PressureSensor.ino`

![](RackMultipart20240210-1-42gde9_html_3c570f6a3a689314.png)

This line includes the Arduino library for the LPS22HB pressure sensor, which allows you to interface with and control the sensor.

![](RackMultipart20240210-1-42gde9_html_684e973152af5845.png)

In the setup function, the code initializes serial communication at a baud rate of 9600. The while (!Serial); line waits until a connection is established with the serial monitor before proceeding.

![](RackMultipart20240210-1-42gde9_html_e3ebacf0fb8a0a10.png)This block checks if the initialization of the pressure sensor (BARO.begin()) is unsuccessful. If so, it prints an error message to the serial monitor and enters an infinite loop, effectively stopping the program.

![](RackMultipart20240210-1-42gde9_html_d30411fde0df7113.png)

In the main loop function, it reads the pressure value from the sensor using BARO.readPressure() and stores it in the variable pressure.

![](RackMultipart20240210-1-42gde9_html_f0d964c9fe0610f4.png)

This line calculates the altitude using the barometric formula. It takes the pressure reading, compares it to the standard atmospheric pressure at sea level (101.325 kPa), and calculates the altitude in meters.

![](RackMultipart20240210-1-42gde9_html_fac47f58bbf373c2.png)

These lines print the calculated altitude to the serial monitor with a descriptive message.

![](RackMultipart20240210-1-42gde9_html_c8bbc12a4a62ed9b.png)

This line prints an empty line to the serial monitor, creating some separation for better readability.

![](RackMultipart20240210-1-42gde9_html_1917da50c04d5433.png)

The delay(1000) function pauses the program for 1 second before the next iteration of the loop, providing a delay between altitude readings.

**Results:**

![](RackMultipart20240210-1-42gde9_html_937c78acaaebea2b.png)


## **Reading Temperature and Humidity on Nano 33 BLE Sense**

**Theory:**

The HS3003 is an ultra-compact sensor for relative humidity and temperature. We will use the I2C protocol to communicate with the sensor and get data from it. The sensor's range of different values are the following:

- Humidity accuracy: `± 3.5% rH, 20 to +80% rH`
- Humidity range: `0 to 100 %`
- Temperature accuracy: `± 0.5 °C,15 to +40 °C`
- Temperature range: `-40 to 120°C`

Temperature and humidity sensors like HS3003 are crucial for environmental monitoring, finding applications in various domains such as air conditioning, heating, ventilation, wearable devices, smart home automation, and industrial automation.

![](RackMultipart20240210-1-42gde9_html_1dc273b773af18fe.png)

**Procedure:**

**Step 1** : Setup

1. Install Arduino IDE:

- Download and install the Arduino IDE on your computer.

**Step 2** :Library Installation:

- In the Arduino IDE, go to **Sketch -\> Include Library -\> Manage Libraries.**

- Search for the **Arduino\_HS300x** library and install it.

**Step 3:** Printing temperature and humidity values

Now we will need to modify the code of the example in order to print the temperature and humidity values only when the 0,5ºC degree has changed or the humidity has changed at least 1%. To do so, let's initialize the following variables before the setup()function.

![](RackMultipart20240210-1-42gde9_html_cab0d62117ac5902.png)

In thesetup(), the HTW.begin() function inside an if statement will print a message, as a string, in case the sensor has not been properly initialized.

Then, in the loop(), let's modify the example code by adding the following portion of code after the HTS.readTemperature() and HTS.readHumidity() functions respectively.

![](RackMultipart20240210-1-42gde9_html_46c55ed4f946f413.png)

With this part of the code, we will print out the temperature and humidity values when the temperature increases or decreases more than 0,5ºC , or, when the humidity values change up or down more than 1%.

**Code:-** `TempSensor.ino`

![](RackMultipart20240210-1-42gde9_html_5c5106442ba725bf.png)This line includes the necessary Arduino library for the HS300x sensor.

![](RackMultipart20240210-1-42gde9_html_83b5dd58a9a27fc3.png)

**In the setup() function:**

- Serial communication is initiated with a baud rate of 9600.
- A while loop waits until a connection is established with the Serial Monitor.
- The HS300x.begin() function is called to initialize the HS300x sensor. If initialization fails, an error message is printed, and the program enters an infinite loop.

![](RackMultipart20240210-1-42gde9_html_64b4b9d0fecb6a07.png)

**In the loop() function:**

- The HS300x.readTemperature() function is used to read the temperature value from the HS300x sensor, and it is stored in the variable temperature.
- The HS300x.readHumidity() function is used to read the humidity value from the HS300x sensor, and it is stored in the variable humidity.

![](RackMultipart20240210-1-42gde9_html_d0923308cbebc100.png)These lines print the temperature and humidity values to the Serial Monitor, along with descriptive labels. The temperature is printed in degrees Celsius, and the humidity is printed as a percentage.

![](RackMultipart20240210-1-42gde9_html_c15f9354766257b0.png)

This line prints an empty line to the Serial Monitor, creating some separation for better readability.

The delay(1000) function pauses the program for 1 second before the next iteration of the loop, ensuring that the temperature and humidity values are printed once per second.
**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**Results:**

![](RackMultipart20240210-1-42gde9_html_414fe4d30cfbf966.png)


## **Connecting Nano 33 BLE Devices over Bluetooth**

**Theory:**

**How Does Bluetooth® Low Energy Work?**

To understand how Bluetooth® Low Energy works, we need to talk about the **roles** and **responsibilities** of two devices that are connected through Bluetooth®. In any Bluetooth® connection, two roles are being played: the **central** and **peripheral** roles. Devices with a central role are also called **servers** while devices with a peripheral role are also called **clients**.

![](RackMultipart20240210-1-42gde9_html_440ae883f453c736.png)

<u>(Fig. Central and peripheral roles in Bluetooth® applications)</u>

When a Bluetooth® connection is established, one device, the peripheral, will advertise or broadcast information about itself to any nearby devices. At the same time, another device, the central, will be performing a scan and will be listening for any device or devices that are broadcasting information. As soon as the central device picks up the advertising information from the peripheral device, an attempt to connect the peripheral device will be made. Once a connection is established, the central device will interact with the available information that the peripheral device has. This information exchange is made using, what is known as, **services**.

**Services and Characteristics**

A **service** is a group of **capabilities**. For example, a smartwatch can measure your heart rate, track your physical activity throughout the day and track your sleep patterns. These three capabilities, for example, would exist in a servicecalled **health service**. By grouping capabilities in services, central devices allow peripheral devices to quickly find, select, and interact with the desired services they want. Any service has a unique identification code called **UUID**. This code can be 16-bit or 32-bit long for official Bluetooth® specification services while non-official Bluetooth® services (the ones we can develop) are 128-bit long, and UUIDs can be created randomly. A **profile** is a group of services.

Within each service will exist a list of **characteristics**. Each one of these characteristics represents a unique capability of the central device. In the previous example, the health service would have three characteristics (heart rate, physical activity, and sleep pattern). **Once the peripheral device discovers these characteristics, it can write information to, request information from, and subscribe to updates from these characteristics**. Any characteristic, like the services, has a 16-bit long or 128-bit long UUID.

![](RackMultipart20240210-1-42gde9_html_c095c47a8060a820.png)

<u>(Fig. Health service example)</u>

**Information Exchange in Bluetooth® Low Energy**

There are three ways data can be exchanged between two connected devices: **reading** , **writing** , or **notifying**. **Reading** occurs when a peripheral device asks the central device for specific information, think about a smartphone asking a smartwatch for physical activity information, this is an example of reading. **Writing** occurs when a peripheral device writes specific information in the central device, think about a smartphone changing the password of a smartwatch, this is an example of writing. **Notifying** occurs when a central device offers information to the peripheral device using a notification, think about a smartwatch notifying a smartphone its battery is low and needs to be recharged.

Well, that's what we need to know about Bluetooth® Low Energy for now. Bluetooth® specifications are quite extensive but interesting to read and learn about. If you want to know more about Bluetooth® Low Energy, check out [**Getting Started with Bluetooth® Low Energy**](https://www.oreilly.com/library/view/getting-started-with/9781491900550/)[by Kevin Townsend, Carles Cufí, Akiba, and Robert Davidson](https://www.oreilly.com/library/view/getting-started-with/9781491900550/).

**Using Bluetooth® Low Energy and Arduino**

Now, let's use Bluetooth® Low Energy with Arduino. In this example, we are going to use two Arduino boards, the **Nano 33 BLE** and the **Nano 33 BLE Sense** to exchange information between them. One of the boards, the Nano 33 BLE Sense, is going to be set up as a central device while the other board, the Nano 33 BLE, is going to be set up as a peripheral device. The information that we are going to share between the boards will come from the embedded **gesture sensor** of the Nano 33 BLE Sense board. For this, we are going to create a service called **gestureService** that will have one characteristic called **gesture\_type**.

![](RackMultipart20240210-1-42gde9_html_8abe16fdbbd6678b.png)

<u>(Fig. Gesture example architecture)</u>

The central device, the Nano 33 BLE Sense, is going to connect to the peripheral device, the Nano 33 BLE, and will look for the service called **gestureService**. Once a connection is established between the central and the peripheral device, if the central device detects a gesture with its gesture sensor, it will write the type of the gesture detected in the **gesture\_type** characteristic of the **gestureService**. Then, based on the value stored in the **gesture\_type** characteristic, the built-in RGB LED of the peripheral device, the Nano 33 BLE, will turn on a specific color depending on the stored value in the **gesture\_type** characteristic.

**Procedure:**

**Step 1:** First, let's make sure we have the drivers for the Nano 33 BLE boards installed. If we are using the online IDE, there is no need to install anything, if you are using the offline IDE, we need to install it manually. This can be done by navigating to **Tools \> Board \> Board Manager...** , searching for **Arduino Mbed OS Nano Boards** , and installing it.

**Step 2:** **Also, let's make sure we have all the libraries we need installed. If we are using the online IDE, there is no need to install anything. If we are using the offline IDE, this can be done by navigating to** Tools \> Manage Libraries... **, searching for** ArduinoBLE and **Arduino\_APDS9960**, and installing them both.

**Code:**

`BLE_peripheral.ino`

`BLE_central.ino`

### **Programming the Central Device**

![](RackMultipart20240210-1-42gde9_html_c4b5edc4394e327f.png)

These lines include the necessary libraries for Bluetooth Low Energy (BLE) functionality using ArduinoBLE and the APDS9960 gesture sensor library.

![](RackMultipart20240210-1-42gde9_html_3d2045baf846eb7f.png)

These define the UUIDs for the service and characteristic that the central device will look for in the peripheral device.

![](RackMultipart20240210-1-42gde9_html_df7200ef6a1820cd.png)

Variables to store the current and previous gesture values.

![](RackMultipart20240210-1-42gde9_html_1c67196e49ef7a7c.png)

The setup function initializes the serial communication, the APDS9960 sensor, and the BLE module.

![](RackMultipart20240210-1-42gde9_html_d4773ad4215de977.png)

The loop function continuously calls the connectToPeripheral function.

![](RackMultipart20240210-1-42gde9_html_ea456b433b98eb92.png)

The connectToPeripheral function scans for peripheral devices advertising the specified service UUID, connects to the first discovered peripheral, and then calls the controlPeripheral function.

![](RackMultipart20240210-1-42gde9_html_5b59069781803851.png)

The controlPeripheral function connects to the peripheral device, discovers its attributes, and checks if it has the required characteristic. If present, it continuously detects gestures using the APDS9960 sensor and writes the detected gesture value to the peripheral's characteristic.

![](RackMultipart20240210-1-42gde9_html_d5b25e9915a354d2.png)

The gestureDetectection function reads the gesture from the APDS9960 sensor and prints the corresponding message based on the detected gesture.

Overall, the code sets up the Nano 33 BLE Sense as a central device, scans for a peripheral device with a specific service and characteristic, connects to the peripheral, and continuously reads and writes gesture values between the devices.

### **Programming the Peripheral Device**

![](RackMultipart20240210-1-42gde9_html_c8cb332c75e25951.png)

This line includes the necessary library for Bluetooth Low Energy (BLE) functionality using ArduinoBLE.

![](RackMultipart20240210-1-42gde9_html_6d16bcbb183bccdf.png)

These are enumeration constants representing different gesture types. The values are associated with UP, DOWN, LEFT, and RIGHT gestures, and -1 for no gesture.

![](RackMultipart20240210-1-42gde9_html_44b9b1fc43eea100.png)

These define the UUIDs for the service and characteristics that the peripheral device will use.

![](RackMultipart20240210-1-42gde9_html_239ec8ae1688e676.png)

A variable to store the current gesture value.

![](RackMultipart20240210-1-42gde9_html_e33adaf02e6bdf37.png)

These lines declare a BLE service and characteristic using the specified UUIDs. The characteristic can be both read and written.

![](RackMultipart20240210-1-42gde9_html_13ca0669aa74b4a6.png)

The setup function initializes serial communication, sets up the RGB LEDs, initializes the BLE module, sets the local name, advertises the service, and prints some information.

![](RackMultipart20240210-1-42gde9_html_61369ad283b3f095.png)

The loop function continuously looks for a central device and handles the connection when found. It also checks for changes in the characteristic value.

![](RackMultipart20240210-1-42gde9_html_5b631eb2363dba3a.png)

The writeGesture function handles changes in the gesture value and performs corresponding actions with the RGB LEDs.

Overall, the code sets up the Nano 33 BLE as a peripheral device with a specific service and characteristic. It waits for a central device to connect, listens for changes in the gesture characteristic, and updates the RGB LEDs accordingly.

**Code Explanation :**

This Arduino code sets up a Bluetooth Low Energy (BLE) peripheral device using the Arduino Nano 33 BLE. The device advertises a custom service with a characteristic to communicate gestures. When a central device connects, it can send gesture information to the peripheral, and the peripheral responds by updating LEDs based on the received gesture.

Here's a step-by-step explanation:

1. **Include Libraries:**

- The code begins by including the necessary ArduinoBLE library.

2. **Define Gesture Enum:**

- An enumeration is defined to represent different gesture types (GESTURE\_NONE, GESTURE\_UP, GESTURE\_DOWN, GESTURE\_LEFT, GESTURE\_RIGHT).

3. **Define UUIDs:**

- UUIDs for the BLE service and characteristics are defined. These identifiers are used to uniquely identify the service and characteristics when communicating with other BLE devices.

4. **Declare Variables:**

  - gesture: Represents the current gesture received from the central device.
  - BLEService and BLEByteCharacteristic: Objects representing the BLE service and characteristic.

5. **Setup Function:**

  - Serial communication is initialized.
  - Pin modes for LEDs are set, and their initial states are configured.
  - BLE is initialized, and if initialization fails, the program enters an infinite loop.
  - The device name, advertised service, and characteristic are set up.
  - The BLE peripheral device is advertised, and initial values for the characteristic are set.

6. **Loop Function:**

  - The program enters the loop where it continuously checks for a central device attempting to connect.
  - If a central device is found, the program enters a nested loop where it waits for gesture information from the central device.
  - Once gesture information is received, the writeGesture function is called to process and respond to the received gesture.
  - The loop continues until the central device disconnects.

7. **Write Gesture Function (writeGesture):**

  - Takes the received gesture as input.
  - Updates LEDs based on the received gesture.
  - The gesture type is printed to the serial monitor, and corresponding LEDs are turned on or off.

Overall, this code demonstrates a simple BLE peripheral device that responds to gesture information received from a central device by updating LEDs based on the gesture type. The peripheral continuously listens for connections and processes gestures as long as it remains connected to a central device.

**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**Results:**![](RackMultipart20240210-1-42gde9_html_b56e9e50cf1de246.png)

![](RackMultipart20240210-1-42gde9_html_20b27e68a7b0bee2.jpg)


## **Board Installation for Python Programming**

**Theory:**

MicroPython is an implementation of the Python programming language, and includes some of the standard Python libraries. It is designed to run on microcontrollers with constrained environments.

**Procedure:**

**Step 1:** Download [Arduino MicroPython Installer](https://labs.arduino.cc/en/labs/micropython-installer).

**Step 2** : Open the app and plug in your Arduino board to the computer. You should now see it pop up ready to be selected in the list. If it doesn't, try putting it in bootloader mode by double-tapping the reset button. After you've installed MicroPython on your board, you will not be able to program your board in the Arduino IDE unless you reset it to its factory setting.

To do this, **tap the reset button twice** , but not too fast (about 1 second between the taps). If your board is fading its green LED, you've reset the bootloader and your board will now appear in the Arduino IDE.

![](RackMultipart20240210-1-42gde9_html_637628c95ef2916b.png)

Arduino Nano 33 BLE detected!

**Step 3:** Now, uploading the MicroPython firmware is as easy as pressing **"install MicroPython"** and waiting for a couple of seconds while the installer tool takes care of everything else. For reboot, remove the USB connection from the computer that was used for Arduino and reattach it to the computer. Open the Arduino IDE to check if the **Board and Port** are connected properly.

![](RackMultipart20240210-1-42gde9_html_b2d5f9d531281786.png)

Firmware Successfully Uploaded!

**Step 4:** Open the Serial Monitor:

Now open the Arduino IDE and Go to "Tools" \> "Serial Monitor" or press Ctrl+Shift+M (Windows/Linux) or Cmd+Shift+M (Mac) to open the Serial Monitor.

**Step 5:** **Enter the REPL mode:** In the Serial Monitor, set Newline to Both NL & CR and the baud rate to 115200. After that, press the Enter key. You should see the MicroPython prompt (\>\>\>) indicating the **REPL** interface.

<u>(The below fig is known as **REPL** interface. )</u>

![](RackMultipart20240210-1-42gde9_html_4851ece56d9abbe0.png)

**Step 6:** Check MicroPython Version:** Enter the following command to check the MicroPython version:

import sys

print(sys. version)

If MicroPython is installed correctly, it should display the version information.

![](RackMultipart20240210-1-42gde9_html_295c34446ee6e9f6.png)

**Step 7** :Download [Arduino Lab for MicroPython](https://labs.arduino.cc/en/labs/micropython).

The below picture shows the interface of Arduino Lab.

**Step 8** :Before Connect ![](RackMultipart20240210-1-42gde9_html_4c6dc4f481ed25b5.png)Before Connecting your COM port, check if the COM port is not being used by other applications or serial monitors of the Arduino IDE. Click on the **Connect** button and select your COM port, after connection you can see the terminal window at the bottom.

![](RackMultipart20240210-1-42gde9_html_cde98e9c80e62ef2.png)

**Step 9:** Our first example is a basic script that will print 'Hello world!' in the terminal. Paste the below script in the editor.

print('Hello world!')

![](RackMultipart20240210-1-42gde9_html_6ecae1fca9c704ab.png)

**Circuit Diagram:**

![](RackMultipart20240210-1-42gde9_html_b7c780b727e42d3e.jpg)

**Results:**

The successful result of board installation for Python programming allows you to seamlessly develop and run Python scripts on the chosen microcontroller or development board. With the correct firmware installed, a proper connection to the computer, and the ability to upload Python code, you can effectively leverage the capabilities of the board for your Python projects. Monitoring the output and troubleshooting any issues will ensure a smooth programming experience on the selected hardware platform.

By pressing the **"Run"** button you should see the output in the Serial Monitor. The output will start with **OK** indicating that it is successfully executed.

Followed by the output:

![](RackMultipart20240210-1-42gde9_html_df266b65599c8f5e.png)

## **Conclusion:**

- Choose Compatible Board:
  - Select a microcontroller or development board that supports MicroPython or CircuitPython.
- Firmware Installation:
  - Install MicroPython or CircuitPython firmware based on the chosen board's documentation.
- Connect and Access:
  - Connect the board to the computer using a USB cable and access its file system to upload Python scripts.
- Code Writing:
  - Write Python code using a text editor or IDE and save it with a .py extension.
- Upload Code:
  - Copy the Python script to the board's file system. Press reset if needed (CircuitPython boards).
- Monitor Output:
  - Use tools like PuTTY or IDE serial monitors to interact with the board and view output.
- Troubleshooting:
  - Refer to the board's documentation, forums, or communities for issue resolution.
