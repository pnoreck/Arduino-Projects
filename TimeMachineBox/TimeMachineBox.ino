
//**************************************************************//
// Code for using a 74HC595 Shift Register display characters
// on a 7-segment-display
//****************************************************************

//Pin connected to ST_CP of 74HC595
// Arduino Pin 8
int latchPin = 2;

//Pin connected to SH_CP of 74HC595
// Arduino Pin 12
int clockPin = 3;

////Pin connected to DS of 74HC595
// Arduino 11
int dataPin = 0;

// Pin connected to the transistor / output switch
int lightSwitch = 1;

// Turn the light on?
boolean lightOn = false;

// Pin connected to the light sensor
#define lightSensor A2

// Number on the display
int currentDisplayNumber = -1;

// Time between the toggled dot
int blinkDelay = 500;

// Last light value measured in the last loop
int lastLightValue = 0;

// did we had a loop where the light was on?
bool lastRun = false;

// The current number on the display
int currentShifted = 0;

// How often did we blinked the number?
int blinkLoop = 0;


// If we test with the ATMEGA328 we have to change the pins
void setArduinoPins() {

  //Pin connected to ST_CP of 74HC595
  // Arduino Pin 8
  latchPin = 8;

  //Pin connected to SH_CP of 74HC595
  // Arduino Pin 12
  clockPin = 12;

  ////Pin connected to DS of 74HC595
  // Arduino 11
  dataPin = 11;

  // Pin connected to the transistor / output switch
  lightSwitch = 7;

  // Serial.begin(9600);
}

void setup() {

  // setArduinoPins();

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(lightSwitch, OUTPUT);
  pinMode(lightSensor, INPUT);

  // 34 is 0x00 - we clear the display
  shiftToDisplay(34);

  // Let's wait a second
  delay(1000);

}

void loop() {

  int lightValue = analogRead(lightSensor);

  if (lightValue <= 600 && currentDisplayNumber < 0 && lastRun == false) {
    currentDisplayNumber = 9;
    lightOn = true;
    lastRun = true;
  }
  else if (lightValue > 900 && currentDisplayNumber < 7 && currentDisplayNumber >= 0) {
    currentDisplayNumber = 9;
    lightOn = true;
  }
  else if (lightValue > 900 && currentDisplayNumber >= 8) {
    currentDisplayNumber = -1;
    lightOn = false;
    lastRun = true;
  }
  else if (lightValue > 600 && lastRun == true) {
    lastRun = false;
    lightOn = false;
  }
  else if (currentDisplayNumber < 0) {
    lightOn = false;
  }

  digitalWrite(lightSwitch, lightOn);

  if (currentDisplayNumber >= 0 && currentDisplayNumber < 10) {
    // blinkNumber(currentDisplayNumber, 600);
    blinkNumber(currentDisplayNumber, 2);
    if (blinkLoop >= 300) {
      currentDisplayNumber = currentDisplayNumber - 1;
      blinkLoop = 0;
    }
    else {
      blinkLoop++;
    }
  } else {

    // Clear the display
    if (currentShifted != 34) {
      shiftToDisplay(34);
    }

    delay(1000);
  }

}

