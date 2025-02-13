#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHTPIN 13               // DHT sensor pin
#define DHTTYPE DHT11          // DHT sensor type

#define SCREEN_WIDTH 128       // OLED display width (in pixels)
#define SCREEN_HEIGHT 64      // OLED display height (in pixels)
#define SCREEN_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

DHT dht(DHTPIN, DHTTYPE);    // Initialize DHT sensor
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  dht.begin();  // Initialize the DHT sensor
  if (!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Halt if OLED fails to initialize
  }

  // Initial display message
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor(0, 0);
  screen.print("Initializing...");
  screen.display();
  delay(2000);  // Wait for 2 seconds
}

void loop() {
  delay(2000);  // Wait 2 seconds before taking another reading

  float temperature = dht.readTemperature();  // Read temperature
  float humidity = dht.readHumidity();  // Read humidity

  screen.clearDisplay();  // Clear the display for fresh data

  if (isnan(humidity) || isnan(temperature)) {
    // If reading fails, display an error
    screen.setTextSize(1);
    screen.setCursor(0, 20);
    screen.print("Failed to read");
    screen.setCursor(0, 35);
    screen.print("from DHT sensor!");
    screen.display();
    return;  // Exit the loop
  }

  // Display Temperature
  screen.setTextSize(1);
  screen.setCursor(0, 0);
  screen.print("Temperature:");
  screen.setTextSize(2);
  screen.setCursor(0, 12);
  screen.print(temperature);
  screen.print((char)247);  // Degree symbol
  screen.print("C");

  // Display Humidity
  screen.setTextSize(1);
  screen.setCursor(0, 35);
  screen.print("Humidity:");
  screen.setTextSize(2);
  screen.setCursor(0, 47);
  screen.print(humidity);
  screen.print(" %");

  screen.display();  // Update the screen
}
