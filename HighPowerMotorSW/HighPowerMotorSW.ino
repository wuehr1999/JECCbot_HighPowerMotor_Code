#include "JECCbotAPI.h"

#include <Arduino.h>

void setup() {
  
  Serial.begin(115200);
  ResponseMessage message = initJECCbot();
  Serial.write(message.message);
  //Wire.begin();
}

void loop() {
  
  static String serialData = "";
  
  if(Serial.available())
  {
    char c = Serial.read();
    serialData += c;
    if(c == '\n')
    {
      char *str = new char[serialData.length()+1];
      serialData.toCharArray(str, serialData.length()+1);
      ResponseMessage message = processCommand(str);
      Serial.write(message.message);
      serialData = "";
    }
  }
}