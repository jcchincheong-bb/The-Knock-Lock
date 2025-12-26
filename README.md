>>>
**Project-Template**

Please use this template for your practical electronics project. (feel free to delete this section) 

You can find a quick guide in the following [cheat sheet](https://www.markdownguide.org/cheat-sheet/) or specific [gitlab style](https://docs.gitlab.com/ee/user/markdown.html) here

>>>

**Make sure your submit your deliverables (project description, schematic, pcb design and report on time - timestamp is used as reference)


----

# Title of the project

by: *Names of the authors*


**Faculty of Technology and Bionics**

***Rhine-Waal University of Applied Sciences***

Date: XX January 2022

----

## Abstract

Short summary of the project and the work conducted

## Table of Contents

[[_TOC_]]

## 1 Introduction
We have all built secret passwords, sometimes words, sometimes numbers, sometimes just a pattern of knocking, sometimes it was to get into a box castle, sometime a room. 

Suprisingly, the password nowadays are boring, just words, numers, NFCs sometimes biometric. However what happened to the secret knock? In this project we want to create a 
more fun way to unlock a door, while also keeping it safe using a secret knock pattern, with millions of potential permutations. This unlocking mechanism can be used for 
getting through a door, open a drawer, or opening a safe box, the possibilities are endless. 

The KnockLock Project will demonstrate the idea by implementation into a lock box.

### 1.1	Teaser <! -- I have changed background to teaser -->
The primary goal of this project is to be able create a system which can detect knocks reliably with correct timings in order to identify if it is the correct pattern
or not, and react accordingly. For the detection an accelerometer will be used.

For this we will have to first understand, if this has been done before, if so how can it be improved. If not it must be compared to the exhisting methods. This will talked about
in the literature review in Chapter 2.

Further more we must understand how an accelerometer works, and how to interface it with a microcontroller. This will be presented in Chapter 3.

Then we shall talk about how we it will be implemented (Chapter 5: Methodology) and what results were achieved (Chapter 6: Results). Finally we will discuss the results (Chapter 7: Discussion)

Before all this lets outline the requirements for the project.

### 1.2	Requirements
To fully implement the system, a number of requirements related to function, technology and project management have been outlined. 

### 1.2.1 Functional Requirements

For Knock Knock Lock Box to be a satisfiable product, the following functional requirements must be implemented:

- It unlocks within 1-2 seconds when a specific knocking pattern is used on the surface of the box
- It turns a green LED on and simultaneously plays a simple beep to indicate that the box has been unlocked
- It rejects pattern if incorrect within 1-2 seconds after knocking has ended
- It turns a red LED on and simultaneously plays a simple alarm to indicate that the knocking pattern was false or unrecognized
- It alerts when the battery level drops below a certain level by flashing a red LED, even in power saving mode
- It only powers on after some initial knock to wake up the system, on wake it shows an yellow LED
- If no knocks detected for 30 seconds, it goes back to power saving mode
- It has provision to use a Micro USB port as an alternative power source in case battery dies out, with no prospect to upload firmware through it
- It uses a servo motor for unlocking and locking 

Some further optional and advanced features include:

- It has a programming mode where the user sets the knock for the system to recognize, mode can only be entered when the box is unlocked (for example using NFC)
- It has an NFC to unlock the box in case of system failure
- It alerts user in case door is left unlocked for a long time using beep sound

### 1.2.2 Technical Requirements

For the Knock Knock Lock Box to operate and perform its functions, the following technical requirements must be implemented:

- The accelerometer can detect at knock amplitudes and output a measurable voltage reading to the MCU
- There are provisions to protect the sensor and MCU from voltage spikes that might occur from the power supply
- The MCU Software can detect at most 30 knocks with consequitive knocks being less than 2s apart and match the timings to the predefined knock pattern with a set tolerance of acceptance
- The power supply is a battery with a working voltage of 3.2V to 5.5V
- The enclosure can protect the system within a typical indoor environment (IP 31)
- The provision to set MCU to low power mode and wake it back up
- Should function at temperatures ranging 0-40°C and humidity 10-90%

### 1.2.3 Project Requirements

For the Knock Knock Lock Box project to produce a functional product upon close out, the following project requirements must be met:

- the budget is 25€ not including the PCB
- the project workload is estimated at 240h
- the project schedule adheres to the following deadlines
    - Schematic Design: 2025-10-26
    - PCB Design Draft: 2025-11-09
    - PCB Design and Partslist: 2025-11-23
    - PCB Assembly: 2025-12-20
    - Project Report and Presentation: 2026-01-11

## 2	Literature review
Many projects have been made to ease unlocking a device, for example using RFID, NFC, Bluetooth, WiFi, fingerprint sensors etc. Some have also implemented knock detection, 
These projects have used various techniques to detect knocks, such as using piezo sensors, vibration sensors etc. These will be discussed here

### 2.1	Related Work
Piezo sensors have been the primary choice in most project, such as [1]. Here a Arduino Duemilanove has been used with a piezo sensor to detect knocks and a gear reduction motor 
acts as the actuator to open the lock. Another project [2] uses a similar approach, but uses a solenoid as the actuator and an Arduino Nano instead. [3] also again uses a piezo sensor 
but a servo motor as an actuator.

All these projects have used piezo sensors to detect knocks, which is a good choice as they are cheap and easy to use. However, they are also prone to noise and false positives. 
Even after extensive research, we could not find any project that used an an accelerometer to detect knocks.

## 3	Theory
If necessary please present theory in this section.

This math is inline $`a^2+b^2=c^2`$.

## 4	Methodology
How was your approach to solve the given problem/task.
This will include descriptions of the HW used as well as the SW.

This is an example how to include code snippet:
```python
def function():
    #indenting works just fine in the fenced code block
    s = "Python code"
    print s
```

Example how to draw a table:

| Left Aligned | Centered | Right Aligned |
| :---         | :---:    | ---:          |
| Cell 1       | Cell 2   | Cell 3        |
| Cell 4       | Cell 5   | Cell 6        |
| OpAmp 741    | 2        | 1.00          |


## 5	Results
Here you should present your results.

This is an example how to include image:
![alt text](resources/Open_Source_Hardware_(OSHW)_Logo_on_blank_PCB.jpg "Example Image")
(C) Altzone, CC BY-SA 3.0 <https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia Commons


## 6	Discussion
Here you should discuss your results

## 7	Concluding Comments
You might want to discuss possible future work here

## 8	References

* [1]: Instructables. (2022, May 8). Secret knock detecting door lock. Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Secret-Knock-Detecting-Door-Lock/ 
* [2]: Dodhia, V. (2021, June 20). Arduino secret knock pattern door lock. Viral Science. Retrieved November 20, 2025, from https://www.viralsciencecreativity.com/post/arduino-secret-knock-pattern-door-lock
* [3]: Instructables. (2017, October 21). Knock Box (it Opens When You Knock on It!). Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Knock-box-it-opens-when-you-knock-on-it/


## 9	Appendices

