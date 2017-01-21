
#define voltageFlipPin1 0
#define voltageFlipPin2 1
#define sensorPin A1
#define redLED 3
#define greenLED 4

int green = 950;
int yellow = 900;
int red = 850;

int flipTimer = 1000;
int blinkHelper = 0;

void setup(){
  // Serial.begin(9600);
  pinMode(voltageFlipPin1, OUTPUT);
  pinMode(voltageFlipPin2, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void setLedStatus(int iVal) {
  if(iVal > green) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  
  if(iVal > yellow && iVal <= green) {
    if(blinkHelper == 0) {
      digitalWrite(greenLED, HIGH);
      blinkHelper = 1;
    }
    else {
      digitalWrite(greenLED, LOW);
      blinkHelper = 0;
    }
    digitalWrite(redLED, LOW);
  }

  if(iVal > red && iVal <= yellow) {
    if(blinkHelper == 0) {
      digitalWrite(redLED, HIGH);
      blinkHelper = 1;
    }
    else {
      digitalWrite(redLED, LOW);
      blinkHelper = 0;
    }
    digitalWrite(greenLED, LOW);
  }  

  if(iVal <= red) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
 
}

void setSensorPolarity(boolean flip){
  if(flip){
    digitalWrite(voltageFlipPin1, HIGH);
    digitalWrite(voltageFlipPin2, LOW);
  }else{
    digitalWrite(voltageFlipPin1, LOW);
    digitalWrite(voltageFlipPin2, HIGH);
  }
}


void loop(){
 
  setSensorPolarity(true);
  delay(flipTimer);
  int val1 = analogRead(sensorPin);
  delay(flipTimer);  
  setSensorPolarity(false);
  delay(flipTimer);
  // invert the reading
  int val2 = 1023 - analogRead(sensorPin);
  reportLevels(val1,val2);
}


void reportLevels(int val1,int val2){
  
  int avg = (val1 + val2) / 2;
 
  // String msg = "avg: ";
  // msg += avg;
  // Serial.println(msg);
  
  setLedStatus(avg);

}

