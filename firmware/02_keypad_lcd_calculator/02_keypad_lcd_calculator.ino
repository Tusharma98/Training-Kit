/*
 * 02_keypad_lcd_calculator
 * Board : JPSCUBE Engineers Training Kit (ATmega32U4)
 * Goal  : Multi-digit calculator (+, -, *, /) using a 4x4 matrix keypad,
 *         with output on a 16x2 I2C LCD (PCF8574 + HD44780) and Serial Monitor.
 *
 * Keypad layout used by this program:
 *      C1(8) C2(9) C3(10) C4(1)
 *  R1(4):  7     8     9     +
 *  R2(12): 4     5     6     -
 *  R3(6):  1     2     3     C (clear)
 *  R4(13): *     0     #(=)  /
 *
 * Libraries: Wire, LiquidCrystal_I2C (NewLiquidCrystal)
 * Note: the I2C address 0x27 may differ on your module (try 0x3F or run an
 *       I2C scanner). A wrong address gives a blank display.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 3, 4, 5, 6, 7, POSITIVE);

char  perform;
char  once;
float input;
float mulint;
float value1;
float value2;
float result;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Rows -> outputs (idle HIGH)
  pinMode(12, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(13, HIGH);

  // Columns -> inputs with pull-ups
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
}

void loop() {
  // ---------- Row 1 : 7 8 9 + ----------
  digitalWrite(4, LOW);
  if (digitalRead(8) == LOW) {
    input = 7;
    mulint = mulint * 10 + input;
    lcd.print(7);
    Serial.println("Pressed 7");
    delay(500);
  }
  if (digitalRead(9) == LOW) {
    input = 8;
    mulint = mulint * 10 + input;
    lcd.print(8);
    Serial.println("Pressed 8");
    delay(500);
  }
  if (digitalRead(10) == LOW) {
    input = 9;
    mulint = mulint * 10 + input;
    lcd.print(9);
    Serial.println("Pressed 9");
    delay(500);
  }
  if (digitalRead(1) == LOW) {
    perform = '+';
    value1 = mulint;
    mulint = 0;
    lcd.print("+");
    Serial.println("Pressed +");
    delay(500);
  }

  // ---------- Row 2 : 4 5 6 - ----------
  digitalWrite(4, HIGH);
  digitalWrite(12, LOW);
  if (digitalRead(8) == LOW) {
    input = 4;
    mulint = mulint * 10 + input;
    lcd.print(4);
    Serial.println("Pressed 4");
    delay(500);
  }
  if (digitalRead(9) == LOW) {
    input = 5;
    mulint = mulint * 10 + input;
    lcd.print(5);
    Serial.println("Pressed 5");
    delay(500);
  }
  if (digitalRead(10) == LOW) {
    input = 6;
    mulint = mulint * 10 + input;
    lcd.print(6);
    Serial.println("Pressed 6");
    delay(500);
  }
  if (digitalRead(1) == LOW) {
    perform = '-';
    value1 = mulint;
    mulint = 0;
    lcd.print("-");
    Serial.println("Pressed -");
    delay(500);
  }

  // ---------- Row 3 : 1 2 3 C ----------
  digitalWrite(12, HIGH);
  digitalWrite(6, LOW);
  if (digitalRead(8) == LOW) {
    input = 1;
    mulint = mulint * 10 + input;
    lcd.print(1);
    Serial.println("Pressed 1");
    delay(500);
  }
  if (digitalRead(9) == LOW) {
    input = 2;
    mulint = mulint * 10 + input;
    lcd.print(2);
    Serial.println("Pressed 2");
    delay(500);
  }
  if (digitalRead(10) == LOW) {
    input = 3;
    mulint = mulint * 10 + input;
    lcd.print(3);
    Serial.println("Pressed 3");
    delay(500);
  }
  if (digitalRead(1) == LOW) {
    Serial.println("Clear");
    lcd.clear();
    input = 0;
    mulint = 0;
    value1 = 0;
    value2 = 0;
    result = 0;
    perform = 0;
    once = 0;
  }

  // ---------- Row 4 : * 0 # / ----------
  digitalWrite(6, HIGH);
  digitalWrite(13, LOW);
  if (digitalRead(8) == LOW) {
    perform = '*';
    value1 = mulint;
    mulint = 0;
    lcd.print("*");
    Serial.println("Pressed *");
    delay(500);
  }
  if (digitalRead(9) == LOW) {
    input = 0;
    mulint = mulint * 10 + input;
    lcd.print(0);
    Serial.println("Pressed 0");
    delay(500);
  }
  if (digitalRead(10) == LOW) {
    once = '=';
    lcd.print("=");
    Serial.println("Pressed #");
    delay(500);
  }
  if (digitalRead(1) == LOW) {
    perform = '/';
    value1 = mulint;
    mulint = 0;
    lcd.print("/");
    Serial.println("Pressed /");
    delay(500);
  }
  digitalWrite(13, HIGH);

  // ---------- Evaluate when '=' was pressed ----------
  if (once == '=') {
    value2 = mulint;
    if (perform == '+') result = value1 + value2;
    if (perform == '-') result = value1 - value2;
    if (perform == '*') result = value1 * value2;
    if (perform == '/') result = value1 / value2;

    lcd.clear();
    lcd.print(result, 10);
    lcd.setCursor(0, 1);
    Serial.println(result, 10);

    input = 0;
    mulint = 0;
    value1 = 0;
    value2 = 0;
    result = 0;
    perform = 0;
    once = 0;
  }
}
