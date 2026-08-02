#include "convert_code.h"
#include <Arduino.h>
#include <math.h>

int convertCode(int* dedos[], int code){

  for(int i = 4; i >= 0; i--){
    if(i != 2 && i != 0){
      if(analogRead(dedos[i]) > 4000)){
        code += pow(10, 5-(i+1));
      }
    } else {
      if(analogRead(dedos[i]) > 3000){
        code += 2 * pow(10, 5-(i+1));
      }
    }

  }
  return code;
}
