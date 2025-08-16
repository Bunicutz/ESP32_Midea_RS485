#pragma once

#include "../Bunicutz_AC.h"

namespace esphome {
namespace Bunicutz_AC {

class BunicutzAC_Number : public number::Number, public Parented<BunicutzAC> {
 public:

    BunicutzAC_Number() = default;

  protected:
    
    void control(float value) override;
    

};

}  // namespace Bunicutz_AC
}  // namespace esphome