<!----------------------------------------------------------------
<div id="logo" align="center">
<figure>
  <img src="/resources/images/Logo.png" alt="Logo" width="400">
  <figcaption align="center"><b>Figure 1:</b> Knock Lock Logo</figcaption>
</figure>
</div>

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
  <figcaption align="center"><b>Figure 5.8:</b> Final PCB without Components</figcaption>
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

<div align="center">
  <table border="0" style="width: 100%; border: none;">
    <tr>
      <td align="left" style="vertical-align: middle; width: auto; padding: 10px 0;">
        by: <a href="https://www.linkedin.com/in/abhinav-kothari-2ak/">Abhinav Kothari</a> (33349) and <a href="https://jcchincheong-bb.github.io/">Justin Chin Cheong</a> (34140)
        <br><br>
        <strong>Faculty of Technology and Bionics</strong>
        <br><br>
        <em><strong>Rhine-Waal University of Applied Sciences</strong></em>
        <br><br>
        Date: 18 January 2026
      </td>
      <td align="right" style="vertical-align: middle; width: 1%; white-space: nowrap; padding-left: 20px;">
        <img src="/resources/images/hsrw.png" height="100" alt="HSRW Logo" style="display: block;">
      </td>
    </tr>
  </table>
  </figure>
</div>

<!-- by: [Abhinav Kothari](https://www.linkedin.com/in/abhinav-kothari-2ak/) (33349) and [Justin Chin Cheong](https://jcchincheong-bb.github.io/) (34140) -->

<!-- **Faculty of Technology and Bionics** -->

<!-- ***Rhine-Waal University of Applied Sciences*** -->

<!-- Date: 18 January 2022  -->

----

## Abstract

The Knock Lock project presents the design, implementation, and evaluation of a novel access control system that unlocks a small lock box through the recognition a user-defined knocking pattern. Motivated by the limitations of conventional key-based and electronic locking mechanisms, the system aims to provide a fun and intuitive alternative that does not rely on physical tokens or wireless credentials. Unlike most existing knock-based systems that use piezoelectric sensors, this project explores the use of a MEMS accelerometer for knock detection, enabling improved reliability, flexibility and multi-axis measurement.

Following a V-model design methodology, the system was developed from defined requirements through hardware, software, and housing design, to full system integration and testing. The final prototype consists of an ESP32-based controller, an accelerometer sensor, a servo-driven locking mechanism, a custom PCB, a user interface employing LEDs and a buzzer and a custom 3D printed housing. Verification and validation tests demonstrate reliable knock pattern recognition, successful locking and unlocking behaviour, effective power management with sleep modes, and positive user acceptance.

The results confirm the feasibility of accelerometer-based knock recognition for access control applications and highlight the potential for further development toward full-scale door locking systems and enhanced security features.

## Table of Contents

[[_TOC_]]
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 1 Introduction 
### 1.1 Rationale
As children, many of us might have invented secret knocks that we used to identify ourselves to our friends or siblings. But, what if those special codes could actually unlock the door itself? As adults, how many times have we forgotten your keys and wished you could just knock in a certain way to unlock the door? 

There are many different types of security systems on the market that use systems ranging from combinations to NFC, but there are no commercial products of this kind that unlock by recognising a specific knocking pattern. As such, the aim of The Knock Lock project is to design and assemble a system that unlocks a door by recognising a specific knocking pattern. As a proof of concept, the system is designed as a small lock box as shown in [Figure 1.1](#preliminary-sketch) with the hope of extending the idea to work on a full door in the future.

<div id="preliminary-sketch" align="center">
<figure>
  <img src="/resources/images/preliminarySketch.png" alt="preliminary-sketch" width="400">
  <figcaption align="center"><b>Figure 1.1:</b> Preliminary Sketch of the Knock Lock</figcaption>
</figure>
</div>

### 1.2	Outline
This report documents the complete development and verification process of the Knock Lock project from conception to assembly to testing. 

[Chapter 1](#1-introduction) introduces the problem with current security systems which the Knock Lock project is trying to solve as well as the project team and their contributions to the project's development. However, before the actual development can be explained, a review of any existing solutions must be done to understand how others approached the problem as discussed in [Chapter 2](#2literature-review). Further, a number of key concepts such as accelerometers and servo motors are discussed in [Chapter 3](#3theory) to establish a theoretical foundation for the project's design. 

In [Chapter 4](#4methodology-and-design), the presentation of the actual development process begins with the definition of the V-model design flow ([4.1](#41-design-approach)) and system requirements ([4.2](#42-system-requirements)). The system is then designed at the highest level with the system architecture ([4.3](#43-system-architecture)) before going into the details of the intended hardware ([4.4](#44hardware-design)), software ([4.5](#45-software-design)) and housing design ([4.6](#46-housing-design)). In keeping with the V-model, verification methods are defined for both before ([4.7](#47-pre-implementation-verification-methods)) and after ([4.8](#48-post-implementation-verification-methods)) implementation. Validation ([4.9](#49-validation-methods)) of the system is also discussed and how the system could be tested against the needs of the user.

After defining the intended design and test specifications, the actual implementation, results and issues are explained in [Chapter 5](#5results). Here the results of prototyping ([5.1](#51-pre-implementation-verification-results)) are treated and their impact on the components used ([5.2](#52-component-selection)) and PCB design ([5.3](#53-pcb-design)) are explored. The process of actually assembling the PCB ([5.4](#54-pcb-assembly)) and developing the software ([5.5](#55-software-implementation)) is described as well as the issues encountered. The construction of the housing ([5.6](#56-housing-prototype)) and the complete list of materials ([5.7](#57-bill-of-materials)) used is also illustrated. Finally, the system's verification ([5.8](#58-post-implementation-verification-results)) and validation ([5.9](#59-validation-results)) results are presented.

Finally, [Chapter 6](#6discussion) discusses how the results of the Knock Lock compares to other projects ([6.1](#61-product-evaluation)) and expounds upon the limitations([6.2](#62-product-limitations)) and significance ([6.3](#63-product-significance)) of the product's performance. [Chapter 7](#7conclusion) concludes the report with a summary of the development journey and outlines some potential future work ([7.1](#71-future-improvements)) for the project.

### 1.3 Project Team
The project team consists of two Mechatronics Engineering Students whose responsibilities in the project were divided
as follows:
- Abhinav Kothari (33349):
  - Design of power regulation, sensor system and human machine interface circuits
  - Development of complete program software
  - Design of preliminary PCB layout
  - Design and refinement of final prototype housing
- Justin Julius Chin Cheong (34140): 
  - Component selection
  - Design of power protection, programming interface and lock actuator circuits
  - Design and refinement of final PCB layout
  - Design of preliminary prototype housing
- Both: 
  - Soldering and assembly
  - Verification of components and system integration
  - Validation of functionality and user acceptance

With regard to writing of this report, the following illustrates the contributions of each team member:
- Abhinav Kothari (33349): 
  - Chapter 2
  - Chapter 4: 4.2, 4.5, 4.6
  - Chapter 5: 5.4, 5.5, 5.6, 5.9
  - Chapter 6
  - Chapter 7
- Justin Julius Chin Cheong (34140): 
  - Chapter 1
  - Chapter 3
  - Chapter 4: 4.1, 4.2, 4.3, 4.4, 4.7, 4.8, 4.9
  - Chapter 5: 5.1, 5.2, 5.3, 5.7, 5.8
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 2	Literature review
In pursuit of unique and easy methods for users to unlock systems, many developments have been made. These methods for unlocking vary from NFCs to Biometric. Knock detection is also a method used in some small scale (non-commercial) projects, which allows for unlocking even without carrying tangible assets (For example a card for NFC unlocking). This section covers the existing projects implementing knock detection, and compares them to a new possible approach which has not been so commonly used in these systems.

### 2.1 Related Work
Reviewing hobbyist and academic projects, gives us an overview of the common techniques used to accomplish this task. Notable implementations [[1,2,3](#9references)] show reliable interpretation of knocks using a piezoelectric elements. However all had some limitations shown from the demonstration. The knock detection was only on a surface parallel to the piezo element. They all had also relatively hard knocks for detection. Some projects pointed out that increasing precision also increases the number of false positives. Even after more research, no projects using accelerometers were found. From reviewing the projects further, it can also been seen that none of the systems implemented a sleep mode for a more power efficient approach.

For processing most the projects implemented and Arduino Deumilanove or an Arduino Nano, and used gear reduction motors, solenoids or servo for locking/unlocking mechanism. Other than the controller used, it is essential to choose the right sensor for knock detection.

### 2.2 Technical Comparison of Sensors
As noted from the previous section, no accelerometers were used in the project, which particularly interesting considering, they are commonly used in high-end consumer electronics such as smartphones for detecting back taps, which work reliably. Hence this section compares the three sensor technologies (Piezoelectric, capacitive accelerometers, vibration sensor) to better understand the situation.

While piezoelectric transducers offer a good signal to noise ratio, they also act as high pass filters. This property provides them with a higher sensitivity for higher frequency vibrations, but hence not the ideal solution for lower frequency vibrations, which is more similar to human knocks [[4](#9references)]. While this blog [[4](#9references)], compares accelerometers with professional piezoelectric sensors, which are much more sensitive than the piezoelectric transducers used in other projects, the same fundamental limitation applies to them as well. Especially considering, vibrations when traveling through various materials may lose high frequency energy relatively quickly, depending on the material property and thickness, which may make it even harder to detect. On the other hand accelerometers allow sensing of flat responses (0Hz) and hence have good sensitivity for even lower frequencies [[4](#9references)]. Vibration sensors allow for detecting only above a specified frequency, depending on its calibration. Moreover, piezoelectric transducers are analog passive devices, hence have quite less power consumption, however also implies they must be always awake to read. 

Vibration sensor have limited customisability due to their digital nature. They can either detect a knock or not, which can potentially cause problems differentiating general environmental vibrations from intentional knocks.

Accelerometers generally have chips to process and amplify signal which can communicate the information using I2C or SPI communication instead of piezoelectric transducers, which as stated earlier are analog or vibration sensor which are digital. This implies, theoretically, an accelerometer should allow for much more customisability via software, as the chips also have many in-built interrupts, which can help make the system more efficient. Moreover, the chips are able to process readings quite well to reduce noise. An accelerometer, being 3-axis, may also allow detection direction of knock which could be helpful in certain scenarios.

A summary of all the differences between piezos, MEMS accelerometers and vibration sensor is shown in [Table 2.1](#PiezoVsAccelVsVibration)

<div id="PiezoVsAccelVsVibration" >
</div>

*Table 2.1: Comparison of Piezo, Vibration Sensors and MEMS Accelerometer*

| Feature                   | Piezoelectric Buzzer              | Digital Vibration Sensor              | MEMS Accelerometer (Capacitive)           |
| :---                      | :---                              | :---                                  | :---                                      |
| **Sensing Principle**     | Piezoelectric (Acoustic/Resonant) | Spring-and-Ball (Mechanical Switch)   | **Capacitive (Proof-Mass Displacement)**  |
| **Output Type**           | Raw Analog Voltage (Uncalibrated) | Digital Binary (HIGH/LOW)             | **Digital Data (I2C/SPI)**              |
| **Detection Axis**        | Single Axis (Directional)         | Omni-directional (Uncalibrated)       | **3-Axis (X, Y, Z) Sensing**              |
| **Customizability**       | **Low:** Fixed by hardware/surface| **None:** On/Off trigger only         | **High:** Software-defined thresholds     |
| **Power Management**      | Requires constant CPU sampling    | Interrupt-capable                     | **Integrated Interrupts (Deep Sleep)**    |
| **Primary Limitation**    | High-frequency bias (Acoustic)    | Lack of pattern sensitivity           | Higher initial code complexity            |
| **Cost**                  | Extremely Low                     | Low                                   | Moderate                                  |

These sensors are then compared in [Section 4.4.2](#442-sensor-sub-system) and results can be found in [Section 5.1.1](#511-concept-feasibility)

<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->

## 3	Theory
Building upon the sensor characteristics identified in [Section 2](#2-literature-review), this sections outlines the fundamental theoretical concepts required to implement the system effectively. These concepts relate to the different aspects of the system's circuit design and are required for fully understanding the design created. 

### 3.1 Accelerometers
Capacitive accelerometers are sensors used to measure acceleration forces by detecting changes in capacitance. They typically consist of a small movable mass suspended between fixed electrodes as seen in [Figure 3.1](#imu)[[6](#9references)]. When acceleration is applied, the mass shifts, altering the distance between the electrodes and therefore changing the capacitance. This change is proportional to the applied acceleration and is converted into an electrical signal.

<div id="imu" align="center">
<figure>
  <img src="/resources/images/MEMS.jpg" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.1:</b> Diagram of Capacitive Accelerometer Working Principle</figcaption>
</figure>
</div>

The Knock Lock project uses an accelerometer as the main sensor for knock detection. Initial testing revealed that these accelerometers are very well suited for detecting knocks (See [Section 5.1.1](#511-concept-feasibility)) compared to piezoelectric devices, which use the piezoelectric effect to convert mechanical vibrations into voltage to be detected. The sensor's role in the design is discussed in [Section 4.4.2](#442-sensor-sub-system).

Most modern capacitive accelerometers are sold as integrated circuits (ICs) with three accelerometers (one for each axis) as well as signal conditioning electronics and an I2C interface [[7](#9references)].

### 3.2 I2C
Since most accelerometers use I2C to communicate, it is necessary to include I2C interface and connections in the circuit design as discussed in [Section 4.4.4](#444-controller-sub-system).

I2C is a synchronous, serial communication protocol commonly used for short-distance communication between integrated circuits [[7](#9references)]. It uses two shared lines: a serial data line (SDA) and a serial clock line (SCL). Devices on the bus are identified by unique addresses and operate in a master–slave configuration. I2C allows multiple devices to communicate using the same bus, reducing wiring complexity. [Figure 3.2](#i2c) taken from [[7](#9references)] shows how a typical I2C device connects with a microcontroller.

<div id="i2c" align="center">
<figure>
  <img src="/resources/images/i2c_theory_scherz.PNG" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.2:</b> Diagram of I2C Connection</figcaption>
</figure>
</div>

### 3.3 High-Side Driver
To perform the actual locking and unlocking after the system recognises knocks with the [accelerometer](#31-accelerometers), the system needs a lock actuator. To interface this actuator, a high side driver is used as described in [Section 4.4.3](#443-lock-actuator-sub-system). It is essentially used to cut power to the actuator in sleep mode to reduce power consumption.

High-side drivers are electronic circuits used to control a load by switching the high voltage side of the load. They are typically implemented using transistors or integrated driver ICs and allow a microcontroller to safely control high-voltage or high-current loads such as motors, relays, or solenoids [[8](#9references)]. [Figure 3.3](#highDriver) taken from [[8](#9references)] shows how a typical high side driver configuration for use with a microcontroller. The microcontroller controls the base of the transistor. When it is set to low, the transistor does not conduct and the gate of the MOSFET is pulled up. This means the gate-source voltage of the MOSFET is 0V and thus, it does not conduct and the motor is cut off from power. When the base of the transistor is set high, the opposite occurs and the gate of the MOSFET is pulled down to ground causing the MOSFET to trigger and connect the motor to power.

<div id="highDriver" align="center">
<figure>
  <img src="/resources/images/driver_theory.png" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.3:</b> Diagram of High Side Driver Circuit</figcaption>
</figure>
</div>

### 3.4 Servo Motor
With the high side driver as the interface, the actual lock actuator is a servo motor as described in [Section 4.4.3](#443-lock-actuator-sub-system).

Servo motors are electromechanical devices used for precise control of angular position, speed, and torque. A typical servo motor consists of a DC motor, a gearbox, a position sensor (usually a potentiometer), and a control circuit. The motor position is controlled using a pulse-width modulation (PWM) signal, where the pulse width determines the desired angle as shown in [Figure 3.4](#servo)[[7](#9references)]. 

<div id="servo" align="center">
<figure>
  <img src="/resources/images/servo_theory_scherz.PNG" alt="IMU" width="400">
  <figcaption align="center"><b>Figure 3.4:</b> Diagram of Servo Motor Working Principle</figcaption>
</figure>
</div>
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->

## 4	Methodology and Design
With the theoretical foundation established, the actual development process can be outlined, beginning with the [design approach](#41-design-approach).

### 4.1 Design Approach <!-- V-model-->
Due to the high complexity of the project, the project team decided to use the V-model design flow. With this approach of continuous verification, the project team aimed to reduce risk by finding issues and their solutions early.

### 4.2 System Requirements <!-- Requirements, not specs -->
To fully implement the system, a number of requirements related to function, technology and project management have been outlined. 

#### 4.2.1 Functional Requirements

For Knock Knock Lock Box to be a satisfiable product, the following functional requirements must be implemented:

- It unlocks within 1-2 seconds when a specific knocking pattern is used on the surface of the box
- It indicates turns a green LED on and simultaneously plays a simple beep to indicate that the box has been unlocked
- It rejects pattern if incorrect within 1-2 seconds after knocking has ended
- It turns a red LED on and simultaneously plays a simple alarm to indicate that the knocking pattern was false or unrecognised
- It alerts when the battery level drops below a certain level by flashing a red LED, even in power saving mode
- It only powers on after some initial knock to wake up the system, on wake it shows an yellow LED
- If no knocks detected for 60 seconds, it goes back to power saving mode
- It has provision to use a additional port as an alternative power source in case battery dies out, with no prospect to upload firmware through it
- It uses some actuator for unlocking and locking 
- It has a programming mode where the user sets the knock for the system to recognise, mode can only be entered when the box is unlocked 

#### 4.2.2 Technical Requirements

For the Knock Knock Lock Box to operate and perform its functions, the following technical requirements must be implemented:

- The sensor system can detect knock amplitudes and output a measurable reading to the microcontroller
- There are provisions to protect the sensor and microcontroller from voltage spikes that might occur from the power supply
- The microcontroller software can detect up to 30 knocks with consecutive knocks being less than 2s apart and match the timings to the predefined knock pattern with a set tolerance of acceptance
- The power supply is a battery with a working voltage of 3.2V to 6.5V
- The enclosure can protect the system within a typical indoor environment (IP 31)
- The provision to set microcontroller to low power mode and wake it back up
- Should function at temperatures ranging 0-40°C and humidity 10-90%

#### 4.2.3 Project Requirements

For the Knock Knock Lock Box project to produce a functional product upon close out, the following project requirements must be met:

- the budget is 25€ not including the PCB or mechanical components
- the project workload is estimated at 240h
- all components used for the project must be ordered from mouser.de or taken from the in-house supply  at HSRW
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
  <img src="/resources/images/KnockLock_Schematic.png" alt="schematic" width="1100">
  <figcaption align="center"><b>Figure 4.2:</b> Full Schematic of the System</figcaption>
</figure>
</div>

The following sections discuss the design of the schematic as well as the specifications of the most important components for each sub-system. 

#### 4.4.2 Sensor Sub-System
The first of the sub-systems is the sensor sub-system as shown in [Figure 4.3](#sensor-sch). 

<div id="sensor-sch" align="center">
<figure>
  <img src="/resources/images/sensor_sch.PNG" alt="sensor-sch" width="400">
  <figcaption align="center"><b>Figure 4.3:</b> Schematic of the Sensor Sub-System</figcaption>
</figure>
</div>

As mentioned in the [Section 2 Literature Review](#2literature-review), most existing projects implemented a piezo element over an accelerometer or a vibration sensor to detect knocks. However, [Table 2.1](#PiezoVsAccelVsVibration) also revealed the potential efficacy of using an accelerometer instead of a piezo. Thus, to identify an appropriate sensor for the most accurate and reliable knock detection, a simple comparative experiment must be conducted. A piezo disc (DAOKAI JA-DA-036 27mm) wass tested against an accelerometer development module (JOY-IT SEN-MMA8452Q) which was readily available in the lab. Note the vibration sensor is excluded from this comparative testing as with its preliminary testing it was revealed that it has significant reliability issues. The sensor lacked the necessary sensitivity control, often oscillating between over-sensitivity (detecting ghost knocks) and under-sensitivity.

The sensors are tested in two different scenarios: a thin plastic lid and on a wooden chair as seen in Figures [4.4](#sensorTestPlastic) and [4.5](#sensorTestWood) respectively. This allowed for understanding how each sensor performed on materials of very different densities and stiffness's. In each test, the sensors are attached to the surface and connected to an Arduino UNO for processing the output. Knocks are then applied to the opposite side of the material and the readings are recorded and compared.

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

The sensors are compared based on two criteria. 
1. Reliability of detecting knocks of different strengths in each setup
2. Reliability of detecting knocks of different speeds in each setup

The results of this comparative test and the final sensor decision are presented in [Section 5.2.1](#521-sensor-selection). 

The general expectation was that both sensors would exhibit similar accuracies, with accelerometer being only slightly better when it came to detection through a thicker surface, and since the piezo is significantly cheaper and consumes less current, the piezo would be the ideal sensor.

#### 4.4.3 Lock Actuator Sub-System
On the other end of the system is the locking mechanism which is accomplished through a lock actuator. The circuit to interface this actuator is shown in [Figure 4.6](#lock-actuator-sch). 

<div id="lock-actuator-sch" align="center">
<figure>
  <img src="/resources/images/motor-control_sch.PNG" alt="lock-actuator-sch" width="600">
  <figcaption align="center"><b>Figure 4.6:</b> Schematic of the Lock Actuator Sub-System</figcaption>
</figure>
</div>

The initial concept of the product as shown in [Figure 1.1](#preliminary-sketch) envisioned the use of a solenoid actuator to work similarly to the bolt in a door. However, another component which could accomplish the locking while also being cheaper and using less power is a simple servo motor. As such, a number of options for both were found on Mouser for consideration and compared in [Table 4.1](#tab:servo-comp). Clearly, the power requirement for the solenoid is much higher than the that of the servo. This would mean either a boost converter or some other additional voltage regulation would be needed to power the solenoid. On top of that, the solenoids are more expensive per unit. As such, the project team opted to use a servo motor and chose the SER0050 since it is a higher torque than the SER0049. 

<div id="tab:servo-comp">

*Table 4.1: Comparison of Solenoids and Servos Available on Mouser*
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

The microcontroller (MCU) interfaces the sensor, the lock actuator and the human machine interface (HMI). It handles all the processing and runs the program developed in [Section 5.5](#55-software-implementation). The complete pin mapping of the MCU is shown in [Table 4.2](#tab:controller-pin-mapping). 

<div id="tab:controller-pin-mapping">

*Table 4.2: Pin Mapping of Microcontroller*
| Pin   | Name  | Type / Label     | Description / Connection                                                   |
|------:|-------|------------------|----------------------------------------------------------------------------|
| 1     | 3V3   | Power            | +3.3V Supply from Regulator                                                |
| 2     | EN    | Reset            | Enable / Reset connecting to Reset Button                                  |
| 3     | IO4   | WAKE_INT         | Wake Interrupt for Sensor                                                  |
| 4     | IO5   | SCL              | SCL (I2C Clock) with 4.7kΩ Pull-up                                         |
| 5     | IO6   | SDA              | SDA (I2C Data) with 4.7kΩ Pull-up                                          |
| 6     | IO7   | PROG             | Input to trigger programming mode. Pulled up.                              |
| 7     | IO8   | -                | Strapping pin pulled up for easy booting into UART download mode           |
| 8     | IO9   | BOOT             | Strapping Pin connected to pin header for booting into UART download mode  |
| 9     | GND_1 | Ground           | Not Connected                                                              |
| 10    | IO10  | BUZZ             | Buzzer                                                                     |   
| 11    | RXD   | RX               | UART Receive                                                               |
| 12    | TXD   | TX               | UART Transmit                                                              |
| 13    | IO18  | RLED             | Red LED                                                                    |
| 14    | IO19  | YLED             | Yellow LED                                                                 |       
| 15    | IO3   | GLED             | Green LED                                                                  |
| 16    | IO2   | BAT_V            | Battery Voltage Monitoring                                                 |
| 17    | IO1   | CONTROL          | Control signal for Lock Actuator                                           |
| 18    | IO0   | SERVO            | Signal to cut-power to Lock Actuator                                       |
| 19–27 | GND   | Ground           | Main System Ground                                                         |
</div>

From [Table 4.2](#tab:controller-pin-mapping), it can be seen that the chosen MCU must have:
- at least 11 programmable GPIOs
- I2C communication
- at least 1 ADC GPIO 
- on-board UART interface 
- exposed enable and strapping pins

Additionally, the chosen MCU must large enough to easily solder onto a PCB. 

Given the ease in which it can be programmed via the Arduino IDE and it's high computation speed and robust features, the project team believed an MCU from the ESP32 line would best fit the specifications. On Mouser, a number of options that met the basic specifications were found as shown in [Table 4.3](#tab:esp32-comp). Ultimately, the decision to chose the ESP32-C3-WROOM-02-N4 [[9](#9references)] was because it was large and had pins exposed on the sides for easier assembly (unlike the 356-ESP32C6MINI1H8) and it was cheaper than the H4 while still meeting all the specifications. This chip also has a lower power consumption sleep mode which draws only 5uA, making it incredibly viable for a low power design.
<div id="tab:esp32-comp"> 

*Table 4.3: Comparison of ESP32 Chips Available on Mouser*
| Part Number           | Price [€] | Interfaces       | GPIO Count | ADC GPIOs | Size [mm]   | Package Type                                    |
| --------------------- | --------- | ---------------- | ---------- | --------- | ----------- | ----------------------------------------------- |
| ESP32-C3-WROOM-02-N4  | 3.12      | I2C, SPI, UART   | 15         | 4         | 18 × 25.5   | Castellated module with exposed pins            | 
| ESP32-C3-WROOM-02-H4  | 3.36      | I2C, SPI, UART   | 22         | 4         | 18 × 25.5   | Castellated module with exposed pins            | 
| 356-ESP32C6MINI1H8    | 4.69      | I2C, SPI, UART   | 22         | 6         | 13.2 × 16.6 | Castellated mini module with pins underneath    |
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

Finally, the HMI includes a simple button which can be used to enter the programming mode of the product. A summary of all the actions the HMI should perform is given in [Table 4.4](#tab:hmi)

<div id="tab:hmi">

*Table 4.4: HMI Actions*
| Mode        | User Input                 | Purpose / Action            | System Output                                         |
| ----------- | -------------------------- | --------------------------- | ----------------------------------------------------- |
| Locked      | Idle                       | Waiting for input           | Yellow LED on                                         |
| Locked      | Any knock                  | Knock registered            | Green LED blinks once                                 |
| Locked      | Knocking correct pattern   | Successfully unlocking      | Green LED on, pleasant buzzer sound, actuator unlocks |
| Locked      | Knocking incorrect pattern | Unsuccessfully unlocking    | Red LED blinks once, unpleasant buzzer sound          |
| Locked      | Pressing button            | Cannot program while locked | Red LED blinks once, unpleasant buzzer sound          |
| Locked      | Wait 60 s                  | Go to sleep                 | All LEDs turn off                                     |
| Unlocked    | Idle                       | Waiting for input           | Green LED on                                          |
| Unlocked    | Pressing button            | Entering programming mode   | All LEDs blink once                                   |
| Unlocked    | Knocking twice             | Re-locking                  | Yellow LED on, actuator locks                         |
| Programming | Idle                       | Waiting for input           | Yellow LED on                                         |
| Programming | Any knock                  | Knock registered            | Green LED blinks once                                 |
| Programming | Knock new pattern          | Programming new pattern     | Buzzer plays back pattern, green LED blinks pattern   |
| Programming | Wait 5 s                   | Programming mode timeout    | Red LED blinks once, unpleasant buzzer sound          |
| Sleep       | Idle                       | Waiting for input           | All LEDs off                                          |
| Sleep       | Knock twice                | Wake up                     | Yellow LED on                                         |
</div>

#### 4.4.7 Power Regulation Sub-System
Finally, the system cannot function without reliable power and as such a power regulation system has to be defined as shown in [Figure 4.10](#power-sch). 

<div id="power-sch" align="center">
<figure>
  <img src="/resources/images/power-regulation_sch.png" alt="power-sch" width="800">
  <figcaption align="center"><b>Figure 4.10:</b> Schematic of the Power Regulation Sub-System</figcaption>
</figure>
</div>

Since the [controller](#444-controller-sub-system) uses an ESP32 which requires 3.3V [[9](#9references)], a voltage regulator that outputs 3.3V is required. The most common and efficient means of accomplishing this is using a higher voltage supply and using regulator to step down the supply. For the purpose of this project, a switching buck converter was chosen instead of using a linear voltage regulator as they are higher efficiency and produce less heat. Mouser has a very large range of switching regulators, many of which meet these minimum specifications. Ultimately, the LM2575-3.3WT was chosen since it was rather cheap, has a maximum input voltage of 40V and typical efficiency of 75%. Additionally, the diode used in the regulation circuit also needs to have low forward voltage drop and low junction capacity so that it provides minimal impede the high-frequency switching.

The voltage regulation must also provide protection in addition to providing the right voltage level. The buck converter itself inherently provides over-voltage protection up to 40V. To implement reverse polarity protection, TVS diodes are used in combination with a fuse. The diode is connected across the junctions such that when a reversed voltage is connected, the diode shorts the external source and not the rest of the circuit. The fuses also provide over-current protection. To dimension the fuse, the specifications of the LM2575-3.3WT were considered. With a maximum output current of 1A, output voltage of 3.3V, efficiency of 75% and input voltage of 6V, the maximum current required by the regulator is around 0.733A. See [Appendix A](#appendix-a-circuit-dimensioning-calculations) for the calculations. Thus, the fuse should safely carry around 1A to account for fluctuations. As such, the PFRA110 was chosen as it has a hold current of 1.1A and a trip current of 2.2A. This fuse is also resettable so after current is cut-off, the fuse can cool down and reset. 

Another interesting aspect of the circuit is the inclusion of an alternative power connection. The battery terminal is meant to be the primary power source via 4S AA batteries and the micro USB port is for emergency powering when the battery dies and the box is locked. It also connects to the voltage regulator and has it's own protection fuse and diode.

Finally, the circuit contains a simple voltage divider that steps down the 5V supply line to less than 3.3V so that it can be read by the ADC on the microcontroller. The voltage at the ADC can then be calculated using a voltage divider ratio. 

#### 4.4.8 Component Specifications  <!-- Table of main components and their most important specs -->
Based on the circuit design and requirements described above, the specifications of the main components of the system are compiled in [Table 4.5](#tabSpecs)

<div id="tabSpecs">

*Table 4.5: List of Component Specifications*
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
<div id="sw-flow" align="center">
<figure>
  <img src="/resources/images/MainFlowchart.png" alt="sw-flow" width="400">
  <figcaption align="center"><b>Figure 4.11:</b> Programming Flowchart of Main System</figcaption>
</figure>
</div>

The flowchart in [Figure 4.11](#sw-flow) shows, how the overall full system must work. The system starts in locked state, where it continuously listens for knocks, unless its asleep, and records them. Once the knocks are recorded, they are checked against the target pattern, if they match, the system unlocks, else it stays locked. Knocking twice locks the box again. LEDs and Buzzer are used to give feedback to the user throughout the system flow.

Interrupts are used to wake the system up from sleep for again starting to read knocks as shown in [Figure 4.12](#sw-flow-isr). If the box is unlocked and the programming button is pressed, the system enters programming mode, where it records knocks to save a new pattern. Once the pattern is recorded, it is saved to NVS memory and the system goes back to main system as shown in [Figure 4.12](#sw-flow-isr).

<div id="sw-flow-isr" align="center">
<figure>
  <img src="/resources/images/ISR_Flowchart.png" alt="sw-flow" width="400">
  <figcaption align="center"><b>Figure 4.12:</b> Programming Flowchart of Interrupt Service Routines (ISRs)</figcaption>
</figure>
</div>


#### 4.5.2 Code Structure
For easy code understanding and better readability, a modular approach was taken. Splitting the code in different cpp files depending on the type of function. A config.h file also was created to storing all customisability settings. This file had only settings constants and no code or variables to prevent confusion for a user, and make it less error prone. The files structure to be followed is listed in [Table 4.6](#tab:sw-files).

<div style="text-align: left" id="tab:sw-files">

*Table 4.6: Software Files Structure*
| File Name (Header)                | Purpose                                                                                           |
|:------                            |:---                                                                                               |
|   batteryMonitoring               | Functions to monitor battery                                                                      |
|   config                          | File to store all setting constants, for easy editing of settings                                |
|   globalVariables                 | File storing all global variables, also explanations of some other important non global variables |
|   hardware                        | All pin, objects definition and hardware initialization and interrupt functions                   |
|   hmi                             | All human interface related functions, for controlling buzzer, LEDs and actuator                  |
|   KnockLock (ino)                 | Main code to run with setup and endless loop                                                      | 
|   patternRecognitionandRecording  | Core functions to process/record                                                                  |
|   sleepMode                       | Function related to sleep and wake up of controller                                               |
|   usingNVS                        | Functions related to saving and reading data from the non-volatile storage of the controller      |
</div>

Arduino IDE is used to program the controller in C++. This is because Arduino IDE provides access to wide range of libraries for various controllers with ease.

The final code implementation can be seen in [Section 5.5](#55-software-implementation).

### 4.6 Housing Design <!-- design for housing -->

<div id="housing-model"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/firstHousingConcept.PNG" height="300">
        <figcaption align="center"><b>(a):</b> Closed </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/firstHousingConcept_MountView.PNG" height="300">
        <figcaption align="center"><b>(b):</b> Open </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 4.13:</b>Preliminary 3D Model of Housing</figcaption>
  </figure>
</div>

For demonstration purposes, a box was modeled. The door must mount the PCB, this way the knocks can be reliably detected when door (typically primary place for knocking) is knocked. Many screw pillars have been used for a more firm housing and preventing the PCB from vibrating on its own by making it more rigidly connected with the door. An indent was made in the door to sit the servo motor, and a groove in the housing to slot in the servo to lock the box as shown in [Figure 4.13](#housing-model). Hole have been created in the door to show the LEDs for status of the box and holes on top of the buzzer to allow for better audibility.

The final housing can be seen in [Section 5.6](#56-housing-prototype).

### 4.7 Pre-Implementation Verification Methods <!-- How did we test during development? -->
Since this project follows the V-model design flow, the different layers and aspects of the design must be verified both before and after implementation. The following sections define the test specifications followed to continuously verify and prototype the layers of the design before the system was fully implemented. 

#### 4.7.1 Concept Feasibility Testing <!-- Testing the sensor to see if concept is feasible -->
Before implementation, the feasibility of the knock detection concept must be tested. If there is no reliable way of detecting knocks and most importantly detecting the knock pattern, then the project is a failure. Fortunately, the experimental setups described for sensor selection in [Section 4.4.2](#442-sensor-sub-system) can provide results that not only identify the most appropriate sensor for the project but also the entire concept feasibility. The results of this experiment are presented in [section 5.1.1](#511-concept-feasibility)

#### 4.7.2 Prototype System Testing <!-- Testing entire system in breadboard -->
After confirming feasibility, the system as described in [Section 4.4.1](#441-full-schematic-design) must also be verified. For ease of setup, development modules were selected to test the overall function of the system as well as initiate software development while the PCB was being manufactured. The following components were used:
- Microcontroller: ESP32-DevKitM-1
- HMI: red, yellow and green LEDs and a piezoelectric buzzer
- Sensor: JOY-IT SEN-MMA8452Q
- Lock Actuator: SG90 servo motor
- Misc: breadboard, resistors, jumper cables

The results of this test are presented in [Section 5.1.2](#512-prototype-system)

#### 4.7.3 Prototype Module Testing <!-- Testing different sections of circuitry to see if PCB layout is good -->
Before the PCB could be designed and manufactured, some of the sub-systems were tested to ensure they could function as designed. The following briefly describes the tests conducted:
- **Lock Actuator Sub-system**: 
  - To ensure the power cut off configuration works, the circuit as defined in [Figure 4.6](#lock-actuator-sch) is constructed on a breadboard using an ESP32-DevKitM-1, a BC547B NPN Transistor, an IRF4905 P-channel MOSFET, SER0050 servo motor and through-hole resistors. Only the decoupling capacitors are neglected as the development board provided stable power. The system is feasible if the servo is operational when the transistor base is high and not operational when the transistor base is low. Results of this test are presented in [Section 5.1.3](#513-lock-actuator-interface-test).
- **Programming Interface Sub-system**: 
  - To ensure that the microcontroller can easily be programmed directly via the UART interface, an Arduino UNO board is used to    program an ESP32-DevKitM-1. Like the ESP32C3, the ESP32MINI found on the ESP32-DevKitM-1 has a UART interface which it can supposedly be programmed via. The Arduino Uno board is essentially used as just a USB-to-UART bridge as the enable pin are connected to ground and the RX and TX pins are connected to the TX and RX pins of the ESP32-DevKitM-1 respectively. The system is feasible if the ESP32 board is recognised by Arduino IDE and a simple program can be flashed. Results of this test are presented in [Section 5.1.4](#514-programming-interface-test). 
- **HMI Sub-system**: 
  - To ensure the HMI is well engineered for human use, the circuit as defined in [Figure 4.9](#hmi-sch) is constructed on a breadboard. This test is essentially done as part of the prototype system test as described in [Section 4.7.2](#472-prototype-system-testing). Results of this test are presented in [Section 5.1.5](#515-hmi-test)

### 4.8 Post-Implementation Verification Methods <!-- How did we test after development?-->
After implementation, the system must again be verified to ensure everything is functioning as specified. The following sections thus define the test specifications used to verify the PCB and final product to ensure it ultimately met the [system requirements](#42-system-requirements).

#### 4.8.1 PCB Module Testing <!-- Checking each sub-system on the PCB -->
After the PCB has been assembled, each sub-system must be tested before the entire system integration is tested. For this reason, various test points are included within the schematic as seen in [Figure 4.2](#schematic). The following describes what each test point is designed to check:
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

#### 4.8.2 PCB System Integration Testing <!-- Checking if sub-systems integrating together as designed -->
With certainty that the sub-systems are powered and functional, the integration between sub-systems can be tested. The following test specifications to test integration were defined:
- **Reading Serial Data of the Sensor**: 
  - To test the functionality and integration of controller, programming interface and sensor sub-systems, the MCU is flashed with an example program to read the sensor data and print it in the serial monitor. The sub-systems are fully integrated if data appears in the serial monitor and is responsive when the PCB is moved around.
- **Programming the MCU to Blink and Beep**: 
  - To test the functionality and integration of controller, programming interface and HMI sub-systems, the MCU is flashed with an example blink program and example beep program from Arduino IDE (with pins adjusted accordingly). The sub-systems are fully integrated if each LED blinks and the buzzer beeps when programmed to.
- **Programming the MCU to Turn on and Cut Lock Actuator Power**: 
  - To test the functionality and integration of controller, programming interface and lock actuator interface sub-systems, the MCU is flashed with a basic program that brings the IO0 high and the voltage across pins 2 and 3 of the servo connector (J5) is measured.  The sub-systems are fully integrated if the voltage is high when IO0 is high.

It should also be noted that all of these tests also verify the integration of the power regulation sub-system as it provides power to all other sub-systems and they would not function without it. 

The results of these tests are presented in [Section 5.8.2](#582-system-integration-performance).

#### 4.8.3 Complete Product Verification <!-- Checking function of the entire PCB -->
Finally, the integration of the complete system must be tested against the requirements outlined in [Section 4.2](#42-system-requirements). 

The setup for this test is defined as follows:
- The MCU is flashed with the program developed in [Section 5.5](#55-software-implementation).
- The PCB is placed on piece of material which is knocked. 
- The USB-to-UART programmer is connected to the RX and TX pins of the PCB so that the serial monitor can be used for debugging
- The MCU is connected to the battery for power

The criteria for the test being successful are:
1. The system can detect whenever the user knocks on the box.
2. The yellow LED is illuminated when the system is in locked state.
3. The servo motor rotates to unlocked position when the correct pre-defined knock pattern is applied in locked state.
4. The green led is illuminated and the buzzer plays the unlocked sound when the correct pre-defined knock pattern is applied in locked state.
5. The red led is illuminated and the buzzer plays the false pattern sound when the correct pre-defined knock pattern is applied in locked state.
6. The green LED is illuminated when the system is in unlocked state.
7. The system enters programming mode and records knocks when the button is pressed in unlocked state. 
8. The system alerts the user that it has entered programming mode when the button is pressed in unlocked state. 
9. The red led is illuminated and the buzzer plays the false pattern sound when the button is pressed in locked state. 
10. The system changes to unlocked state when the most recent pattern defined in programming mode is applied in locked state.
11. The servo motor rotates to locked position when two knocks are applied in unlocked state. 
12. The system goes into sleep state after 60 seconds of inactivity when in locked state.

Once the PCB is verified, these same test specifications can also be used to verify the fully assembled product when the PCB is connected to the housing designed in [Section 4.6](#46-housing-design). 

The results of these tests are presented in [Section 5.8.3](#583-complete-product-performance).

#### 4.8.4 Power Consumption  <!-- Checking power consumption in active and sleep modes -->
Once the general functionality of the system has been verified, another important characteristic of the system must be investigated: the power consumption. To determine the amount of power consumed by the system and estimate the battery life of the system, the current drawn by the system is measured. To do this, an ammeter is connected in series with the power supply and the battery terminal. The system is tested in different modes and functions so that the current measurements in all cases can be taken. The results of this test are presented in [Section 5.8.4](#584-power-consumption).

### 4.9 Validation Methods  <!-- Are we making the right product? -->
After the product has been verified, it must be validated. Essentially, it must be tested in a way to reveal if it not only meets the [system requirements](#42-system-requirements) but the requirements of the user.

#### 4.9.1 User Acceptance Testing  <!-- Presenting prototype to potential users -->
The most direct way to checking the product against the needs of the user is to survey users directly. Over the course of a week, 10 people were surveyed using convenience sampling. Each person was shown the final prototype and asked four questions:
1. What would you rate this product out of ten?
2. What is one feature you especially liked about the product?
3. What is one feature you disliked about the product?
4. What is one feature you believe would improve or should be implemented into the product?

Participants were also allowed to leave any question unanswered. 

The findings can be found in [Section 5.9.1](#591-user-feedback).
<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 5	Results
After the entire methodology and intended design were defined, implementation, verification and validation of the system could commence. The results of this phase of the development process are discussed in this section, starting with the prototyping and continuous verification done before the PCB was manufactured.

### 5.1 Pre-Implementation Verification Results
Before the PCB could be designed and manufactured, the system must be verified from concept to the individual sub-systems.

#### 5.1.1 Concept Feasibility 
To verify the feasibility of knock pattern detection, the tests described in [Section 4.4.2 Sensor Sub-system](#442-sensor-sub-system) were conducted and the results are summarized below:
- Both the piezo disc and IMU were able to detect knocks through a plastic case quite reliably. Though, through the wood, only the IMU was able to detect any knocks.
- In both setups, the IMU was able to detect very fast knocks, but the piezo in plastic setup occasionally missed knocks that were too quick. 

Even after trying to make the piezo a more sensitive by using 3.3V supply instead of 5V, it still couldn’t match the performance of the IMU. This result was unexpected considering other projects in the [Literature Review](#2literature-review). Additionally, the I2C communication of the IMU was observed to be significantly more reliable than the voltage output of the piezo element. 

The IMU also gave data for all three axes. A typical series of knocks as detected by the IMU can be seen in [Figure 5.1](#imu-test). The y-axis is the magnitude in g (gravitational units), while the x-axis is time in milliseconds. The blue, yellow and green lines are the x, y and z axis respectively. Each knock caused a peak in each of the three axes, but most prominently in the axis perpendicular to the surface of the material. As such the knock detection software as discussed in [Section 5.5.2](#552knock-detection), initially considered only the value of this axis. [Figure 5.1](#imu-test) also clearly shows that the peaks have a noticeable time gap between them. This suggests that if the peaks are registered as knocks and the interval between peaks are measured, it is definitely feasible for the software to detect a specific knock pattern based on the the amount of knocks and their intervals.

<div id="imu-test" align="center">
<figure>
  <img src="/resources/images/knockDetectionIMU.png" alt="imu-test" width="500">
  <figcaption align="center"><b>Figure 5.1:</b> Serial Plot from Test of MMA8452Q IMU </figcaption>
</figure>
</div>

#### 5.1.2 Prototype System 
With feasibility confirmed, the development processes continued and a prototype for the entire system as described in [Section 4.7.2](#472-prototype-system-testing) was created. The prototype is shown in [Figure 5.2](#system-prototype). 

<div id="system-prototype" align="center">
<figure>
  <img src="/resources/images/testingSystem_top_annotated.png" alt="system-prototype" width="400">
  <figcaption align="center"><b>Figure 5.2:</b> Breadboard Prototype System</figcaption>
</figure>
</div>

With this prototype, the system was able to recognise knock patterns and alert the user of a successful recognition by turning on the green LED and playing an unlocked sound on the buzzer. Programming mode was also tested as when the button was pushed the system entered programming mode. In this mode, a new knock pattern was applied and the system was reset. Applying this new knock pattern was also recognised after some attempts, and the system played the unlock sound and turned on the green LED. This shows that the system is certainly possible to implement.

However, this prototype had somewhat unreliable knock detection. It was overly sensitive as any movement of the plastic surface was registered as a knock. On the other hand, when the surface was secured to a desk and the desk was knocked, nothing was registered. Many times, the correct knock pattern would also not be recognised. Thus, the system implementation required that great care be taken when designing the surface on which the PCB would be secured (See [Section 5.6](#56-housing-prototype)) and the way the knocking is detected (See [Section 5.5.2](#552-knock-detection)). 

#### 5.1.3 Lock Actuator Interface Test
With the system concept verified, the sub-systems could now be tested and prototyped, starting with the lock actuator interface. The prototype setup is shown in [Figure 5.3](#lock-actuator-prototype). 

<div id="lock-actuator-prototype" align="center">
<figure>
  <img src="/resources/images/motor-control_test_annotated.png" alt="lock-actuator-prototype" width="400">
  <figcaption align="center"><b>Figure 5.3:</b> Breadboard Prototype Lock Actuator Interface</figcaption>
</figure>
</div>

In this prototype, an example program to make the servo motor move back and forth continuously was modified so that the pin connected to the base of the NPN transistor (GPIO9) was high. After flashing, the servo rotated as programmed to, indicating that the system was working in on-mode. The program was then modified again so that GPIO9 was low, essentially deactivating the transistor and by extension cutting the servo's supply. After flashing, the servo no longer rotated, indicating that the cut-off worked. To verify again, the voltage between the power line of the servo and ground was measured to be near zero (with a very small leakage of a few mV). Thus, the lock actuator sub-system is feasible as designed.

#### 5.1.4 Programming Interface Test
The next sub-system verified was the programming interface. The setup to test the direct UART programming is shown in [Figure 5.4](#prog-interface-prototype). 

<div id="prog-interface-prototype" align="center">
<figure>
  <img src="/resources/images/testing-programming_annotated.png" alt="prog-interface-prototype" width="400">
  <figcaption align="center"><b>Figure 5.4:</b> Setup to Test Direct UART Programming</figcaption>
</figure>
</div>

When the circuit was setup and the Arduino UNO was connected to the computer, Arduino IDE did not recognise that board was attached. Even after the board was but into UART download mode by holding the boot button and pressing the reset button, the IDE did not detect the ESP32 board, much less allow for flashing. At first, this result seemed to suggest that programming directly via UART was not possible. However, the project team continued testing with different boards (Arduino UNO R4 Wifi, ESP8266 DevKit) and eventually, a AYWHP CP2102 HW-598 USB-UART-TTL converter was purchased. 

The AYWHP CP2102 HW-598 is a USB-to-UART programmer which can connect directly to the RX, TX, VCC and GND pins of the ESP32 board. When connected, put int UART download mode and plugged into the computer, Arduino IDE detected the board immediately. After this success, the ESP32 board was programmed to make the on-board LED blink and it functioned correctly. Thus, the programming interface sub-system is feasible as designed as long as an dedicated USB-to-UART programmer module is used.

#### 5.1.5 HMI Test
The final sub-system prototyped was the HMI. This prototype was done as part of the system prototype shown in [Figure 5.2](#system-prototype). 

When the system was tested, the HMI was programmed to indicate four main actions:
1. Successful unlock
2. Unsuccessful unlock
3. Entering programming mode
4. Successful lock (re-locking the box after unlocking it)

For a successful unlock, the green LED illuminated and the buzzer made an unlock sound. This sound was designed to sound pleasant using two high frequency chirps. Both the project team and other students in the lab at the time of testing found this sound to be pleasant and a good indication that the box has been unlocked.

For an unsuccessful unlock, the red LED illuminated and the buzzer made an alarm sound. This sound was designed to sound unpleasant to deter unauthorised users from tampering with the box. It takes inspiration from the "wrong-choice" buzzer sound featured in many game shows.

For entering programming mode upon the button press, all LEDs flash for a moment before the yellow LED was illuminated to indicate that programming mode has begun recording. 

For successful lock, all of the LEDs turn off for a moment and the yellow LED is illuminated to indicate that the box is locked once again. It should also be noted that the input for re-locking the box is two simple knocks with any interval between. This was done so that the user does not have to remember any complex pattern to re-lock the box and so that accidental re-locking is less likely as opposed to using a single knock.

Overall, the HMI was satisfactorily ergonomic and the sub-system is feasible as designed. A more complete list of the inputs and outputs of the system is provided in [Section 4.4.6](#446-human-machine-interface-sub-system).

### 5.2 Component Selection <!-- Results of tests between components -->
With the system and sub-systems verified, components could be selected according to the specifications outlined in [Section 4.4.8](#448-component-specifications).

#### 5.2.1 Sensor Selection <!-- Choosing an appropriate sensor -->
As demonstrated in [Section 5.1.1](#511-concept-feasibility), the accelerometer exhibited much better performance than the piezo disc and thus the project team decided that an accelerometer would be the most appropriate sensor. 

While the tests were conducted with a MMA8452Q by Sparksfun Electronics, the final design uses an ADXL345, as it was cheaper and larger in package size making it easier to solder. The ADXL345 is also 13-bit instead of 12-bit, hence should perform even better. It also has a very low power consumption (~23uA) [5] making it ideal for project.

#### 5.2.2 Other Components
Aside from the sensors, all components were chosen based on the specifications outlined in [Section 4.4.8](#448-component-specifications) in [Table 4.4](#tabSpecs). The complete list of all materials used is shown in [Section 5.7](#57-bill-of-materials). Any modifications to the components selected or designed in [Section 4](#4methodology-and-design) is explained in following sections. 

### 5.3 PCB Design <!-- PCB layout, issues and changes to schematic -->
With components selected and the system prototype verified, the layout of the PCB could be designed.

#### 5.3.1 PCB Version 1
The first version of the PCB layout is shown in [Figure 5.5](#pcb-v1). In creating the design, a few important things were considered as follows:
- The voltage regulator was placed far away from the MCU to prevent the switching magnetic field from interfering with the processing.
- The track width for power (0.7mm) was significantly larger than that of signals (0.2mm) to ensure power tracks have lower resistance and can carry sufficient current.
- Both the top and bottom copper layers had a ground plane for better grounding and heat dissipation.
- Wherever possible, power and signal tracks were not run parallel to each other.
- Tracks were never drawn with 90 degree bends.

<div id="pcb-v1" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V1.PNG" alt="pcb-v1" width="600">
  <figcaption align="center"><b>Figure 5.5:</b> First PCB Layout </figcaption>
</figure>
</div>

While this design passed the design rule check in KiCAD, it had a number of issues:
- The biggest issue is that the PCB antenna is above a copper plane which can lead to electromagnetic interference in the ground net.
- Some of the clearances between tracks are too small leading to poor manufacturability and poor insulation between tracks
- 0.2mm track width is difficult to manufacture
- Vias with 0.6mm diameter and 0.3mm hole diameter are too small to be manufactured by AISLER

#### 5.3.2 PCB Version 2
Thus, considering these issues a second design was done as shown in [Figure 5.6](#pcb-v2). In this design, the MCU was shifted to the edge of the PCB and a copper keep-out zone was defined beneath the antenna. The track width and vias diameter were increased to 0.7mm and 0.8mm (with 0.4mm hole diameter) respectively. Additionally, under the advice of Professor Andy Stamm, all of the resistors and ceramic capacitors were changed to surface mount technology (SMT) components instead of through-hole technology (THT) components. The idea behind this switch was that since the accelerometer and MCU required reflow soldering regardless, it would be more efficient to also solder these components in the reflow oven in the same session.

<div id="pcb-v2" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V2.PNG" alt="pcb-v2" width="600">
  <figcaption align="center"><b>Figure 5.6:</b> Second PCB Layout </figcaption>
</figure>
</div>

In this version of the layout, a button for entering programming mode was also added. For the sake of ergonomics, it was placed on the opposite side of the MCU than the LEDs to ensure that they were fully visible when the button is pressed.

One issue encountered in the formation of this layout was the routing to the micro-controller pins became incredibly difficult. Thus, some of the pins were remapped to make the routing is more intuitive. (Note that the pin mapping in [Table 4.2](#tab:controller-pin-mapping) is already the final mapping).

<div id="tab:pin-revision">

*Table 5.1: Changes in Pin Mapping For PCB Adjustments*
| Signal / Function         | Old MCU Pin | New MCU Pin       |
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

#### 5.3.3 PCB Version 3
Finally, the third and final design shown in [Figure 5.7](#pcb-v3) involved some refinement such changing the battery and servo connectors, adding vias for thermal relief, adding mounting holes and adding a [logo](#logo) in the silkscreen. The change in connectors was to facilitate the use of simple JST pin headers which were available in the lab.

<div id="pcb-v3" align="center">
<figure>
  <img src="/resources/images/pcb-layout_V3-final.PNG" alt="pcb-v3" width="600">
  <figcaption align="center"><b>Figure 5.7:</b> Final PCB Layout </figcaption>
</figure>
</div>

### 5.4 PCB Assembly <!-- Final and issues encountered in assembly or after testing-->
#### 5.4.1 Assembly Process
After the PCB layout was finalised, the design was sent to AISLER for manufacturing. The final PCB without any components can be seen in [Figure ](#pcb-blank).

<div id="pcb-blank"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/Unsoldered PCB.jpeg" height="300">
        <figcaption align="center"><b>(a):</b> Front </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/Unsoldered PCB 2.jpeg" height="300">
        <figcaption align="center"><b>(b):</b> Back </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 5.8:</b> Final PCB without Components</figcaption>
  </figure>
</div>

Due to the large number of SMT Components, especially the ADXL345 being an LGA (Land Gate Array package), i.e. pads underneath, reflow oven was used to solder those components after placing the components with a pick and place machine. The solder paste was applied manually for each pad with a pneumatic solder paste dispenser. The THT components were later soldered using manual hand soldering.

The fully assembled PCB is shown in [Figure 5.9](#pcb-final).

<div id="pcb-final"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/SolderedOld.jpeg" alt="pcb-front" height="300">
        <figcaption align="center"><b>(a):</b> Front </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/pcb_back.jpg" alt="pcb-back" height="300">
        <figcaption align="center"><b>(b):</b> Back </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 5.9:</b> Final PCB with Components</figcaption>
  </figure>
</div>

#### 5.4.2 Assembly Issues
Due to the extremely small size of the pads of the ADXL345 pads and ESP32-C3, placing solder paste took many attempts. Only after tweaking the pressure and the nozzle diameter of the dispenser was it possible to place adequate quantities without overfilling the pad. For components such as these, it might be a better approach in future to use a stencil, however for only producing one PCB, the cost of a stencil was not justified and hence the approach avoided. 

Moreover, even though having a large GND plane allowed for better heat dissipation and a better PCB, it made soldering THT components harder as well. Much more heat was required to be able to solder the components reliability. 

Most faults in the soldering were corrected immediately after soldering, due to the continuous [verification process](#48-post-implementation-verification-methods). However one fault was missed. Later during [product validation testing](#491-complete-product-testing), it was discovered the servo was not functioning reliably. After using an oscilloscope to see its response, it was found out that the GND pin of the servo connector was connected, however solder joint was unstable leading to momentary breakage and hence the response was sometimes missed or delayed. This was fixed by soldering it again.

### 5.5 Software Implementation <!-- Final code and issues after testing and how they were solved-->
With the PCB completed, now the software must be implemented on to it, to get the system to work. As discussed in [Section 4.5](#45-software-design) a modular approach was used. The main startup code is in the file KnockLock.ino. 

The libraries used were:
- **ESP32 NVS Library**: For using the NVS memory of ESP32-C3 - in-built with Arduino IDE
- **SparkFun ADXL345 Library (v1.0.0)**: For interfacing with the ADXL345 accelerometer
- **Wire Library**: For I2C communication with the ADXL345 - in-built with Arduino IDE
- **ESP32Servo (v3.0.9)**: For controlling the servo motor

The code implementation of some crucial parts is explained below.
#### 5.5.1 System Initialization
Upon startup, the system must perform many intializations to get everything working correctly in sync. The order is also quite important to save power and to ensure best reliability. 

Upon starting up, its is the important for the system to know why it is starting up. This is because for saving battery, the system is kept in deep-sleep, and in ESP32, waking up from deep-sleep means setup functions runs again. Hence to prevent the system from draining to much battery, even if it woke up to only check battery and alert user for low power or because of double knocking or just first time starting up. How handleWakeup() does this can be seen in [Section 5.5.5](#555-power-management). If the system is supposed to full turn on, only then is the accelerometer setup and the servo enabled. It is important to setupHardware() before checking for wake-up, as the pin must be ready for battery voltage and used to flash the red LED to indicate low battery. setupHardware() is also responsible to attach interrupts to the correct pins and setting up the servo (not enabled yet). How this can be done can be seen in [Listing 1](#lst:setup_hw).

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

The ADXL, being powered directly by the power regulator (and not the MCU) means it retains its settings hence even in deep-sleep keeps its interrupts and other settings.

Once all hardware is setup, it is important for the system to load back the stored pattern, to prevent having the user from setting up the pattern each time the system wakes up. The system does this by loading the pattern, and its length from the NVS storage on the ESP32. It must then just reset the timers to prevent any unwanted actions before time. The system performs this as shown in [Listing 2](#loadPatternResetTimer).

<div =id"lst:loadPatternResetTimer">

*Listing 2: Loading the pattern and resetting timers*
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

For setting up the ADXL (accelerometer), the system uses its library for initializing it with the right settings and then disabling all the unnecessary interrupts. The library used is SparkFun_ADXL345 (Version v1.0.0) as mentioned already in [Section 5.5](#55-software-implementation). All the values are given as constants here, from the setting up in config.h. For giving all these values and communicating with the ADXL, Wire library is used for setting up the I2C communication with it. This allows for easy editing for all parameters from one file. [Listing 3](#init_adxl) from hardware.cpp shows how the ADXL345 is setup.

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

Disabling all interrupts ensure that no unecessary wake-ups occur. Reseting all flags is very important, as ADXL345 interrupts work as latches. Which when triggered keep interrupt high, until reset. 

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

Initially a different approach was used for reading and processing the knocks. The raw ADXL values where read continuously while the system is awake and converted to g for easier comparison as shown in [Listing 7](#oldCalcApproach). 

<div id="oldCalcApproach">

*Listing 7: Older magnitude calculation approach*
```cpp
inline float accelMagnitudeG(int x, int y, int z) {
  return sqrt(x*x + y*y + z*z)*0.0039*; // Calculate magnitude, for g, it must be multiplied by 0.0039 (from datasheet) 
}
```
</div>

The result could then be reduced by one to remove the static gravitational force to find dynamic force and compared to a fixed threshold found using many readings. This approach worked, however was not very effective and reliable with it being too sensitive or too insensitive at times. This was later then changed to reading only z-axis (absolute value), keeping in mind the axis is perpendicular to the PCB so when knock a plane parallel to the PCB it was the only axis greatly affected. Same was also seen in [Figure 5.1](#imu-test). This new approach worked much better for detecting knocks, however had one big drawback. It only worked in one specific orientation, with the PCB perpendicular to the ground plane. Finally it was realized, that the wake up which used the double tap interrupt was working much better, and hence for detecting individual knocks, single tap interrupt can be used. As this is made by the developers of the board, its noise removal and reliablitity was extremely high and knocks could be detected in all orientation. The threshold could also be setup much more reliably. The threshold of 40 was set which corresponded to ~2.5g with a measurement sensitivity of 256 LSB/g or 62.5mg/LSB [[5](#9references)]. The system with this threshold was able to ignore most background noise, as well not trigger the system if the box is moved around. (Note the scale +-2g is for reading purposes, and the threshold here is unaffected by it.)

With the new approach, the system is also much more efficient as it is not reading x,y,z values continuously from the ADXL than only reacting to taps. The ADXL is responsible for monitoring the knocks and finding if the knock is above a threshold to be considered a knock, and because the chip is made primarily for that task it is more efficient in doing so.

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
To save power, the ESP32-C3 stays in deep-sleep mode most of the time, only waking up when knocks are detected. However to put the system to sleep appropriate steps must be taken in the correct order. 

Before going to sleep, the system first checks the battery voltage, to see if it is low or not. If it is low, the system must wake up every few seconds to blink the red LED indicating low battery to alert the user to changee it. If the battery is good, the system can sleep indefinitely until a knock is detected. There may be concern, that what if the system does not have low battery when going to sleep, but the battery drains while sleeping. However this is not a really big concern, as the drain will be very slow. Waking it up to check battery status regularly will waste more power. This decision of checking battery only before sleep was taken also taking into account the system has been designed with two sets of power supply, battery and USB. If the battery drains, the user can always plug in the USB power to power the system.

Checking the battery voltage by reading ADC value from the voltage divider and using the formula as stated in [Appendix A](#appendix-a-circuit-dimensioning-calculations-and-formulae). The system compares this to a threshold to denote if it is too low or not, as shown in [Listing 13](#batteryCheck). The system can also start powering down hardware which is not necessary anymore such as the LEDs off (until Red is required later) and the Servo motor.

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

As there are two methods of waking up, each with different operations to be performed on wake-up, the wake-up reason is checked and system reacts accordingly as shown in the function in [Listing 15](#handleWakeup)

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

This function must be called near the start of the setup() function (right after Serial setup) to save as much power as possible as previously stated in [Section 5.5.1](#551-system-initialization). The reason for it being in setup() is that after deep-sleep, the ESP32-C3 does a full reset, hence setup() is called again.

As the sytem is in deep-sleep most of the time, when an ESP32-C is woken up from deep-sleep mode, it goes through setup again, and must recall its memory to restore the pattern of the user. To recall these values NVS memory of the controller is used as explained in the next section.

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
Having finished the implementation of the software and hardware, the system could be implemented into the housing.

As discussed in [Section 4.6](#46-housing-design), the model was made. However it had some issues which prevented the system from working reliably. These issues and how they were fixed in shown in [Table 5.2](#tab:housingIssues).

<div id="tab:housingIssues">

*Table 5.2: Housing issues and fixes*
|Issue                                                  |Fix                                                                        |
|:--                                                    |:--                                                                        |
| Button hard to press                                  | Instead if bending button, use column to slide in and out                 |
| Screw mounts to tall causing issues in button pressing| Add space in door to insert voltage regulator, get PCB close to door      |
| Servo motor wire interfering                          | Add clearance for wires                                                   |
| Battery using box space                               | Add area for battery in the base, to also help with weight distribution   |
| Battery exposed                                       | Add lid to cover battery                                                  |
| Clearance issues due printer accuracy                 | Increase clearances for fits                                              |
| Wires of servo interfering with closing               | Add to prevent servo wires interference                                   |
| Micro USB-B hole missing                              | Add Micro USB-B port hole                                                 |

</div>

With all fixes implemented the final housing model can be seen in [Figure 5.10](#housing-model-final).

<div id="housing-model-final"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/finalHousingModel.PNG" alt="final-housing-isometric-view" height="300">
        <figcaption align="center"><b>(a):</b> Closed </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/finalHousingModel1.PNG" alt="final-housing-inside-view" height="300">
        <figcaption align="center"><b>(b):</b> Open </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 5.10:</b> Final 3D Model of Housing</figcaption>
  </figure>
</div>

This was model was then 3D printed using PLA (0.2mm Nozzle) to get the final product as seen in [Figure 5.11](#final-product). The following settings were implemented for printing:

- Lightning grid pattern
- Door with an infill of 70% (Higher infill for better vibrations passthrough)
- Rest of the parts with an infill of 10%

<div id="final-product"  align="center">
  <figure>
  <table border="0">
    <tr>
      <td><figure>
        <img src="/resources/images/full-prototype_closed.jpg" alt="final-product-open-view" height="500">
        <figcaption align="center"><b>(a):</b> Closed </figcaption>
      </figure></td>
      <td><figure>
        <img src="/resources/images/full-prototype_open-1.jpg" alt="final-product-open-view" height="500">
        <figcaption align="center"><b>(b):</b> Open </figcaption>
      </figure></td>
    </tr>
  </table>
  <figcaption align="center"><b>Figure 5.11:</b> Final Fully Assembled Product</figcaption>
  </figure>
</div>

For connecting the door to the box, the filament used for 3D printing can be passed through the hinges and melted at the corners. The diameter of filament should be less than or equal to 2mm. However, this approach was not implemented in the final prototype given its permenance. Instead, M2x20 screws were placed into the holes to act as temporary hinges.

One issue faced when assembling the PCB into the housing was that the SER50090 servo motor prevented the door from closing because it was too tall. Thus, the SG90 servo motor used in [prototyping the system](#472-prototype-system-testing) was used instead. Another issue was that while the [techincal requirements](#422-technical-requirements) specified an IP31 rating, 2.5mm screw drivers could fit through the gap between the door and the box as well as through the micro USB port hole, thus making the housing only IP21. 

### 5.7 Bill of Materials <!-- Full list of materials used -->
With this final prototype complete, it is important to know how much the entire system costs to make, including electrical and mechanical components.

The complete list of all electrical materials used to assemble the product is shown in [Table 5.3](#tab:BOM-E). Note that the PCB is taken as item 34, but not included in this table.
<div id="tab:BOM-E">

*Table 5.3: Electrical Bill of Materials*
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
| **Total without HSRW Components** |                           |     |                                 |                         |                       |        |              | **15.05** |
| **Total with all Components** |                           |     |                                 |                         |                       |        |              | **26.61** |
</div>

[Table 5.3](#tab:BOM-E) shows that the costs of all the electrical components excluding the PCB sum up to **€26.61**. This a budget overun of €1.61, but that is within the tolerance of acceptance for the project team. However, if the costs of components taken from HSRW supply are neglected, the total electrical costs are only **€15.05**. Additionally, costs could have potentially been reduced by using a cheaper microcontroller, sensor or lock actuator, however these components were selected for significant reasons as explained in previous sections. 

The complete list of all mechancial materials used to assemble the product is shown in [Table 5.4](#tab:BOM-M). 
<div id="tab:BOM-M">

*Table 5.4: Mechanical Bill of Materials*
| Item Number | Qty | Component           | Price / Unit [€] | Price [€] |
| ----------- | --- | ------------------- | ---------------- | --------- |
| 35          | 7   | M2×6 Screw          | 0.11             | 0.77      |
| 36          | 2   | M2×20 Screw         | 0.14             | 0.28      |
| 37          | 1   | M3×15 Plastic Screw | 0.08             | 0.08      |
| 38          | 7   | M3 Plastic Washer   | 0.01             | 0.07      |
| 39          | 1   | M3 Hex Nut          | 0.07             | 0.07      |
| 40          | 1   | 3D Printed Housing  | 8.43             | 8.43      |
| **Total**   |     |                     |                  | **9.70**  |
</div>

[Table 5.3](#tab:BOM-E) shows that the costs of all the mechanical components sum up to **€9.70**. The main contributor to this cost is evidently the 3D printed housing. The calculations for the cost estimate of the 3D printed housing can be found in [Appendix B](#appendix-b).

Summing the total electrical costs (€26.61), mecahnical costs (€9.70) and cost of the PCB (€7.24) the total cost of the project came up to be **€43.55**. While these costs are quite high, this is just a first version of the product and if further iterations are made costs could be reduced especially if cheaper components that still meet specifications are chosen. These costs also do not account for the cost of labour for the assembly process, however those considerations are beyond the scope of this project. 

### 5.8 Post-Implementation Verification Results 
Following the implementation of the system is, of course, the verification of the system. From the sub-systems of the PCB to the final assembled product, verification was done according to the test specifications defined in [Section 4.8](#48-post-implementation-verification-methods) and any issues discovered were treated.

#### 5.8.1 Module Performace  <!-- How is each circuit performing? -->
Following the test specifications defined in [Section 4.8.1](#481-pcb-module-testing), the results of the PCB verfication is as follows:
- **Sensor Sub-system**: 
  - When power was connected, the voltage measured at test point 6 relative to ground was approximately 3.3V. This shows that the sensor sub-system is recieving sufficient power.
- **Lock Actuator Interface Sub-system**: 
  - When the voltage at base of the NPN was measured to be around 3.3V (relative to ground), the voltage at the supply pin of the servo connector was measured to be around 6V (relative to ground). 
  - When the voltage at base of the NPN was measured to be 0V (relative to ground), the voltage at the supply pin of the servo connector was measured to be approximately 0V (relative to ground).
  - Thus, the lock actuator interface sub-system is receiving sufficient power and the power cut-off configuration is working as designed. 
- **Controller Sub-system**: 
  - When power was connected, the yellow LED was dimly lit. 
  - The voltage at the enable and supply pins of the MCU were measured to be around 3.3V (relative to ground). 
  - This indicates that the controller sub-system is receiving sufficient power.
- **Programming Interface Sub-system**: 
  - When the AYWHP CP2102 HW-598 USB-to-UART programmer was connected to the programming interface as shown in [Figure 5.12](#programming-mcu)and the system was booted into UART download mode, the Arduino IDE recognises the ESP32 immeditately. 
  - Thus, the programming interface sub-system is fully functional. 
- **Power Regulation Sub-system**: 
  - When power was connected via the battery terminal, the voltage at test point 4 was measured to be around 3.3V (relative to ground). 
  - When power was connected via the mirco USB port, the voltage at test point 4 was measured to be around 3.3V (relative to ground).  
  - When power was connected via both the battery and micro USB simulatenously, the voltage at test point 4 was measured to be around 3.3V (relative to ground). 
  - Thus, the power regulation sub-system is fully functional. 

<div id="programming-mcu" align="center">
<figure>
  <img src="/resources/images/programming_annotated.png" alt="programming-mcu" width="400">
  <figcaption align="center"><b>Figure 5.12:</b> Using External USB-to-UART Programmer to Program the ESP32 on the PCB </figcaption>
</figure>
</div>

#### 5.8.2 System Integration Performance <!-- How are the integrations performing? -->
Since all of the sub-systems on the PCB are functional, the integration tests as defined in [Section 4.8.2](#482-pcb-system-integration-testing) were conducted. The results of these tests are as follows:
- **Reading Serial Data of the Sensor**: 
  - After connecting the system as shown in [Figure 5.12](#programming-mcu), the ESP32 was successfully flashed with the example program.
  - The serial monitor showed the accelerometer data as programmed.
  - Thus, the controller, programming and sensor sub-systems are successfully integrated. 
- **Programming the MCU to Blink and Beep**: 
  - Using the same setup as shown in [Figure 5.12](#programming-mcu), the blink and beep example program was flashed successfully. The LEDs were set to turn on and off on after each other in a repeating pattern. The buzzer was made to beep every times the LEDs changed.
  - After flashing, the HMI behaved exactly as programmed. 
  - Thus, the controller, programming and HMI sub-systems are successfully integrated.  
- **Programming the MCU to Turn on and Cut Lock Actuator Power**: 
  - Using the same setup as shown in [Figure 5.12](#programming-mcu) and the same program as in [Section 5.1.3](#513-lock-actuator-interface-test), the ESP32 was successfully flashed. The only differences in the program were the pin definitions and the PROG button on the PCB was setup to control the NPN transistor base pin, i.e. to turn on or off the servo motor.
  - When the button was pressed, the servo motor stopped rotating. Once pressed again, it started rotating again.
  - Thus, the controller, programming, HMI and lock actuator interface sub-systems are successfully integrated. 

The success of all of these tests, by extension, verifies the integration of the voltage regulation sub-system. 

#### 5.8.3 Complete Product Performance <!-- How is the complete product performing?-->
Finally, the complete integration of the system was tested to ensure that it meets all requirements outlined in [Section 4.2](#42-system-requirements). Following the test specifications defined in [Section 4.8.3](#483-complete-product-verification), the PCB was connected and setup as shown in [Figure 5.13](#full-pcb-testing). 

<div id="full-pcb-testing" align="center">
<figure>
  <img src="/resources/images/pcb-testing-integration.jpg" alt="full-pcb-testing" width="400">
  <figcaption align="center"><b>Figure 5.13:</b> Setup for Verification of Full PCB</figcaption>
</figure>
</div>

With the setup shown in [Figure 5.13](#full-pcb-testing), the system was able to succeed in almost all test criterias defined in [Section 4.8.3](#483-complete-product-verification) except, critically, criterion 1. That is: "The system can detect whenever the user knocks on the box". When knocks were detected, the pattern recognition software, programming mode and HMI all worked as intended, but many knocks went unregistered unless the PCB itself was touched or if the user applied a lot of force in their knocks on the surface. The reason for this fault was the intial way the knock detection was done in the software. This issue is discussed in more detail in [Section 5.5.2](#552-knock-detection), but essentially, all three axes of the accelerometer were used in knock detection and this lead to unreliability. When the software was changed to measure only the z-axis (the axis perpendicular to the ground plane), the knock detection became more reliable, but the PCB had to be oriented in a vertical position as shown in [Figure 5.14](#full-pcb-testing-vert). When in the horizontal position shown in [Figure 5.13](#full-pcb-testing), the accelerometer read constant accelerations and hence continouously registered knocks that were not occuring. 

<div id="full-pcb-testing-vert" align="center">
<figure>
  <img src="/resources/images/testingOrientation.jpg" alt="full-pcb-testing-vert" width="400">
  <figcaption align="center"><b>Figure 5.14:</b> Setup for Verification of PCB in Vertical Orientation</figcaption>
</figure>
</div>

Verification in the vertical orientation as shown in [Figure 5.14](#full-pcb-testing-vert) was successfull in all criteria, more so than before. Thus, the PCB was installed into the housing as shown in [Figure 5.11](#final-product) and the tests were performed again. In this case, the reliability of knock detection became an apparent issue once again as knocks were only registered when applied a to the lower part of the door, near the position of the accelerometer on the PCB. Thus, the knock detection method in the software was altered once again to use the activity interrupt of the ADXL345. This gives the final version of the software presented in [Section 5.5.2](#552-knock-detection).

With this final version of the software, the product performed signficantly better within the housing, easily succeeding in all success criteria. As such, this version was taken as the final product for this project and development as ceased. A showcase of the performance of the final product can be seen in [Figure 5.15](#product-showcase), just click on the image to open the video. 

<div id="product-showcase" align="center">
<figure>
  <a href="https://youtu.be/qGrgIr3oHPE">
  <img src="/resources/images/full-prototype_closed.jpg" alt="product-showcase" width="400">
  </a>
  <figcaption align="center"><b>Figure 5.15:</b> Showcase of Complete Product (click image to open video)</figcaption>
</figure>
</div>

#### 5.8.4 Power Consumption <!-- How much power is being consumed? -->
With the system fully functional, the investigation of the power consumption was conducted as described in [Section 4.8.3](#483-power-consumption). The experimental setup used is shown in [Figure 5.16](#current-consumption).
<div id="current-consumption" align="center">
<figure>
  <img src="/resources/images/power-consumption-verification.jpg" alt="current-consumption" width="400">
  <figcaption align="center"><b>Figure 5.16:</b> Setup for Current Measurement</figcaption>
</figure>
</div>

The results of the current measurements are shown in [Table 5.5](#tab:current-readings). It can be clearly seen that the while the system is active the current consumption is quite high in both unlocked and locked states. When the system was switched to programming mode from unlocked mode, the current reading did not change. The deep-sleep of the microcontroller reduces the current consumption drastically, however, 5.32mA is still not an insignificant current draw. When the ammeter was placed in series with the servo supply line and the supply pin on the servo connector in sleep mode, it showed that the current draw was only a few uA which shows that the power cut-off is functional and is thus not the issue. To diagnose the exact reason for this problem would require invasive or destructive techniques and for this reason the project team decided not to investigate further. 

It should also be noted that the "Start-up" mode is when the PCB is initially connected to power. This mode has a lower current draw because the PWM signal for the servo is not being sent to the servo as yet. However, once the box is unlocked for the first time the servo is constantly getting the PWM signal and hence the current draw increases.

<div id="tab:current-readings">

*Table 5.5: Current Readings in Different Modes*
| Mode                 | Current [mA]         | Assumed Time per Day [s] | Average Current [mA] |
| -------------------- | -------------------- | ------------------------ | -------------------- |
| Idle (upon Start-up) | 36.3                 | 0                        | 0.00                 |
| Unlocked             | 42.85                | 600                      | 0.30                 |
| Locked               | 47.5                 | 350                      | 0.19                 |
| Programming Mode     | 42.85                | 60                       | 0.03                 |
| Sleep                | 5.32                 | 85390                    | 5.26                 |
</div>

To estimate the power usage, the average current consumption must be estimated. For a general case scenario, it can be assumed that a person may unlock and lock the box around 5 times in a given day and reprogram the box 1 time in a day. The box may be in locked mode for around 70s; 10s after wake up to unlock and 60s after re-locking to go into sleep mode. It may be in unlocked state for around 120s as the person could be deciding what to put in the box. Finally, programming may take around 60s. The remaining time in the day, the box would be in sleep mode. 

With all of these assumptions, the average currents were found and recorded in [Table 5.5](#tab:current-readings). The currents were summed up giving the total average current to be around **5.78mA**. With an average battery voltage of 6V, this results in an estimated power consumption of **34.67mW**. See [Appendix B](#appendix-b-power-consumption-calculations) for the formulae used.

With this average current consumption, the battery life of the box was estimated to be around **18.03 days** assuming the AA batteries have a capacity of 2500mAh. 

### 5.9 Validation Results 
After the system was verified against the [system requirements](#42-system-requirements), the Knock Lock product was finally able to be validated by users. 

#### 5.9.1 User Feedback <!-- what did people think? -->
From the survery defined in [Section 4.9.1](#491-user-acceptance-testing), the findings are shown in [Table 5.6](#tab:user-feedback). 
<div id="tab:user-feedback">

*Table 5.6: User Feedback*
| S. No.      | Overall Rating (out of 10) | Good Feature                     | Bad Feature                                   | Lacking Feature / Potential Improvements |
| ----------- | -------------------------- | -------------------------------- | --------------------------------------------- | ---------------------------------------- |
| 1           | 9                          | Keyless entry                    | Knocking anywhere                             | Only possibility to store one password   |
| 2           | 9                          | Keyless entry                    | Electronics too visible                       | –                                        |
| 3           | 9                          | Asleep when not in use           | Not safe as knock could be heard and mimicked | No recovery method                       |
| 4           | 9                          | You can knock anywhere           | Knob too small to open                        | Possibility of mechanical unlocking      |
| 5           | 9.5                        | Like the idea of beats to unlock | –                                             | Different shapes for housing             |
| 6           | 9                          | Keyless entry                    | Housing slides too much                       | Using rubber pads on bottom of housing   |
| 7           | 10                         | –                                | –                                             | –                                        |
| 8           | 9.5                        | –                                | Door can easily be pulled open                | No recovery method                       |
| 9           | 10                         | Like the idea of beats to unlock | –                                             | –                                        |
| 10          | 9                          | Keyless entry                    | –                                             | Could be implemented into a mailbox      |
| **Average** | **9.3**                    |                                  |                                               |                                          |
</div>

With an average rating of 9.3, it appears that the Knock Lock is a satisfactory product. The main feature that people appreciated was the ability to open the door without a key. However, product still has room for improvement and the suggestions provided by users were considered in the future improvements discussed in [Section 7.1](#71-future-improvements). It should be noted that the majority of the people surveyed are familiar with the members of the project team and thus some responses may contain bias. 

<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 6	Discussion
With the final product complete and running, it must be evaluated against the existing products and its limitations pointed. Finally the products signficance and applications should be talked about.

### 6.1 Product Evaluation
Looking back at the [Section 2](#2-literature-review), this product has a similar functionality, with vastly different approach to implement that functionality and also covers many of the limitations faced by the other products, these include: sensing reliability, power efficiency, flexbility and multi-axis detection.

### 6.1.1 Sensing Reliability
As noted in literature [[4](#9references)], piezos act as high pass filters, and hence often miss the lower frequency sounds especially across thicker materials. The accelerometer on the other is able to detect flat responses down to 0 Hz across varying material thickness.
Moreover while piezos have to be constantly monitored by the CPU and noise removed, the ADXL345 is able to do this monitoring completely on chip and can effectively reduce envireomental noise.

### 6.1.2 Power Efficiency
Most reviewed projects [[1,2,3](#9references)] also lacked a sophisticated power mangement system. They were constantly awake monitoring the values. Whereas the Knock Lock, spends most of its time in deep-sleep mode (~5uA), only waking up for battery monitoring or double knocks. The ADXL having hardware interrupts also helps in achieving a better wake up method, as the accelerometer itself has very minimal current drawn (~23uA in measurement mode [[5](#9references)]).

The system also has a dedicated PCB with only the required components and not unecessary hardware, which also saves battery with having an average current consumption of 5.78mA according the assumptions in [Table 5.5](#tab:current-readings), unlike the other projects which use developement board.

MOSFET Power gating servo motor is another feature which helps the system save battery, by effectively removing any current drawn by the servo when not required, this is not done for most other projects.

These techniques allow for the battery life as found in [Section 5.8.4](#584-power-consumption) of around 18.03 days even after a very frequent use of 5 unlocks a day, and one reprogram a day, considering 120s of unlocked each time and 60s of reprogramming time.

The system also implements a battery monitoring system unlike the other projects, which allows the user to know when the battery must be replaced. 

### 6.1.3 Flexibility
While other projects do work, they are limited to the specific enviroment conditions they are designed for. To change sensitivity of the piezo, while it can be done via software it is very limited, for more sensitivity hardware changes are required, such as an amplification circuit. While for the Knock Lock most settings are software based already, with possibility of even changing scale to make system less sensitive for when only heavy knocks to be detected, as the accelerometer can be communicated with using I2C. 

The system also implements certain features to allow for leniency, such as allowing a defined number of mistakes, to allow system to detect knock as correct even if the first few or last few knocks maybe incorrect. 

### 6.1.4 Multi-axis detection
The projects seen in the literature review ([Section 2](#2-literature-review)) all had one limitation, they had omnidirectional sensing, i.e. the knock surface could only be parallel to the knocking sensor. However, in the Knock Lock using an accelerometer the system has access to 3-axis (x,y,z) which allows system to reliably detect knocks regardless of the side of the enclosure the system is knocked. This makes the system also more versatile for implementing in different housing or orientations.

However even after the many benefits of this system over the others discussed, each system has its limitations.

### 6.2 Product Limitations
After extensive testing, some limitations of system were realized:

- Power Source: The current system uses 4xAA primary cells, which are not rechargable. Battery must be replaced each time they run out.
- Enviromental protection: The system currently has a very low IP (Ingress Protection) rating of only IP21 and hence susceptible to dust and moisture.
- Ergonomics: With the current housing design, the USB port is difficult to access. The LEDs are also not as clearly visible from a height.
- Mechanical integrity: While the software is secure, a hard enough torque on the door can cause the servo horn/arm to decouple from the servo.
- Recovery: No provision to recover the pattern if forgotten.

### 6.3 Product Significance
The development of the Knock Lock demonstrates a shift towards more intuitive and "invisisble" security interfaces. Using knocks instead of traditional locking systems such as NFC, RFID, Mechanical or Biometric systems offers some key advantages:

- Security: Knock Lock provides an alternative entry method which does not require a physical key, which can be lost or stolen. Also by allowing anywhere from 5 to 30 knocks the possible permuations of knocks is approximately $\approx 2.14 \times 10^{32}$** (Calculation in [Appendix D](#appendix-d-knock-permutations-calculation)).
- Versatility: To due the ability of detecting upto 0 Hz vibrations, the material versatility using an accelerometers is much higher.
- Sustainability: The project highlights the viability of long-term battery powered IoT security solutions, by achieving such low deep-sleep currents and use of such low power demanding sensor modules.
- Privacy Protection: Due to the system only monitoring mechanical vibrations, it ensures users privacy which may be of concern if a biometric, camera or microphone system was implemented.

<!--------------------------------------------------------------------------------------------------------------------->
<!--------------------------------------------------------------------------------------------------------------------->
## 7	Conclusion
The Knock Lock project sucesfully demonstrates a more fun method of unlocking a door. It makes the process of opening door a more fun and intuitive process. It demonstrates this idea by implementation in a small box, however the design is highly scalable and can be implemented even in, for example, a door with only minor modifications, if necessary, to the actuation mechanism and/or the thresholds.

The project was able to meet most of its project requirements, except the IP31 rating, by achieving only IP21 rating. However this is mainly to do with the housing which can be improved with minor tweaks to hole sizes of the USB port and door size relative to the box. Use of Gaskets could improve this even past IP31 rating. Other than this all other functional and system requirements were met while also following all the project requirements in mind. Some additional features such as mistake allowance were also implemented succesfully within a total budget of €43.55, including everything, as calculated in [Section 5.7](#57-bill-of-materials).

Following the V-Model Development structure also helped fascilitate timely error fixes in each stage, which is especially more critical in a project of such time contraint and limited budget. Ultimately the Knock Lock was able to demonstrated a shift of analog dependent hardware to I2C based software defined system for a more power efficient, customisable and reliable system.

### 7.1 Future Improvements
Doing this project, and with the user feedback from [Section 5.9.1](#591-user-feedback) opened more aspects which can be worked on in future when reiterating the project. These include:
- Rechargeability: Implementing a recharging circuit on the existing micro USB-B port and using rechargable batteries
- Redundant sensors: Use Piezo with ADXL to more effectively detect a knock
- Improved Ergonomics: Using a material that does not hurt to knock, a housing shape which does not hurt to carry around and also does not slide when knocked on
- Better locking mechanism: Using a solenoid to lock the system to make it more secure
- Recovery: Possible recovery method for pattern in case forgotten
- Multiple passwords: Possibility to store multiple passwords
- Alternative entry: An alternative entry mechanism, perhaps mechanical

## 8 Acknowledgement
The project team would like to express their sincerest gratitude to Mr. Friedrich Muhs who provided incredible guidance and aid during the assembly and testing phases of the project. They would also like to thank Professor Andy Stamm, Mr. Frank Kremer and Mr. Jure Cubelic who gave advice and guidance during the design phase of the project, especially Professor Stamm whose idea it was to use an accelerometer in the first place.

## 9	References

* [1]: Instructables. (2022, May 8). *Secret knock detecting door lock*. Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Secret-Knock-Detecting-Door-Lock/ 
* [2]: Dodhia, V. (2021, June 20). *Arduino secret knock pattern door lock*. Viral Science. Retrieved November 20, 2025, from https://www.viralsciencecreativity.com/post/arduino-secret-knock-pattern-door-lock
* [3]: Instructables. (2017, October 21). *Knock Box (it Opens When You Knock on It!)*. Instructables. Retrieved November 20, 2025, from https://www.instructables.com/Knock-box-it-opens-when-you-knock-on-it/
* [4]: Burgognoni, E. (2025, August 28). *Comparing MEMS and IEPE accelerometers for structural vibration behavior testing*. Data Acquisition | Test and Measurement Solutions. Retrieved October 30, 2025, from https://dewesoft.com/blog/comparing-mems-and-iepe-accelerometers
* [5]: Analog Devices. (n.d.). *ADXL345* [Datasheet]. Analog Devices. Retrieved November 20, 2025, from https://www.analog.com/en/products/adxl345.html
* [6]: Arar, S. (2021, Decemeber 12). *Introduction to Capacitive Accelerometers: Measuring Acceleration with Capacitive Sensing*. All About Circuits. Retrieved January 5, 2026, from https://www.allaboutcircuits.com/technical-articles/introduction-to-capacitive-accelerometer-measure-acceleration-capacitive-sensing/ 
* [7]: Scherz, P and Monk, S. (2016). *Practical Electronics for Inventors*. Mc Graw Hill.
* [8]: Gammon, N. (2015, Janurary 30). *High side driver*. Gammon.com. Retrieved October 26, 2025, from https://www.gammon.com.au/motors
* [9]: Espressif Systems. (2021). *ESP32-C3 Series* [Datasheet]. In Espressif. https://www.espressif.com/documentation/esp32-c3_datasheet_en.pdf

## 10	Appendices
### Appendix A: Circuit Dimensioning Calculations and Formulae
*Calculation of Required Carrying Current for Fuses*
$$I_{in}=\frac{P_{in}}{V_{in}}=\frac{I_{out}\cdot V_{out}}{\eta \cdot V_{in}} = \frac{1A\cdot3.3V}{0.75\cdot 6V}=0.733A$$

*Formulae for Calculating Battery Voltage from MCU ADC Reading*
The general voltage division rule is as follows: 
$$ V_{out} = \frac{R_2}{R_1 + R_2}\cdot V_{bat} $$

Thus, to calculate the battery voltage:
$$ V_{bat} = \frac{\text{readingInMillivolts}}{1000}\cdot\frac{R_1+R_2}{R_2} $$

$$ V_{bat} = \frac{\text{readingInMillivots}}{1000}\cdot 2.47 $$

$V_{out}$ is what is read by the microcontoller and hence can be used to calculate the voltage at the battery using the fixed resistor values (See[Section 4.4.7](#447-power-regulation-sub-system)).


### Appendix B: Power Consumption Calculations
The formula used to calculate the average current for any given case:
$$ I_{avg} = \frac{I \cdot t}{24h \cdot 3600 \frac{s}{h}} $$
Where $I$ is the current reading in mA and $t$ is the assumed time per day in s. 

The formula used to calculate the average power consumption for any given case:
$$ P_{avg} = I_{avg} \cdot V_{avg} $$

Where $V_{avg}$ is the average voltage of the power source which is taken as 6V in all cases.

The formula used to estimate the battery life:
$$ T_{\text{Battery Life}} = \frac{C}{I_{avg, total} \cdot 24 \frac{h}{day} } $$
Where $T_{\text{Battery Life}}$ in days, $C$ is the battery capacity in mAh and $I_{avg, total}$ is the total average current.  

### Appendix C: 3D Printed Housing Price Estimate

| Item                 | Infill (Lightning) [%] | Mass [g] | Material | Cost per g [€/g] | Cost [€]  |
| -------------------- | ---------------------- | -------- | -------- | ---------------- | --------- |
| Door + Battery Cover | 70                     |  76.13   | PLA      | 0.025            | 1.90      |
| Box Top              | 10                     | 187.63   | PLA      | 0.025            | 4.69      |
| Box Bottom           | 10                     |  70.36   | PLA      | 0.025            | 1.76      |
| **Total**            |                        |          |          |                  | **8.43**  |

### Appendix D: Knock Permutations Calculation

Calculation of possible permutations with the following parameters:
* **Minimum Knocks:** 5 (4 intervals)
* **Maximum Knocks:** 30 (29 intervals)
* **Maximum Time ($T_{max}$):** 2000 ms
* **Tolerance ($\Delta t$):** 150 ms

The number of discrete "timing slots" available in a single gap between two knocks is the maximum duration divided by the tolerance:

$$k = \lfloor \frac{2000}{150} \rfloor = 13$$

For a pattern with $n$ knocks, there are $n-1$ intervals. The number of combinations for a specific number of knocks is:
$$C_n = 13^{(n-1)}$$

The total number of combinations ($S$) is the sum of all patterns from 4 intervals to 29 intervals:

$$S = 13^4 + 13^5 + 13^6 + \dots + 13^{29}$$

This is a **Geometric Series** where:
* **First term ($a$):** $13^4$
* **Ratio ($r$):** $13$
* **Number of terms ($m$):** 26 (from $29 - 4 + 1$)

Applying the Sum Formula
The formula for the sum of a geometric series is $S_m = \frac{a(r^m - 1)}{r - 1}$:

$$S = \frac{13^4(13^{26} - 1)}{13 - 1}$$

$$S = \frac{28,561 \times (13^{26} - 1)}{12}$$

Final Result
Using the value of $13^{26} \approx 9.004 \times 10^{28}$:

**Total Combinations $\approx 2.14 \times 10^{32}$**