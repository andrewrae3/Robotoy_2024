const byte ROWS = 12; // 12 rows
const byte COLS = 8;  // 8 columns

// Define the symbols for each button on the matrix
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5', '6', '7', '8'},
  {'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'},
  {'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'},
  {'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W'},
  {'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e'},
  {'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'},
  {'n', 'o', 'p', 'q', 'r', 's', 't', 'u'},
  {'v', 'w', 'x', 'y', 'z', '0', '1', '2'},
  {'3', '4', '5', '6', '7', '8', '9', '!'},
  {'@', '#', '$', '%', '^', '&', '*', '('},
  {')', '-', '_', '=', '+', '[', ']', '{'},
  {'}', '|', ';', ':', '"', '/', '<', '>'}
};

// Define the row and column pin mappings
byte rowPins[ROWS] = { 38, 40, 42, 44, 37, 35, 34, 36, 45, 43, 41, 39 };  
byte colPins[COLS] = { 46, 48, 50, 52, 53, 51, 49, 47 };

// Variables for debounce handling
char lastKey = '\0';
unsigned long lastKeyPressTime = 0;
const unsigned long debounceDelay = 200;  // Adjust if needed

void setup() {
  Serial.begin(9600);

  // Initialize row pins as OUTPUT and set them HIGH initially
  for (byte i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Initialize column pins as INPUT_PULLUP (active low logic)
  for (byte i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  scanMatrix();
  delay(50); // Small delay to prevent excessive CPU usage
}

void scanMatrix() {
  for (byte row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW); // Activate one row at a time

    for (byte col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == LOW) { // Detect key press
        char pressedKey = hexaKeys[row][col];

        if (pressedKey != lastKey || (millis() - lastKeyPressTime) > debounceDelay) {
          Serial.print("Key Pressed: ");
          Serial.println(pressedKey);

          lastKey = pressedKey; // Store last pressed key
          lastKeyPressTime = millis(); // Record press time

          // Wait for key release to avoid repeated detection
          while (digitalRead(colPins[col]) == LOW) {
            delay(10);
          }
          lastKey = '\0'; // Reset last key after release
        }
      }
    }

    digitalWrite(rowPins[row], HIGH); // Deactivate row
  }
}
