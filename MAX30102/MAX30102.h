#ifndef MAX30102_H
#define MAX30102_H

class MAX30105;

void INIT_VitalSensor(MAX30105 &VitalSensorF);
void VitalSensorLoop(uint16_t * VitalSensorArrayF, MAX30105 &VitalSensorF);

#endif
