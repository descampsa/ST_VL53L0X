#ifndef _VL53L0X_I2C_PLATFORM_H_
#define _VL53L0X_I2C_PLATFORM_H_

#include "vl53l0x_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t VL53L0X_comms_initialise(uint16_t comms_speed_khz);
int32_t VL53L0X_comms_close(void);

int32_t VL53L0X_write_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count);
int32_t VL53L0X_read_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count);
int32_t VL53L0X_write_byte(uint8_t address, uint8_t index, uint8_t data);
int32_t VL53L0X_write_word(uint8_t address, uint8_t index, uint16_t data);
int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t data);
int32_t VL53L0X_read_byte(uint8_t address, uint8_t index, uint8_t *pdata);
int32_t VL53L0X_read_word(uint8_t address, uint8_t index, uint16_t *pdata);
int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata);

#ifdef __cplusplus
}
#endif

#endif //_VL53L0X_I2C_PLATFORM_H_

