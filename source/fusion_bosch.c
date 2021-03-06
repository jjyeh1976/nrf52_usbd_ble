#include "BsxFusionLibrary.h"
#include "BsxLibraryCalibConstants.h"
#include "BsxLibraryConstants.h"
#include "BsxLibraryDataTypes.h"
#include "BsxLibraryErrorConstants.h"
#include "bmi160.h"

#define str_accsensorspec "37,0,3,1,0,9,12,150,0,16,60,0,1,0,1,0,176,4,82,3,0,0,64,65,1,1,1,1,2,2,2,3,3,1,1,180,115"
#define str_gyrosensorspec "14,0,1,1,3,9,12,136,19,16,1,1,129,46"
#define str_config "116,6,1,1,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,51,179,62,205,204,12,63,205,204,12,63,51,51,51,63,51,51,51,63,205,204,76,63,1,0,9,4,2,23,183,209,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,183,209,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,183,209,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,189,55,134,53,189,55,134,53,189,55,134,53,0,0,0,0,0,0,16,66,232,3,5,0,45,0,132,3,176,4,150,0,8,150,0,13,1,1,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,51,179,62,205,204,12,63,205,204,12,63,51,51,51,63,51,51,51,63,205,204,76,62,1,6,4,1,0,5,0,65,1,64,1,36,0,120,0,4,1,20,20,2,2,0,4,0,0,128,63,205,204,204,61,154,153,153,63,205,204,204,62,205,204,204,61,1,0,20,0,16,4,120,0,8,0,0,5,154,153,25,63,154,153,25,63,80,0,9,0,30,0,232,3,80,0,65,0,4,0,4,0,0,128,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,181,254,22,55,181,254,22,55,181,254,22,55,139,222,169,56,0,0,224,64,13,1,1,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,205,204,204,61,1,9,9,3,19,50,163,4,205,12,100,40,4,13,0,1,154,153,153,62,154,153,153,62,205,204,204,62,154,153,25,63,154,153,153,62,0,0,128,62,154,153,153,62,236,81,184,62,205,204,76,63,205,204,76,63,205,204,76,63,205,204,76,63,205,204,76,62,205,204,76,62,205,204,76,62,205,204,76,62,0,194,184,178,62,53,250,142,60,10,0,10,0,0,2,0,10,0,80,119,86,61,13,0,0,128,62,143,194,245,60,10,215,163,60,100,128,52,45,70,1,10,0,80,0,0,0,192,63,0,0,0,64,9,2,0,0,200,65,0,0,128,66,0,0,128,65,0,0,192,63,205,204,76,61,194,184,178,61,50,37,59,24,71,0,0,160,64,154,153,25,63,80,119,86,61,0,1,205,204,76,63,0,0,96,64,0,0,32,64,205,204,204,61,4,143,194,245,60,2,1,2,3,4,1,10,176,4,88,2,10,215,35,60,10,0,10,0,0,0,250,67,0,0,122,68,0,0,160,63,0,0,72,66,0,0,128,63,0,0,128,62,205,204,204,61,0,0,32,66,0,0,128,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,62,0,36,116,73,0,0,0,0,0,0,0,0,0,0,0,0,0,36,116,73,0,0,0,0,0,0,0,0,0,0,0,0,0,36,116,73,0,0,192,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,64,10,215,35,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,215,35,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,215,35,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,183,209,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,183,209,56,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23,183,209,56,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,172,197,39,55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,172,197,39,55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,172,197,39,55,0,36,116,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,116,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,116,73,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,4,3,0,0,0,0,0,0,10,3,4,25,64,18,24,0,64,114,8,0,13,226,109"

static struct bmi160_dev* bmi;

void fusion_poll(struct bmi160_dev* dev)
{
  libraryinput_t input;
  struct bmi160_sensor_data accel,gyro;
  bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL | BMI160_TIME_SEL), &accel, &gyro, dev);
  input.acc.data.x = accel.x;
  input.acc.data.y = accel.y;
  input.acc.data.z = accel.z;
  input.acc.time_stamp = accel.sensortime;
  input.gyro.data.x = gyro.x;
  input.gyro.data.y = gyro.y;
  input.gyro.data.z = gyro.z;
  input.gyro.time_stamp = gyro.sensortime;
  
  bsx_dostep(&input);
  
  ts_dataeulerf32 orient;
  bsx_get_orientdata_euler_rad(&orient);
  
}

void fusion_init(void)
{
  initParam_t s_input;
  BSX_S8 init_status;
  
  s_input.accelspec = str_accsensorspec;
  s_input.gyrospec = str_gyrosensorspec;
  
  s_input.usecase = str_config;
  
  init_status = bsx_init(&s_input);
  
  if(init_status != BSX_STATE_OK){
    
  }
  
  ts_workingModes workingMode;
  ts_HWsensorSwitchList HWsensorSwitchList;
  workingMode.opMode = BSX_WORKINGMODE_NDOF_GEORV_FMC_OFF;
  
  init_status = bsx_set_workingmode(&workingMode);
  bsx_get_hwdependency (workingMode,&HWsensorSwitchList);
  
  
  
}