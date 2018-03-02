#include <DHT.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#include <LiquidCrystal.h>
#define DHTPIN 8

#define DHTTYPE DHT22
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

int switchdisp = 6;
int display_type = 0;
int snooze = 7;
boolean snooze_state = false;
int alarm = 9;

int alarmhour = 10;
int alarmmin = 13;
int alarmhourvalue = 0;
int alarmminvalue = 0;


void setup()  {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(alarm, OUTPUT);
  pinMode(switchdisp, INPUT);
  pinMode(snooze, INPUT);
  pinMode(alarmhour, INPUT);
  pinMode(alarmmin, INPUT);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
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

void readbutton()
{
   if (digitalRead(switchdisp))
   {
      if (display_type == 2)
      {
        display_type = 0;
        delay(500);
      }
      else 
      {
        display_type = display_type + 1;
        delay(500);
      }
   }
}

void printlcdDigits(int digits)
{
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
  lcd.print(":");
  printlcdDigits(minute());
  lcd.print(":");
  printlcdDigits(second());
  lcd.setCursor(0, 1);
  lcd.print(day());
  lcd.print(" ");
  lcd.print(month());
  lcd.print(" ");
  lcd.print(year());
  
}

void temphumid()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(f, 0);
    lcd.print("F  ");
    lcd.print(t, 0);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humid:");
    lcd.print(h);
    lcd.print("%");
}

void setAlarm()
{
  
  if (digitalRead(alarmhour))
  {
    if (alarmhourvalue == 23)
    {
      alarmhourvalue = 0;
    }
    else
    {
      alarmhourvalue = alarmhourvalue + 1;
    }
    delay(100);
  }

  if (digitalRead(alarmmin))
  {
    if (alarmminvalue == 59)
    {
      alarmminvalue = 0;
    }
    else
    {
      alarmminvalue = alarmminvalue + 1;
    }
    delay(100);
  }
}

void alarmdisplay()
{
  setAlarm();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarm");
  lcd.setCursor(0, 1);
  
  printlcdDigits(alarmhourvalue);
  lcd.print(":");
  printlcdDigits(alarmminvalue);
  /*if (alarmhourvalue < 10)
  {
    lcd.print("0");
    lcd.print(alarmhourvalue);
  }
  if (alarmhourvalue >= 10)
  {
    lcd.print(alarmhourvalue);
  }
  lcd.print(":");
  if (alarmminvalue < 10)
  {
    lcd.print("0");
    lcd.print(alarmminvalue);
  }
  if (alarmminvalue >= 10)
  {
    lcd.print(alarmminvalue);
  }*/
}



// Serial monitor print time and date
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
}



void readsnooze() 
{
  //snooze_state = false;
  if (digitalRead(snooze))
  {
    snooze_state = true;
  }
}

void alarmsystem()
{
  readsnooze();
  if (hour() == alarmhourvalue && minute() == alarmminvalue && snooze_state == false)
  {
      //snooze_state = false;
      tone(alarm, 1000);
      //delay(100);
      //noTone(alarm);
      //delay(100);
      readsnooze();
  }
  if (snooze_state == true)
  {
    noTone(alarm);
  }
}

void loop()
{
  if (timeStatus() == timeSet) {
    alarmsystem();
    readbutton();
    
    if (display_type == 0)
    {
        lcdclock();
    }
    if (display_type == 1)
    {
      temphumid();
    }
    if (display_type == 2)
    {
      alarmdisplay();
    }
  } 
  
  else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(100);

  
}
