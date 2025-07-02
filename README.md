# 🔐 Smart Arduino Home Security System with Password-Enabled Alarm and Multi-Sensor Control

This project is a microcontroller-based home security system built on the **Arduino Uno**. It combines multiple environmental and motion sensors with a **custom 4-button password mechanism**, providing multi-layered security control. It uses **one-wire** and **I2C communication protocols** to interact with peripherals like the **DHT11 temperature/humidity sensor** and a **16x2 LCD display**.

---

## 🧰 Components & Features

### 🔍 Sensors & Modules Used:
- **DHT11** (One-wire): Temperature and humidity monitoring
- **PIR Sensor**: Detects motion/intrusion
- **Flame Sensor**: Detects infrared radiation (fire/smoke)
- **Photoresistor (LDR)**: Detects low light (darkness)
- **Reed Switches (KY-025, KY-021)**: Door status detection
- **16x2 LCD** (I2C): Displays temperature and humidity in real time
- **Passive Buzzer**: Sound alarm
- **LED Indicators**: Status signaling for all alerts

### 🔐 Security Logic:
- **Password Activation/Deactivation** using 4 buttons:
  - `PSW`: Enter password mode
  - `UP`, `DWN`: Increment password counter
  - `OK`: Confirm input
- Password Sequence: e.g. UP x2 + OK, DWN x3 + OK, etc.
- Alarm triggers on:
  - Door opening (reed switch)
  - Motion detection (PIR)
  - Fire/smoke detection (flame sensor)
  - Temperature > 40°C or Humidity > 160%
  - Darkness (photoresistor)

### 🧠 Behavior Overview:
- Alarm system arms only after password is verified
- Alarm deactivates with correct password
- Serial Monitor logs real-time data and system status
- LEDs light up corresponding to triggered sensor zones
- LCD continuously displays current temperature and humidity

---

## 💾 Code Versions

| Version | Description |
|---------|-------------|
| `v1`    | Sensor integration test (DHT11, PIR, etc.) |
| `v2`    | Password system logic and validation |
| `v3`    | Full system integration and working prototype |

---

## 🛠️ Tools & Communication

- **Platform**: Arduino Uno
- **Protocols**: I2C (LCD), One-wire (DHT11)
- **Development Tools**: Arduino IDE, Serial Monitor
- **Libraries Used**: 
  - `DHT.h`
  - `LiquidCrystal_I2C.h`
  - Custom debounce/password logic

---

## 📚 Future Improvements
- GSM/IoT integration for remote alerts
- Keypad or touchscreen input for full password entry
- Add real-time clock (RTC) for timestamped logs

---

## 👨‍💻 Author

**Samuel Oladosu**  
- 📫 [samueloladosu37@gmail.com](mailto:samueloladosu37@gmail.com)  
- 🔗 [LinkedIn](https://www.linkedin.com/in/samueloladosu/)  
