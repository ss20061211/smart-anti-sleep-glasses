# 😴 Smart Anti-Sleep Glasses (Blynk IoT)

A wearable IoT safety system designed to detect drowsiness in real time using an ESP32 microcontroller, MPU6050 accelerometer, and Blynk cloud dashboard. The system monitors eye blinks, head tilt, and vibration to alert the user before sleep-related accidents occur.

---

## 📌 Project Overview

Drowsy driving and fatigue-related accidents are a major safety concern. This project simulates a **smart glasses system** that detects signs of drowsiness and immediately triggers alerts (buzzer + LED) while sending live sensor data to a cloud dashboard via the **Blynk IoT platform**.

The simulation is built and tested using **Wokwi** (an online ESP32 simulator), making it accessible without physical hardware.

---

## 🔗 Links

| Resource | URL |
|---|---|
| 🔬 Wokwi Simulation | https://wokwi.com/projects/465235636528953345 |
| 📊 Blynk Dashboard |<img width="339" height="730" alt="image" src="https://github.com/user-attachments/assets/8fde4734-122c-44d2-9cd9-d6b7be4cfab9" />
 |

---

## 🧰 Components Used

| Component | Role |
|---|---|
| **ESP32** | Main microcontroller with built-in Wi-Fi |
| **MPU6050** | Gyroscope/Accelerometer — detects head tilt/movement |
| **Push Button** | Simulates eye blink detection |
| **Potentiometer** | Simulates vibration sensor |
| **Buzzer** | Audio alert on drowsiness detection |
| **LED** | Visual alert on drowsiness detection |
| **Blynk IoT** | Cloud platform for real-time monitoring dashboard |
| **Wokwi** | Online ESP32 simulator used for testing |

---

## ⚙️ System Features

- 👁️ **Eye Blink Detection** — A push button simulates the blink sensor. When pressed, the LED turns ON.
- 🤕 **Head Tilt Detection** — The MPU6050 reads acceleration data. If tilt exceeds threshold (`20000`), the buzzer sounds.
- 📳 **Vibration Detection** — A potentiometer simulates a vibration sensor. If value exceeds `3000`, both the LED and buzzer activate.
- ☁️ **Blynk Cloud Integration** — Sensor data is sent in real time to the Blynk dashboard via virtual pins:
  - `V1` → Vibration alert status
  - `V2` → Eye blink status
  - `V3` → Tilt value
  - `V4` → Overall alert status (1 = alert triggered, 0 = normal)
- 🔔 **Alert Logic Summary:**

| Condition | LED | Buzzer |
|---|---|---|
| Eye blink detected | ✅ ON | ❌ OFF |
| Head tilt > 20000 | ❌ OFF | ✅ ON |
| Vibration > 3000 | ✅ ON | ✅ ON |
| Normal state | ❌ OFF | ❌ OFF |

---

## 📐 Circuit / Pin Configuration

| Pin | Component |
|---|---|
| GPIO 10 | Push Button (Eye Blink) |
| GPIO 4 | Potentiometer (Vibration) |
| GPIO 12 | Buzzer |
| GPIO 13 | LED |
| I2C (SDA/SCL) | MPU6050 |

---

## 🚀 How to Run the Simulation

### Option A — Run on Wokwi (No Hardware Needed)

1. Visit the simulation link: [https://wokwi.com/projects/465235636528953345](https://wokwi.com/projects/465235636528953345)
2. Click the **▶ Play** button to start the simulation.
3. Interact with the push button and potentiometer to simulate sensor inputs.
4. Observe the Serial Monitor for real-time output.

### Option B — Deploy to Real ESP32 Hardware

1. **Install Arduino IDE** from [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. **Install the ESP32 board package:**
   - Go to `File > Preferences`
   - Add this URL to "Additional Boards Manager URLs":  
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Go to `Tools > Board > Boards Manager`, search `esp32`, and install.
3. **Install required libraries** via `Sketch > Include Library > Manage Libraries`:
   - `Blynk`
   - `MPU6050` by Electronic Cats
4. **Update WiFi credentials** in the code:
   ```cpp
   char ssid[] = "Your_WiFi_Name";
   char pass[] = "Your_WiFi_Password";
   ```
5. **Update Blynk credentials** (already in the code):
   ```cpp
   #define BLYNK_TEMPLATE_ID "TMPL6rfpdzX2w"
   #define BLYNK_TEMPLATE_NAME "Smart Anti Sleep Glasses Wokwi"
   #define BLYNK_AUTH_TOKEN "nWOfO1o1FGSNS_HejsnwqFgYRX60-h5a"
   ```
6. Connect your ESP32 via USB, select the correct **COM port** and **Board**, then click **Upload**.

---

## 📊 Blynk Dashboard Setup

1. Create a free account at [https://blynk.io](https://blynk.io)
2. Create a new **Template** named `Smart Anti Sleep Glasses Wokwi`
3. Add the following **Datastreams** (Virtual Pins):

| Virtual Pin | Name | Data Type |
|---|---|---|
| V1 | Vibration | Integer (0/1) |
| V2 | Eye Blink | Integer (0/1) |
| V3 | Tilt Value | Integer |
| V4 | Alert Status | Integer (0/1) |

4. Add widgets to your dashboard:
   - **LED Indicator** → V2 (Eye Blink)
   - **LED Indicator** → V1 (Vibration)
   - **Gauge / Value Display** → V3 (Tilt)
   - **LED / Notification** → V4 (Alert Status)

---

---

## 🧪 Serial Monitor Output (Sample)

```
System Started...
Button: 0 | Pot: 512 | Tilt: 3200
Normal State
Button: 1 | Pot: 512 | Tilt: 3200
Eye Blink Detected → LED ON
Button: 0 | Pot: 3500 | Tilt: 3200
Vibration Detected → LED + Buzzer ON
Button: 0 | Pot: 512 | Tilt: 25000
Head Movement → Buzzer ON
```

---

## 📚 Libraries & Dependencies

| Library | Version | Source |
|---|---|---|
| `WiFi.h` | Built-in (ESP32) | Arduino ESP32 Core |
| `BlynkSimpleEsp32.h` | Latest | [Blynk Library](https://github.com/blynkkk/blynk-library) |
| `Wire.h` | Built-in | Arduino Core |
| `MPU6050.h` | Latest | [Electronic Cats](https://github.com/ElectronicCats/mpu6050) |

---

## 🙋 Author

> Developed as part of an IoT project using Wokwi simulation and Blynk cloud integration.

---

## 📄 License

This project is open-source and free to use for educational purposes.
