

// Define the pins used based on your Python map
const int pinD = 2;
const int pinA = 3;
const int pinSpace = 4;
const int pinW = 5;
const int pinS = 6;

// Array of pins to easily loop through them
const int pins[] = {pinD, pinA, pinSpace, pinW, pinS};
const int numPins = sizeof(pins) / sizeof(pins[0]);

// Array to store the previous state of each pin (initially HIGH due to INPUT_PULLUP)
int lastStates[numPins];

void setup() {
  Serial.begin(9600); // Must match the 9600 baud rate in your Python script
  
  // Set up all pins with internal pull-up resistors
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], INPUT_PULLUP);
    lastStates[i] = HIGH; 
  }
}

void loop() {
  for (int i = 0; i < numPins; i++) {
    int currentState = digitalRead(pins[i]);
    
    // Detect if the button state changed (Press or Release event)
    if (currentState != lastStates[i]) {
      
      // First, send the pin number (e.g., "2")
      Serial.print(pins[i]);
      
      // Next, send 'P' for Press (LOW) or 'R' for Release (HIGH)
      if (currentState == LOW) {
        Serial.println("P"); // Enters a newline character (\n) at the end
      } else {
        Serial.println("R");
      }
      
      // Save the current state as the last state for the next loop
      lastStates[i] = currentState;
    }
  }
  
  delay(10); // A 10ms debounce delay to prevent button "ghost double-clicks"
}