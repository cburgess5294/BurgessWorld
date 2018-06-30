/* Test Sketch for the Raspberry Pi Shield for Arduino from BurgessWorld Custom Electronics
 *  
 * This sketch assumes that the sheild is being used with an Arduino-compatible board which
 * SoftwarSerial and that the uC select jumpers are to the left-hand position, (D8-TX / D7-RX) 
 * 
 * The Serial port on the Raspberry Pi (/dev/ttyS0 or alias serial0) must be enabled first using
 *  raspi-config or by modifying the appropriate configuration files.
 * 
 * You will also need to disable the Raspberry Pi console output to the serial port:
 * $ sudo systemctl stop serial-getty@ttyS0.service
 * $ sudo systemctl disable serial-getty@ttyS0.service
 * and removing the reference to console=serial0,115200 from /boot/cmdline.txt
 * 
 * This sketch, when used in conjunction with the python script on the Raspberry Pi, will
 * wait for the Pi to issue a request for you to input some data via the Arduino IDE Serial Monitor
 * then report back the data it received from you.  This will demonstrate bi-direction serial 
 * communication between the Raspberry pi and Arduino or compatible Micro-controller
 * 
 * The SoftwareSerial port and Arduino IDE Serial monitor are configured for a BAUD rate of 57600
 * 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  mySerial.begin(57600);

  Serial.println("rPI-AVR Serial Test");
}

void loop() { // run over and over
  if (mySerial.available() >= 1) {
    Serial.write(mySerial.read());
  }
  if (Serial.available() >= 1) {
    mySerial.write(Serial.read());
  }
  
}

