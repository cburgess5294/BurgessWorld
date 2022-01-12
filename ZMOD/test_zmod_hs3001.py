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

ledReady.off()

# create instance of smbus on rpi I2C bus 1 
bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

# Give the I2C device time to settle
sleep(2)

ledReady.on()

def clearBit(int_type, offset):
   mask = ~(1 << offset)
   return(int_type & mask)

def exitState(): 
  ledBlue.off()
  ledAmber.off()
  ledReady.off()

def checkSensors():
  ledBlue.off()
  ledAmber.off()
  sleep(.5)
  ledBlue.on()
  ledAmber.on()
  sleep(.5)
  ledBlue.off()
  ledAmber.off()
  try:
    sleep(2)
    bus.write_quick(0x32) # wake sensor up and take a reading
    print("ZMOD OK")
    ledBlue.on()
  except:
    pass
    print("ZMOD FAILED")
  try:
    sleep(2)
    bus.write_quick(0x33) # wake ZMOD4510 sensor up and take a reading
    print("ZMOD4510 OK")
    ledBlue.on()
  except:
    pass
    print("ZMOD4510 FAILED")
  try:
    bus.write_quick(0x44) # wake sensor up and take a reading
    sleep(.040)
    readSensor =  bus.read_i2c_block_data(0x44,0,4) 
    # process humidity data
    hum = readSensor[0]
    hum = clearBit( hum , 7 )
    hum = clearBit( hum, 6 )
    hum = hum * 256.0 + readSensor[1]
    hum = (hum / 16383) * 100
    print("humidity" , int(hum) , "%")

    # process temperature data
    temp = readSensor[2] * 256
    temp = temp + readSensor[3]
    temp = temp >> 2 
    temp = ( temp / 16383.0) * 165 - 40
    print("temperature" , int(temp) , "C")
    if 10 <= hum <= 90  and  1 <= temp <= 50:
      print("HS300x OK")
      ledAmber.on()
  except:
    pass
    print("HS300x FAILED")
  ledReady.off()
  sleep(.500)
  ledReady.on()

  sleep(5)
  ledAmber.off()
  ledBlue.off() 

atexit.register(exitState)# turn off LEDs on exit 

button.when_pressed = checkSensors
pause()
