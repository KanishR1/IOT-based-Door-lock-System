#include<PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd =LiquidCrystal_I2C (0x27, 16, 2);
WiFiManager wm;

void setup() {
    lcd.init(); 
    lcd.backlight();
    lcd.clear();
    WiFi.mode(WIFI_STA); 
    Serial.begin(115200);
    bool res;
    res = wm.autoConnect("ESP8266","esp8266");
    if(!res) {
        lcd.setCursor(0,0);
        lcd.print("Failed to connect");
        delay(2500);
    } 
    else {    
        lcd.setCursor(0,0);
        lcd.print("connected...yeey :)");
        delay(2500);
    }
    lcd.clear();

}

void loop() {
    // put your main code here, to run repeatedly:   
    lcd.setCursor(3,0);
    lcd.print("Hello World");
    lcd.setCursor(0,1);
    lcd.print("! LCD_I2C Test !");
}
