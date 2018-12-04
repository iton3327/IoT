#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Sync(10, 11);

void countDown(byte limit){
  //int sec = limit*300;
  for(int i = 0 ; i < limit ; i++)  {
    Serial.print("-> remaining time : ");
    Sync.print("-> remaining time : ");
    Serial.println(limit - i);
    Sync.print(limit - i);
    delay(1000);
  }
}

void setup() {
  Serial.begin(9600);
  Sync.begin(115200);
}

void loop() {
  byte time_limit = 0;
  Serial.println("Ready!");
  while(!Sync.available());     // wait for command        
  char cmd = Sync.read();  
  delay(1000);
  switch(cmd){
    case 'q'    :
        Serial.println("Quick wash");
        Sync.print("Quick wash");
        time_limit = 10;
        break;
    case 'n'   :
        Serial.println("Normal wash");
        time_limit = 15;
        break;
    case 'l'   :
        Serial.println("Long time wash");
        time_limit = 20;
        break;
    default         :
        time_limit = 5;
        Serial.println(cmd);
        break;
  }

  delay(1000);
  Serial.println("Start!");
  Sync.print("Start!");
  delay(1000);
  Serial.println("Soak");
  Sync.print("Soak");
  countDown(2);
  // delay(2000);
  Serial.println("Washing");
  Sync.print("Washing");
  countDown(time_limit);
  Serial.println("First rinse");
  Sync.print("First rinse");
  countDown(4);
  Serial.println("Last rinse");
  Sync.print("Last rinse");
  countDown(4);
  Serial.println("Spinning");
  Sync.print("Spinning");
  countDown(7);
  Serial.print("Finished!");
  Sync.print("Finished!");
  delay(1500);
}
