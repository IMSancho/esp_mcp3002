#include "mcp3002.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {

namespace mcp3002 {

static const char *const TAG = "mcp3002";

float MCP3002::get_setup_priority() const { return setup_priority::HARDWARE; }

void MCP3002::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  this->spi_setup();
}

void MCP3002::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP3002:");
  LOG_PIN("  CS Pin:", this->cs_);
}

float MCP3002::read_data(uint8_t pin) {
  uint8_t data_null, data_msb, data_lsb = 0;

  uint8_t command = ((0x03 << 6) |          // sgl/diff bit
                     ((pin & 0x01) << 5));  // channel number

  this->enable();
  data_null = this->transfer_byte(0x01);

  //data_msb = this->transfer_byte(command) & 0x03;
  data_msb = this->transfer_byte(command);
  //data_msb = this->transfer_byte(0x0E) & 0x7F;
  data_lsb = this->transfer_byte(0x00);

  this->disable();

  uint16_t data = encode_uint16(data_msb, data_lsb);
  //uint16_t data = encode_uint16(data_null, data_msb);
  float dataf = data;
  // return data / 1023.0f;
  return dataf;
}

}  // namespace mcp3002

}  // namespace esphome
