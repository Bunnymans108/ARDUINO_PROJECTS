#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128          // OLED width, in pixels
#define SCREEN_HEIGHT 64          // OLED height, in pixels
#define SCREEN_I2C_ADDRESS 0x3C   // I2C address for OLED
#define OLED_RESET -1             // Reset pin (not used)

// Moisture Sensor Pin
#define MOISTURE_SENSOR_PIN A1    // Analog pin connected to the moisture sensor

// Moisture Levels (Reversed Logic)
#define DRY_THRESHOLD 1000        // Dry soil threshold
#define MODERATE_THRESHOLD 800    // Moderate soil threshold
#define WET_THRESHOLD 800         // Wet soil threshold (same as moderate start)

// Initialize OLED Display
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize OLED Display
  if (!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Halt if OLED fails to initialize
  }

  // Initial Screen Message
  screen.clearDisplay();
  screen.setTextSize(2);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  screen.println("Soil      Moisture  Sensor");
  screen.display();
  delay(2000);
}

void loop() {
  // Read Moisture Sensor Value
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN);
  Serial.print("Moisture Level: ");
  Serial.println(moistureValue);

  // Clear OLED Display
  screen.clearDisplay();

  // Display Moisture Level
  screen.setTextSize(1);
  screen.setCursor(0, 0);
  screen.println("Soil Moisture Level:");
  screen.setTextSize(2);
  screen.setCursor(0, 15);
  screen.print(moistureValue);

  // Update Plant Image Based on Moisture Level
  if (moistureValue > DRY_THRESHOLD) {
    // Dry Condition
    screen.setCursor(0, 40);
    screen.setTextSize(1);
    screen.println("Status: Dry");
    drawDryPlant();
  } else if (moistureValue > MODERATE_THRESHOLD) {
    // Moderate Condition
    screen.setCursor(0, 40);
    screen.setTextSize(1);
    screen.println("Status: Moderate");
    drawModeratePlant();
  } else {
    // Wet Condition
    screen.setCursor(0, 40);
    screen.setTextSize(1);
    screen.println("Status: Wet");
    drawHealthyPlant();
  }

  // Update OLED Display
  screen.display();

  // Delay for 1 second before next reading
  delay(1000);
}

// Function to draw a dry plant
void drawDryPlant() {
  screen.drawLine(90, 50, 95, 40, WHITE); // Dry stem
  screen.drawLine(95, 40, 100, 50, WHITE); // Dry stem
  screen.drawCircle(95, 35, 3, WHITE);     // Small dry leaf
}

// Function to draw a healthy plant
void drawHealthyPlant() {
  screen.drawLine(90, 50, 95, 30, WHITE); // Healthy stem
  screen.drawLine(95, 30, 100, 50, WHITE); // Healthy stem
  screen.fillCircle(93, 25, 5, WHITE);     // Large leaf
  screen.fillCircle(97, 25, 5, WHITE);     // Large leaf
}

// Function to draw a moderate plant
void drawModeratePlant() {
  screen.drawLine(90, 50, 95, 35, WHITE); // Moderate stem
  screen.drawLine(95, 35, 100, 50, WHITE); // Moderate stem
  screen.fillCircle(95, 30, 3, WHITE);     // Moderate leaf
}
