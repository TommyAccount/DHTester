#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
 LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
long timer;
int button, hour, m, sec;
int value1, value2, value3;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  EEPROM.get(2, hour);
  EEPROM.get(4, m);
  EEPROM.get(6, sec);
}

void loop() {
  if (millis() - timer > 1000){
    timer = millis();
      sec++;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("H: ");
  lcd.setCursor(2, 0);
  lcd.print(h);
  lcd.setCursor(5, 0); 
  lcd.print ("T: ");
  lcd.setCursor(7, 0); 
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
 // value1 = EEPROM.read(hour);
  lcd.setCursor(6, 1);
  if (hour<10) {
  lcd.print(hour);
  lcd.setCursor(5, 1);
  lcd.print(0);
  }
  else
  {
    lcd.setCursor(5, 1);
    lcd.print(hour);
     if (hour==24) {hour = 00;}
  }
  lcd.setCursor(7, 1);
  lcd.print(":");
//  value2 = EEPROM.read(m);
  if (m<10) {
  lcd.setCursor(9, 1);     
  lcd.print(m);
  lcd.setCursor(8, 1);
  lcd.print(0);
  }
  else
 {
    lcd.setCursor(8, 1);
    lcd.print(m);
     if (m==59) { hour = hour + 1;
     m = 00;}
}
  lcd.setCursor(10, 1);
  lcd.print(":");
 // value3 = EEPROM.read(sec);
  if (sec<10) {
  lcd.setCursor(12, 1);     
  lcd.print(sec);
  lcd.setCursor(11, 1);
  lcd.print(0);
  }
  else
 {
    lcd.setCursor(11, 1);
    lcd.print(sec);
     if (sec==59) { m = m + 1;
     sec = 00;}
}
 EEPROM.put(2, hour);
 EEPROM.put(4, m);
 EEPROM.put(6, sec);
  }
}
