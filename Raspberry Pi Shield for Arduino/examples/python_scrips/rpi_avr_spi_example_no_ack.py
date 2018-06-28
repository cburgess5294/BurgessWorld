#!/usr/bin/python

import spidev
import time
 
spi = spidev.SpiDev()
spi.open(0, 1)
spi.max_speed_hz = 976000
try:
  while True:
   spi.xfer2([0x68,0x65,0x6c,0x6c,0x6f,0x0a])# transfer data 
   time.sleep(.025)
except KeyboardInterrupt: # Ctrl+C pressed
   spi.close()
   print("---------------")
   print("good trans: %d" %  goodTrans)
   print("bad trans: %d" % badTrans)

