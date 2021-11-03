/*
  Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  This example code is in the public domain.

  Changes made by jens@poetic.systems :

  - moved send and receive in to separate functions for better network testing
  - added comments to improve readability
*/

#include <MKRWAN.h>

LoRaModem modem;

#include "arduino_secrets.h"
// Please create an arduino_secrets.h file and
// add your secret network credetials this way:
// #define SECRET_APP_EUI "xxxxxxxxxxxxx"
// #define SECRET_APP_KEY "yyyyyyyyyyyyyyyyyyyyyyy"

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Change this to your regional band (eg. US915, AS923, ...)
  // My location at the time of training: EU868
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Module version is: ");
  Serial.println(modem.version());
  Serial.print("Device EUI is: ");
  Serial.println(modem.deviceEUI());

  // We are ready to connect to the network
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }

  Serial.println("Connected successfully");

  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {

  sendMessage();

  delay(1000);

  receiveMessage();

}

void sendMessage() {
  Serial.println();
  Serial.println("Enter a message to send to network");
  Serial.println("(make sure that end-of-line 'NL' is enabled)");

  while (!Serial.available());
  String msg = Serial.readStringUntil('\n');

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
  int err;
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
}

void receiveMessage() {
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
    return;
  }
  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
}
