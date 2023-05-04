
#include "InoWifiProvisioning.h"

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);
  Serial.println();
  Serial.println("Serial ready.");
  Serial.println();
  pinMode(BUTTON_PIN, INPUT);
  delay(10);
  if(digitalRead(BUTTON_PIN) == HIGH) buttonUsed = true;
  if(!buttonUsed) Serial.println("Button not detected");
  else Serial.println("Button detected");
  Serial.println();
  delay(10);
  initProvisioningServer();
}

void loop() {
  checkResetButton();
  handleProvisioningServer();
  if(WiFi.status() == WL_CONNECTED){
    // do your stuff
  }
}

