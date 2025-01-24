#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pin definitions for buttons
const int dotButtonPin = 2;
const int dashButtonPin = 3;

// Timing parameters for dot and dash durations
const int dotDuration = 200; // milliseconds
const int dashDuration = 600; // milliseconds
const int interLetterSpace = 1000; // milliseconds

// Initialize display (adjust for your model)
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Morse Code Table (A-Z)
const String morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

char receivedLetter = ' ';
String morseInput = "";  // To store Morse code input

void setup() {
  Serial.begin(9600);

  pinMode(dotButtonPin, INPUT);
  pinMode(dashButtonPin, INPUT);

  // Initialize display
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Morse Code Decoder");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  static unsigned long buttonPressTime = 0;
  static bool dotButtonState = false;
  static bool dashButtonState = false;
  
  int dotButtonVal = digitalRead(dotButtonPin);
  int dashButtonVal = digitalRead(dashButtonPin);
  
  if (dotButtonVal == HIGH) {
    if (!dotButtonState) { // Button pressed down
      buttonPressTime = millis();
      dotButtonState = true;
    } 
  } else {
    if (dotButtonState) { // Button released
      if (millis() - buttonPressTime < dotDuration) {
        morseInput += ".";  // Add dot
        Serial.print(".");
      }
      dotButtonState = false;
    }
  }

  if (dashButtonVal == HIGH) {
    if (!dashButtonState) { // Button pressed down
      buttonPressTime = millis();
      dashButtonState = true;
    } 
  } else {
    if (dashButtonState) { // Button released
      if (millis() - buttonPressTime > dotDuration) {
        morseInput += "-";  // Add dash
        Serial.print("-");
      }
      dashButtonState = false;
    }
  }

  // Check for letter finish input (e.g., by pressing both buttons simultaneously)
  if (dotButtonVal == HIGH && dashButtonVal == HIGH) {
    processMorseInput();
    delay(interLetterSpace);  // Delay after processing a letter
  }
}

void processMorseInput() {
  // Convert Morse code to letter
  char decodedChar = decodeMorseCode(morseInput);
  if (decodedChar != ' ') {
    Serial.print("Decoded: ");
    Serial.println(decodedChar);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Decoded: ");
    display.print(decodedChar);
    display.display();
    delay(2000);  // Display for a while before clearing

    // Output the decoded letter to serial monitor
    Serial.print("Decoded letter: ");
    Serial.println(decodedChar);
  } else {
    Serial.println("Invalid Morse code");
  }
  morseInput = "";  // Reset input after processing
}

char decodeMorseCode(String morse) {
  for (int i = 0; i < 26; i++) {
    if (morse == morseCode[i]) {
      return 'A' + i;
    }
  }
  return ' ';  // Return space for invalid Morse
}
