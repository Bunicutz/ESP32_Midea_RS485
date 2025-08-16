import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_EMPTY, ICON_EMPTY

Bunicutz_AC_ns = cg.esphome_ns.namespace("Bunicutz_AC")
BunicutzAC = Bunicutz_AC_ns.class_("BunicutzAC", cg.PollingComponent)

CONF_BUNICUTZAC_ID = "BunicutzAC"

AUTO_LOAD = ["sensor"]

CONF_Unknown1 = "Unknown1"
CONF_Capabilities = "Capabilities"
CONF_ACT1Temp = "ACT1Temp"
CONF_ACT2ATemp = "ACT2ATemp"
CONF_ACT2BTemp = "ACT2BTemp"
CONF_ACT3Temp = "ACT3Temp"
CONF_Current = "Current"
CONF_Unknown2 = "Unknown2"
CONF_Unknown3 = "Unknown3"
CONF_OperatingFlags = "OperatingFlags"
CONF_ErrorFlags = "ErrorFlags"
CONF_ProtectFlags = "ProtectFlags"
CONF_CCMComErrorFlags = "CCMComErrorFlags"
CONF_Unknown4 = "Unknown4"
CONF_Unknown5 = "Unknown5"
CONF_ACNotResponding = "ACNotResponding"

BUNICUTZAC_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_BUNICUTZAC_ID): cv.use_id(BunicutzAC),
    }
)


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(BunicutzAC),
            cv.Required(CONF_Unknown1): sensor.sensor_schema(
                unit_of_measurement="???",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Capabilities): sensor.sensor_schema(
                unit_of_measurement="bitfield",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ACT1Temp): sensor.sensor_schema(
                unit_of_measurement="°C",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ACT2ATemp): sensor.sensor_schema(
                unit_of_measurement="°C",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ACT2BTemp): sensor.sensor_schema(
                unit_of_measurement="°C",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ACT3Temp): sensor.sensor_schema(
                unit_of_measurement="°C",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Current): sensor.sensor_schema(
                unit_of_measurement="A",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Unknown2): sensor.sensor_schema(
                unit_of_measurement="???",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Unknown3): sensor.sensor_schema(
                unit_of_measurement="???",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_OperatingFlags): sensor.sensor_schema(
                unit_of_measurement="bitfield",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ErrorFlags): sensor.sensor_schema(
                unit_of_measurement="bitfield",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ProtectFlags): sensor.sensor_schema(
                unit_of_measurement="bitfield",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_CCMComErrorFlags): sensor.sensor_schema(
                unit_of_measurement="bitfield",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Unknown4): sensor.sensor_schema(
                unit_of_measurement="???",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_Unknown5): sensor.sensor_schema(
                unit_of_measurement="???",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
            cv.Required(CONF_ACNotResponding): sensor.sensor_schema(
                unit_of_measurement="bool",
                icon=ICON_EMPTY,
                accuracy_decimals=0,
            ).extend(),
        }
    )
    .extend(cv.polling_component_schema("30s"))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)


    if CONF_Unknown1 in config:
        sens = await sensor.new_sensor(config[CONF_Unknown1])
        cg.add(var.set_Unknown1(sens))
    if CONF_Capabilities in config:
        sens = await sensor.new_sensor(config[CONF_Capabilities])
        cg.add(var.set_Capabilities(sens))
    if CONF_ACT1Temp in config:
        sens = await sensor.new_sensor(config[CONF_ACT1Temp])
        cg.add(var.set_ACT1Temp(sens))
    if CONF_ACT2ATemp in config:
        sens = await sensor.new_sensor(config[CONF_ACT2ATemp])
        cg.add(var.set_ACT2ATemp(sens))
    if CONF_ACT2BTemp in config:
        sens = await sensor.new_sensor(config[CONF_ACT2BTemp])
        cg.add(var.set_ACT2BTemp(sens))
    if CONF_ACT3Temp in config:
        sens = await sensor.new_sensor(config[CONF_ACT3Temp])
        cg.add(var.set_ACT3Temp(sens))
    if CONF_Current in config:
        sens = await sensor.new_sensor(config[CONF_Current])
        cg.add(var.set_Current(sens))
    if CONF_Unknown2 in config:
        sens = await sensor.new_sensor(config[CONF_Unknown2])
        cg.add(var.set_Unknown2(sens))
    if CONF_Unknown3 in config:
        sens = await sensor.new_sensor(config[CONF_Unknown3])
        cg.add(var.set_Unknown3(sens))
    if CONF_OperatingFlags in config:
        sens = await sensor.new_sensor(config[CONF_OperatingFlags])
        cg.add(var.set_OperatingFlags(sens))
    if CONF_ErrorFlags in config:
        sens = await sensor.new_sensor(config[CONF_ErrorFlags])
        cg.add(var.set_ErrorFlags(sens))
    if CONF_ProtectFlags in config:
        sens = await sensor.new_sensor(config[CONF_ProtectFlags])
        cg.add(var.set_ProtectFlags(sens))
    if CONF_CCMComErrorFlags in config:
        sens = await sensor.new_sensor(config[CONF_CCMComErrorFlags])
        cg.add(var.set_CCMComErrorFlags(sens))
    if CONF_Unknown4 in config:
        sens = await sensor.new_sensor(config[CONF_Unknown4])
        cg.add(var.set_Unknown4(sens))
    if CONF_Unknown5 in config:
        sens = await sensor.new_sensor(config[CONF_Unknown5])
        cg.add(var.set_Unknown5(sens))
    if CONF_ACNotResponding in config:
        sens = await sensor.new_sensor(config[CONF_ACNotResponding])
        cg.add(var.set_ACNotResponding(sens))
