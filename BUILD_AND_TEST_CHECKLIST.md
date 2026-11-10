# Build and Test Checklist

Use this as a record of real work. Tick items only after you have completed them.

## Design checks
- [ ] Confirm exact ESP32 DevKit model and pinout.
- [ ] Confirm APDS-9960 breakout model and voltage requirements.
- [ ] Measure actual motor body, gearbox, shaft, and mounting features.
- [ ] Measure wheel diameter, width, and shaft fit.
- [ ] Measure caster plate and all four hole centres (do not assume a square pattern).
- [ ] Confirm battery type, voltage, current rating, and holder dimensions.
- [ ] Confirm L298N board dimensions and mounting-hole locations.
- [ ] Check chassis balance, ground clearance, wheel alignment, and cable clearance.

## Electronics tests (motors disconnected)
- [ ] Upload firmware and open Serial Monitor.
- [ ] Confirm APDS-9960 is detected.
- [ ] Confirm gesture readings.
- [ ] Scan for BLE device `TITAN-HAND-CAR`.
- [ ] Connect and write `STOP`; confirm reply notification.
- [ ] Test each BLE command with motor power disconnected.

## Motor tests (wheels lifted)
- [ ] Verify common ground and supply polarity.
- [ ] Test left motor direction at low power.
- [ ] Test right motor direction at low power.
- [ ] Test STOP and physical power switch.
- [ ] Check driver temperature and motor current.

## Combined tests
- [ ] Test gesture movement pulses.
- [ ] Test phone speech-to-text -> BLE commands.
- [ ] Confirm STOP overrides movement.
- [ ] Confirm car stops after each 300 ms pulse.
- [ ] Test safely in a clear area at low speed.

Do not mark any item complete unless you actually performed the test.
