void lcdPrint(String sent){
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(sent.substring(0, 16));
  lcd.setCursor(0, 1);
  lcd.print(sent.substring(16));

}

void HomePageLCD(){
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("M.A.O.R");
  lcd.setCursor(4, 1);
  lcd.print("Department");
}

void EntrenceLCD(int id){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Welcome ID: " + String(id));
}
