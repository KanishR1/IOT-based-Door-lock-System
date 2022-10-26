//pasword=123456

#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, A4, A5);

#define passwordLength 7

char inputText[passwordLength];
char password[passwordLength] = "123456";

const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 
int LCDPos = 0;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

bool isDoorOpen = false;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
 
  lcd.print("Enter password  ");
  lcdRestPos();
}

void lcdRestPos() {
  LCDPos = 0;
  lcd.setCursor(LCDPos, 1);
}

void lcdClearLine() {
  lcdRestPos();
 
  lcd.print("                ");
  lcdRestPos();
}

void loop(){
  
  char key = keypad.getKey();
  char keys='*';
  
  if (isDoorOpen && key == '#') { // close door
    // TODO: close door using servo
    lcdRestPos();
   
    lcd.print("Door closed     ");
    lcdRestPos();
    isDoorOpen = false;
  } else if (!isDoorOpen && key == '*') { // clear text
    lcdClearLine();
  } else if (!isDoorOpen && key){
    if (LCDPos == 0) { // clear row
      lcdClearLine();
    }
    Serial.println(keys);
    inputText[LCDPos] = key;
   
    lcd.print(keys);
    lcd.setCursor(++LCDPos, 1);
    if (LCDPos == 6) {
      lcdRestPos();
      if (!strcmp(inputText, password)) {
        
        lcd.print("Open door :)    ");
        // TODO: open door using servo
        isDoorOpen = true;
      } else {
       
        lcd.print("Password wrong  ");
      }
      lcdRestPos();
    }
  }
}