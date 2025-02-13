#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// MQ-9 sensor and OLED configuration
#define GAS_SENSOR_PIN A0         // Analog pin connected to MQ-9
#define BUZZER_PIN 11              // Digital pin connected to the buzzer
#define SCREEN_WIDTH 128          // OLED display width (pixels)
#define SCREEN_HEIGHT 64          // OLED display height (pixels)
#define SCREEN_I2C_ADDRESS 0x3C   // OLED I2C address (use I2C scanner to confirm)
#define OLED_RESET_PIN -1         // OLED reset pin (not used)

// Threshold for gas detection
#define GAS_THRESHOLD 300

// Initialize OLED display
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  Serial.begin(9600);

  // Initialize the OLED screen
  if (!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);  // Halt if OLED fails to initialize
  }

  // Initial OLED message
  screen.clearDisplay();
  screen.setTextSize(2);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  screen.println("GasLeakage Detector");
  screen.display();
  delay(2000);

  // Initialize pins
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);  // Ensure buzzer is off initially
}

void loop() {
  int gasValue = analogRead(GAS_SENSOR_PIN);  // Read gas sensor value
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  screen.clearDisplay();  // Clear the OLED screen

  if (gasValue > GAS_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);  // Activate buzzer
    screen.setTextSize(1);
    screen.setCursor(0, 0);
    screen.println("WARNING!");
    screen.setCursor(0, 12);
    screen.println("Gas Leakage Detected!");
    screen.setCursor(0, 30);
    screen.setTextSize(2);
    screen.print("Level: ");
    screen.print(gasValue);
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
    screen.setTextSize(1);
    screen.setCursor(0, 0);
    screen.println("Status: Safe");
    screen.setCursor(0, 20);
    screen.setTextSize(2);
    screen.print("Level: ");
    screen.print(gasValue);
  }

  screen.display();  // Update the OLED
  delay(1000);  // Wait 1 second before next reading
}
