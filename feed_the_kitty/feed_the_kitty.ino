const unsigned int LED_PIN = 2;
const unsigned int MOTOR_PIN = 8;

// Run the motor every 12h
const unsigned long DISPENSE_INTERVAL = 43200000; // 12h * 60m * 60s * 1000ms
// Run motor for 4s, which dispenses the correct amount of food for this particular feeder
const int MOTOR_RUNTIME = 4000;
// Every 30s, flash the LED to indicate the number of times we've fed the kitty since boot
const int DELAY = 30000;
// Flash LED for 200ms - enough to be clearly visible on a low-framerate webcam
const int LED_RUNTIME = 200;

unsigned long dispenseCount = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting up. MOTOR_RUNTIME=" + String(MOTOR_RUNTIME) + ", DISPENSE_INTERVAL=" + String(DISPENSE_INTERVAL / 1000) + " seconds");
}

void feed_the_kitty() {
    Serial.println("Feeding the kitty...");
    digitalWrite(MOTOR_PIN, HIGH);
    delay(MOTOR_RUNTIME);
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Kitty fed.");
    
    dispenseCount++;
}

void flash_led() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LED_RUNTIME);
    digitalWrite(LED_BUILTIN, LOW);
    delay(LED_RUNTIME);
}

void loop() {
  Serial.println("Dispense Count " + dispenseCount);
  
  if (millis() >= DISPENSE_INTERVAL * dispenseCount) {
    // It has been at least DISPENSE_INTERVAL milliseconds since the last dispense,
    // meaning it is time to feed the kitty again
    feed_the_kitty();
  }

  Serial.println("Flashing LED with current run count of " + String(dispenseCount));
  for (int i = 0; i < dispenseCount; i++) {
    flash_led();
  }

  delay(DELAY);
}
