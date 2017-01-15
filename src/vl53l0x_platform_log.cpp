#include "vl53l0x_platform_log.h"
#include "Arduino.h"


#define trace_print(level, ...) trace_print_module_function(TRACE_MODULE_PLATFORM, level, TRACE_FUNCTION_NONE, ##__VA_ARGS__)
#define trace_i2c(...) trace_print_module_function(TRACE_MODULE_NONE, TRACE_LEVEL_NONE, TRACE_FUNCTION_I2C, ##__VA_ARGS__)

#define VL53L0X_MAX_STRING_LENGTH_PLT 256


#ifdef __cplusplus
extern "C" {
#endif

char  debug_string[VL53L0X_MAX_STRING_LENGTH_PLT];

char * _trace_filename = NULL;
FILE *_tracefile = NULL;

uint32_t _trace_level = TRACE_LEVEL_WARNING;
uint32_t _trace_modules = TRACE_MODULE_NONE;
uint32_t _trace_functions = TRACE_FUNCTION_NONE;

unsigned long millis_c()
{
	return millis();
}

int32_t VL53L0X_trace_config(uint32_t modules, uint32_t level, uint32_t functions)
{
	_trace_functions = functions;
	_trace_level = level;
	_trace_modules = modules;
	return 0;
}

void trace_print_module_function(uint32_t module, uint32_t level, uint32_t function, const char *format, ...)
{
	if( ((level <=_trace_level) && ((module & _trace_modules) > 0))
		|| ((function & _trace_functions) > 0) )
	{
		va_list arg_list;
		char message[VL53L0X_MAX_STRING_LENGTH_PLT];

		va_start(arg_list, format);
		sprintf(message, VL53L0X_MAX_STRING_LENGTH_PLT, format, arg_list);
		va_end(arg_list);

		Serial.print(message);
	}
}

#ifdef __cplusplus
}
#endif

