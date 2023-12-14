
void motorRotateDegrees() {
  stepper.rotate(360);
}

//---------------------------------------------------------------------

void checkMotorHome() {
  // put your main code here, to run repeatedly:
  int reedValue = digitalRead(REED_SWITCH_PIN);
  if (reedValue == LOW) {
    motorIsHome = true;
  } else if (reedValue == HIGH) {
    motorIsHome = false;
  }
}

//---------------------------------------------------------------------