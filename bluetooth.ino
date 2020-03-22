
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 10); // RX | TX (11 direct 10 R)

long BTBAUD = 57600 ; //4:9600 5:19200, 6:38400, 7:57600, 8: 115200 (not stable)
char readBuffer[128];
int readPos = 0;
byte termFound = 0;
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
     Serial.write(c);
  }
  // Keep reading from Arduino Serial Monitor and send to HC-05

  
  if (Serial.available()){
    int c = Serial.read();
    readBuffer[readPos++] = (char)c;
    if (c == '\n' || readPos > 100) {
      termFound = 1;
    }
  }
  if (termFound) {
    termFound = 0;
    for(int i = 0; i < readPos;i++) {
      int c = readBuffer[i];
      Serial.write(c);
      BTSerial.write(c);
    }
    readPos = 0;
  }
}
