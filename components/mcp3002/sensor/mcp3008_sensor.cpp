#include "mcp3002_sensor.h"

#include "esphome/core/log.h"

namespace esphome {
namespace mcp3002 {

static const char *const TAG = "mcp3002.sensor";

float MCP3002Sensor::get_setup_priority() const { return setup_priority::DATA; }

void MCP3002Sensor::dump_config() {
  ESP_LOGCONFIG(TAG,
                "MCP3002Sensor:\n"
                "  Pin: %u\n"
                "  Reference Voltage: %.2fV",
                this->pin_, this->reference_voltage_);
}

float MCP3002Sensor::sample() {
  float value_v = this->parent_->read_data(pin_);
  value_v = (value_v * this->reference_voltage_);
  return value_v;
}

void MCP3002Sensor::update() { this->publish_state(this->sample()); }

}  // namespace mcp3002
}  // namespace esphome
