/*
 Fading

 This example shows how to control the 20A DC Motor Controller (based on the BTN8962) using the analogWrite() function.

 The circuit:
 Arduino Pin  ->  Motor Controller Pin
 -------------------------------------
 D2 -> INH
 D3 -> IN1
 D5 -> IN2
 GND -> V-

 Connect the motor voltage (battery) to the V+ and V- connectors on the motor controller
 Connect the motor + wire to M-OUT1
 Connect the motor - wire to M-OUT2

 Created 23 Feb 2018
 By Chris L Burgess

 This example code is in the public domain.

 */


int in1Pin = 3;    // IN1 pin connected to D3
int in2Pin = 5;    // IN2 pin connected to D5
int inhPin = 2;    // INH pin connected to D2

void setup() {
  pinMode(2, OUTPUT); //set pin D2 to digital output mode
}

void loop() {
  //spin motor forward at half-speed for 10 seconds
  analogWrite(in1Pin, 130);  // make IC1 output voltage at ~50% (motor+)
  analogWrite(in2Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(10000);  //delay 10 seconds

  //spin motor forward at full-speed for 5 seconds
  analogWrite(in1Pin, 255);  // make IC1 output voltage at ~100% (motor+)
  analogWrite(in2Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(5000);  //delay 5 seconds

  //set motor to free-running
  analogWrite(in1Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(in2Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(2000);  //delay 2 seconds

  //brake motor - setting both IC1 and IC2 to positive voltage makes motor stop spinning
  analogWrite(in1Pin, 255);  // make IC1 output voltage at ~100% (motor+)
  analogWrite(in2Pin, 255);  // make IC2 output voltage at ~100% (motor+)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(2000);  //delay 2 seconds
  
 //spin motor backwards at half-speed for 10 seconds
  analogWrite(in1Pin, 0);  // make IC1 sink voltage (act as GND or motor-)
  analogWrite(in2Pin, 130);  // make IC2 output voltage at ~50% (motor+)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(10000);  //delay 10 seconds

  //spin motor backwards at full-speed for 5 seconds
  analogWrite(in1Pin, 0);  // make IC1 sink voltage (act as GND or motor-)
  analogWrite(in2Pin, 255);  // make IC2 output voltage at ~50% (motor+)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(5000);  //delay 5 seconds
  
  //set motor to freewheel
  analogWrite(in1Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(in2Pin, 0);  // make IC2 sink voltage (act as GND or motor-)
  analogWrite(inhPin, HIGH); //enable IC1 and IC2
  delay(2000);  //delay 2 seconds

  //disable motor controller
  analogWrite(inhPin, LOW); //disable IC1 and IC2
  delay(5000);  //delay 5 seconds
}


