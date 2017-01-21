/**
 * define all constant values
 */
#define RED_LED 6
#define YELLOW_LED 7
#define GREEN_LED 8
#define PIR_SENSOR 2
#define LIGHT_SENSOR A0
#define RELAY 9
#define STARTUP_DELAY 5000
#define DEBUG false


/**
 * 0 = all
 * 1 = green/blue
 * 2 = red/blue
 * 3 = red/green
 * 4 = red
 * 5 = yellow
 * 6 = green
 * 7 = none
 */
int ledPinsRed[]   = {1,0,1,1,1,0,0,0};
int ledPinsYellow[] = {1,1,0,1,0,1,0,0};
int ledPinsGreen[]  = {1,1,1,0,0,0,1,0};

int motionValue = 0;
int lightValue = 0;
int lightSetup = 6;
int oldLightSetup = 0;
int relayStatus = LOW;
int oldRelayStatus = LOW;

unsigned long lastTimeOfMotion = 0;
unsigned long timeSinceMotion = 0;
unsigned long timeToWait = 120000;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);
  
  if(DEBUG == true) {
    Serial.begin(9600);  
  }

  delay(STARTUP_DELAY);
}

void setLedColor(int ledSetup) {
  digitalWrite(RED_LED, ledPinsRed[ledSetup]);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(YELLOW_LED, ledPinsYellow[ledSetup]);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(GREEN_LED, ledPinsGreen[ledSetup]);   // turn the LED on (HIGH is the voltage level)  
}

// the loop function runs over and over again forever
void loop() {
  
  motionValue = digitalRead(PIR_SENSOR);
  lightValue = analogRead(A0);

  if(motionValue == HIGH) {
    lastTimeOfMotion = millis();
    lightSetup = 4;
  }
  
  if(lightSetup == 4 && lightValue < 300) {
    lightSetup = 4;
    relayStatus = HIGH;
  }

  if(lastTimeOfMotion > 0) {
    timeSinceMotion = millis() - lastTimeOfMotion;

    if(timeSinceMotion > timeToWait) {
        lightSetup = 5;
        relayStatus = LOW;
    }

    if(timeSinceMotion > timeToWait * 2) {
      lightSetup = 6;
      timeSinceMotion = 0;
    }

  }

  if(lightSetup != oldLightSetup) {
    setLedColor(lightSetup);
    oldLightSetup = lightSetup;
  }

  if(relayStatus != oldRelayStatus) {
    digitalWrite(RELAY, relayStatus);
    oldRelayStatus = relayStatus;
  }

  delay(100);
  
  if(DEBUG == true) {
    Serial.println(motionValue);
    Serial.println(lightValue);
    Serial.println(timeSinceMotion);
    delay(100);
  }
  
}



