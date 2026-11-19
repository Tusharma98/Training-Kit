/*
 * 04_eeprom_store_float
 * Board : JPSCUBE Engineers Training Kit (ATmega32U4)
 * Goal  : Store a floating-point value in external I2C EEPROM as a scaled
 *         integer (value x 100, kept in 2 bytes), then read it back.
 *
 * Example: type 12.34 -> stored as 1234 (int16) -> printed back as 12.34
 *
 * Library: extEEPROM + Wire
 * Range  : -327.68 to 327.67 (2 decimal places)
 */

#include <Wire.h>
#include <extEEPROM.h>

extEEPROM EEPROM(kbits_128, 1, 64, 0x57);

const unsigned long ADDR  = 32;
const float         SCALE = 100.0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  byte status = EEPROM.begin();
  if (status != 0) {
    Serial.print("EEPROM init failed, status = ");
    Serial.println(status);
  }
  Serial.println("Enter a decimal value (e.g. 12.34):");
}

void loop() {
  if (Serial.available()) {
    float value = Serial.parseFloat();
    while (Serial.available()) Serial.read();   // clear leftovers

    int16_t scaled = (int16_t)round(value * SCALE);
    Serial.print("Input: ");
    Serial.println(value, 2);

    // Write 2 bytes
    EEPROM.write(ADDR, (byte*)&scaled, sizeof(scaled));
    Serial.println("value stored in EEPROM");

    // Read 2 bytes back
    int16_t stored = 0;
    EEPROM.read(ADDR, (byte*)&stored, sizeof(stored));
    Serial.print("value read from EEPROM: ");
    Serial.println(stored / SCALE, 2);
  }
}
