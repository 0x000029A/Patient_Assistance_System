#include <stdint.h>
#include "Arduino.h"
#include "MPU6050.h"
#include "Wire.h"
#include <MPU6050_light.h>

float RoomTemp;
const uint8_t RollThres = 30;
const uint8_t PitchThres = 30;

void INIT_MPU6050(MPU6050 &mpu6050F) {
  Wire.begin();  
  byte status = mpu6050F.begin();
  while (status != 0) {
    //Serial.println("MPU Sensor did not begin");
  }
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu6050F.calcOffsets();
  mpu6050F.MotionDetectionEnable();
}

void MPU6050Loop(uint8_t * MPU6050ArrayF, MPU6050 &mpu6050F) {
  mpu6050F.update();
  if (mpu6050F.getAccAngleX() > PitchThres)
    MPU6050ArrayF[0] = 0; //towards
  else if (mpu6050F.getAccAngleX() < -PitchThres)
    MPU6050ArrayF[0] = 1; // back
  else if (mpu6050F.getAccAngleY() > RollThres)
    MPU6050ArrayF[0] = 2; // left
  else if (mpu6050F.getAccAngleY() < -PitchThres)
    MPU6050ArrayF[0] = 3; //right
  else
    MPU6050ArrayF[0] = 4; //right position
  MPU6050ArrayF[1] = mpu6050F.getTemp();
  if (mpu6050F.MotionDetectionFlag())
    MPU6050ArrayF[2] = 1;
  else
   MPU6050ArrayF[2] = 0;
  delay(50);
}
