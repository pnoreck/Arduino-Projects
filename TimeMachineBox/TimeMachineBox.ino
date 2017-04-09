
//**************************************************************//
// Code for using a 74HC595 Shift Register display characters
// on a 7-segment-display
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int blinkDelay = 500;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
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


};


void shiftToDisplay(int mapKey) {

  int numberToDisplay = lut[mapKey];
  Serial.println(mapKey);
  Serial.println(numberToDisplay);

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
  for (int number = 0; number <= 9; number++) {
    blinkNumber(number, 60);
  }
  delay(500);
}

