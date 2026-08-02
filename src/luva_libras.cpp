#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "mpu6050.h"
#include "dados_sensores.h"

#define d0 14  // dedao
#define d1 27  // indicador
#define d2 26  // do meio
#define d3 25  // anelar
#define d4 33  // minimo

#define contato_d1d2 16

#define botaoBoot 17

Adafruit_MPU6050 mpu;

double rot_x = 0, rot_y = 0, rot_z = 0, filtered_rot_x, filtered_rot_y;
long unsigned tempo_atual = 0, letras_debounce = 0;

int libras_code = 0;
String letra = "a";
String palavra = "";

void setup() {
  Serial.begin(115200);

  while (!Serial) delay(10);

  if (!mpu.begin()) {
    Serial.println("Sensor nao detectado");
    while (1) {
      delay(10);
    }
  }
  Serial.println("Sensor detectado");

  statusMPU();
  
  Serial.println("");
  delay(100);


  pinMode(botaoBoot, INPUT_PULLUP);
  pinMode(contato_d1d2, INPUT_PULLUP);
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);

  letra = ' ';
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  rot_x += g.gyro.x+0.02603;
  rot_y += g.gyro.y-0.00485;
  rot_z += g.gyro.z+0.0061;

  long dt = millis() - tempo_atual;
  filtered_rot_x = double(0.98 * (rot_x + g.gyro.x * dt) + 0.02 * a.acceleration.x);
  filtered_rot_y = double(0.98 * (rot_y + g.gyro.y * dt) + 0.02 * a.acceleration.y);
                   
  libras_code = 0;
  letra = ' ';

  if(analogRead(d0) > 2500){
    libras_code += 10000;
  }
  if(analogRead(d1) > 2000){
    libras_code += 1000;
  }else if(analogRead(d1) > 1000){
    libras_code += 2000;
  }
  if(analogRead(d2) > 3000){
    libras_code += 100;
  }
  if(analogRead(d3) > 4000){
    libras_code += 10;
  }else if(analogRead(d3) > 3500){
    libras_code += 20;
  }
  if(analogRead(d4) > 2000){
    libras_code += 1;
  }else if(analogRead(d4) > 900){
    libras_code += 2;
  }

  if(millis()-letras_debounce > 1000){
    switch(libras_code){
      case 1111:
        letra = 'A';
        break;
      case 10000:
        letra = 'B';
        break;
      case 1112:
      case 2112:
        if((g.gyro.y > 5) || (g.gyro.y < -5)){
          letra = "C (cedillha)";
          letras_debounce = millis();
        }else{
          letra = 'C';
        }
        break;
      case 112:
        if(rot_y < -600){
          letra = 'Q';
        }else{
          letra = 'D';
        }
        break;
      case 11111:
        letra = 'E';
        break;
      case 2000:
      case 1000:
        letra = 'F';
        break;
      case 10112:
      case 10111:
        if(rot_x < -600){
          letra = 'Q';
        }else if((a.acceleration.x > 10) || (a.acceleration.x < 10 < -5) && (rot_x > -200)){
          letra = 'Z';
          letras_debounce = millis();
        }else{
          letra = 'G';
        }
        break;
      case 12:
        if((rot_x < -250)){
          letra = 'P';
        }else if((a.acceleration.y > -4) && (rot_x > -100)){
          letra = 'K';
          letras_debounce = millis();
        }else if((g.gyro.y < -5)){
          letra = 'H';
          letras_debounce = millis();
        }
        break;
      case 11110:
      case 12110:
        if(rot_x < -600){
          letra = 'J';
        }else{
          letra = 'I';
        }
        break;
      case 111:
        letra = 'L';
        break;  
      case 10001:
      case 10002:
        if(rot_x < -600){
          letra = 'M';
        }else{
          letra = 'W';
        }
        break;
      case 10011:
      case 10012:
        if(rot_x < -500){
          letra = 'N';
        }else{
          letra = 'R';
        }
        break;
      case 11112:
      case 12112:
        letra = 'O';
        break;
      case 11:
        if(digitalRead(contato_d1d2)){
          letra = 'U';
        }else{
          letra = 'V';
        }
        break;
      case 12000:
        letra = 'T';
        break;
      case 12111:
        if(rot_x < -300){
          letra = 'X';
        }
        break;
      case 1110:
        letra = 'Y';
        break;
      default:
        letra = ' ';
    }
  }
  
   if (dt > 500){
    Serial.println(libras_code);

    tempo_atual = millis();
 
    printAcceleration(a);
    printAngularAcceleration(g);
    printRotation(rot_x, rot_y, rot_z);

    if(rot_x > 300){
      Serial.println("Inclinado para frente.");
    }
    if(rot_y < -300){
      Serial.println("Rotacionado anti-horário");
    }
    if((g.gyro.y > 5) || (g.gyro.y < -3)){
      Serial.println("Girando");
    }

    int estado = digitalRead(botaoBoot);


    Serial.print("DEDAO: ");
    Serial.println(analogRead(d0));
    Serial.print("INDICADOR: ");
    Serial.println(analogRead(d1));
    Serial.print("DO MEIO: ");
    Serial.println(analogRead(d2));
    Serial.print("ANELAR: ");
    Serial.println(analogRead(d3));
    Serial.print("MINIMO: ");
    Serial.println(analogRead(d4));
    Serial.print("CONTATO: ");
    Serial.println(digitalRead(contato_d1d2));
    Serial.print("\nLETRA: ");
    Serial.println(letra);
    Serial.print("PALAVRA: ");
    Serial.println(palavra);

    if (estado == LOW) {
      if(letra == " "){
        if (palavra.length() > 0) {
          palavra.remove(palavra.length() - 1);
        }
      }else{
        palavra.concat(letra);
        switch(letra.charAt(0)){
          case 'A': 
          case 'B': 
          case 'C': 
          case 'D': 
          case 'E': 
          case 'F': 
          case 'G': 
          case 'I': 
          case 'O': 
          case 'R': 
          case 'S': 
          case 'T': 
          case 'U': 
          case 'V': 
          case 'W': 
          case 'Y': 
            rot_x = 0;
            rot_y = 0;
            rot_z = 0;
            break;
          default:
            break;
        }
      }
    }


    if (estado == LOW) {
      delay(1000);
      tempo_atual = millis();
    }
  }

}
