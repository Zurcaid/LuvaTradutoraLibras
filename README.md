# Luva Tradutora de Libras

Sistema embarcado desenvolvido para reconhecer configurações de mão da Língua Brasileira de Sinais (Libras) e convertê-las em caracteres do alfabeto comum.

O projeto utiliza sensores ópticos para detectar a flexão dos dedos e uma unidade de medição inercial para determinar a orientação da mão, permitindo o reconhecimento de letras do alfabeto manual da Libras.

---

## Funcionamento

A luva utiliza sensores ópticos de flexão baseados na variação da intensidade luminosa entre um LED e um LDR posicionados em cada dedo.

Quando ocorre a flexão dos dedos, a quantidade de luz recebida pelo LDR é alterada, modificando sua resistência elétrica. Essas variações são utilizadas para determinar a posição dos dedos.

A orientação da mão é obtida através do sensor inercial MPU6050, que combina acelerômetro e giroscópio para estimar a posição e movimentação da mão.

## Arquitetura

O sistema é dividido nos seguintes módulos:

- **Sensores de flexão:** responsáveis pela aquisição da posição dos dedos.
- **MPU6050:** responsável pela medição da orientação da mão.
- **ESP32:** realiza a leitura dos sensores e o processamento dos dados.
- **Algoritmo de classificação:** determina a letra correspondente ao sinal realizado.
- **Display OLED:** exibe a letra reconhecida pelo sistema.

## Hardware

| Componente | Função |
|------------|--------|
| Sensores ópticos (LED + LDR) | Detecção da flexão dos dedos |
| MPU6050 | Determinação da orientação da mão |
| Microcontrolador | Processamento dos dados dos sensores |
| Display OLED | Exibição da letra reconhecida |

## Software

- Linguagem: C/C++
- Plataforma: Arduino IDE / PlatformIO
- Bibliotecas:
  - Adafruit MPU6050
  - Adafruit Unified Sensor
  - Wire.h (built-in Arduino library)

A biblioteca **Adafruit MPU6050** foi modificada para atender aos requisitos específicos deste projeto. A versão modificada está incluída neste repositório.
