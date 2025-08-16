#include "esphome/core/log.h"
#include "Bunicutz_AC_Switch.h"

namespace esphome {
namespace Bunicutz_AC {

void BunicutzAC_Switch::write_state(bool state) {
     
  this->publish_state(state);

}



}  // namespace Bunicutz_AC
}  // namespace esphome