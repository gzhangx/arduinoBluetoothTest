
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX (11 direct 10 R)
 
#include <Servo.h>
Servo myservo;  // create servo object to control a servo


// Change DEBUG to true to output debug information to the serial monitor
boolean DEBUG = true;

int myservoPos = 90;
int wantedPos = 90; 

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

  myservo.attach(5);
  myservo.write(myservoPos);  
} // void setup()
 

char sendstr[128];
int sendstrpos = 0;
 char dbgstr[64];
 char dbgstr128[128];
 int step= 10;
 unsigned long lastAvailableTime = millis();
void loop()  
{
     if (BTSerial.available()){
        int c = BTSerial.read();
        Serial.write(c);    
        if (c == 'A') {
          wantedPos-=step;
          if (wantedPos < 0) wantedPos = 0;
        }else if (c == 'D') {
          wantedPos+=step;
          if (wantedPos > 180) wantedPos = 180;
        }
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


  servoControl();
}


void servoControl() {
  if (wantedPos != myservoPos) {
    myservoPos = wantedPos;
    BTSerial.write(myservoPos);
    BTSerial.write('\n');
    myservo.write(myservoPos); 
  }
}
