/**
 * drv2605I-serial allows to trigger builtin haptic effect patterns over serial
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

#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("DRV test");
  drv.begin();
  
  drv.selectLibrary(6);
  drv.useLRA();
  
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG); 

  // set the effect to play: Strong Buzz
  drv.setWaveform(0, 14);  // play effect 
  drv.setWaveform(1, 0);       // end waveform

  Serial.begin(9600);
}

uint8_t effect = 1;

void loop() {
  if (Serial.available()) {
    effect = Serial.read();
    // set the effect to play: Strong Buzz
    drv.setWaveform(0, effect);  // play effect 
    drv.setWaveform(1, 0);       // end waveform
    drv.go();
    // wait a bit
    delay(10);
  }
}
