>>>
**Project-Template**

Please use this template for your practical electronics project. (feel free to delete this section) 

You can find a quick guide in the following [cheat sheet](https://www.markdownguide.org/cheat-sheet/) or specific [gitlab style](https://docs.gitlab.com/ee/user/markdown.html) here

>>>

**Make sure your submit your deliverables (project description, schematic, pcb design and report on time - timestamp is used as reference)


----

# Knock Lock

by: [Justin Chin Cheong](https://jcchincheong-bb.github.io/) (34140) and [Abhinav Kothari](https://www.linkedin.com/in/abhinav-kothari-2ak/) (33349)


**Faculty of Technology and Bionics**

***Rhine-Waal University of Applied Sciences***

Date: 10 January 2022

----

## Abstract

Short summary of the project and the work conducted

## Table of Contents

[[_TOC_]]

## 1 Introduction 
We have all built secret passwords, sometimes words, sometimes numbers, sometimes just a pattern of knocking, sometimes it was to get into a box castle, sometime a room. 

Suprisingly, the password nowadays are boring, just words, numbers, NFCs sometimes biometric. However what happened to the secret knock? In this project we want to create a 
more fun way to unlock a door, while also keeping it safe using a secret knock pattern, with millions of potential permutations. This unlocking mechanism can be used for 
getting through a door, open a drawer, or opening a safe box, the possibilities are endless. 

The KnockLock Project will demonstrate the idea by implementation into a lock box.

### 1.1	Background <!-- Teaser sounds extremely unprofessional -->
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
    - Project Report: 2026-01-18
    - Project Presentation and Demo: 2026-01-21

## 1.3 Project Team
The project team consists of two Mechatronics Engineering Students whose responsibilities in the project were divided
as follows:
- Justin Julius Chin Cheong (34140): 
  - Component selection
  - Design of programming interface and motor control circuits
  - Design of final PCB layout
  - Design of preliminary prototype housing
- Abhinav Kothari (33349):
  - Design of power regulation, sensor system and human machine interface circuits
  - Development of complete program software
  - Design of preliminary PCB layout
  - Design of final prototype housing
- Both: 
  - Soldering and assembly
  - Testing of components and system integration
  - Testing of functionality

## 2	Literature review
Many projects have been made to ease unlocking a device, for example using RFID, NFC, Bluetooth, WiFi, fingerprint sensors etc. Some have also implemented knock detection, 
These projects have used various techniques to create a similar final product. These will be discussed here

### 2.1	Related Work
Orignally in the brainstorming phase, many sensors were thrown into the mix for succesfully detection, this included a digital vibrations sensor, a piezo sensor and a accelerometer amoungst others, but these were the primary contendors. Vibration sensors were avoided, as they will not be as senstive as an piezo or accelerometer, also being digital reduces the customisability. Piezo and accelerometers were both looked into in more detail.

Piezo sensors have been the primary choice in most project [1,2,3]. One uses a Arduino Duemilanove with a piezo sensor to detect knocks and a gear reduction motor acts as the actuator to open the lock. Other projects use a similar approach but with an Arduino nano, but uses a solenoid or a servo motor as the actuator.

Even after extensive research, we could not find any project that used an an accelerometer to detect knocks, only piezos, which increased our curiosity.

The reason for using piezo is most likely because of them being accordable and easy to use while maintaining a good SNR (Signal To Noise Ratio). However, we believed that MEMs accelerometers can be used as well, and even could prove to be better for this specific application.
The blog post [4] shows MEMS accelerometers have a better frequency response and are more sensitive than piezo sensors at lower frequencies, due to the high passing filtering used. While this blog post is about IEPE the same principle applies to piezo sensors as well. Even in industrial applications [5], when MEMs were compared to traditional piezo sensors, the max deviation was only found to be 6.6%  at lower frequencies of upto 2,500 Hz, which is perfect for our application of knock detection. While piezo accelerations sensors, usually have a superior SNR to MEMs, with recent development the difference is slowly diminishing as shown by this paper. 

The major reason for why we first though of using IMUs, is guidance from our professor, and then us thinking back to our phones, which use accelerometers to succesfully detect back taps for performing some
actions, precisely what we want to do here. A summary of all the differences between piezo and MEMs accelerometers is shown in the table below:
| Feature               | Piezo Accelerometer                | MEMS Accelerometer                 |
|----------------------|-----------------------------------|-----------------------------------|
| Sensitivity          | High sensitivity, especially at higher frequencies | Good sensitivity, especially at lower frequencies |
| Frequency Response   | Wide frequency response, typically from a few Hz to several kHz | Good frequency response, typically from DC to several kHz |
| Size and Weight      | Generally larger and heavier due to the need for a seismic mass and housing | Compact and lightweight due to microfabrication techniques |
| Power Consumption    | Typically higher power consumption due to signal conditioning requirements | Low power consumption, suitable for battery-powered applications |
| Cost                 | Generally more expensive due to complex manufacturing processes | Cost-effective due to mass production capabilities |

Looking at the project made before in more detail [1], an issue was pointed out, that there can be a lot of false positives. However, as accelerometers communicate over I2C (Used here) or SPI,
we get digital values of analog readings directly, which can be processed better than the analog voltage from piezo sensors. This allows us with more flexibility in filtering and processing the signal to reduce false positives.

Hence to actually find the better alternative for our project we did some testing in Section 4.1.

While an ESP32 has a higher power consumption in normal mode, in deep it falls much lower (around 5 uA) [7]. Which makes a viable option for battery powered applications with the controller mainly in deepsleep. It also has more than enough processing power to handle the knock detection algorithm.

## 3	Theory
If necessary please present theory in this section.

This math is inline $`a^2+b^2=c^2`$.
### 3.1 Accelerometers
### 3.2 I2C
### 3.3 High-Side Driver

## 4	Design and Methodology

### 4.1 Design Approach
V model

### 4.2 System Architecture
fsd 

program flowchart 

### 4.3 Bill of Materials

### 4.4 Preliminary Testing
#### 4.4.1 Sensor Selection <!-- Kinda want to talk to Stamm abt whether to put this in method or results, for now we do method -->
To test the accurcacy in knock detection with both sensors, we created a setup as shown below:
![alt text](resources/testingSetupPlastic.png "Testing setup 1 - Plastic")
(C) Image shot by authors
Here both sensors were attached to a thin plastic lid, a knocks were applied to the lid. The readings from both sensors were recorded and compared.

Another setup was created to simulate a more rigid and thicker surface, here we used a wooden chair we found. This surface is more likely to be similar to the actual box, or door, which are the 
intended use cases. The setup is shown below:
![alt text](resources/testingSetupWood.png "Testing setup 2 - Wood")
(C) Image shot by authors
Here both sensors, one by one were attached to the wooden surface, and the knocks were applied from the other side of the chair. The readings were recorded and compared.

The results from both tests are summarized below:
- The IMU is much more reliable and easier to detect, the communication works quite seamless with i2c. Each knock produces spike for all 3 axis, some more prominantly than others.
- Piezo was able to detect knocks against it through a plastic case quite reliably, occasional misses when knocked too quickly
- The IMU is able to detect even through a wooden chair, while piezo couldn’t

Even after trying to make the piezo a bit more sensitive using 3.3V supply instead of 5V, it still couldn’t match the performance of the IMU. Which was shocking considering other projects.
However we still decided to go with the IMU for knock detection.

The accelerometer used was a MMA8452Q by Sparksfun Electronics, however the final design uses an ADXL345, as it was cheaper and bigger in package size making it possible to solder using
the tools available to us. However the ADXL345 is 13-bit instead of 12-bit, hence should perform even better.

The accelerometer gives 3-axis readings and how the 3-axis readings look like when 3 knocks are applied is shown below:
![alt text](resources/knockDetectionIMU.png "Knock Detection IMU")
(C) Screeenshot by authors

The y-axis is the magnitude in g, while the x-axis is time in milliseconds. The blue, yellow and green lines are the x, y and z axis respectively.

#### 4.4.2 System Prototype
An accelerometer module was used to test if the system was feasible and to start software development

### 4.5	Schematic Design
#### 4.5.1 Full Schematic Design
#### 4.5.2 Controller System
Just talk about the controller used and some comments on passives
#### 4.5.3 Programming Interface
Mention the use of the buttons and why the design has no UART chip and just pin headers

#### 4.5.4 Sensor System
How the ADXL connects, which pin modes are set and how i2c is implemented


#### 4.5.5 Human Machine Interface
LEDs and buzzer to communicate status 

#### 4.5.6 Motor Driver
high side driver with transistors 

#### 4.5.7 Power Regulation System and Power Supply
Describe the not only the power regulator but also the reverse polarity protection and such

#### 4.5.8 Limitations of ESP32-C3  <!-- Seems weird to be here, maybe better in discussion -->
One possible limitation of the ESP32-C3 for our project is the write cycles of the NVS memory, which will be actively used to store the knock pattern.

Its internal flash has a typical limit of 100k write cycles per sector 
- i.e. each **sector** (usually 4 KB) can be **erased and rewritten ~100,000 times** before the flash may start to fail
- If you only **write the knock pattern when it changes**, even **once per day**, you’d reach 100,000 writes after ~274 years.
- Hence to be on the safe side, we must make sure to only write to flash when the pattern is changed by the user.
- If for some reason one has to flash a lot, use FRAM (very expensive), however that will not be needed here.

### 4.6 PCB Design


### 4.7 Software Design
The software was made using the Arduino IDE. The code is written in C++. A modular approach was taken to make it easier to debug and maintain. All the main configurations are in the config.h file, while the main starting logic is in the KnockLock.ino file. All other functions are in seperate files to make it easier to read. The libraries used are:
- ESP32 NVS Library: For using the NVS memory of ESP32-C3 - in-built with Arduino IDE
- SparkFun ADXL345 Library (v1.0.0): For interfacing with the ADXL345 accelerometer
- Wire Library: For i2c communication with the ADXL345 - in-built with Arduino IDE
- ESP32Servo (v3.0.9): For controlling the servo motor

The following flowchart shows the overall logic of the program:
![alt text](resources/FlowchartOfMainSystem.png "Flowchart")
(C) Image created by authors using Mermaid Live Editor

The flowchart shows, how the system must work, spikes denote knocks detected. The system starts in locked state, where it continously listens for knocks, unless it sleeps, and records them. Interrupts will be used to wake the system up from sleep for again starting to read knocks. Once the knocks are recorded, they are checked against the target pattern, if they match, the system unlocks, else it stays locked. If the box is unlocked and the programming button is pressed, the system enters programming mode, where it records knocks to save a new pattern. Once the pattern is recorded, it is saved to NVS memory and the system goes back to idle mode. Knocking twice locks the box again. LEDs and Buzzer are used to give feedback to the user.

The actual code implementation of the main parts are explained below.
#### 4.7.1 System Initialization
Upon startup, the system must perform many intializations to get everything working correctly. The order is also quite important to save power and to ensure best reliability. 

First the system must check the reason for wakeup, so that it can perform the correct operations accordinly. This done as shown in the snippet below:
```cpp
// Enable Serial Monitor if required
if(SERIAL_MONITOR_EN) {
    Serial.begin(115200);
    Serial.println("Serial monitor enabled!");
}

setupHardware(); // Setup hardware

// WAKE UP
handleWakeup();

ADXLsetup();                  // Setup ADXL
digitalWrite(SERVO_EN, HIGH); // Turn servo On
```
Here the Serial monitor is enabled first, if required, so that debug messages at all stages can be printed. Then it is necessary to setup the hardware, which includes setting pin modes. This is necessary to do before checking wakeup reason, as different pins may be used for different wakeup reasons. Then the wakeup reason is handled using handleWakeup() function, which will be explained in Section 4.3.5. Finally the ADXL345 is setup using ADXLsetup() function, and the servo power is turned on. The ADXL can be setup after wakeup reason check, as it keeps its settings even in while the controller is in deep sleep.

Now finally the stored knock pattern must be loaded from NVS memory and timers reset to get system ready for reading. This is done using the following code:
```cpp
// Load pattern
patternLength = loadPatternFromNVS(targetPattern);
  
// Reset timers
unsigned long startT = millis();
lastKnockTime = startT;
lastActivityTime = startT;

if(SERIAL_MONITOR_EN) Serial.println("System Ready.");
led_ryg(0, 1, 0);
```

Both the code snippets above are part of the setup() function in KnockLock.ino file.

For setting up the ADXL, we must set its settings using its library. The library used is SparkFun_ADXL345 (Version v1.0.0). The following function allows us to set its settings as well as setup interrupts:
```cpp
//Function to setup the ADXL sensor with interrupts and sensitivity
void ADXLsetup() {
  Wire.begin(SDA_PIN, SCL_PIN);                                   // Start communication via i2c
  adxl.powerOn();                                                 // Power the ADXL345 on
  adxl.setRangeSetting(SENSITIVITY);                              // Set up the sensitivity, from config.h
  adxl.setTapDetectionOnXYZ(ADXL_EN_X, ADXL_EN_Y, ADXL_EN_Z);     // Enable individual acceleration sensor
  adxl.setTapThreshold(TAP_THRESHOLD);                            // Set minimum threshold for detecting wakeup
  adxl.setTapDuration(TAP_DURATION);                              // Minimum duration for detecting a wake up
  adxl.setDoubleTapLatency(DOUBLE_TAP_LATENCY);                   // Minimum duration between the second tap and first tap
  adxl.setDoubleTapWindow(DOUBLE_TAP_WINDOW);                     // Maximum duration to wait for the second tap

  // Disable all interrupts, until required
  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);
  adxl.FreeFallINT(0);
  adxl.ActivityINT(0);
  adxl.InactivityINT(0);
  adxl.getInterruptSource();
}
```
Disabling all interrupts ensure that no false wakeups occur. The settings for sensitivity and tap detection are taken from config.h file, allowing easy tuning. Wire library allows i2c communication with the ADXL345.

#### 4.7.2 Knock Detection
When the system is awake, it continously reads the accelerometer data (main loop), and calculates the dynamic acceleration by removing the gravity component. This is done with a short function:
```cpp
inline float accelMagnitudeG(int x, int y, int z) {
  return abs(z); // Calculate magnitude using relevant axis, for g, multiply this by 0.0039 (from datasheet) 
}
```
The values from the accelerometer are in raw format, if the g is required, it can be multiplied by 0.0039 (value from datasheet of ADXL[6]). In this use case, only the change in magnitude of the reading is of interest. Keeping it a raw value also allows a more finer tuning of the thereshold. Here it was necessary to take readings in the specific scenario for getting the right threshold. As the orientation of using the box changes the value we need to measure. 
By regular testing we found a good threshold to be around 150-200 (raw value) for knock detection. These readings were found using a seperate prototyping script, which just read and printed the raw values from the accelerometer continously on to the Serial Monitor. It was necessary to have continous values to realize, what are the typical readings and when actual knocks occur.
From testing we found the main predominant axis for knocking detection to be the Z axis only. Hence the X and Y axis are ignored to reduce noise. However if the orientation of the box is changed, it might be necessary to change the axis used for detection. Using only Z axis also made it so that, opening or closing the box (which would cause movement in X and Y axis) does not trigger false positives.

To actually process and record those knocks for checking, the following algorithm was implemented:
```cpp
// Function to deal with response if system locked
void handleLockedState(float aDynamic, unsigned long now) {
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) { // If knock is detected start recording its timing
    lastKnockTime = now;
    lastActivityTime = now; 
    flashGreenTick(); // Alert user a knock was detected
    led_ryg(0, 1, 0); // Show it is still recording
    knockTimes[knockCount] = now;
    knockCount++; // Count number of knocks
    if(SERIAL_MONITOR_EN) Serial.printf("Locked Knock #%d\n", knockCount);
  } else {
    if(digitalRead(YLED) == LOW) digitalWrite(YLED, HIGH);
  }
  if (knockCount > 0 && (now - lastKnockTime > PATTERN_TIMEOUT)) { // If a long  break with  knocks, start checking the pattern
    checkPattern(); // Check the pattern, if it is correct it goes to unlocked state
    knockCount = 0; // If checked reset for next iteration
    led_ryg(0, 1, 0); // Show it is recording
  }
  if (knockCount == 0 && (now - lastActivityTime > SLEEP_TIMEOUT)) { // If too long a break with no knocks, go to sleep
    goToSleep();
  }
}
```
Here we checked if the knock matched the threshold (again configurable), and alerted the user if it was recorded. If no knocks were
detected for a certain time (configurable), it means the user has finished knocking, and the pattern can be checked. If no knocks were detected for a longer time (configurable), the system goes to sleep to save power. 


#### 4.7.3 Knock Pattern Checking Algorithm
For checking the knock pattern, a pessimistic approach was taken. Here the pattern was assumed to be wrong , unless proven otherwise. This allows for a safe approach, so that even if the system faces issues, the box is less likely to open. However before checking the pattern, to minimize CPU cycles Some basic checks were done. This helped save processing time, especially if the pattern is completely wrong. The following checks were implemented:
```cpp
// Check if any pattern is even saved, if not return
if (patternLength <= 0) {
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern.");
    return;
}

if (knockCount < MIN_KNOCKS)
    return;
```
These checks were implemented at the start of the function and made sure that if no pattern is saved, or if too few knocks were recorded, the function returns immediately.

If these checks were passed, we calculate the intervals using the knock timings recorded using the following code:
```cpp
// Calculate intervals using knock timings
int intervalCount = knockCount - 1;

for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
}
```
Finally the algorithm can start checking the pattern. The following snippet shows how some incorrect conditions are checked first to save processing time:
```cpp
// Actually checking for mistakes
bool ok = false; // Keep track of a mistake - true means pattern is correct, false means pattern was incorrect
  
// Check for pattern size before actual checking, to be more efficient 
int patternDiff = intervalCount - patternLength; // See difference in the knocks recorded vs knocks to be done
if (patternDiff < 0){
    // Too few knocks 
    ok = false;
    if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Too few knocks");
}
else if (patternDiff > ALLOWED_MISTAKES) {
    // Too many mistakes
    ok = false;
    if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Too many mistakes");
}
```
This checks if the number of knocks recorded is less than the pattern length, or if there are too many extra knocks (more than allowed mistakes). If any of these conditions are met, the pattern is marked as incorrect and the function returns.

If these checks are passed, the actual pattern checking algorithm is implemented as follows:
```cpp
else {
    for(int mistakeCount = 0; mistakeCount <= patternDiff; mistakeCount++){ 
        // Now if there is a mistake (or multiple), slide window to see if the mistake is at the start only, and full correct pattern is to follow. Run it only till the number of mistakes he has made, which is patternDiff
        bool currentWindowCheck = true; // See if pattern play for a specific window
        for(int k = 0; k < patternLength; k++){
            long diff = labs((long)intervals[k+mistakeCount] - (long)targetPattern[k]);

            if(diff > KNOCK_TOL){ // Is difference not tolerable, according to config.h
              currentWindowCheck = false;
              break; // If a mistake then no need to check rest, go to check if mistake is ignored
            }
        }
        if(currentWindowCheck) { // If pattern is correct after some mistakes (less than allowed mistakes)
            ok = true;
            break;
        }
        else{
            if(mistakeCount == patternDiff) { // Check if it is the last tolerable mistake
                if(SERIAL_MONITOR_EN) Serial.println("Incorrect pattern: Wrong difference");
                break;
            }
        }
    }
}
```
Here the algorithm slides a window over the recorded intervals, checking if the target pattern matches the recorded intervals, even if a few mistakes were made before
or after the pattern. This allows for more a more robust yet lenient detection, as if someone started wrong, or a double knock at the end on accident. When more
security is of concern, the allowed mistakes can be set to zero using config.h. 

Naturally the intervals will never exactly match the target pattern, so a tolerance is set, which can also be configured in the config.h file. 

Then according to the result of the checking stored in the variable ok, the system reacts accordingly:
```cpp
if (ok) { // If pattern correct
    if(SERIAL_MONITOR_EN) Serial.println("✅ Correct pattern!");
    goodBeep();
    unlockBox();
} else { // If pattern not correct
    if(SERIAL_MONITOR_EN) Serial.println("❌ Wrong pattern.");
    badBeep();
}
```

All these code snippers in this section are part of the function checkingPattern() in file patternRecognitionAndRecording.cpp.

#### 4.7.4 Saving a New Pattern
A similar function to locked state handler was implemented for the unlocked state as well as for recording the knocks to save a pattern. However this can only be called by cliking the programming button (Pin 7) when the box is unlocked. Once the pattern was recorded a different function was called to save the pattern to the NVS memory of the ESP32-C3 and also playback the pattern to the user for a confirmation. To do so the following function was implemented:
```cpp
void finishRecording() {
  if (knockCount < MIN_KNOCKS) {
    if(SERIAL_MONITOR_EN) Serial.println("❌ Recording Failed: Too few knocks.");
    badBeep();
  } else {
    for (int j = 0; j < knockCount - 1; j++) {
      intervals[j] = knockTimes[j + 1] - knockTimes[j];
    }
    patternLength = knockCount - 1;
    savePatternToNVS(intervals, patternLength);
    successSave();
    playbackPattern();
  }
  currentMode = MODE_IDLE;
  knockCount = 0;
  led_ryg(0, 0, 0); 
}
```
Here first it is checked if enough knocks were recorded, if not, the user is alerted. If enough knocks were recorded, the intervals are calculated and saved to NVS memory using the function savePatternToNVS(). Then a success indication is given to the user using successSave() function, followed by playback of the pattern using playbackPattern() function. To allow user to unlock the box with the new pattern, without having to reset the system, the stored values are loaded again. They are not loaded each time in checking to save processing time. Finally the system goes back to idle mode, and the knock counts are reset. The LEDs are also turned off, but when it goes back to handle locked or unlocked state, they will be turned on again accordingly.

#### 4.7.5 Power Management
To save power, the ESP32-C3 is kept in deep sleep mode most of the time, only waking up when knocks are detected. However to put the system to sleep appropriate steps must be taken in the correct order. 

Before going to sleep, the system should first check the battery voltage, to see if it is low or not. If it is low, the system must wake up every few seconds to blink the red LED indicating low battery to alert the user to changee it. If the battery is good, the system can sleep indefinitely until a knock is detected. There may be concern, that what if the system does not have low battery when going to sleep, but the battery drains while sleeping. However this is not a really big concern, as the drain will be very slow. Waking it up to check battery status regularly will waste more power. This decision of checking battery only before sleep was taken also taking into account the system has been designed with two sets of power supply, battery and USB. If the battery drains, the user can always plug in the USB power to power the system.

Checking the battery voltage is done using this simple code snippet:
```cpp
led_ryg(0,0,0); // Turn off all LEDs before sleeping
  
// Check Battery before sleeping
float batV = getBatteryVoltage();
bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);
```
Here first all the LEDs are turned off to save power. Then the battery voltage is read using getBatteryVoltage() function, and compared against the threshold defined in config.h to see if it is low or not.
Then the system can be put to sleep using the following code:
```cpp
digitalWrite(SERVO_EN, LOW); // Turn servo off the save battery

// Prepare ADXL Wakeup
adxl.doubleTapINT(1); // Interrupt for double tap on, which wakes up the MCU up
adxl.getInterruptSource(); // Clear the interrupt flags
esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH); // Set the GPU pin connected to interrupt as wake up

if (lowBattery) { // If battery is to low, while sleeping set a timer to wake up and indicate battery status. When battery not low no need to set timer interrupt
    if(SERIAL_MONITOR_EN) Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    led_ryg(1,0,0);
    delay(100);
    led_ryg(0,0,0);
    
    // Enable Timer Wakeup
    esp_sleep_enable_timer_wakeup(FLASHING_TIME * 1000000ULL); 
} else {
    if(SERIAL_MONITOR_EN) Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleeps indefinitely until knock
}
esp_deep_sleep_start();
```

Here first the servo is turned off, using power gating (designed in schematic) to save power. Then the ADXL345 is configured to generate an interrupt on double tap detection using its inbuilt interrupt, which will be used to wake the system up on double knock. The GPIO pin of the ESP32-C3 is connected to the interrupt pin of ADXL345. As the ADXL345 is powered directly from power supply and not the controller, this approach can be used, as interrupts will trigger in ADXL345 even if controller is off. When the specific GPIO Pin on the controller reads a high, it will turn the system back on. The interrupt flags are also cleared to avoid false wakeups.
If the system is low on battery, a timer wakeup is also configured to wake the system up every few seconds (configured in config.h) to blink the red LED indicating low battery, default is 60s.

As there are two methods of waking up, each with different operations to be performed on wakeup, the wakeup reason is checked and system reacts accordingly using the function below:
```cpp
// Function to realize reason for wake up, and do tasks accordingly
void handleWakeup(){
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap, that means some one wants to get in the box probably
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up due to low battery, need to indicate using battery
    if(SERIAL_MONITOR_EN) Serial.println("♻ Woke up from Low Bat Timer");
    goToSleep(); // This has the code to check battery status again and indicate led signal accordingly
  }
}
```
This function must be called near the start of the setup() function (right after Serial setup) to save as much power as possible. The reason for it being in setup() is that after deep sleep, the ESP32-C3 does a full reset, hence setup() is called again.

### 4.7.6 NVS Memory Handling
To save the knock pattern even after power off, the NVS memory of ESP32-C3 is used. This is a non-volatile memory built into the ESP32-C3, which can be used to store small amounts of data.
To save the pattern length and intervals, the following function was implemented:
```cpp
// Function to load saved pattern
void savePatternToNVS(unsigned long intervals[], int count) {
  prefs.begin("knocks", false);  // Start communication, Read and Write mode

  prefs.putInt("count", count); // Store count of intervals

  // Store each interval
  for (int i = 0; i < count; i++) {
    char key[8];
    sprintf(key, "i%d", i);     // keys: i0, i1, i2...
    prefs.putULong(key, intervals[i]);
  }

  prefs.end(); // End communication reading storage
  if(SERIAL_MONITOR_EN) Serial.println("Pattern saved to NVS!");
}
```
As NVS memory works with key-value pairs, first the count of intervals is stored using key "count", then each interval is stored using individual keys "i0", "i1", "i2" ... for each interval. Finally the communication is ended to save power.
To load the pattern back, a similar approach is taken, reading the count first, then reading each interval using the same keys. Just instead of put functions, get functions are used. The function can be seen in the file usingNVS.cpp.

#### 4.7.7 Helper Functions
All of the functions above user some helper function to make the code more modular and easier to read. Some of these functions include:
- led_ryg(int r, int y, int g): To set the red, yellow and green LED states
- flashGreenTick(): To flash the green LED quickly to indicate a knock was recorded
- goodBeep() and badBeep(): To play a good or bad beep sound using the buzzer
- unlockBox() and lockBox(): To unlock and lock the servo motor


## 5	Results
Here you should present your results.

This is an example how to include image:
![alt text](resources/Open_Source_Hardware_(OSHW)_Logo_on_blank_PCB.jpg "Example Image")
(C) Altzone, CC BY-SA 3.0 <https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia Commons

Example how to draw a table:

| Left Aligned | Centered | Right Aligned |
| :---         | :---:    | ---:          |
| Cell 1       | Cell 2   | Cell 3        |
| Cell 4       | Cell 5   | Cell 6        |
| OpAmp 741    | 2        | 1.00          |

### 4.8 Housing Design


### 4.9 Verification Methods
#### 4.9.1 Component Testing
#### 4.9.2 System Integration Testing
#### 4.9.3 Power Consumption
power consumption 

## 6	Results
### 6.1 Assembly
### 6.2 Functional PCB
### 6.3 PCB with Housing
Here you should present your results.

This is an example how to include image:
![alt text](resources/Open_Source_Hardware_(OSHW)_Logo_on_blank_PCB.jpg "Example Image")
(C) Altzone, CC BY-SA 3.0 <https://creativecommons.org/licenses/by-sa/3.0>, via Wikimedia Commons

### 6.4 Issues
primarily coding issues after lots of testing

also lots of issues with housing

## 7	Discussion
Here you should discuss your results
### 7.1 Product Evaluation
A comparison of the results we had with existing products or what we saw in literature

### 7.2 Product Limitations
What are the main limitations we realised after extensive testing

like the .... I cant think of any rn

## 8	Conclusion
You might want to discuss possible future work here
### 8.1 Future Improvements
Doing this project, opened more aspects which can be worked on in future when reiterating the project. These include:
- Working in all orientations: Automatically adjusting the axis to read using orientation of box.
- Redundant sensors: Use Piezo with ADXL to more effectively detect a knock

## 8	References

* [1]: Instructables. (2022, May 8). Secret knock detecting door lock. Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Secret-Knock-Detecting-Door-Lock/ 
* [2]: Dodhia, V. (2021, June 20). Arduino secret knock pattern door lock. Viral Science. Retrieved November 20, 2025, from https://www.viralsciencecreativity.com/post/arduino-secret-knock-pattern-door-lock
* [3]: Instructables. (2017, October 21). Knock Box (it Opens When You Knock on It!). Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Knock-box-it-opens-when-you-knock-on-it/
* [4]: Burgognoni, E. (2025, August 28). Comparing MEMS and IEPE accelerometers for structural vibration behavior testing. Data Acquisition | Test and Measurement Solutions. Retrieved October 30, 2025, from https://dewesoft.com/blog/comparing-mems-and-iepe-accelerometers
* [5]: Miranda, V. R., & Landre, J., Jr. (2018). Comparison of the signal characteristics measured by a MEMS and a Piezoelectric accelerometers. International Journal of Advanced Engineering Research and Science, 5(11), 148–152. https://doi.org/10.22161/ijaers.5.11.21
* [6]: Analog Devices. (n.d.). ADXL345 datasheet. Analog Devices. Retrieved November 20, 2025, from https://www.analog.com/en/products/adxl345.html
* [7]: Espressif Systems. (2021). ESP32-C3 Series datasheet. In Espressif. https://www.espressif.com/documentation/esp32-c3_datasheet_en.pdf

## 9	Appendices

