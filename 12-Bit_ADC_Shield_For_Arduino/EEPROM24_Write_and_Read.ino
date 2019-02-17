#include <Wire.h>
#include <EEPROM24.h>

EEPROM24_256 eeprom;
char buff [15]; // must be large enough for your whole string!

void setup() {
    Serial.begin(115200);
    eeprom.begin();

    eeprom.write(0, 0x01);
    eeprom.write(1, 0x05);
    eeprom.write(2, 0xBE);
    eeprom.write(3, 0xEF);
    eeprom.write(4, 0xFE);
    eeprom.write(5, 0xED);
    Serial.println("6 Blocks EEPROM written.");
    Serial.println();
    Serial.println("EEPROM READ:");
    Serial.println("-------------");
    for (int i = 0; i < 6; i++) {
      Serial.println(eeprom.read(i));
    }
    Serial.println();
}

void loop() {
}
