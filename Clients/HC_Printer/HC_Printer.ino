/*************************************************************************
  This is an Arduino library for the Adafruit Thermal Printer.
  Pick one up at --> http://www.adafruit.com/products/597
  These printers use TTL serial to communicate, 2 pins are required.

  Adafruit invests time and resources providing this open source code.
  Please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution.
 *************************************************************************/

#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
//#include "adalogo.h"
//#include "adaqrcode.h"
#include <avr/pgmspace.h>

int printer_RX_Pin = 3;  // This is the green wire
int printer_TX_Pin = 2;  // This is the yellow wire
String incomingCommand;
int separatorPosition;
String clueText;
String service;

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

void setup(){
  Serial.begin(9600);
  Serial.println("Printer started on Serial");
  printer.begin();

 
}

void loop() {
     if(Serial.available() > 0)
    {
      incomingCommand = Serial.readStringUntil('\n');
//      Serial.println("Stringa: ");
//      Serial.println(incomingCommand);     
      delay(100);      
//      Serial.println(incomingCommand.equals("prova"));
//      Serial1.print("Incoming command: ");
//      Serial1.println(incomingCommand);
      separatorPosition = incomingCommand.indexOf(':');
      service = incomingCommand.substring(0,separatorPosition);
//      Serial1.print("Service: ");
//      Serial1.println(service);
      clueText = incomingCommand.substring(separatorPosition+1,incomingCommand.length());
//      Serial1.print("imgName: ");
//     Serial1.println(imgName);
      if(service == "text")
       { 
          printer.justify('C');
          printer.setSize('L');     // Set type size, accepts 'S', 'M', 'L'
          printer.print(clueText);
          printer.feed(8);
     }
    }       
    delay(1000);
}
