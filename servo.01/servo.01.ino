#include <Servo.h>
Servo myServo;

// Licht-Sensor
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

// Onboard LED
const int ledPin = 13;
void setupLED() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void LedOn() {
  digitalWrite(ledPin, HIGH);    
}

void LedOff() {
  digitalWrite(ledPin LOW);
}

// Servo Motor
int const servoPin = 9;
int angle;
int angles[] = {1, 45, 90, 135, 165};

// Setup
void setup() {
  myServo.attach(servoPin);
  tone(8, 4000, 100);
  myServo.write(1);
  delay(3000);
}

// Loop
void loop() {
  // put your main code here, to run repeatedly:
  angle += 1;
  if(angle > 4) {
    angle = 0;
    tone(8, 2000, 100);
  }
  
  myServo.write(angles[angle]);
  delay(2500);
}
