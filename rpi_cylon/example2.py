#!/usr/bin/env python
# File rpi_74HC595_cylon.py
# Use left and right shift resister functions.
# 8 LEDs connected to 74HC595
# http://www.bristolwatch.com/index.htm
# by Lewis Loflin lewis@sullivan-county.com
# http://www.bristolwatch.com/ele2/74HC595_cylon.htm
# access to GPIO must be through root
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
LATCH = 35 # Pin 12 Latch clock
CLK = 33 # Pin 11 shift clock
dataBit = 37 # Pin 14 A


GPIO.setup(LATCH, GPIO.OUT) # P0 
GPIO.setup(CLK, GPIO.OUT) # P1 
GPIO.setup(dataBit, GPIO.OUT) # P7 


# Setup IO
GPIO.output(LATCH, 0)
GPIO.output(CLK, 0)


def pulseCLK():
    GPIO.output(CLK, 1)
   # time.sleep(.01) 
    GPIO.output(CLK, 0)
    return

def serLatch():
    GPIO.output(LATCH, 1)
   # time.sleep(.01)
    GPIO.output(LATCH, 0)
    return




while 1:
    temp = 1
    for j in range(0, 16 ):
        ssrWrite(temp)
        temp = temp << 1
        time.sleep(.2)

    for j in range(0, 16 ):
        temp = temp >> 1
        ssrWrite(temp)
        time.sleep(.2)  

print "Good by!"
exit
