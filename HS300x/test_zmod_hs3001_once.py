#!/usr/bin/python3
from gpiozero import LED
import smbus
from time import sleep
import atexit

# define pins
ledBlue = LED(24) 
ledAmber = LED(25)


# create instance of smbus on rpi I2C bus 1 
bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

# Give the I2C device time to settle
sleep(2)

def clearBit(int_type, offset):
  mask = ~(1 << offset)
  return(int_type & mask)

ledBlue.off()
ledAmber.off()

try:
  sleep(2)
  bus.write_quick(0x32) # wake sensor up and take a reading
  print("ZMOD OK")
  ledBlue.on()
except:
  print("ZMOD FAILED")
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
  print("HS300x FAILED")
sleep(3)
