#ifndef MPU6050C_H
#define MPU6050C_H

class MPU6050;

void INIT_MPU6050(MPU6050 &mpu6050F);
void MPU6050Loop(uint8_t * MPU6050ArrayF, MPU6050 &mpu6050F);

#endif
