//RFID Password Typer
//If a matching tag is found, the keyboard types
//CTRL-ALT-DEL, then types the password and presses enter
//Which should log you on to a Windows computer
//Or Lock the computer if you're already logged in

#include <SPI.h>
#include <MFRC522.h>
#include "Keyboard.h"

#define RST_PIN 9         
#define SS_PIN 10        

byte tag[10]={0x64,0xAE,0xDD,0xFC,};
char pswd[]="********\n";      //password, end with just \n
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
  for(byte i = 0; i < mfrc522.uid.size; i++){
    if(mfrc522.uid.uidByte[i]!=tag[i]){return;}
  }
  mfrc522.PICC_HaltA();         //stop tag so we don't get repeats
  digitalWrite(13,HIGH);        //LED on so we know we've got tag match
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  delay(300);
  Keyboard.print(pswd);
  delay(100);
  digitalWrite(13,LOW);         //LED off
}

