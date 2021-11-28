/**
 * BLE basics for haptic memories buzzy thing
 * 
 * Basic BLE connection handling.
 * Extend later to drive a DRV2605 with a linear resonant actuator
 *
 * Copyright (C) 2021  jens alexander ewald <jens@poetic.systems>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ------
 *
 * This project has received funding from the European Union’s Horizon 2020
 * research and innovation programme under the Marie Skłodowska-Curie grant
 * agreement No. 813508.
 */

#include <ArduinoBLE.h>

// Create a service for buzzing
BLEService buzzService("D716B856-8B7A-4719-B3B8-CC301E144841");

BLEByteCharacteristic buzzTrigger("D716B857-8B7A-4719-B3B8-CC301E144841", BLEWrite);

void setup() {
  Serial.begin(9600);
  while(!Serial); // wait for Serial

  pinMode(LED_BUILTIN, OUTPUT); // Use the built in LED as simulated buzzer

  // Configure the BLE device
  BLE.setLocalName("The Buzzy Thing");
  BLE.setDeviceName("The Buzzy Thing");

  // Handling of connection and disconnection is done in callbacks
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);


  // Configure the Buzz Service
  buzzService.addCharacteristic(buzzTrigger);
  
  // Configure the Buzz Trigger Characteristic
  buzzTrigger.setEventHandler(BLEWritten, buzzTriggered);
  buzzTrigger.setValue(0);

  // Add the service to the device
  BLE.addService(buzzService);
  BLE.setAdvertisedService(buzzService);

  // Start advertising
  BLE.advertise();
}

void loop() {
  // Process the BLE device
  BLE.poll();
}


void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void buzzTriggered(BLEDevice other, BLECharacteristic self) {
  // central wrote new value to characteristic, update LED
  Serial.print("Characteristic event, written: ");

  if (buzzTrigger.value()) {
    Serial.println("Buzz on");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    Serial.println("Buzz off");
    digitalWrite(LED_BUILTIN, LOW);
  }
}
