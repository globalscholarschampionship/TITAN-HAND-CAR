# TITAN HAND CAR — Wiring and Pin Map (starter)

## ESP32 to APDS-9960
| APDS-9960 breakout | ESP32 |
|---|---|
| VIN / VCC | 3V3, only if the breakout supports 3.3 V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| INT | Not connected in starter firmware |

Some breakout boards accept 5 V on VIN because they include regulation/level shifting; others do not. Read the exact board documentation. Do not assume all APDS-9960 boards are identical.

## ESP32 to L298N
| L298N | ESP32 |
|---|---|
| ENA | GPIO 25 |
| IN1 | GPIO 27 |
| IN2 | GPIO 14 |
| ENB | GPIO 26 |
| IN3 | GPIO 18 |
| IN4 | GPIO 19 |
| GND | Common GND |

Remove ENA/ENB jumpers only if your particular L298N board uses jumpers to enable those pins and you intend to control speed with PWM. Board layouts vary.

## Motors and power
- Left motor: L298N OUT1 / OUT2.
- Right motor: L298N OUT3 / OUT4.
- Motor battery positive: L298N motor supply input (often labelled `12V` or `Vs`).
- Motor battery negative: L298N GND.
- ESP32 GND, sensor GND, and driver GND must share a common ground.
- Power the ESP32 through its USB input or a suitable regulated supply. Do not connect the motor battery directly to the ESP32 3V3 pin.
- Fit a physical master switch in the battery supply path. Select wiring and fuse protection appropriate to the battery and motor current.

## BLE voice-control data
The firmware advertises a BLE UART-like service:
- Service UUID: `6E400001-B5A3-F393-E0A9-E50E24DCCA9E`
- Write characteristic (phone -> ESP32): `6E400002-B5A3-F393-E0A9-E50E24DCCA9E`
- Notify characteristic (ESP32 -> phone): `6E400003-B5A3-F393-E0A9-E50E24DCCA9E`

The iPhone app must perform speech recognition and write command text to the write characteristic. Send one of:
`FORWARD`, `BACKWARD`, `LEFT`, `RIGHT`, `STOP`.

## Important electrical checks before power-up
1. Verify your ESP32 board's logic voltage and pinout.
2. Verify the exact APDS-9960 breakout supply and I2C voltage requirements.
3. Verify TT motor rated voltage and stall current.
4. Verify the L298N current and thermal limits; it has significant voltage drop and can overheat.
5. Verify battery voltage/current capability and polarity.
6. Never power motors from the ESP32 3V3 pin.
7. Test with wheels lifted and a physical way to disconnect power.
