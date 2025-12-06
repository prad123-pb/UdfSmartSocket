/*
 *    Copyright 2025 UDFOwner
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    More details: https://udfsoft.com/
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <WiFiManager.h>  // lib tzapu/WiFiManager

#include <WiFiClientSecure.h>

#define APP_VERSION "1"
#define DEVICE_ID "XXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // YOUR DEVICE ID, to get it write to us: support@udfsoft.com

#define ENDPOINT_URL "https://smart.udfsoft.com/api/device/status"

#define API_KEY "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"  // YOUR API Key, to get it write to us: support@udfsoft.com

#define LED_PIN 1
#define RELAY_PIN 0  // GPIO0

unsigned long lastCheck = 0;

void setup() {
  Serial.begin(115200);
  setupRelay();
  printDeviceInfo();

  // setupLedPin();
  setupWifi();
}

void loop() {
  // checkCommand();
  // delay(10000);  // 10 sec

  if (millis() - lastCheck >= 10000) {
    lastCheck = millis();
    checkCommand();
  }

  yield();
}

void setupRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void setupLedPin() {
  pinMode(LED_PIN, OUTPUT);     // GPIO1 (TX)
  digitalWrite(LED_PIN, HIGH);
}

void setupWifi() {
  WiFiManager wm;

  //for test
  // wm.resetSettings();

  wm.setConnectTimeout(120);  // 2 mins
  wm.setConfigPortalTimeout(300);

  // If the connection fails, the configurator will start
  if (!wm.autoConnect("SMART_SOCKET_AP", "12345678")) {
    Serial.println("Failed to connect, rebooting...");
    ESP.restart();
  }

  Serial.println("Connected to WiFi!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void printDeviceInfo() {

  Serial.println(" ======================= ");
  Serial.println("   Hi, I'm smart device)");
  Serial.println("   Device ID: " + String(DEVICE_ID));
  Serial.println("   App version: " + String(APP_VERSION));
  Serial.println(" ======================= ");
}

void checkCommand() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting WiFi...");
    WiFi.reconnect();
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();  // ⚠️ disable certificate verification

  HTTPClient https;

  https.setTimeout(15000);
  https.setReuse(true);  // keep-alive on

  https.begin(client, ENDPOINT_URL);
  https.addHeader("Content-Type", "application/json");
  https.addHeader("X-Api-Key", String(API_KEY));
  https.addHeader("X-DEVICE-ID", String(DEVICE_ID));

  https.addHeader("X-APP-VERSION", String(APP_VERSION));


  int httpResponseCode = https.GET();

  Serial.print("HTTPS Response code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode == 200) {
    Serial.println("SmartSocket ON");
    digitalWrite(RELAY_PIN, LOW);
  } else if (httpResponseCode == 423) {
    Serial.println("SmartSocket OFF");
    // Выключить реле
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("Unexpected code: ");
    Serial.println(httpResponseCode);
  }

  https.end();
}
