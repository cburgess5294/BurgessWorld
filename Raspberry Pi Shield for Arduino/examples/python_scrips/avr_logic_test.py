#!/usr/bin/env python

from time import sleep           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
import atexit

GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering
INPUT_PIN = 23           # Sets our input pin, in this example I'm connecting our button to pin 4. Pin 0 is the SDA pin so I avoid using it for sensors/buttons
OUTPUT_PIN = 13          # GPIO13 is connected to an LED on the Raspberry Pi Shield
on = 0 
GPIO.setup(INPUT_PIN, GPIO.IN)           # Set our input pin to be an input
GPIO.setup(OUTPUT_PIN, GPIO.OUT)
GPIO.output(OUTPUT_PIN, GPIO.LOW)
# Start a loop that never ends
while True:
   try: 
           if (GPIO.input(INPUT_PIN) == True): # Physically read the pin now
                    if on == 0: 
                         GPIO.output(OUTPUT_PIN, GPIO.HIGH)
                         on = 1 

           else:
                    if on == 1: 
                         GPIO.output(OUTPUT_PIN, GPIO.LOW)
                         on = 0 
   except KeyboardInterrupt: 
         GPIO.cleanup()
         break
