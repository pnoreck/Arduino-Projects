
#define REMOTE_CONTROL 8

int helligkeit = 980;
int control_delay = 75;
int sensorValue;

// Setup
void setup() {
  // Serial.begin(9600);
  // tone(8, 4000, 100);
  pinMode(REMOTE_CONTROL, OUTPUT);
  digitalWrite(REMOTE_CONTROL, LOW);
}

void make_picture() {
  digitalWrite(REMOTE_CONTROL, HIGH);
  delay(500);
  digitalWrite(REMOTE_CONTROL, LOW);
}

// Loop
void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);
  // Serial.println(sensorValue);
  if(sensorValue < helligkeit) {
    if(control_delay > 0) {
      delay(control_delay);
    } 
    make_picture();
  }
}

