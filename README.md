# Smart Socket (ESP8266 (ESP-01s) + 5V relay module)

![Smart Socket](https://img.shields.io/badge/ESP8266-WiFiManager-blue)
![License](https://img.shields.io/badge/License-Apache%202.0-green)

[official page](https://udfsoft.com/) 

**Smart Socket** is a simple solution for remote control of a relay socket based on **ESP8266 (ESP-01S)**.  
The device periodically polls a server, receives an **ON / OFF** command, and controls the relay accordingly.

---

## 📌 Features

- Wi-Fi connection via [WiFiManager](https://github.com/tzapu/WiFiManager) (AP + Captive Portal)  
- Relay control through a server API (`https://smart.udfsoft.com/api/device/status`)  
- HTTPS support (with keep-alive for faster requests)  
- Simple ON/OFF logic for the smart socket  
- Optional LED indicator (GPIO1)  
- Non-blocking loop using `millis()` + `yield()` for stable Wi-Fi and watchdog operation  

---

## ⚙️ Requirements

- **ESP8266 (ESP-01S)**  
- Arduino IDE or PlatformIO  
- Arduino libraries:
  - [ESP8266WiFi](https://github.com/esp8266/Arduino)  
  - [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient)  
  - [WiFiManager](https://github.com/tzapu/WiFiManager)  

---

## 🛠 Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/smart-socket.git
```
2. Open the project in Arduino IDE or PlatformIO.

3. Install the required libraries via Library Manager:

    * ESP8266WiFi
    * ESP8266HTTPClient
    * WiFiManager

4. In the code, replace the following with your( support@udfsoft.com ) values:
   ```cpp
   #define DEVICE_ID "YOUR_DEVICE_ID"
   #define API_KEY "YOUR_API_KEY"
   ```
5. Upload the firmware to your ESP8266 (ESP-01S).

---

## 💡 Usage

1. On startup, ESP will create an access point SMART_SOCKET_AP.

2. Connect to it and configure Wi-Fi through the WiFiManager portal.

3. The device will connect to your network and start polling the server every 10 seconds:

  * HTTP 200 → relay ON
  * HTTP 423 → relay OFF

## 🔧 Relay and LED Configuration

  * RELAY_PIN: GPIO0 (connect to your relay)
  * LED_PIN: GPIO1 (TX, optional for status LED)
  * HIGH / LOW to turn ON/OFF depends on your relay module type.

---

## ⚠️ Notes

client.setInsecure() is used for HTTPS — certificate verification is disabled.

The loop uses yield() and millis() to keep Wi-Fi stable and avoid watchdog resets.

If Wi-Fi is lost, ESP automatically tries to reconnect.

## 📄 License

This project is licensed under the [Apache 2.0 License(https://www.apache.org/licenses/LICENSE-2.0).

```Copyright 2025 UDFOwner```
🔗 Useful Links

  * [WiFiManager GitHub](https://github.com/tzapu/WiFiManager)
  * [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
  * [UDFSoft Smart Device API](https://udfsoft.com/) (Coming soon) support@udfsoft.com

## 📷 Photo (example)
![<img src="IMG_20251205_235617.jpg" alt="Device preview" width="100">](IMG_20251205_235617.jpg)
![<img src="IMG_20251205_235920.jpg" alt="Device preview" width="100">](IMG_20251205_235920.jpg)
![<img src="IMG_20251205_235934.jpg" alt="Device preview" width="100">](IMG_20251205_235934.jpg)
![<img src="IMG_20251206_102323.jpg" alt="Device preview" width="100">](IMG_20251206_102323.jpg)

## 🔧 Author: udfowner
