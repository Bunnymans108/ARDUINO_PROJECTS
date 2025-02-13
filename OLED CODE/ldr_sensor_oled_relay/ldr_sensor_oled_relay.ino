#include <Wire.h>                          // Include Wire library for I2C
#include <Adafruit_GFX.h>                   // Include graphics library
#include <Adafruit_SSD1306.h>               // Include OLED display library

#define SENSOR_PIN 9
#define RELAY_PIN 10
#define START_DELAY 1000  // 1 second 
#define ON_TIME 1000      // 2 seconds on time

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long previousTime = millis();

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);  
  
  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Infinite loop if display doesn't initialize
  }
  
  display.clearDisplay();  // Clear the screen
  display.setTextColor(SSD1306_WHITE);  
  display.setCursor(0, 0);  
}

void loop() 
{
  
  int sensorValue = digitalRead(SENSOR_PIN);


  if (sensorValue == LOW)
  {
    if (millis() - previousTime > START_DELAY) 
  {
    digitalWrite(RELAY_PIN, HIGH); 
    previousTime = millis();  
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(40, 20);
    display.print("DAY");  
    display.display();
    delay(ON_TIME);  
  }
  }
  else
    {
      digitalWrite(RELAY_PIN, LOW);
      display.clearDisplay();
      display.setTextSize(3);
      display.setCursor(25, 20);
      display.print("NIGHT");  
      display.display();  
       
    }
}

