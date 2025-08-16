#include "esphome/core/log.h"
#include "Bunicutz_AC_Number.h"

namespace esphome {
namespace Bunicutz_AC {

void BunicutzAC_Number::control(float value) {
     
  this->publish_state(value);

}



}  // namespace Bunicutz_AC
}  // namespace esphome