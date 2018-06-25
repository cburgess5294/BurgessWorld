
// ====================================================================
// Arduino code example for SPI Slave Mode
// Read unsigned short one byte at a time from SPI, send word to serial port
// On 16 MHz Arduino, can work at > 500 words per second
// Original by J.Beale July 19 2011
// 
// Sketch turns on the SPI port in slave mode and waits for SS line (10) to 
// go low.  It then reads from the SPI port one byte and at a time and stores
// the received data in a character array until it finds it newline character (\n).  
// It then writes the received data to the serial port.
// ====================================================================

/* SCK_PIN   13  // D13
   MISO_PIN  12  // D12
   MOSI_PIN  11  // D11
   SS_PIN    10  // D10
*/
#define SS_PIN 10
#define MISO_PIN  12

char buf [6];
volatile byte pos;
volatile boolean process_it;
volatile byte count = 0;
uint16_t stamp = 0;

void setup() {
 Serial.begin(115200);
 Serial.println("SPI port reader v0.1");
 SPCR = (1<<SPE)|(0<<DORD)|(0<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(0<<SPR0); // Turn on SPI port in slave mode at full speed (4Mhz)
 pinMode(MISO_PIN, INPUT);
}

// ============================================================
// main loop: read in bytes, one at a time from external SPI master
// and send value out via serial port
// On 16 MHz Arduino, works at > 500 words per second
// ============================================================
void loop() {
  unsigned short word1;
  
  if (digitalRead(SS_PIN)== 0) {// wait until SlaveSelect goes low (active)
      stamp ++;
      pinMode(MISO_PIN, OUTPUT);//turn the MISO pin to OUTPUT so we can respond to master
      while (true){
        while(!(SPSR & (1<<SPIF))) ; // SPIF bit set when 8 bits received
        word1 = SPDR;
        if (word1 != 0x00){//if returned byte = 0, discard it
          if (word1 == 0xfe){//if returned byte = 254, we have reached the end of the data
            if (count == 6){//if we captured all of the data...
              SPDR = 0x01; //send a 1 back to master to indicate a good transaction
            }
            else{
              SPDR = 0x02; //send a 2 back to master to indicate a bad transaction
            }
            pinMode(MISO_PIN, INPUT);//turm MISO pin to INPUT mode so other SPI devices can talk to master
            process_it = true;
            count = 0;
            break;
          }
         else{
           buf [pos++] = word1; //add byte into the received character buffer
           count ++;   
         }
       }    
    }
   if (process_it){
      Serial.print (buf);  // prints out the rreceived character buffer if it was a good transaction
      Serial.println (stamp);  //prints out the iteration number of the transaction
      buf [pos] = 0; // empty received character buffer
      pos = 0; // reset 
      process_it = false;
    }
  }  
}
