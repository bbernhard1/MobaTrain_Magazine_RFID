
/* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 *
 */

#define RST_PIN 9   // Configurable, see typical pin layout above
#define SS_1_PIN 10 // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2
#define SS_2_PIN 8  // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 1


// Define your TAGs and outputs
// TubeID[x]  will trigger OutPinNr[x]
// take care both array are have same size, no consistency check is done !!!
char *TubeID[] = { "400662a94081", "444662a94081",  "42adb7ae43f81", "422662a94081", "465662a94081", "440db7ae43f81"};   // this are the TAGID
// int  OutPinNr[] = { 14, 15, 16, 17, 18, 19};  // this are the arduio output pins  (Arduino Mega)

#define PulsePin 15
#define ResetPin 14

const int PulseLowTime = 100;
const int PulseHighTime = 100;
