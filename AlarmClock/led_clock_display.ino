#include <DS1307RTC.h>
#include <Wire.h>
#include <RTClib.h>
#include <LedControl.h>

// pin 12 DIN
// pin 11 CLK
// pin 10 LOAD
LedControl lc=LedControl(12, 11, 10, 1);

int tenhour;
int onehour;
int tenminute;
int oneminute;
int tensecond;
int onesecond;
int zero = 0; 

void setup() 
{
    Serial.begin(9600);
    while (!Serial); // wait until Arudino Serial Monitor opens
     setSyncProvider(RTC.get); // the function to get the time from the RTC
     if(timeStatus() != timeSet)
     {
        Serial.println("Unable to sync with RTC");    
     }
     else 
     {
        Serial.println("RTC has set the system time");
     }

      lc.shutdown(0, false);  // wakeup call
      lc.setIntensity(0,8);   // set brightness to medium
      lc.clearDisplay(0);     // clear display
}

void printhourdigits(int hours)
{
    if (hours > 9)
    {
        tenhour = hours / 10;
        onehour = hours % 10;
        lc.setDigit(0, 7, tenhour, false);
        lc.setDigit(0, 6, onehour, false);
        //lc.setDigit(0, 6, '.', false);
        //Serial.print(tenhour);
        //Serial.print(onehour);
    }
    else
    {
      lc.setDigit(0, 7, zero, false);
      lc.setDigit(0, 6, hours, false);
      //lc.setDigit(0, 6, ".", false);
    }
    
}

void printminutedigits(int minutes)
{
    if (minutes > 9 )
    {
        tenminute = minutes / 10;
        oneminute = minutes % 10;
        //lc.setDigit(0, 5, tenminute, false);
        //lc.setDigit(0, 4, oneminute, true);
        lc.setDigit(0, 4, tenminute, false);
        lc.setDigit(0, 3, oneminute, false);
    }
    else
    {
      //lc.setDigit(0, 5, zero, false);
      //lc.setDigit(0, 4, minutes, true);
      lc.setDigit(0, 4, zero, false);
      lc.setDigit(0, 3, minutes, false);
    }
}

void printseconddigits(int seconds)
{
    if (seconds > 9 )
    {
        tensecond = seconds / 10;
        onesecond = seconds % 10;
        //lc.setDigit(0, 3, tensecond, false);
        //lc.setDigit(0, 2, onesecond, true);
        lc.setDigit(0, 1, tensecond, false);
        lc.setDigit(0, 0, onesecond, false);
    }
    else
    {
      //lc.setDigit(0, 3, zero, false);
      //lc.setDigit(0, 2, seconds, true);
      lc.setDigit(0, 1, zero, false);
      lc.setDigit(0, 0, seconds, false);
    }
}

void printclock()
{
    printhourdigits(hour());
    printminutedigits(minute());
    printseconddigits(second());
}

void digitalClockDisplay(){
  // digital clock display of the time
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

void loop() 
{
     printclock();
     Serial.print(tenhour);
     Serial.print(onehour);
     //digitalClockDisplay();

}
