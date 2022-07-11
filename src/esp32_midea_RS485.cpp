#include "esp32_midea_RS485.h"
#include "HardwareSerial.h"

#define TEMP_LOW  17
#define TEMP_HIGH 30

#define MIDEA_BAUDRATE 4800

#define DEFAULT_SERIAL_COM_DI_PIN 16
#define DEFAULT_SERIAL_COM_RO_PIN 17 
#define DEFAULT_SERIAL_COM_BUS &Serial2
#define DEFAULT_SERIAL_COM_CONTROL_PIN 4
#define DEFAULT_SERIAL_COM_MASTER_ID 0
#define DEFAULT_SERIAL_COM_SLAVE_ID 0
#define DEFAULT_SERIAL_COM_MASTER_SEND_TIME 40
#define DEFAULT_SERIAL_COM_SLAVE_TIMEOUT_TIME 100

#define RS485_TX_PIN_VALUE HIGH
#define RS485_RX_PIN_VALUE LOW


    //Master command structure
    #define PREAMBLE      0XAA
    #define PROLOGUE      0X55
    
    #define MASTER_COMMAND_QERRY  0xC0
    #define MASTER_COMMAND_SET    0xC3
    #define MASTER_COMMAND_LOCK   0xCC
    #define MASTER_COMMAND_UNLOCK 0xCD
    
    #define FROM_MASTER           0x80
    
    #define OP_MODE_OFF          0x00
    #define OP_MODE_AUTO         0x80
    #define OP_MODE_FAN          0x81
    #define OP_MODE_DRY          0x82
    #define OP_MODE_HEAT         0x84
    #define OP_MODE_COOL         0x88
    
    #define FAN_MODE_AUTO        0x80
    #define FAN_MODE_HIGH        0x01
    #define FAN_MODE_MEDIUM      0x02
    #define FAN_MODE_LOW         0x04
    
    #define TEMP_SET_FAN_MODE    0xFF
    
    #define MODE_FLAG_AUX_HEAT   0x02
    #define MODE_FLAG_NORM       0x00
    #define MODE_FLAG_ECO        0x01
    #define MODE_FLAG_SWING      0x04
    #define MODE_FLAG_VENT       0x88
    
    #define TIMER_15MIN          0x01
    #define TIMER_30MIN          0x02
    #define TIMER_1HOUR          0x04
    #define TIMER_2HOUR          0x08
    #define TIMER_4HOUR          0x10
    #define TIMER_8HOUR          0x20
    #define TIMER_16HOUR         0x40
    #define TIMER_INVALID        0x80
    
    #define COMMAND_UNKNOWN      0x00  
    
    //Slave Response

    #define SLAVE_COMMAND_QERRY  0xC0
    #define SLAVE_COMMAND_SET    0xC3
    #define SLAVE_COMMAND_LOCK   0xCC
    #define SLAVE_COMMAND_UNLOCK 0xCD
    
    #define TO_MASTER            0x80
    
    #define RESPONSE_UNKNOWN     0x30  
    
    #define CAPABILITIES_EXT_TEMP 0x80  
    #define CAPABILITIES_SWING    0x10
    
    #define RESPONSE_UNKNOWN1    0xFF  
    #define RESPONSE_UNKNOWN2    0x01  
    
    #define OP_FLAG_WATER_PUMP   0x04  
    #define OP_FLAG_WATER_LOCK   0x80  
    
    #define RESPONSE_UNKNOWN3    0x00  

    #define TRANSMIT_CRC 16
    #define RECEIVE_CRC  32

ESP32_Midea_RS485Class::ESP32_Midea_RS485Class(HardwareSerial *hwSerial, uint8_t ro_pin, uint8_t di_pin, uint8_t re_de_pin, uint8_t master_id, uint8_t slave_id, uint8_t command_time, uint8_t response_timeout):
ComControlPin(re_de_pin),
SerialBus(hwSerial),
datain_pin(di_pin),
dataout_pin(ro_pin),
SlaveId(slave_id),
MasterId(master_id),
Master_Send_Time(command_time),
Slave_Resp_Time(response_timeout),
UpdateNextCycle(0)
{
}

