#include <stdint.h>
#include "Arduino.h"
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "MAX30102.h"

long lastBeat = 0;  //Time at which the last beat occurred
float beatsPerMinute;
float fingertemp;
bool fingersense = 0;

void INIT_VitalSensor(MAX30105 &VitalSensorF) {
  if (!VitalSensorF.begin(Wire, I2C_SPEED_STANDARD))  //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  VitalSensorF.setup();                     //Configure sensor with default settings
  VitalSensorF.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  VitalSensorF.setPulseAmplitudeGreen(0);   //Turn off Green LED
  VitalSensorF.enableDIETEMPRDY();
}

void VitalSensorLoop(uint16_t *VitalSensorArrayF, MAX30105 &VitalSensorF) {

  long irValue = VitalSensorF.getIR();

  if (checkForBeat(irValue) == true) {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
  }

  if (irValue > 10000)
    fingersense = 1;
  else
    fingersense = 0;
  fingertemp = VitalSensorF.readTemperature();
  VitalSensorArrayF[0] = (uint16_t)beatsPerMinute;
  VitalSensorArrayF[1] = fingertemp;
  VitalSensorArrayF[2] = fingersense;
}
