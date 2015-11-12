#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int pinTemp = A0;      // pin of temperature sensor

float temperature;
float temperatureF;
int B=3975;                  // B value of the thermistor
float resistance;
char outstr[6]; 

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print(String("Temperature:"));  
    
}

void loop()
{
    int val = analogRead(pinTemp);                               // get analog value
    resistance=(float)(1023-val)*10000/val;                      // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc temperature
    temperatureF = (temperature * 9) / 5 + 32;
    Serial.println(temperatureF);
    
    dtostrf(temperatureF, 3, 2, outstr);
    if (temperatureF < 70) {
      lcd.setRGB(0, 0, 255);
    }
    else {
        lcd.setRGB(255, 0, 0);    
    }
    lcd.setCursor(0,1);
    lcd.print(String(temperatureF) + String(" "));
    delay(3000);
}
