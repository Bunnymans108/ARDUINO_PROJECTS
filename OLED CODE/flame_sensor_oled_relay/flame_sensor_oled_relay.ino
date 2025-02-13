
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




int relay = 10;
int buzzer = 11;
int FireA0 = A2;
// Your threshold value
int sensorThres = 250;

void setup() {

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(FireA0, INPUT);
  Serial.begin(9600);
}

void loop() {
   display.clearDisplay();
  int analogSensor = analogRead(FireA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 10);
  // Display static text
  display.println("Fire Level");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(32,30);
  display.print(analogSensor);
  display.display(); 
  
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {

    digitalWrite(relay, HIGH);
    noTone(buzzer);
  }
  else
  {

    digitalWrite(relay, LOW);
    tone(buzzer, 800, 200);
  }
  delay(100); noTone(buzzer);
}