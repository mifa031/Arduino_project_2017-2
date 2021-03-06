#ifndef BUTTON1
#define BUTTON1 5
#define BUTTON2 6
#define BUTTON3 7
#endif

boolean lastRButton=LOW;
boolean currentRButton=LOW;
boolean lastBButton=LOW;
boolean currentBButton=LOW;
boolean lastYButton=LOW;
boolean currentYButton=LOW;

boolean ledR = true;
boolean ledB = false;
boolean ledY = false;
boolean ledG = false;

boolean debounceR(boolean lastR){
  boolean currentR = digitalRead(BUTTON1);

  if(lastR != currentR){
    delay(5);
    currentR = digitalRead(BUTTON1);
  }
  return currentR;
}

boolean debounceY(boolean lastY){
  boolean currentY = digitalRead(BUTTON2);

  if(lastY != currentY){
    delay(5);
    currentY = digitalRead(BUTTON2);
  }
  return currentY;
}

boolean debounceB(boolean lastB){
  boolean currentB = digitalRead(BUTTON3);

  if(lastB != currentB){
    delay(5);
    currentB = digitalRead(BUTTON3);
  }
  return currentB;
}
