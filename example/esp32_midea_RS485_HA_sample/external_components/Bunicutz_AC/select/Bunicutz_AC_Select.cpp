#include "esphome/core/log.h"
#include "Bunicutz_AC_Select.h"

namespace esphome {
namespace Bunicutz_AC {

void BunicutzAC_Select::control(const std::string &value)
{
    this->publish_state(value);
}

}  // namespace Bunicutz_AC
}  // namespace esphome