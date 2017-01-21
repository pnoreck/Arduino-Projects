
#define redLED 3
#define greenLED 4

int flipTimer = 1000;
int blinkHelper = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(blinkHelper == 1) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    blinkHelper = 0;
  }else{
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    blinkHelper = 1;
  }
  delay(flipTimer);
}
