#include <SoftwareSerial.h>

String incomingCommand;
SoftwareSerial lcd(15, A5); // RX, TX
char charBuf[50];

void setup() {
  Serial.println("Pawn-LCD started");

  Serial.begin(38400);
  while (!Serial) { ; }
  
  lcd.begin(9600);
  delay(100);
  tft_command(3,2);
  lcd.println("LCD started");  
}


void loop() 
{
    if(Serial.available() > 0)
    {
      incomingCommand = Serial.readStringUntil('\n');
      Serial.println("Stringa: ");
      Serial.println(incomingCommand);     
      delay(100);      
      Serial.println(incomingCommand.equals("prova"));
      incomingCommand += ".bmp";
      incomingCommand.toCharArray(charBuf, 50); 
      tft_command(0); 
      tft_command(13,0,0,charBuf);
    }       
    delay(1000);
}


// ------------------------------------------------------
// Overloaded tft_command functions (to make life easier)
// ------------------------------------------------------
void tft_command(unsigned char cmd)
{
  lcd.write(0x1B);
  lcd.write(cmd); 
  lcd.write(0xFF); 
}
void tft_command(unsigned char cmd, unsigned char param1)
{
  lcd.write(0x1B);
  lcd.write(cmd); 
  lcd.write(param1);
  lcd.write(0xFF); 
}
void tft_command(unsigned char cmd, unsigned char param1, unsigned char param2, unsigned char param3)
{
  lcd.write(0x1B);
  lcd.write(cmd); 
  lcd.write(param1);
  lcd.write(param2);
  lcd.write(param3); 
  lcd.write(0xFF); 
}
void tft_command(unsigned char cmd, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4)
{
  lcd.write(0x1B);
  lcd.write(cmd); 
  lcd.write(param1);
  lcd.write(param2);
  lcd.write(param3);
  lcd.write(param4);
  lcd.write(0xFF); 
}
void tft_command(unsigned char cmd, unsigned char param1, unsigned char param2, const char str[])
{
  lcd.write(0x1B);
  lcd.write(cmd); 
  lcd.write(param1);
  lcd.write(param2);
  lcd.write(str); 
  lcd.write(0xFF); 
}
