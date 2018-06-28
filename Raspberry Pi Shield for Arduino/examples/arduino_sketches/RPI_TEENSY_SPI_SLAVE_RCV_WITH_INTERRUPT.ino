/*  This sketch is for use with the Raspberry Pi Arduino-Shield by created by 
 *   BurgessWorld Custom Electronics.  It uses SPI to communicate between a
 *   Raspberry Pi Zero or Zero W and an Arduino-Teensy (with Teensy 3.1/3.2) v4.x or v5.x available from 
 *   my Tindie shop at the link below:
 *   
 *   https://www.tindie.com/products/cburgess129/arduino-teensy-v44-with-wifibluetoothnrf24l01/
 *   
 *   This sketch implements a hybrid muulti-master mode between the Raspberry Pi and Teensy and requires
 *   the MISO and MOSI lines to be crossed.
 *   
 *   Raspberry Pi           Teensy 3.1/3.2
 *   -------------------------------------
 *   MISO           -->     MOSI
 *   MOSI           -->     MISO
 *   SCK            -->     SCK
 *   CE1            -->     10
 *   
 *   You will have to remove the jumpes from the MISO and MOSI pin bridge and make connections with
 *   the included jumper wires
 *   
 */
#include <t3spi.h>

//Initialize T3SPI class as SPI_SLAVE
T3SPI SPI_SLAVE;

//The number of integers per data packet
//MUST be the same as defined on the MASTER device
#define dataLength  5

//Initialize the arrays for incoming data
volatile uint8_t data[dataLength] = {};
//volatile uint16_t data[dataLength] = {};


void setup(){
  
  Serial.begin(115200);
  
  //Begin SPI in SLAVE (SCK pin, MOSI pin, MISO pin, CS pin)
  //SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  SPI_SLAVE.begin_SLAVE(13, 12, 11, 10); //specify pins, function of MOSI and MISO are reversed in the slave config
  
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE1);
  //SPI_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);
  
  //Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0);
  
}

void loop(){

  //Capture the time before receiving data
  if (SPI_SLAVE.dataPointer==0 && SPI_SLAVE.packetCT==0){
    SPI_SLAVE.timeStamp1=micros();}  
 
  //Capture the time when transfer is done
  if (SPI_SLAVE.packetCT==1){
    SPI_SLAVE.timeStamp2=micros();

    //Print data received & data sent
    for (int i=0; i<dataLength; i++){
      Serial.print("data[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.write(data[i]);
      Serial.println();
      Serial.flush();}
  
      //Print statistics for the previous transfer
      SPI_SLAVE.printStatistics(dataLength); 
   
    //Reset the packet count   
    SPI_SLAVE.packetCT=0;}
}

//Interrupt Service Routine to handle incoming data
void spi0_isr(void){
  
  //Function to handle data
  SPI_SLAVE.rx8 (data, dataLength);
  //SPI_SLAVE.rx16(data, dataLength);
}
