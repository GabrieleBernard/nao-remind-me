#!/usr/bin/env python3
from gpiozero import Button
from signal import pause
import time
from pololu_drv8835_rpi import motors, MAX_SPEED

button = Button(4)

MOTOR_MAX_SPEED = int(MAX_SPEED / 3)

# Set up sequence of motor speeds.
motor_speeds = list(range(0, -MOTOR_MAX_SPEED, -1)) \
               + [-MOTOR_MAX_SPEED] * 10 \
               + list(range(-MOTOR_MAX_SPEED, 0, 1)) \
               + [0] \
               + list(range(0, MOTOR_MAX_SPEED, 1)) \
               + list(range(MOTOR_MAX_SPEED, 0, -1)) \
               + [0]

def activateMonitorMotor():
    print("Persona seduta")
    print("Motore attivo, sta accendendo il monitor")
    for s in motor_speeds:
        motors.motor2.setSpeed(s)
        time.sleep(0.005)

def deactivateMonitorMotor():
    print("Nessuno seduto")
    print("Motore attivo, sta spegnendo il monitor")
    for s in motor_speeds:
        motors.motor2.setSpeed(s)
        time.sleep(0.005)

button.when_pressed = activateMonitorMotor
button.when_released = deactivateMonitorMotor
try:
    pause()
except:
    pass
finally:
    # Stop the motors, even if there is an exception
    # or the user presses Ctrl+C to kill the process.
    motors.setSpeeds(0, 0)
