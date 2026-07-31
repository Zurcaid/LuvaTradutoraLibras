#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define d0 14  // dedao
#define d1 27  // indicador
#define d2 26  // do meio
#define d3 25  // anelar
#define d4 33  // minimo

#define contato_d1d2 16

#define botaoBoot 17

Adafruit_MPU6050 mpu;

double rot_x = 0, rot_y = 0, rot_z = 0, filtered_rot_x, filtered_rot_y;
long unsigned tempo_atual = 0;

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



  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Range do acelerometro definido: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Range do giroscopio definido: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filtro de frequencia definido: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;

    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;

    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;

    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;

    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;

    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;

    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }
  Serial.println("");
  delay(100);


  pinMode(botaoBoot, INPUT_PULLUP);
  pinMode(contato_d1d2, INPUT_PULLUP);
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  rot_x += g.gyro.x+0.02603;
  rot_y += g.gyro.y-0.00485;
  rot_z += g.gyro.z+0.0061;

  long dt = millis() - tempo_atual;
  filtered_rot_x = double(0.98 * (rot_x + gyro.x * dt) + 0.02 * acceleration.x);
  filtered_rot_y = double(0.98 * (rot_y + gyro.y * dt) + 0.02 * acceleration.y);
                   
  libras_code = 0;
  letra = ' ';

  if(analogRead(d0) > 2500){
    libras_code += 10000;
  }
  if(analogRead(d1) > 4000){
    libras_code += 1000;
  }else if(analogRead(d1) > 3000){
    libras_code += 2000;
  }
  if(analogRead(d2) > 3000){
    libras_code += 100;
  }
  if(analogRead(d3) > 4000){
    libras_code += 10;
  }else if(analogRead(d3) > 3000){
    libras_code += 20;
  }
  if(analogRead(d4) > 4000){
    libras_code += 1;
  }else if(analogRead(d4) > 3500){
    libras_code += 2;
  }

  switch(libras_code){
    case 1111:
      letra = 'A';
      break;
    case 10000:
      letra = 'B';
      break;
    case 1112:
      if((g.gyro.x > 5) || (g.gyro.x < -5)){
        letra = "C (cedillha)";
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
    case 1000:
      letra = 'F';
      break;
    case 10112:
    case 10111:
      if(rot_y < -600){
        letra = 'Q';
      }else if((a.acceleration.y < -4) || (a.acceleration.y > 4)){
        letra = 'Z';
      }
      else{
        letra = 'G';
      }
      break;
    case 12:
      if((rot_y < -300) && (rot_x > 300)){
        letra = 'P';
      }else if(a.acceleration.x < 8){
        letra = 'K';
      }else{
        letra = 'H';
      }
      break;
    case 11110:
      if(rot_x > 400){
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
      if(rot_y < -600){
        letra = 'M';
      }else{
        letra = 'W';
      }
      break;
    case 10011:
    case 10012:
      if(rot_y < -500){
        letra = 'N';
      }else{
        letra = 'R';
      }
      break;
    case 11112:
      letra = 'O';
      break;
    case 11:
      if(digitalRead(contato_d1d2)){
        letra = 'U';
      }else{
        letra = 'V';
      }
      break;
    case 1110:
      letra = 'Y';
      break;
    default:
      letra = ' ';
  }
   if (dt > 500){
    Serial.println(libras_code);

    tempo_atual = millis();

    Serial.print("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

     Serial.print("Angular acceleration X: ");
    Serial.print(g.gyro.x);
    Serial.print(", Y: ");
    Serial.print(g.gyro.y);
    Serial.print(", Z: ");
    Serial.print(g.gyro.z);
    Serial.println(" rad/s");

    Serial.print("Rotation X: ");
    Serial.print(rot_x);
    Serial.print(", Y: ");
    Serial.print(rot_y);
    Serial.print(", Z: ");
    Serial.print(rot_z);
    Serial.println(" rad");

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
