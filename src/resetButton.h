
// this code is needed if you want to set an external button that pressed clears the credentials and start a new connection flow.

void checkResetButton(){
  if(!buttonUsed) return;
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    Serial.println();
    Serial.println("Resetting...");
    Serial.println();
    clearCredentials();
  }
}