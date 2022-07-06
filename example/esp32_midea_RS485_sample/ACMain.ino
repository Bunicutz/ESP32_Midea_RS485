
/*********
  Midea AC RS485 library usage example
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <WiFi.h>
#include <esp32_midea_RS485.h>



#define DI_PIN 16
#define RO_PIN 17 
#define DE_PIN 4
#define RE_PIN 4

#define SERIAL_COM_BUS &Serial2
#define SERIAL_COM_CONTROL_PIN DE_PIN
#define SERIAL_COM_MASTER_ID 0
#define SERIAL_COM_SLAVE_ID 0
#define SERIAL_COM_MASTER_SEND_TIME 40
#define SERIAL_COM_SLAVE_TIMEOUT_TIME 100

void setup() {

  Serial.begin(9600);
  Serial.println ("starting");

  ESP32_Midea_RS485.begin(SERIAL_COM_BUS,RO_PIN,DI_PIN,SERIAL_COM_CONTROL_PIN,SERIAL_COM_MASTER_ID,SERIAL_COM_SLAVE_ID,SERIAL_COM_MASTER_SEND_TIME,SERIAL_COM_SLAVE_TIMEOUT_TIME);
  
}


void loop() {

  Serial.println("===============================================================================");
  Serial.println("NewReadng");
  Serial.println("===============================================================================");
  
  ESP32_Midea_RS485.Update(); 
  
  Serial.print("Unknown1:");
  Serial.println(String(ESP32_Midea_RS485.State.Unknown1));
  Serial.print("Capabilities:");
  Serial.println(String(ESP32_Midea_RS485.State.Capabilities));
  Serial.print("OpMode:");
  Serial.println(String(ESP32_Midea_RS485.State.OpMode));
  Serial.print("FanMode:");
  Serial.println(String(ESP32_Midea_RS485.State.FanMode));
  Serial.print("SetTemp:");
  Serial.println(String(ESP32_Midea_RS485.State.SetTemp));
  Serial.print("T1Temp:");
  Serial.println(String(ESP32_Midea_RS485.State.T1Temp));
  Serial.print("T2ATemp:");
  Serial.println(String(ESP32_Midea_RS485.State.T2ATemp));
  Serial.print("T2BTemp:");
  Serial.println(String(ESP32_Midea_RS485.State.T2BTemp));
  Serial.print("T3Temp:");
  Serial.println(String(ESP32_Midea_RS485.State.T3Temp));
  Serial.print("Current:");
  Serial.println(String(ESP32_Midea_RS485.State.Current));
  Serial.print("Unknown2:");
  Serial.println(String(ESP32_Midea_RS485.State.Unknown2));
  Serial.print("TimerStart:");
  Serial.println(String(ESP32_Midea_RS485.State.TimerStart));
  Serial.print("TimerStop:");
  Serial.println(String(ESP32_Midea_RS485.State.TimerStop));
  Serial.print("Unknown3:");
  Serial.println(String(ESP32_Midea_RS485.State.Unknown3));
  Serial.print("ModeFlags:");
  Serial.println(String(ESP32_Midea_RS485.State.ModeFlags));
  Serial.print("OperatingFlags:");
  Serial.println(String(ESP32_Midea_RS485.State.OperatingFlags));
  Serial.print("ErrorFlags:");
  Serial.println(String(ESP32_Midea_RS485.State.ErrorFlags));
  Serial.print("ProtectFlags:");
  Serial.println(String(ESP32_Midea_RS485.State.ProtectFlags));
  Serial.print("CCMComErrorFlags:");
  Serial.println(String(ESP32_Midea_RS485.State.CCMComErrorFlags));
  Serial.print("Unknown4:");
  Serial.println(String(ESP32_Midea_RS485.State.Unknown4));
  Serial.print("Unknown5:");
  Serial.println(String(ESP32_Midea_RS485.State.Unknown5));
  Serial.print("ACNotResponding:");
  Serial.println(String(ESP32_Midea_RS485.State.ACNotResponding));
  delay(10000);
  
}
