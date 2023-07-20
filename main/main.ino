
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
unsigned long timeDoorOpen;
boolean isOpenDoor = false;

boolean setupSystem = false; // indicates if the system is already ran once


FPS_GT511C3 fps(4, 5); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)
Adafruit_LiquidCrystal lcd(0);


void(* resetFunc) (void) = 0;//declare reset function at address 0
unsigned long delayAutoReset = 72000;
unsigned long currTimeReset = 0;

void setup()
{  
  pinMode(downButtonPin, INPUT); // or INPUT_PULLUP
  pinMode(upButtonPin, INPUT); // or INPUT_PULLUP
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
  //if (millis() - currTimeReset >= delayAutoReset){ resetFunc(); }
  
  currUser = IdentifyFinger();
  if (currUser == -1) return;  

  // enter door
  if (currUser != adminFinger){  
     timeDoorOpen = millis();
     EntrenceLCD(currUser);
     
     digitalWrite(buzzerPin, HIGH);
     digitalWrite(relayPin ,HIGH);
     
     while(!(millis() - timeDoorOpen >= delayDoor)) { lcd.blink(); delay(100); lcd.noBlink(); delay(100); }
     lcd.noBlink();

     HomePageLCD();
     digitalWrite(buzzerPin, LOW);
     digitalWrite(relayPin, LOW);
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

  delay(100);
}
