#include <DHT.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#include <LiquidCrystal.h>
#define DHTPIN 8

#define DHTTYPE DHT22
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

int button = 6;
boolean booldisplaytime = true;


void setup()  {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(button, INPUT);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
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

void readbutton()
{
   if (digitalRead(button))
   {
      booldisplaytime = !booldisplaytime;
      delay(500);
   }
}

void loop()
{
  if (timeStatus() == timeSet) {
    
    //digitalClockDisplay();
    //lcdclock();
    readbutton();
    if (booldisplaytime == true)
    {
        lcdclock();
    }
    if (booldisplaytime == false)
    {
      temphumid();
    }
  } 
  
  else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1307RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(1000);
}
