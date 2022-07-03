/*
    ESP32 library to control/monitor Midea air conditioner via XYE (RS485) bus
*/

#pragma once

#ifndef _esp32_midea_rs485_h
    #define _esp32_midea_rs485_h
   
    //Master command structure
    #define ESP32_MIDEA_RS485_PREAMBLE      0XAA
    #define ESP32_MIDEA_RS485_PROLOGUE      0X55
    #define ESP32_MIDEA_RS485_MASTER_COMMAND_QERRY  0xC0
    #define ESP32_MIDEA_RS485_MASTER_COMMAND_SET    0xC3
    #define ESP32_MIDEA_RS485_MASTER_COMMAND_LOCK   0xCC
    #define ESP32_MIDEA_RS485_MASTER_COMMAND_UNLOCK 0xCD
    #define ESP32_MIDEA_RS485_FROM_MASTER           0x80
    
    #define ESP32_MIDEA_RS485_OP_MODE_OFF          0x00
    #define ESP32_MIDEA_RS485_OP_MODE_AUTO         0x80
    #define ESP32_MIDEA_RS485_OP_MODE_FAN          0x81
    #define ESP32_MIDEA_RS485_OP_MODE_DRY          0x82
    #define ESP32_MIDEA_RS485_OP_MODE_HEAT         0x84
    #define ESP32_MIDEA_RS485_OP_MODE_COOL         0x88
    
    #define ESP32_MIDEA_RS485_FAN_MODE_AUTO        0x80
    #define ESP32_MIDEA_RS485_FAN_MODE_HIGH        0x01
    #define ESP32_MIDEA_RS485_FAN_MODE_MEDIUM      0x02
    #define ESP32_MIDEA_RS485_FAN_MODE_LOW         0x03
    
    #define ESP32_MIDEA_RS485_TEMP_SET_FAN_MODE    0xFF
    
    #define ESP32_MIDEA_RS485_MODE_FLAG_AUX_HEAT   0x02
    #define ESP32_MIDEA_RS485_MODE_FLAG_NORM       0x00
    #define ESP32_MIDEA_RS485_MODE_FLAG_ECO        0x01
    #define ESP32_MIDEA_RS485_MODE_FLAG_SWING      0x04
    #define ESP32_MIDEA_RS485_MODE_FLAG_VENT       0x88
    
    #define ESP32_MIDEA_RS485_TIMER_15MIN          0x01
    #define ESP32_MIDEA_RS485_TIMER_30MIN          0x02
    #define ESP32_MIDEA_RS485_TIMER_1HOUR          0x04
    #define ESP32_MIDEA_RS485_TIMER_2HOUR          0x08
    #define ESP32_MIDEA_RS485_TIMER_4HOUR          0x10
    #define ESP32_MIDEA_RS485_TIMER_8HOUR          0x20
    #define ESP32_MIDEA_RS485_TIMER_16HOUR         0x40
    #define ESP32_MIDEA_RS485_TIMER_INVALID        0x80
    
    #define ESP32_MIDEA_RS485_COMMAND_UNKNOWN      0x00  
    
    //Slave Response
    
    #define ESP32_MIDEA_RS485_SLAVE_COMMAND_QERRY  0xC0
    #define ESP32_MIDEA_RS485_SLAVE_COMMAND_SET    0xC3
    #define ESP32_MIDEA_RS485_SLAVE_COMMAND_LOCK   0xCC
    #define ESP32_MIDEA_RS485_SLAVE_COMMAND_UNLOCK 0xCD
    
    #define ESP32_MIDEA_RS485_TO_MASTER            0x80
    
    #define ESP32_MIDEA_RS485_RESPONSE_UNKNOWN     0x30  
    
    #define ESP32_MIDEA_RS485_CAPABILITIES_EXT_TEMP 0x80  
    #define ESP32_MIDEA_RS485_CAPABILITIES_SWING    0x10
    
    #define ESP32_MIDEA_RS485_RESPONSE_UNKNOWN1    0xFF  
    #define ESP32_MIDEA_RS485_RESPONSE_UNKNOWN2    0x01  
    
    #define ESP32_MIDEA_RS485_OP_FLAG_WATER_PUMP   0x04  
    #define ESP32_MIDEA_RS485_OP_FLAG_WATER_LOCK   0x80  
    
    #define ESP32_MIDEA_RS485_RESPONSE_UNKNOWN3    0x00  


    #ifdef __cplusplus
    extern "C" {
    #endif

    void esp32_midea_rs485_Init(Serial SerialPort, uint8_t ro_pin, uint8_t di_pin, uint8_t re_de_pin, );
    uint8_t esp32_midea_rs485_SetMode(uint8_t mode);
    uint8_t esp32_midea_rs485_SetTemp(uint8_t temp);
    void esp32_midea_rs485_Cyclic();
    uint8_t esp32_midea_rs485_GetMode(uint8_t *mode);
    uint8_t esp32_midea_rs485_GetTemp(uint8_t *temp);

    #ifdef __cplusplus
    } // extern C
    #endif
#endif