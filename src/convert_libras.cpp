#include "convert_libras.h"


String convert_libras(int code, sensors_event_t g, sensors_event_t a, int state_d12){
  String letra = "";
  switch(code){
    case 1111:
      letra = "A";
      break;
    case 10000:
      letra = "B";
      break;
    case 1112:
      if((g.gyro.x > 5) || (g.gyro.x < -5)){
        letra = "C (cedilha)";
      }else{
        letra = "C";
      }
      break;
    case 112:
      if(rot_y < -600){
        letra = "Q";
      }else{
        letra = "D";
      }
      break;
    case 11111:
      letra = "E";
      break;
    case 1000:
      letra = "F";
      break;
    case 10112:
    case 10111:
      if(rot_y < -600){
        letra = "Q";
      }else if((a.acceleration.y < -4) || (a.acceleration.y > 4)){
        letra = "Z";
      }else{
        letra = "G";
      }
      break;
    case 12:
      if((rot_y < -300) && (rot_x > 300)){
        letra = "P";
      }else if(a.acceleration.x < 8){
        letra = "K";
      }else{
        letra = "H";
      }
      break;
    case 11110:
      if(rot_x > 400){
        letra = "J";
      }else{
        letra = "I";
      }
      break;
    case 111:
      letra = "L";
      break;
    case 10001:
    case 10002:
      if(rot_y < -600){
        letra = "M";
      }else{
        letra = "W";
      }
      break;
    case 10011:
    case 10012:
      if(rot_y < -500){
        letra = "N";
      }else{
        letra = "R";
      }
      break;
    case 11112:
      letra = "O";
      break;
    case 11:
      if(state_d12){
        letra = "U";
      }else{
        letra = "V";
      }
      break;
    case 1110:
      letra = "Y";
      break;
    default:
      letra = "";
  }

  return letra;
}
