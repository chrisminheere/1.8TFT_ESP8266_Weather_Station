
//=================================Libraries===================================//
#include <ESP8266WiFi.h>
#include "Ucglib.h"                      // Core graphics library
#include <SPI.h>
#include <SD.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>
#include <SimpleTimer.h>
#include <ArduinoJson.h>

//=============================================================================//



//==================================Global Variables===================================//
int currentHour;
int currentMinutes;
int currentDay;

DynamicJsonDocument doc(1024);
File root;

String weatherType;
String weatherTypeUpperCase;

String weatherTypeMain;
String weatherTypeUpperCaseMain;


const char* ssid     = "*****";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "*****";               // The password of the Wi-Fi network

const String endpoint = "*****";
const String key = "*****";

const long utcOffsetInSeconds = 7200;                 //Winter (3600)  Zomer(7200).
const int chipSelect = D8;-

//=============================================================================//



//==============================Define Stuf Here===============================//
#define TFT_CS     D0
#define SD_CS      D8
#define TFT_RST    D3
#define TFT_DC     D4
#define PIXELCOLOR 0xFFFF
SimpleTimer timer;

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);

Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ TFT_DC, /*cs=*/ TFT_CS, /*reset=*/ TFT_RST);

//=============================================================================//


void setup() {
  Serial.begin(74880);                       //starts serial connection to computer.

  timer.setInterval(120000L, secondTimer);   //Time length of the 2nd timer. //1000L = 1Sec

  Serial.println('\n');
  Serial.println("Made By: Chris Minheere & Robert Donker    19-04-2020");
  Serial.println("https://github.com/chrisminheere");
  Serial.println('\n');



  //====================================WIFI==================================//
  WiFi.begin(ssid, password);   // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("  ");

  while (WiFi.status() != WL_CONNECTED) {   // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(".");
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  //==============================================================================//

  //============================Initializing SPI===========================//
  SD.begin(chipSelect);
  ucg.begin(UCG_FONT_MODE_SOLID);
  //==============================================================================//

  ucg.clearScreen();
  ucg.setRotate180();
  ucg.setColor(255, 255, 255);
  ucg.setFont(ucg_font_6x12_mf);
  ucg.setPrintPos(0, 15);
  ucg.println("Connected to:");
  ucg.setPrintPos(0, 30);
  ucg.println(ssid);
  ucg.setPrintPos(0, 45);
  ucg.setColor(0, 255, 0);
  ucg.println("IP address:  ");
  ucg.setPrintPos(0, 60);
  ucg.setColor(0, 0, 255);
  ucg.println(WiFi.localIP());
  delay(3000);
  ucg.clearScreen();
  ucg.setFont(ucg_font_7x14_mf);

  httpRequest(); //Retrieves weather data once after reset.
}
//=================================End of Setup====================================//




void loop() {
  timer.run();
  getTime();
  sdTest();
  drawLcd();


  delay(20000);
}
