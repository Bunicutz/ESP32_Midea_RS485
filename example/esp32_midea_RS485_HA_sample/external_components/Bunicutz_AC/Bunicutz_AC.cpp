#include "esphome/core/log.h"
#include "Bunicutz_AC.h"
#include <esp32_midea_RS485.h>

#define DI_PIN 16
#define RO_PIN 17 
#define DE_PIN 0
#define RE_PIN 0

#define SERIAL_COM_BUS &Serial2
#define SERIAL_COM_CONTROL_PIN DE_PIN
#define SERIAL_COM_MASTER_ID 0
#define SERIAL_COM_SLAVE_ID 0
#define SERIAL_COM_MASTER_SEND_TIME 40
#define SERIAL_COM_SLAVE_TIMEOUT_TIME 100

namespace esphome {
namespace Bunicutz_AC {

static const char *TAG = "Bunicutz_AC.component";

void BunicutzAC::setup() {

    ESP32_Midea_RS485.begin(SERIAL_COM_BUS,RO_PIN,DI_PIN,SERIAL_COM_CONTROL_PIN,SERIAL_COM_MASTER_ID,SERIAL_COM_SLAVE_ID,SERIAL_COM_MASTER_SEND_TIME,SERIAL_COM_SLAVE_TIMEOUT_TIME);

    SetMode_->add_on_state_callback([this](std::string value, size_t size)
                                        { if((1 != update_internal)&&(value != SetMode)){update_command =1;} });
    SetFanMode_->add_on_state_callback([this](std::string value, size_t size)
                                        { if((1 != update_internal)&&(value != SetFanMode)){update_command =1;}});
    SetTemp_->add_on_state_callback([this](float value)
                                        { if((1 != update_internal)&&(value != SetTemp)){update_command =1;}});
    aux_heat_->add_on_state_callback([this](bool value)
                                        { if((1 != update_internal)&&(value != aux_heat)){update_command =1;}});
    echo_sleep_->add_on_state_callback([this](bool value)
                                        { if((1 != update_internal)&&(value != echo_sleep)){update_command =1;}});
    swing_->add_on_state_callback([this](bool value)
                                        { if((1 != update_internal)&&(value != swing)){update_command =1;}});
    vent_->add_on_state_callback([this](bool value)
                                        { if((1 != update_internal)&&(value != vent)){update_command =1;}});
    lock_->add_on_state_callback([this](bool value)
                                        { if(value == 1){ESP32_Midea_RS485.Lock();}else{ESP32_Midea_RS485.Unlock();}});

}

void BunicutzAC::loop() {

}

void BunicutzAC::update() {

  float temp;
  uint8_t index;

  if(1==update_command)
  {
    SetMode = SetMode_->state.c_str();
  
    if(SetMode == "Auto")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_AUTO);
    }
    if(SetMode == "Off")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_OFF);
    }
    if(SetMode =="Cool")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_COOL);
    }
    if(SetMode == "Heat")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_HEAT);
    }
    if(SetMode == "Dry")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_DRY);
    }
    if(SetMode == "Fan")
    {
        ESP32_Midea_RS485.SetMode(MIDEA_AC_OPMODE_FAN);
    }
    
    SetFanMode = SetFanMode_->state.c_str();

    if(SetFanMode=="Auto")
    {
        ESP32_Midea_RS485.SetFanMode(MIDEA_AC_FANMODE_AUTO);
    }
    if(SetFanMode=="High")
    {
        ESP32_Midea_RS485.SetFanMode(MIDEA_AC_FANMODE_HIGH);
    }
    if(SetFanMode=="Medium")
    {
        ESP32_Midea_RS485.SetFanMode(MIDEA_AC_FANMODE_MEDIUM);
    }
    if(SetFanMode=="Low")
    {
        ESP32_Midea_RS485.SetFanMode(MIDEA_AC_FANMODE_LOW);
    }
    
    SetTemp = (SetTemp_->state)/1;
    ESP32_Midea_RS485.SetTemp(SetTemp);

    aux_heat = aux_heat_->state;
    if(!aux_heat)
    {
        ESP32_Midea_RS485.SetAuxHeat_Turbo(MIDEA_AC_ACTIVE);
    }else
        {
            ESP32_Midea_RS485.SetAuxHeat_Turbo(MIDEA_AC_INACTIVE);
        }
    
    echo_sleep = echo_sleep_->state;
    if(!echo_sleep)
    {
        ESP32_Midea_RS485.SetEcho_Sleep(MIDEA_AC_ACTIVE);
    }else
        {
            ESP32_Midea_RS485.SetEcho_Sleep(MIDEA_AC_INACTIVE);
        }

    vent = vent_->state;
    if(!vent)
    {
        ESP32_Midea_RS485.SetVent(MIDEA_AC_ACTIVE);
    }else
        {
            ESP32_Midea_RS485.SetVent(MIDEA_AC_INACTIVE);
        }

    swing = swing_->state;
    if(!swing)
    {
        ESP32_Midea_RS485.SetSwing(MIDEA_AC_ACTIVE);
    }else
        {
            ESP32_Midea_RS485.SetSwing(MIDEA_AC_INACTIVE);
        }

    update_command = 2;
  } 

  ESP32_Midea_RS485.Update();

  ESP_LOGD("custom","SentData: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x ",\
  ESP32_Midea_RS485.SentData[0],\
  ESP32_Midea_RS485.SentData[1],\
  ESP32_Midea_RS485.SentData[2],\
  ESP32_Midea_RS485.SentData[3],\
  ESP32_Midea_RS485.SentData[4],\
  ESP32_Midea_RS485.SentData[5],\
  ESP32_Midea_RS485.SentData[6],\
  ESP32_Midea_RS485.SentData[7],\
  ESP32_Midea_RS485.SentData[8],\
  ESP32_Midea_RS485.SentData[9],\
  ESP32_Midea_RS485.SentData[10],\
  ESP32_Midea_RS485.SentData[11],\
  ESP32_Midea_RS485.SentData[12],\
  ESP32_Midea_RS485.SentData[13],\
  ESP32_Midea_RS485.SentData[14],\
  ESP32_Midea_RS485.SentData[15]);
  ESP_LOGD("custom","ReceivedData: %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x",\
  ESP32_Midea_RS485.ReceivedData[0],\
  ESP32_Midea_RS485.ReceivedData[1],\
  ESP32_Midea_RS485.ReceivedData[2],\
  ESP32_Midea_RS485.ReceivedData[3],\
  ESP32_Midea_RS485.ReceivedData[4],\
  ESP32_Midea_RS485.ReceivedData[5],\
  ESP32_Midea_RS485.ReceivedData[6],\
  ESP32_Midea_RS485.ReceivedData[7],\
  ESP32_Midea_RS485.ReceivedData[8],\
  ESP32_Midea_RS485.ReceivedData[9],\
  ESP32_Midea_RS485.ReceivedData[10],\
  ESP32_Midea_RS485.ReceivedData[11],\
  ESP32_Midea_RS485.ReceivedData[12],\
  ESP32_Midea_RS485.ReceivedData[13],\
  ESP32_Midea_RS485.ReceivedData[14],\
  ESP32_Midea_RS485.ReceivedData[15],\
  ESP32_Midea_RS485.ReceivedData[16],\
  ESP32_Midea_RS485.ReceivedData[17],\
  ESP32_Midea_RS485.ReceivedData[18],\
  ESP32_Midea_RS485.ReceivedData[19],\
  ESP32_Midea_RS485.ReceivedData[20],\
  ESP32_Midea_RS485.ReceivedData[21],\
  ESP32_Midea_RS485.ReceivedData[22],\
  ESP32_Midea_RS485.ReceivedData[23],\
  ESP32_Midea_RS485.ReceivedData[24],\
  ESP32_Midea_RS485.ReceivedData[25],\
  ESP32_Midea_RS485.ReceivedData[26],\
  ESP32_Midea_RS485.ReceivedData[27],\
  ESP32_Midea_RS485.ReceivedData[28],\
  ESP32_Midea_RS485.ReceivedData[29],\
  ESP32_Midea_RS485.ReceivedData[30],\
  ESP32_Midea_RS485.ReceivedData[31],\
  ESP32_Midea_RS485.ReceivedData[32],\
  ESP32_Midea_RS485.ReceivedData[33],\
  ESP32_Midea_RS485.ReceivedData[34],\
  ESP32_Midea_RS485.ReceivedData[35],\
  ESP32_Midea_RS485.ReceivedData[36],\
  ESP32_Midea_RS485.ReceivedData[37],\
  ESP32_Midea_RS485.ReceivedData[38],\
  ESP32_Midea_RS485.ReceivedData[39]);
  
  for(index=0;index<40;index++)
  {
    ESP32_Midea_RS485.ReceivedData[index]=0;
  }
  
  if(ESP32_Midea_RS485.State.ACNotResponding == 0)
  {
    update_internal = 1;
    
    if(ESP32_Midea_RS485.State.OpMode == MIDEA_AC_OPMODE_AUTO)
    {
       SetMode_->publish_state("Auto");
    }else if(ESP32_Midea_RS485.State.OpMode == MIDEA_AC_OPMODE_OFF)
    {
        SetMode_->publish_state("Off");
    }else if(ESP32_Midea_RS485.State.OpMode ==MIDEA_AC_OPMODE_COOL)
    {
        SetMode_->publish_state("Cool");
    }else if(ESP32_Midea_RS485.State.OpMode == MIDEA_AC_OPMODE_HEAT)
    {
        SetMode_->publish_state("Heat");
    }else if(ESP32_Midea_RS485.State.OpMode == MIDEA_AC_OPMODE_DRY)
    {
        SetMode_->publish_state("Dry");
    }else if(ESP32_Midea_RS485.State.OpMode == MIDEA_AC_OPMODE_FAN)
    {
        SetMode_->publish_state("Fan");
    }else
    {
        SetMode_->publish_state("Unknown");
    }

    if(ESP32_Midea_RS485.State.FanMode == MIDEA_AC_FANMODE_AUTO)
    {
       SetFanMode_->publish_state("Auto");
    }else if(ESP32_Midea_RS485.State.FanMode == MIDEA_AC_FANMODE_HIGH)
    {
        SetFanMode_->publish_state("High");
    }else if(ESP32_Midea_RS485.State.FanMode ==MIDEA_AC_FANMODE_MEDIUM)
    {
        SetFanMode_->publish_state("Medium");
    }else if(ESP32_Midea_RS485.State.FanMode == MIDEA_AC_FANMODE_LOW)
    {
        SetFanMode_->publish_state("Low");
    }else
    {
        SetFanMode_->publish_state("Unknown");
    }
    
    if(ESP32_Midea_RS485.State.SetTemp>0)
    {
        temp = ESP32_Midea_RS485.State.SetTemp * 1.0;
        SetTemp_->publish_state(temp);
    }else
        {
            SetTemp_->publish_state(18);
        }
    
    aux_heat_->publish_state((ESP32_Midea_RS485.State.ModeFlags&0x02)>0);
    echo_sleep_->publish_state((ESP32_Midea_RS485.State.ModeFlags&0x01)>0);
    vent_->publish_state((ESP32_Midea_RS485.State.ModeFlags&0x88)>0);
    swing_->publish_state((ESP32_Midea_RS485.State.ModeFlags&0x04)>0);

    update_internal = 0;
  }

  Unknown1_->publish_state(ESP32_Midea_RS485.State.Unknown1);
  Capabilities_->publish_state(ESP32_Midea_RS485.State.Capabilities);
  ACT1Temp_->publish_state(ESP32_Midea_RS485.State.T1Temp);
  ACT2ATemp_->publish_state(ESP32_Midea_RS485.State.T2ATemp);
  ACT2BTemp_->publish_state(ESP32_Midea_RS485.State.T2BTemp);
  ACT3Temp_->publish_state(ESP32_Midea_RS485.State.T3Temp);
  Current_->publish_state(ESP32_Midea_RS485.State.Current);
  Unknown2_->publish_state(ESP32_Midea_RS485.State.Unknown2);
  Unknown3_->publish_state(ESP32_Midea_RS485.State.Unknown3);
  OperatingFlags_->publish_state(ESP32_Midea_RS485.State.OperatingFlags);
  ErrorFlags_->publish_state(ESP32_Midea_RS485.State.ErrorFlags);
  ProtectFlags_->publish_state(ESP32_Midea_RS485.State.ProtectFlags);
  CCMComErrorFlags_->publish_state(ESP32_Midea_RS485.State.CCMComErrorFlags);
  Unknown4_->publish_state(ESP32_Midea_RS485.State.Unknown4);
  Unknown5_->publish_state(ESP32_Midea_RS485.State.Unknown5);
  ACNotResponding_->publish_state(ESP32_Midea_RS485.State.ACNotResponding);

}

void BunicutzAC::dump_config(){
    ESP_LOGCONFIG(TAG, "Bunicutz_AC component");
}


}  // namespace Bunicutz_AC
}  // namespace esphome