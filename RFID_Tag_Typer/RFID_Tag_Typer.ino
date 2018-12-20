//RFID Tag typer
//Types out tag id in hex over USB keyboard

#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define RST_PIN 9         
#define SS_PIN 10        

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	SPI.begin();              //start SPI
	mfrc522.PCD_Init();       //start RC522 module
  Keyboard.begin();         //start USB keyboard
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);     //LED off
}

void loop() {
	if (!mfrc522.PICC_IsNewCardPresent()){return;}
  if (!mfrc522.PICC_ReadCardSerial()){return;}
  digitalWrite(13,HIGH);     //LED on
  for(byte i = 0; i < mfrc522.uid.size; i++){
    Keyboard.print(mfrc522.uid.uidByte[i] < 0x10 ? "0x0" : "0x");
    Keyboard.print(mfrc522.uid.uidByte[i], HEX);
    Keyboard.print(",");
  }
  Keyboard.print("\n");
  mfrc522.PICC_HaltA();
  digitalWrite(13,LOW);     //LED off
}
