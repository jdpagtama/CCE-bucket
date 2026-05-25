#include <LiquidCrystal.h>

const int mq135Pin = 1;

const int rs = 12;
const int en = 11;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int baseline = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);

  long total = 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrating...");
  lcd.setCursor(0, 1);
  lcd.print("Clean air only");

  for (int i = 0; i < 100; i++) {
    total += analogRead(mq135Pin);
    delay(50);
  }

  baseline = total / 100;

  Serial.print("Baseline: ");
  Serial.println(baseline);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Baseline:");
  lcd.setCursor(0, 1);
  lcd.print(baseline);
  delay(2000);
}

void loop() {
  int value = analogRead(mq135Pin);
  int difference = value - baseline;

  Serial.print("Raw: ");
  Serial.print(value);
  Serial.print(" | Difference: ");
  Serial.println(difference);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("MQ135:");
  lcd.print(value);

  lcd.setCursor(0, 1);

  if (difference > 1000) {
    lcd.print("VOC HIGH");
    Serial.println("Possible benzene/VOC presence: HIGH");
  } 
  else if (difference > 500) {
    lcd.print("VOC MEDIUM");
    Serial.println("Possible benzene/VOC presence: MEDIUM");
  } 
  else if (difference > 200) {
    lcd.print("VOC LOW");
    Serial.println("Possible benzene/VOC presence: LOW");
  } 
  else {
    lcd.print("Air Normal");
    Serial.println("Air quality normal");
  }

  delay(1000);
}