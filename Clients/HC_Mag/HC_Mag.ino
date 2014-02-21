
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define OFF      0
#define ON       1
#define LED_PIN     15
String currentpayload = "";
String payloadAsString = "";

void setup() {
  vibrator_setup();
  nfc.begin();
  
  Serial1.begin(38400);
  while (!Serial1) { ; }
  Serial1.println("Magnifier Started");
  delay(100);
  
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
  delay(100);
  digitalWrite(LED_PIN,HIGH);
  delay(100);
  digitalWrite(LED_PIN,LOW);
  delay(100);  
}

void loop() {
  
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    if (tag.hasNdefMessage())
    {
      NdefMessage message = tag.getNdefMessage();
      NdefRecord record = message.getRecord(0);
      int payloadLength = record.getPayloadLength();
      payloadAsString = "";

      
      byte payload[payloadLength];
      record.getPayload(payload);
      
      for (int c = 3; c < payloadLength; c++) {
        payloadAsString += (char)payload[c];
      }
      if (payloadAsString != currentpayload)
      {
        Serial1.println(payloadAsString);

        set_vibrator(ON);
        digitalWrite(LED_PIN,HIGH);
        delay(1000);
        set_vibrator(OFF);
        digitalWrite(LED_PIN,LOW);
      }
    }
  }  
  currentpayload = payloadAsString;
  delay(500);
}

void vibrator_setup() {
  DDRF |= 0x01;	
  DDRB |= 0x04;
  // once and for all
  PORTB |= 0x04;
}

void set_vibrator(int state) {
  if (state == OFF) {
    PORTF &= ~(0x01);
    //PORTB |= 0x04;
  }
  else {
    PORTF |= 0x01;
    //PORTB |= 0x04;
  }
}




