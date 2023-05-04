
#include "InoWifiProvisioning.h"

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial ready.");
  Serial.println();
  delay(10);
  initProvisioningServer();
}

void loop() {
  handleProvisioningServer();
  if(WiFi.status() == WL_CONNECTED){
    // do your stuff
  }
}

