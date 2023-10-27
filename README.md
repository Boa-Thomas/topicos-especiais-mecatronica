# Sistema de Controle de Semáforos com Sensores

## Descrição

Este projeto é um sistema de controle de semáforos usando Arduino. O código é configurado para dois semáforos em um cruzamento, cada um com uma faixa de pedestres. Cada semáforo possui dois sensores de fluxo para veículos: um mais próximo e um mais afastado do semáforo.

## Hardware Necessário

- Placa Arduino (testado em Arduino Uno)
- LEDs para representar os semáforos (2 vermelhos, 2 amarelos, 2 verdes)
- Sensores para detecção de pedestres (2 sensores)
- Sensores de fluxo para veículos (4 sensores)

## Pinagem

### LEDs

- LED Vermelho do Semáforo 1: Pino 2
- LED Amarelo do Semáforo 1: Pino 3
- LED Verde do Semáforo 1: Pino 4

- LED Vermelho do Semáforo 2: Pino 5
- LED Amarelo do Semáforo 2: Pino 6
- LED Verde do Semáforo 2: Pino 7

### Sensores

- Sensor de Pedestres do Semáforo 1: Pino 8
- Sensor de Pedestres do Semáforo 2: Pino 9

- Sensor de Fluxo de Veículos Próximo do Semáforo 1: Pino 10
- Sensor de Fluxo de Veículos Afastado do Semáforo 1: Pino 11
- Sensor de Fluxo de Veículos Próximo do Semáforo 2: Pino 12
- Sensor de Fluxo de Veículos Afastado do Semáforo 2: Pino 13

## Funcionalidades

- `mode1()`: Modo de operação padrão dos semáforos.
- `mode2()`: Modo de operação que dá prioridade aos pedestres.
- `mode3()`: Modo de operação que dá prioridade ao tráfego de veículos.

## Como Usar

1. Conecte todos os componentes de hardware conforme a pinagem descrita.
2. Carregue o código no Arduino.
3. O sistema começa a operar automaticamente.

## Contribuições

Sinta-se à vontade para contribuir com este projeto.

## Licença

MIT
