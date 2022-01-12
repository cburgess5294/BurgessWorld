/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
int led = 6;  // D6 connects to GPIO23 on Raspberry Pi
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(13, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // Send HIGH signal to GPIO23 on Raspberry Pi
  digitalWrite(13, HIGH);   // Set the LED on D13 to on
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // Send LOW signal to GPIO23 on Raspberry Pi
  digitalWrite(13, LOW);    // Set the LED on D13 to off
  delay(1000);               // wait for a second
}
