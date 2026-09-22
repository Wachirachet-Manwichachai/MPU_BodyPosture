# Innovator Journal — Posture Monitoring System
## 1. Starting Point

During this unit, I became most interested in MPU as it complexity is similarly to matrix as their 3 axis where I learning the basic at this time, which linked my interest into MPU. As I also pick LCD display to used it into motoring real time information with limitation on the representation with only 16x2 spaces.

## My first prototype

At first, I want to build measurement system that show how how far an object had been lifted and at what angle it had been tilted. My idea is to used MPU to measure the angle and the location it have been lifted. 

## Changing concept to the second prototype

While researching sensors and thinking about how I could make the project more meaningful and impactful, I realized that the MPU-6050 could be used to measure orientation and tilt. Instead of only measuring an object being lifted, after brainstroming the idea, I came out with "human posture".


## 2. New Component

For this project, I chose the MPU-6050 accelerometer/gyroscope module.

I used two MPU-6050 modules so that I could monitor two different parts of the body: the upper back and lower back.

The sensors communicate with the Arduino using I²C. Since both sensors normally use the same I²C address, I configured one sensor as 0x68 and the other as 0x69 using the AD0 pin.

## 3. My Goal

My goal was to create a system that could measure the orientation of two parts of the back:
* Upper back
* Lower back

Then set a range for medium, and bad posture.

## 4. What I Tried
I tried adding an buzzer to this project to improve the alarm system when it reach medium and bad posture. However, when I tried testing it, it keep beeping continuously instead of only activating after medium (slower) and bad(faster) posture.

## 5. What I struggled
Eventhough the code is working, I wonder why is work as I deeply learning from everyline and it meaning. Until almost the end there a function that is not fimilar to my mind, but I guessed that it was related to calculating the angle. This was one of the most challenging parts of the project because it required me to understand not only Arduino code, but also some mathematics and how accelerometer data represents physical orientation.

## 6. Peer Support
I helped Sean to connect LCD display, where I show him step by step of checking where is the problem and why is it not working. Additionally, this weekend I also helped him fix his broken LCD display, but this problem is weird as the light is on but the letter showed. I checked the wiring for LCD display but there's nothing wrong, so I shifted to what component he have that might interupted LCD. Which he used motor where the wiring is fine, so I checked the code where he seem didn't include motor into the code yet, that might be the reason why it is not working. This show me that the problem might not come from itself rather than something that work together and might end up be the problem itself.

## 7 . Reflection

What kind of problem or situation could this input or output be useful for, and for whom?
What would need to change or be added to your current build to actually be useful in that situation?
What's one skill from this unit (wiring, debugging, reading a datasheet, debouncing, etc.) that you'd rely on most if you kept developing this idea?
