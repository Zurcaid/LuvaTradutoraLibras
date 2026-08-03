#include "dados_sensores.h"
#indlude <Arduino.h>

void printAcceleration(const sensors_event_t& a){

    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");
}

void printAngularAcceleration(const sensors_event_t& g){

    Serial.print("Angular acceleration X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");
}

void printRotation(double rot_x, double rot_y, double rot_z){

    Serial.print("Rotation X: ");
    Serial.print(rot_x);
    Serial.print(", Y: ");
    Serial.print(rot_y);
    Serial.print(", Z: ");
    Serial.print(rot_z);
    Serial.println(" rad");
}