void ESP32_Midea_RS485Class::begin(HardwareSerial *hwSerial, uint8_t ro_pin, uint8_t di_pin, uint8_t re_de_pin, uint8_t master_id, uint8_t slave_id, uint8_t command_time, uint8_t response_timeout)
{
  ComControlPin = re_de_pin;
  SerialBus = hwSerial;
  datain_pin=di_pin;
  dataout_pin=ro_pin;
  pinMode(ComControlPin, OUTPUT);
  digitalWrite(ComControlPin, RS485_RX_PIN_VALUE);
  SerialBus->begin(MIDEA_BAUDRATE, SERIAL_8N1, datain_pin, dataout_pin);
  SlaveId = slave_id;
  MasterId = master_id;
  Master_Send_Time = command_time;
  Slave_Resp_Time = response_timeout;
  UpdateNextCycle = 0;
  Update();
  DesiredState.OpMode = State.OpMode;
  DesiredState.FanMode = State.FanMode;
  DesiredState.SetTemp = State.SetTemp;
  DesiredState.TimerStart = State.TimerStart;
  DesiredState.TimerStop = State.TimerStop;
  if((State.ModeFlags&0x02) == 0x02)
  {
    DesiredState.AuxHeat_Turbo = MIDEA_AC_ACTIVE;
  }else
  {
    DesiredState.AuxHeat_Turbo = MIDEA_AC_INACTIVE;
  }
  if((State.ModeFlags&0x01) == 0x01)
  {
    DesiredState.Echo_Sleep = MIDEA_AC_ACTIVE;
  }else
  {
    DesiredState.Echo_Sleep = MIDEA_AC_INACTIVE;
  }
  if((State.ModeFlags&0x04) == 0x04)
  {
    DesiredState.Swing = MIDEA_AC_ACTIVE;
  }else
  {
    DesiredState.Swing = MIDEA_AC_INACTIVE;
  }
  if((State.ModeFlags&0x88) == 0x88)
  {
    DesiredState.Vent = MIDEA_AC_ACTIVE;
  }else
  {
    DesiredState.Vent = MIDEA_AC_INACTIVE;
  }
}

uint8_t ESP32_Midea_RS485Class::SetMode(MideaACOpModeType mode)
{
   DesiredState.OpMode = mode; 
   UpdateNextCycle = 1;
   return 1;     
}

uint8_t ESP32_Midea_RS485Class::SetFanMode(MideaACFanModeType mode)
{
   DesiredState.FanMode = mode; 
   UpdateNextCycle = 1;     
   return 1;     
}

uint8_t ESP32_Midea_RS485Class::SetTemp(uint8_t temp)
{
   DesiredState.SetTemp = temp; 
   UpdateNextCycle = 1;     
   return 1;     
}

uint8_t ESP32_Midea_RS485Class::SetAuxHeat_Turbo(MideaACOpFeatureStateType value)
{
   DesiredState.AuxHeat_Turbo = value; 
   UpdateNextCycle = 1;     
   return 1;     
}
uint8_t ESP32_Midea_RS485Class::SetEcho_Sleep(MideaACOpFeatureStateType value)
{
   DesiredState.Echo_Sleep = value; 
   UpdateNextCycle = 1;     
   return 1;     
}
uint8_t ESP32_Midea_RS485Class::SetSwing(MideaACOpFeatureStateType value)
{
   DesiredState.Swing = value; 
   UpdateNextCycle = 1;     
   return 1;     
}
uint8_t ESP32_Midea_RS485Class::SetVent(MideaACOpFeatureStateType value)
{
   DesiredState.Vent = value; 
   UpdateNextCycle = 1;     
   return 1;     
}


