/*  
 * Read a card using a mfrc522 reader on your SPI interface  
 * Pin layout should be as follows (on Arduino Uno):  
 * MOSI: Pin 11 / ICSP-4 -- white 
 * MISO: Pin 12 / ICSP-1 -- blue
 * SCK: Pin 13 / ISCP-3 -- green 
 * SS: Pin 10  -- orange
 * RST: Pin 5 
 */  
#include <SPI.h>  
#include <RFID.h>  
#define SS_PIN 10  
#define OTHER_SS_PIN 8  
#define RST_PIN 9  //-- yellow


bool flip;

void setup(){  
  Serial.begin(9600);  
  flip = true;
}  

void loop(){  
  //int ss = flip ? SS_PIN : OTHER_SS_PIN;
  //flip = ! flip;
  int ss = SS_PIN;

  RFID rfid1(ss, RST_PIN);  
  SPI.begin(ss, 13, 11);
  rfid1.init();  

  if(rfid1.isCard() && rfid1.readCardSerial()) {  
    Serial.print(rfid1.serNum[0],DEC);  
    Serial.print(" ");  
    Serial.print(rfid1.serNum[1],DEC);  
    Serial.print(" ");  
    Serial.print(rfid1.serNum[2],DEC);  
    Serial.print(" ");  
    Serial.print(rfid1.serNum[3],DEC);  
    Serial.print(" ");  
    Serial.print(rfid1.serNum[4],DEC);  
    Serial.println("");  
  }  
  rfid1.halt();  

  ss = OTHER_SS_PIN;
  RFID rfid2(ss, RST_PIN);  
  SPI.begin(ss, 13, 11);
  rfid2.init();  

  if(rfid2.isCard() && rfid2.readCardSerial()) {  
    Serial.print(rfid2.serNum[0],DEC);  
    Serial.print(" ");  
    Serial.print(rfid2.serNum[1],DEC);  
    Serial.print(" ");  
    Serial.print(rfid2.serNum[2],DEC);  
    Serial.print(" ");  
    Serial.print(rfid2.serNum[3],DEC);  
    Serial.print(" ");  
    Serial.print(rfid2.serNum[4],DEC);  
    Serial.println("");  
  }  
  rfid2.halt();  
}  
