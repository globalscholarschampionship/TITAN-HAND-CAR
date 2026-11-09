/*
  TITAN HAND CAR — preliminary ESP32 starter sketch
  Gesture sensor: APDS-9960 (I2C)
  Motor driver: L298N

  IMPORTANT:
  - This is starter firmware, not hardware-tested.
  - Confirm your exact ESP32 board, APDS-9960 breakout, motor driver,
    motor voltage/current, and wiring before powering anything.
  - Install the "Adafruit APDS9960" library in Arduino IDE.
  - Test with the motors disconnected first.
*/

#include <Wire.h>
#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

// APDS-9960 I2C pins on a typical ESP32 DevKit
const int I2C_SDA = 21;
const int I2C_SCL = 22;

// L298N control pins — match these to your actual wiring
const int ENA = 25;
const int IN1 = 27;
const int IN2 = 14;
const int ENB = 26;
const int IN3 = 18;
const int IN4 = 19;

const int MOTOR_SPEED = 170;             // 0–255; tune only after safe testing
const unsigned long MOVE_TIME_MS = 300;  // short pulse, then automatic stop

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  Wire.begin(I2C_SDA, I2C_SCL);

  if (!apds.begin()) {
    Serial.println("APDS-9960 not found. Check 3.3V, GND, SDA and SCL.");
    while (true) {
      stopMotors();
      delay(1000);
    }
  }

  apds.enableProximity(false);
  apds.enableColor(false);
  apds.enableGesture(true);

  Serial.println("TITAN HAND CAR ready. Motors remain stopped between gestures.");
}

void loop() {
  if (apds.gestureValid()) {
    int gesture = apds.readGesture();

    switch (gesture) {
      case APDS9960_UP:
        Serial.println("UP: forward");
        moveForward();
        delay(MOVE_TIME_MS);
        break;

      case APDS9960_DOWN:
        Serial.println("DOWN: reverse");
        moveBackward();
        delay(MOVE_TIME_MS);
        break;

      case APDS9960_LEFT:
        Serial.println("LEFT: turn left");
        turnLeft();
        delay(MOVE_TIME_MS);
        break;

      case APDS9960_RIGHT:
        Serial.println("RIGHT: turn right");
        turnRight();
        delay(MOVE_TIME_MS);
        break;

      default:
        Serial.println("Unknown gesture: stop");
        break;
    }

    stopMotors();
  }

  delay(20);
}
