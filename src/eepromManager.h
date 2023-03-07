

void storeCredentials() {
  for(int i = 0; i < 33; i++){
    EEPROM.update(i, ssid[i]);
  }
  EEPROM.update(99, 1);

  for(int t = 33; t < 97; t++){
    int index = t-33;
    EEPROM.update(t, pass[index]);
  }
  EEPROM.update(100, 1);
}

void retreiveCredentials() {
  EEPROM.get(0,ssid);
  EEPROM.get(33,pass);
  
  Serial.print("Ssid from EEPROM: ");
  Serial.println(ssid);
  Serial.print("Pass from EEPROM: ");
  Serial.println(pass);
}

void clearCredentials() {
  EEPROM.update(99,0);
  EEPROM.update(100,0);
  resetFunc();
}

bool credentialsSaved(){
  int ssidSaved = EEPROM.read(99);
  int passSaved = EEPROM.read(100);
  if(passSaved==0 || ssidSaved==0) return false;
  else return true;
}
