# ESP32_Midea_RS485

# Home Assistant Integration:

1. copy the file GitHub\ESP32_Midea_RS485\example\esp32_midea_RS485_HA_sample\bunicutz_AC.h in HA in the folder /config/esphome/
2. initialize your esp32 device following normal esphome plugin procedure (if you do not have esphome plugin installed then install it)
3. copy the configuration of the sensor from the template GitHub\ESP32_Midea_RS485\example\esp32_midea_RS485_HA_sample\aer-conditionat.yaml

# HW connection:
Master configuration from:
https://microcontrollerslab.com/rs485-serial-communication-esp32-esp8266-tutorial/

# RS485 communication protocol
Special thanks to XYE for reverse engineering the protocol:
https://codeberg.org/xye/xye

# Interface description:

# Functions:
    begin:
       hwSerial - ESP32 HW serial unit connected to the bus
       ro_pin - RI pin
       di_pin - RO pin
       re_de_pin - RE/DE pin
       master_id - id of the master
       slave_id - id of the slave
       command_time - time in ms needed for command: ~40ms ()
       response_timeout - time after which the response is read: ~100ms
       
    SetMode
       mode  - ac mode
    SetFanMode
       fan_mode - ac fan mode
    SetTemp
       temp - ac temperature
    SetAuxHeat_Turbo
       value - switch on or off the feature
    SetEcho_Sleep
       value - switch on or off the feature
    SetSwing
       value - switch on or off the feature
    SetVent
       value - switch on or off the feature
    
    Update - call cyclically to send the commands
    
    Lock - call to lock the AC
    
    Unlock - call to unlock the AC

# Globals
    State
      Unknown1 - see https://codeberg.org/xye/xye
      Capabilities - see https://codeberg.org/xye/xye
      OpMode - see https://codeberg.org/xye/xye
      FanMode - see https://codeberg.org/xye/xye
      SetTemp - see https://codeberg.org/xye/xye
      T1Temp - see https://codeberg.org/xye/xye
      T2ATemp - see https://codeberg.org/xye/xye
      T2BTemp - see https://codeberg.org/xye/xye
      T3Temp - see https://codeberg.org/xye/xye
      Current - see https://codeberg.org/xye/xye
      Unknown2 - see https://codeberg.org/xye/xye
      TimerStart - see https://codeberg.org/xye/xye
      TimerStop - see https://codeberg.org/xye/xye
      Unknown3 - see https://codeberg.org/xye/xye
      ModeFlags - see https://codeberg.org/xye/xye
      OperatingFlags - see https://codeberg.org/xye/xye
      ErrorFlags - see https://codeberg.org/xye/xye
      ProtectFlags - see https://codeberg.org/xye/xye
      CCMComErrorFlags - see https://codeberg.org/xye/xye
      Unknown4 - see https://codeberg.org/xye/xye
      Unknown5 - see https://codeberg.org/xye/xye
      ACNotResponding - flag indicating the communication status with the AC
      
    SentData - send buffer : for debug purpose
    ReceivedData - receive buffer : for debug purpose



