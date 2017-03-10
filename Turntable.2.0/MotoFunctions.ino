

// Delay between each step
int delaylegnth = 20;

// PIN 9
int chA[]   = {LOW, HIGH, LOW, HIGH};

// PIN 8
int chB[]   = {HIGH, LOW, HIGH, LOW};

//Moves CH A
int pin3[]  = {255, UNDEFINED, 255, UNDEFINED};

//Moves CH B
int pin11[] = {UNDEFINED, 255, UNDEFINED, 255};

//Sets direction of CH A
int pin12[] = {HIGH, UNDEFINED, LOW, UNDEFINED};

//Sets direction of CH B
int pin13[] = {UNDEFINED, HIGH, UNDEFINED, LOW};

// Current step (can have a value of 0 till 3)
short currentStep = 0;


// Pictures during one round
short indexPicturesPerRound = 22;
short picutresPerRound[] = {

  2,  // 0 (0)
  3,  // 1 (-1)
  4,  // 2 (0)
  5,  // 3 (-1)
  6,  // 4 (2)
  7,  // 5 (0)
  9,  // 6 (-1)
  11, // 7 (0)
  13, // 8 (0)
  14, // 9 (0)
  15, // 10 (-1)
  22, // 11 (0)
  23, // 12 (2)
  26, // 13 (0)
  28, // 14 (0)
  29, // 15 (2)
  44, // 16 (0)
  45, // 17 (-1)
  46, // 18 (2)
  52, // 19 (0)
  58, // 20 (2)
  69, // 21 (2)
  77, // 22 (0)
  87, // 23 (2)
  89, // 24 (-1)
  91, // 25 (0)
  138, // 26 (2)
  143, // 27 (0)
  154, // 28 (0)
  174, // 29 (2)
  182, // 30 (0)
  267, // 31 (-1)
  286, // 32 (0)
};


// Total steps for one round
#define ONE_ROUND 4004

void initializeMotor() {
  
  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards???

  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B

  setStep(currentStep);

  stepsBetweenPictures = ONE_ROUND / picutresPerRound[indexPicturesPerRound];

}

/**
   Set the specified step values to all pins
*/
void setStep(short stepToSet) {
  if (stepToSet < 0 || stepToSet > 3) {
    return;
  }

  digitalWrite(9, chA[stepToSet]);
  digitalWrite(8, chB[stepToSet]);

  if (pin3[stepToSet] != UNDEFINED) {
    analogWrite(3, pin3[stepToSet]);
  }

  if (pin11[stepToSet] != UNDEFINED) {
    analogWrite(11, pin11[stepToSet]);
  }

  if (pin12[stepToSet] != UNDEFINED) {
    digitalWrite(12, pin12[stepToSet]);
  }

  if (pin13[stepToSet] != UNDEFINED) {
    digitalWrite(13, pin13[stepToSet]);
  }

}

/**
   Do one step forward
*/
void stepForward() {
  currentStep += 1;
  if (currentStep > 3) {
    currentStep = 0;
  }
  setStep(currentStep);
  delay(delaylegnth);
}


/**
   Do one step backward
*/
void stepBackward() {
  currentStep -= 1;
  if (currentStep < 0) {
    currentStep = 3;
  }
  setStep(currentStep);
  delay(delaylegnth);
}


/**
   Do the specified amount of steps forward
*/
void doStepsForward(int steps) {
  for (int i = 0; i < steps; i++) {
    stepForward();

    if (DEBUG) {
      Serial.print("var i = ");
      Serial.println(i);
    }
  }
}


int getPicturesPerRound() {
  return picutresPerRound[indexPicturesPerRound];
}

