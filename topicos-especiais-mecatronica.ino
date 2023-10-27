#include <Arduino.h>

// Definindo os pinos para os LEDs dos semáforos
const int red_led1 = 2;
const int yellow_led1 = 3;
const int green_led1 = 4;

const int red_led2 = 5;
const int yellow_led2 = 6;
const int green_led2 = 7;

// Definindo os sensores
// Supondo que os sensores de peso e fotoelétricos retornem valores digitais
const int pedestrian_sensor = 8;
const int vehicle_sensor = 9;

void setup() {
  // Inicializar os LEDs como saídas
  pinMode(red_led1, OUTPUT);
  pinMode(yellow_led1, OUTPUT);
  pinMode(green_led1, OUTPUT);
  
  pinMode(red_led2, OUTPUT);
  pinMode(yellow_led2, OUTPUT);
  pinMode(green_led2, OUTPUT);
  
  // Inicializar os sensores como entradas
  pinMode(pedestrian_sensor, INPUT);
  pinMode(vehicle_sensor, INPUT);
  
  // Inicializar a porta serial para depuração
  Serial.begin(9600);
}

void mode1() {
  Serial.println("Modo 1 Ativado");
  digitalWrite(red_led1, HIGH);
  digitalWrite(red_led2, LOW);
  delay(5000);
  
  digitalWrite(yellow_led1, HIGH);
  delay(2000);
  
  digitalWrite(red_led1, LOW);
  digitalWrite(yellow_led1, LOW);
  digitalWrite(green_led1, HIGH);
  delay(5000);
  
  digitalWrite(green_led1, LOW);
  digitalWrite(red_led2, HIGH);
  delay(5000);
  
  digitalWrite(yellow_led2, HIGH);
  delay(2000);
  
  digitalWrite(red_led2, LOW);
  digitalWrite(yellow_led2, LOW);
  digitalWrite(green_led2, HIGH);
  delay(5000);
  
  digitalWrite(green_led2, LOW);
}

void mode2() {
  Serial.println("Modo 2 Ativado");
  // Código para dar prioridade aos pedestres
}

void mode3() {
  Serial.println("Modo 3 Ativado");
  // Código para dar prioridade ao tráfego de veículos
}

void loop() {
  int pedestrian_count = digitalRead(pedestrian_sensor);
  int vehicle_count = digitalRead(vehicle_sensor);
  
  if(pedestrian_count > 10) {  // Supondo que 10 seja o limite
    mode2();
  } else if(vehicle_count > 10) {  // Supondo que 10 seja o limite
    mode3();
  } else {
    mode1();
  }
  
  delay(1000);  // Aguardar 1 segundo antes de fazer a próxima leitura
}
