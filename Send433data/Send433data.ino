#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int i = 0;

void setup() {
  // Transmitter is connected to Pin 10
  mySwitch.enableTransmit(10);
  // Optional set pulse length
  // mySwitch.setPulseLength(320);
  // Optinal set protocal (default is 1, will work for most outlets)
  mySwitch.setProtocol(2);
  // Optional set number of transmissions repetitions
  // mySwitch.setRepeatTransmit(15);
}

void loop() {
  mySwitch.send(i,24);
  i++;
  delay(1000);
}
