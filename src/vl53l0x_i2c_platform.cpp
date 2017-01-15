
#include "vl53l0x_i2c_platform.h"
#include "Wire.h"
#include "Arduino.h"

#define STATUS_OK   0
#define STATUS_FAIL 1

#ifdef __cplusplus
extern "C" {
#endif


int32_t VL53L0X_comms_initialise(uint16_t comms_speed_khz)
{
	Wire.begin();
	Wire.setClock(comms_speed_khz*1000);
	return STATUS_OK;
}

int32_t VL53L0X_comms_close(void)
{
	Wire.end();
	return STATUS_OK;
}

int32_t VL53L0X_write_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write(pdata, count);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	return STATUS_OK;
}

int32_t VL53L0X_write_byte(uint8_t address, uint8_t index, uint8_t data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write(data);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	return STATUS_OK;
}

int32_t VL53L0X_write_word(uint8_t address, uint8_t index, uint16_t data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write(data>>8 & 0xFF);
	Wire.write(data & 0xFF);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	return STATUS_OK;
}

int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write(data>>24 & 0xFF);
	Wire.write(data>>16 & 0xFF);
	Wire.write(data>>8 & 0xFF);
	Wire.write(data & 0xFF);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	return STATUS_OK;
}

int32_t VL53L0X_read_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	
	if(Wire.requestFrom(address, count)<count)
		return STATUS_FAIL;
	for(uint32_t i=0; i<count; ++i)
	{
		pdata[i]=Wire.read();
	}
	return STATUS_OK;
}

int32_t VL53L0X_read_byte(uint8_t address, uint8_t index, uint8_t *pdata)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	if(Wire.requestFrom(address, 1u)<1)
		return STATUS_FAIL;
	*pdata=Wire.read();
	return STATUS_OK;
}

int32_t VL53L0X_read_word(uint8_t address, uint8_t index, uint16_t *pdata)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	
	if(Wire.requestFrom(address, 2u)<2)
		return STATUS_FAIL;
	*pdata=((uint16_t)Wire.read())<<8;
	*pdata|=((uint16_t)Wire.read());
	return STATUS_OK;
}

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	if(Wire.endTransmission()!=0)
		return STATUS_FAIL;
	
	if(Wire.requestFrom(address, 4u)<4)
		return STATUS_FAIL;
	*pdata=((uint32_t)Wire.read())<<24;
	*pdata|=((uint32_t)Wire.read())<<16;
	*pdata|=((uint32_t)Wire.read())<<8;
	*pdata|=((uint32_t)Wire.read());
	return STATUS_OK;
}

#ifdef __cplusplus
}
#endif


