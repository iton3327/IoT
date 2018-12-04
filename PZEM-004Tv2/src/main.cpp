#include <Arduino.h>
#include <HardwareSerial.h>
#include <PZEM004T.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

#define SSID "JookGroo"
#define PASSWORD "74107410"
#define FIREBASE_HOST "seniorpj-slm.firebaseio.com"
#define FIREBASE_AUTH "Kd7tgqE7m3POtfBgFtVKjMhYyA2JBXoqJbWJ4y9Y"
/*
   An example on how to use ESP32 hardware serial with PZEM004T
*/

// HardwareSerial Serial2(2);     // Use hwserial UART2 at pins IO-16 (RX2) and IO-17 (TX2)
PZEM004T pzem(&Serial2);
IPAddress ip(192,168,1,1);

/*
 * PDAControl
 * Documentation PDAControl English:
 * http://pdacontrolen.com/meter-pzem-004t-with-arduino-esp32-esp8266-python-raspberry-pi/
 * Documentacion PDAControl Español:
 * http://pdacontroles.com/medidor-pzem-004t-con-arduino-esp32-esp8266-python-raspberry-pi/
 * Video Tutorial : https://youtu.be/qt32YT_1oH8
 * 
 */

void setup() {
   Serial.begin(115200);

   WiFi.mode(WIFI_STA);
   WiFi.begin(SSID,PASSWORD);

   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
   }
   digitalWrite(LED_BUILTIN, HIGH);
   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());   

   while (true) {
      Serial.println("Connecting to PZEM...");
      if(pzem.setAddress(ip))
        break;
      delay(1000);
   }
}

// float cost = 0.0;
void loop() {

   float v = pzem.voltage(ip);
   if (v < 0.0) v = 0.0;
      Serial.print(v);Serial.print("V; ");

   float i = pzem.current(ip);
      if(i >= 0.0){ Serial.print(i);Serial.print("A; "); }

   float p = pzem.power(ip);
      if(p >= 0.0){ Serial.print(p);Serial.print("W; "); }

   float e = pzem.energy(ip);
      if(e >= 0.0){ Serial.print(e);Serial.print("Wh; "); }

   Serial.println();

   Firebase.setFloat("/cost/electric", p);
   // cost += e*3.5/1000;
   delay(3000);
}