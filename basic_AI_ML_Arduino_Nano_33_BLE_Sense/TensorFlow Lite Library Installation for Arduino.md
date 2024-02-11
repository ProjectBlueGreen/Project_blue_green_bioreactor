# Installing TensorFlow Lite for Arduino 33 BLE Sense:

## Table of contents:
* [Prerequisites](#prerequisites)
* [Step 1: Open Arduino Libraries Folder](#step-1-open-arduino-libraries-folder)
* [Step 2: Downloading the TensorFlow Lite Micro Library (Manual downloading or Git clone)](#step-2-downloading-the-tensorflow-lite-micro-library-manual-downloading-or-git-clone)
    * [Manual Downloading](#manual-downloading)
    * [Git clone (Optional)](#optional-git-clone-clone-the-tensorflow-lite-micro-repository)
* [Step 3: Update the Repository (Optional)](#step-3-update-the-repository-optional)
* [Step 4: Checking your Installation](#step-4-checking-your-installation)
* [Conclusion](#conclusion)


## Prerequisites

- **Arduino IDE:** Make sure you have the [Arduino IDE](https://www.arduino.cc/en/software) installed on your computer.
- **Git (Optional):** Install Git on your computer if you don't have it. You can download it from [here](https://git-scm.com/).

## Step 1: Open Arduino Libraries Folder

- Locate the libraries folder for the Arduino IDE on your computer. The location depends on your operating system:
  - **Linux:** `~/Arduino/libraries`
  - **MacOS:** `~/Documents/Arduino/libraries/`
  - **Windows:** `\Documents\Arduino\Libraries`

## Step 2: Downloading the TensorFlow Lite Micro Library (Manual downloading or Git clone)

### Manual Downloading:

- Go to [this Reposiroty](https://github.com/palnitin24/Arduino_TensorFlowLite)
- Download the repository in a zip file: Go to `Code -> Download Zip`

   ![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/TF_Img/TF1.png?raw=true)

- Extract the downloaded zip file in `C:\Users\your_pc\username\Documents\Arduino\libraries`
- Rename the file to **Arduino\_TensorFlowLite**

### (Optional Git clone): Clone the TensorFlow Lite Micro Repository

- Open a terminal or command prompt by pressing `windows` + `R` button and type `cmd` and press `OK` to launch it.
- Navigate to the Arduino libraries folder. For example, on windows, you can use `cd` the command:
    ```
    cd C:\Users\your_pc\username\Documents\Arduino\libraries
    ```
    <img src="https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/TF_Img/TF2.png?raw=true" width="320" alt="Alt Text">
    
- Clone the TensorFlow Lite Micro Arduino Examples repository using the following command:
    ```
    git clone https://github.com/palnitin24/Arduino_TensorFlowLite Arduino_TensorFlowLite
    ```

   ![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/TF_Img/TF3.png?raw=true)

**Note:** If you are getting an error `fatal: could not create work tree dir "Arduino_TensorFlowLite": No such file or directory` so probably your windows is blocking git to make any changes in the folder. So go to your pc `settings -> windows security -> allow the access`. After this the issue will be resolved and you can see the cloning process completed successfully.

## Step 3: Update the Repository (Optional)

- If you want to update your clone to the latest version later, navigate into the TensorFlow Lite Micro Arduino Examples folder:
    ```
    cd Arduino_TensorFlowLite
    ```

- Use the following command to pull the latest changes from the repository:
    ```
    git pull
    ```

## Step 4: Checking your Installation

- Once the library has been installed, you should then start the Arduino IDE. You will now see an `Arduino_TensorFlowLite` entry in the `File -> Examples` menu of the Arduino IDE. This submenu of **Arduino_TensorFlowLite** contains a list of sample projects you can try out.

   ![](https://github.com/ProjectBlueGreen/project_blue_green_software/blob/main/basic_AI_ML_Arduino_Nano_33_BLE_Sense/assets/TF_Img/TF4.png?raw=true)

## Conclusion

After completing these steps, you should have the TensorFlow Lite Micro library for Arduino installed in the `Arduino_TensorFlowLite` folder within your Arduino libraries directory.

Now, you can use the **Arduino IDE** to open the **examples** provided in the **Arduino_TensorFlowLite** folder and start experimenting with TensorFlow Lite on your **Arduino 33 BLE Sense board**.
