
// Motor-Pins definieren / sind auf Shield fest definiert
int motorPin[2] = {3, 11};
int breakPin[2] = {9, 8};
int motorChannel[2] = {12, 13};


// Runde: 75
const int loop_circle_max = 10; // Anzahl Bilder insgesamt
int loop_circle = loop_circle_max;

// Start-Button
const int buttonPin = 2;     // the number of the pushbutton pin

// Runde 350
const int table_turn_duration = 200;

// Runde 122
const int motor_speed = 150;

// Warte
const int wait_before_photo = 2000;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


// Pin 10 ist auf Motor Shield frei und liegt günstig
#define REMOTE_CONTROL 10

// Motorpins für einen Motor definieren
void setupMotorPins(int motor) {
    pinMode(motorChannel[motor], OUTPUT); //Initiates Motor Channel A pin
    pinMode(breakPin[motor], OUTPUT); //Initiates Brake Channel A pin
}

// Richtung Vorwärts für einen Motor definieren
// var motor = 0|1
void setMotorForward(int motor) {
  digitalWrite(motorChannel[motor], HIGH); //Establishes forward direction of Channel A
  digitalWrite(breakPin[motor], LOW);   //Disengage the Brake for Channel A
}

// Richtung Rückwärts für einen Motor defnieren
// var motor = 0|1
void setMotorBackward(int motor) {
  digitalWrite(motorChannel[motor], LOW); //Establishes backward direction of Channel A
  digitalWrite(breakPin[motor], LOW);   //Disengage the Brake for Channel A
}

// Einen Motor anhalten
void stopMotor(int motor) {
  digitalWrite(breakPin[motor], HIGH); //Eengage the Brake for Channel A
}

// Geschwindigkeit für einen Motor setzen
void setMotorSpeed(int motor, int speed) {

    if(speed >= 0) {
        setMotorForward(motor);
    }
    else {
        setMotorBackward(motor);
        speed = -speed;
    }
    
    if(speed < 0) speed = 0;
    if(speed > 255) speed = 255;
    
    analogWrite(motorPin[motor], speed);
}

// Fernauslöser drücken
void make_picture() {
  digitalWrite(REMOTE_CONTROL, HIGH);
  delay(500);
  digitalWrite(REMOTE_CONTROL, LOW);
}

void check_for_loop() {
  
  if(loop_circle >= loop_circle_max) {
    return;
  }
  
  while(loop_circle <= loop_circle_max) {
    loop_circle++;
    
    // Forward @ full speed
    stopMotor(0);
    delay(500);

    setMotorSpeed(0, motor_speed);
    delay(table_turn_duration);

    stopMotor(0);
    delay(wait_before_photo);

    make_picture();
  }
  
}


// Setup Methode mit allen wichtigen Initialisierungen
void setup() {
  setupMotorPins(0);
  setupMotorPins(1);
  
  stopMotor(0);
  stopMotor(1);
  
  pinMode(REMOTE_CONTROL, OUTPUT);
  digitalWrite(REMOTE_CONTROL, LOW);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
}


// Endless Loop mit Funktionalität
void loop(){
 
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    loop_circle = 0;
  }
  loop_circle = 0;
  check_for_loop();
}
