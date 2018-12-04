#include <Arduino.h>
#include <HardwareSerial.h>
/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {17, 5, 18, 19}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 0, 4, 16}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void stateReady(){
  Serial.println("Ready");
  Serial.println("Input your service key to start");
  Serial.println("Delete: '*'  Enter: '#'");
  Serial.print("-> ");
  char customKey = NULL;
  char input_key[4];
  for(byte i = 0 ; i < 4 ; i++){
    while(customKey == NULL){
      customKey = customKeypad.getKey();
    }
    input_key[i] = customKey;
    Serial.print('*');
    customKey = NULL;
  }
  Serial.print("\nKey : ");
  for(byte i = 0 ; i < 4 ; i++){
    Serial.print(input_key[i]);
  }
  Serial.println();
  
}

void stateInvalid(){
  Serial.println("Invalid service key");
  Serial.println("Press any key to try again");
}

void stateConfirm(){
  Serial.println("Confirm to start");
  Serial.println("*: Yes or #: No");
}

void stateRunning(){
  Serial.println("Washing");
  Serial.println("<username>");
}

void setup(){
  Serial.begin(115200);
  Serial2.begin(115200);
}
  
void loop(){
  stateReady();
}