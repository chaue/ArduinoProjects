#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>

void setup() {
  while (!Serial) ;
  setSyncProvider(RTC.get);
  Serial.begin(9600);
  if(timeStatus() != timeSet)
  {
    Serial.println("Unable to sync with the RTC");
  }
  else 
  {
    Serial.println("RTC has set the system time");
  }
   setclock();
   RTC.set(now());
}

void setclock() // hour, min, second, day, month, year
{
  setTime(16, 49, 0, 23, 10, 2016);
}

void printSerialDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
  {
      Serial.print('0');
      Serial.print(digits);
  }
  else
  {
    Serial.print(digits);
  }
}

void loop() {
  if (timeStatus() == timeSet)
  {
    
      Serial.print(hour());
      printSerialDigits(minute());
      printSerialDigits(second());
      Serial.print(" ");
      Serial.print(day());
      Serial.print(" ");
      Serial.print(month());
      Serial.print(" ");
      Serial.print(year()); 
      Serial.println(); 
  }

}
