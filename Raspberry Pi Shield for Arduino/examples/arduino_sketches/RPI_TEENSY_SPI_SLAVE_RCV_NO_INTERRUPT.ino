
#include <t3spi.h>

//Initialize T3SPI class as SPI_SLAVE
T3SPI SPI_SLAVE;

//The number of integers per data packet
//MUST be the same as defined on the MASTER device
#define dataLength  5

//Initialize the arrays for incoming data
//volatile uint8_t data[dataLength] = {};
volatile uint16_t data[dataLength] = {};



uint8_t dataPointer = 0;
void setup(){
  Serial.begin(115200);
  
  //Begin SPI in SLAVE (SCK pin, MOSI pin, MISO pin, CS pin)
  SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);
  //SPI_SLAVE.setCTAR_SLAVE(16, SPI_MODE0);
  SPI0_CTAR0 |= SPI_CTAR_DBR | SPI_CTAR_CSSCK(0b0111) | SPI_CTAR_BR(0b0111);//set SPI CLOCK SPEED TO 370Kbps
 
}

void loop(){
  if (digitalRead(10) == 0){
    while (dataPointer < dataLength){
      delay(20);
      while(!SPI_SR_RFDF){}//wait until byte is sent
      data[dataPointer] = SPI0_POPR;
      Serial.println(data[dataPointer],BIN);
      dataPointer++;
      SPI0_SR |= SPI_SR_RFDF;
    }
    if (dataPointer == dataLength){
      dataPointer=0;
    }
    //Print data received
    for (int i=0; i<dataLength; i++){
      Serial.print("data[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.write(data[i]);
      Serial.println();
      Serial.flush();}   
  }
}
