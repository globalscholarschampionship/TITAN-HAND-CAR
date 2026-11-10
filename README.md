# TITAN HAND CAR — Starter Pack

A 2WD robotic car controlled by:
1. APDS-9960 hand gestures.
2. Voice commands recognised by an iPhone app and sent to the ESP32 over Bluetooth Low Energy (BLE).

## Important voice-control detail
The ESP32 does not understand spoken words by itself in this design. The iPhone performs speech recognition, then sends a short text command (`FORWARD`, `BACKWARD`, `LEFT`, `RIGHT`, or `STOP`) over BLE. You will need an iOS app/workflow that supports both speech recognition and writing text to a BLE UART characteristic. A generic BLE scanner is useful for testing but does not automatically provide voice recognition.

## Included files
- `TITAN_HAND_CAR_ESP32_BLE_GESTURE.ino` — starter firmware.
- `WIRING_AND_PIN_MAP.md` — connection plan and electrical cautions.
- `BOM.csv` — preliminary parts list.
- `CHASSIS_LAYOUT.scad` — editable conceptual chassis layout.
- `BUILD_AND_TEST_CHECKLIST.md` — staged test plan.

## Current design assumptions
- ESP32 DevKit with BLE support
- APDS-9960 breakout board
- L298N motor driver
- Two TT DC gear motors and two wheels
- Front swivel caster
- Separate motor battery supply
- Physical master power switch

## Safety and readiness
This is a design/starter package, not a verified manufacturing package. Do not buy parts or connect power solely from these files. Check the exact board pin labels, APDS-9960 breakout voltage requirements, motor voltage/current, battery chemistry and voltage, L298N ratings, motor polarity, and actual mounting dimensions. The CAD is a conceptual layout and must be checked against the physical parts before fabrication.

## Suggested development order
1. Confirm exact part models and dimensions.
2. Test ESP32 BLE connection with motors disconnected.
3. Test APDS-9960 gestures with motors disconnected.
4. Test motor driver and each motor separately using a current-limited/safe supply.
5. Combine controls, with STOP taking priority.
6. Verify emergency power switch and safe stopping behavior.

Do not claim the design is tested until you have actually tested it.
