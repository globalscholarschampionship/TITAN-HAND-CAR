/*
  TITAN HAND CAR — BLE voice + APDS-9960 gesture starter firmware

  Voice:
    iPhone speech-recognition app -> BLE write characteristic -> ESP32
    Commands: FORWARD, BACKWARD, LEFT, RIGHT, STOP

  Gestures:
    APDS-9960 swipe up/down/left/right

  Safety:
    Short 300 ms movement pulses, then stop.
    STOP command has priority.
    This is starter code and has not been hardware-tested.

  Libraries:
    - ESP32 Arduino core (BLE support)
    - Adafruit APDS9960 library
*/

#include <Wire.h>
#include <Adafruit_APDS9960.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

Adafruit_APDS9960 apds;

// L298N pins
const int ENA = 25;
const int IN1 = 27;
const int IN2 = 14;
const int ENB = 26;
const int IN3 = 18;
const int IN4 = 19;

const unsigned long MOVE_PULSE_MS = 300;
unsigned long stopAt = 0;
bool moving = false;

// Nordic-UART-style BLE UUIDs
#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define RX_CHARACTERISTIC  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define TX_CHARACTERISTIC  "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

BLECharacteristic *txCharacteristic = nullptr;

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  moving = false;
  stopAt = 0;
}

void driveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 170); analogWrite(ENB, 170);
  moving = true; stopAt = millis() + MOVE_PULSE_MS;
}

void driveBackward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 170); analogWrite(ENB, 170);
  moving = true; stopAt = millis() + MOVE_PULSE_MS;
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 170); analogWrite(ENB, 170);
  moving = true; stopAt = millis() + MOVE_PULSE_MS;
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 170); analogWrite(ENB, 170);
  moving = true; stopAt = millis() + MOVE_PULSE_MS;
}

void runCommand(String command) {
  command.trim();
  command.toUpperCase();

  if (command.indexOf("STOP") >= 0) {
    stopMotors();
    return;
  }
  if (command.indexOf("FORWARD") >= 0) driveForward();
  else if (command.indexOf("BACKWARD") >= 0 || command.indexOf("REVERSE") >= 0) driveBackward();
  else if (command.indexOf("LEFT") >= 0) turnLeft();
  else if (command.indexOf("RIGHT") >= 0) turnRight();
}

class RXCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *characteristic) override {
    std::string value = characteristic->getValue();
    if (!value.empty()) {
      String command = String(value.c_str());
      runCommand(command);
      if (txCharacteristic) {
        String reply = "Received: " + command;
        txCharacteristic->setValue(reply.c_str());
        txCharacteristic->notify();
      }
    }
  }
};

void setupBLE() {
  BLEDevice::init("TITAN-HAND-CAR");
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);

  BLECharacteristic *rx = service->createCharacteristic(
    RX_CHARACTERISTIC,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );
  rx->setCallbacks(new RXCallbacks());

  txCharacteristic = service->createCharacteristic(
    TX_CHARACTERISTIC,
    BLECharacteristic::PROPERTY_NOTIFY
  );
  txCharacteristic->addDescriptor(new BLE2902());

  service->start();
  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  stopMotors();

  Wire.begin(21, 22);
  if (!apds.begin()) {
    Serial.println("APDS-9960 not found. Check wiring; BLE voice remains available.");
  } else {
    apds.enableProximity(false);
    apds.enableGesture(true);
    Serial.println("APDS-9960 ready.");
  }

  setupBLE();
  Serial.println("BLE ready: TITAN-HAND-CAR");
}

void loop() {
  // Automatic stop after each short movement pulse.
  if (moving && (long)(millis() - stopAt) >= 0) {
    stopMotors();
  }

  // Gesture input. A gesture pulse also stops automatically.
  if (apds.gestureValid()) {
    uint8_t gesture = apds.readGesture();
    switch (gesture) {
      case APDS9960_UP:    driveForward();  break;
      case APDS9960_DOWN:  driveBackward(); break;
      case APDS9960_LEFT:  turnLeft();      break;
      case APDS9960_RIGHT: turnRight();     break;
      default: break;
    }
  }

  delay(10);
}
