import esphome.codegen as cg
from esphome.components import sensor, voltage_sampler
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_NUMBER,
    CONF_REFERENCE_VOLTAGE,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    UNIT_VOLT,
)

from .. import MCP3002, mcp3002_ns

AUTO_LOAD = ["voltage_sampler"]

DEPENDENCIES = ["mcp3002"]

MCP3002Sensor = mcp3002_ns.class_(
    "MCP3002Sensor",
    sensor.Sensor,
    cg.PollingComponent,
    voltage_sampler.VoltageSampler,
    cg.Parented.template(MCP3002),
)
CONF_MCP3002_ID = "mcp3002_id"

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        MCP3002Sensor,
        unit_of_measurement=UNIT_VOLT,
        state_class=STATE_CLASS_MEASUREMENT,
        device_class=DEVICE_CLASS_VOLTAGE,
    )
    .extend(
        {
            cv.GenerateID(CONF_MCP3002_ID): cv.use_id(MCP3002),
            cv.Required(CONF_NUMBER): cv.int_,
            cv.Optional(CONF_REFERENCE_VOLTAGE, default="3.3V"): cv.voltage,
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_parented(var, config[CONF_MCP3002_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    cg.add(var.set_pin(config[CONF_NUMBER]))
    cg.add(var.set_reference_voltage(config[CONF_REFERENCE_VOLTAGE]))
