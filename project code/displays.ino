
void display_slot()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("S_1:"));
  lcd.setCursor(4, 0);
  lcd.print(s_1);
  lcd.setCursor(10, 0);
  lcd.print(F("S_2:"));
  lcd.setCursor(14, 0);
  lcd.print(s_2);
  lcd.setCursor(0, 1);
  lcd.print(F("H_C:"));
  lcd.setCursor(4, 1);
  lcd.print(s_3);
  lcd.setCursor(10, 1);
  lcd.print(F("T_R:"));
  lcd.setCursor(14, 1);
  lcd.print(s_4);  
}

void main_page()
{
   lcd.clear();
   lcd.setCursor(0, 0);  
   lcd.print(F("Android Application "));
   lcd.setCursor(0, 1);
   lcd.print(F("  Based Smart IOT   "));
   lcd.setCursor(0, 2);
   lcd.print(F("Parking System using"));
   lcd.setCursor(0, 3);
   lcd.print(F("        RFID        "));
   delay(1000);
}

void display_slot_full()
{
   lcd.clear();
   lcd.setCursor(0, 0);  
   lcd.print(F("Sorry!!!"));
   lcd.setCursor(0, 1);
   lcd.print(F("Parking is Full..."));
   delay(500);
}

void entry_display()
{
   lcd.clear();
   lcd.setCursor(0, 0);  
   lcd.print(F("Welcome to Smart IOT"));
   lcd.setCursor(0, 1);
   lcd.print(F("Parking System"));
   delay(500);
}

void balance_low_disp()
{
   lcd.clear();
   lcd.setCursor(0, 0);  
   lcd.print(F("Inefficient Balance!"));
   lcd.setCursor(0, 1);
   lcd.print(F("Please Recharge.."));
   delay(500);
}
