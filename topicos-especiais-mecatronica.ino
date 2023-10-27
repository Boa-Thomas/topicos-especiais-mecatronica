#include <Arduino.h>

// Definindo os pinos para os LEDs dos semáforos
const int red_led1 = 2;
const int yellow_led1 = 3;
const int green_led1 = 4;

const int red_led2 = 5;
const int yellow_led2 = 6;
const int green_led2 = 7;

// Definindo os sensores para pedestres
const int pedestrian_sensor1 = 8;
const int pedestrian_sensor2 = 9;

// Definindo sensores de fluxo para veículos (próximos e afastados)
const int vehicle_sensor1_near = 10;
const int vehicle_sensor1_far = 11;
const int vehicle_sensor2_near = 12;
const int vehicle_sensor2_far = 13;

void setup() {
  // Inicializar os LEDs como saídas
  pinMode(red_led1, OUTPUT);
  pinMode(yellow_led1, OUTPUT);
  pinMode(green_led1, OUTPUT);

  pinMode(red_led2, OUTPUT);
  pinMode(yellow_led2, OUTPUT);
  pinMode(green_led2, OUTPUT);

  // Inicializar os sensores como entradas
  pinMode(pedestrian_sensor1, INPUT);
  pinMode(pedestrian_sensor2, INPUT);

  pinMode(vehicle_sensor1_near, INPUT);
  pinMode(vehicle_sensor1_far, INPUT);
  pinMode(vehicle_sensor2_near, INPUT);
  pinMode(vehicle_sensor2_far, INPUT);

  // Inicializar a porta serial para depuração
  Serial.begin(9600);
}

void mode1() {
  semaforo(red, 1);
  delay(5000);
  semaforo(yellow, 1);
  delay(2000);
  semaforo(green, 1);
  delay(15000);
}

void mode2() {
  // Código para Modo 2 (Prioridade para pedestres)
  // Implemente a lógica aqui
}

void mode3() {
  // Código para Modo 3 (Prioridade para tráfego de veículos)
  // Implemente a lógica aqui
}

void semaforo(String color, int semaforo_id) {
  int redPin, yellowPin, greenPin;
  
  // Definir os pinos com base no ID do semáforo
  if (semaforo_id == 1) {
    redPin = red_led1;
    yellowPin = yellow_led1;
    greenPin = green_led1;
  } else if (semaforo_id == 2) {
    redPin = red_led2;
    yellowPin = yellow_led2;
    greenPin = green_led2;
  } else {
    Serial.println("ID de semáforo inválido.");
    return;
  }
  
  // Desativar todos os LEDs primeiro
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);

  // Ativar o LED de acordo com a cor especificada
  if (color == "red") {
    digitalWrite(redPin, HIGH);
  } else if (color == "yellow") {
    digitalWrite(yellowPin, HIGH);
  } else if (color == "green") {
    digitalWrite(greenPin, HIGH);
  } else {
    Serial.println("Cor inválida.");
  }
}

void loop() {
  int pedestrian_count1 = digitalRead(pedestrian_sensor1);
  int pedestrian_count2 = digitalRead(pedestrian_sensor2);

  int vehicle_count1_near = digitalRead(vehicle_sensor1_near);
  int vehicle_count1_far = digitalRead(vehicle_sensor1_far);
  int vehicle_count2_near = digitalRead(vehicle_sensor2_near);
  int vehicle_count2_far = digitalRead(vehicle_sensor2_far);

  // Suponha que 10 seja um limite para ativar modos especiais
  if (pedestrian_count1 > 10 || pedestrian_count2 > 10) {
    mode2();
  } else if (vehicle_count1_near > 10 || vehicle_count1_far > 10 || vehicle_count2_near > 10 || vehicle_count2_far > 10) {
    mode3();
  } else {
    mode1();
  }

  delay(1000);  // Aguardar 1 segundo antes de fazer a próxima leitura
}
