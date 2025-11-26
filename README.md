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

### 1.1	Background
Necessary background to your work….

Chapter 1 presents….. 

Chapter 2 presents…..

## 2	Literature review
Many projects have been made to ease unlocking a device, for example using RFID, NFC, Bluetooth, WiFi, fingerprint sensors etc. Some have also implemented knock detection, 
These projects have used various techniques to detect knocks, such as using piezo sensors, vibration sensors etc. These will be discussed here

### 2.1	Related Work
Piezo sensors have been the primary choice in most project, such as [1]. Here a Arduino Duemilanove has been used with a piezo sensor to detect knocks and a gear reduction motor 
acts as the actuator to open the lock. Another project [2] uses a similar approach, but uses a solenoid as the actuator and an Arduino Nano instead. [3] also again uses a piezo sensor 
but a servo motor as an actuator.

All these projects have used piezo sensors to detect knocks, which is a good choice as they are cheap and easy to use. However, they are also prone to noise and false positives.

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

