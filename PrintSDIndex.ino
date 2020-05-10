void sdTest(){

Serial.print("\r\nWaiting for SD card to initialise...");
  if (!SD.begin(chipSelect)) { // CS is D8 in this example
    Serial.println("Initialising failed!");
    return;
  }


  Serial.println("Initialisation completed");
    // SD.open(filename,OPEN_READ|OPEN_WRITE) SD.open(filename) defaults to OPEN_READ
  root = SD.open("/");
  root.rewindDirectory();
  printDirectory(root, 0); //Display the card contents
  root.close();
  Serial.println("\r\nOPEN FILE example completed");
//  Serial.flush();
//  Serial.begin(74880);
//  while (!Serial.available());

}

void printDirectory(File dir, int numTabs) {
  int colcnt = 0;
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    if (numTabs > 0) {
      for (uint8_t i = 0; i <= numTabs; i++) {
        Serial.print('\t');
      }
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else
    {
      // files have sizes, directories do not
      Serial.print("\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
