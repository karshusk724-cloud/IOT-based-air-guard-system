// IoT-Based Air Guard System
// ESP32 + MQ2 + LM35/DHT11 + Buzzer + LEDs

// Pin Definitions
int mq2Pin = 34;        // Gas sensor analog pin
int tempPin = 35;       // Temperature sensor analog pin (LM35)
int buzzer = 25;        // Buzzer pin
int redLED = 26;        // Danger LED
int greenLED = 27;      // Safe LED

// Threshold values (adjust based on testing)
int gasThreshold = 400;
int tempThreshold = 60; // Celsius equivalent approx

void setup() {
  Serial.begin(115200);

  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH); // Safe mode default
}

void loop() {
  int gasValue = analogRead(mq2Pin);
  int tempValue = analogRead(tempPin);

  // Convert temperature (for LM35)
  float voltage = tempValue * (3.3 / 4095.0);
  float temperature = voltage * 100;

  Serial.print("Gas Value: ");
  Serial.print(gasValue);
  Serial.print(" | Temperature: ");
  Serial.println(temperature);

  // Danger condition
  if (gasValue > gasThreshold || temperature > tempThreshold) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    Serial.println("⚠ ALERT: Fire or Gas Leak Detected!");
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    Serial.println("✅ Safe Environment");
  }

  delay(1000);
}
