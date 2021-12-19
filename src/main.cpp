
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "settings.h"

#define NR_OF_READERS 1

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS]; // Create MFRC522 instance.

// convert Binary data to huaman readable HEX format
String mkString(byte *buffer, byte bufferSize)
{
  String UID = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    if (buffer[i] == 0)
    {
      UID = UID + "00";
    }
    else
    {
      UID = UID + String(buffer[i], HEX);
    }
  }
  return UID;
}

// standard Arduino setup
void setup()
{

  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial)
    ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin(); // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
  {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

// main loop
void loop()
{
  String TagID;

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
  {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial())    // check if new tag detected
    {
      TagID = mkString(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.print("RFID TAG read: ");
      Serial.println(TagID);

      for (int i = 0; i < sizeof TubeID / sizeof TubeID[0]; i++)  // loop through IDs and cehck if match found
      {
        digitalWrite(OutPinNr[i], true); // reset all Output
        if (String(TubeID[i]) == TagID)
        {
          Serial.print("Tube #");
          Serial.print(i + 1);
          Serial.print(" detected, Switch Arduino PIN: ");
          Serial.println(OutPinNr[i]);
          digitalWrite(OutPinNr[i], false); // set output to low (Itrain feedback are low active)
        }
      }
      mfrc522[reader].PICC_HaltA(); // Halt PICC
      mfrc522[reader].PCD_StopCrypto1();   // Stop encryption on PCD
    } 
  }   
}
