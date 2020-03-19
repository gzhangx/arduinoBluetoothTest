
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 10); // RX | TX (11 direct 10 R)

void setup()  
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.println(__DATE__);
    Serial.println(" ");
    BTSerial.begin(9600); //9600
    Serial.println("BTserial started at 38400");
} // void setup()
 

void loop()  
{
  if (BTSerial.available()){
     int c = BTSerial.read();
     Serial.write(c);            
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    int c = Serial.read();
    BTSerial.write(c);    
  }
}
