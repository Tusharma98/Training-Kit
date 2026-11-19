# ATmega32U4 Peripheral Interfacing Projects

A collection of Arduino-IDE firmware projects for the **ATmega32U4** microcontroller,
covering GPIO, matrix keypad scanning, an I2C LCD, and external I2C EEPROM storage.
Built and tested on the **JPSCUBE Engineers Training Kit**.

## Projects

| # | Sketch | What it does |
|---|--------|--------------|
| 1 | [`01_dual_led_buzzer`](firmware/01_dual_led_buzzer) | Sequential LED blinking with buzzer beeps via `tone()` (buzzer switched by a 2N2222 transistor) |
| 2 | [`02_keypad_lcd_calculator`](firmware/02_keypad_lcd_calculator) | Multi-digit calculator (+ − × ÷) using a 4×4 matrix keypad (hand-written row/column scanning) and a 16×2 I2C LCD |
| 3 | [`03_eeprom_store_integer`](firmware/03_eeprom_store_integer) | Store/read an integer in external I2C EEPROM from Serial input |
| 4 | [`04_eeprom_store_float`](firmware/04_eeprom_store_float) | Store/read a float as a scaled 16-bit integer in external EEPROM |
| 5 | [`05_eeprom_store_string`](firmware/05_eeprom_store_string) | Store/read a text string in external EEPROM |

## Hardware

- JPSCUBE Engineers Training Kit (ATmega32U4, 16 MHz, USB)
- 4×4 matrix keypad
- 16×2 character LCD (HD44780) + PCF8574 I2C I/O expander
- External I2C EEPROM (24LC256 / GT24C128 class, address `0x57`)
- Dual LEDs, buzzer + NPN transistor (2N2222)
- Studied at schematic level: PCF8563 I2C RTC, MCP4018T-103 digital potentiometer, LM358 op-amp

## Software & Libraries

- [Arduino IDE](https://www.arduino.cc/en/software)
- `Wire` (built in)
- `LiquidCrystal_I2C` / NewLiquidCrystal – LCD
- [`extEEPROM`](https://github.com/PaoloP74/extEEPROM) – external EEPROM
- Proteus Design Suite – schematic-level circuit study

## Getting Started

1. Install the Arduino IDE and the libraries above (Sketch → Include Library → Manage Libraries).
2. Open any `.ino` file from `firmware/` (each sketch sits in a folder of the same name – an Arduino requirement).
3. Select the board (Arduino Leonardo / the kit's ATmega32U4 profile) and the correct COM port.
4. Upload, and open the Serial Monitor at **9600 baud** for sketches 2–5.

> **Warning:** While testing the EEPROM programs, the kit's bootloader was erased once
> and the board had to be re-flashed. Keep a known-good bootloader/firmware image handy.

## Notes

- **LCD address:** sketches assume I2C address `0x27`. If the display stays blank, run an I2C scanner – many modules use `0x3F`.
- **Keypad pins** are specific to this kit (rows on 4, 12, 6, 13; columns on 8, 9, 10, 1).
- **Integer EEPROM sketch** stores a single byte, so values are limited to 0–255.

## Schematics

Add exported circuit images to `docs/images/` and link them here
(ATmega32U4 + LEDs/buzzer/keypad, I2C LCD expander, external EEPROM, RTC, digital potentiometer).

## Skills Demonstrated

Embedded C/C++ · AVR architecture · SPI / I2C / UART · GPIO & transistor switching ·
matrix keypad scanning · I2C LCD · external EEPROM · datasheet reading · hardware debugging

## License

Released under the [MIT License](LICENSE).
