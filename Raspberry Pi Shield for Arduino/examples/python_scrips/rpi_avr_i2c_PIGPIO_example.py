#!/usr/bin/python
import time
import pigpio

pi = pigpio.pi() # create pigpio instance
bus = pi.i2c_open(1, 0x08) # open device at address 8 on i2c bus 1
time.sleep(2)

def StringToBytes(val):
    retVal = []
    for c in val:
            retVal.append(ord(c))
    return retVal

byteString = ("hello")
bytelist = StringToBytes(byteString)

while True:
  # write the bytes to the device
  for byte in bytelist:
    pi.i2c_write_byte(bus, byte)
  while pi.i2c_read_byte(bus) != 1:
    pass 

pi.i2c_close(bus) # close the device

