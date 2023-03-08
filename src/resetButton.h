
// this code is needed if you want to set an external button that pressed clears the credentials and start a new connection flow.

const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void checkResetButton(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    Serial.println();
    Serial.println("Resetting...");
    Serial.println();
    clearCredentials();
  }
}
