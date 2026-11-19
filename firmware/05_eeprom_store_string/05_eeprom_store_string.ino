/*
 * 05_eeprom_store_string
 * Board : JPSCUBE Engineers Training Kit (ATmega32U4)
 * Goal  : Read a text string from the Serial Monitor, store it character by
 *         character in external I2C EEPROM, and read it back.
 *
 * Library: extEEPROM + Wire
 * Tip    : Set the Serial Monitor line ending to "Newline".
 */

#include <Wire.h>
#include <extEEPROM.h>

extEEPROM EEPROM(kbits_128, 1, 64, 0x57);

const unsigned long ADDR    = 34;
const int           MAX_LEN = 30;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  byte status = EEPROM.begin();
  if (status != 0) {
    Serial.print("EEPROM init failed, status = ");
    Serial.println(status);
  }
  Serial.println("Enter text to store:");
}

void loop() {
  if (Serial.available()) {
    String name = Serial.readString();
    name.trim();
    if (name.length() > MAX_LEN) name = name.substring(0, MAX_LEN);

    Serial.print("Input: ");
    Serial.println(name);

    // Write characters + null terminator
    for (unsigned int i = 0; i < name.length(); i++) {
      EEPROM.write(ADDR + i, name[i]);
    }
    EEPROM.write(ADDR + name.length(), 0);
    Serial.println("Write done");

    // Read back until null terminator
    char result[MAX_LEN + 1];
    int i = 0;
    for (; i < MAX_LEN; i++) {
      result[i] = (char)EEPROM.read(ADDR + i);
      if (result[i] == 0) break;
    }
    result[i] = 0;

    Serial.print("Read back: ");
    Serial.println(result);
    Serial.println("Read done");
  }
}
