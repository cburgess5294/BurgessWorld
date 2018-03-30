// ---------------------------------------------------------------------------
// CORE sketch to enable remote sensor reading with the NodeMCU Sensor Shield
// Sketch version 1.0

// THIS SKETCH GETS LOADED ONTO THE NODEMCU SENSOR BOARD VIA A USB-SERIAL CABLE
//
// This sketch listens on the hardware serial port of the Sensor Shield for a request to read a sensor 
// or list of sensors and responds with sensor data in the following format:
// 
//       Sensor type       | Sensor # | Sensor Reading | Reading Seperator |  End of Request Character
// ---------------------------------------------------------------------------------------------------
//   u Ultrasonic          |   1-4    | reading in CM  |        ,          |           e
//   p Passive Infra-red   |   1-4    | 0 or 1         |        ,          |           e
//
//
// Sensor data can be requested by transmitting a request to the serial port of the Sensor Shield.  The
// Serial port on the Sensor Shield is connect to the NodeMCU Deveopment Board as shown below:
// 
//  Sensor Shield      NodeMCU Development
//  Pin                Board Pin
//  -----------------------------------
//  RX        <-       D3(GPIO0)
//  TX        ->       D4(GPIO4)

// A Software Serial connection on the NodeMCU Development Board is used to communincate with the Sensor Shield
//
// You can specify individual sensors to be read or specifying all sensors of a particular type be read.
//
// Request examples:
// Read ultrasonic sensor 1:                          u1
// Read ultrasonic sensor 2 and 3:                    u2u3
// Read all ultrasonic sensors:                       u5
// Read PIR sensor 1 an ultrasonic sensor 2:          p1u2
// Read all ultrasonic sensors and all PIR sensors:   u5p5
// 
// There is no need to separate request elemants and requests must end in CR or NL an CR characters
// The maximum number of readings per second is limited by the baud rate of the serial connection (57600bps) and
// the time it takes to read a sensor (10-15ms)

// Example Query 1:
//   mySerial.println("u1u2u3u4p1p2p3p4");
//
// Example Query 2:
//   mySerial.println("u5p5");
//
// Both Queries request the data for all sensors.
// Example reading returned:
//   u1104,u250,u30,u412,p11,p20,p30,p41e
//
// ---------------------------------------------------------------------------


#include <NewPing.h>

//DEFINE ULTRASONIC SENSOR CONNECTIONS
//Ultratronic Sensor port 1
#define TRIGGER_PIN1  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
//Ultratronic Sensor port 2
#define TRIGGER_PIN2  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
//Ultratronic Sensor port 3
#define TRIGGER_PIN3  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
//Ultratronic Sensor port 4
#define TRIGGER_PIN4  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     9  // Arduino pin tied to echo pin on the ultrasonic sensor.

//DEFINE PIR SENSOR CONNECTIONS
//PIR Sensor Port 1
//PIR Sensor Port 2
//PIR Sensor Port 3
//PIR Sensor Port 4

int intByte;
//bool lastByte = false;
String xmitStr;
bool strReady = false;
bool goodReq = false;
int strLen;

#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(57600); // Open serial monitor at 115200 baud to see ping results.

  //set PIR sensor pins to INPUT mode
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);
  pinMode(11, INPUT);
}

void loop() {
  while(Serial.available() > 0){
    char serByte = Serial.read();
    if(serByte == 117){
      delay(10);
      intByte = Serial.read() - 48;
      if (intByte > 0 && intByte < 6){
        readSonor(intByte);
      }
      xmitStr += ",";
      goodReq = true;
    }
    else if(serByte == 112){
      delay(10);
      intByte = Serial.read() -48;
      if (intByte == 1){
        xmitStr += "p1";
        if (digitalRead(12)){
          xmitStr += "1";
        }
        else{
          xmitStr += "0";
        }
      }
      if (intByte == 2){
        xmitStr += "p2";
        if (digitalRead(13)){
          xmitStr += "1";
        }
        else{
          xmitStr += "0";
        }
      }
      if (intByte == 3){
        xmitStr += "p3";
        if (digitalRead(14)){
          xmitStr += "1";
        }
        else{
          xmitStr += "0";
        }
      }
      if (intByte == 4){
        xmitStr += "p4";
        if (digitalRead(11)){
          xmitStr += "1";
        }
        else{
          xmitStr += "0";
        }
      }
      xmitStr += ",";
      goodReq = true;
    }
    else if(serByte == 10 && !strReady && goodReq){
      strReady = true;
      //strLen = xmitStr.length();
      //xmitStr.remove(xmitStr.length() - 1);
      xmitStr += "e";
    }
  }
  if(strReady){
    Serial.println(xmitStr);
    strReady = false;
    xmitStr = "";
    goodReq = false;
  }
//  delay(250);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
}

// FUNCTION TO READ ULTRASONIC SENSORS
 void readSonor(int num){
   if(num < 5){
    xmitStr += "u";
    xmitStr += num;
    switch (num) {
    case 1:
      xmitStr += sonar1.ping_cm();
      break;
    case 2:
      xmitStr += sonar2.ping_cm();
      break;
    case 3:
      xmitStr += sonar3.ping_cm();
      break;
    case 4:
      xmitStr += sonar4.ping_cm();
     break;
    }
   }
   else{
    xmitStr += "u1";
    xmitStr += sonar1.ping_cm();
    xmitStr += ",u2";
    xmitStr += sonar2.ping_cm();
    xmitStr += ",u3";
    xmitStr += sonar3.ping_cm();
    xmitStr += ",u4";
    xmitStr += sonar4.ping_cm();
  }
 }

