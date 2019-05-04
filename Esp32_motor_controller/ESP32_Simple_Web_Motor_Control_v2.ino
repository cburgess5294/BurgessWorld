/*
 WiFi Motor Controller

 A simple web interface that allows basic control of a 4-wheel robot via the web.
 This sketch will print the IP address of your robot (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to control robot direction.

 Use web browser to control robot by accessing IP address:
 http://ip-address-of-robot

 You can also use MIT App Inventor 2 to build an android app to control your robot
 when running this sketch.  The example app can be found on in my github repo:

 https://github.com/cburgess5294/BurgessWorld/blob/master/Esp32_motor_controller/Esp32MotorControl_v1.aia

 Other examples and libraries can be found can be found here:

 https://github.com/cburgess5294/BurgessWorld/tree/master/Esp32_motor_controller

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * ESP32 Motor Controller Shield attached
 * 4 DC motors attached

 created for arduino 25 Nov 2012
 by Tom Igoe

 ported for ESP32 Project Board 
 02.05.2019 by Chris Burgess
 
 */

#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MotorShield_MOD_CB.h>

const char* ssid     = "BURGESSWORLD1";
const char* password = "thisistherouterpassword";

WiFiServer server(80);

// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x40); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// Make another motor on port M2
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
// Make another motor on port M3
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
// Make another motor on port M4
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

//  Define Global variables
uint8_t mSpeed = 150;
uint8_t lSpeed = 90;

void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32 - DC Motor test!");
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

    AFMS.begin();  // create with the default frequency 1.6KHz
    //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
    // Set the speed to start, from 0 (off) to 255 (max speed)
    myMotor->setSpeed(mSpeed);
    myMotor->run(FORWARD);
    // turn on motor
    myMotor->run(RELEASE);

    myMotor2->setSpeed(mSpeed);
    myMotor2->run(FORWARD);
    // turn on motor
    myMotor2->run(RELEASE);

    myMotor3->setSpeed(mSpeed);
    myMotor3->run(FORWARD);
    // turn on motor
    myMotor3->run(RELEASE);

    myMotor4->setSpeed(mSpeed);
    myMotor4->run(FORWARD);
    // turn on motor
    myMotor4->run(RELEASE);

}

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<br><br>");
            client.print("<font size='15'><center><a href=\"/F\">FORWARD</a><br><br>");
            client.print("<font size='15'><center><a href=\"/L\">LEFT</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"/S\">STOP</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"/R\">RIGHT</a><br><br>");
            //client.print("<font size='15'><br>");
            client.print("<font size='15'><center><a href=\"/D\">SPEED -</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"/B\">BACK</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"/U\">SPEED +</a><br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /F")) {  // run all motors forward
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor3->run(FORWARD);
          myMotor4->run(FORWARD);
        }
        if (currentLine.endsWith("GET /L")) {  // turn left
          myMotor->setSpeed(lSpeed);  //  set left motors to low speed for turn
          myMotor2->setSpeed(lSpeed);  //  set left motors to low speed for turn
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          myMotor->run(BACKWARD);
          myMotor2->run(BACKWARD);
          myMotor3->run(FORWARD);
          myMotor4->run(FORWARD);
        }
        if (currentLine.endsWith("GET /R")) {  // turn right
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(lSpeed);  //  set left motors to low speed for turn
          myMotor4->setSpeed(lSpeed);  //  set left motors to low speed for turn
          myMotor->run(FORWARD);
          myMotor2->run(FORWARD);
          myMotor3->run(BACKWARD);
          myMotor4->run(BACKWARD);
        }
        if (currentLine.endsWith("GET /B")) {  // run all motors backwards
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          myMotor->run(BACKWARD);
          myMotor2->run(BACKWARD);
          myMotor3->run(BACKWARD);
          myMotor4->run(BACKWARD); 
        }
        if (currentLine.endsWith("GET /S")) {  // disable all motors
          myMotor->run(RELEASE);
          myMotor2->run(RELEASE);
          myMotor3->run(RELEASE);
          myMotor4->run(RELEASE); 
        }
        if (currentLine.endsWith("/P")) {  // change Speed
          String sSpeed = "";
          sSpeed += currentLine.charAt(currentLine.length() -5);  // extract motor speed from http string
          sSpeed += currentLine.charAt(currentLine.length() -4);  // extract motor speed from http string
          sSpeed += currentLine.charAt(currentLine.length() -3);  // extract motor speed from http string
          mSpeed = sSpeed.toInt();  // convert string to integer
          lSpeed = mSpeed * .6;  // set low speed to 60%
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          }
        if (currentLine.endsWith("GET /U")) {  // increase Speed
          if (mSpeed < 240) {
            mSpeed = mSpeed + 15;

          }
          else {
            mSpeed = 255;
          }
          lSpeed = mSpeed * .6;  // set low speed to 60%
          Serial.println();Serial.print("mSpeed: ");
          Serial.println(mSpeed);
          Serial.print("lSpeed: ");
          Serial.println(lSpeed);
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          }
        if (currentLine.endsWith("GET /D")) {  // decrese Speed
          if (mSpeed > 16) {
            mSpeed = mSpeed - 15;
            lSpeed = mSpeed * .6;  // set low speed to 60%
          }
          else {
            mSpeed = 0;
            lSpeed = 0;
          }
          Serial.println();Serial.print("mSpeed: ");
          Serial.println(mSpeed);
          Serial.print("lSpeed: ");
          Serial.println(lSpeed);
          myMotor->setSpeed(mSpeed);
          myMotor2->setSpeed(mSpeed);
          myMotor3->setSpeed(mSpeed);
          myMotor4->setSpeed(mSpeed);
          }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
