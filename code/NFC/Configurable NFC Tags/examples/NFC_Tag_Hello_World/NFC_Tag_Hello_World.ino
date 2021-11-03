/* power on/off your led with NFC_TAG
 * created by lawliet zou (lawliet.zou@gmail.com)
 * Data: 2014/03/25   version: 1.0
 *
 * Usage: 
 * please follow the steps as following
 * 1. Install the APK file which is under NfcTag_M24LR6E/Resources 
 * in your Android Mobile.
 * 2. Connect your NFC TAG and led to your Arduino board
 * 3. Open the application and move your NFC TAG close to your mobile
 * 4. Enter the "BASIC FORMAT" menu, and click "READ" button
 * 5. Block should be writen as 0x7FF(we use the last byte in EEPROM)
 * 6. write last value as 0xFF, the led will turn bright and write 0x00
 * to turn off the led. Have fun!
 */
 
#include "NfcTag.h"
#include <Wire.h>


// This should elicit "Hello World!" for NFC Readers as text card

byte payload[] = { 0x3C, 0x4E, 0x64, 0x65, 0x66, 0x4D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x3E, 0x64, 0x31, 0x30,
0x31, 0x31, 0x64, 0x35, 0x34, 0x38, 0x32, 0x36, 0x35, 0x36, 0x65, 0x66, 0x66, 0x66, 0x65, 0x34,
0x38, 0x30, 0x30, 0x36, 0x35, 0x30, 0x30, 0x36, 0x63, 0x30, 0x30, 0x36, 0x63, 0x30, 0x30, 0x36,
0x66, 0x30, 0x30, 0x32, 0x30, 0x30, 0x30, 0x35, 0x37, 0x30, 0x30, 0x36, 0x66, 0x30, 0x30, 0x37,
0x32, 0x30, 0x30, 0x36, 0x63, 0x30, 0x30, 0x36, 0x34, 0x30, 0x30, 0x32, 0x31, 0x30, 0x30, 0x3C,
0x2F, 0x4E, 0x64, 0x65, 0x66, 0x4D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x3E };

uint8_t payload_length = 31;

unsigned int payload_addr = EEPROM_I2C_LENGTH - payload_length - 1;


NfcTag nfcTag;
int led = 5;
bool flag = false;
bool preFlag = false;
void setup(){
  Serial.begin(9600);
  while(!Serial);

  Serial.println("----------------------------------");

  pinMode(led,OUTPUT);
  nfcTag.init();

  nfcTag.clearMemory();
  delay(5);

  // Do some 1 bytre testing
//  nfcTag.writeByte(EEPROM_I2C_LENGTH - 1, 0xff);
//  delay(20);
//  Serial.println(nfcTag.readByte(EEPROM_I2C_LENGTH - 1), HEX);
//  nfcTag.writeByte(EEPROM_I2C_LENGTH - 1, 0x0f);
//  delay(20);
//  Serial.println(nfcTag.readByte(EEPROM_I2C_LENGTH - 1), HEX);
//  delay(20);
  
  nfcTag.writeBytes(payload_addr, payload, payload_length);
  delay(20);


  char response[EEPROM_I2C_LENGTH];
  nfcTag.readBytes(0, (byte*)response, EEPROM_I2C_LENGTH);

  for (uint16_t i=0; i < EEPROM_I2C_LENGTH; i++) {
    Serial.print(i);
    Serial.print(": 0x");
    Serial.print(response[i], HEX);
    Serial.print("-> '");
    Serial.print(response[i]);
    Serial.println("'");
  }
}

void loop(){
}
