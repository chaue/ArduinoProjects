void setup() {
  lcd.begin(16, 2);
  while (!Serial); // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
  {
     Serial.println("Unable to sync with the RTC");
  }
  else
  {
     Serial.println("RTC has set the system time");   
  }
}

void printlcdDigits(int digits)
{
  lcd.print(":");
  if(digits < 10)
  {
    lcd.print("0");
    lcd.print(digits);
  }
  else 
  {
    lcd.print(digits);
  }
}

void lcdclock()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(hour());
  printlcdDigits(minute());
  printlcdDigits(second());
  lcd.setCursor(0, 1);
  lcd.print(day());
  lcd.print(" ");
  lcd.print(month());
  lcd.print(" ");
  lcd.print(year());
}
void loop() {
  lcdclock();
}
