# TITAN HAND CAR

A hand\-gesture\-controlled robotic car using an ESP32 and computer vision\..

## Project Overview

TITAN HAND CAR is a planned robotics project that aims to control a small two\-wheel robot car using hand gestures detected by a camera\.

The intended system will use:

- A phone camera to capture hand movements
- Hand\-tracking software to recognise gestures
- An ESP32 development board to receive movement commands over Wi\-Fi
- A motor driver to control the car’s two DC motors
- A 2WD robot chassis and battery pack

## Planned Hand Controls

|Hand gesture / movement|Intended car action|
|-----------------------|-------------------|
|Open palm              |Stop               |
|Hand moved upward      |Move forward       |
|Hand moved downward    |Reverse            |
|Hand moved left        |Turn left          |
|Hand moved right       |Turn right         |
|Closed fist            |Emergency stop     |

The exact gesture mapping may change during testing\.

## Planned Hardware

|Component                               |Quantity |Status                                                    |
|----------------------------------------|--------:|----------------------------------------------------------|
|ESP32 development board                 |1        |To be selected / purchased                                |
|2WD robot car chassis with two DC motors|1        |To be selected / purchased                                |
|L298N motor driver                      |1        |To be checked for motor compatibility                     |
|Suitable battery pack                   |1        |To be selected after checking motor and board requirements|
|Jumper wires and connectors             |As needed|To be acquired                                            |

**Important:** This is a preliminary parts list\. Motor voltage/current, driver limits, battery requirements, and wiring must be checked against the exact components before assembly\.

## Planned Software

- Arduino IDE / ESP32 Arduino core for the car controller
- Hand tracking on a phone or computer using a suitable computer\-vision library
- Wi\-Fi communication between the hand\-tracking device and ESP32

The phone\-camera and wireless\-control approach is a proposed architecture, not yet tested\.

## Safety

- Test with the wheels raised off the ground first\.
- Include a reliable stop command and test it before driving\.
- Use a battery and motor driver rated for the selected motors\.
- Do not power the motors directly from the ESP32\.
- Disconnect power before changing wiring\.
- Test at low speed in a clear area\.

## Development Plan

- [ ] Finalise the hardware choices and verify compatibility
- [ ] Create the initial circuit and pin plan
- [ ] Set up the ESP32 development environment
- [ ] Test each motor using the motor driver
- [ ] Establish Wi\-Fi communication with the ESP32
- [ ] Implement hand detection and gesture recognition
- [ ] Map gestures to car movement commands
- [ ] Add and test an emergency stop
- [ ] Assemble the car and test it safely
- [ ] Record real build progress, test results, and changes

## Current Status

**Stage:** Planning

No hardware assembly or physical testing has been completed yet\. This README will be updated as the project is designed, built, and tested\.

## Project Documentation

As the project progresses, this repository will contain the wiring diagram, source code, parts list, photographs, and test notes\.
