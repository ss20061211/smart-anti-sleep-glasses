#define BLYNK_TEMPLATE_ID "TMPL6KTYrEQPf"
#define BLYNK_TEMPLATE_NAME "Smart Anti Sleep Glasses"
#define BLYNK_AUTH_TOKEN "kMuVwZef3mkDzAS8fvAtPch0-zJwGIbo"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <MPU6050.h>

char ssid[] = "Susein";
char pass[] = "Susein1211";

BlynkTimer timer;
MPU6050 mpu;

// Pins
int eyePin = 5;     // IR Eye Blink Sensor
int vibPin = 4;      // Vibration Sensor
int buzzerPin = 6;
int ledPin = 13;

// Variables
bool eyeClosed;
bool vibrationDetected;
int16_t ax, ay, az;

// This function runs every second
void sendSensorData() {

  // Read sensors
  eyeClosed = (digitalRead(eyePin) == LOW);   // adjust if needed
  vibrationDetected = (digitalRead(vibPin) == HIGH);

  mpu.getAcceleration(&ax, &ay, &az);
  int tilt = abs(ax) + abs(ay);

  Serial.print("Eye: ");
  Serial.print(eyeClosed);
  Serial.print(" | Vib: ");
  Serial.print(vibrationDetected);
  Serial.print(" | Tilt: ");
  Serial.println(tilt);

  // Reset outputs
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  // 1Eye blink → LED
  if (eyeClosed) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Blynk.virtualWrite(V2, 1);
  }

  // 2️Head movement → Buzzer
  else if (tilt > 1000) {
    digitalWrite(buzzerPin, HIGH);
    Blynk.virtualWrite(V3, tilt);
  }

  // 3Vibration → BOTH
  else if (vibrationDetected) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Blynk.virtualWrite(V1, 1);
  }

  // 4️Normal
  else {
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(eyePin, INPUT);
  pinMode(vibPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Wire.begin(8,9);
  mpu.initialize();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Run function every 1 second (like example)
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
