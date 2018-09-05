
// Example sketch for Raspberry Pi Arduino Shield
//
// Receives data as an I2C/TWI slave device from Raspberry Pi
// and returns a acknowlegement
//
// ensure both I2C jumpers are in place on the shield and you
// are running the sample python script on the Raspberry Pi

#include <Wire.h>

char recBuf;
int i = 0;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  //Wire.setClock(100000);         // set I2C clock lower to reduce I2C errors on Raspberry pi (you can play with this value)
  Wire.onReceive(receiveEvent); // register event when data received
  Wire.onRequest(sendData);     // wait for request from master before sending Ack
  Serial.begin(115200);         // start serial for output
  Serial.println("I2C Receiver With Response V2.0");
}

void loop() {
  //delay(10);
  }

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all the received data
     recBuf = Wire.read(); // receive byte as a character
  }
}
void sendData(){
  Serial.write(recBuf); // print the data received to Serial
  Wire.write(recBuf);  //send a 1 to master acknowlege the data
  i++;
  if (i == 5){
    i = 0;
    Serial.write(0x0A);
  }
}