void ESP32_Midea_RS485Class::Update()
{
    uint8_t i,resp;
    
    if(0==UpdateNextCycle)
    {
      //construct querry command
      SentData[0] =  PREAMBLE;
      SentData[1] =  MASTER_COMMAND_QERRY;
      SentData[2] =  SlaveId;
      SentData[3] =  MasterId;
      SentData[4] =  FROM_MASTER;
      SentData[5] =  MasterId;
      SentData[6] =  0;
      SentData[7] =  0;
      SentData[8] =  0;
      SentData[9] =  0;
      SentData[10] =  0;
      SentData[11] =  0;
      SentData[12] =  0;
      SentData[13] =  0xFF-SentData[1];
      SentData[15] =  PROLOGUE;
      SentData[14] = CalculateCRC(TRANSMIT_CRC);
    }else
    {
      //construct set command
      SentData[0] =  PREAMBLE;
      SentData[1] =  MASTER_COMMAND_SET;
      SentData[2] =  SlaveId;
      SentData[3] =  MasterId;
      SentData[4] =  FROM_MASTER;
      SentData[5] =  MasterId;
      //set mode
      switch(DesiredState.OpMode)
      {
        case MIDEA_AC_OPMODE_OFF: SentData[6] =  OP_MODE_OFF; break;
        case MIDEA_AC_OPMODE_AUTO: SentData[6] =  OP_MODE_AUTO; break;
        case MIDEA_AC_OPMODE_FAN: SentData[6] =  OP_MODE_FAN; break;
        case MIDEA_AC_OPMODE_DRY: SentData[6] =  OP_MODE_DRY; break;
        case MIDEA_AC_OPMODE_HEAT: SentData[6] =  OP_MODE_HEAT; break;
        case MIDEA_AC_OPMODE_COOL: SentData[6] =  OP_MODE_COOL; break;
        default: SentData[6] =  OP_MODE_OFF;     
      }
      //set fan mode
      switch(DesiredState.FanMode)
      {
        case MIDEA_AC_FANMODE_AUTO: SentData[7] =  FAN_MODE_AUTO; break;
        case MIDEA_AC_FANMODE_HIGH: SentData[7] =  FAN_MODE_HIGH; break;
        case MIDEA_AC_FANMODE_MEDIUM: SentData[7] =  FAN_MODE_MEDIUM; break;
        case MIDEA_AC_FANMODE_LOW: SentData[7] =  FAN_MODE_LOW; break;
        default: SentData[7] =  FAN_MODE_AUTO;     
      }
      //set temp 
      SentData[8] =  DesiredState.SetTemp;
      //set mode flags
      SentData[9] =   (DesiredState.AuxHeat_Turbo<<1)|(DesiredState.Echo_Sleep<<0)|(DesiredState.Swing<<2)|(DesiredState.Vent*0x88);
      //set timer start
      SentData[10] =  CalculateSetTime(State.TimerStart);      
      //set timer stop
      SentData[11] =  CalculateSetTime(State.TimerStop);
      //unknown -> 0
      SentData[12] =  0;
      SentData[13] =  0xFF-SentData[1];
      SentData[15] =  PROLOGUE;
      SentData[14] = CalculateCRC(TRANSMIT_CRC);
      
      UpdateNextCycle=0;
    }  
    
    digitalWrite(ComControlPin, RS485_TX_PIN_VALUE);
    SerialBus->write(SentData,16);
    delay(Master_Send_Time);
    digitalWrite(ComControlPin, RS485_RX_PIN_VALUE);
    delay(Slave_Resp_Time);
    
    State.ACNotResponding = 0;
    
    resp = SerialBus->available();

    if(resp==32)
    {
        for(i=0;i<32;i++)
        {
            ReceivedData[i]=SerialBus->read();
        }
      if(1 == ParseResponse())
      {
        State.ACNotResponding = 1;
      }
    }else if(resp>0)
        {
            for(i=0;i<resp;i++)
            {
                ReceivedData[i]=SerialBus->read();
            }
            for(i=resp;i<40;i++)
            {
                ReceivedData[i]=0;
            }
            State.ACNotResponding = 2;
        } 
}

