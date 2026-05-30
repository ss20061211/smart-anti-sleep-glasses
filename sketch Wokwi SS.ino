#define BLYNK_TEMPLATE_ID "TMPL6rfpdzX2w"
#define BLYNK_TEMPLATE_NAME "Smart Anti Sleep Glasses Wokwi"
#define BLYNK_AUTH_TOKEN "nWOfO1o1FGSNS_HejsnwqFgYRX60-h5a"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <MPU6050.h>

// WiFi (Wokwi default)
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

MPU6050 mpu;

// Pins
int buttonPin = 10;   // Eye blink (push button)
int potPin = 4;       // Potentiometer
int buzzerPin = 12;
int ledPin = 13;

// Variables
int potValue;
bool buttonPressed;
int16_t ax, ay, az;

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Wire.begin();
  mpu.initialize();

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("System Started...");
}

void loop() {
  Blynk.run();  // Required for Blynk

  // Reset outputs
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  // Read inputs
  buttonPressed = (digitalRead(buttonPin) == LOW);
  potValue = analogRead(potPin);
  mpu.getAcceleration(&ax, &ay, &az);

  int tilt = abs(ax) + abs(ay);

  // Send data to Blynk
  Blynk.virtualWrite(V1, potValue > 3000);   // Vibration
  Blynk.virtualWrite(V2, buttonPressed);     // Eye Blink
  Blynk.virtualWrite(V3, tilt);              // Tilt

  // Alert Status (V4)
  if (buttonPressed || potValue > 3000 || tilt > 20000) {
    Blynk.virtualWrite(V4, 1);
  } else {
    Blynk.virtualWrite(V4, 0);
  }

  // Serial Monitor
  Serial.print("Button: ");
  Serial.print(buttonPressed);
  Serial.print(" | Pot: ");
  Serial.print(potValue);
  Serial.print(" | Tilt: ");
  Serial.println(tilt);

  // System Logic

  //  Eye Blink → LED
  if (buttonPressed) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Eye Blink Detected → LED ON");
  }

  //  Head Movement → Buzzer
  else if (tilt > 20000) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Head Movement → Buzzer ON");
  }

  //  Vibration → BOTH
  else if (potValue > 3000) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Serial.println("Vibration Detected → LED + Buzzer ON");
  }

  // Normal
  else {
    Serial.println("Normal State");
  }

  delay(300);
}