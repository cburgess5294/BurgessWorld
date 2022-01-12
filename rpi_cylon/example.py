#!/usr/bin/env python
# File relay_example.py
# Use left and right shift resister functions.
# 16 LEDs connected to 74HC595 shift registers
# http://tindie.com/stores/cburgess129
# by Chris Burgess cburgess@burgessworld.net
#
# setting output to LOW enables relay, setting output to HIGH disables relay

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

# MSB out first!
def ssrWrite(value):
    for  x in range(0,16):
        temp = value & 0x8000
        if temp == 0x8000:
           GPIO.output(dataBit, 1) # data bit HIGH
        else:
           GPIO.output(dataBit, 0) # data bit LOW
        pulseCLK()
        value = value << 0x01 # shift left
    serLatch() # output byte
    return


# convert an 8-bit number to a binary string
def convBinary(value):
    binaryValue = '0b'
    for  x in range(0,16):
        temp = value & 0x8000
        if temp == 0x8000:
           binaryValue = binaryValue + '1'
        else:
            binaryValue = binaryValue + '0'
        value = value << 1
    return binaryValue

# turn off all relays
temp = 0xffff # equates to binary 1111111111111111
ssrWrite(temp)
time.sleep(.5)

# turn relays on and off one at a time
temp = 1
for j in range(0, 16 ):
	ssrWrite(temp)
	temp = temp << 1
	time.sleep(.2)

for j in range(0, 16 ):
	temp = temp >> 1
	ssrWrite(temp)
	time.sleep(.2)

# turn all relays on and off at once
temp = 0x0 # equates to binary 1111111111111111
ssrWrite(temp)
time.sleep(.5)
temp = 0xffff
ssrWrite(temp)
time.sleep(.5)
temp = 0x0
ssrWrite(temp)
time.sleep(.5)
temp = 0xffff
ssrWrite(temp)

# turn on relays 1-8
temp = 0b0000000011111111
ssrWrite(temp)
time.sleep(.5)

# turn on relays 9-16
temp = 0b1111111100000000
ssrWrite(temp)
time.sleep(.5)

# turn off all relays
temp = 0b1111111111111111
ssrWrite(temp)

print "Good by!"
exit
