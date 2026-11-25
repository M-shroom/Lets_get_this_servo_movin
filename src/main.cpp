
#include <Arduino.h>
#include <ESP32Servo.h>

// Servo signal connected to XIAO D0
const int servoPin = D0;

Servo turnoutServo;

// Starting positions - we will calibrate these
const int LEFT_POSITION  = 75;
const int RIGHT_POSITION = 115;

void moveServo(int position) {
    turnoutServo.write(position);

    Serial.print("Moving to ");
    Serial.print(position);
    Serial.println(" degrees");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    turnoutServo.setPeriodHertz(50);
    turnoutServo.attach(servoPin, 1000, 2000);

    // Start in the middle
    moveServo(90);

    Serial.println();
    Serial.println("LEGO Track Switch Controller");
    Serial.println("----------------------------");
    Serial.println("L = Left");
    Serial.println("R = Right");
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();

        switch (command) {
            case 'L':
            case 'l':
                moveServo(LEFT_POSITION);
                break;

            case 'R':
            case 'r':
                moveServo(RIGHT_POSITION);
                break;

            default:
                break;
        }
    }
}
