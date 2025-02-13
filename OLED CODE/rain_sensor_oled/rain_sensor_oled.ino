#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display configuration
#define SCREEN_WIDTH 128        // OLED width, in pixels
#define SCREEN_HEIGHT 64        // OLED height, in pixels
#define OLED_RESET -1           // Reset pin (not used)
#define SCREEN_I2C_ADDRESS 0x3C // I2C address for OLED

// Rain Drop Sensor pin
#define RAIN_SENSOR_PIN A1      // Analog pin connected to Rain Sensor

// Threshold for rain detection
#define RAIN_THRESHOLD 500

// Initialize OLED display
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Start Serial Monitor
  Serial.begin(9600);

  // Initialize OLED display
  if (!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);  // Halt if OLED fails to initialize
  }

  // Initial screen message
  screen.clearDisplay();
  screen.setTextSize(2);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  screen.println("Rain      Detector");
  screen.display();
  delay(2000);
}

void loop() {
  // Read rain sensor value
  int rainValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);

  // Clear OLED display for fresh data
  screen.clearDisplay();

  if (rainValue < RAIN_THRESHOLD) {
    // Rain detected
    screen.setTextSize(1);
    screen.setCursor(0, 0);
    screen.println("Status: Raining");
    screen.setCursor(0, 12);
    screen.println("Stay dry!");

    // Display rain animation
    drawRainAnimation();
  } else {
    // No rain
    screen.setTextSize(1);
    screen.setCursor(0, 0);
    screen.println("Status: No Rain");
    screen.setCursor(0, 12);
    screen.println("Enjoy the sunshine!");
  }

  // Update OLED display
  screen.display();
  delay(1000);  // Delay before next reading
}

// Function to draw raining animation
void drawRainAnimation() {
  for (int i = 0; i < 5; i++) {
    int x = random(0, SCREEN_WIDTH);   // Random horizontal position
    int y1 = random(0, SCREEN_HEIGHT / 2);  // Random start position
    int y2 = y1 + 10;                 // Rain drop length

    screen.drawLine(x, y1, x, y2, WHITE);  // Draw rain drop
  }
}
