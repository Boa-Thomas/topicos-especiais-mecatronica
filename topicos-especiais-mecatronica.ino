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
// Modo de operação padrão
void mode1() {
  semaforo(red, 1);
  delay(5000);
  semaforo(yellow, 1);
  delay(2000);
  semaforo(green, 1);
  delay(15000);
}

void mode21() {
  // Código para Modo 21 (Prioridade para pedestres no semaforo 1)
  int tempo_1 = 15000;
  int tempo_2 = 3000;
  int tempo_3 = 5000;
  
    semaforo(red, 1);
    semaforo(green, 2);
    delay(tempo_1);
    semaforo(yellow, 1);
    semaforo(yellow,2);
    delay(tempo_2);
    semaforo(green, 1);
    semaforo(red, 2);
    delay(tempo_3);
  // Implemente a lógica aqui
}

void mode22() {
  // Código para Modo 22 (Prioridade para pedestres no semaforo 2)
  // Implemente a lógica aqui
  int tempo_1 = 15000;
  int tempo_2 = 3000;
  int tempo_3 = 5000;
  
    semaforo(red, 2);
    semaforo(green, 1);
    delay(tempo_1);
    semaforo(yellow, 2);
    semaforo(yellow,1);
    delay(tempo_2);
    semaforo(green, 2);
    semaforo(red, 1);
    delay(tempo_3);
}

void mode31() {
  // Código para Modo 31 (Prioridade para tráfego de veículos no semaforo 1)
  // 
  // Implemente a lógica aqui
  mode22();
}

void mode31() {
  // Código para Modo 32 (Prioridade para tráfego de veículos no semaforo 2)
  // 
  // Implemente a lógica aqui
  mode21();
}

void mode4() {
  // Código para Modo 4 (Carros com total prioridade)
  semaforo(green, 1);
  semaforo(green, 2);
  delay(15000);
}

void mode5() {
  // Código para Modo 5 (Pedestres com total prioridade)
  semaforo(red, 1);
  semaforo(red, 2);
  delay(15000);
}

int read_pedestrian_sensor( int sensor_pin) {
  // Código para ler o sensor de pedestres
  // 
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
  // Ler os sensores
  // Semaforo 1
  int pedestrian_count1 = read_pedestrian_sensor(pedestrian_sensor1);
  // Semafoto 2
  int pedestrian_count2 = read_pedestrian_sensor(pedestrian_sensor2);

  // Ler os sensores de fluxo de veículos
  // Semaforo 1
  int vehicle_count1_near = digitalRead(vehicle_sensor1_near);
  int vehicle_count1_far = digitalRead(vehicle_sensor1_far);
  // Semaforo 2
  int vehicle_count2_near = digitalRead(vehicle_sensor2_near);
  int vehicle_count2_far = digitalRead(vehicle_sensor2_far);

  // Suponha que 10 seja um limite para ativar modos especiais
if ( pedestrian_count1 > 10 || pedestrian_count2 > 10 ) {
    if ( pedestrian_count1 > 10 && pedestrian_count2 > 10 ) {
      mode5();
    } else if ( pedestrian_count1 > 10 ) {
      mode21();
    } else if ( pedestrian_count2 > 10 ) {
      mode22();
    }
  } else if ( vehicle_count1_near == HIGH || vehicle_count1_far == HIGH || vehicle_count2_near == HIGH || vehicle_count2_far == HIGH ) {
    if ( vehicle_count1_near == HIGH && vehicle_count1_far == HIGH && vehicle_count2_near == HIGH && vehicle_count2_far == HIGH ) {
      mode4();
    } else if ( vehicle_count1_near == HIGH || vehicle_count1_far == HIGH ) {
      mode31();
    } else if ( vehicle_count2_near == HIGH || vehicle_count2_far == HIGH ) {
      mode32();
    }
  } else {
    mode1();
  }

  delay(1000);  // Aguardar 1 segundo antes de fazer a próxima leitura
}
