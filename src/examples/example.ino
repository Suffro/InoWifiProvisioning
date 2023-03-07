
#include <InoWiFiProvisioning.h>

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial ready.");
  Serial.println();
  initProvisioningServer();
}

void loop() {
  handleProvisioningServer();
  if(WiFi.status() == WL_CONNECTED){
    // do your stuff
  }
}

