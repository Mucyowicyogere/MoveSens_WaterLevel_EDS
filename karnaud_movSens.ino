#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#define LED_ON    HIGH
#define LED_OFF   LOW
// Define the keypad layout
const byte ROWS = 4;
const byte COLS = 4;

const int LED_R = 6;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte colPins[COLS] = { 39, 38, 37, 36 };
byte rowPins[ROWS] = { 35, 34, 33, 32 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int PIR_PIN = 52;                    // Motion sensor input pin
const int LDR_PIN = A0;                    // buzPhoto resistor input pin
const int BUZZER_PIN = 11;                 // Buzzer output pin
const int AUTHENTICATION_TIMEOUT = 60000;  // Timeout for authentication in milliseconds

bool authenticated = false;             // Flag to keep track of authentication status
unsigned long authenticationStartTime;  // Time when authentication started


bool motionDetected = false;
int lightLevel = 0;

const String password = "3131";  // change
String input_password;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  input_password.reserve(10);  // maximum input characters is 33, change if needed
lcd.init(); // initialize the lcd
  lcd.backlight();  
}

void loop() {
  delay(200);
  if (!authenticated) {
    // Check if motion is detected and light level is low
    motionDetected = digitalRead(PIR_PIN);
    lightLevel = analogRead(LDR_PIN);
    Serial.println("Motion status:" + String(motionDetected));

    Serial.println("Light Level is:" + String(lightLevel));
    delay(200);
    if (motionDetected && lightLevel < 300) {
      authenticationStartTime = millis();
      // Wait for keypad input for 1 minute
      Serial.println("Please Enter the password:");
      while (1) {
   
        char key = keypad.getKey();
        if (key) {
          Serial.println(key);
          if (key == '*') {
            input_password = "";  // clear input password
          } else if (key == '#') {
            if (password == input_password) {
              Serial.println("Welcome");

              delay(5000);
              authenticated=true; 

              break;
            } else {
              Serial.println("password is incorrect, try again");
            }
            input_password = "";  // clear input password
          } else {
            input_password += key;  // append new character to input password string
            Serial.println("The current password:"+input_password);
          }
        }

        if ((millis() - authenticationStartTime) >= 60000) {
          break;
        }
      }
      
      if (!authenticated) {
        // Trigger the buzzer if authentication fails
        Serial.println("Sound alert.");
        digitalWrite(BUZZER_PIN, 1);
        tone(BUZZER_PIN, 500, 10000); 
        digitalWrite(LED_R, LED_ON);
        delay(5000);
        digitalWrite(BUZZER_PIN, 0);
        digitalWrite(LED_R, LED_OFF);
      }
      authenticated=false;
    }

  }
 
}
