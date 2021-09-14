#include <Arduino.h>

int command = 0;
char state = 'r';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0){
    // read the incoming byte:
    command = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(command, DEC);
    // you can compare the value received to a character constant, like 'g'.
    switch (command)
    {
    case 'g':
      Serial.println("I received a go command");

      switch (state){
        case 'r':
          Serial.println("Source state: red, target state: green");
          state = 'g';
          break;
        case 'g':
          Serial.println("Source state: green, target state: green");
          break;
      }
      break;
    case 's':
      Serial.println("I received a stop command");
      
      switch (state){
        case 'g':
          Serial.println("Source state: green, target state: yellow");
          state = 'y';
          _delay_ms(2000);
          Serial.println("Timeout");
          state = 'r';
          Serial.println("Source state: yellow, target state: red");
          break;
        case 'r':
          Serial.println("Source state: red, target state: red");
          break;
      }
      break;
    }
  }
}