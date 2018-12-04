#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
  Serial2.begin(115200);
  Serial.begin(115200);
}

void loop() {
  // while(!Serial.available() > 0);
  // char cmd = Serial.read();
  // Serial.print("Pressed: ");
  // Serial.println(cmd);

  Serial2.print("q");
  delay(40000);
  Serial2.print("n");
  delay(50000);
  Serial2.print("l");
  delay(50000);
}