# **Speech Recognition Documentation**

## **Overview:**

Nano BLEsense Speech Recognition is a project aimed at enabling speech recognition capabilities on the Nano BLEsense development board. This documentation provides an overview of the project, including its purpose, References, Code, and implementation steps.

The purpose of Nano BLEsense Speech Recognition is to create a portable and low-power speech recognition system using the Nano BLEsense board. By integrating speech recognition capabilities into the board, developers can build applications ranging from voice-controlled IoT devices to wearable gadgets with speech interaction.

## **Reference:**

1. Check [Speech Code](https://drive.google.com/file/d/15iDmkifs_hNAZCab8v8PSXJMBX0ygC78/view?usp=sharing)
2. Check [Youtube video](https://www.youtube.com/playlist?list=PL3E6XmqhhLBHXX2fG2dVER-LOq_7nl9p6)


## STEP 1: Arduino IDE Setup

- Open the Arduino IDE application on your computer.
- Choose the board `Tools -> Board -> Arduino Nano 33 BLE`
- Choose the port `Tools -> Port -> COM3 (Arduino Nano 33 BLE)` **Note that the actual port may be different on your computer**.
- To start with micro Speech Go to `Files-> Examples -> Arduino_Tensorflowlite -> micro_speech`, Upload the sketch to the board using the `Sketch -> Upload` menu or the right arrow button from the toolbar.
- Open the Serial Monitor `Tools -> Serial Monitor` to view the text output.

![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/SR_img/sr1.png?raw=true)

- Board select:

![](RackMultipart20240211-1-hy0u9q_html_c1c9d8b3981a2cf4.png)

## STEP 2: Compile

- Compile the sketch and upload it to the board: `Sketch -> Upload`
- Press the reset button on the board
- Open the Serial Monitor: `Tools -> Serial Monitor` and keep **newLine** to `Both NL & CR` and **baud rate** to `9600 baud`

## STEP 3: Observe

- Objective Clarity:
  - The project aims to implement a speech recognition system on the board, enabling it to respond to specific commands with LED indications.
- User Interaction Enhancement:
  - By associating LED colors with recognized commands (`"yes"`, `"no"`, and `"unknown"`), the system offers immediate visual feedback to users, improving interaction and understanding.
- Clear Command Feedback:
  - **Green LED signifies** the detection of `"yes"`, **red LED indicates** `"no"`, and **blue LED represents** an `"unknown"` command. This clear feedback mechanism aids users in understanding the system's recognition status.
- Hardware Integration:
  - The function abstracts hardware-specific details, ensuring compatibility with different hardware configurations. This promotes portability and ease of deployment across various devices.
- Real-time Responsiveness:
  - The system responds promptly to detected commands, providing users with timely feedback and enhancing the overall user experience.

## STEP 4: Output

![](RackMultipart20240211-1-hy0u9q_html_9ebbbfe59d5321be.png)

(Fig. **Serial output**)

Serial printing prints the real time Output of the board on the serial monitor.

![](RackMultipart20240211-1-hy0u9q_html_dda60bdbaefdd023.png)

(Fig. **"Unknown" Indication**)

`Blue LED Indicator`: When the board fails to detect the predefined input, it activates a "Blue" LED. This serves as a visual cue indicating that the expected input signal is not present or has not been received.

![](RackMultipart20240211-1-hy0u9q_html_3b48ca29b6b282b8.png)

(Fig. **"Yes" Indication**)

`Green LED Indicator`: Upon successful detection of the input signal as "Yes," the board triggers a "Green" LED to illuminate. This signals to the observer that the input has been recognized as affirmative or positive.

![](RackMultipart20240211-1-hy0u9q_html_3bfffbf7efbab21a.png)

(Fig. **"No" Indication**)

`Red LED Indicator`: Conversely, when the input signal is identified as "No," the board activates a "Red" LED. The glowing red light serves as an indication that the input received was negative or contrary to the expected response.
