# Smart Bag with Child & Women Safety Alerts 🎒🛡️

## 📌 Overview
The Smart Safety Bag is an IoT-based personal security system designed to protect children and women during travel. It integrates GPS-based real-time location tracking, emergency alert notifications, RFID attendance monitoring, and tamper detection intelligence to ensure safety against kidnapping, harassment, and theft.

The system automatically sends alerts to parents/guardians via Telegram with a live Google Maps link when emergency conditions are detected.

---

## 🧠 Key Features
✅ Real-time GPS location tracking  
✅ SOS emergency button for distress alert  
✅ RFID-based arrival/departure notifications  
✅ Accelerometer-based tamper & throw detection  
✅ Cloud-based alert service using Telegram Bot API  
✅ Portable, lightweight design embedded in a normal bag  

---

## 🛠️ Components Used

| Component | Quantity |
|----------|---------|
| ESP32 Development Board | 1 |
| NEO-6M GPS Module | 1 |
| MFRC522 RFID Module + RFID Tag | 1 |
| ADXL345 Accelerometer | 1 |
| SOS Push Button | 1 |
| 3.7V Li-ion Battery | 1 |
| Jumper Wires & Breadboard | As required |

---

## 🔧 System Architecture
ESP32 is the central controller which reads data from RFID, GPS, and Accelerometer sensors, detects emergency events, and communicates alerts to parents using Wi-Fi + Telegram Cloud API.

---

## 🏗️ Working Methodology

| Safety Feature | Trigger Condition | Action Taken |
|---------------|-----------------|--------------|
| SOS Button Pressed | Manual alert | Sends instant emergency message with live location |
| Bag thrown/freefall detected | Tampering or kidnapping attempt | Sends alert with location |
| RFID scanned | User entering/exiting safe zone | Sends arrival/departure notification |
| Location Update during SOS | Every 2 mins | Repeated live tracking |

---

## 🔗 Software Requirements
- Arduino IDE
- Telegram Bot API
- Libraries:
  - `TinyGPS++`
  - `Adafruit_ADXL345_U`
  - `MFRC522.h`
  - `WiFi.h`
  - `HTTPClient.h`

---

## 📲 Telegram Bot Setup
1️⃣ Create a bot using **@BotFather**  
2️⃣ Copy the **Bot Token** and paste it into code  
3️⃣ Get your **Chat ID** using:  
