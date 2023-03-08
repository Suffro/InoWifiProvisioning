
#include <InoWiFiProvisioning.h>

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("Serial ready.");
  Serial.println();
  initProvisioningServer();
}

void loop() {
  checkResetButton();
  handleProvisioningServer();
  if(WiFi.status() == WL_CONNECTED){
    // do your stuff
  }
}


