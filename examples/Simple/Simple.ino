#include <Arduino.h>
#include <SerialCommander.hpp>

SerialCommander commander;

void setup() {
  Serial.begin(115200);
  commander.begin(Serial);

  commander.add("hello", []() {
    Serial.println("Hello from SerialCommander!");
  });
}

void loop() {
  commander.update(); // Continuously check for new commands
}
