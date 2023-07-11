
 // Notes: 
 // GT-521F32 can hold 200 fingerprint templates
#include "FPS_GT511C3.h"
#include "Adafruit_LiquidCrystal.h"


#define relayPin 8
#define buzzerPin 2
#define downButtonPin 6
#define upButtonPin 7

const int adminFinger = 0;
int currUser = -1;

bool menu = false;
bool isMenu = false;

const int delayEnterMenu = 5000;
const int delayDoor = 3000;
unsigned long currAdminPress;
unsigned long timeA;
boolean isOpenDoor = false;

boolean setupSystem = false; // indicates if the system is already ran once


FPS_GT511C3 fps(4, 5); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)
Adafruit_LiquidCrystal lcd(0);


void setup()
{
  Serial.begin(9600);
  
  pinMode(downButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  fps.Open(); // serial command to initialize fps
  fps.SetLED(true);

  lcd.begin(16, 2);

  //resetSystem();
  while(!fps.CheckEnrolled(adminFinger)){
    setupEnroll();
  }
  setupSystem = true;
  HomePageLCD();
}

void loop()
{
  currUser = IdentifyFinger();
  

  // enter door
  if (currUser != -1  && currUser != adminFinger && !isOpenDoor){  
     isOpenDoor = true;
     timeA = millis();
  
     digitalWrite(buzzerPin, HIGH);
     digitalWrite(relayPin ,HIGH);
  }
    
  if (isOpenDoor){
    if (millis() - timeA >= delayDoor){
      digitalWrite(buzzerPin, LOW);
      digitalWrite(relayPin, LOW);
      isOpenDoor = false;
    }
  }

  // menu
  if (currUser == adminFinger){
    if(!isMenu){
      currAdminPress = millis();
      isMenu = true;
    }
    else if((millis() - currAdminPress >= delayEnterMenu)){
      lcdMenu();
      HomePageLCD();
      isMenu = false;
    }
  }
}
