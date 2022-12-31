#include <stdint.h>
#include "DFRobotDFPlayerMini.h"
#include "LiquidCrystal.h"
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <MPU6050_light.h>
/*****************************/
#include "/MPU6050/MPU6050.h"
#include "/MAX30102/MAX30102.h"
#include "/DFPlayer/DFPlayer.h"
#include "/FlexRead/FlexRead.h"
/*********************************/
uint16_t VitalSensorArray[3] = { 0 };
/*
  [0] -> Heart Rate
  [1] -> Finger Temp
  [2] -> Finger Sense
*/
/********************************/
uint8_t MPU6050Array[3] = { 0 };
/*
 [0] -> Flipped towards = 0
 [0] -> Flipped backwards = 1
 [0] -> Flipped right = 2
 [0] -> Flipped left = 3
 [0] -> Right position = 4
 [1] -> Room temp
 [2] -> Motion detected = 1, else 0
*/
/**************************************/
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal lcd(29, 28, 27, 26, 25, 24, 23);
MAX30105 VitalSensor;
MPU6050 mpu6050(Wire);
/*************************************/
void setup() {
  Serial.begin(115200);
  lcd.begin(20, 4);
  lcd.home();
  INIT_DFPlayer(myDFPlayer);
  INIT_VitalSensor(VitalSensor);
  INIT_MPU6050(mpu6050);
  pinMode(22, INPUT_PULLUP);
}
uint8_t ChairOccuStat;
void loop() {
  ////// Functions
  FlexLoop(lcd, myDFPlayer);
  VitalSensorLoop(VitalSensorArray, VitalSensor);
  MPU6050Loop(MPU6050Array, mpu6050);
  ChairOccuStat = digitalRead(22);
  //////// Serial print all values to ESP
  String data = (String(!ChairOccuStat) + ", " + String(VitalSensorArray[0]) + ", " + String(VitalSensorArray[1]) + ", " + String(VitalSensorArray[2]) + ", " + String(MPU6050Array[0]) + ", " + String(MPU6050Array[1]) + ", " + String(MPU6050Array[2]));
  Serial.flush();
  Serial.print(data);
  Serial.print("\n");
  ///////// CLEARING ARRAYS
 /* memset(MPU6050Array, 0, sizeof(MPU6050Array));
  memset(VitalSensorArray, 0, sizeof(VitalSensorArray));*/
  yield();
}
