from machine import Pin
import time

#identificar los pines que conectan con el driver
pinEnable = Pin(5, pin.OUT, value=0)
pinStep = Pin(4, pin.OUT)
pinDir = Pin(0, pin.OUT)

#cuantospasos por revolucion (depende de los grados del motor)
stepPerRevolution = 200

#estructura de bucle infinito
while True:

    #va para un lado
    pinDir.on()

    #bucle para dar una vuelta completa
    for i in range(0, stepPerRevolution):
        pinStep.on()
        time.sleep_ms(10)
        pinStep.off()
        time.sleep_ms(10)

    #va para el otro lado
    pinDir.off()

    for i in range(0, stepPerRevolution):
        pinStep.on()
        time.sleep_ms(10)
        pinStep.off()
        time.sleep_ms(10)