void ESP32_Midea_RS485Class::Lock()
{
    uint8_t i,resp;
    
      //construct lock command
      SentData[0] =  PREAMBLE;
      SentData[1] =  MASTER_COMMAND_LOCK;
      SentData[2] =  SlaveId;
      SentData[3] =  MasterId;
      SentData[4] =  FROM_MASTER;
      SentData[5] =  MasterId;
      SentData[6] =  0;
      SentData[7] =  0;
      SentData[8] =  0;
      SentData[9] =  0;
      SentData[10] =  0;
      SentData[11] =  0;
      SentData[12] =  0;
      SentData[13] =  0xFF-SentData[1];
      SentData[15] =  PROLOGUE;
      SentData[14] = CalculateCRC(TRANSMIT_CRC);
    
    digitalWrite(ComControlPin, RS485_TX_PIN_VALUE);
    SerialBus->write(SentData,16);
    delay(Master_Send_Time);
    digitalWrite(ComControlPin, RS485_RX_PIN_VALUE);
    delay(Slave_Resp_Time);
    
    State.ACNotResponding = 0;
    
    resp = SerialBus->available();

    if(resp==32)
    {
        for(i=0;i<32;i++)
        {
            ReceivedData[i]=SerialBus->read();
        }
      if(1 == ParseResponse())
      {
        State.ACNotResponding = 1;
      }
    }else if(resp>0)
        {
            for(i=0;i<resp;i++)
            {
                ReceivedData[i]=SerialBus->read();
            }
            for(i=resp;i<40;i++)
            {
                ReceivedData[i]=0;
            }
            State.ACNotResponding = 2;
        } 
}
void ESP32_Midea_RS485Class::Unlock()
{
    uint8_t i,resp;
    
      //construct unlock command
      SentData[0] =  PREAMBLE;
      SentData[1] =  MASTER_COMMAND_UNLOCK;
      SentData[2] =  SlaveId;
      SentData[3] =  MasterId;
      SentData[4] =  FROM_MASTER;
      SentData[5] =  MasterId;
      SentData[6] =  0;
      SentData[7] =  0;
      SentData[8] =  0;
      SentData[9] =  0;
      SentData[10] =  0;
      SentData[11] =  0;
      SentData[12] =  0;
      SentData[13] =  0xFF-SentData[1];
      SentData[15] =  PROLOGUE;
      SentData[14] = CalculateCRC(TRANSMIT_CRC);
    
    digitalWrite(ComControlPin, RS485_TX_PIN_VALUE);
    SerialBus->write(SentData,16);
    delay(Master_Send_Time);
    digitalWrite(ComControlPin, RS485_RX_PIN_VALUE);
    delay(Slave_Resp_Time);
    
    State.ACNotResponding = 0;
    
    resp = SerialBus->available();

    if(resp==32)
    {
        for(i=0;i<32;i++)
        {
            ReceivedData[i]=SerialBus->read();
        }
      if(1 == ParseResponse())
      {
        State.ACNotResponding = 1;
      }
    }else if(resp>0)
        {
            for(i=0;i<resp;i++)
            {
                ReceivedData[i]=SerialBus->read();
            }
            for(i=resp;i<40;i++)
            {
                ReceivedData[i]=0;
            }
            State.ACNotResponding = 2;
        } 
    
}

uint8_t ESP32_Midea_RS485Class::CalculateCRC(uint8_t len)
{
    uint8_t i=0;
    uint32_t crc=0;
    uint8_t retVal=0;
    for(i=0;i<len;i++)
    { 
        if(16==len)
        {
            if(i!=14)
            {
              crc+=SentData[i];
            }
        }else if (30!=i)
            {
                crc+=ReceivedData[i];
            } 
    }
    return 0xFF - (crc&0xFF);
}

void ESP32_Midea_RS485Class::ClearResponseBuffer()
{
    uint8_t i=0;
    for(i=0;i<32;i++)
    {
      ReceivedData[i]=0;   
    }
}

