/*
 * 01_dual_led_buzzer
 * Board : JPSCUBE Engineers Training Kit (ATmega32U4)
 * Goal  : Blink LEDs in sequence and beep the buzzer using tone().
 *
 * Pins used (as wired on the training kit):
 *   A0, A1, 7 -> LED groups
 *   11        -> Buzzer (driven through NPN transistor Q1, 2N2222)
 */

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(A0, HIGH);
  delay(500);
  digitalWrite(11, HIGH);
  tone(11, 100, 10);
  delay(500);

  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  delay(500);
  digitalWrite(11, HIGH);
  tone(11, 100, 10);
  delay(500);

  digitalWrite(A1, LOW);
  digitalWrite(7, HIGH);
  delay(500);
  digitalWrite(11, HIGH);
  tone(11, 100, 10);
  delay(500);

  digitalWrite(7, LOW);
  digitalWrite(11, LOW);
  delay(100);
}
