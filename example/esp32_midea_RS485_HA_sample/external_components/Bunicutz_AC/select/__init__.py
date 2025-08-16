import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

from .. import CONF_BUNICUTZAC_ID, BUNICUTZAC_COMPONENT_SCHEMA, Bunicutz_AC_ns

BunicutzAC_Select = Bunicutz_AC_ns.class_("BunicutzAC_Select", cg.Component)

DEPENDENCIES = ["Bunicutz_AC"]
AUTO_LOAD = ["select"]

CONF_SETMODE = "SetMode"
CONF_SETFANMODE = "SetFanMode"

CONFIG_SCHEMA = BUNICUTZAC_COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(BunicutzAC_Select),
        cv.Required(CONF_SETMODE): select.select_schema(
           BunicutzAC_Select
        ),
        cv.Required(CONF_SETFANMODE): select.select_schema(
           BunicutzAC_Select
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):

    parn = await cg.get_variable(config[CONF_BUNICUTZAC_ID])

    if SetMode_config := config.get(CONF_SETMODE):
        sel = await select.new_select(SetMode_config,options=["Off","Auto","Cool","Dry","Heat","Fan","Unknown"])
        await cg.register_parented(sel, config[CONF_BUNICUTZAC_ID])
        cg.add(getattr(parn, f"set_{CONF_SETMODE}")(sel))

    if SetFanMode_config := config.get(CONF_SETFANMODE):
        sel = await select.new_select(SetFanMode_config,options=["Auto","High","Medium","Low","Unknown"])
        await cg.register_parented(sel, config[CONF_BUNICUTZAC_ID])
        cg.add(getattr(parn, f"set_{CONF_SETFANMODE}")(sel))
