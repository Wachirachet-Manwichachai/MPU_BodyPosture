# Posture Monitoring System

An Arduino posture monitoring system that uses **two MPU-6050 accelerometer sensors** to measure the orientation of the upper and lower back and provide real-time posture feedback through a **16×2 LCD display**.

## Project Overview

This project was designed to monitor sitting posture by measuring the angle of different parts of the back(upper and lower). During startup, the user sits in their desired posture while the system performs a short 5s calibration.

The system then continuously measures the user's current angles and calculates how far they have deviated from the initiated position.

## How It Works

1. The Arduino initializes the two MPU-6050 sensors and the LCD display.
2. The user sits in their desired posture during a **5-second calibration**.
3. The system records the upper- and lower-back angles as baseline values.
4. The accelerometers continuously measure the current orientation.
5. The Arduino calculates the **pitch angle** using the X, Y, and Z acceleration values.
6. The current angle is compared with the calibration baseline.
7. The angular deviation is classified as:
   * **Good**
   * **Medium**
   * **Bad**
8. The results are displayed on the LCD and sent to the Serial Monitor.

## Components

* Arduino Uno
* 2 × MPU-6050
* 16×2 LCD Display
* Jumper wires
* Breadboard
* Uploading Cable

## Communication

The two MPU-6050 sensors communicate with the Arduino using **I²C**.

Because both sensors are the same device, they use different I²C addresses:

| Sensor      | Location   | I²C Address |
| ----------- | ---------- | ----------- |
| MPU-6050 #1 | Upper Back | `0x68`      |
| MPU-6050 #2 | Lower Back | `0x69`      |

The LCD uses a parallel interface connected to Arduino digital pins.

## Angle Calculation

The project currently uses the **accelerometer** of the MPU-6050. The gyroscope is not included.

The raw acceleration measurements are converted into acceleration in terms of `g` and then used to calculate the pitch angle:

```text
Pitch = atan2(X, √(Y² + Z²)) × 180 / π
```

The calculated angle is compared with the angle recorded during calibration.

```text
Deviation = |Current Angle − Baseline Angle|
```

## Posture Classification

The system uses different thresholds for the upper and lower back.

### Upper Back

| Deviation | Status |
| --------: | ------ |
|     < 20° | Good   |
| 20°–29.9° | Medium |
|     ≥ 30° | Bad    |

### Lower Back

| Deviation | Status |
| --------: | ------ |
|     < 10° | Good   |
| 10°–14.9° | Medium |
|     ≥ 15° | Bad    |

These thresholds are configurable in the Arduino code.

## Example LCD Output

```text
U:12.5°   Good
L:6.2°    Good
```

If the user's posture deviates further:

```text
U:24.7°   Medium
L:12.1°   Medium
```

## Serial Monitor

The Arduino also outputs the raw calculated angles and deviations for debugging and analysis.

Example:

```text
Upper_Raw: -12.40 | Upper_Dev: 18.20 || Lower_Raw: 5.30 | Lower_Dev: 7.10
```

## Future Improvements

Possible future improvements include:

* Make it more economically fit the sitting body posture
* Make it wireless by using bluetooth
* Creating a historical dashboard for analysis
* Add vibration or buzzer for posture alerts

## Project Structure

```text
Posture-Monitoring/
│
├── Posture-Monitoring.ino
├── README.md
└── Journal.md
```
