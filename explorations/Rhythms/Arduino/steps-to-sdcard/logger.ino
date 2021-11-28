// Logger constants
// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t chipSelect = SS;

// Interval between data records in milliseconds.
// The interval must be greater than the maximum SD write latency plus the
// time to acquire and write data to the SD to avoid overrun errors.
// Run the bench example to check the quality of your SD card.
const uint32_t SAMPLE_INTERVAL_MS = 200;

// Log file base name.  Must be six characters or less.
#define FILE_BASE_NAME "Data"
//------------------------------------------------------------------------------
// File system object.
SdFat sd;

// Log file.
SdFile file;

//==============================================================================
// User functions.  Edit writeHeader() and logData() for your requirements.

//------------------------------------------------------------------------------
// Write data header.
void writeHeader() {
  file.print(F("time,steps"));
  file.println();
}
//------------------------------------------------------------------------------

//==============================================================================
// Error messages stored in flash.
#define error(msg) sd.errorHalt(F(msg))

//------------------------------------------------------------------------------
void setupLogger() {
  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  char fileName[13] = FILE_BASE_NAME "00.csv";

  // Initialize the SD card at SPI_HALF_SPEED to avoid bus errors with
  // breadboards.  use SPI_FULL_SPEED for better performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
    Serial.println(F("Error initialising SD card. Halting!"));
    while(true) {
      delay(100000000); // very long to save power
    }
  }

  // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
  while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      error("Can't create file name");
    }
  }
  if (!file.open(fileName, O_CREAT | O_WRITE | O_EXCL)) {
    error("file.open");
  }
  do {
    delay(10);
  } while (Serial.read() >= 0);

  Serial.print(F("Logging to: "));
  Serial.println(fileName);
  Serial.println(F("Type any character to stop"));

  // Write data header.
  writeHeader();

  // Start on a multiple of the sample interval.
  logTime = micros()/(1000UL*SAMPLE_INTERVAL_MS) + 1;
  logTime *= 1000UL*SAMPLE_INTERVAL_MS;
}

//------------------------------------------------------------------------------
void loopLogger() {
  // Time for next record.
  logTime += 1000UL*SAMPLE_INTERVAL_MS;

  // Wait for log time.
  int32_t diff;
  do {
    diff = micros() - logTime;
  } while (diff < 0);

  // Check for data rate too high.
  if (diff > 10) {
    error("Missed data record");
  }

  logData(file);

  // Force data to SD and update the directory entry to avoid data loss.
  if (!file.sync() || file.getWriteError()) {
    error("write error");
  }

  // file.close();
}