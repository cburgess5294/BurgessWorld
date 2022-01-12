/*
 Feb 2020 - Updated by BURGESS C cburgess@burgessworle.net
 Parts derived from examples by J. Coliz <maniacbug@ymail.com>
  
 Example for efficient call-response using ack-payloads 
 
 This example has been modified to work on ESP8266 Dev Board, ESP32 Project Board and 
 Arduino-Teensy boards available from the BurgessWorld Custom Electronics Tindie store:
 https://tindie.com/stores/cburgess129
 
 It makes use of all the normal functionality of the radios including
 the auto-ack and auto-retry features, but allows ack-payloads to be written optionally as well.
 This allows very fast call-response communication, with the responding radio never having to 
 switch out of Primary Receiver mode to send back a payload, but having the option to if wanting
 to initiate communication instead of respond to a commmunication.
 
 Requires installation of the RF24 Arduino Library along with ESP32 and ESP8266 boards manager
 Select DO IT Dev Kit V1 from boards menu
 */
 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(27,5);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

// Role management: Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  

typedef enum { role_ping_out = 1, role_pong_back } role_e;                 // The various roles supported by this sketch
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};  // The debug-friendly names of those roles
role_e role = role_pong_back;                                              // The role of the current running sketch

// A single byte to keep track of the data being sent back and forth
byte counter = 1;

void setup(){

  Serial.begin(115200);
  Serial.print("RF24/examples/pingpair_ack/ROLE: ");
  Serial.println(role_friendly_name[role]);
  Serial.println("*** PRESS 'T' to begin transmitting to the other node");

  // Setup and configure rf radio

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();                 // Start listening
  //radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop(void) {

  if (role == role_ping_out){
    
    radio.stopListening();                                  // First, stop listening so we can talk.

    Serial.print("Now sending ");    
    Serial.print(counter);
    Serial.println(" as payload ");  
    byte gotByte;  
    unsigned long time = micros();                          // Take the time, and send it.  This will block until complete   
                                                            //Called when STANDBY-I mode is engaged (User is finished sending)
    if (!radio.write( &counter, 1 )){
      Serial.println("failed.");      
    }else{

      if(!radio.available()){ 
        Serial.println("Blank Payload Received."); 
      }else{
        while(radio.available() ){
          unsigned long tim = micros();
          radio.read( &gotByte, 1 );
          Serial.print("Got response ");
          Serial.print(gotByte);
          Serial.print(" microseconds ");
          Serial.println(tim-time);
          counter++;
        }
      }

    }
    // Try again later
    delay(1000);
  }

  // Pong back role.  Receive each packet, dump it out, and send it back

  if ( role == role_pong_back ) {
    byte pipeNo;
    byte gotByte;                                       // Dump the payloads until we've gotten everything
    while( radio.available(&pipeNo)){
      radio.read( &gotByte, 1 );
      radio.writeAckPayload(pipeNo,&gotByte, 1 );    
   }
 }

  // Change roles

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      Serial.println("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK");

      role = role_ping_out;                  // Become the primary transmitter (ping out)
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      Serial.println("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK");
      
       role = role_pong_back;                // Become the primary receiver (pong back)
       radio.openWritingPipe(pipes[1]);
       radio.openReadingPipe(1,pipes[0]);
       radio.startListening();
    }
  }
}