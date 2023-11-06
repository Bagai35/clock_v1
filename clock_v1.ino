#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>
#include "buildTime.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SSD1306_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600); 
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2); 
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  display.clearDisplay();
  
  // take real time and transform to string
  int hours = hour();
  int minutes = minute();
  int seconds = second();
  int dayOfMonth = BUILD_DAY;
  int monthNumber = BUILD_MONTH;
  int yearNumber = BUILD_YEAR;
  
  char timeStr[9]; // Time format: "HH:MM:SS"
  char buildTimeStr[20]; // Формат: "гггг-мм-дд чч:мм:сс"

  sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);

  sprintf(buildTimeStr, "%s", __DATE__);

  display.setCursor(0, 0);
  display.print(timeStr);
  display.setCursor(0, 40);
  display.print(buildTimeStr);
  
  
  display.display();
  delay(1000);
}
