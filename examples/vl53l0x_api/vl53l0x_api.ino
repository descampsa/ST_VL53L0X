
#include "vl53l0x_api.h"

void print_error(VL53L0X_Error Status)
{
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buf);
    Serial.print("API Status: ");
    Serial.print(Status);
    Serial.print(" : ");
    Serial.print(buf);
    Serial.print("\n");
}

void print_version(VL53L0X_Version_t *version)
{
  Serial.print(version->major);
  Serial.print(".");
  Serial.print(version->minor);
  Serial.print(".");
  Serial.print(version->build);
  Serial.print(".");
  Serial.print(version->revision);
  Serial.print("\n");
}

void print_device_info(VL53L0X_DeviceInfo_t *info)
{
   Serial.print("VL53L0X_GetDeviceInfo:\n");
   Serial.print("Device Name : ");
   Serial.print(info->Name);
   Serial.print("\n");
   Serial.print("Device Type : ");
   Serial.print(info->Type);
   Serial.print("\n");
   Serial.print("Device ID : ");
   Serial.print(info->ProductId);
   Serial.print("\n");
   Serial.print("ProductRevisionMajor : ");
   Serial.print(info->ProductRevisionMajor);
   Serial.print("\n");
   Serial.print("ProductRevisionMinor : ");
   Serial.print(info->ProductRevisionMinor);
   Serial.print("\n");
}

const int i2c_speed_khz=400;
VL53L0X_Dev_t device;
VL53L0X_Error error;
VL53L0X_RangingMeasurementData_t RangingMeasurementData;

void setup() {
  Serial.begin(115200);

  //VL53L0X_trace_config(TRACE_MODULE_ALL, TRACE_LEVEL_ALL, TRACE_FUNCTION_ALL);

  Serial.print(F("Checking API version ...\n"));
  VL53L0X_Version_t version;
  
  VL53L0X_GetVersion(&version);
  Serial.print(F("Implementation version : "));
  print_version(&version);

  VL53L0X_GetPalSpecVersion(&version);
  Serial.print(F("Specification version : "));
  print_version(&version);
  Serial.print("\n");


  Serial.print(F("Initiating communication ...\n"));

  device.I2cDevAddr      = 0x29;
  device.comms_speed_khz =  i2c_speed_khz;

  VL53L0X_comms_initialise(i2c_speed_khz);

  Serial.print(F("DataInit ...\n"));
  error=VL53L0X_DataInit(&device);
  print_error(error);
  Serial.print("\n");

  Serial.print(F("GetDeviceInfo ...\n"));
  VL53L0X_DeviceInfo_t device_info;
  error=VL53L0X_GetDeviceInfo(&device, &device_info);
  print_error(error);
  Serial.print("\n");

  print_device_info(&device_info);
  Serial.print("\n");
  
  //Serial.print("Initiating device ...\n");
  Serial.print(F("StaticInit ...\n"));
  error=VL53L0X_StaticInit(&device);
  print_error(error);
  Serial.print("\n");

  uint8_t VhvSettings;
  uint8_t PhaseCal;
  Serial.print(F("PerformRefCalibration ...\n"));
  error=VL53L0X_PerformRefCalibration(&device, &VhvSettings, &PhaseCal);
  print_error(error);
  Serial.print("\n");

  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  Serial.print(F("PerformRefSpadManagement ...\n"));
  error=VL53L0X_PerformRefSpadManagement(&device, &refSpadCount, &isApertureSpads);
  print_error(error);
  Serial.print("\n");

 /* Serial.print(F("SetDeviceMode ...\n"));
  VL53L0X_SetDeviceMode(&device, VL53L0X_DEVICEMODE_SINGLE_RANGING); 
  print_error(error);
  Serial.print("\n");

  VL53L0X_RangingMeasurementData_t RangingMeasurementData;
  Serial.print(F("PerformSingleRangingMeasurement ...\n"));
  error=VL53L0X_PerformSingleRangingMeasurement(&device, &RangingMeasurementData);
  print_error(error);
  Serial.print("\n");

  Serial.print(F("Range measured : "));
  Serial.print(RangingMeasurementData.RangeMilliMeter);
  Serial.print(F(" mm\n"));*/

  Serial.print(F("SetDeviceMode ...\n"));
  VL53L0X_SetDeviceMode(&device, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); 
  print_error(error);
  Serial.print("\n");

  Serial.print(F("StartMeasurement ...\n"));
  error=VL53L0X_StartMeasurement(&device);
  print_error(error);
  Serial.print("\n");
  
}

void loop() {

  uint8_t data_ready=0;
  while(!data_ready){
    error=VL53L0X_GetMeasurementDataReady(&device, &data_ready);
    if(error!=VL53L0X_ERROR_NONE)
      print_error(error);
    VL53L0X_PollingDelay(&device);
  }

  error=VL53L0X_GetRangingMeasurementData(&device, &RangingMeasurementData);
  if(error!=VL53L0X_ERROR_NONE)
    print_error(error);
  
  Serial.print(F("Range measured : "));
  Serial.print(RangingMeasurementData.RangeMilliMeter);
  Serial.print(F(" mm\n"));
}

