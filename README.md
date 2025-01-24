# Morse Code Decoder

## Overview
This project is a Morse Code Decoder that utilizes both a hardware interface and a serial monitor UI for decoding and displaying Morse code. The system interprets Morse code signals (dots and dashes) entered via buttons or transmitted through a serial monitor and translates them into text displayed on a screen.

### Features
- **Dual Input System:**
  - Hardware buttons for dots (.) and dashes (-).
  - Serial monitor interface for entering Morse code.
- **Real-Time Decoding:**
  - Converts input Morse code into human-readable text in real-time.
- **Interactive Display:**
  - Text output is displayed on an integrated screen.
- **Portable Design:**
  - Enclosed in a compact and vibrant orange case with clearly labeled buttons.

### Hardware Components
- **Microcontroller:** Arduino (specific model used in the code).
- **Display:** LCD or similar display for showing decoded text.
- **Input Buttons:**
  - Red button: Represents a dot (.).
  - Green button: Represents a dash (-).
  - Additional buttons or switches for functionality.
- **Case:** Custom 3D-printed orange enclosure.
- **LED Indicators:** Provides visual feedback for inputs.

### Software Features
- **Morse Code Translation Algorithm:**
  - Decodes dots and dashes into alphanumeric characters.
  - Handles space for separating words.
- **Serial Monitor Interface:**
  - Allows Morse code input through the Arduino IDE serial monitor.
  - Displays decoded output in the serial monitor as well.

---

## How to Use

### Hardware Setup
1. Connect the buttons and LEDs to the Arduino as per the pin assignments in the code.
2. Mount the display onto the case and connect it to the appropriate pins.
3. Secure all components inside the enclosure.
4. Power the device using a USB cable or a suitable power source.

### Software Setup
1. Open the Arduino IDE on your computer.
2. Connect the Arduino to your computer via USB.
3. Upload the provided `morse_code_Interpreter.ino` sketch to the Arduino.
4. Open the Serial Monitor (ensure the baud rate matches the code configuration).

### Operating Instructions
1. **Using the Buttons:**
   - Press the red button for a dot (.).
   - Press the green button for a dash (-).
   - Release the button to register the input.
2. **Using the Serial Monitor:**
   - Type Morse code using `.` for dots and `-` for dashes.
   - Separate each character with a space and use `/` to separate words.
   - Press `Enter` to send the input for decoding.
3. **Reading the Output:**
   - Decoded text will appear on the display and the Serial Monitor.

---

## Code Structure
- **`setup()` Function:** Initializes the pins, display, and serial communication.
- **`loop()` Function:** Continuously reads inputs from buttons and the serial monitor and decodes them.
- **Morse Code Dictionary:** A mapping of Morse code patterns to alphanumeric characters.

---

## Files
- **Hardware Design:** Schematic and wiring diagram (if applicable).
- **Software Code:** `morse_code_Interpreter.ino`
- **Demonstration Video:** `MC1.mp4`
- **Images:** `MC.jpg` (device photo).

---

## Future Improvements
1. Add support for special characters and symbols.
2. Implement audio feedback for inputs (e.g., beeps for dots and dashes).
3. Expand the dictionary for international Morse code.
4. Integrate a battery for standalone operation.
5. Enhance the case design for better ergonomics and durability.

---

## License
This project is open-source and licensed under the [MIT License](https://opensource.org/licenses/MIT).

---
Thank you for using the Morse Code Decoder!

