void resetSystem(){
  fps.SetLED(false);
  int delayOptionAdminDeletion = 5000;
  unsigned long currTime = millis();
  bool deletionOption = false;

  while(!digitalRead(upButtonPin) && !digitalRead(downButtonPin)){
    if(millis() - currTime >= (delayOptionAdminDeletion)){
      lcdPrint("WARNING!!! ADMIN DELETEION");
      deletionOption = true;
      break;
    }
  }
  delay(2000);

  fps.SetLED(true);
  if (deletionOption == true){
    if(toDelete()){ fps.DeleteID(adminFinger); lcdPrint("ADMIN HAS BEEN DELETED!"); }
    else lcdPrint("NOT DELETED!");
    delay(2000);
  }
  
  return;
}
