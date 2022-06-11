unsigned int LED_PIN = 2;
unsigned int MOTOR_PIN = 8;
unsigned long DISPENSE_INTERVAL = 43200000; // 12h * 60m * 60s * 1000ms
int MOTOR_RUNTIME = 4000;
int DELAY = 30000;
int LED_RUNTIME = 200;

unsigned long milliseconds = 0;
unsigned int dispenseCount = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting up. MOTOR_RUNTIME=" + String(MOTOR_RUNTIME) + ", DISPENSE_INTERVAL=" + String(DISPENSE_INTERVAL / 1000) + " seconds");
}

void loop() {
  Serial.print("Milliseconds ");
  Serial.println(milliseconds);
  Serial.print("Dispense Count ");
  Serial.println(dispenseCount);
  
  if (milliseconds == 0 || milliseconds >= DISPENSE_INTERVAL) {
    // It has been at least DISPENSE_INTERVAL milliseconds since the last dispense
    dispenseCount++;
    
    Serial.println("Dispensing...");
    digitalWrite(MOTOR_PIN, HIGH);
    
    delay(MOTOR_RUNTIME);
    milliseconds += MOTOR_RUNTIME;
    
    digitalWrite(MOTOR_PIN, LOW);
    Serial.println("Dispensed.");
    
    milliseconds = 0;
  }

  Serial.println("Flashing LED with current run count of " + String(dispenseCount));
  for (int i = 0; i < dispenseCount; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LED_RUNTIME);
    milliseconds += LED_RUNTIME;
    
    digitalWrite(LED_BUILTIN, LOW);
    delay(LED_RUNTIME);
    milliseconds += LED_RUNTIME;
  }

  delay(DELAY);
  milliseconds += DELAY;
}
