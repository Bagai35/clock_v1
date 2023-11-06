#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimeLib.h>
#include "buildTime.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SSD1306_I2C_ADDRESS 0x3C
#define BUTTON_PIN_MENU 6
#define BUTTON_PIN_NEXT 7 
#define BUTTON_PIN_PLS1 8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int receivedHour, receivedMinute, receivedSecond, receivedDay, receivedMonth, receivedYear;

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
  if (Serial.available() > 0) {
    // Read time and date from PC via Serial
    String input = Serial.readStringUntil('\n');
    sscanf(input.c_str(), "%d:%d:%d %d/%d/%d", &receivedHour, &receivedMinute, &receivedSecond, &receivedDay, &receivedMonth, &receivedYear);
    setTime(receivedHour, receivedMinute, receivedSecond, receivedDay, receivedMonth, receivedYear);
  }

  display.clearDisplay();
   
  // take real time and transform to string
  int hours = hour();
  int minutes = minute();
  int seconds = second();
  int dayOfMonth = day();
  int monthNumber = month();
  int yearNumber = year();
  
  char timeStr[9]; // Time format: "HH:MM:SS"
  char dateStr[11]; // date format "dd/mm/yyyy"

  sprintf(timeStr, "%02d:%02d:%02d", hours, minutes, seconds);
  sprintf(dateStr, "%02d/%02d/%02d", dayOfMonth, monthNumber, yearNumber);

  display.setCursor(18, 10);
  display.print(timeStr);
  display.setCursor(6, 40);
  display.print(dateStr);
  
  display.display();
  delay(1000); // Update every second
}
