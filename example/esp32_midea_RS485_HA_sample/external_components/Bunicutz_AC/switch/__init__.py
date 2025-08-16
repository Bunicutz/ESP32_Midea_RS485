import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

from .. import CONF_BUNICUTZAC_ID, BUNICUTZAC_COMPONENT_SCHEMA, Bunicutz_AC_ns

DEPENDENCIES = ["Bunicutz_AC"]
AUTO_LOAD = ["switch"]

CONF_AUX_HEAT = "aux_heat"
CONF_ECHO_SLEEP = "echo_sleep"
CONF_VENT = "vent"
CONF_SWING = "swing"
CONF_LOCK = "lock"

BunicutzAC_Switch = Bunicutz_AC_ns.class_("BunicutzAC_Switch", cg.Component)


CONFIG_SCHEMA =  BUNICUTZAC_COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(BunicutzAC_Switch),
        cv.Required(CONF_AUX_HEAT): switch.switch_schema(
           BunicutzAC_Switch
        ),
        cv.Required(CONF_ECHO_SLEEP): switch.switch_schema(
           BunicutzAC_Switch
        ),
        cv.Required(CONF_VENT): switch.switch_schema(
           BunicutzAC_Switch
        ),
        cv.Required(CONF_SWING): switch.switch_schema(
           BunicutzAC_Switch
        ),
        cv.Required(CONF_LOCK): switch.switch_schema(
           BunicutzAC_Switch
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parn = await cg.get_variable(config[CONF_BUNICUTZAC_ID])

    if aux_heat_config := config.get(CONF_AUX_HEAT):
        swt = await switch.new_switch(aux_heat_config)
        await cg.register_parented(swt, parn)
        cg.add(getattr(parn, f"set_{CONF_AUX_HEAT}")(swt))
    
    if echo_sleep_config := config.get(CONF_ECHO_SLEEP):
        swt = await switch.new_switch(echo_sleep_config)
        await cg.register_parented(swt, parn)
        cg.add(getattr(parn, f"set_{CONF_ECHO_SLEEP}")(swt))

    if vent_config := config.get(CONF_VENT):
        swt = await switch.new_switch(vent_config)
        await cg.register_parented(swt, parn)
        cg.add(getattr(parn, f"set_{CONF_VENT}")(swt))

    if swing_config := config.get(CONF_SWING):
        swt = await switch.new_switch(swing_config)
        await cg.register_parented(swt, parn)
        cg.add(getattr(parn, f"set_{CONF_SWING}")(swt))

    if lock_config := config.get(CONF_LOCK):
        swt = await switch.new_switch(lock_config)
        await cg.register_parented(swt, parn)
        cg.add(getattr(parn, f"set_{CONF_LOCK}")(swt))

