

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

  // 34 = empty
  0,
};


void shiftToDisplay(int mapKey) {

  currentShifted = mapKey;

  // Map the input value to the shift value
  int numberToDisplay = lut[mapKey];

  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
}


// Blink the dot for the number x times
void blinkNumber(int number, int blinkingTimes) {
  for (int i = 0; i < blinkingTimes; i++) {
    shiftToDisplay(number);
    // pause before next value:
    delay(blinkDelay);
    shiftToDisplay(10 + number);
    // pause before next value:
    delay(blinkDelay);
  }
}

