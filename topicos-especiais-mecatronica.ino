#include <Arduino.h>

// Defining the pins for the LEDs of the traffic lights
const int red_led1 = 2;
const int yellow_led1 = 3;
const int green_led1 = 4;

const int red_led2 = 5;
const int yellow_led2 = 6;
const int green_led2 = 7;

// Defining the sensors
// Assuming that weight and photoelectric sensors return digital values
const int pedestrian_sensor = 8;
const int vehicle_sensor = 9;

void setup() {
  // Initialize the LEDs as outputs
  pinMode(red_led1, OUTPUT);
  pinMode(yellow_led1, OUTPUT);
  pinMode(green_led1, OUTPUT);
  
  pinMode(red_led2, OUTPUT);
  pinMode(yellow_led2, OUTPUT);
  pinMode(green_led2, OUTPUT);
  
  // Initialize the sensors as inputs
  pinMode(pedestrian_sensor, INPUT);
  pinMode(vehicle_sensor, INPUT);
  
  // Initialize the serial port for debugging
  Serial.begin(9600);
}

void mode1() {
  Serial.println("Mode 1 Activated");
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
  Serial.println("Mode 2 Activated");
  // Code to prioritize pedestrians
}

void mode3() {
  Serial.println("Mode 3 Activated");
  // Code to prioritize vehicle traffic
}

void loop() {
  int pedestrian_count = digitalRead(pedestrian_sensor);
  int vehicle_count = digitalRead(vehicle_sensor);
  
  if(pedestrian_count > 10) {  // Assuming 10 is the limit
    mode2();
  } else if(vehicle_count > 10) {  // Assuming 10 is the limit
    mode3();
  } else {
    mode1();
  }
  
  delay(1000);  // Wait for 1 second before making the next reading
}
