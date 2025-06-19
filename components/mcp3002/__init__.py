import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["spi"]
AUTO_LOAD = ["sensor"]
MULTI_CONF = True

CONF_MCP3002 = "mcp3002"

mcp3002_ns = cg.esphome_ns.namespace("mcp3002")
MCP3002 = mcp3002_ns.class_("MCP3002", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(MCP3002),
    }
).extend(spi.spi_device_schema(cs_pin_required=True))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
