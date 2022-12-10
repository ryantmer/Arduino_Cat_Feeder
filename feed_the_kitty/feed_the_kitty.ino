unsigned int LED_PIN = 2;
unsigned int MOTOR_PIN = 8;
unsigned long DISPENSE_INTERVAL = 12UL * 60 * 60 * 1000; // Dispense every 1h.
int MOTOR_RUNTIME = 4 * 1000; // Run dispensing motor for 4 seconds each time.
int DELAY = 30 * 1000; // Run loop (and thus flash LED) every 30 seconds.
int LED_RUNTIME = 200; // Flash LED at 5Hz.

unsigned int dispenseCount = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting up. MOTOR_RUNTIME=" + String(MOTOR_RUNTIME) + ", DISPENSE_INTERVAL=" + String(DISPENSE_INTERVAL / 1000) + " seconds");
}

void loop() {
  Serial.println("Millis since boot: " + String(millis()));
  Serial.println("Dispense Count: " + String(dispenseCount));
  Serial.println("Dispense Interval: " + String(DISPENSE_INTERVAL));

  if (millis() >= dispenseCount * DISPENSE_INTERVAL) {
    dispenseCount++;

    Serial.println("Dispensing...");
    digitalWrite(MOTOR_PIN, HIGH);
    delay(MOTOR_RUNTIME);
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Dispensed.");
  }

  Serial.println("Flashing LED with current run count of " + String(dispenseCount));
  for (int i = 0; i < dispenseCount; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(LED_RUNTIME);
    digitalWrite(LED_PIN, LOW);
    delay(LED_RUNTIME);
  }

  delay(DELAY);
}
