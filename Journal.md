# Project Journal

## Week 1 — Initial Design

### Goal
Build a posture-monitoring system using two MPU-6050 sensors.

### What I Did
- Researched the MPU-6050.
- Learned how I²C communication works.
- Designed the initial sensor placement.
- Tested communication between the Arduino and one MPU-6050.

### Problems
- Both MPU-6050 sensors initially had the same I²C address.

### Solution
Connected the AD0 pin of the second MPU-6050 to 3.3V, giving it address `0x69`.

### What I Learned
I learned how two identical I²C devices can communicate with the same Arduino by using different addresses.
