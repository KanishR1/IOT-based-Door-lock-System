#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiClient.h>


const String PROJECT_ID = "iot-test-3d185-default-rtdb.firebaseio.com";
const String fingerprint = "5:54:AC:F9:6D:9B:E0:9C:10:B4:09:B1:E2:7C:12:AF:B4:C8:6C:EA";
const String AUTH  = "xptWOSxRbtS6ssIkOy9VpYFDIFq5PLElblKf4dCt";

LiquidCrystal_I2C lcd = LiquidCrystal_I2C (0x27, 16, 2);
WiFiManager wm;




void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  bool res;
  res = wm.autoConnect("ESP8266", "esp8266");
  if (!res) {
    lcd.setCursor(0, 0);
    lcd.print("Failed to connect");
    delay(2500);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("connected...yeey :)");
    delay(2500);
  }
  Firebase.begin(PROJECT_ID,AUTH);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print("! LCD_I2C Test !");
  delay(3000);

}

void loop() {
  lcd.clear();
  Firebase.setString("Test Data/setString", "Test Data");
  if(Firebase.failed())
  {
    Serial.println("Failed");
  }
}
