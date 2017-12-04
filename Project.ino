#include <SPI.h>
#include <Phpoc.h>
#include <TimeLib.h>
#include <TM1637.h>
#include "LEDsetting.h"

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

#define RLED 5
#define YLED 6
#define BLED 7
#define GLED 8


#define CLK 10
#define DIO 9

int yr, mo, da, hr, mi, sec;

TM1637 watchDisplay(CLK, DIO);

char server_name[] = "121.128.151.144";

PhpocClient client;
PhpocDateTime datetime;

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  
  Serial.begin(9600);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);  

  hr = datetime.hour();
  mi = datetime.minute();
  sec = datetime.second();
  da = datetime.day();
  mo = datetime.month();
  yr = datetime.year();
  
  setTime(hr, mi, sec, da, mo, yr);

  watchDisplay.init();
  watchDisplay.set(BRIGHT_TYPICAL);
}

int mode0 = 1;
String s = "";
void getLec(){
  if(mode0 == 1){
    if(second()%60 == 0){
      if(client.connect(server_name, 80))
      {
        Serial.println("Connected to server");
        client.println("GET /status.php?room_num=3 HTTP/1.0");
        client.println();
        mode0 = 0;
      }
      else{
        Serial.println("connection failed");
        mode0 = 0;
      }  
    }
  }

  if(second()%60 == 30){
    mode0 = 1;
  }

  Serial.println(client.available());
  while(client.available())
  {
    char c = client.read();
   // Serial.print(c);
    s.concat(c);
    if(c == '\r' || c== '\n')
         s = "";
  }
    Serial.println(s);
  
  delay(1000);
  
  if(!client.connected())
  {
    Serial.println("disconnected");
    client.stop();
  }
  if(s.equals("lec")){
    Serial.println("Success");
    ledG = true;
    ledR = false;
    ledB = false;
    ledY = false;
  }
  else{
    if(ledB == true || ledY == true){
    }
    else{
      ledR = true;
      ledG = false;
    }
  }
}

void button_LED(void){
  currentRButton = debounceR(lastRButton);
  currentBButton = debounceB(lastBButton);
  currentYButton = debounceY(lastYButton);

  if(ledG == true)
    ;
  else if(lastRButton == LOW && currentRButton == HIGH){
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
  watchDisplay.point(POINT_ON);
}

void loop() {
  watch();

  getLec();
  
  button_LED();
}
