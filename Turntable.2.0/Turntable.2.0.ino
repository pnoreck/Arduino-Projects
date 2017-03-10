
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
#define DEBUG true

// Debug step counter
int loop_count = 0;

// Start and stop the turn table
volatile byte startStopMode = LOW;

// Pin of the input button
const short startButtonPin = 2;

// Steps between the pictures (calculated)
int stepsBetweenPictures = 0;

// Pin of the camera remote
const short cameraPin = 4;


/**
   Initialize the motor shield pins for the stepper motor
*/
void setup() {

  initializeMotor();
  
  pinMode(cameraPin, OUTPUT);
  pinMode(startButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(startButtonPin), startStop, RISING);
  

  initializeDisplay();
 
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

    if (loop_count == getPicturesPerRound()) {
      startStopMode = !startStopMode;
    }
  }

  
}
