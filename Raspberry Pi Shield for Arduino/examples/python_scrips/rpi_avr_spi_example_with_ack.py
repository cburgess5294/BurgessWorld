#!/usr/bin/python

import spidev
import time
 
stamp = 0;
goodTrans = 0;
badTrans = 0;
spi = spidev.SpiDev()
<<<<<<< HEAD
spi.open(0, 0)
=======
spi.open(0, 1)
>>>>>>> 5343e4047b8296d9229f3f5bc2ac65fb526ad1ee
spi.max_speed_hz = 1000000
try:
  while True:
    stamp += 1
    returned = 0x00
    spi.xfer2([0x68,0x65,0x6c,0x6c,0x6f,0xfe])# transfer data and check for reply 
    while returned == 0x00:# wait for the ardunio to reply
      time.sleep(.005)# delay to prevent overloading arduino buffer
      returned = spi.xfer2([0x00])[0]# check for reply 
    if returned == 0x01:
      print("good trans %d" % stamp)
      goodTrans += 1
    else: 
      print("bad trans %d, %d" % ( returned, stamp))
      badTrans += 1
    #time.sleep(.01)# delay to allow arduino to print the output and reply
    if stamp == 65000:
      print("---------------")
      print("good trans: %d" %  goodTrans)
      print("bad trans: %d" % badTrans) 
      break
except KeyboardInterrupt: # Ctrl+C pressed
   spi.close()
   print("---------------")
   print("good trans: %d" %  goodTrans)
   print("bad trans: %d" % badTrans)

