#include <Arduino.h>
#include "Adafruit_VL53L0X.h"
#include "HX711.h"


// Definindo os pinos para os LEDs dos semáforos
// Semaforo 1
const int red_led1 = 28;
const int yellow_led1 = 30;
const int green_led1 = 32;
// Semaforo 2
const int red_led2 = 43;
const int yellow_led2 = 45;
const int green_led2 = 47;


// Definição dos pinos para o módulo HX711
const int LOADCELL_DOUT_PIN1 = A0;
const int LOADCELL_SCK_PIN1 = A1;

const int LOADCELL_DOUT_PIN2 = A2;
const int LOADCELL_SCK_PIN2 = A3;

// Definição dos objetos para o módulo HX711
HX711 scale1;
HX711 scale2;



// Crie dois objetos para o VL53L0X
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// Pinos de desligamento para cada sensor conectado a diferentes GPIOs
const int shutdownPin1 = 10; //<- essa parte precisa ser conectada ao pino de desligamento do sensor 1 (ainda não conectado)
const int shutdownPin2 = 11; //<- essa parte precisa ser conectada ao pino de desligamento do sensor 2 (ainda não conectado)


void setID() {
  // Desligue lox1 e mantenha lox2 funcionando
  digitalWrite(shutdownPin1, LOW);
  digitalWrite(shutdownPin2, HIGH);
  delay(10);
  // Inicialize lox2 com o endereço padrão
  if (!lox2.begin()) {
    Serial.println(F("Falha ao iniciar o segundo VL53L0X"));
    while (1);
  }

  // Altere o endereço de lox2
  lox2.setAddress((uint8_t)22);

  // Reinicie lox1
  digitalWrite(shutdownPin1, HIGH);
  delay(10);
  // Inicialize lox1 com o endereço padrão
  if (!lox1.begin()) {
    Serial.println(F("Falha ao iniciar o primeiro VL53L0X"));
    while (1);
  }
}

// Função para ler de um sensor específico
int readDistance(int sensorNumber) {
  VL53L0X_RangingMeasurementData_t measure;

  if (sensorNumber == 1) {
    lox1.rangingTest(&measure, false);
  } else if (sensorNumber == 2) {
    lox2.rangingTest(&measure, false);
  } else {
    return -1; // Número de sensor inválido
  }

  if (measure.RangeStatus != 4) { // Verifique se a medição é válida
    return measure.RangeMilliMeter;
  } else {
    return -2; // Fora do alcance
  }
}



void setup() {
  // Inicializar os LEDs como saídas
  pinMode(red_led1, OUTPUT);
  pinMode(yellow_led1, OUTPUT);
  pinMode(green_led1, OUTPUT);

  pinMode(red_led2, OUTPUT);
  pinMode(yellow_led2, OUTPUT);
  pinMode(green_led2, OUTPUT);

  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);

  pinMode(shutdownPin1, OUTPUT);
  pinMode(shutdownPin2, OUTPUT);

  // Inicializar a porta serial para depuração
  Serial.begin(9600);
  setID();

}
// Modo de operação padrão
void mode1() {
  semaforo("red", 1);
  delay(5000);
  semaforo("yellow", 1);
  delay(2000);
  semaforo("green", 1);
  delay(15000);
}

void mode21() {
  // Código para Modo 21 (Prioridade para pedestres no semaforo 1)
  int tempo_1 = 15000;
  int tempo_2 = 3000;
  int tempo_3 = 5000;
  
    semaforo("red", 1);
    semaforo("green", 2);
    delay(tempo_1);
    semaforo("yellow", 1);
    semaforo("yellow",2);
    delay(tempo_2);
    semaforo("green", 1);
    semaforo("red", 2);
    delay(tempo_3);
  // Implemente a lógica aqui
}

void mode22() {
  // Código para Modo 22 (Prioridade para pedestres no semaforo 2)
  // Implemente a lógica aqui
  int tempo_1 = 15000;
  int tempo_2 = 3000;
  int tempo_3 = 5000;
  
    semaforo("red", 2);
    semaforo("green", 1);
    delay(tempo_1);
    semaforo("yellow", 2);
    semaforo("yellow",1);
    delay(tempo_2);
    semaforo("green", 2);
    semaforo("red", 1);
    delay(tempo_3);
}

void mode31() {
  // Código para Modo 31 (Prioridade para tráfego de veículos no semaforo 1)
  // 
  // Implemente a lógica aqui
  mode22();
}

void mode32() {
  // Código para Modo 32 (Prioridade para tráfego de veículos no semaforo 2)
  // 
  // Implemente a lógica aqui
  mode21();
}


void mode5() {
  // Código para Modo 5 (Pedestres com total prioridade)
  semaforo("red", 1);
  semaforo("red", 2);
  delay(15000);
}

int read_pedestrian_sensor() {
  // Código para ler o sensor de pedestres
  // 
  // Implemente a lógica aqui
}


float readWeight(HX711 scale) {

  //Utilizar a função 'read' do objeto HX711 para ler o peso
  // float weight1 = readWeight(scale1);
  // float weight2 = readWeight(scale2);

  if (scale.is_ready()) {
    long reading = scale.read();
    // Substituir 'calibration_factor' pelo fator de calibração específico
    float weight = reading / calibration_factor;
    return weight;
  } else {
    Serial.println("Erro na leitura da célula de carga");
    return 0;
  }
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
  float weight1 = readWeight(scale1);
  
  // Semafoto 2
  float weight2 = readWeight(scale2);


  // Ler os sensores de fluxo de veículos
  // Semaforo 1
  int vehicle_count1 = readDistance(1);
  // Semaforo 2
  int vehicle_count2 = readDistance(2);

  // Definir os limites para ativar os modos especiais
  // Limiares do sensor de carros
  int carro_detectado = 1000;
  int nao_detectado = -2;

  // Suponha que 10 seja um limite para ativar modos especiais
if ( weight1 > 200 || weight2 > 200 ) {
    if ( weight1 > 200 && weight2 > 200 ) {
      mode5();
    } else if ( weight1 > 200 ) {
      mode21();
    } else if ( weight2 > 200 ) {
      mode22();
    }
  } else if ( vehicle_count1 < carro_detectado || vehicle_count2 < nao_detectado || vehicle_count1 < nao_detectado || vehicle_count2 < carro_detectado) {
    if (vehicle_count1 < carro_detectado && vehicle_count2 < nao_detectado && vehicle_count1 < nao_detectado && vehicle_count2 < carro_detectado ) {
      mode4();
    } else if ( vehicle_count1 < carro_detectado || vehicle_count2 < nao_detectado ) {
      mode31();
    } else if ( vehicle_count2 < carro_detectado || vehicle_count1 < nao_detectado ) {
      mode32();
    }
  } else {
    mode1();
  }

  delay(1000);  // Aguardar 1 segundo antes de fazer a próxima leitura
}
