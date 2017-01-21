

#include <IRremote.h>

IRsend irsend;

int dataOn = 0xF7C03F;
int dataOff = 0xF740BF;


void setup()
{
}

void loop() {
  irsend.sendLG(dataOn, sizeof(dataOn));
  delay(5000); //5 second delay between each signal burst
  irsend.sendLG(dataOff, sizeof(dataOn));
  delay(5000); //5 second delay between each signal burst
}
