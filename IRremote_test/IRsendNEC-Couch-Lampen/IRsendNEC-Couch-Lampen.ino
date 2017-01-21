/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;


void sendCode(unsigned long  code) {
  for (int i = 0; i < 10; i++) {
    irsend.sendNEC(code, 32);
    delay(40);
  }
  delay(1000); //5 second delay between each signal burst
}

void setup()
{
}

void loop() {
  // EIN
  sendCode(0xF7C03F); 

  // ROT
  sendCode(0xF720DF); 
  // GRUEN
  sendCode(0xF7A05F); 
  // BLAU
  sendCode(0xF7609F); 
  // WEISS
  sendCode(0xF7E01F);

   // AUS 
  sendCode(0xF740BF); 
}
