/*
 * OpenBtNFC first beta sketch (https://github.com/AndreaBruno/OpenBtNFC)
 *
 * When a RFID card is detected, the UUID is send to the Bluetooth serial.
 * based on:
 *
 * MFRC522 - Library by miguelbalboa (https://github.com/miguelbalboa/rfid)
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 */

#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

SoftwareSerial btSerial(2, 3); // RX, TX
String UUID="";

void setup() {
  Serial.begin(9600);	// Initialize serial communications with the PC
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();	// Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //Serial.print("Card UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UUID+=mfrc522.uid.uidByte[i];
  } 

  Serial.println(UUID);
  btSerial.println(UUID); //send UUID to the bluetooth module
  UUID=""; //clear the UUID

  delay(3000); //wait 3 second to avoid double sending.
}




