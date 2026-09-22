# Innovator Journal — Posture Monitoring System
## 1. Starting Point: What I Built On

During this unit, I became most interested in MPU as it complexity is similarly to matrix as their 3 axis where I learning the basic at this time, which linked my interest into MPU. As I also pick LCD display to used it into motoring real time information with limitation on the representation with only 16x2 spaces.

## 2. New Component

For this project, I chose the MPU-6050 accelerometer/gyroscope module.

I used two MPU-6050 modules so that I could monitor two different parts of the body: the upper back and lower back.

The sensors communicate with the Arduino using I²C. Since both sensors normally use the same I²C address, I configured one sensor as 0x68 and the other as 0x69 using the AD0 pin.

What I researched

I researched:

MPU-6050 pin configuration
I²C communication
MPU-6050 register addresses
Accelerometer measurements
Calculating pitch from X, Y, and Z acceleration
Arduino Wire.h communication
3. My Goal

My goal was to create a system that could measure how much a person's posture changes from a calibrated sitting position.

The system would:

Ask the user to sit straight.
Record the initial angles.
Continuously measure the current angles.
Calculate the difference from the original position.
Display the result as Good, Medium, or Bad.
4. What I Tried
First Attempt

I first tested communication with the MPU-6050 and tried to read its sensor data through I²C.

I learned that the MPU-6050 stores its accelerometer measurements across multiple registers, so I needed to read several bytes and combine them into X, Y, and Z values.

Problem I Encountered

One of the challenges was using two identical MPU-6050 sensors at the same time. Both sensors normally use the same I²C address, which means the Arduino would not be able to distinguish between them.

What I Changed

I connected the AD0 pin of one MPU-6050 to 3.3V. This changed its I²C address from 0x68 to 0x69.

This allowed both sensors to communicate with the same Arduino.

5. Calibration

I added a five-second calibration countdown.

During calibration, the user sits in their desired posture. At the end of the countdown, the Arduino records the current angle from each sensor.

These values become the baseline:

Upper Baseline = calibration angle from upper sensor
Lower Baseline = calibration angle from lower sensor

The system then calculates:

Deviation = |Current Angle - Baseline Angle|
6. Final Working System

The final system uses:

Arduino
2 × MPU-6050
16×2 LCD
I²C communication
Accelerometer-based pitch calculation

The LCD displays the deviation and posture status in real time.

Example:

U:12.5°   Good
L:6.2°    Good

[Insert photo/video of final circuit here]

7. Debugging

One of the most important parts of the project was debugging.

When the circuit or code did not work, I had to determine whether the problem came from:

Wiring
I²C communication
Sensor addresses
Arduino code
Incorrect register addresses
Sensor readings
Angle calculations

Instead of assuming the entire project was broken, I tested individual parts to identify the source of the problem.

8. Peer Support

[Write about a REAL interaction with a classmate here.]

For example:

While I was working on [specific part], I had trouble with [specific problem]. I asked [classmate] for help, and they [specific thing they did or suggested]. This helped me realize [what you learned]. After that, I changed [what you changed].

9. Reflection: Real-World Application

A system like this could potentially be useful for people who spend long periods sitting, such as students or people who work at desks. It could provide a reminder when someone's posture moves significantly away from their calibrated position.

However, my current prototype would need several improvements before it could become a practical system. For example, I would need to improve sensor accuracy, reduce noise, make the device comfortable to wear, and potentially add an alert such as a buzzer or vibration motor.

The skill from this unit that I would rely on most is debugging. With a more advanced version, there would be many different possible causes of incorrect readings, so being able to test each part of the system individually would be important.

10. What I Would Do Next

If I continued developing this project, I would like to:

Use the gyroscope together with the accelerometer.
Add sensor fusion to produce more stable angle measurements.
Improve the calibration process by averaging multiple readings.
Add a buzzer or vibration motor for alerts.
Record posture data over time.
Create a graph or dashboard showing posture changes.
Make the system smaller and easier to wear.
11. What I Learned

Through this project, I learned how to work with a new sensor without having a complete step-by-step tutorial. I learned how I²C addresses allow multiple devices to communicate with one Arduino, how accelerometer data can be used to estimate orientation, and how debugging requires testing individual parts of a system rather than changing everything at once.
