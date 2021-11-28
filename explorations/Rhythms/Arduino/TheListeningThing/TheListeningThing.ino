/**
 * Logging Sensor/Step data to an OpenLog Board
 * 
 * Experiment failed due to an ancient OpenLog board not being able to update the firmware.
 * Code left in the repository for completeness of trials.
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

///* For LSM9DS1 9-axis IMU sensor */
//// The inertia messasuring unit

#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while(!Serial); // wait for Serial
  
  Serial.println("Openlog connecting...");
  Serial1.begin(9600);

  while(!Serial1); // wait for Serial

  Serial.println("Openlog ready");

  Serial1.print("hello\t");
  Serial1.println(analogRead(A0));

  Serial1.print(26);
  Serial1.print(26);
  Serial1.print(26);
  delay(200);
  Serial1.println("?");

  delay(2000);
}

void loop() {
  while (Serial1.available()) {
    Serial.print(Serial1.read());
  }
  while (Serial.available()) {
    Serial1.print(Serial.read());
  }
}
