#include<PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiManager.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFiClient.h>


#define ORG "nbl97v"
#define DEVICE_TYPE "Door_lock"
#define DEVICE_ID "Door_Lock"
#define TOKEN "Kanish@2002"

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char publishTopic[] = "iot-2/evt/Distance/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

 
LiquidCrystal_I2C lcd =LiquidCrystal_I2C (0x27, 16, 2);
WiFiManager wm;
WiFiClient wificlient;
PubSubClient client(server, 1883, NULL ,wificlient);

void PublishData(String test) {
  server_connect();
  String payload;
  payload = "{\"Test Data\":";
  payload += "\""+test+"\"";
  payload += "}";
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sending payload:");
  Serial.println(payload);

  
  if (client.publish(publishTopic, (char*) payload.c_str())) {
    lcd.setCursor(0,1);
    lcd.print("Publish ok");
  } else {
    lcd.setCursor(0,1);
    lcd.print("Publish failed");
  }
  
}
void server_connect() {
    lcd.clear();
    if (!client.connected()) {
      lcd.setCursor(0,0);
      lcd.print("Reconnect ");
      lcd.setCursor(11,0);
      lcd.print(server);
      lcd.setCursor(0,1);
      while (!client.connect(clientId, authMethod, token)) {
        lcd.print(".");
        delay(500);
      }
  }
  lcd.clear();
}

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
    lcd.setCursor(3,0);
    lcd.print("Hello World");
    lcd.setCursor(0,1);
    lcd.print("! LCD_I2C Test !");
    delay(3000);

}

void loop() {
    client.loop();
    lcd.clear();

    lcd.clear();

    PublishData("Test Data");
    delay(1000);
    if (!client.loop()) {
    server_connect();
    }
}
