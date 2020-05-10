// Visit this page for more information:
// https://github.com/arduino-libraries/NTPClient

void getTime() {
  timeClient.update();
  currentHour = timeClient.getHours();
  currentMinutes = timeClient.getMinutes();
  currentDay = timeClient.getDay();
}
