// Visit this page for more information:
// https://github.com/olikraus/Ucglib_Arduino         //Lib
// https://github.com/olikraus/ucglib/wiki/fontsize   //Fonts
// https://github.com/olikraus/ucglib/wiki/reference#table-of-contents

void drawLcd() {
//  ucg.begin(UCG_FONT_MODE_SOLID);
//  ucg.clearScreen();
//  ucg.setRotate180();


  //Prints the current date.
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(25, 13);
  ucg.setFont(ucg_font_helvR08_hf);  //Sets font.
  ucg.println("Ma, 20 Apr 2020");

  //Prints the current time.
  ucg.setFont(ucg_font_inr16_mn);
  ucg.setPrintPos(30, 35);
  ucg.print(currentHour);
  ucg.setPrintPos(58, 35);
  ucg.print(":");
  ucg.println(currentMinutes);



  ucg.setFont(ucg_font_helvR10_hf);  //Sets font.
  ucg.setPrintPos(5, 115);
  ucg.println(weatherTypeUpperCase + weatherType.substring(1));  //Prints current weather type.
  //  ucg.println(weatherTypeUpperCaseMain + weatherTypeMain.substring(1));

  ucg.setPrintPos(5, 138);
  ucg.setFont(ucg_font_helvB14_hf);  //Sets font.
  ucg.println(String(doc["main"]["temp"].as<int>()) + " " + char(176) + "C");  //Prints current temperature.
  ucg.setPrintPos(83, 138);
  ucg.println(String(doc["main"]["humidity"].as<int>()) + " %");  //Prints current humidity.


  ucg.setPrintPos(7, 155);
  ucg.setFont(ucg_font_helvR08_hf);  //Sets font.
  ucg.println(String(doc["name"].as<char*>())); //Prints current city.
}
