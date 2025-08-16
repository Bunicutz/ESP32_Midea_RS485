#pragma once

#include "../Bunicutz_AC.h"
#include "esphome/components/select/select.h"

namespace esphome {
namespace Bunicutz_AC {

class BunicutzAC_Select : public select::Select, public Parented<BunicutzAC> {
 public:
    
    BunicutzAC_Select() = default;

  protected:
  
  void control(const std::string &value) override;

};

}  // namespace Bunicutz_AC
}  // namespace esphome