# Semáforo com Sensores

## Descrição

Este projeto é um semáforo Arduino que usa sensores para detectar pedestres e veículos. O sistema possui três modos:

- Modo 1: Semáforo padrão sem qualquer prioridade.
- Modo 2: Prioridade para pedestres.
- Modo 3: Prioridade para veículos.

## Requisitos

- Placa Arduino (qualquer modelo compatível)
- LEDs para os semáforos (vermelho, amarelo e verde)
- Sensores para detectar pedestres e veículos

## Pinos

Os pinos utilizados no Arduino para este projeto são:

- LEDs do semáforo 1: 2, 3 e 4
- LEDs do semáforo 2: 5, 6 e 7
- Sensor de pedestres: 8
- Sensor de veículos: 9

## Setup

1. Conecte os LEDs e sensores aos pinos apropriados no Arduino.
2. Carregue o código para a placa Arduino.
3. Abra o monitor serial para visualizar as mensagens de depuração.

## Uso

Após carregar o código, o sistema entrará no Modo 1 por padrão, a menos que detecte um número significativo de pedestres ou veículos.

## Contribuição

Fique à vontade para contribuir e adicionar novas funcionalidades a este projeto.

## Licença

Este projeto é licenciado sob a Licença MIT.
