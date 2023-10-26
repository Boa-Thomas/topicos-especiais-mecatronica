import machine
import time
import utime

# Definindo os pinos para os LEDs dos semáforos
red_led1 = machine.Pin(2, machine.Pin.OUT)
yellow_led1 = machine.Pin(3, machine.Pin.OUT)
green_led1 = machine.Pin(4, machine.Pin.OUT)

red_led2 = machine.Pin(5, machine.Pin.OUT)
yellow_led2 = machine.Pin(6, machine.Pin.OUT)
green_led2 = machine.Pin(7, machine.Pin.OUT)

# Definindo os sensores
# Assumindo que os sensores de peso e fotoelétricos retornem valores digitais
pedestrian_sensor = machine.Pin(8, machine.Pin.IN)
vehicle_sensor = machine.Pin(9, machine.Pin.IN)

# Função para o Modo 1: Controle por Tempo (Normal)
def mode1():
    print("Modo 1 Ativado")
    red_led1.on()
    red_led2.off()
    time.sleep(5)
    
    yellow_led1.on()
    time.sleep(2)
    
    red_led1.off()
    yellow_led1.off()
    green_led1.on()
    time.sleep(5)
    
    green_led1.off()
    red_led2.on()
    time.sleep(5)
    
    yellow_led2.on()
    time.sleep(2)
    
    red_led2.off()
    yellow_led2.off()
    green_led2.on()
    time.sleep(5)
    
    green_led2.off()

# Função para o Modo 2: Controle por densidade de pedestres
def mode2():
    print("Modo 2 Ativado")
    # Código para dar prioridade aos pedestres

# Função para o Modo 3: Controle por sensor fotoelétrico de movimento de carros
def mode3():
    print("Modo 3 Ativado")
    # Código para dar prioridade ao tráfego de veículos

# Loop principal
while True:
    pedestrian_count = pedestrian_sensor.value()
    vehicle_count = vehicle_sensor.value()
    
    if pedestrian_count > 10:  # Supondo que 10 seja o limite
        mode2()
    elif vehicle_count > 10:  # Supondo que 10 seja o limite
        mode3()
    else:
        mode1()
    
    time.sleep(1)  # Aguardar 1 segundo antes de fazer a próxima leitura
