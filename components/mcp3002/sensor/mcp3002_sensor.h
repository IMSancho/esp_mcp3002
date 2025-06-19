#pragma once

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"
#include "esphome/core/component.h"

#include "../mcp3002.h"

namespace esphome {
namespace mcp3002 {

class MCP3002Sensor : public PollingComponent,
                      public sensor::Sensor,
                      public voltage_sampler::VoltageSampler,
                      public Parented<MCP3002> {
 public:
  void set_reference_voltage(float reference_voltage) { this->reference_voltage_ = reference_voltage; }
  void set_pin(uint8_t pin) { this->pin_ = pin; }

  void update() override;
  void dump_config() override;
  float get_setup_priority() const override;
  //float sample() override;
  uint16_t sample() override;

 protected:
  uint8_t pin_;
  float reference_voltage_;
};

}  // namespace mcp3002
}  // namespace esphome
