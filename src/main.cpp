#include <Arduino.h>
#include <AHT10.h>
#include <Wire.h>


#pragma GCC optimize ("O3")   //code optimisation controls - "O2" & "O3" code performance, "Os" code size

#include <LiquidCrystal_I2C.h>

#define COLUMS           20   //LCD columns
#define ROWS             4    //LCD rows
#define LCD_SPACE_SYMBOL 0x20 //space symbol from LCD ROM, see p.9 of GDM2004D datasheet

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

uint8_t readStatus = 0;

AHT10 myAHT10(AHT10_ADDRESS_0X38);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  
  while (myAHT10.begin() != true)
  {
    Serial.println(F("AHT10 not connected or fail to load calibration coefficient")); //(F()) save string to flash & keeps dynamic memory free
    delay(5000);
  }
  Serial.println(F("AHT10 OK"));

//Wire.setClock(400000); //experimental I2C speed! 400KHz, default 100KHz


  while (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) //colums, rows, characters size
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);   
  }

  lcd.print(F("PCF8574 is OK..."));    //(F()) saves string to flash & keeps dynamic memory free
  delay(2000);

  lcd.clear();

  // prints static text 

  
}


void loop()
{
 
  lcd.setCursor(0, 0);
  lcd.println(F("PRACTICA 5"));
  lcd.setCursor(0, 1);
  lcd.print(F("Ona   Dídac"));
  lcd.setCursor(0, 2);
  lcd.print(F("Temperatura:")); lcd.print(myAHT10.readTemperature(AHT10_FORCE_READ_DATA)); 
  lcd.setCursor(0, 3);
  lcd.print(F("Humitat:")); lcd.print(myAHT10.readHumidity(AHT10_USE_READ_DATA)); 
  
  readStatus = myAHT10.readRawData(); //read 6 bytes from AHT10 over I2C

  delay(10000); //recomended polling frequency 8sec..30sec


  // print dynamic text
  

  delay(1000);

}







