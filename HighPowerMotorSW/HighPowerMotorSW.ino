#include "HWDriver.h"

#include <Arduino.h>

#include <Wire.h>

void setup() {
  
  Serial.begin(115200);
  ResponseMessage message = initJECCbot();
  Serial.write(message.message);
  //Wire.begin();
}

void loop() {
      /*Serial.println("Scanning...");
 
  int nDevices = 0;
  for(int address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    int error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  */static String serialData = "";
  
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
