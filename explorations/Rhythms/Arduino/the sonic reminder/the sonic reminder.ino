/**
 * The Sonic Reminder is a inactivity reminder which turns into a MIDI
 * controller
 *
 * Based on the BLE MIDI example by Adafruit. Written for an Adafruit Feather
 * nRF52840 Sense board.
 *
 * Some code used from:
 * https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/blemidi
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

#include <bluefruit.h>
#include <MIDI.h>

BLEDis bledis;
BLEMidi blemidi;

// Create a new instance of the Arduino MIDI Library,
// and attach BluefruitLE MIDI as the transport.
MIDI_CREATE_BLE_INSTANCE(blemidi);

// Variable that holds the current position in the sequence.
int position = 0;

// Store example melody as an array of note values
byte note_sequence[] = {
  74,78,81,86,90,93,98,102,57,61,66,69,73,78,81,85,88,92,97,100,97,92,88,85,81,78,
  74,69,66,62,57,62,66,69,74,78,81,86,90,93,97,102,97,93,90,85,81,78,73,68,64,61,
  56,61,64,68,74,78,81,86,90,93,98,102
};


// Add the accelarometer
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM6DS33.h>

Adafruit_LSM6DS33 lsm6ds33; // accelerometer, gyroscope


void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // Log when a note is pressed.
  Serial.printf("Note on: channel = %d, pitch = %d, velocity - %d", channel, pitch, velocity);
  Serial.println();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Log when a note is released.
  Serial.printf("Note off: channel = %d, pitch = %d, velocity - %d", channel, pitch, velocity);
  Serial.println();
}


void midiRead()
{
  // Don't continue if we aren't connected.
  if (! Bluefruit.connected()) {
    return;
  }

  // Don't continue if the connected device isn't ready to receive messages.
  if (! blemidi.notifyEnabled()) {
    return;
  }

  // read any new MIDI messages
  MIDI.read();
}

void setup()
{
  lsm6ds33.begin_I2C();
  lsm6ds33.setAccelRange(LSM6DS_ACCEL_RANGE_2_G); // keep it sensitive
  lsm6ds33.setAccelDataRate(LSM6DS_RATE_104_HZ);

  Serial.begin(115200);
  Serial.println("Adafruit Bluefruit52 MIDI over Bluetooth LE Example");

  Bluefruit.begin();
  Bluefruit.setName("Sonic Reminder 1");

  // Setup the on board blue LED to be enabled on CONNECT
  Bluefruit.autoConnLed(true);

  // Configure and Start Device Information Service
  bledis.setManufacturer("Poetic Systems");
  bledis.setModel("Sonic Reminder");
  bledis.begin();

  // Initialize MIDI, and listen to all MIDI channels
  // This will also call blemidi service's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Attach the handleNoteOn function to the MIDI Library. It will
  // be called whenever the Bluefruit receives MIDI Note On messages.
  MIDI.setHandleNoteOn(handleNoteOn);

  // Do the same for MIDI Note Off messages.
  MIDI.setHandleNoteOff(handleNoteOff);

  // Set General Discoverable Mode flag
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

  // Advertise TX Power
  Bluefruit.Advertising.addTxPower();

  // Advertise BLE MIDI Service
  Bluefruit.Advertising.addService(blemidi);

  // Advertise device name in the Scan Response
  Bluefruit.ScanResponse.addName();

  // Start Advertising
  Bluefruit.Advertising.start();

  // Start MIDI read loop
  Scheduler.startLoop(midiRead);
}

int previous = -1;
float progress = position;

void loop()
{
  // Don't continue if we aren't connected.
  if (! Bluefruit.connected()) {
    return;
  }

  // Don't continue if the connected device isn't ready to receive messages.
  if (! blemidi.notifyEnabled()) {
    return;
  }

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);
  // r->accel_x = accel.acceleration.x;
  // r->accel_y = accel.acceleration.y;
  // r->accel_z = accel.acceleration.z;
  // r->steps = lsm6ds33.readPedometer();

  // lis3mdl.read();
  // r->magnetic_x = lis3mdl.x;
  // r->magnetic_y = lis3mdl.y;
  // r->magnetic_z = lis3mdl.z;

  if (previous != position) {
    // Send Note On for current position at full velocity (127) on channel 1.
    MIDI.sendNoteOn(note_sequence[position], 127, 1);

    // Send Note Off for previous note.
    if (previous >= 0 && previous <= sizeof(note_sequence)) {
      MIDI.sendNoteOff(note_sequence[previous], 0, 1);
    }
  }

  // int tick = max(50, accel.acceleration.y * 286);
  float tick = map(accel.acceleration.y, -10, 10, -1, 1);
  // Increment position
  progress += tick;

  // If we are at the end of the sequence, start over.
  if (progress >= sizeof(note_sequence)) {
    progress = 0;
  } else if (progress < 0) {
    progress = sizeof(note_sequence) - 1;
  }

  previous = position;
  position = floor(progress);

  Serial.print("acc:\t"); Serial.print(accel.acceleration.y);
  Serial.print("\ttick\t"); Serial.print(tick);
  Serial.print("\tposition\t"); Serial.print(position);
  Serial.print("\tprogress\t"); Serial.print(progress);
  Serial.println();

  // delay(tick);
  delay(100);

}

