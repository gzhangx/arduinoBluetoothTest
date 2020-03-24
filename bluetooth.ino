
#include <SoftwareSerial.h>
#include "GArduinoBufUtil.h"
SoftwareSerial BTSerial(2, 10); // RX | TX (11 direct 10 R)

long BTBAUD = 57600 ; //4:9600 5:19200, 6:38400, 7:57600, 8: 115200 (not stable)

RecBuf serBuf, blueBuf;
void setup()  
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.println(__DATE__);
    Serial.println(" ");
    BTSerial.begin(BTBAUD); 
    Serial.println("BTserial started at " + String(BTBAUD));
} // void setup()
 

void loop()  
{
  if (BTSerial.available()){
     int c = BTSerial.read();
     if (blueBuf.onRecv(c)) {
      Serial.println(blueBuf.origVal);
     }
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05

  
  if (Serial.available()){
    int c = Serial.read();
    if (serBuf.onRecv(c)) {      
      BTSerial.write(serBuf.val.c_str());
      BTSerial.write("\r\n");
    }
  }  
}
