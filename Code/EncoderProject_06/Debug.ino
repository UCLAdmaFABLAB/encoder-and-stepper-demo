void consoleLog() {
  Serial.print("zero: ");
  Serial.println(encoderIsZeroed);
  Serial.print("last zero: ");
  Serial.println(lastKnownEncoderZero);
  Serial.print("current encoder: ");
  Serial.println(oldEncoderPosition);
  Serial.print("encoder home: ");
  Serial.println(CWEncoderHome);
}

//---------------------------------------------------------------------

void reportState(){
  Serial.print("STATE: ");
  Serial.println(state);
}

//---------------------------------------------------------------------

void reportAngle(){

  if(millis() - SerialTimerFire > SerialTimerInterval){
    Serial.println(encoderPositionDegrees);
 //   Serial.print( " | ");
 //   Serial.println(motorMovementAcum);
    SerialTimerFire = millis();
  }
}

//---------------------------------------------------------------------

void report(int n){
  Serial.println(n);
}