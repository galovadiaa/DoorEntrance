void enterDoor(){
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
