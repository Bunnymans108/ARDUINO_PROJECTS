#include <Servo.h>               // Servo library
#include <Wire.h>                 // Required for I2C communication
#include <Adafruit_GFX.h>         // Graphics library
#include <Adafruit_SSD1306.h>     // SSD1306 OLED library

Servo s1;  // Servo object

const int trigPin = 8;  // Trigger pin for ultrasonic sensor
const int echoPin = 7;  // Echo pin for ultrasonic sensor
long duration;
int distanceCm, distanceInch;

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);  // Set trig pin as output
  pinMode(echoPin, INPUT);   // Set echo pin as input

  s1.attach(12);  // Attach the servo to pin 12

  // Initialize OLED display with correct I2C address
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // I2C address 0x3C for 1.3" OLED
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);  // Infinite loop if OLED fails to initialize
  }

  display.display();  // Clear display buffer
  delay(2000);        // Pause for 2 seconds to allow the display to initialize
}

void loop() {
  // Trigger the ultrasonic sensor to measure distance
  digitalWrite(trigPin, LOW);  // Ensure trigPin is LOW for 2us
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Send the pulse to the trig pin
  delayMicroseconds(10);        // Keep HIGH for 10us
  digitalWrite(trigPin, LOW);   // Set trigPin LOW to stop pulse
  
  // Read the echo pin to get the duration of the pulse
  duration = pulseIn(echoPin, HIGH);  

  // Calculate the distance in cm and inches
  distanceCm = duration * 0.034 / 2;  // Calculate distance in cm
  distanceInch = duration * 0.0133 / 2;  // Calculate distance in inches
  
  // Print the distance to Serial Monitor for debugging
  Serial.println("Distance (cm): ");
  Serial.println(distanceCm);
  delay(50);  // Small delay to prevent serial print overload

  // Clear the OLED display
  display.clearDisplay();
  
  // Check if the object is within 10 cm
  if (distanceCm < 10) {
    s1.write(90);  // Open the gate (servo at 90 degrees)
    delay(500);   // Wait for 1 second while the servo is open

    // Display "GO" on the OLED screen
    display.setTextSize(3);  // Set text size to 2
    display.setTextColor(SSD1306_WHITE);  // Set text color to white
    display.setCursor(40, 20);  // Set text cursor position (centered)
    display.print("GO");
  } else {
    
    s1.write(0);   // Close the gate (servo at 0 degrees)
    delay(500);     // Small delay while the servo is moving

    // Display "STOP" on the OLED screen
    display.setTextSize(3);  // Set text size to 2
    display.setTextColor(SSD1306_WHITE);  // Set text color to white
    display.setCursor(30, 20);  // Set text cursor position (centered)
    display.print("STOP");
  }

  // Update the OLED display to show the current message
  display.display();
  delay(100);
}
