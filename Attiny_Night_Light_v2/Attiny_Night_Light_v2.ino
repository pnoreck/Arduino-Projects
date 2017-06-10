
//**************************************************************//
// Code for using a 74HC595 Shift Register display characters
// on a 7-segment-display
//****************************************************************

//Pin connected to ST_CP of 74HC595
// int latchPin = 8;  // Arduino
int latchPin = 1;  // Attiny

//Pin connected to SH_CP of 74HC595
// int clockPin = 12;
int clockPin = 2;

////Pin connected to DS of 74HC595
// int dataPin = 11;
int dataPin = 0;

int blinkDelay = 500;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // Serial.begin(9600);
}

int lut[] = {

  0,    // 0
  1,    // 1
  3,    // 2
  131,  // 3
  195,  // 4
  227,  // 5
  243,  // 6
  251,  // 7
  255,  // 8

};


void shiftToDisplay(int mapKey) {

  int numberToDisplay = lut[mapKey];
  // Serial.println(mapKey);
  // Serial.println(numberToDisplay);

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

void shiftOutNumber(int numberToDisplay) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, numberToDisplay);
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPin, HIGH);
  // Serial.println(numberToDisplay);
}

void shiftOutMapped(int mapKey) {
  int numberToDisplay = lut[mapKey];
  shiftOutNumber(numberToDisplay);
}

void loop() {
  /*
    for (int number = 0; number <= 9; number++) {
    blinkNumber(number, 60);
    }
  */
/*
  for (int number = 0; number <= 255; number++) {
    shiftOutNumber(number);
    delay(350);
  }
  */

  for (int number = 0; number <= 8; number++) {
    shiftOutMapped(number);
    delay(50);
  }
  
  for (int number = 8; number >= 0; number--) {
    shiftOutMapped(number);
    delay(1500);
  }

  delay(1000); 
}

