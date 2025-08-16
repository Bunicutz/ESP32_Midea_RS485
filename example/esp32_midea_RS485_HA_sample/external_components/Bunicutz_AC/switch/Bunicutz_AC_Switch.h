#pragma once

#include "../Bunicutz_AC.h"

namespace esphome {
namespace Bunicutz_AC {

class BunicutzAC_Switch : public switch_::Switch, public Parented<BunicutzAC> {
 public:

    BunicutzAC_Switch() = default;

  protected:
    
    void write_state(bool state) override;
    

};

}  // namespace Bunicutz_AC
}  // namespace esphome