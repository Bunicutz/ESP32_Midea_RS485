#pragma once

#include "esphome/core/component.h"
#include "esphome/components/select/select.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace Bunicutz_AC {

class BunicutzAC : public PollingComponent{
 public:

    void set_Unknown1(sensor::Sensor *Unknown1) { Unknown1_ = Unknown1; }
    void set_Capabilities(sensor::Sensor *Capabilities) { Capabilities_ = Capabilities; }
    void set_ACT1Temp(sensor::Sensor *ACT1Temp) { ACT1Temp_ = ACT1Temp; }
    void set_ACT2ATemp(sensor::Sensor *ACT2ATemp) { ACT2ATemp_ = ACT2ATemp; }
    void set_ACT2BTemp(sensor::Sensor *ACT2BTemp) { ACT2BTemp_ = ACT2BTemp; }
    void set_ACT3Temp(sensor::Sensor *ACT3Temp) { ACT3Temp_ = ACT3Temp; }
    void set_Current(sensor::Sensor *Current) { Current_ = Current; }
    void set_Unknown2(sensor::Sensor *Unknown2) { Unknown2_ = Unknown2; }
    void set_Unknown3(sensor::Sensor *Unknown3) { Unknown3_ = Unknown3; }
    void set_OperatingFlags(sensor::Sensor *OperatingFlags) { OperatingFlags_ = OperatingFlags; }
    void set_ErrorFlags(sensor::Sensor *ErrorFlags) { ErrorFlags_ = ErrorFlags; }
    void set_ProtectFlags(sensor::Sensor *ProtectFlags) { ProtectFlags_ = ProtectFlags; }
    void set_CCMComErrorFlags(sensor::Sensor *CCMComErrorFlags) { CCMComErrorFlags_ = CCMComErrorFlags; }
    void set_Unknown4(sensor::Sensor *Unknown4) { Unknown4_ = Unknown4; }
    void set_Unknown5(sensor::Sensor *Unknown5) { Unknown5_ = Unknown5; }
    void set_ACNotResponding(sensor::Sensor *ACNotResponding) { ACNotResponding_ = ACNotResponding; }


    void set_SetTemp(number::Number *SetTemp) { SetTemp_ = SetTemp; }

    void set_aux_heat(switch_::Switch *aux_heat) { aux_heat_ = aux_heat; }
    void set_echo_sleep(switch_::Switch *echo_sleep) { echo_sleep_ = echo_sleep; }
    void set_vent(switch_::Switch *vent) { vent_ = vent; }
    void set_swing(switch_::Switch *swing) { swing_ = swing; }
    void set_lock(switch_::Switch *lock) { lock_ = lock; }

    void set_SetMode(select::Select *SetMode) { SetMode_ = SetMode; }
    void set_SetFanMode(select::Select *SetFanMode) { SetFanMode_ = SetFanMode; }


    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;

  protected:
  
    sensor::Sensor *Unknown1_;
    sensor::Sensor *Capabilities_;
    sensor::Sensor *ACT1Temp_;
    sensor::Sensor *ACT2ATemp_;
    sensor::Sensor *ACT2BTemp_;
    sensor::Sensor *ACT3Temp_;
    sensor::Sensor *Current_;
    sensor::Sensor *Unknown2_;
    sensor::Sensor *Unknown3_;
    sensor::Sensor *OperatingFlags_;
    sensor::Sensor *ErrorFlags_;
    sensor::Sensor *ProtectFlags_;
    sensor::Sensor *CCMComErrorFlags_;
    sensor::Sensor *Unknown4_;
    sensor::Sensor *Unknown5_;
    sensor::Sensor *ACNotResponding_;

    number::Number *SetTemp_;

    switch_::Switch *aux_heat_;
    switch_::Switch *echo_sleep_;
    switch_::Switch *vent_;
    switch_::Switch *swing_;
    switch_::Switch *lock_;

    select::Select *SetMode_;
    select::Select *SetFanMode_;
    
    std::string SetMode = "Unknown";
    std::string SetFanMode = "Unknown";
    uint8_t SetTemp = 18;
    bool aux_heat = 0;
    bool echo_sleep = 0;
    bool vent = 0;
    bool swing = 0;
    bool lock = 0;

    uint8_t update_command=0;
    uint8_t update_internal=0;


};

}  // namespace Bunicutz_AC
}  // namespace esphome