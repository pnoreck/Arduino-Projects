
#define LightSensor A1
#define LED1 1
#define LED2 3
#define LED3 4

int led_1_setup[]   = {LOW, HIGH, LOW, LOW};
int led_2_setup[]   = {LOW, HIGH, HIGH, LOW};
int led_3_setup[]   = {LOW, HIGH, HIGH, HIGH};

int valOld = 1000;
int valNew = 1000;
int diff = 0;
short firstLoop = 1;
short leds = 3;
short LedSetting = 0;

void setLEDs(short setting) {
  digitalWrite(LED1, led_1_setup[setting]);
  digitalWrite(LED2, led_2_setup[setting]);
  digitalWrite(LED3, led_3_setup[setting]);

  if(setting > 0) {
    delay(15000);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LightSensor, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {

  setLEDs(LedSetting);
  valNew = analogRead(LightSensor);
  diff = valOld - valNew;
  
  if(LedSetting > 0) {
    LedSetting += 1;
  }
  else {
    if(valNew < 300 && diff > 100 && firstLoop == 0) {
      LedSetting += 1;
    }
  }

  if(LedSetting > 3 || valNew > 500) {
    LedSetting = 0;
  }
 
  
  firstLoop = 0;
  valOld = valNew;
  delay(2000);
}
