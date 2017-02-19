/**
 * Photography 
 * SETUP Cables on Arduino Motor Shield Rev3
 * A+ = black
 * A- = green
 * B+ = red
 * B- = blue
 */

#define UNDEFINED 666

// Delay between each step
int delaylegnth = 20;

// Current step (can have a value of 0 till 3)
short currentStep = 0;

// 
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

/**
 * Initialize the motor shield pins for the stepper motor
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

}

/**
 * Set the specified step values to all pins
 */
void setStep(short stepToSet) {
  if(stepToSet < 0 || stepToSet > 3) {
   return;
  }

  digitalWrite(9, chA[stepToSet]);
  digitalWrite(8, chB[stepToSet]);

  if(pin3[stepToSet] != UNDEFINED) {
    analogWrite(3, pin3[stepToSet]);
  }

  if(pin11[stepToSet] != UNDEFINED) {
    analogWrite(11, pin11[stepToSet]);
  }
  
  if(pin12[stepToSet] != UNDEFINED) {
    digitalWrite(12, pin12[stepToSet]);
  }

  if(pin13[stepToSet] != UNDEFINED) {
    digitalWrite(13, pin13[stepToSet]);
  }
  
}

void startStop() {
  startStopMode = !startStopMode;
}

void stepForward() {
  currentStep += 1;
  if(currentStep > 3) {
    currentStep = 0;
  }
  setStep(currentStep);
  delay(delaylegnth);
}

void stepBackward() {
  currentStep -= 1;
  if(currentStep < 0) {
    currentStep = 3;
  }
  setStep(currentStep);
  delay(delaylegnth);
}


void loop() {
  if(startStopMode) {
    stepForward();
  }
}
