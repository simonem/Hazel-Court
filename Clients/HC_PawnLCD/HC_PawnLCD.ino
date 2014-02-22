#include <SoftwareSerial.h>

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
String currentpayload = "";
String payloadAsString = "";

String incomingCommand;
SoftwareSerial lcd(15, A5); // RX, TX
char charBuf[50];

void setup() {

  Serial1.begin(38400);
  while (!Serial1) { ; }
  Serial1.println("Pawn-LCD started");

  lcd.begin(9600);
  delay(100);
  tft_command(3,2);
  lcd.println("LCD started");  
  
  nfc.begin();

  
}


void loop() 
{
    if(Serial1.available() > 0)
    {
      incomingCommand = Serial1.readStringUntil('\n');
//      Serial.println("Stringa: ");
//      Serial.println(incomingCommand);     
      delay(100);      
//      Serial.println(incomingCommand.equals("prova"));
      incomingCommand += ".bmp";
      incomingCommand.toCharArray(charBuf, 50); 
      tft_command(0); 
      tft_command(13,0,0,charBuf);
    }       
    delay(1000);
    
    if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    if (tag.hasNdefMessage())
    {
      NdefMessage message = tag.getNdefMessage();
      NdefRecord record = message.getRecord(0);
      String payloadAsString = "";
      int payloadLength = record.getPayloadLength();
      byte payload[payloadLength];
      record.getPayload(payload);      
      for (int c = 3; c < payloadLength; c++) {
        payloadAsString += (char)payload[c];
      }
      if (payloadAsString != currentpayload)
      {
      Serial1.println(payloadAsString);
      currentpayload = payloadAsString;
      }
    }
    delay(1000);
  }
    
    
    
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
