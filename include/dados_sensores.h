#ifndef DADOS_SENSORES_H
#define DADOS_SENSORES_H

#include <Adafruit_Sensor.h>

void printAcceleration(const sensors_event_t& a);
void printAngularAcceleration(const sensors_event_t& g);
void printRotation(double rot_x, double rot_y, double rot_z);

#endif
