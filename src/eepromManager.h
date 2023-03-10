
void storeCredentials() {
  for(int i = 0; i < 33; i++){
    EEPROM.update(i, ssid[i]);
  }
  EEPROM.update(99, 1);

  for(int t = 33; t < 98; t++){
    int index = t-33;
    EEPROM.update(t, pass[index]);
  }
  EEPROM.update(100, 1);
  delay(10);
  EEPROMCommit();
}

void retreiveCredentials() {
  for(int i = 0; i<33; i++){
    ssid[i] = EEPROM.read(i);
  }
  for(int i = 33; i<98; i++){
    pass[i-33] = EEPROM.read(i);
  }
  
  Serial.print("Ssid from EEPROM: ");
  Serial.println(ssid);
  Serial.print("Pass from EEPROM: ");
  Serial.println(pass);
}

void clearCredentials() {
  Serial.println("Clearing credentials...");
  EEPROM.update(99,0);
  EEPROM.update(100,0);
  delay(10);
  EEPROMCommit();
  delay(100);
  resetFunc();
}

bool credentialsSaved(){
  int ssidSaved = EEPROM.read(99);
  int passSaved = EEPROM.read(100);
  if(passSaved!=1 || ssidSaved!=1) return false;
  else return true;
}
