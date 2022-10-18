#include <SoftwareSerial.h>
#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale;

float calibration_factor = 447; 
// Attach the serial enabld LCD's RX line to digital pin 11
SoftwareSerial LCD(10, 11); // Arduino SS_RX = pin 10 (unused), Arduino SS_TX = pin 11 

void setup()
{
  LCD.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
}

void loop()
{
  // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  // clear display by sending spaces
  LCD.write("                  ");
  LCD.write("                  "); 
  

  // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  
  LCD.print(scale.get_units(),2);
  LCD.print(" g");



  while (scale.get_units() > 200){
    LCD.write("                  ");
    LCD.write("                  "); 

    LCD.write(254); 
    LCD.write(128);

    LCD.print("Zu schwer!");

    LCD.write("                  ");
    LCD.write("                  "); 
    
  }
  delay(50);
  
}
