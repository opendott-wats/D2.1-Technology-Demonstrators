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

NfcTag nfcTag;

int led = LED_BUILTIN;
bool flag = false;
bool preFlag = false;

byte bbuf[EEPROM_I2C_LENGTH];

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  pinMode(led, OUTPUT);

  nfcTag.init();
  nfcTag.readBytes(0, bbuf, EEPROM_I2C_LENGTH);

  Serial.println(nfcTag.getDSFID(), BIN);
  Serial.println(nfcTag.getRFU(), BIN);
  Serial.println(nfcTag.getAFI(), BIN);

  Serial.println(nfcTag.getICNumber(), BIN);
}

void loop()
{
  Serial.println("************************************");
  byte buf[EEPROM_I2C_LENGTH];
  nfcTag.readBytes(0, buf, EEPROM_I2C_LENGTH);
  for(int i=0; i<EEPROM_I2C_LENGTH; i++) {
    if (buf[i] != bbuf[i]) {
      Serial.print(i);
      Serial.print(" -> ");
      Serial.println(buf[i], HEX);
    }
  }
  memcpy(buf, bbuf, EEPROM_I2C_LENGTH);
  Serial.println();
  delay(1000);
  return;

  flag = nfcTag.readByte(EEPROM_I2C_LENGTH - 1) == 0xff ? true : false;
  Serial.println(flag, HEX);
  if (flag != preFlag)
  {
    Serial.println("get remote NFC control signal!");
    if (flag == true)
    {
      Serial.println("led will light up!");
      digitalWrite(led, HIGH);
    }
    else
    {
      Serial.println("led will turn dark!");
      digitalWrite(led, LOW);
    }
    preFlag = flag;
  }
  delay(5 * 1000);
}
