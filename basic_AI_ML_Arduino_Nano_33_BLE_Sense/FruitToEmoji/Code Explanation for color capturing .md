# **The code explanation of the color_capturing.ino sketch :**


## **Objective:**

- The purpose of this sketch is to sample color data from objects placed near the color sensor on the Arduino Nano 33 BLE Sense board.

- It captures the color information and outputs it in CSV format via the serial console.

## **Setup Section:**

- The `setup()` function is called once during initialization.

- Serial communication is initialized at a baud rate of `9600`.

- The sketch waits for the serial connection to be established (indicated by `while (!Serial) {};`).

- The `APDS9960` sensor (color and proximity sensor) is initialized.

- The header line `Red`, `Green`, `Blue` is printed to the serial console.

## **Loop Section:**

- The `loop()` function runs continuously after setup.

- It waits until both color data and proximity data are available from the sensor.

- The color sensor reads the `red (r)`, `green (g)`, `blue (b)`, and `clear (c)` values.

- The sum of red, green, and blue values is calculated (`sum = r + g + b`).

- The proximity value (`p`) is also read.

- If the object is close (**proximity value is 0**), well-illuminated (**clear value greater than 10**), and the sum of color values is positive:

    - The normalized color ratios (`redRatio`, `greenRatio`, `blueRatio`) are calculated.

    - The data is printed in CSV format with three decimal places.

    - The format is: `redRatio, greenRatio, blueRatio`.

## **Color Ratios:**

- The normalized color ratios are calculated as follows:

    - redRatio = `r / sum`

    - greenRatio = `g / sum`

    - blueRatio = `b / sum`

## **Output:**

- The sketch continuously samples color data from nearby objects and prints it in CSV format.

- You can observe the color ratios in the serial monitor.

## **Next Steps:**

- This sketch is part of a larger project that combines Arduino, TensorFlow Lite Micro, and machine learning.

- The color data collected here could be used for further analysis or classification tasks.

```c
#include <Arduino\_APDS9960.h>

void setup() {

`	`Serial.begin(9600);

`	`while (!Serial) {}; // Wait for serial connection

`	`if (!APDS.begin()) {

`    	`Serial.println("Error initializing APDS9960 sensor.");

`	`}

`	`// Print the header

`	`Serial.println("Red,Green,Blue");

}

void loop() {

    int r, g, b, c, p;

    float sum;

    // Wait for proximity and color sensor data

    while (!APDS.colorAvailable() || !APDS.proximityAvailable()) {}

    // Read the color and proximity data

    APDS.readColor(r, g, b, c);

    sum = r + g + b;

    p = APDS.readProximity();

    // If object is close and well-illuminated

    if (p == 0 && c > 10 && sum > 0) {

        float redRatio = r / sum;

        float greenRatio = g / sum;

        float blueRatio = b / sum;

        // Print the data in CSV format

        Serial.print(redRatio, 3);

        Serial.print(',');

        Serial.print(greenRatio, 3);

        Serial.print(',');

        Serial.print(blueRatio, 3);

        Serial.println();

    }

}
```


