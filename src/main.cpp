#include <Arduino.h>   // WAJIB
#include "gateway.h"

void setup() {
  Serial.begin(115200);
  setupGateway();
}

void loop() {
  loopGateway();
}