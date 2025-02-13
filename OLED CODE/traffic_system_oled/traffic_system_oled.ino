#include <Wire.h>                          // Include Wire library for I2C
#include <Adafruit_GFX.h>                   // Include graphics library
#include <Adafruit_SSD1306.h>               // Include OLED display library

#define RED_PIN    2  // Red LED pin
#define YELLOW_PIN 3  // Yellow LED pin
#define GREEN_PIN  4  // Green LED pin

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long previousMillis = 0;  // Store the time for light transitions
const long redTime = 15000;         // Red light duration (15 seconds)
const long yellowTime = 3000;      // Yellow light duration (3 seconds)
const long greenTime = 15000;       // Green light duration (15 seconds)

enum LightState { RED, YELLOW, GREEN };  // States for traffic lights
LightState currentState = RED;           // Initial state is RED

unsigned long stateStartTime = 0;  // Tracks the start time of the current state
int remainingTime = 0;             // Remaining time for the current light state (in seconds)

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Infinite loop if display doesn't initialize
  }

  display.clearDisplay();  // Clear the screen
  display.setTextSize(2);  // Set text size to 2 (larger text)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  updateDisplay();  // Initial display update
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if we need to update the light state based on the timer
  if (currentMillis - stateStartTime >= 1000) {  // Update every second
    stateStartTime = currentMillis;
    remainingTime--;  // Decrease the remaining time by 1 second

    // If time for the current state has ended, switch to the next state
    if (remainingTime <= 0) {
      switch (currentState) {
        case RED:
          currentState = YELLOW;
          remainingTime = yellowTime / 1000;  // Convert ms to seconds
          break;
        case YELLOW:
          currentState = GREEN;
          remainingTime = greenTime / 1000;  // Convert ms to seconds
          break;
        case GREEN:
          currentState = RED;
          remainingTime = redTime / 1000;  // Convert ms to seconds
          break;
      }
    }

    // Control the LEDs based on the current state
    digitalWrite(RED_PIN, currentState == RED ? HIGH : LOW);
    digitalWrite(YELLOW_PIN, currentState == YELLOW ? HIGH : LOW);
    digitalWrite(GREEN_PIN, currentState == GREEN ? HIGH : LOW);

    // Update the OLED display with the current state
    updateDisplay();
  }
}

void updateDisplay() {
  display.clearDisplay();  // Clear previous display content
  
  // Calculate text width and height for centering the main state text
  int16_t textX, textY;
  uint16_t textWidth, textHeight;
  String stateText;

  // Set the appropriate text for the current state
  switch (currentState) {
    case RED:
      stateText = "STOP";
      break;
    case YELLOW:
      stateText = "READY";
      break;
    case GREEN:
      stateText = "GO";
      break;
  }

  // Get text width and height to center the main state text
  display.getTextBounds(stateText, 0, 0, &textX, &textY, &textWidth, &textHeight);
  
  // Center the main state text horizontally and vertically
  int xPos = (SCREEN_WIDTH - textWidth) / 2;
  int yPos = (SCREEN_HEIGHT - textHeight) / 2 - 10;  // Adjust slightly to leave space for seconds
  display.setCursor(xPos, yPos);
  display.print(stateText);  // Print the current state

  // Display remaining time at the bottom center
  String timeText = String(remainingTime) + "s";
  int timeWidth = timeText.length() * 12;  // Estimate width based on font size (12px per character)

  // Calculate position for the time display at the bottom center
  int timeXPos = (SCREEN_WIDTH - timeWidth) / 2;
  int timeYPos = SCREEN_HEIGHT - 16;  // Position near the bottom of the screen
  display.setCursor(timeXPos, timeYPos);
  display.print(timeText);  // Print the remaining time

  display.display();  // Update the display
}
