#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int GS = A3;
const int PIEZO = 10;
const int RED = 11;
const int YELLOW = 12;
const int GREEN = 13;

const float HIGH_LEVEL = 125;
const float MED_LEVEL = 100;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PIEZO, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  String str = String("gas: ");
  int value = analogRead(GS);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(str + value);
  Serial.println(str + value);
  
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  noTone(PIEZO);
  
  if (value >= HIGH_LEVEL) {
    lcd.setCursor(0,1);
    lcd.print("Warning");
    digitalWrite(RED, HIGH);
    tone(PIEZO, 500);
    delay(100);
    digitalWrite(RED, LOW);
    tone(PIEZO, 1000);
  } else if (value >= MED_LEVEL && value < HIGH_LEVEL) {
    digitalWrite(YELLOW, HIGH);
  } else if (value < MED_LEVEL) {
    digitalWrite(GREEN, HIGH);
  }

  delay(300);
}
