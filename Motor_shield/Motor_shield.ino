int motorPin[2] = {3, 11};
int breakPin[2] = {9, 8};
int motorChannel[2] = {12, 13};

void setupMotorPins(int motor) {
    pinMode(motorChannel[motor], OUTPUT); //Initiates Motor Channel A pin
    pinMode(breakPin[motor], OUTPUT); //Initiates Brake Channel A pin
}

void setMotorForward(int motor) {
  digitalWrite(motorChannel[motor], HIGH); //Establishes forward direction of Channel A
  digitalWrite(breakPin[motor], LOW);   //Disengage the Brake for Channel A
}

void setMotorBackward(int motor) {
  digitalWrite(motorChannel[motor], LOW); //Establishes backward direction of Channel A
  digitalWrite(breakPin[motor], LOW);   //Disengage the Brake for Channel A
}

void stopMotor(int motor) {
  digitalWrite(breakPin[motor], HIGH); //Eengage the Brake for Channel A
}

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

void setup() {
  setupMotorPins(0);
  setupMotorPins(1);
}

void loop(){

  // Forward @ full speed
  stopMotor(0);
  delay(500);
  setMotorSpeed(0, 125);
  delay(500);
  
  /*
  stopMotor(1);
  setMotorSpeed(0, 125);
  delay(500);
  
  //backward @ half speed
  stopMotor(0);
  setMotorSpeed(1, -123);
  delay(500);
  
  stopMotor(1);
  setMotorSpeed(0, -123);
  delay(500);
  */
}
