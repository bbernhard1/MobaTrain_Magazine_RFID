
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
  pinMode(PulsePin, OUTPUT);
  pinMode(ResetPin, OUTPUT);
  digitalWrite(PulsePin, LOW);
  digitalWrite(ResetPin, LOW);
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
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) // check if new tag detected
    {
      TagID = mkString(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.print("RFID TAG read: ");
      Serial.print(TagID);

      for (int TubeNr = 0; TubeNr < sizeof TubeID / sizeof TubeID[0]; TubeNr++) // loop through IDs and check if match found
      {
        //  digitalWrite(OutPinNr[i], true); // reset all Output
        if (String(TubeID[TubeNr]) == TagID)
        {
          Serial.print("Tube #");
          Serial.print(TubeNr + 1);
          Serial.println(" detected. ");
          //    Serial.println(OutPinNr[i]);

          digitalWrite(ResetPin, LOW); // set reset to low to reset counter in iTrain
          delay(PulseLowTime);
          for (int pulse = 0; pulse < TubeNr + 1; pulse++)
          {
            digitalWrite(PulsePin, LOW);
            delay(PulseLowTime);
            digitalWrite(PulsePin, HIGH);
            delay(PulseHighTime);
            //    digitalWrite(PulsePin, LOW);
          }
        

          delay(PulseHighTime);
          digitalWrite(ResetPin, HIGH); // set reset to low to indicate all pulses sent
          digitalWrite(PulsePin, HIGH);

           delay(PulseHighTime);
          digitalWrite(ResetPin, LOW); // set reset to low to indicate all pulses sent
          digitalWrite(PulsePin, LOW);
        }
      }
      mfrc522[reader].PICC_HaltA();      // Halt PICC
      mfrc522[reader].PCD_StopCrypto1(); // Stop encryption on PCD
    }
  }
}
