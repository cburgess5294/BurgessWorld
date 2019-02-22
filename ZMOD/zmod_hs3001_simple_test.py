#!/usr/bin/python3
from gpiozero import LED
from gpiozero import Button
import smbus
from time import sleep
from signal import pause
import atexit

# define pins
button = Button(21)
ledBlue = LED(24) 
ledAmber = LED(25)
ledReady = LED(19)

# create instance of smbus on rpi I2C bus 1 
bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

# Give the I2C device time to settle
sleep(2)

ledReady.on()

def exitState(): 
  ledBlue.off()
  ledAmber.off()
  ledReady.off()

def checkSensors():
  ledBlue.off()
  ledAmber.off()
  try:
    bus.write_quick(0x32) # wake sensor up and take a reading
    print("ZMOD OK")
    ledBlue.on()
  except:
    print("ZMOD FAILED")
  try:
    bus.write_quick(0x44) # wake sensor up and take a reading
    print("HS300x OK")
    ledAmber.on()
  except:
    print("HS300x FAILED")
  ledReady.off()
  sleep(.500)
  ledReady.on()

atexit.register(exitState)# turn off LEDs on exit 

button.when_pressed = checkSensors
pause()
