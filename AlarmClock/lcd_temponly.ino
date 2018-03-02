#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 8
#define DHTTYPE DHT22

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
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
void loop() {
  temphumid();
}
