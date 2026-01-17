<!----------------------------------------------------------------
<div id="logo" align="center">
<figure>
  <img src="/resources/images/Logo.png" alt="Logo" width="400">
  <figcaption align="center"><b>Figure 1:</b> Knock Lock Logo</figcaption>
</figure>
</div>
----------------------------------------------------->
<!--
STOP CHANGING THE STRUCTURE! IT'S GOOD NOW!!!
-->
# Knock Lock
<div id="logo" align="center">
<figure>
  <img src="/resources/Logo/Logo.png" alt="Logo" width="400">
</figure>
</div>

by: [Abhinav Kothari](https://www.linkedin.com/in/abhinav-kothari-2ak/) (33349) and [Justin Chin Cheong](https://jcchincheong-bb.github.io/) (34140)


**Faculty of Technology and Bionics**

***Rhine-Waal University of Applied Sciences***

Date: 18 January 2022

----

## Abstract

Short summary of the project and the work conducted

## Table of Contents

[[_TOC_]]
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 1 Introduction 
We have all built secret passwords, sometimes words, sometimes numbers, sometimes just a pattern of knocking, sometimes it was to get into a box castle, sometime a room. 

Surprisingly, the password nowadays are boring, just words, numbers, NFCs sometimes biometric. However what happened to the secret knock? In this project we want to create a 
more fun way to unlock a door, while also keeping it safe using a secret knock pattern, with millions of potential permutations. This unlocking mechanism can be used for 
getting through a door, open a drawer, or opening a safe box, the possibilities are endless. 

The KnockLock Project will demonstrate the idea by implementation into a lock box.

### 1.1	Background
The primary goal of this project is to be able create a system which can detect knocks reliably with correct timings in order to identify if it is the correct pattern
or not, and react accordingly. For the detection an accelerometer will be used.

For this we will have to first understand, if this has been done before, if so how can it be improved. If not it must be compared to the existing methods. This will talked about
in the literature review in Chapter 2.

Further more we must understand how an accelerometer works, and how to interface it with a microcontroller. This will be presented in Chapter 3.

Then we shall talk about how we it will be implemented (Chapter 5: Methodology) and what results were achieved (Chapter 6: Results). Finally we will discuss the results (Chapter 7: Discussion)

<div id="preliminary-sketch" align="center">
<figure>
  <img src="/resources/images/preliminarySketch.png" alt="preliminary-sketch" width="400">
  <figcaption align="center"><b>Figure 1.1:</b> Preliminary Sketch of the Knock Lock</figcaption>
</figure>
</div>

### 1.2 Project Team
The project team consists of two Mechatronics Engineering Students whose responsibilities in the project were divided
as follows:
- Abhinav Kothari (33349):
  - Design of power regulation, sensor system and human machine interface circuits
  - Development of complete program software
  - Design of preliminary PCB layout
  - Design and refinement of final prototype housing
- Justin Julius Chin Cheong (34140): 
  - Component selection
  - Design of programming interface and lock actuator circuits
  - Design and refinement of final PCB layout
  - Design of preliminary prototype housing
- Both: 
  - Soldering and assembly
  - Testing of components and system integration
  - Testing of functionality

With regard to writing of this report, the following illustrates the contributions of each team member:
- Abhinav Kothari (33349): 
  - Chapter 2
  - Chapter 4: 4.5, 4.6, 4.8
  - Chapter 5: 5.5, 5.5
  - Chapter 6
  - Chapter 7
- Justin Julius Chin Cheong (34140): 
  - Chapter 1
  - Chapter 3
  - Chapter 4: 4.1, 4.2, 4.3, 4.4, 4.7, 4.8
  - Chapter 5: 5.1, 5.2, 5.3, 5.6
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 2	Literature review
In pursuit of unique and easy methods for users to unlock systems, many developments have been made. These methods for unlocking vary from NFCs to Biometric. Knock detection is also a method used in some projects, which allows for unlocking even without carying anything extra (Like card for NFCs). This section covers the existing projects implementing knock detection, and compares them to a new approach which is not so commonly used in these systems.

### 2.1 Related Work
Reviewing hobyist and academic projets, gives us an overview of the common techniques used to accompolish this task. Notable implemetations [1,2,3] show reliable intepretation of knocks using a piezoelectric elements. However all had some limitations shown from the demonstration. The knock detection was only on a surface parallel to the piezo element. They all had also relatively hard knocks for detection. Some projects pointed out that increasing precision also increases the number of false positives. Even after more research, no projects using accelerometers were found. From reviewing the projects further, it can also been seen that none of the systems implemented a sleep mode to save battery.

For processing most the projects implemented and Arduino Deumilanove or an Arduino Nano, and used gear reduction motors, solenoids or servo for locking/unlocking mechanism.

## 2.2 Technical Comparison of Sensors
As noted from the previous section, no accelerometers were used in the project, which particularly interesting considering, they are commonly used in high-end consumer electronics such as smartphones for detecting back taps, which work reliably. Hence this section compares the three sensor technologies (Piezoelectric, capacative accelerometers, vibration sensor) to better understand the situation.

While piezoelements offer a good signal to noise ratio, they also act as high pass filters. This property provides them with a higher sensitivity for higher frequency vibrations, but hence not the ideal solution for lower frequency vibrations, which is more similar to human knocks [4]. While this blog [4], compares accelerometers with professional piezoelectric sensors, which are much more sensitive than the piezoelectric devices used in other projects, the same fundamental limitation applies to them as well. Especially considering, vibrations when traveling through various materials may loose high frequency energy relatively quickly, depending on the material property and thickness, which may make it even harder to detect. On the other hand accelerometers allow sensing of flat responses (0Hz) and hence have good sensitivity for even lower frequencies [4]. Vibration sensors allow for detecting only above a specified frequency, depending on its calibration.
Accelerometers generally have chips to process and amplify signal which can communicate the information using I2C or SPI communication instead of Piezoelectrics devices, which are analog or vibration sensor which are digital. This implies, theoretically, an accelerometer should allow for much more customisability via software, as the chips also have many interrupts. They chips are able to process these informations quite well to reduce noise. Accelerometer being 3-axis may also allow detection direction of knock which could be helpful in certain scenarios.
Piezo electric are analog passive devices, hence have quite less power consumption, however also implies they must be always awake to read. 
Vibration sensor have limited customisability due to their digital nature. They can either detect a knock or not, which can potentionally cause problems differentiating general vibrations from knocks.

A summary of all the differences between piezos, MEMs accelerometers and vibration sensor is shown in Table. 2.1

<div id="PiezoVsAccelVsVibration" >
</div>

*Table X: Comparison of Piezo, Vibration Sensors and MEMs Accelerometer*

| Feature | Piezoelectric Buzzer | Digital Vibration Sensor | MEMS Accelerometer (Capacative) |
| :--- | :--- | :--- | :--- |
| **Sensing Principle** | Piezoelectric (Acoustic/Resonant) | Spring-and-Ball (Mechanical Switch) | **Capacitive (Proof-Mass Displacement)** |
| **Output Type** | Raw Analog Voltage (Uncalibrated) | Digital Binary (HIGH/LOW) | **Digital Data ($I^2C$/SPI)** |
| **Detection Axis** | Single Axis (Directional) | Omni-directional (Uncalibrated) | **3-Axis ($X, Y, Z$) Sensing** |
| **Customizability** | **Low:** Fixed by hardware/surface | **None:** On/Off trigger only | **High:** Software-defined thresholds |
| **Power Management** | Requires constant CPU sampling | Interrupt-capable | **Integrated Interrupts (Deep Sleep)** |
| **Primary Limitation** | High-frequency bias (Acoustic) | Lack of pattern sensitivity | Higher initial code complexity |
| **Cost** | Extremely Low | Low | Moderate |

These sensors are then tested in [Section 4.4.2](#522-sensor-sch) and results can be found in [Section 5.1.1](#511-sensor-selection)

While an ESP32 has a higher power consumption in normal mode, in deep it falls much lower (around 5 uA) [6]. Which makes a viable option for battery powered applications with the controller mainly in deep-sleep. It also has more than enough processing power to handle the knock detection algorithm.
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->

## 3	Theory
### 3.1 Accelerometers
<div id="imu" align="center">
<figure>
  <img src="/resources/images/MEMS.jpg" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.1:</b> Diagram of Capacitive Accelerometer Working Principle</figcaption>
</figure>
</div>

### 3.2 I2C
<div id="i2c" align="center">
<figure>
  <img src="/resources/images/i2c_theory.png" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.2:</b> Diagram of I2C Working Principle</figcaption>
</figure>
</div>

### 3.3 High-Side Driver
<div id="highDriver" align="center">
<figure>
  <img src="/resources/images/driver_theory.png" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.3:</b> Diagram of High Side Driver Circuit</figcaption>
</figure>
</div>

### 3.4 Servo Motor
<div id="servo" align="center">
<figure>
  <img src="/resources/images/servo_theory.png" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.4:</b> Diagram of Servo Motor Working Principle</figcaption>
</figure>
</div>
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->

## 4	Methodology and Design

### 4.1 Design Approach <!-- V-model-->
Due to the high complexity of the project, the project team decided to use the V-model design flow. With this approach of continuous verification, the project team aimed to reduce risk by finding issues and their solutions early.

### 4.2 System Requirements <!-- Requirements, not specs -->
To fully implement the system, a number of requirements related to function, technology and project management have been outlined. 

#### 4.2.1 Functional Requirements

For Knock Knock Lock Box to be a satisfiable product, the following functional requirements must be implemented:

- It unlocks within 1-2 seconds when a specific knocking pattern is used on the surface of the box
- It indicates turns a green LED on and simultaneously plays a simple beep to indicate that the box has been unlocked
- It rejects pattern if incorrect within 1-2 seconds after knocking has ended
- It turns a red LED on and simultaneously plays a simple alarm to indicate that the knocking pattern was false or unrecognized
- It alerts when the battery level drops below a certain level by flashing a red LED, even in power saving mode
- It only powers on after some initial knock to wake up the system, on wake it shows an yellow LED
- If no knocks detected for 60 seconds, it goes back to power saving mode
- It has provision to use a Micro USB port as an alternative power source in case battery dies out, with no prospect to upload firmware through it
- It uses some actuator for unlocking and locking 
- It has a programming mode where the user sets the knock for the system to recognize, mode can only be entered when the box is unlocked 

#### 4.2.2 Technical Requirements

For the Knock Knock Lock Box to operate and perform its functions, the following technical requirements must be implemented:

- The sensor system can detect at knock amplitudes and output a measurable voltage reading to the MCU
- There are provisions to protect the sensor and MCU from voltage spikes that might occur from the power supply
- The MCU Software can detect at most 30 knocks with consecutive knocks being less than 2s apart and match the timings to the predefined knock pattern with a set tolerance of acceptance
- The power supply is a battery with a working voltage of 3.2V to 5.5V
- The enclosure can protect the system within a typical indoor environment (IP 31)
- The provision to set MCU to low power mode and wake it back up
- Should function at temperatures ranging 0-40°C and humidity 10-90%

#### 4.2.3 Project Requirements

For the Knock Knock Lock Box project to produce a functional product upon close out, the following project requirements must be met:

- the budget is 25€ not including the PCB or mechanical components
- the project workload is estimated at 240h
- all components ordered for the project must come from mouser.de 
- the project schedule adheres to the following deadlines
    - Schematic Design: 2025-10-26
    - PCB Design Draft: 2025-11-09
    - PCB Design and Partslist: 2025-11-23
    - PCB Assembly: 2025-12-20
    - Project Report: 2026-01-18
    - Project Presentation and Demo: 2026-01-21

### 4.3 System Architecture <!-- FSD and maybe specs -->
From the requirements outlined in [Section 4.2](#42-system-requirements), a system architecture was designed as shown in [Figure 4.1](#fsd). 
<div id="fsd" align="center">
<figure>
  <img src="/resources/images/fsd.png" alt="fsd" width="800">
  <figcaption align="center"><b>Figure 4.1:</b> Functional Structure Diagram of Entire System</figcaption>
</figure>
</div>

### 4.4	Hardware Design <!-- Schematics, explanations and component specifications -->
#### 4.4.1 Full Schematic Design
The next layer after the [system architecture](#43-system-architecture) was defined as the schematic of the system as shown in [Figure 4.2](#schematic). In designing the schematic, each of the sub-systems defined in [Figure 4.1](#fsd) were treated separately before integrating together.
<div id="schematic" align="center">
<figure>
  <img src="/resources/images/KnockLock_Schematic.png" alt="Schmematic" width="1100">
  <figcaption align="center"><b>Figure 4.2:</b> Full Schematic of the System</figcaption>
</figure>
</div>

The following sections discuss the design of the schematic as well as the specifications of the most important components for each sub-system. 

#### 4.4.2 Sensor Sub-System
The first of these sub-systems is the sensor sub-system is as shown in [Figure 4.3](#sensor-sch). 
<div id="sensor-sch" align="center">
<figure>
  <img src="/resources/images/sensor_sch.PNG" alt="sensor-sch" width="400">
  <figcaption align="center"><b>Figure 4.3:</b> Schematic of the Sensor Sub-System</figcaption>
</figure>
</div>

As mentioned in the [Section 2 Literature Review](#2literature-review), most existing projects implemented a piezo element over an accelerometer or a vibration sensor to detect knocks. However, [Table 1](#PiezoVsAccelVsVibration) also revealed the potential efficacy of using an accelerometer instead of a piezo. Thus, to identify an appropriate sensor for the most accurate and reliable knock detection, a simple comparative experiment was conducted. A piezo disc (DAOKAI JA-DA-036 27mm) was tested against an accelerometer development module (JOY-IT SEN-MMA8452Q) which was readily available in the lab. Note the vibration sensor was excluded from this comparative testing as with its preliminary testing it was revealed that it has significant reliability issues. The sensor lacked the necessary sensitivity control, often oscillating between over-sensitivity (detecting ghost knocks) and under-sensitivity.

The sensors were tested in two different scenarios: a thin plastic lid and on a wooden chair as seen in Figures [4.4](#sensorTestPlastic) and [4.5](#sensorTestWood) respectively. This allowed for understanding how each sensor performed on materials of very different densities and stiffness's. In each test, the sensors were attached to surface and connected to an Arduino UNO for processing the output. Knocks were then applied to the other side of the material and the readings were recorded and compared.
<div id="sensorTestPlastic" align="center">
<figure>
  <img src="/resources/images/testingSetupPlastic.png" alt="Testing setup 1 - Plastic" width="400">
  <figcaption align="center"><b>Figure 4.4:</b> Testing Setup 1 - Plastic</figcaption>
</figure>
</div>

<div id="sensorTestWood" align="center">
<figure>
  <img src="/resources/images/testingSetupWood.png" alt="Testing setup 2 - Wood" width="400">
  <figcaption align="center"><b>Figure 4.5:</b> Testing Setup 2 - Wood</figcaption>
</figure>
</div>

The results of this comparative test can be found in [Section 5.2.1](#521-sensor-selection). The sensors were compared based on two criteria. 
1. Reliability of detecting knocks of different strengths in each setup
2. Reliability of detecting knocks of different speeds in each setup

The general expectation was that both sensors would exhibit similar accuracies and since the piezo is significantly cheaper, the piezo would be the ideal sensor.

#### 4.4.3 Lock Actuator Sub-System
On the other end of the system is the locking mechanism which is accomplished through a lock actuator. The circuit to interface this actuator is shown in [Figure 4.6](#lock-actuator-sch).  
<div id="lock-actuator-sch" align="center">
<figure>
  <img src="/resources/images/motor-control_sch.PNG" alt="lock-actuator-sch" width="600">
  <figcaption align="center"><b>Figure 4.6:</b> Schematic of the Lock Actuator Sub-System</figcaption>
</figure>
</div>

The initial concept of the product as shown in [Figure 1.1](#prelimiary-sketch) envisioned the use of a solenoid actuator to work similar to bolt in a door. However, another component which could accomplish the locking while also being cheaper and using less power is a simple servo motor. As such, a number of options for both were found on Mouser for consideration and compared in [Table X](#tab:servo-comp). Clearly, the power requirement for the solenoid is much higher than the that of the servo. This would mean either a boost converter or some other additional voltage regulation would be needed to power the solenoid. On top of that, the solenoids are more expensive per unit. As such, the project team opted to use a servo motor and chose the SER0050 since it is a higher torque than the SER0049. 

<div id="tab:servo-comp">

*Table X: Comparison of Solenoids and Servos Available on Mouser*
| Type     | Model Number | Price [€] | Voltage [V] | Load Current [mA] | Lock Length [mm]        |
| -------- | ------------ | --------- | ----------- | ----------------- | ----------------------- |
| Solenoid | 3992         | 6.45      | 5–6         | 800-1000          | 10                      |
| Solenoid | 412          | 6.45      | 12          | 300               | 15                      |
| Solenoid | 2776         | 4.43      | 5           | 1100              | 3                       |
| Servo    | SER0050      | 5.16      | 4.8–6       | 110-120           | 15                      |
| Servo    | SER0049      | 4.30      | 4.8–6       | 110-120           | 15                      |
<div>

Another important aspect of the lock actuator interface is the power cut-off system. This is accomplished using a high side driver as described in [Section 3.3](#33-high-side-driver). Essentially, the P-MOSFET (Q2) cuts the actuator's power supply line off when triggered. It is driven by an NPN transistor (Q1) which is driven by the microcontroller. 

#### 4.4.4 Controller Sub-System
Potentially the most important of the sub-systems is the controller sub-system shown in [Figure 4.7](#controller-sch).
<div id="controller-sch" align="center">
<figure>
  <img src="/resources/images/controller_sch.png" alt="controller-sch" width="480">
  <figcaption align="center"><b>Figure 4.7:</b> Schematic of the Controller Sub-System</figcaption>
</figure>
</div>

The microcontroller (MCU) interfaces the sensor, the lock actuator and the human machine interface (HMI). It handles all the processing and runs the program developed in [Section 5.5](#55-software-design). The complete pin mapping of the MCU is shown in [Table X](#tab:controller-pin-mapping). 

<div id="tab:controller-pin-mapping">

*Table X: Pin Mapping of Microcontroller*
| Pin   | Name  | Type / Label     | Description / Connection                                   |
|------:|-------|------------------|------------------------------------------------------------|
| 1     | 3V3   | Power            | +3.3V Supply from Regulator                                |
| 2     | EN    | Reset            | Enable / Reset connecting to Reset Button                  |
| 3     | IO4   | WAKE_INT         | Wake Interrupt for Sensor                                  |
| 4     | IO5   | SCL              | SCL (I2C Clock) with 4.7kΩ Pull-up                         |
| 5     | IO6   | SDA              | SDA (I2C Data) with 4.7kΩ Pull-up                          |
| 6     | IO7   | PROG             | Input to trigger programming mode. Pulled up.              |
| 7     | IO8   | -                | Strapping pin pulled up for easy booting into UART download mode |
| 8     | IO9   | BOOT             | Strapping Pin connected to pin header for booting into UART download mode |
| 9     | GND_1 | Ground           | Not Connected                                              |
| 10    | IO10  | BUZZ             | Buzzer                                                     |
| 11    | RXD   | RX               | UART Receive                                               |
| 12    | TXD   | TX               | UART Transmit                                              |
| 13    | IO18  | RLED             | Red LED                                                    |
| 14    | IO19  | YLED             | Yellow LED                                                 |
| 15    | IO3   | GLED             | Green LED                                                  |
| 16    | IO2   | BAT_V            | Battery Voltage Monitoring                                 |
| 17    | IO1   | CONTROL          | Control signal for Lock Actuator                           |
| 18    | IO0   | SERVO            | Signal to cut-power to Lock Actuator                       |
| 19–27 | GND   | Ground           | Main System Ground                                         |
</div>

From [Table X](#tab:controller-pin-mapping), it can be seen that the chosen MCU must have:
- at least 11 programmable GPIOs
- I2C communication
- at least 1 ADC GPIO 
- on-board UART interface 
- exposed enable and strapping pins

Additionally, the chosen MCU must large enough to easily solder onto a PCB. 

Given the ease in which it can be programmed via the Arduino IDE and it's high speed and robust features, the project team believed an MCU from the ESP32 line would best fit the specifications. On Mouser, a number of options that met the basic specifications were found as shown in [Table X](#esp32-comp). Ultimately, the decision to chose the ESP32-C3-WROOM-02-N4 was because it was large and had pins exposed on the sides for easier assembly (unlike the 356-ESP32C6MINI1H8) and it was cheaper than the H4 while still meeting all the specifications.
<div id="tab:esp32-comp"> 

*Table X: Comparison of ESP32 Chips Available on Mouser*
| Part Number           | Price [€] | Interfaces       | GPIO Count | ADC GPIOs | Size [mm]   | Package Type                         |
| --------------------- | --------- | ---------------- | ---------- | --------- | ----------- | ------------------------------------ |
| ESP32-C3-WROOM-02-N4  | 3.12      | I2C, SPI, UART   | 15         | 4         | 18 × 25.5   | Castellated module with exposed pins | 
| ESP32-C3-WROOM-02-H4  | 3.36      | I2C, SPI, UART   | 22         | 4         | 18 × 25.5   | Castellated module with exposed pins | 
| 356-ESP32C6MINI1H8    | 4.69      | I2C, SPI, UART   | 22         | 6         | 13.2 × 16.6 | Castellated mini module with pins underneath |
</div>

#### 4.4.5 Programming Interface Sub-System
In order to program the [controller sub-system](#442-controller-sub-system), a programming interface as shown in [Figure 4.8](#prog-interface-sch) is required. 
<div id="prog-interface-sch" align="center">
<figure>
  <img src="/resources/images/programming-interface_sch.png" alt="prog-interface-sch" width="400">
  <figcaption align="center"><b>Figure 4.8:</b> Schematic of the Programming Interface Sub-System</figcaption>
</figure>
</div>
The design simply uses a pin header which connects to the UART receiver and transmitter pins of the microcontroller so that it can be programmed directly through the on-board UART interface. This is done as opposed to using a USB-to-UART Bridge chip because it requires less components on the PCB and thus lowers costs. The boot pins can be connected with a jumper to pull down the strapping pin and the the button pulls down the enable pin to reset the microcontroller so that it can boot into UART download mode.

#### 4.4.6 Human Machine Interface Sub-System
Since the product has to be used by humans, it requires a human machine interface (HMI) which is illustrated in [Figure 4.9](#hmi-sch). 
<div id="hmi-sch" align="center">
<figure>
  <img src="/resources/images/hmi_sch.png" alt="hmi-sch" width="400">
  <figcaption align="center"><b>Figure 4.9:</b> Schematic of the HMI Sub-System</figcaption>
</figure>
</div>

The HMI uses three different LEDs to convey different meanings to the user. The general idea was: 
- the green LED indicates that the box is unlocked
- the yellow LED indicates the box is locked and in stand-by
- the red LED indicates when unlocking attempt was unsuccessful

The buzzer was then intended to create auditory feedback for the same actions as described above. One sound indicates when the box is unlocked successfully. Another for when it is unsuccessful. Here, careful consideration of which frequencies to use on the buzzer must be taken. The loudness of the buzzer should be high enough to be heard through housing, but not so loud as to be uncomfortable for the user. Thus, a sound pressure level of around 80dB is sufficient.

Finally, the HMI includes a simple button which can be used to enter the programming mode of the product.

#### 4.4.7 Power Regulation Sub-System
Finally, the system cannot function without reliable power and as such a power regulation system has to be defined as shown in [Figure 4.10](#power-sch). 
<div id="power-sch" align="center">
<figure>
  <img src="/resources/images/power-regulation_sch.png" alt="power-sch" width="800">
  <figcaption align="center"><b>Figure 4.10:</b> Schematic of the Power Regulation Sub-System</figcaption>
</figure>
</div>

Since the [controller](#444-controller-sub-system) uses an ESP32 which requires 3.3V, a voltage regulator that outputs 3.3V is required. The most common and efficient means of accomplishing this is using a higher voltage supply and using regulator to step down the supply. For the purpose of this project, a switching buck converter was chosen instead of using a linear voltage regulator as they are higher efficiency and produce less heat. Mouser has a very large range of switching regulators, many of which meet these minimum specifications. Ultimately, the LM2575-3.3WT was chosen since it was rather cheap, has a maximum input voltage of 40V and typical efficiency of 75%. Additionally, the diode used in the regulation circuit also needs to have low forward voltage drop and low junction capacity so that it provides minimal impede the hight frequency switching.

The voltage regulation must also provide protection in addition to providing the right voltage level. The buck converter itself inherently provides over-voltage protection up to 40V. To implement reverse polarity protection, TVS diodes are used in combination with a fuse. The diode is connected across the junctions such that when a reversed voltage is connected, the diode shorts the external source and not the rest of the circuit. The fuses also provide over-current protection. To dimension the fuse, the specifications of the LM2575-3.3WT were considered. With a maximum output current of 1A, output voltage of 3.3V, efficiency of 75% and input voltage of 6V, the maximum current required by the regulator is around 0.733A. Thus, the fuse should safely carry around 1A to account for fluctuations. As such, the PFRA110 was chosen as it has a hold current of 1.1A and a trip current of 2.2A. This fuse is also resettable so after current is cut-off, the fuse can cool down and reset. 

Another interesting aspect of the circuit is the inclusion of an alternative power connection. The battery terminal is meant to be the primary power source via 4S AA batteries and the micro USB port is for emergency powering when the battery dies and the box is locked. It also connects to the voltage regulator and has it's own protection fuse and diode.

Finally, the circuit contains a simple voltage divider that steps down the 5V supply line to less than 3.3V so that it can be read by the ADC on the microcontroller. The voltage at the ADC can then be calculated using a voltage divider. However since the resistor values are fixed and the ADC value is read by the controller, it can be reversed to get the voltage of the battery as follows:

$`V_{out} = \frac{R_2}{R_1 + R_2}\dotV_{bat}`$

$`V_{bat} = \frac{readingInMillivolts}{1000}\dot\frac{R_1+R_2}{R_2}`$

$`V_{bat} = \frac{readingInMillivots}{1000}\dot2.47`$


V~out~ is what is read by the microcontoller and hence can be used to calculate the voltage at the battery using the fixed resistor values.

#### 4.4.8 Component Specifications  <!-- Table of main components and their most important specs -->
Based on the circuit design and requirements, the specifications of the main components of the system are compiled in [Table X]()

<div id="tab:specs">

*Table X: List of Component Specifications*
| Component                      | Main Specifications                                                                          |
| ------------------------------ | -------------------------------------------------------------------------------------------- |
| Sensor                         | Reliably detect knocks of different strengths and at different speeds                        |
| Lock Actuator                  | 5 V operation, > 4 mm travel length (suitable for small box)                                 |
| Bipolar NPN Transistor         | Maximum collector–emitter voltage > 5 V                                                      |
| P-channel MOSFET               | Maximum drain–source voltage > 5 V, gate–source threshold voltage < 3.3 V                    |
| Microcontroller                | 11 GPIOs, I2C, 1 ADC GPIO, UART, enable and strapping pins, large package size, exposed pins |
| LEDs                           | Medium luminous intensity (> 180 mcd) and low power consumption (< 100 mW)                   |
| Buzzer                         | Medium sound pressure level (~80 dB)                                                         |
| Push Button                    | Isolating voltage > 5 V                                                                      |
| 3.3 V Output Voltage Regulator | Input voltage up to 40 V, output voltage 3.3 V                                               |
| TVS Diode                      | Maximum forward current > 2.5 A, DC blocking voltage > 10 V                                  |
| Schottky Diode                 | Forward voltage drop < 1 V, low junction capacitance < 1 nF                                  |
| Resettable Fuse                | Hold current > 1 A, trip current > 2 A                                                       |
| Battery Holder                 | Holds 4 AA batteries in series                                                               |
| AA Battery                     | 1.5 V                                                                                        |
| Micro USB B                    | Input voltage > 6 V, durability > 2000 cycles                                                |
</div>

### 4.5 Software Design <!-- Just logic no code yet -->
#### 4.5.1 System Flowchart
The following flowchart shows the overall logic of the program:
<div id="sw-flow" align="center">
<figure>
  <img src="/resources/images/FlowchartOfMainSystem.png" alt="sw-flow" width="400">
  <figcaption align="center"><b>Figure X:</b> Programming Flowchart of Entire System</figcaption>
</figure>
</div>

The flowchart in [Figure X](#sw-flow) shows, how the system must work, spikes denote knocks detected. The system starts in locked state, where it continously listens for knocks, unless its asleep, and records them. Interrupts will be used to wake the system up from sleep for again starting to read knocks. Once the knocks are recorded, they are checked against the target pattern, if they match, the system unlocks, else it stays locked. If the box is unlocked and the programming button is pressed, the system enters programming mode, where it records knocks to save a new pattern. Once the pattern is recorded, it is saved to NVS memory and the system goes back to idle mode. Knocking twice locks the box again. LEDs and Buzzer are used to give feedback to the user.

#### 4.5.2 Code Structure
For easy code understanding and better readability, a modular approach was taken. Splitting the code in different cpp files depending on the type of function. A config.h file also was created to storing all customisability settings. This file had only settings constants and no code or variables to prevent confusion for a user, and make it less error prone. The files structure to be followed is listed in [Table X](#tab:sw-files).

<div style="text-align: left" id="tab:sw-files">

*Table X: Software Files Structure*
| File Name (Header)    | Purpose                                                                                           |
|------:                |---:                                                                                               |
|   batteryMonitoring               | Functions to monitor battery                                                                      |
|   config                          | File to store all setting constants, for easy editting of settings                                |
|   globalVariables                 | File storing all global variables, also explanations of some other important non global variables |
|   hardware                        | All pin, objects definition and hardware initialization and interrupt functions                   |
|   hmi                             | All human interface related functions, for controlling buzzer, LEDs and actuator                  |
|   KnockLock (ino)                 | Main code to run with setup and endless loop                                                 | 
|   patternRecognitionandRecording  | Core functions to process/record                                                             |
|   sleepMode                       | Function related to sleep and wake up of controller                                          |
|   usingNVS                        | Functions related to saving and reading data from the non-volatile storage of the controller |
</div>

Arduino IDE will be used to program the controller in C++. This is because Arduino IDE provides access to wide range of libraries for various controllers with ease.

The final code implementation can be seen in [Section 5.5](#55-software-implementation).

### 4.6 Housing Design <!-- design for housing -->
<div id = "housing-model" style="display: flex; gap: 10px; height: 250px;">
<figure>
  <img src="/resources/images/KnockLockFront_1.PNG" loading ="lazy" alt="housing-front">
  <img src="/resources/images/KnockLockSide.PNG" loading ="lazy" alt="housing-side">
  <figcaption align="center"><b>Figure X:</b> Programming Flowchart of Entire System</figcaption>
</figure>
</div>

For demonstration purposes, a box was modeled. The door must mount the PCB, this way the knocks can be reliably detected when door (typically primary place for knocking) is knocked. The battery has been kept in the base of the box to reduce the weight of the hinges for longetivity of the box. Keeping it in the base also makes battery replacement a bit easier. 
In the door, it is important to have supports to screw in the PCB well, with minimal movement to prevent double knock detections. The door must have also have holes to keep the LEDs visisble as well as a button which connects to the button on the PCB to allow user to program the system when required. The USB B port must remain accessible as well, as well as a place to secure in the servo motor. The preliminary 3D Model can be seen in [Figure X](#housing-model). The final housing can be seen in [Section 5.6](#56-housing-prototype).

### 4.7 Pre-Implementation Verification Methods <!-- How did we test during development? -->
#### 4.7.1 Concept Feasibility Testing <!-- Testing the sensor to see if concept is feasible -->
Before development, the feasibility of the knock detection concept must be tested. If there is no reliable way of detecting knocks and most importantly detecting the knock pattern, then the project is a failure. Luckily, the experimental setups described for sensor selection in [Section 4.4.2](#442-sensor-sub-system) can provide results that not only identify the most appropriate sensor for the project but also the entire concept feasibility. The results of this experiment are presented in [section 5.1.1](#511-concept-feasibility)

#### 4.7.2 Prototype System Testing <!-- Testing entire system in breadboard -->
After confirming feasibility, the system as described in [Section 4.4.1](#441-full-schematic-design) must also be verified. For ease of setup, development modules were selected to test the overall function of the system as well as initiate software development while the PCB was being manufactured. The following components were used:
- Microcontroller: ESP32-DevKitM-1
- HMI: red, yellow and green LEDs and a piezoelectric buzzer (PKM22EPPH4001-B0)
- Sensor: JOY-IT SEN-MMA8452Q
- Lock Actuator: SG90 servo motor
- Misc: breadboard, resistors, jumper cables

The results of this test are presented in [Section 5.1.2](#512-prototype-system)

#### 4.7.3 Prototype Module Testing <!-- Testing different sections of circuitry to see if PCB layout is good -->
Before the PCB could be designed and manufactured, some of the sub-systems were tested to ensure they could function as designed. The following briefly describes the tests conducted:
- **Lock Actuator Sub-system**: To ensure the power cut off configuration works, the circuit as defined in [Figure 4.6](#lock-actuator-sch) was constructed on a breadboard using an ESP32-DevKitM-1, a BC547B NPN Transistor, an IRF4905 P-channel MOSFET, SER0050 servo motor and THT resistors. Only the decoupling capacitors were neglected as the development board provided stable power. Results of this test are presented in [Section 5.1.3](#513-lock-actuator-interface-test).
- **Programming Interface Sub-system**: To ensure that the microcontroller can easily be programmed directly via the UART interface, an Arduino UNO board was used to program an ESP32-DevKitM-1. Like the ESP32C3, the ESP32MINI found on the ESP32-DevKitM-1 has a UART interface which it can supposedly be programmed via. The Arduino Uno board was essentially used just as a USB-to-UART bridge as the enable pin was connected to ground and the RX and TX pins were connected to the TX and RX pins of the ESP32-DevKitM-1 respectively. Results of this test are presented in [Section 5.1.4](#514-programming-interface-test). 
- **HMI Sub-system**: To ensure the HMI, the circuit as defined in [Figure 4.9](#hmi-sch) was constructed on a breadboard. This test was essentially done as part of the prototype system test as described in [Section 4.7.2](#472-prototype-system-testing).

### 4.8 Post-Implementation Verification Methods <!-- How did we test after development?-->
#### 4.8.1 PCB Module Testing <!-- Checking each sub-system on the PCB -->
After the PCB has been assembled, each sub-system must be tested before the entire system integration is tested. For this reason, various test points are included within the schematic as seen in [Figure 4.2](#schematic) for each sub-system. The following describes what each test point is designed to check:
- **Sensor Sub-system**: 
  - Test Point 5: the signal sent by the accelerometer's activity interrupt
  - Test Point 6: the supply voltage of the accelerometer
- **Controller Sub-system**
  - Test Point 3: the I2C communication line for the MCU
- **Power Regulation Sub-system**:
  - Test Point 1: the input voltage from the battery supply
  - Test Point 2: the input voltage from the alternative supply via micro USB
  - Test Point 4: the output voltage of the voltage regulator

The main purpose of these test points is checking if components are receiving the correct power. They also check communication lines between the sensor and MCU for debugging. 

In addition to the test points, some test specifications were defined to test the general functionality of the sub-systems:
- **Sensor Sub-system**: 
  - Can only be tested if controller, programming interface and power regulation sub-systems are functional. See [Section 4.8.2](#482-pcb-system-integration-testing) for test specifications.
- **Lock Actuator Interface Sub-system**: 
  - To test functionality of the this sub-system, the voltage across pins 2 and 3 of the servo connector (J5) and voltage of the base (pin 2) of NPN transistor (Q1) relative to ground can be measured. The sub-system is functional if the connector voltage is high when the base voltage is high and low when the base voltage is low. See [Figure 4.6](#lock-actutator-sch) for pins.
- **Controller Sub-system**: 
  - To test functionality of this sub-system, the MCU is connected to power and the status yellow LED checked. The sub-system is functional if the yellow LED is on when the MCU is powered. This is because the yellow LED is on IO19 which pulled up by default.
- **Programming Interface Sub-system**: 
  - To test the functionality of this sub-system, an external USB-to-UART programmer (or Arduino UNO) is connected to the RX and TX pins, the boot pins are connected together and the the reset button is pressed. If the MCU is recognised by Arduino IDE, the sub-system is functional. 
- **HMI Sub-system**:  
  - Can only be tested if controller, programming interface and power regulation sub-systems are functional. See [Section 4.8.2](#482-pcb-system-integration-testing) for test specifications.
- **Power Regulation Sub-system**: 
  - To test the functionality of this sub-system, the voltage at test point 4 relative to ground is be measured when the battery is connected. If this voltage is 3.3V, the sub-system is functional.

#### 4.8.2 PCB System Integration Testing <!-- Checking function of the entire PCB -->
With certainty that the sub-systems are powered and functional, the integration between sub-systems can be tested. The following test specifications to test integration were defined:
- **Reading Serial Data of the Sensor**: 
  - To test the functionality and integration of controller, programming interface and sensor sub-systems, the MCU can be flashed with an example program to read the sensor data and print it in the serial monitor. The sub-systems are fully integrated if data appears in the serial monitor and is responsive when the PCB is moved around.
- **Programming the MCU to Blink and Beep**: 
  - To test the functionality and integration of controller, programming interface and HMI sub-systems, the MCU can be flashed with an example blink program and example beep program from Arduino IDE (with pins adjusted accordingly). The sub-systems are fully integrated if each LED blinks and the buzzer beeps when programmed to.
- **Programming the MCU to Turn on and Cut Lock Actuator Power**: 
  - To test the functionality and integration of controller, programming interface and lock actuator interface sub-systems, the MCU can be flashed with a basic program that brings the IO0 high and measuring the voltage across pins 2 and 3 of the servo connector (J5).  The sub-systems are fully integrated if the voltage is high when IO0 is high.

Finally, the integration of the complete system must be tested against the requirements outlined in [Section 4.2](#42-system-requirements). The following is the test specifications defined:
- The MCU is flashed with a the program developed in [Section 5.5](#55-software-implementation).
- The corner of the PCB is tapped to simulate a pre-defined knock pattern. 



#### 4.8.3 Power Consumption  <!-- Checking power consumption in active and sleep modes -->
Once the general functionality of the system has been verified, another important characteristic of the system must be investigated: the power consumption. To determine the amount of power consumed by the system and estimate the battery life of the system, the current drawn by the system must be measured. To do this, an ammeter can be connected in series with the power supply and the battery terminal. The system can then be tested in different modes and functions so that the current measurements in all cases can be taken. The results of this test are presented in [Section 5.8.3](#583-power-consumption).

### 4.9 Validation Methods  <!-- Are we making the right product? -->
#### 4.9.1 Complete Product Testing <!-- How can we test the product in the right environment -->


#### 4.9.2 User Acceptance Testing  <!-- Presenting prototype to potential users -->
Over the course of a week, 10 people were surveyed using convenience sampling. Each person was shown the final prototype and asked four questions:
1. What would you rate this product out of ten?
2. What is one feature you especially liked about the product?
3. What is one feature you disliked about the product?
4. What is one feature you believe would improve or should be implemented into the product?

The findings can be found in [Section 5.9.1](#591-user-feedback).

It should also be noted that the majority of the people surveyed are familiar with the members of the development team and thus some responses may contain bias. 
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 5	Results
### 5.1 Pre-Implementation Verification Results
#### 5.1.1 Concept Feasibility 
The results from the tests described in [Section 4.4.2 Sensor Sub-system](#442-sensor-sub-system) are summarized below:
- Both the piezo disc and IMU were able to detect knocks through a plastic case quite reliably. Though, through the wood, only the IMU was able to detect any knocks.
- In both setups, the IMU was able to detect very fast knocks, but the piezo in plastic setup occasionally missed knocks that were too quick. 

Even after trying to make the piezo a more sensitive by using 3.3V supply instead of 5V, it still couldn’t match the performance of the IMU. This was very unexpected considering other projects in the [Literature Review](#2literature-review). Additionally, the i2c communication of the IMU was observed to be significantly more reliable than the voltage output of the piezo element. 

The IMU also gave data for all three axes. A typical series of knocks as detected by the IMU can be seen in [Figure 5.1](#imu-test). The y-axis is the magnitude in g (gravitational units), while the x-axis is time in milliseconds. The blue, yellow and green lines are the x, y and z axis respectively. Each knock caused a peak in each of the three axes, but most prominently in the axis perpendicular to the surface of the material. As such the knock detection software as discussed in [Section 5.5.2](#542-knock-detection), initially considered only the value of this axis. [Figure 5.1](#imu-test) also clearly shows that the peaks have a noticeable time gap between them. This suggests that if the peaks are registered as knocks and the interval between peaks are measured, it is definitely feasible for the software to detect a specific knock pattern based on the the amount of knocks and their intervals.
<div id="imu-test" align="center">
<figure>
  <img src="/resources/images/knockDetectionIMU.png" alt="imu-test" width="400">
  <figcaption align="center"><b>Figure 5.1:</b> Serial Plot from Test of MMA8452Q IMU </figcaption>
</figure>
</div>

#### 5.1.2 Prototype System 
With feasibility confirmed, the development processes continued and a prototype for the entire system as described in 

<div id="system-prototype" align="center">
<figure>
  <img src="/resources/images/testingSystem_iso.jpg" alt="system-prototype" width="400">
  <figcaption align="center"><b>Figure 5.2:</b> Breadboard Prototype System</figcaption>
</figure>
</div>

#### 5.1.3 Lock Actuator Interface Test

<div id="lock-actuator-prototype" align="center">
<figure>
  <img src="/resources/images/motor-control_test.jpg" alt="lock-actuator-prototype" width="400">
  <figcaption align="center"><b>Figure 5.3:</b> Breadboard Prototype Lock Actuator Interface</figcaption>
</figure>
</div>


#### 5.1.4 Programming Interface Test

<div id="prog-interface-prototype" align="center">
<figure>
  <img src="/resources/images/testing-programming.jpg" alt="prog-interface-prototype" width="400">
  <figcaption align="center"><b>Figure 5.4:</b> Setup to Test Direct UART Programming</figcaption>
</figure>
</div>

#### 5.1.5 HMI Test

### 5.2 Component Selection <!-- Results of tests between components -->
#### 5.2.1 Sensor Selection <!-- Choosing an appropriate sensor -->
As demonstrated in [Section 5.1.1](#511-concept-feasibility), the accelerometer exhibited much better performance than the piezo disc and thus the project team decided that an accelerometer would be the most appropriate sensor. 

While the tests were conducted with a MMA8452Q by Sparksfun Electronics, the final design uses an ADXL345, as it was cheaper and larger in package size making it easier to solder. The ADXL345 is also 13-bit instead of 12-bit, hence should perform even better.

#### 5.2.2 Other Components
Aside from the sensors, all components were chosen based on the specifications outlined in [Section 4.4.8](#448-component-specifications) in [Table X](#tab:specs). The complete list of all materials used is shown in [Section 5.7](#57-bill-of-materials). Any modifications to the components selected or designed in [Section 4](#4methodology-and-design) is explained in following sections. 

### 5.3 PCB Design <!-- PCB layout, issues and changes to schematic -->
With components selected and the system prototype verified, the layout of the PCB could be designed. The first version of the PCB layout is shown in [Figure 5.5](#pcb-v1). In creating the design, a few important things were considered as follows:
- The voltage regulator was placed far away from the MCU to prevent the switching magnetic field from interfering with the processing.
- The track width for power (0.7mm) was significantly larger than that of signals (0.2mm) to ensure power tracks have lower resistance and can carry sufficient current.
- Both the top and bottom copper layers had a ground plane for better grounding and heat dissipation.
- Wherever possible, power and signal tracks were not run parallel to each other.
- Tracks were never drawn with 90 degree bends.

<div id="pcb-v1" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V1.PNG" alt="pcb-v1" width="400">
  <figcaption align="center"><b>Figure 5.5:</b> First PCB Layout </figcaption>
</figure>
</div>

While this design passes the design rule check in KiCAD, it has a number of issues:
- The biggest issue is that the PCB antenna is above a copper plane which can lead to electromagnetic interference in the ground net.
- Some of the clearances between tracks are too small leading to poor manufacturability and poor insulation between tracks
- 0.2mm track width is difficult to manufacture
- Vias with 0.6mm diameter and 0.3mm hole diameter are too small to be manufactured by AISLER

Thus, considering these issues a second design was done as shown in [Figure 5.6](#pcb-v2). In this design, the MCU was shifted to the edge of the PCB and a copper keep-out zone was defined beneath the antenna. The track width and vias diameter were increased to 0.7mm and 0.8mm (with 0.4mm hole diameter) respectively. Additionally, under the advice of Professor Andy Stamm, all of the resistors and ceramic capacitors were changed to SMT components instead of THT. The idea behind this switch was that since the accelerometer and MCU required reflow soldering regardless, it would be more efficient to also solder these components in the reflow oven in the same session.
<div id="pcb-v2" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V2.PNG" alt="pcb-v2" width="400">
  <figcaption align="center"><b>Figure 5.6:</b> Second PCB Layout </figcaption>
</figure>
</div>

One issue encountered in the formation of this layout was the routing to the micro-controller pins was incredibly difficult. Thus, some of the pins were remapped to make the routing is more intuitive. (Note that the pin mapping in [Table X](#tab:pin-mapping) is already the final mapping).
<div id="tab:pin-revision">

*Table X: Changes in Pin Mapping For PCB Adjustments*
| Signal / Function         | Old PCB Pin | New PCB Pin       |
| ------------------------- | ----------- | ----------------- |
| Battery Voltage (BAT_V)   | 3           | 16                |
| I2C SDA                   | 14          | 5                 |
| I2C SCL                   | 13          | 4                 |
| Wake Interrupt (WAKE_INT) | 15          | 3                 |
| Servo Cut-off (SERVO)     | 5           | 18                |
| Servo Control Signal      | 4           | 17                |
| Red LED                   | 16          | 13                |
| Yellow LED                | 17          | 14                |
| Green LED                 | 18          | 15                |
</div>


Finally, the third and final design shown in [Figure 5.7](#pcb-v3) involved some refinement such changing the battery and servo connectors, adding vias for thermal relief, adding mounting holes and adding a [logo](#logo) in the silkscreen. The change in connectors was to facilitate the use of simple JST pin headers which were available in the lab.
<div id="pcb-v3" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V3-final.PNG" alt="pcb-v3" width="400">
  <figcaption align="center"><b>Figure 5.7:</b> Final PCB Layout </figcaption>
</figure>
</div>

### 5.4 PCB Assembly <!-- Final and issues encountered in assembly or after testing-->
After the PCB layout was finalised, the design was sent to AISLER for manufacturing. The final PCB without any components can be seen in [Figure ](#pcb-blank) 
<div id="pcb-blank"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/Unsoldered PCB.jpeg" height="200">
        <figcaption align="center"><b>(a):</b> Front </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/Unsoldered PCB 2.jpeg" height="200">
        <figcaption align="center"><b>(b):</b> Back </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 5.8:</b> Final Unsoldered PCB </figcaption>
  </figure>
</div>
<!-- <div id="pcb-blank" align="center">
<figure>
  <img src="/resources/images/Unsoldered PCB 2.jpeg" alt="pcb-blank" width="400">
  <figcaption align="center"><b>Figure 5.8:</b> Final Unsoldered </figcaption>
</figure>
</div> -->

<div id="pcb-front" align="center">
<figure>
  <img src="/resources/images/pcb_front.jpg" alt="pcb-front" width="400">
  <figcaption align="center"><b>Figure 5.9</b> Final PCB (front) </figcaption>
</figure>
</div>

<div id="pcb-back" align="center">
<figure>
  <img src="/resources/images/pcb_back.jpg" alt="pcb-back" width="400">
  <figcaption align="center"><b>Figure 5.10:</b> Final PCB (back) </figcaption>
</figure>
</div>

Due to the large number of SMD (Surface Mount Devices) Components, as well as because of ADXl345 being an LGA (Land Gate Array package), i.e. pads underneath, reflow oven was used to solder those components after placing the components using a pick and place. The solder paste was applied manually for each pad. The THT (Through Hole Technology) were later soldered using manual hand soldering.

Due to the extremely small size of the pads of the ADXL345 pads and ESP32-C3, placing solder paste took many attempts. Only after tweaking the pressure and the nozzle diameter for the solder paste dispensor was it possible to place it in adequate quantities without it reaching out of the pad. For components such as these, it might be a better approach in future to use a stencil, however for only producing one PCB, the cost were not justified and hence the approach avoided. 
Moreover, even though having a large GND plane allowed for better heat dissipation and a better PCB, it made soldering THT components harder as well. Much more heat was required to be able to solder the components reliabily. 

Most issues with soldering were sorted right after soldering, due to the verification process being right after. However the one was missed. Later it was discovered the servo was not functioning reliably. After using an oscilloscope to see its response, it was found out that the GND pin of the servo was connected, however not well which cause breakage at sometimes and hence the response was sometimes missed or delayed. This was fixed by soldering it again.

With the PCB all ready, now the software must be implemented on to it, to get the system to work.

### 5.5 Software Implementation <!-- Final code and issues after testing and how they were solved-->
As discussed in [Section 4.5](#45-software-design) a modular approach was used. The main startup code is in the file KnockLock.ino. 

The libraries used were:
- **ESP32 NVS Library**: For using the NVS memory of ESP32-C3 - in-built with Arduino IDE
- **SparkFun ADXL345 Library (v1.0.0)**: For interfacing with the ADXL345 accelerometer
- **Wire Library**: For i2c communication with the ADXL345 - in-built with Arduino IDE
- **ESP32Servo (v3.0.9)**: For controlling the servo motor

The code implementation of some crucial parts is explained below.
#### 5.5.1 System Initialization
Upon startup, the system must perform many intializations to get everything working correctly in sync. The order is also quite important to save power and to ensure best reliability. 

Upon starting up, its is the important for the system to know why it is starting up. This is because for saving battery, the system is kept in deepsleep, and in ESP32, waking up from deepsleep means setup functions runs again. Hence to prevent the system from draining to much battery, even if it woke up to only check battery and alert user for low power or because of double knocking or just first time starting up. How handleWakeup() does this can be seen in [Section 5.5.5](#551-power-management). If the system is supposed to full turn on, only then is the accelerometer setup and the servo enabled. It is important to setupHardware() before checking for wakeup, as the pin must be ready for battery voltage and used to flash the red LED to indicate low battery. setupHardware() is also responsible to attach interrupts to the correct pins and setting up the servo (not enabled yet). How this can be done can be seen in [Listing 1](#lst:setup_hw).

<div id="lst:setup_hw">

*Listing 1: Setting up hardware*
```cpp
if(SERIAL_MONITOR_EN) { // Enable Serial Monitor if required (can be changed in config.h)
    Serial.begin(115200);
    Serial.println("Serial monitor enabled!");
}

setupHardware(); // Setup hardware, all the pins modes and objects

handleWakeup(); //Check reason for waking up, and go accordingly.
// In case of checking battery and flashing led, it only does that and goes back to deep sleep
// If due to double knock, it goes through to normal setup to start listening for knocks

ADXLsetup();                  // Setup ADXL (accelerometer)
digitalWrite(SERVO_EN, HIGH); // Turn servo On
```
</div>

The ADXL, being powerered directly by the battery means it retains its settings hence even in deepsleep keeps its interrupts and other settings.

Once all hardware is setup, it is important for the system to load back the stored pattern, to prevent having the user from setting up the pattern each time the system wakes up. The system does this by loading the pattern, and its length from the NVS storage on the ESP32. It must then just reset the timers to prevent any unwanted actions before time. The system performs this as shown in [Listing 2](#loadPatternResetTimer).

<div =id"lst:loadPatternResetTimer">

*Listing 2: Loading the pattern and reseting timers*
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
</div>

Both the code snippets above are part of the setup() function in KnockLock.ino file.

For setting up the ADXL (accelerometer), the system uses its library for initializing it with the right settings and then disabling all the unecessary interrupts. The library used is SparkFun_ADXL345 (Version v1.0.0) as mentioned already in [Section 5.5](#55-software-implementation). All the values are given as constants here, from the setting up in config.h. For giving all these values and communicating with the ADXL, Wire library is used for setting up the i2c communication with it. This allows for easy editting for all parameters from one file. [Listing 3](#init_adxl) from hardware.cpp shows how the ADXL345 is setup.

<div id="init_adxl">

*Listing 3: Setting up the ADXL(accelerometer)*
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
  adxl.singleTapINT(1);                                           // Enable single tap interrupt

  // Disable all other interrupts, until required
  adxl.doubleTapINT(0);
  adxl.FreeFallINT(0);
  adxl.ActivityINT(0);
  adxl.InactivityINT(0);
  adxl.getInterruptSource();        // Reset all interrupt flags 
}
```
</div>

Disabling all interrupts ensure that no unecessary wakeups occur. Reseting all flags is very important, as ADXL345 interrupts work as latches. Which when triggered keep interrupt high, until reset. 

Now that the system is up and running, it must start detecting knocks.

#### 5.5.2 Knock Detection
When the system is awake, it is in idle state and locked state. During this the system keep checking for battery and the interrupts. Whenever a knock is detected by the ADXL (single tap interrupt) it sets the interrupt pin to high. This triggers an interrupt service routine of the system to set knockDetected as true.
The knock can then be processed and counted to compare against the pattern later. First, as [Listing 4](#readKnocks) shows, it is necessary to prevent a double knock and hence a debounce time is set between two knocks being recorded. Upon a succesful knock, the green LED is flashed, to indicate the knock being detected.
<div id="readKnocks">

*Listing 4: Reading knocks*
```cpp
// Function to deal with response if system locked
void handleLockedState(float aDynamic, unsigned long now) {
  if (knockDetected && (now - lastKnockTime) > DEBOUNCE_TIME) { // If knock is detected start recording its timing, debounce knock to prevent double knock
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
```
</div>

If it has been long since the last knock, it means the user is done and hence the knock is then checked against the pattern.
The processing of knocks in locked state is shown in [Listing 5](#startCheckingPattern).
<div id="startCheckingPattern">

*Listing 5: Finish reading knocks*
```cpp
  if (knockCount > 0 && (now - lastKnockTime > PATTERN_TIMEOUT)) { // If a long  break with  knocks, start checking the pattern
    checkPattern(); // Check the pattern, if it is correct it goes to unlocked state
    knockCount = 0; // If checked reset for next iteration
    led_ryg(0, 1, 0); // Show it is recording
  }
```
</div>

If no knocks are done, and it has been a while, the system goes to sleep to save battery as shown in [Listing 6](#backToSleep). It also resets its flags at the end to allow system to reuse them in other scenarios.
<div id="backToSleep">

*Listing 6: Going to sleep*
```cpp
  if (knockCount == 0 && (now - lastActivityTime > SLEEP_TIMEOUT)) { // If too long a break with no knocks, go to sleep
    goToSleep();
  }
  knockDetected = false;      // Clear flag
  adxl.getInterruptSource();  // Clear interrupt flags to reset interrupt pin
}
```
</div>

*Issues faced*

Initially a different approach was used for reading and processing the knocks. The raw ADXl values where read continously while the system is awake and converted to g for easier comparison as shown in [Listing 7](#oldCalcApproach). 
<div id="oldCalcApproach">

*Listing 7: Older magnitude calculation approach*
```cpp
inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(x*x + y*y + z*z)*0.0039*; // Calculate magnitude, for g, it must be multiplied by 0.0039 (from datasheet) 
}
```
</div>

The result could then be reduced by one to remove the static gravitational force to find dynamic force and compared to a fixed threshold found using many readings. This approach worked, however was not very effective and reliable with it being too sensitive or too insensitive at times. This was later then changed to reading only z-axis (absolute value), keeping in mind the axis is perpendicular to the PCB so when knock a plane parallel to the PCB it was the only axis greatly affected. Same was also seen in [Figure 5.1](#imu-test). This new approach worked much better for detecting knocks, however had one big drawback. It only worked in one specific orientation, with the PCB perpendicular to the ground plane. Finally it was realized, that the wake up which used the double tap interrupt was working much better, and hence for detecting individual knocks, single tap interrupt can be used. As this is made by the developers of the board, its noise removal and reliablitity was extremely high and knocks could be detected in all orientation. The threshold could also be setup much more reliably. The threshold of 40 was set which corresponded to ~2.5g when set to a scale of +-2g with a measurement sensitivity of 256 LSB/g [5]. The system with this threshold was able to ignore most background noise.  

With the knocks recorded, the system must now check for if the pattern is correct.

#### 5.5.3 Knock Pattern Checking Algorithm
For checking the knock pattern, the system takes a pessimistic approach. Here the pattern is assumed to be wrong , unless proven otherwise. This allows for a safe approach, so that even if the system faces issues, the box is less likely to open. However before checking the pattern, to minimize CPU cycles Some basic checks are done. This helped save processing time, especially if the pattern is completely wrong. The implementation is shown in [Listing 8](#preChecks).
<div id="preChecks">

*Listing 8: Prechecks before checking pattern*
```cpp
// Check if any pattern is even saved, if not return
if (patternLength <= 0) {
    if(SERIAL_MONITOR_EN) Serial.println("⚠ No saved pattern.");
    return;
}

if (knockCount < MIN_KNOCKS)
    return;
```
</div>

These checks were implemented at the start of the function and made sure that if no pattern is saved, or if too few knocks were recorded, the function returns immediately.

If these checks were passed, we calculate the intervals using the knock timings recorded using the code in [Listing 9](#calcIntervals).
<div id="calcIntervals">

*Listing 9: Calculate intervals*
```cpp
// Calculate intervals using knock timings
int intervalCount = knockCount - 1;

for (int i = 1; i < knockCount; i++) {
    intervals[i - 1] = knockTimes[i] - knockTimes[i - 1];
}
```
</div>

The algorithm then checks if the pattern entered by user is too short or too long for the target pattern. This is done, as shown in [Listing 10](#patternLengthCheck), before checking pattern to reduce CPU cycles in case incorrect. It also account for allowed mistake, which can be set from config.h, to make the system a bit more lenient by ignoring a certain number of mistake at the start or the end of the pattern, maybe due to accidental knocks. Setting this to zero makes it only accept only the right pattern of the right length.
<div id="patternLengthCheck">

*Listing 10: Checking pattern length*
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
</div>

If these checks are passed, the system starts checking the pattern, as shown in [Listing 11](#patternChecks), against the stored pattern with a tolerance. This tolerance is necessary, as it is next to impossible to get the exact same timings. Increasing or decreasing this value changes the leniency of the system. The checking also keeps into account the allowed number of mistakes. This is done using a slide window approach, where the pattern is checked against target, if it doesnt match, it is shifted by one until the allowed mistakes and checked against target pattern if correct.

<div id="patternCheck">

*Listing 11: Pattern checking*
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
</div>

Then according to the result of the checking stored in the variable ok the system either unlocks the box, sets state to unlocked (hence 1) with a good beep or if ok is false, does a bad beep and goes back to main.

All these code snippers in this section are part of the function checkingPattern() in file patternRecognitionAndRecording.cpp.

Now that the system can check for patterns, it must also be able to store new patterns to check. How this is done is explained in the next [Section 5.5.4](#554-saving-a-new-pattern).

#### 5.5.4 Saving a New Pattern
A similar function to locked state handler was implemented for the unlocked state as well as for recording the knocks to save a pattern. However this can only be called by cliking the programming button (Pin 7) when the box is unlocked. The button is attached as an interrupt, to allow it to be called whenever. Once the pattern was recorded a different function was called to save the pattern to the NVS memory of the ESP32-C3 and also playback the pattern to the user for a confirmation. To do so the the function shown in [Listing 12](#finishRecording) was implemented.
<div id="finishRecording">

*Listing 12: Processing finished recording*
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
</div>

Here first it is checked if enough knocks were recorded, if not, the user is alerted. If enough knocks were recorded, the intervals are calculated and saved to NVS memory using the function savePatternToNVS(). Then a success indication is given to the user using successSave() function, followed by playback of the pattern using playbackPattern() function. To allow user to unlock the box with the new pattern, without having to reset the system, the stored values are loaded again. They are not loaded each time in checking to save processing time. Finally the system goes back to idle mode, and the knock counts are reset. The LEDs are also turned off, but when it goes back to handle locked or unlocked state, they will be turned on again accordingly.

Finally, the system has all the crucial functions to work. However to run these system it must manage its battery efficiently to last as long as it possible on its battery life.

#### 5.5.5 Power Management
To save power, the ESP32-C3 stays in deep sleep mode most of the time, only waking up when knocks are detected. However to put the system to sleep appropriate steps must be taken in the correct order. 

Before going to sleep, the system first checks the battery voltage, to see if it is low or not. If it is low, the system must wake up every few seconds to blink the red LED indicating low battery to alert the user to changee it. If the battery is good, the system can sleep indefinitely until a knock is detected. There may be concern, that what if the system does not have low battery when going to sleep, but the battery drains while sleeping. However this is not a really big concern, as the drain will be very slow. Waking it up to check battery status regularly will waste more power. This decision of checking battery only before sleep was taken also taking into account the system has been designed with two sets of power supply, battery and USB. If the battery drains, the user can always plug in the USB power to power the system.

Checking the battery voltage by reading ADC value from the voltage divider and using the formula as stated in [Section 4.4.7](#447-power-regulation-sub-system). The system compares this to a threshold to denote if it is too low or not, as shown in [Listing 13](#batteryCheck). The system can also start powering down hardware which is not necessary anymore such as the LEDs off (until Red is required later) and the Servo motor.

<div id="batteryCheck">

*Listing 13: Checking battery*
```cpp
led_ryg(0,0,0); // Turn off all LEDs before sleeping
  
// Check Battery before sleeping
float batV = getBatteryVoltage();
bool lowBattery = (batV < LOW_BAT_THRESHOLD_V);

digitalWrite(SERVO_EN, LOW); // Turn servo off the save battery
```
</div>

Now that the system is going to power down, as shown in [Listing 14](#goingToSleep), it is vital to setup a way for it to wake back up, hence the double tap interrupt must be enabled on the ADXL. The GPIO pin connected to this interrupt is then set as wake up GPIO pin, so whenever it is set to high the system wakes up. Hence the system must also disable single tap interrupt to prevent waking up on single taps. The interrupt flags must also be cleared. 
Then depending on if battery is low the systems sets up another way of waking back up, using a timer to wake up in regular intervals (60s by default) to flash the red LED to alert user of low battery. After which it again goes back to sleep to save battery.

<div id="goingToSleep">

*Listing 14: Going to sleep*
```cpp
// Prepare ADXL Wakeup
adxl.singleTapINT(0); // No need for single tap interrupt any,ore
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
</div>

As there are two methods of waking up, each with different operations to be performed on wakeup, the wakeup reason is checked and system reacts accordingly as shown in the function in [Listing 15](#handleWakeup)

<div id="handleWakeup">

*Listing 15: Handle Wakeup*
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
</div>

This function must be called near the start of the setup() function (right after Serial setup) to save as much power as possible as previously stated in [Section 5.5.1](#551-system-initialization). The reason for it being in setup() is that after deep sleep, the ESP32-C3 does a full reset, hence setup() is called again.

As the sytem is in deep sleep most of the time, when an ESP32-C is woken up from deep sleep mode, it goes through setup again, and must recall its memory to restore the pattern of the user. To recall these values NVS memory of the controller is used as explained in the next section.

#### 5.5.6 NVS Memory Handling
To save the knock pattern even after power off, the NVS memory of ESP32-C3 is used. This is a non-volatile memory built into the ESP32-C3, which can be used to store small amounts of data.
To save the pattern length and intervals, the function from [Listing 16](#loadPattern) was implemented.

<div id="loadPattern">

*Listing 16: Loading pattern intervals and length from the non-volatile storage*
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
</div>

As NVS memory works with key-value pairs, first the count of intervals is stored using key "count", then each interval is stored using individual keys "i0", "i1", "i2" ... for each interval. Finally the communication is ended to save power.
To load the pattern back, a similar approach is taken, reading the count first, then reading each interval using the same keys. Just instead of put functions, get functions are used. The function can be seen in the file usingNVS.cpp.

For running all these functions till now many smaller helper functions have been created to efficienctly do the redundant tasks. 

#### 5.5.7 Helper Functions
All of the functions above user some helper function to make the code more modular and easier to read. Some of these functions include:
- led_ryg(int r, int y, int g): To set the red, yellow and green LED states
- flashGreenTick(): To flash the green LED quickly to indicate a knock was recorded
- goodBeep() and badBeep(): To play a good or bad beep sound using the buzzer
- unlockBox() and lockBox(): To unlock and lock the servo motor


<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->


### 5.6 Housing Prototype <!-- Whatever modifications we made -->

### 5.7 Bill of Materials

<div id="tab:BOM-E">

*Table X: Electrical Bill of Materials*
| Item      | Schematic Ref             | Qty | Component                       | Part Number             | Manufacturer          | Vendor | Price/Unit[€]| Price [€] |
| --------- | ------------------------- | --- | ------------------------------- | ----------------------- | --------------------- | ------ | ------------ | --------- |
| 1         | U1                        | 1   | Capacitive Accelerometer        | ADXL345BCCZ-RL7         | Analog Devices        | Mouser | 5.65         | 5.65      |
| 2         | –                         | 1   | Servo Motor                     | SG90                    | Soldered              | HSRW   | 5.07         | 5.07      |
| 3         | Q1                        | 1   | Bipolar NPN Transistor          | BC547B                  | CDIL                  | HSRW   | 0.04         | 0.04      |
| 4         | Q2                        | 1   | P-channel MOSFET                | IRLML6402TRPBF          | Infineon Technologies | Mouser | 0.35         | 0.35      |
| 5         | IC2                       | 1   | ESP32 Microcontroller           | ESP32-C3-WROOM-02-N4    | Espressif Systems     | Mouser | 3.12         | 3.12      |
| 6         | D5                        | 1   | Red LED                         | DLE3MMR                 | Hottech               | HSRW   | 0.06         | 0.06      |
| 7         | D6                        | 1   | Yellow LED                      | DLE3MMY                 | Hottech               | HSRW   | 0.06         | 0.06      |
| 8         | D7                        | 1   | Green LED                       | DLE3MMG                 | Hottech               | HSRW   | 0.06         | 0.06      |
| 9         | LS1                       | 1   | Buzzer                          | PKM22EPPH4001-B0        | Murata Electronics    | Mouser | 0.48         | 0.48      |
| 10        | S1, S2                    | 2   | Push Button                     | TS02-66-60-BK-260-LCR-D | Samesky               | Mouser | 0.09         | 0.18      |
| 11        | IC1                       | 1   | 3.3 V Voltage Regulator         | LM2575-3.3WT            | Microchip Technology  | Mouser | 1.48         | 1.48      |
| 12        | D1, D2                    | 2   | TVS Diode                       | 1N5908                  | STMicroelectronics    | HSRW   | 0.66         | 1.32      |
| 13        | D3, D4                    | 2   | Schottky Diode                  | 1N5822                  | MIC Electronics       | HSRW   | 0.15         | 0.30      |
| 14        | F1, F2                    | 2   | Resettable Fuse                 | PFRA110                 | Schurter              | HSRW   | 0.28         | 0.56      |
| 15        | –                         | 1   | Battery Holder                  | 2477                    | Keystone Electronics  | Mouser | 1.87         | 1.87      |
| 16        | –                         | 4   | AA Battery                      | –                       | –                     | HSRW   | 0.30         | 1.20      |
| 17        | L1                        | 1   | 330 µH Inductor                 | RFC0810B-334KE          | Coilcraft             | Mouser | 1.26         | 1.26      |
| 18        | C1, C4, C5, C10, C11, C12 | 6   | 0.1 µF Ceramic Capacitor (0805) | B37873U5101S            | EPCOS                 | HSRW   | 0.11         | 0.66      |
| 19        | C2                        | 1   | 100 µF Electrolytic Capacitor   | EEU-FC1C101H            | Panasonic             | HSRW   | 0.14         | 0.14      |
| 20        | C3                        | 1   | 1 µF Electrolytic Capacitor     | RA1/25-R                | Jameco                | HSRW   | 0.02         | 0.02      |
| 21        | C6, C8, C9                | 3   | 10 µF Electrolytic Capacitor    | EEU-FR1H100             | Panasonic             | HSRW   | 0.11         | 0.33      |
| 22        | C7                        | 1   | 330 µF Electrolytic Capacitor   | EEU-FR1E331             | Panasonic             | HSRW   | 0.26         | 0.26      |
| 23        | J1                        | 1   | Male 2-Pin Header               | –                       | –                     | HSRW   | 0.08         | 0.08      |
| 24        | J2                        | 1   | Female 2-Pin Header             | –                       | –                     | HSRW   | 0.10         | 0.10      |
| 25        | J3                        | 1   | Male JST 2-Pin Header           | –                       | –                     | HSRW   | 0.10         | 0.10      |
| 26        | J4                        | 1   | Micro USB B                     | USB3145-30-1-A          | GCT                   | Mouser | 0.66         | 0.66      |
| 27        | J5                        | 1   | Male JST 3-Pin Header           | –                       | –                     | HSRW   | 0.12         | 0.12      |
| 28        | R1, R4, R5, R7            | 4   | 10 kΩ Resistor                  | RC1206FR-0710KL         | YAGEO                 | HSRW   | 0.09         | 0.36      |
| 29        | R2                        | 1   | 6.8 kΩ Resistor                 | RC1206FR-076K8L         | YAGEO                 | HSRW   | 0.09         | 0.09      |
| 30        | R3, R6                    | 2   | 4.7 kΩ Resistor                 | RC1206FR-074K7L         | YAGEO                 | HSRW   | 0.09         | 0.18      |
| 31        | R8                        | 1   | 100 Ω Resistor                  | RC1206FR-07100RL        | YAGEO                 | HSRW   | 0.09         | 0.09      |
| 32        | R9                        | 1   | 100 kΩ Resistor                 | RC1206FR-07100KL        | YAGEO                 | HSRW   | 0.09         | 0.09      |
| 33        | R10, R11, R12             | 3   | 27 Ω Resistor                   | RC1206FR-0727RL         | YAGEO                 | HSRW   | 0.09         | 0.27      |
| **Total** |                           |     |                                 |                         |                       |        |              | **26.61** |
</div>

<div id="tab:BOM-M">

*Table X: Mechanical Bill of Materials*
| Item Number | Qty | Component           | Price / Unit | Price     |
| ----------- | --- | ------------------- | ------------ | --------- |
| 35          | 7   | M2×6 Screw          | 0.11         | 0.77      |
| 36          | 2   | M2×20 Screw         | 0.14         | 0.28      |
| 37          | 1   | M3×15 Plastic Screw | 0.08         | 0.08      |
| 38          | 7   | M3 Plastic Washer   | 0.01         | 0.07      |
| 39          | 1   | M3 Hex Nut          | 0.07         | 0.07      |
| 40          | 1   | 3D Printed Housing  | 13.95        | 13.95     |
| **Total**   |     |                     |              | **15.22** |
</div>

### 5.8 Post-Implementation Verification Results 
#### 5.8.1 Module Performace  <!-- How is each circuit performing? -->
#### 5.8.2 System Integration Performance <!-- How is the entire system performing -->
#### 5.8.3 Power Consumption <!-- How much power is being consumed? -->

### 5.9 Validation Results 
#### 5.9.1 Product Performance <!-- How well does the system perform when completely assembled? -->
#### 5.9.2 User Feedback <!-- what did people think? -->
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 6	Discussion
Here you should discuss your results
### 6.1 Product Evaluation
A comparison of the results we had with existing products or what we saw in literature

### 6.2 Product Limitations
What are the main limitations we realised after extensive testing

- not rechargable
- very low IP rating
- 

### 6.3 Product Significance
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 7	Conclusion
You might want to discuss possible future work here
### 8.1 Future Improvements
Doing this project, opened more aspects which can be worked on in future when reiterating the project. These include:
- Rechargeability: Implementing a recharging circuit and using rechargable batteries
- Redundant sensors: Use Piezo with ADXL to more effectively detect a knock
- Improved Ergonomics: Using a material that does not hurt to knock or

## 8	References

* [1]: Instructables. (2022, May 8). Secret knock detecting door lock. Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Secret-Knock-Detecting-Door-Lock/ 
* [2]: Dodhia, V. (2021, June 20). Arduino secret knock pattern door lock. Viral Science. Retrieved November 20, 2025, from https://www.viralsciencecreativity.com/post/arduino-secret-knock-pattern-door-lock
* [3]: Instructables. (2017, October 21). Knock Box (it Opens When You Knock on It!). Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Knock-box-it-opens-when-you-knock-on-it/
* [4]: Burgognoni, E. (2025, August 28). Comparing MEMS and IEPE accelerometers for structural vibration behavior testing. Data Acquisition | Test and Measurement Solutions. Retrieved October 30, 2025, from https://dewesoft.com/blog/comparing-mems-and-iepe-accelerometers
* [5]: Analog Devices. (n.d.). ADXL345 datasheet. Analog Devices. Retrieved November 20, 2025, from https://www.analog.com/en/products/adxl345.html
* [6]: Espressif Systems. (2021). ESP32-C3 Series datasheet. In Espressif. https://www.espressif.com/documentation/esp32-c3_datasheet_en.pdf

## 9	Appendices

