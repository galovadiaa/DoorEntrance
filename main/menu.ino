const int arrowPlace = 0;

int space = arrowPlace + 2;

bool toggleArrow = false;
bool downArrow = false;

unsigned long menuEnterTime = 0;
unsigned long lastToggleTime = 0;


int selectorPos = 0;
int rowSelector = 0;
const int numOptions = 2;

bool pressedMenu = false;

// strings //
const char REGISTER[] = "Register ID";
const char DELETE[] = "Delete ID";
// strings //


// function to enter functions of admin mode
void lcdMenu(){
  initLCD();
  delay(1500);
  enterMenu();
  selector();
}

// initialize variables
void enterMenu(){
  menu = true;
  menuEnterTime = millis();
}

// reinitialize variables (clear)
void exitMenu(){
  menu = false;
  lcd.clear();
}

void initLCD(){
  lcd.setCursor(space, 0);
  lcd.print(REGISTER);
  lcd.setCursor(space, 1);
  lcd.print(DELETE);
  
}

// exit from current state when no actions are taken
void TimeOut(int after, uint32_t &menuEnterTime){
  if (pressedMenu == true){ menuEnterTime = millis(); }
  int elapsedTime = millis() - menuEnterTime;
  if(elapsedTime >= after){
    exitMenu();
  }
}

void toggleSelector(int row, int column, String symbol){
  int elapsedTime = millis() - lastToggleTime;
  if (elapsedTime >= 500){
    lcd.setCursor(column, row);
    if(!toggleArrow){
      lcd.print(symbol);
    }
    else{
      for(int i = symbol.length(); i > 0; i--)
        lcd.print(" ");
    }

    toggleArrow = !toggleArrow;
    lastToggleTime = millis();
  }
}


void selector(){
  do{
      TimeOut(5000, menuEnterTime);

      toggleSelector(rowSelector, 0, ">");

      if (rowSelector <= 0){ lcd.setCursor(0, 1); lcd.print(" "); }
      else { lcd.setCursor(0, 0); lcd.print(" "); }

      if(digitalRead(upButtonPin) && digitalRead(downButtonPin)){
        pressedMenu = false;
      }

      if(!digitalRead(upButtonPin) && !pressedMenu){
        if(rowSelector > 0) {rowSelector--;}
        pressedMenu = true;

        if (rowSelector > 0) { rowSelector--; }
      }
      if(!digitalRead(downButtonPin) && !pressedMenu){
        if(rowSelector < (ROWS - 1)){ rowSelector++; }

        pressedMenu = true;
        
      }

//      if(countPressed >= 2){
//        // replace functions on screen?
//        selectorPos = 0;
//      }
      if (rowSelector== 0){
          if(fps.IsPressFinger())
          {
            while(!Enroll());
            delay(2000);
            return;
          }
      }
      else if (rowSelector == 1){
          if(fps.IsPressFinger()){
            Delete();
            delay(2000);
            return;
          }
      }
  }while(menu);
}
