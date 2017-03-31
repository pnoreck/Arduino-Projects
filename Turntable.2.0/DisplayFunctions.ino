
// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

#define ON 0x1

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

  lcd.print("Steps | Pics/u");

  lcd.setCursor(0, 1);
  lcd.print(stepsBetweenPictures);
  
  lcd.print("    | ");
  lcd.print(getPicturesPerRound());
  
}

void checkForButtons() {
  
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);

    switch(buttons) {
      
      case BUTTON_UP:
        lcd.print("UP ");
        break;
        
      case BUTTON_DOWN:
        lcd.print("DOWN ");
        break;
        
      case BUTTON_RIGHT:
        lcd.print("RIGHT ");
        break;
        
      case BUTTON_LEFT:
        lcd.print("LEFT ");
        break;
        
      case BUTTON_SELECT:
        lcd.print("SELECT ");
        startStop();
        
        if (startStopMode) {
          lcd.print("START ");
        }
        else {
          lcd.print("STOP ");
        }
        break;
        
      default:
        lcd.print("Default");
        break;
        
    }
  }
}

