/**
   Photography
   SETUP Cables on Arduino Motor Shield Rev3
   A+ = black
   A- = green
   B+ = red
   B- = blue

   4006 steps for one round
*/

// We define undefined with 666
#define UNDEFINED 666

// Debug mode on / off
#define DEBUG false

// Total steps for one round
#define ONE_ROUND 4004

// Delay between each step
int delaylegnth = 20;

// Current step (can have a value of 0 till 3)
short currentStep = 0;

// Debug step counter
int loop_count = 0;

// Start and stop the turn table
volatile byte startStopMode = LOW;

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

// Pin of the camera remote
const short cameraPin = 4;

// Pin of the input button
const short startButtonPin = 2;

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

// Steps between the pictures (calculated)
int stepsBetweenPictures = 0;

/**
   Initialize the motor shield pins for the stepper motor
*/
void setup() {

  //establish motor direction toggle pins
  pinMode(12, OUTPUT); //CH A -- HIGH = forwards and LOW = backwards???
  pinMode(13, OUTPUT); //CH B -- HIGH = forwards and LOW = backwards???

  //establish motor brake pins
  pinMode(9, OUTPUT); //brake (disable) CH A
  pinMode(8, OUTPUT); //brake (disable) CH B

  setStep(currentStep);

  pinMode(cameraPin, OUTPUT);
  pinMode(startButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startButtonPin), startStop, RISING);

  stepsBetweenPictures = ONE_ROUND / picutresPerRound[indexPicturesPerRound];

  if (DEBUG) {
    Serial.begin(9600);
    delay(1000);
    Serial.print("Initilized with ");
    Serial.print(stepsBetweenPictures);
    Serial.print(" steps between ");
    Serial.print(picutresPerRound[indexPicturesPerRound]);
    Serial.println(" pictures per round.");
  }

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
   Start / stop trigger function
*/
void startStop() {
  startStopMode = !startStopMode;
  if (startStopMode) {
    // reset debug loop value
    loop_count = 0;
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

/**
   Press the remote control and make a picture
*/
void makePicture() {
  digitalWrite(cameraPin, HIGH);
  delay(500);
  digitalWrite(cameraPin, LOW);
}


/**
   The endless loop.

   When startStopMode is false we just loop and do nothing. But when the Start Button was pressed
   the loop_count will zero and we do the full round. If the round is over or some pressed the stop
   button we loop again without doing anything.
*/
void loop() {
  if (startStopMode) {
    doStepsForward(stepsBetweenPictures);
    loop_count++;

    if (DEBUG) {
      Serial.println(loop_count);
    }

    delay(200);
    makePicture();
    delay(500);

    if (loop_count == picutresPerRound[indexPicturesPerRound]) {
      startStopMode = !startStopMode;
    }
  }
}
