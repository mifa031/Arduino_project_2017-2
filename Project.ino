#include <SPI.h>
#include <Phpoc.h>
#include <TimeLib.h>
#include <TM1637.h>
#include "button_LED.h"


#define CLK 3
#define DIO 2

#define BUTTON1 10
#define BUTTON2 9
#define BUTTON3 8

#define RLED 7
#define YLED 6
#define BLED 5
#define GLED 4


int yr, mo, da, hr, mi, sec;

TM1637 watchDisplay(CLK, DIO);


//char server_name[] = "121.128.151.144";
char server_name[] = "www.arduino.cc";
PhpocClient client;
PhpocDateTime datetime;

void setup() {
  Serial.begin(9600);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
  
  if(client.connect(server_name, 80))
  {
    Serial.println("Connected to server");
    client.println("GET / HTTP/1.0");
    //client.println("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36");
    client.println();
  }
  else
    Serial.println("connection failed");

  hr = datetime.hour();
  mi = datetime.minute();
  sec = datetime.second();
  da = datetime.day();
  mo = datetime.month();
  yr = datetime.year();
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

boolean debounceB(boolean lastB){
  boolean currentB = digitalRead(BUTTON3);

  if(lastB != currentB){
    delay(5);
    currentB = digitalRead(BUTTON3);
  }
  return currentB;
}

void button_LED(void){
  currentRButton = debounceR(lastRButton);
  currentBButton = debounceB(lastBButton);
  currentYButton = debounceY(lastYButton);
  if(lastRButton == LOW && currentRButton == HIGH){
    ledR = !ledR;
    ledB = false;
    ledY = false;
    if(ledR == false)
      ledR = true;
  }
  else if(lastBButton == LOW && currentBButton == HIGH){
    ledB = !ledB;
    ledR = false;
    ledY = false;
    if(ledB == false)
      ledR = true;
    else
      ledR = false;
  }
  else if(lastYButton == LOW && currentYButton == HIGH){
    ledY = !ledY;
    ledR = false;
    ledB = false;
    if(ledY == false)
      ledR = true;
    else
      ledR = false;
  }
  lastRButton = currentRButton;
  lastBButton = currentBButton;
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
  //watchDisplay.point(POINT_ON);
   
  
}

void loop() {
  button_LED();
  watch();

  if(client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if(!client.connected())
  {
    Serial.println("disconnected");
    client.stop();
    while(1)
    ;
  }
}
