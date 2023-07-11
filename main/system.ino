void resetSystem(){
  int elapsedTime = 10000;
  unsigned long currTime = millis();

  while(!upButtonPin && !downButtonPin){
    if(millis() - currTime >= (elapsedTime - 8000)){
      lcdPrint("WARNING!!! ADMIN DELETEION");
    }
    if(millis() - currTime >= (elapsedTime - 5000)){
      fps.DeleteID(adminFinger);
      lcdPrint("ADMIN HAS BEEN DELETED!");
    }
    if(millis() - currTime >= elapsedTime - 2000){
      lcdPrint("WARNING!!! USERS DELETION");
    }
    if(millis() - currTime >= elapsedTime){
      fps.DeleteAll();
      lcdPrint("USERS HAS BEEN DELETED");
      delay(2000);
      lcd.clear();
      return;
    }
  }
  return;
}
