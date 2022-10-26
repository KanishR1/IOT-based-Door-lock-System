#include <EEPROM.h>
void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
}

void loop() {
  int i;
  unsigned char Master_Password [] = "ESP8266";
  for(i=0;i<std::size(Master_Password);i++)
    {
      EEPROM.write(i, Master_Password[i]);
      
    }
    
  int len = std::size(Master_Password);
  Serial.println(len);
    if (EEPROM.commit()) {
      Serial.println("EEPROM successfully committed");
    } else {
      Serial.println("ERROR! EEPROM commit failed");
    }

  delay(100);
}
