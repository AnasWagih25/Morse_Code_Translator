#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Pin Definitions
const int dotButtonPin = 2;   // Button for dot
const int dashButtonPin = 3;  // Button for dash

// Morse Code Table (only for a-z and 0-9)
const char* morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",  // A-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

// Reverse Morse Code Lookup (for decoding from Morse to English)
char morseToEnglish[128];

String decodedMessage = "";

// Adafruit LCD Setup
Adafruit_LiquidCrystal lcd(0);

void setup() {
  // Initialize buttons
  pinMode(dotButtonPin, INPUT_PULLUP);
  pinMode(dashButtonPin, INPUT_PULLUP);

  // Initialize LCD
  lcd.begin(16, 2);  // 16x2 LCD
  lcd.setBacklight(LOW);  // Turn off backlight initially
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Morse Code Translator");

  // Initialize Serial communication
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial to initialize
  delay(1000);

  // Create reverse Morse code lookup table
  for (int i = 0; i < 36; i++) {
    if (i < 26) {
      morseToEnglish[i] = 'A' + i;  // A-Z
    } else {
      morseToEnglish[i + 26] = '0' + (i - 26);  // 0-9
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("Ready! Select mode:");
}

void loop() {
  // Check for incoming data from Serial Monitor
  if (Serial.available()) {
    char received = Serial.read();
    if (received == '1') {
      Serial.println("Morse-to-English Mode");
      lcd.clear();
      lcd.print("Enter Morse Code");
      lcd.setCursor(0, 1);
      lcd.print("Press Enter to Decode");
      decodeMorseInput();
    } else if (received == '2') {
      Serial.println("English-to-Morse Mode");
      lcd.clear();
      lcd.print("Enter English Text");
      lcd.setCursor(0, 1);
      lcd.print("Press Enter to Encode");
      encodeToMorse();
    }
  }
}

void decodeMorseInput() {
  // Now we wait for Morse Code via Serial Monitor
  String morseInput = "";
  char currentChar;
  
  while (true) {
    if (Serial.available()) {
      currentChar = Serial.read();
      if (currentChar == '\n') {
        // End of Morse input (Enter key pressed)
        break;
      } else {
        morseInput += currentChar;
      }
    }
  }

  // Now decode the Morse input to English
  String decoded = morseToEnglishString(morseInput);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Decoded: ");
  lcd.setCursor(0, 1);
  lcd.print(decoded);
}

String morseToEnglishString(String morse) {
  String decoded = "";
  int morseLen = morse.length();
  String currentSymbol = "";
  for (int i = 0; i < morseLen; i++) {
    char c = morse.charAt(i);
    if (c == '.' || c == '-') {
      currentSymbol += c;  // Build the current Morse symbol
    } else if (c == ' ') {
      // Space between Morse code symbols (a space means a new character)
      decoded += decodeMorseSymbol(currentSymbol);
      currentSymbol = "";  // Reset for next symbol
    }
  }
  if (currentSymbol != "") {
    decoded += decodeMorseSymbol(currentSymbol);  // Add last symbol
  }
  return decoded;
}

char decodeMorseSymbol(String symbol) {
  for (int i = 0; i < 36; i++) {
    if (symbol == morseCode[i]) {
      if (i < 26) {
        return 'A' + i;
      } else {
        return '0' + (i - 26);
      }
    }
  }
  return '?';  // Return '?' for unknown symbols
}

void encodeToMorse() {
  // Wait for English text input
  String inputText = "";
  char currentChar;
  
  while (true) {
    if (Serial.available()) {
      currentChar = Serial.read();
      if (currentChar == '\n') {
        break;  // End of text input (Enter key pressed)
      } else {
        inputText += currentChar;
      }
    }
  }

  // Now encode the text to Morse code
  String morseOutput = englishToMorseString(inputText);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Text Is:");
  lcd.setCursor(0, 1);
  lcd.print(morseOutput);
}

String englishToMorseString(String text) {
  String morse = "";
  text.toUpperCase();  // Convert to uppercase for consistency
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);
    if (c >= 'A' && c <= 'Z') {
      morse += morseCode[c - 'A'];  // Convert letter to Morse
    } else if (c >= '0' && c <= '9') {
      morse += morseCode[c - '0' + 26];  // Convert digit to Morse
    } else if (c == ' ') {
      morse += "  ";  // Space between words
    }
    morse += " ";  // Space between characters
  }
  return morse;
}
