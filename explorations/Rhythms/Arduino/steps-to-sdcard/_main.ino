/**
 * Steps to SDCard - Simple step count logger based on a BMA456 sensor
 *
 * Aim: Putting together BMA456 and SDCard lib examples to create a step logger.
 * Code partially taken from the examples.
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

#include <SPI.h>
#include <SdFat.h>
#include "arduino_bma456.h"

BMA456 counter;

// Time in micros for next data record.
uint32_t logTime;

uint32_t step = 0;

// logData is called by the logger internally (see logger.ino)
void logData(SdFile& file) {
  // Write data to file.  Start with log time in micros.
  file.print(logTime);
  // Log the step count
  file.print(step);
  // file.write('\n');
  file.println();
}

void setup(void) {
  Serial.begin(115200);

  while(!Serial); // wait for Serial

  Serial.println("BMA456 Step Counter");

  // Prepare the step counter module
  counter.initialize(RANGE_4G, ODR_1600_HZ, NORMAL_AVG4, CONTINUOUS);
  counter.stepCounterEnable();

  setupLogger();
}

void loop(void) {
  step = counter.getStepCounterOutput();
  loopLogger();
}
