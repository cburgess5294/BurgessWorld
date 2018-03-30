/* Test Sketch for the NodeMCU Sensor Shield v1 by BurgessWorld Custom Electronics
 *  
 * THIS SKETCH GETS LOADED ONTO THE NODEMCU DEVELOPMENT BOARD 
 * 
 * This sketch assumes there is an Ultrasonic Range sensor such as the SR-HC04 or US-100
 * attached to port HC-SR04-1 of the Sensor Shield and a Passive Infrared sensor attached 
 * to port PIR-1
 * 
 * This sketch queries the Sensor Shield via a Software Serial connection and prints the
 * response to the hardware (USB) serial port
 * 
 * The Sensor Shield is ccnnected to the NodeMCu Development Board at pins D3 and D4:
 * Pin D3/GPIO0 is configured as TX on the Developement board
 * Pin D4/GPIO2 is configured as RX on the Development board
 * 
 * The Software Serial port is configured for a BAUD rate of 115200
 * 
 * The RUN/PROG switch on the Sensor Shield must be in the RUN position to query the board
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 0); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(115200);


  Serial.println("NodeMCU Sensor Board Test");

}

void loop() { // run over and over
  
  mySerial.println("u1,p1");//query ports u1 and p1 on (HC-SR04-1 and PIR-1) on the sensor board
  delay(150);//delay to allow the Sensor board to query the sensors and reply
  
  //capture all serial data from the Software Serial port and add it to a string
  String printStr = "";
  while (mySerial.available() >= 1) {
    char myByte = (mySerial.read());
    printStr += myByte;
  }
  
  Serial.print(printStr);//print response to hardware serial port
  delay(100);
}

