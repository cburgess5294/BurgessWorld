#!/usr/bin/python

import spidev
import time

spi = spidev.SpiDev()
spi.mode = 0 
spi.open(0, 1)
spi.max_speed_hz = 976000 
spi.xfer2([0x68,0x65,0x6c,0x6c,0x6f])# transfer data 
