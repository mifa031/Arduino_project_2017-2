#include <SPI.h>
#include <Phpoc.h>
#include <TimeLib.h>
#include "TM1637.h"
#include "button_LED.h"


#define CLK 3
#define DIO 2

#define BUTTON1 7
#define BUTTON2 6
#define BUTTON3 5

#define RLED 12
#define YLED 11
#define GLED 10
#define BLED 9


int yr, mo, da, hr, mi, sec;

TM1637 watchDisplay(CLK, DIO);


char server_name[] = "121.128.151.144";
PhpocClient client;
PhpocDateTime datetime;

void setup() {
  Serial.begin(9600);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
  if(client.connect(server_name, 80))
  {
    Serial.println("Connected to server");
    client.println("GET /arduino_time.php?room_num=1&set=0 HTTP/1.0");
    client.println();
  }
  else
    Serial.println("connection failed");

  if(client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if(!client.connected())
  {
    Serial.println("disconnected");
    client.stop();
  }

  
  
  int tt;
  
  tt = datetime.hour();
  hr = tt;
  tt = datetime.minute();
  mi = tt;
  tt = datetime.second();
  sec = tt;
  tt = datetime.day();
  da = tt;
  tt = datetime.month();
  mo = tt;
  tt = datetime.year();
  yr = tt;
  Serial.println(yr);
  Serial.println(mo);
  Serial.println(da);
  Serial.println(hr);
  Serial.println(mi);
  Serial.println(sec);
  
  setTime(hr, mi, sec, da, mo, yr);
  
  watchDisplay.init();
  watchDisplay.set(BRIGHT_TYPICAL);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
}

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

boolean debounceG(boolean lastG){
  boolean currentG = digitalRead(BUTTON3);

  if(lastG != currentG){
    delay(5);
    currentG = digitalRead(BUTTON3);
  }
  return currentG;
}

void button_LED(void){
  currentRButton = debounceR(lastRButton);
  currentGButton = debounceG(lastGButton);
  currentYButton = debounceY(lastYButton);
  if(lastRButton == LOW && currentRButton == HIGH){
    ledR = !ledR;
    ledG = false;
    ledY = false;
    if(ledR == false)
      ledB = true;
    else
      ledB = false;
  }
  else if(lastGButton == LOW && currentGButton == HIGH){
    ledG = !ledG;
    ledR = false;
    ledY = false;
    if(ledG == false)
      ledB = true;
    else
      ledB = false;
  }
  else if(lastYButton == LOW && currentYButton == HIGH){
    ledY = !ledY;
    ledR = false;
    ledG = false;
    if(ledY == false)
      ledB = true;
    else
      ledB = false;
  }
  lastRButton = currentRButton;
  lastGButton = currentGButton;
  lastYButton = currentYButton;

  digitalWrite(RLED, ledR);
  digitalWrite(GLED, ledG);
  digitalWrite(YLED, ledY);
  digitalWrite(BLED, ledB);
}

void watch(void){
  int8_t numTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int8_t listDisp[4] = {0};

  listDisp[0] = hour() / 10;
  listDisp[1] = hour() % 10;
  listDisp[2] = minute() / 10;
  listDisp[3] = minute() % 10;
 
  watchDisplay.display(0, listDisp[0]);
  watchDisplay.display(1, listDisp[1]);
  watchDisplay.display(2, listDisp[2]);
  watchDisplay.display(3, listDisp[3]);
  watchDisplay.point(POINT_ON);
   
  
}

void loop() {
  button_LED();
  watch();
}
