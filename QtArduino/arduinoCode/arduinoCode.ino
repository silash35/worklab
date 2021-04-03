void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    String command = Serial.readString();

    if (command == "on") {
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (command == "off") {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
