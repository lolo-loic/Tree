//   |-----|-----------------------|---------------------------------------------------------------
//   | Pin#| Use                   |  Notes
//   |-----|-----------------------|---------------------------------------------------------------
//   | 0   |                    
//   | 1   |                    
//   | 2   |  Capacitive touch send                          
//   | 3   |     
//   | 4   |  Capacitive touch receive
//   | 5   | 
//   | 6   |
//   | 7   |
//   |     |
//   | 8   |
//   | 9   |  Red RGB pin
//   | 10  |  Green RGB pin
//   | 11  |  Blue RGB pin
//   | 12  |                      
//   | 13  |  Relay                     
//   |-----|------------------------|----------------------------------------------------------------
//   | A0  |                
//   | A1  |  
//   | A2  |  
//   | A3  |  
//   | A4  |  
//   | A5  |  
//   |-----|------------------------|----------------------------------------------------------------


//-------------------------Includes-----------------------------
#include <CapacitiveSensor.h>
#include "RGBTools.h"

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

RGBTools rgb(9,10,11);       // set RGB Pins
bool state = 0;

//---------------------------SETUP------------------------------
void setup()
{
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);
  Serial.print("SETUP... ");
  
  pinMode(13, OUTPUT);
  pinMode(A0,INPUT);
  
  Serial.println("Finished SETUP. ");
  
}


//---------------------------MAIN------------------------------
void loop()
{
  long start = millis();
  long total1 =  cs_4_2.capacitiveSensor(30);
  
  if (total1 > 200) {
    state = 1;
    digitalWrite(13, state);
    Serial.print("    User touched! ");
    Serial.print(" State: ");
    Serial.print(state);

   while(state) {
       unsigned long startMillis= millis();  // Start of sample window
       unsigned int peakToPeak = 0;   // peak-to-peak level
     
       unsigned int signalMax = 0;
       unsigned int signalMin = 1024;
     
//       // collect data for 50 mS
//       while (millis() - startMillis < sampleWindow)
//       {
//          sample = analogRead(A0);
//          if (sample < 1024)  // toss out spurious readings
//          {
//            Serial.print("analogRead(A0)= ");
//            Serial.print(analogRead(A0));
//
//            int action = (sample/5);
//
//            Serial.print("  ||  action= ");
//            Serial.println(action);
//            
//            rgb.setColor(action, action, action);
//             if (sample > signalMax)
//             {
//                signalMax = sample;  // save just the max levels
//                rgb.setColor(250, 0, 0);
//             }
//             else if (sample < signalMin)
//             {
//                signalMin = sample;  // save just the min levels
//                rgb.setColor(0, 0, 250);
//             }
//          }
//       }
    
      rgb.fadeTo(200, 0, 0, 100, 1000);
      rgb.fadeTo(200, 200, 0, 100, 1000);
      rgb.fadeTo(0, 200, 0, 100, 1000);
      rgb.fadeTo(0, 200, 200, 100, 1000);
      rgb.fadeTo(0, 0, 200, 100, 1000);
      rgb.fadeTo(200, 200, 200, 100, 1000);
  
      //rgb.setColor(200, 0, 0);
      }
      
  }
  else {
    digitalWrite(13, state);
    Serial.print(" State: ");
    Serial.print(state);
  }
  Serial.println(" ");

  delay(250);                             // arbitrary delay to limit data to serial port
}
