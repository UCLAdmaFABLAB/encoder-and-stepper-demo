
void handleLEDs() {
 

  if (encoderIsHome) {
    digitalWrite(ENCODER_HOME_LED, HIGH);
  } else {
    digitalWrite(ENCODER_HOME_LED, LOW);
  }

   if (motorIsHome) {
    digitalWrite(MOTOR_HOME_LED, HIGH);
  } else {
    digitalWrite(MOTOR_HOME_LED, LOW);
  }
}

//---------------------------------------------------------------------

void blinkLED(){
  digitalWrite(MODE_LED, modeLedState);
  if(millis() - lastLedSwitch > ledInterval){
    lastLedSwitch = millis();
    modeLedState = !modeLedState;
  }


}

//---------------------------------------------------------------------