
void readEncoder() {
  long newEncoderPosition = myEnc.read();
  if (newEncoderPosition != oldEncoderPosition) {
    long encoderDelta = newEncoderPosition - oldEncoderPosition;
    encoderStepAcum += encoderDelta;
    encoderAcumDebug += encoderDelta;
     encoderTrackAcum += encoderDelta;
    encoderAcumRelativeToHome += encoderDelta;
    oldEncoderPosition = newEncoderPosition;
  }
}

//---------------------------------------------------------------------

void checkEncoderHome() {
  int margin = encoderHomeMargin * 1.0 * ENCODER_STEPS_PER_DEGREE;
  if (encoderHasZeroed) {
    if (((oldEncoderPosition < CWEncoderHome + margin) && (oldEncoderPosition > CWEncoderHome - margin)) || ((oldEncoderPosition < CCWEncoderHome + margin) && (oldEncoderPosition > CCWEncoderHome - margin))) {
      encoderIsHome = true;
      encoderAcumRelativeToHome = 0;
    } else {
      encoderIsHome = false;
    }
  }
}

//---------------------------------------------------------------------

void checkEncoderZ() {
  int encoderZValue = digitalRead(ENCODER_HOME_PIN);
  if (encoderZValue == LOW) {
    encoderAcumDebug = 0;
    encoderHasZeroed = true;
    encoderIsZeroed = true;
    lastKnownEncoderZero = oldEncoderPosition;
    calculateEncoderHomes();
  } else if (encoderZValue == HIGH) {
    encoderIsZeroed = false;
  }
}

//---------------------------------------------------------------------

void calculateEncoderHomes() {
  CWEncoderHome = lastKnownEncoderZero + int(encoderHomeOffset * 1.0 * ENCODER_STEPS_PER_DEGREE);
  CCWEncoderHome = lastKnownEncoderZero - int((360 - encoderHomeOffset) * 1.0 * ENCODER_STEPS_PER_DEGREE);
}

//---------------------------------------------------------------------