#include <SPI.h>
#include <Phpoc.h>
#include <TimeLib.h>
#include <TM1637.h>
#include "LEDsetting.h"

#define CLK_S 2
#define LATCH 3
#define SER 4

#define BUTTON1 5
#define BUTTON2 6   
#define BUTTON3 7

#define DIO 8
#define CLK 9
/*
#define RLED 4
#define YLED 5
#define BLED 6
#define GLED 7
*/
int yr, mo, da, hr, mi, sec;

TM1637 watchDisplay(CLK, DIO);

char server_name[] = "121.128.151.144";

PhpocClient client;
PhpocDateTime datetime;

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK_S, OUTPUT);
/*
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  */
  Serial.begin(9600);
  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);  

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
}

void sendInfo(String status){ // status = mono, share, empty 중 하나
  String str = "GET /status.php?room_num=1&status=";
  str.concat(status);
  str.concat(" HTTP/1.0");
  Serial.println(str);
  if(client.connect(server_name, 80))
   {
     Serial.print("2");
       Serial.println("Connected to server");
       //client.println("GET /status.php?room_num=1&status=share HTTP/1.0");
       client.println(str);
       client.println();
   }
   while(client.available())
  { 
    Serial.print("3");
    char c = client.read();
  }
  client.flush();
   client.stop();
}

int mode0 = 1;
String s = "";
int RLED = 1;

void getLec(){
  if(mode0 == 1){
    if(second()%60 == 0){
      if(client.connect(server_name, 80))
      {
        Serial.print("1");
        Serial.println("Connected to server");
        client.println("GET /status.php?room_num=1 HTTP/1.0");
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

  //Serial.println(client.available());
  while(client.available())
  {
    char c = client.read();
   // Serial.print(c);
    s.concat(c);
    if(c == '\r' || c== '\n')
         s = "";
  }
    //Serial.println(s);
  
  if(!client.connected())
  {
    //Serial.println("disconnected");
    client.flush();
    client.stop();
  }
  if(s.equals("lec")){
    Serial.println("Success");
    ledG = true;
    /*ledR = false;
    ledB = false;
    ledY = false;*/
  }
  else{
    if(ledG == true){
      ledG = false;
      RLED = 1;
    }
  }
}

int currentLED = 0;

void button_LED(void){
  currentRButton = debounceR(lastRButton);
  currentBButton = debounceB(lastBButton);
  currentYButton = debounceY(lastYButton);

  if(ledG == true)
    currentLED = 1;
  else if(lastRButton == LOW && currentRButton == HIGH){
    /*ledR = true;
    ledB = false;
    ledY = false;*/
    currentLED = 8;
    sendInfo("empty");
  }
  else if(lastBButton == LOW && currentBButton == HIGH){
    /*ledB = true;
    ledR = false;
    ledY = false;*/
    currentLED = 2;
    sendInfo("mono");
  }
  else if(lastYButton == LOW && currentYButton == HIGH){
    /*ledY = true;
    ledR = false;
    ledB = false;*/
    currentLED = 4;
    sendInfo("share");
  }
  else if(RLED == 1){
    currentLED = 8;
    sendInfo("empty");
    RLED = 0;
  }
  
  lastRButton = currentRButton;
  lastBButton = currentBButton;
  lastYButton = currentYButton;

  digitalWrite(LATCH, LOW);
  shiftOut(SER, CLK_S, MSBFIRST, currentLED);
  digitalWrite(LATCH, HIGH);
/*
  digitalWrite(RLED, ledR);
  digitalWrite(GLED, ledG);
  digitalWrite(YLED, ledY);
  digitalWrite(BLED, ledB);
  */
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
