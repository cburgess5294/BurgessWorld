// Example sketch for Raspberry Pi Arduino Shield
//
// Receives data as an I2C/TWI slave device from Raspberry Pi
// and returns a acknowlegement
//
// ensure both I2C jumpers are in place on the shield and you
// are running the sample python script on the Raspberry Pi

#include <Wire.h>

String recBuf = "";

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  //Wire.setClock(50000);         // set I2C clock lower to reduce I2C errors on Raspberry pi (you can play with this value)
  Wire.onReceive(receiveEvent); // register event when data received
  Wire.onRequest(sendData);     // wait for request from master before sending Ack
  Serial.begin(115200);         // start serial for output
}

void loop() {
  delay(1000);  // do nothing until data received
 }

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all the received data
    char c = Wire.read(); // receive byte as a character
    recBuf += c;  // add received byte to string buffer
  }
}
void sendData(){
    Serial.println(recBuf); // print the data received to Serial
    recBuf = "";  // empty the receive buffer
    Wire.write(0x01);  //send a 1 to master acknowlege the data
}
