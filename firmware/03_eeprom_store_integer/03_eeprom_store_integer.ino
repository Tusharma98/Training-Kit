/*
 * 03_eeprom_store_integer
 * Board : JPSCUBE Engineers Training Kit (ATmega32U4)
 * Chip  : External I2C EEPROM (24LC256 / GT24C128 class), address 0x57
 * Goal  : Read an integer from the Serial Monitor, store it in external
 *         EEPROM, read it back and print it.
 *
 * Library: extEEPROM (Jack Christensen) + Wire
 * Limit  : EEPROM.write() stores ONE byte, so the value must be 0-255.
 *          See 04_eeprom_store_float for multi-byte values.
 */

#include <Wire.h>
#include <extEEPROM.h>

// kbits_128, 1 device, 64-byte page size, I2C address 0x57
extEEPROM EEPROM(kbits_128, 1, 64, 0x57);

int vol;
int result;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  byte status = EEPROM.begin();
  if (status != 0) {
    Serial.print("EEPROM init failed, status = ");
    Serial.println(status);
  }
}

void loop() {
  if (Serial.available()) {
    vol = Serial.parseInt();
    Serial.read();                 // discard trailing newline
    Serial.println(vol);

    for (int i = 0; i < 10; i++) {
      EEPROM.write(32 + i, vol);   // store at addresses 32..41
    }
    Serial.println("value stored in EEPROM");

    for (int i = 0; i < 10; i++) {
      result = EEPROM.read(32 + i);
    }
    Serial.println(result);
    Serial.println("value read from EEPROM");
  }
}
