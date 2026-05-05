#include "gateway.h"
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

#define SCK 12
#define MISO 13
#define MOSI 11
#define CS 10

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

struct __attribute__((packed)) DataDevicePJU {
  char id[10];
  bool state;
  uint16_t vin;
  uint16_t crc;
};

DataDevicePJU device;

void setupGateway() {
  SPI.begin(SCK, MISO, MOSI, CS);

  Serial.println("Starting Ethernet...");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("❌ DHCP gagal");
  } else {
    Serial.println("✅ Ethernet Connected");
    Serial.print("IP: ");
    Serial.println(Ethernet.localIP());
  }
}

void loopGateway() {
  if (Serial.available()) {

    String json = Serial.readStringUntil('\n');

    Serial.println("\nRAW:");
    Serial.println(json);

    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, json);

    if (!error) {
      strcpy(device.id, doc["id"]);
      device.state = doc["state"];
      device.vin = doc["vin"];
      device.crc = doc["crc"];

      Serial.println("\nPARSED:");
      Serial.print("ID: "); Serial.println(device.id);
      Serial.print("STATE: "); Serial.println(device.state);
      Serial.print("VIN: "); Serial.println(device.vin);
      Serial.print("CRC: "); Serial.println(device.crc);
    } else {
      Serial.println("JSON ERROR");
    }
  }
}