#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define buzzer 11 // This pin is used for Alarm
#define echopin 7 // Echo pin
#define trigpin 8 // Trigger pin
int Alarm = 1; 
int cm; // Duration used to calculate distance

// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialize the display

void setup() {  
  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
  pinMode(buzzer, OUTPUT); // Declare buzzer as output
  pinMode(trigpin, OUTPUT); // Declare ultrasonic sensor Trigger pin as Output
  pinMode(echopin, INPUT);  // Declare ultrasonic sensor Echo pin as input

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Use the I2C address 0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Halt if the OLED fails to initialize
  }
  display.display();  // Clear the buffer
  delay(2000);  // Pause for 2 seconds
}

void loop() {  
  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  
  // Measure the response from the HC-SR04 Echo Pin
  long ultra_time = pulseIn(echopin, HIGH);
  
  // Calculate distance in centimeters
  cm = ultra_time / 29 / 2; 
  Serial.print("cm:"); Serial.println(cm);

  // Clear display for new reading
  display.clearDisplay();
  
  // Display distance on OLED in large size
  display.setTextSize(3);      // Set text size (3 for large text)
  display.setTextColor(SSD1306_WHITE);  // Set text color

  // Convert the distance value to string for display
  String cmStr = String(cm); // Convert cm to a string
  int textWidth = cmStr.length() * 18; // Each character is roughly 18px wide at text size 3
  
  // Calculate the position to center the text
  int x = (SCREEN_WIDTH - textWidth) / 2;
  int y = (SCREEN_HEIGHT - 16) / 2; // Adjust vertical position for text size 3

  display.setCursor(x, y);   // Set cursor position to center the text
  display.print(cmStr);       // Print cm value as string

  display.display();  // Show the display

  // Buzzer logic based on the distance
  if (cm >= 10 && cm <= 100) {
    int d = map(cm, 10, 100, 20, 2000); 
    if (Alarm == 1) {
      digitalWrite(buzzer, HIGH);   // Turn on Buzzer 
      delay(100);  
      digitalWrite(buzzer, LOW);    // Turn off Buzzer 
      delay(d);    
    }
  }

  if (cm < 10) {
    if (Alarm == 1) {
      digitalWrite(buzzer, HIGH);   // Turn on Buzzer
    }
  }

  if (cm > 100) {
    digitalWrite(buzzer, LOW); // Turn off Buzzer 
  }
  
  delay(10);  // Small delay to prevent excessive screen updates
}
