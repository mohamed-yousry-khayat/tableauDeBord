#include <LiquidCrystal.h> 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int BLUE_LED = 2; // Temprerature
const int RED_LED = 3;
const int FAN = 4;
const int TEMP_SENSOR = A0;

const int GREEN_LED = 1; // Humidité
const int YELLOW_LED = 4;
const int HUMIDITY_SENSOR = A1;

const int LDR_SENSOR = A2; // Luminosité

const int TRIGGER_PIN = 5; // Distance
const int ECHO_PIN = 6;
const int BUZZER_PIN = 13;

long duration;
int distance;

void setup() {
  lcd.begin(16, 2);

  pinMode(BLUE_LED, OUTPUT); // Température
  pinMode(RED_LED, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(TEMP_SENSOR, INPUT);

  pinMode(GREEN_LED, OUTPUT); // Humidité
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(HUMIDITY_SENSOR, INPUT);

  pinMode(LDR_SENSOR, INPUT); // Luminosité

  pinMode(TRIGGER_PIN, OUTPUT); // Distance
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

void loop() {
  lcd.clear(); // Afficheur LCD
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print((char)223); //symbole degrès celsius
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(hum);
  lcd.print("%");

  // Temperature

  int temp = analogRead(TEMP_SENSOR) * 0.488; // Conversion de la tension en degrés Celsius

  if (temp >= 10 && temp <= 18) {
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(FAN, LOW);
  }

  else if (temp >= 19 && temp <= 21) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(FAN, LOW);
  }
  else if (temp > 21) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(FAN, HIGH);
  }
  else {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(FAN, LOW);
  }

  // Humidité

  int humidity = analogRead(HUMIDITY_SENSOR);

  if (humidity >= 40 && humidity <= 70) { // taux d'humidité confortable
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
  }
  else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
  }

  // Luminosité

  int light = analogRead(LDR_SENSOR);

  Serial.print("Luminosité : ");
  Serial.println(light);

  // Distance

  // Envoi d'une impulsion de 10µs sur la broche
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;


  // Vérification si l'objet est en mouvement
  if (distance > 0 && distance < 50) {
    // Activation du buzzer pendant 500ms
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Attente de 500ms avant de relire les informations
  delay(500);

