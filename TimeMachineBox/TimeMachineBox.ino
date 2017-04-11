
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
boolean lightOn = false;

// Pin connected to the light sensor
#define lightSensor A2

int currentDisplayNumber = 0;
int blinkDelay = 500;
int lightValue = 0;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(lightSwitch, OUTPUT);
  pinMode(lightSensor, INPUT);
}

int lut[] = {

  // 0-9 = 0-9
  243,  // 0
  96,   // 1
  213,  // 2
  244,  // 3
  102,  // 4
  182,  // 5
  183,  // 6
  224,  // 7
  247,  // 8
  246,  // 9

  // 10-19 = 0.-9.
  251,  // 0.
  104,  // 1.
  221,  // 2.
  252,  // 3.
  110,  // 4.
  190,  // 5.
  191,  // 6.
  232,  // 7.
  255,  // 8.
  254,  // 9.

  // 20-33 char
  231,  // A    20
  239,  // A.
  151,  // E
  159,  // E.
  39,   // h
  103,  // H    25
  111,  // H.
  112,  // J
  121,  // J.
  115,  // U
  123,  // U.   30
  53,   // o
  198,  // °
  148,  // burger

  // 35 = empty
  0,
};


void shiftToDisplay(int mapKey) {

  int numberToDisplay = lut[mapKey];

  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
}


void blinkNumber(int number, int blinkingTimes) {
  for (int i = 0; i < blinkingTimes; i++) {
    shiftToDisplay(9 - number);
    // pause before next value:
    delay(blinkDelay);
    shiftToDisplay(19 - number);
    // pause before next value:
    delay(blinkDelay);
  }
}


void loop() {
  
  lightValue = 1024 - analogRead(lightSensor);
  /*
  if(lightValue >= 900) {
    number = 9;
  } else if(lightValue >= 800 && lightValue < 900) {
    number = 8;
  } else if(lightValue >= 700 && lightValue < 800) {
    number = 7;
  } else if(lightValue >= 600 && lightValue < 700) {
    number = 6;
  } else if(lightValue >= 500 && lightValue < 600) {
    number = 5;
  } else if(lightValue >= 400 && lightValue < 500) {
    number = 4;
  } else if(lightValue >= 300 && lightValue < 400) {
    number = 3;
  } else if(lightValue >= 200 && lightValue < 300) {
    number = 2;
  } else if(lightValue >= 100 && lightValue < 200) {
    number = 1;
  } else {
    number = 0;
  }
  */
  
  if(lightValue < 300 && currentDisplayNumber < 0) {
    currentDisplayNumber = 9;
    lightOn = true;
  }
  else if(lightValue > 900 && currentDisplayNumber < 7) {
    currentDisplayNumber = 9;
    lightOn = true;
  }
  else if(lightValue > 900 && currentDisplayNumber >= 8) {
    currentDisplayNumber = -1;
    lightOn = false;
  }
  else if(lightValue < 0) {
    lightOn = false;
  }
  
  if(currentDisplayNumber >= 0 && currentDisplayNumber < 10) {
    // blinkNumber(currentDisplayNumber, 60);
    blinkNumber(currentDisplayNumber, 2);
    digitalWrite(lightSwitch, lightOn);
    currentDisplayNumber = currentDisplayNumber - 1;
  }
  else {
    shiftToDisplay(35);
  }
  
  delay(100);
}

