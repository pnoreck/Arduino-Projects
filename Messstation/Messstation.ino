// ----------------------------------------------
// Indoor weather station
// ----------------------------------------------

// ----------------------------------------------
// Sendemodul
#include "RCSwitch.h"
RCSwitch mySwitch = RCSwitch();

// ----------------------------------------------
// Air quality sensor
#include "AirQuality.h"
#include "Arduino.h"
AirQuality airqualitysensor;
int current_quality = -1;

// ----------------------------------------------
// Temp & Humidity Sensor
#include "DHT.h"

#define DHTPIN A1
#define LIGHT A2
#define LED 0

// Uncomment whatever type you're using!
// #define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// ----------------------------------------------
// #include "LowPower.h"


/**
*/
void setup() {

  // ----------------------------------------------
  // Serial output
  // Serial.begin(9600);

  // ----------------------------------------------
  // init Air sensor
  airqualitysensor.init(14);

  // ----------------------------------------------
  // init temp & humidity sensor
  dht.begin();

  // ----------------------------------------------
  // Sender modul
  // ----------------------------------------------
  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(10);

  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(2);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}


/**
*/
void loop() {

  digitalWrite(LED, HIGH);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int sensorValue = analogRead(LIGHT);

  current_quality = airqualitysensor.slope();
  if (current_quality >= 0)// if a valid data returned.
  {
    /*
    if (current_quality == 0)
      Serial.println("High pollution! Force signal active");
    else if (current_quality == 1)
      Serial.println("High pollution!");
    else if (current_quality == 2)
      Serial.println("Low pollution!");
    else if (current_quality == 3)
      Serial.println("Fresh air");
      */

    /* See Example: TypeA_WithDIPSwitches */
    mySwitch.send(1100000 + current_quality, 24);

  }

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    // Serial.println("Failed to read from DHT");
  }
  else
  {
    /*
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
    Serial.print("Light: ");
    Serial.println(sensorValue);
    */
    
    mySwitch.send(1200000 + (h * 100), 24);
    mySwitch.send(1300000 + (t * 100), 24);

  }

  mySwitch.send(1400000 + sensorValue, 24);
  
  digitalWrite(LED, LOW);
  
  delay(60000);
}


ISR(TIMER1_OVF_vect) {

  //set 2 seconds as a detected duty
  if (airqualitysensor.counter == 61) {
    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = analogRead(A0);
    airqualitysensor.counter = 0;
    airqualitysensor.timer_index = 1;
    PORTB = PORTB ^ 0x20;
  } else {
    airqualitysensor.counter++;
  }

}
