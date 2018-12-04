#include <Arduino.h>

HardwareSerial Serial1;
void setup(){
  Serial.begin(9600);
  // Serial1.begin(9600);
}

void loop(){
  while(Serial1.available() == 0);
  String msg = Serial1.read();
}