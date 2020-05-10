// Visit this page for more information:
// https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient
// https://arduinojson.org/v6/example/

// the API used is from https://openweathermap.org/
// Key: bdad21eb71010b42f5e3d03cda1bb144

void httpRequest() {
  HTTPClient http;
  Serial.println('\n');
  Serial.print("[HTTP] begin...\n");
  http.useHTTP10(true);
  if (http.begin("http://api.openweathermap.org/data/2.5/weather?q=hardinxveld-giessendam,NL&units=metric&lang=NL&APPID=bdad21eb71010b42f5e3d03cda1bb144")) {  // HTTP



    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
         Serial.print("[HTTP] Succeeded");
        deserializeJson(doc, http.getStream());


        // Read values
        weatherType = String(doc["weather"][0]["description"].as<char*>());
        weatherTypeUpperCase = weatherType.substring(0, 1);
        weatherTypeUpperCase.toUpperCase();

        weatherTypeMain = String(doc["weather"][0]["main"].as<char*>());
        weatherTypeUpperCaseMain = weatherTypeMain.substring(0, 1);
        weatherTypeUpperCaseMain.toUpperCase();



      }
    } else {
      ucg.clearScreen();
      ucg.setPrintPos(0, 70);
      ucg.print(http.errorToString(httpCode).c_str());
      delay(5000);
      ucg.clearScreen();
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

  } else {
    ucg.clearScreen();
    ucg.setPrintPos(10, 70);
    ucg.print("[HTTP} Unable to connect");
    ucg.clearScreen();
    delay(5000);
    Serial.printf("[HTTP} Unable to connect\n");
  }
}
