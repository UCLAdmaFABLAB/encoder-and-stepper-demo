void setTimer(long time){
  timerInterval = time;
  timerFire = millis();
  timerIsRunning = true;
}

//---------------------------------------------------------------------

bool checkTimer(){
  bool done = false;

  if(timerIsRunning){
    if(millis() - timerFire > timerInterval){
      timerIsRunning = false;
      done = true;
    }
  }

  return done;

}