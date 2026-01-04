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

### 1.1	Teaser <!-- I have changed background to teaser -->
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

## 4	Methodology

### 4.1 Testing
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
### 4.2	Hardware Design
### 4.2.1 Schematic Design


#### 4.2.2 Limitations of ESP32-C3
One possible limitation of the ESP32-C3 for our project is the write cycles of the NVS memory, which will be actively used to store the knock pattern.

Its internal flash has a typical limit of 100k write cycles per sector 
- i.e. each **sector** (usually 4 KB) can be **erased and rewritten ~100,000 times** before the flash may start to fail
- If you only **write the knock pattern when it changes**, even **once per day**, you’d reach 100,000 writes after ~274 years.
- Hence to be on the safe side, we must make sure to only write to flash when the pattern is changed by the user.
- If for some reason one has to flash a lot, use FRAM (very expensive), however that will not be needed here.

### 4.3 Software Implementation
The software was made using the Arduino IDE. The code is written in C++. A modular approach was taken to make it easier to debug and maintain.

#### 4.3.1 Knock Detection
When the system is awake, it continously reads the accelerometer data (main loop), and calculates the dynamic acceleration by removing the gravity component. This is done with a short function:
```cpp
inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(y * y + 2 * z * z) * 0.0039;
}
```
The values from the accelerometer are in raw format, and hence converted to g for easier understanding and comparison. For knocks, from our prototyping phase we had found out
the knocks were mainly in the Y and Z axis (z-axis more prominantly), hence the X axis is ignored to reduce noise. The factor 0.0039 is used to convert the raw values to g, as per the datasheet of ADXL345 [6].

To actually process and record those knocks for checking, the following algorithm was implemented:
```cpp
// Function to deal with response if system locked
void handleLockedState(float aDynamic, unsigned long now) {
  if (aDynamic > KNOCK_THRESHOLD && (now - lastKnockTime) > DEBOUNCE_TIME) {
    lastKnockTime = now;
    lastActivityTime = now; 
    flashGreenTick();
    led_ryg(0, 1, 0);
    knockTimes[knockCount] = now;
    knockCount++;
    if(SERIAL_MONITOR_EN) Serial.printf("Locked Knock #%d\n", knockCount);
  } else {
    if(digitalRead(YLED) == LOW) digitalWrite(YLED, HIGH);
  }
  if (knockCount > 0 && (now - lastKnockTime > PATTERN_TIMEOUT)) {
    checkPattern();
    knockCount = 0; 
    led_ryg(0, 1, 0); 
  }
  if (knockCount == 0 && (now - lastActivityTime > SLEEP_TIMEOUT)) {
    goToSleep();
  }
}
```
Here we checked if the knock matched the threshold (again configurable), and alerted the user if it was recorded. If no knocks were
detected for a certain time (configurable), the recorded knocks were checked against the target pattern. 
If no knocks are detected for a longer time (configurable), the system goes to deep sleep to save power.

#### 4.3.2 Knock Pattern Checking Algorithm
For the core logic for knock pattern checking, the following algorithm was implemented:
```cpp
int maxStart = intervalCount - patternLength + ALLOWED_MISTAKES;
bool match = false;

for (int offset = 0; offset <= maxStart; offset++) {
    bool ok = true;

    for (int j = 0; j < patternLength; j++) {
      int idx = offset + j;
      if (idx < 0 || idx >= intervalCount) { ok = false; break; }

      long diff = labs((long)intervals[idx] - (long)targetPattern[j]);
      if (diff > KNOCK_TOL) { ok = false; break; }
    }

    if (ok) { match = true; break; }
  }
```
An offset was provided, in case a few incorrect knocks were made at the start or at the end. The number of allowed mistakes can be set in the config.h file.
The algorithm worked by sliding a window, checking if the target pattern matched the recorded intervals, even if a few mistakes were made before
or after the pattern. This allows for more a more robust yet lenient detection, as if someone started wrong, or a double knock at the end on accident. When more
security is of concern, the allowed mistakes can be set to zero.

Naturally the intervals will never exactly match the target pattern, so a tolerance is set, which can also be configured in the config.h file. 

