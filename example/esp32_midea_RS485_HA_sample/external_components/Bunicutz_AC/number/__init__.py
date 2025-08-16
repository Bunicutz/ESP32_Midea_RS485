import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv

from .. import CONF_BUNICUTZAC_ID, BUNICUTZAC_COMPONENT_SCHEMA, Bunicutz_AC_ns

DEPENDENCIES = ["Bunicutz_AC"]
AUTO_LOAD = ["number"]

CONF_SETTEMP = "SetTemp"

BunicutzAC_Number = Bunicutz_AC_ns.class_("BunicutzAC_Number", cg.Component)


CONFIG_SCHEMA =  BUNICUTZAC_COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(BunicutzAC_Number),
        cv.Required(CONF_SETTEMP): number.number_schema(
           BunicutzAC_Number,
           unit_of_measurement="°C",
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    parn = await cg.get_variable(config[CONF_BUNICUTZAC_ID])

    if SetTemp_config := config.get(CONF_SETTEMP):
        nbr = await number.new_number(SetTemp_config, min_value=18, max_value=32, step=1)
        await cg.register_parented(nbr, parn)
        cg.add(getattr(parn, f"set_{CONF_SETTEMP}")(nbr))