uint8_t ESP32_Midea_RS485Class::ParseResponse()
{
    // validate the response
    if(
    (PREAMBLE==ReceivedData[0])&&\
    (PROLOGUE==ReceivedData[0x1F])&&\
    (TO_MASTER==ReceivedData[0x2])&&\
    (ReceivedData[0x1E]==CalculateCRC(RECEIVE_CRC))\
    )
    {
        State.Unknown1 = ReceivedData[6];
        State.Capabilities = ReceivedData[7];
        switch(ReceivedData[8]) 
        {
            case OP_MODE_OFF: State.OpMode = MIDEA_AC_OPMODE_OFF; break;
            case OP_MODE_AUTO: State.OpMode = MIDEA_AC_OPMODE_AUTO; break;
            case OP_MODE_FAN: State.OpMode = MIDEA_AC_OPMODE_FAN; break;
            case OP_MODE_DRY: State.OpMode = MIDEA_AC_OPMODE_DRY; break;
            case OP_MODE_HEAT: State.OpMode = MIDEA_AC_OPMODE_HEAT; break;
            case OP_MODE_COOL: State.OpMode = MIDEA_AC_OPMODE_COOL; break;
            default: State.OpMode = MIDEA_AC_OPMODE_UNKOWN;
        }        

        switch(ReceivedData[9]) 
        {
            case FAN_MODE_HIGH: State.FanMode = MIDEA_AC_FANMODE_HIGH; break;
            case FAN_MODE_MEDIUM: State.FanMode = MIDEA_AC_FANMODE_MEDIUM; break;
            case FAN_MODE_LOW: State.FanMode = MIDEA_AC_FANMODE_LOW; break;
            default: State.FanMode = MIDEA_AC_FANMODE_UNKNOWN;
        }
        if(ReceivedData[9]&FAN_MODE_AUTO)
        {
            State.FanMode = MIDEA_AC_FANMODE_AUTO;
        }
        State.SetTemp = ReceivedData[0x0A];
        State.T1Temp = (ReceivedData[0x0B]-0x30)/2;        
        State.T2ATemp = (ReceivedData[0x0C]-0x30)/2;        
        State.T2BTemp = (ReceivedData[0x0D]-0x30)/2;        
        State.T3Temp = (ReceivedData[0x0E]-0x30)/2;
        State.Current = ReceivedData[0x0F];
        State.Unknown2 = ReceivedData[0x10];         
        State.TimerStart = CalculateGetTime(ReceivedData[0x11]);         
        State.TimerStop = CalculateGetTime(ReceivedData[0x12]);         
        State.Unknown3 = ReceivedData[0x13];         
        State.ModeFlags = ReceivedData[0x14];         
        State.OperatingFlags = ReceivedData[0x15];         
        State.ErrorFlags = (ReceivedData[0x16]<<0) | (ReceivedData[0x17]<<8);
        State.ProtectFlags = (ReceivedData[0x18]<<0) | (ReceivedData[0x19]<<8);
        State.CCMComErrorFlags = ReceivedData[0x1A];
        State.Unknown4 = ReceivedData[0x1B];
        State.Unknown5 = ReceivedData[0x1C];
     return 0;    
    }else
    {
        return 1;
    }
}

uint8_t ESP32_Midea_RS485Class::CalculateSetTime(uint32_t time)
{
   uint32_t current_time = time; 
   uint8_t timeValue=0;
   
   if(0<(current_time/960))
   {
      timeValue |=0x40;
      current_time = current_time % 960;
   }
   if(0<(current_time/480))
   {
      timeValue |=0x20;
      current_time = current_time % 480;
   }
   if(0<(current_time/240))
   {
      timeValue |=0x10;
      current_time = current_time % 240;
   }
   if(0<(current_time/120))
   {
      timeValue |=0x08;
      current_time = current_time % 120;
   }
   if(0<(current_time/60))
   {
      timeValue |=0x04;
      current_time = current_time % 60;
   }
   if(0<(current_time/30))
   {
      timeValue |=0x02;
      current_time = current_time % 30;
   }
   if(0<(current_time/15))
   {
      timeValue |=0x01;
      current_time = current_time % 15;
   }
   return timeValue; 
}
uint32_t ESP32_Midea_RS485Class::CalculateGetTime(uint8_t time)
{
   uint32_t timeValue=0;
   
   if(0x40 == (time&0x40))
   {
      timeValue += 960;
   }
   if(0x20 == (time&0x20))
   {
      timeValue += 480;
   }
   if(0x10 == (time&0x10))
   {
      timeValue += 240;
   }
   if(0x08 == (time&0x08))
   {
      timeValue += 120;
   }
   if(0x04 == (time&0x04))
   {
      timeValue += 60;
   }
   if(0x02 == (time&0x02))
   {
      timeValue += 30;
   }
   if(0x01 == (time&0x01))
   {
      timeValue += 15;
   }
   return timeValue; 
}


ESP32_Midea_RS485Class ESP32_Midea_RS485(DEFAULT_SERIAL_COM_BUS,DEFAULT_SERIAL_COM_RO_PIN,DEFAULT_SERIAL_COM_DI_PIN,DEFAULT_SERIAL_COM_CONTROL_PIN,DEFAULT_SERIAL_COM_MASTER_ID,DEFAULT_SERIAL_COM_SLAVE_ID,DEFAULT_SERIAL_COM_MASTER_SEND_TIME,DEFAULT_SERIAL_COM_SLAVE_TIMEOUT_TIME);