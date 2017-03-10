
// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#define OFF 0x0
#define ON  0x1


// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


void initializeDisplay() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Backlight on
  lcd.setBacklight(ON);
  // clear the screen
  lcd.clear();
  // set the cursor to zero
  lcd.setCursor(0, 0);

  lcd.print("Initilized");
  
  lcd.setCursor(0,1);
  lcd.print(stepsBetweenPictures);
  lcd.print(" / ");
  lcd.print(getPicturesPerRound());
}


