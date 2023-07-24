void setupEnroll(){
  lcdPrint("ADMIN: First time registration");
  delay(3000);

  Enroll();
}

int searchFreeID(){
  int id = 0;
  bool usedid = true;
  while (usedid == true)

  {
    usedid = fps.CheckEnrolled(id);
    if (usedid==true) id++;
  }

  return id;
}


bool Enroll()
{
  lcd.clear();
  
  int enrollid = searchFreeID();

  lcd.clear();
  lcd.print("CONFIRMATION ID: ");
  lcd.setCursor(0, 1);

  int currentEmpty = enrollid;
  lcd.setCursor(0, 7);
  lcd.print("      #");
  
  delay(1000);
  while(!fps.IsPressFinger()){
      if(enrollid < currentEmpty && enrollid <= 200){
        if(!digitalRead(upButtonPin)){ enrollid++; }
      }

      if(enrollid > 0){
        if(!digitalRead(downButtonPin)){ enrollid--; }
      }

      if(!digitalRead(upButtonPin) && !digitalRead(downButtonPin)){ return true; }
      
    toggleSelector(1, 8, String(enrollid));
  }

  if(fps.CheckEnrolled(enrollid)){
    if(!DeleteByID(enrollid)) return true;
    delay(1000);
  }
  
  lcdPrint("Please remove your finger.");
  fps.SetLED(false);
  delay(2000);
  fps.SetLED(true);

  while(fps.IsPressFinger()){ delay(100); } // make a timeout here:)
  delay(1000);

  lcd.clear();
  lcdPrint("To continue press your finger...");
  while(!fps.IsPressFinger()){ delay(100); }

  fps.EnrollStart(enrollid);
  
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  if (bret != false)
  {
    lcdPrint("Remove finger");
    fps.Enroll1(); 
    while(fps.IsPressFinger() == true) delay(100);
    
    lcd.clear();
    lcd.print("Press again");
    while(fps.IsPressFinger() == false) delay(100);
    
    lcd.clear();
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      lcd.print("Remove finger");
      fps.Enroll2();
      while(fps.IsPressFinger() == true) delay(100);
      lcd.clear();
      lcd.print("Press again");
      while(fps.IsPressFinger() == false) delay(100);
      lcd.clear();
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        lcd.print("Remove finger");
        iret = fps.Enroll3();
        if (iret == 0)
        {
          lcd.clear();
          lcdPrint("Enrollment finished");
          delay(1000);
        }
        else
        {
          lcd.clear();
          lcd.print(("Failed! %d", iret));
        }
      }
      else lcdPrint("Failed at third finger");
    }
    else lcdPrint("Failed at second finger");
  }
  else lcdPrint("Failed at first finger");

  delay(1000);

  return fps.CheckEnrolled(enrollid);
  
}
