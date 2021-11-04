/**
 * Read Temperature, Light, Distance, and Humidity and TX over Serial.
 * 
 * Copyright (C) 2021  jens alexander ewald <jens@poetic.systems>
 * 
 * Based on provided example code from Officine Innesto.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * ------
 * 
 * This project has received funding from the European Union’s Horizon 2020
 * research and innovation programme under the Marie Skłodowska-Curie grant
 * agreement No. 813508.
 */

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// - Seeed Studio Ultrasonic: https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "Ultrasonic.h"

Ultrasonic ultrasonic(0);

const int ldrSensor = A0;

#define DHTPIN 2
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t sensorReadingTime;

void setup()
{
  Serial.begin(9600);

  dht.begin();

  // Create a temporary info structure   
  sensor_t sensor;

  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  // Note: min_delay is in microseconds
  sensorReadingTime = sensor.min_delay / 1000;

  Serial.println(F("# Device ready."));
  Serial.println(F("# Format of data line is: distance,analogueLight,temperature,humidity;"));
}


void loop()
{
  static String seperator = F(",");
  static String errorValue = F("-");

  // Read the distance
  long distance = ultrasonic.MeasureInCentimeters();
  Serial.print(distance);
  Serial.print(F(","));

  // Read the LDR
  int analogueLight = analogRead(ldrSensor);
  Serial.print(analogueLight);
  Serial.print(seperator);

  // Read from the DHT sensor
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Serial.print(errorValue);
  } else {
    Serial.print(event.temperature);
  }
  Serial.print(seperator);

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.print(errorValue);
  }
  else {
    Serial.print(event.relative_humidity);
  }
  Serial.print(seperator);

  Serial.println(F(";"));

  delay(sensorReadingTime);
}
