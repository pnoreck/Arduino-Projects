const int PIRSensor = 2;
const int ledPin = 13;
int sensorValue = 0;

int sensorLow = 1023;
int sensorHigh = 0;

void setup() {
 pinMode(PIRSensor, INPUT);
 pinMode(ledPin, OUTPUT);
 
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
  
  while(millis() < 5000) {
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if(sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  
  digitalWrite(ledPin, LOW); 
 
}

void loop(){
 sensorValue = digitalRead(PIRSensor);

 if (sensorValue == HIGH) {
 digitalWrite(ledPin, HIGH);
 }
 else {
 digitalWrite(ledPin, LOW); }
 
  sensorValue = analogRead(A0);
  Serial.println(sensorValue); 
}
