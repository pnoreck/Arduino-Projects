
#define RED_LED 6
#define GREEN_LED 7
#define BLUE_LED 8

#define DELAY 1000

int ledPinsRed[]   = {1,0,1,1,1,0,0,0};
int ledPinsGreen[] = {1,1,0,1,0,1,0,0};
int ledPinsBlue[]  = {1,1,1,0,0,0,1,0};

int i = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}


void setLedColor(int ledSetup) {
  digitalWrite(RED_LED, ledPinsRed[ledSetup]);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(GREEN_LED, ledPinsGreen[ledSetup]);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(BLUE_LED, ledPinsBlue[ledSetup]);   // turn the LED on (HIGH is the voltage level)  
}

// the loop function runs over and over again forever
void loop() {

  setLedColor(i);
  delay(DELAY);               // wait for a second
  i += 1;
  
  if(i > 7) {
      i = 0;
      delay(5000);
  }
  
}


