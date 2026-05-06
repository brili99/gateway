#include <Arduino.h> // WAJIB
#include "gateway.h"

// Buat handling module Ebyte E220 header di folder include, dan file .cpp di folder cpp

void setup()
{
  Serial.begin(115200);
  setupGateway();
}

void loop()
{
  loopGateway();
  // loop event membaca incoming dari module, if (e220ttl.available()>1) dst
  // jika data berhasil diterima kirim ke httpserver misal pakai google.com asal kirim dulu
}