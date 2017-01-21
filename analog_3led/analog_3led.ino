
#define RED_LED 8
#define YELLOW_LED 9
#define GREEN_LED 10

#define DELAY 25
#define STEP_RED 5
#define STEP_YELLOW 5
#define STEP_GREEN 5

int hell_red = 0;
int hell_yellow = 255;
int hell_green = 0;

int richt_red = 1;
int richt_yellow = 0;
int richt_green = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  analogWrite(RED_LED, hell_red);   // turn the LED on (HIGH is the voltage level)
  analogWrite(YELLOW_LED, hell_yellow);   // turn the LED on (HIGH is the voltage level)
  analogWrite(GREEN_LED, hell_green);   // turn the LED on (HIGH is the voltage level)

  if(richt_red == 1) {
    hell_red += STEP_RED;
  }
  else {
    hell_red -= STEP_RED;
  }
  
  if(richt_yellow == 1) {
    hell_yellow += STEP_YELLOW;
  }
  else {
    hell_yellow -= STEP_YELLOW;
  }
  
  if(hell_red == 0 || hell_red == 255) {
    richt_red *= -1;
  }
  if(hell_yellow == 0 || hell_yellow == 255) {
    richt_yellow *= -1;
  }
 
  delay(DELAY);               // wait for a second
  
}
