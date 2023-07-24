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
  
  if (deleteNotify()) { fps.DeleteID(id); lcdPrint("    Deleted!    ");}
  else lcdPrint("   Not Deleted!  ");
}

bool DeleteByID(int id){
  if (id > 200 or id < 0) return false;
  
  if (deleteNotify()) { fps.DeleteID(id); lcdPrint("    Deleted!    "); return true;}
  
  lcdPrint("   Not Deleted!  ");
  return false;
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

  return toDelete();
}

bool toDelete(){
  bool isDelete = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Delete ID?   ");
  lcd.setCursor(0, 1);
  lcd.print("   Yes  / > No  ");
  while(!fps.IsPressFinger()) {
    lcd.setCursor(0, 1);
    if(!digitalRead(upButtonPin)) { lcd.print(" > Yes  /   No  "); isDelete = true; }
    if(!digitalRead(downButtonPin)) { lcd.print("   Yes  / > No  "); isDelete = false; }
    }
  return isDelete;
}
