#include <EEPROM.h>

unsigned char value;
void setup() {

  Serial.begin(115200);
  EEPROM.begin(512);
}

void loop() {
  
  for(int i=0;i<8;i++)
  {
  value = EEPROM.read(i);
  Serial.print(char(value));
  }
  Serial.println();

  delay(500);
}
