#include <LiquidCrystal.h>

#define LED_ON    HIGH
#define LED_OFF   LOW
// Defines the LCD's parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

const int LED_R = 6; //7
const int LED_G = 7; //6;
const int LED_B = 10;// 10

int resval = 0;  // holds the value
int respin = A3; // sensor pin used
int buzzPin = 11;
void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  //setting buzzerpin as output
  pinMode(buzzPin, OUTPUT); 
  lcd.print("Water level: ");

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);  
}

void loop() {
  lcd.setCursor(0, 1);
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
 
  if (resval <=100) {
    lcd.print("EMPTY   ");
    noTone(buzzPin);
    digitalWrite(LED_R, LED_ON);
    digitalWrite(LED_G, LED_OFF);
    digitalWrite(LED_B, LED_OFF); 
  }
  else if (resval > 100 && resval <= 200) {
    lcd.print("LOW   ");
    tone(buzzPin, 50);
    digitalWrite(LED_R, LED_ON);
    digitalWrite(LED_G, LED_OFF);
    digitalWrite(LED_B, LED_OFF);    
  }
  else if (resval > 200 && resval <= 250) {
    lcd.print("MEDIUM   ");
    noTone(buzzPin);
    digitalWrite(LED_G, LED_ON);
     digitalWrite(LED_R, LED_OFF);
      digitalWrite(LED_B, LED_OFF);
  }
  else if (resval > 250) {
    lcd.print("HIGH   ");
    noTone(buzzPin);
     digitalWrite(LED_G, LED_OFF);
      digitalWrite(LED_R, LED_OFF);
    digitalWrite(LED_B, LED_ON);
  }
  delay(400);
}