/* 
This is a test sketch for the BurgessWorld Custom Electronics
ESP32 and NodeMCU Quad Motor and Servo Shields.

https://www.tindie.com/products/cburgess129/quad-motor-servo-shield-for-esp32-project-board/
https://www.tindie.com/products/cburgess129/quad-motor-servo-shield-for-wireless-dev-board/

The sketch will slowly ramp all 4 motors up and down to maximum speed.
*/

#include <Wire.h>
#include <Adafruit_MotorShield_MOD_CB.h>

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

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

  myMotor2->setSpeed(255);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor2->run(RELEASE);

  myMotor3->setSpeed(255);
  myMotor3->run(FORWARD);
  // turn on motor
  myMotor3->run(RELEASE);

  myMotor4->setSpeed(255);
  myMotor4->run(FORWARD);
  // turn on motor
  myMotor4->run(RELEASE);
}

void loop() {
  uint8_t i;
  
  Serial.print("tick");

  myMotor->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i); 
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i); 
    myMotor4->setSpeed(i);
    delay(10);
  }
  
  Serial.print("tock");

  myMotor->run(BACKWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i);   
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);
    myMotor2->setSpeed(i);
    myMotor3->setSpeed(i);
    myMotor4->setSpeed(i);
    delay(10);
  }

  Serial.print("tech");
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
  delay(1000);
}