### 4.3.3 Saving a New Pattern
A similar function to locked state handler was implemented for the unlocked state as well as for recording the knocks to save a pattern. Once the pattern was recorded this function was called
to save the pattern to the NVS memory of the ESP32-C3 and also playback the pattern to the user for a confirmation. To do so the following function was implemented:
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
### 4.3.4 Power Management
To save power, the ESP32-C3 is put into deep sleep mode when no knocks are detected for a certain time. The following function is used to put the system to sleep:
```cpp
void goToSleep() {
  led_ryg(0,0,0);
  
  // Check Battery before sleeping
  float batV = getBatteryVoltage();
  bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

  // Prepare ADXL Wakeup
  adxl.doubleTapINT(1);
  adxl.getInterruptSource();
  esp_deep_sleep_enable_gpio_wakeup(1ULL << WAKE_INT, ESP_GPIO_WAKEUP_GPIO_HIGH);

  if (lowBattery) {
    if(SERIAL_MONITOR_EN) Serial.printf("💤 Low Battery (%.2fV). Blinking and sleeping 4s...\n", batV);
    
    // Blink Red indicating "I'm sleeping but dying"
    led_ryg(1,0,0);
    delay(100);
    led_ryg(0,0,0);
    
    // Enable Timer Wakeup
    esp_sleep_enable_timer_wakeup(FLASHING_TIME * 1000000ULL); 
  } else {
    if(SERIAL_MONITOR_EN) Serial.println("💤 Good Battery. Deep Sleep (Waiting for Knock)...");
    // No timer wakeup, sleep indefinitely until knock
  }
  esp_deep_sleep_start();
}
```
The primary task here was to configure how to wake the system back up. Here we used the double tap interrupt of the ADXL345 to wake the system back up on a knock. As the ADXL345 
is powered directly from the battery, it can always detect knocks even when the ESP32-C3 is in deep sleep, the ADXL345 also has an inbuilt interrupt for double tap detection, which is 
one of the main reasons to go for this specific sensor package. If the system is low on battery, a timer wakeup is also configured to wake the system up every 4 seconds to blink the 
red LED indicating low battery.

As there are two methods of waking up, each with different operations to be performed on wakeup, the wakeup reason is checked and system reacts accordingly using the function below:
```cpp
void handleWakeup(){
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_GPIO) {
    // Woke up by ADXL Tap
    digitalWrite(YLED, HIGH); 
  } else if (cause == ESP_SLEEP_WAKEUP_TIMER) {
    // Woke up due to low battery
    if(SERIAL_MONITOR_EN) Serial.println("♻ Woke up from Low Bat Timer");
    goToSleep();
  }
}
```

This function must be called near the start of the setup() function (right after Serial setup) to save as much power as possible.

### 4.3.5 Helper Functions
All of the functions above user some helper function to make the code more modular and easier to read. Some of these functions include:
- led_ryg(int r, int y, int g): To set the red, yellow and green LED states
- flashGreenTick(): To flash the green LED quickly to indicate a knock was recorded
- goodBeep() and badBeep(): To play a good or bad beep sound using the buzzer
- unlockBox() and lockBox(): To unlock and lock the servo motor


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
* [4]: Burgognoni, E. (2025, August 28). Comparing MEMS and IEPE accelerometers for structural vibration behavior testing. Data Acquisition | Test and Measurement Solutions. Retrieved October 30, 2025, from https://dewesoft.com/blog/comparing-mems-and-iepe-accelerometers
* [5]: Miranda, V. R., & Landre, J., Jr. (2018). Comparison of the signal characteristics measured by a MEMS and a Piezoelectric accelerometers. International Journal of Advanced Engineering Research and Science, 5(11), 148–152. https://doi.org/10.22161/ijaers.5.11.21
* [6]: Analog Devices. (n.d.). ADXL345 datasheet. Analog Devices. Retrieved November 20, 2025, from https://www.analog.com/en/products/adxl345.html
* [7]: Espressif Systems. (2021). ESP32-C3 Series datasheet. In Espressif. https://www.espressif.com/documentation/esp32-c3_datasheet_en.pdf

## 9	Appendices

