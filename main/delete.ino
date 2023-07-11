void Delete(){
  lcd.clear();

  lcd.print("DELETION:");
  lcd.setCursor(0, 1);

  lcd.setCursor(0, 1);
  lcd.print("ID: #");

  int id=0;

  fps.SetLED(false);
  delay(3000);
  fps.SetLED(true);
    while(!fps.IsPressFinger()){

      if(id < 200)
        if(!digitalRead(upButtonPin)){ id++; }
      

      if (id > 0){
        if(!digitalRead(downButtonPin)){ id--; }
        }

      if(!digitalRead(upButtonPin) && !digitalRead(downButtonPin)){ return; }

    toggleSelector(1, 6, String(id));
    delay(100);

  }
}

bool deleteNotify(){
  int cnt = 0;
  bool deleteFlag = false;
  lcd.clear();
  lcd.print(" Warning!  ");
  lcd.setCursor(0, 1);
  lcd.print("ID ");
  lcd.print("Has Data ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Delete ID?   ");
  delay(200);

  while (fps.IsPressFinger()) {
    if (cnt <= 5) {
      lcd.setCursor (0, 1);
      lcd.print("   Yes  / > No  ");
      deleteFlag = false;
      delay(100);
      cnt++;
    }
    else if (cnt > 5 && cnt < 11) {
      lcd.setCursor (0, 1);
      lcd.print(" > Yes  /   No  ");
      deleteFlag = true;
      delay(100);
      cnt++;
    }
    else cnt = 0;
  }
  if (deleteFlag == false) {
    lcd.clear();
    lcdPrint("   Not Deleted!  ");
    return false;
  }
  else if (deleteFlag == true) {
    lcd.clear();
    lcdPrint("    Deleted!    ");
    return true;

  }
}
