#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define trigPin 9
#define echoPin 10
#define ledPin 7

long duration;
int distance;
int waterLevel;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);

  lcd.setCursor(0,0);
  lcd.print("Water Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance
  distance = duration * 0.034 / 2;

  // Convert to water percentage
  waterLevel = map(distance, 20, 5, 0, 100);

  // Prevent negatives or above 100
  waterLevel = constrain(waterLevel, 0, 100);

  // LCD FIRST LINE
  lcd.setCursor(0,0);
  lcd.print("Water:");
  lcd.print(waterLevel);
  lcd.print("%    ");

  // LOW WATER
  if (waterLevel < 30) {

    digitalWrite(ledPin, HIGH);

    lcd.setCursor(0,1);
    lcd.print("Motor: ON     ");

    // Website serial data
    Serial.print(waterLevel);
    Serial.println(",Motor ON");
  }

  // WATER OK
  else {

    digitalWrite(ledPin, LOW);

    lcd.setCursor(0,1);
    lcd.print("Motor: OFF    ");

    // Website serial data
    Serial.print(waterLevel);
    Serial.println(",Motor OFF");
  }

  delay(1000);
}