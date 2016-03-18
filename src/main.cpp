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
#include <Arduino.h>
#include <TimedAction.h>

#define SS_PIN 10
#define OTHER_SS_PIN 8
#define RST_PIN 9  //-- yellow

#define LED1 5
#define LED2 6



bool flip;
String output = "";

void setup(){
  Serial.begin(9600);
  flip = true;
}

void loop(){
  //int ss = flip ? SS_PIN : OTHER_SS_PIN;
  //flip = ! flip;
  int ss = SS_PIN;
  bool rfid1_is_present = false;

  RFID rfid1(ss, RST_PIN);
  SPI.begin(ss, 13, 11);
  rfid1.init();

  if(rfid1.isCard() && rfid1.readCardSerial()) {
    rfid1_is_present = true;
    output += String(rfid1.serNum[0], DEC);
    output += "_";
    output += String(rfid1.serNum[1], DEC);
    output += "_";
    output += String(rfid1.serNum[2], DEC);
    output += "_";
    output += String(rfid1.serNum[3], DEC);
    output += "_";
    output += String(rfid1.serNum[4], DEC);
    digitalWrite(LED1, HIGH);
  }
  else {
    output = "";
    digitalWrite(LED1, LOW);
  }
  rfid1.halt();

  ss = OTHER_SS_PIN;
  RFID rfid2(ss, RST_PIN);
  SPI.begin(ss, 13, 11);
  rfid2.init();

  if(rfid2.isCard() && rfid2.readCardSerial()) {
    if (rfid1_is_present) {
      output += ":";
    }
    output += String(rfid2.serNum[0], DEC);
    output += "_";
    output += String(rfid2.serNum[1], DEC);
    output += "_";
    output += String(rfid2.serNum[2], DEC);
    output += "_";
    output += String(rfid2.serNum[3], DEC);
    output += "_";
    output += String(rfid2.serNum[4], DEC);

    digitalWrite(LED2, HIGH);
  }
  else {
    digitalWrite(LED2, LOW);
    output = "";
  }
  rfid2.halt();

}

void send() {
  if (output.length() > 0) {
    Serial.println(output);
  }
}

TimedAction timedAction = TimedAction(2000, send);
