
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(11, 10); // RX | TX
 
// Change DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;
 
void setup()  
{
    if (DEBUG)
    {
        // open serial communication for debugging and show 
        // the sketch filename and the date compiled
        Serial.begin(115200);
        Serial.println(__FILE__);
        Serial.println(__DATE__);
        Serial.println(" ");
    }
 
    //  open software serial connection to the Bluetooth module.
    BTSerial.begin(9600); //9600
    if (DEBUG)  {   Serial.println("BTserial started at 38400");     }
 
} // void setup()
 

char sendstr[128];
int sendstrpos = 0;
 char dbgstr[64];
 char dbgstr128[128];
 unsigned long lastAvailableTime = millis();
void loop()  
{
     if (BTSerial.available()){
        Serial.write(BTSerial.read());    
     }
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    int c = Serial.read();
    sendstr[sendstrpos++] =c;
    sendstr[sendstrpos] =0;    
    lastAvailableTime = millis();
  }else {
    if (sendstrpos && (millis()-lastAvailableTime)>500  ) {
      for (int i = 0; i < sendstrpos; i++)
        BTSerial.write(sendstr[i]);   
      BTSerial.write('\r');  
      BTSerial.write('\n');
      Serial.println(sendstr);
      sendstrpos = 0;
    }
    
  }
}
