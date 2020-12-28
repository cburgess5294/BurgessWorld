#!/usr/bin/env python
import time
import math
import colorsys
from neopixel import *
 
# LED strip configuration:
LED_COUNT = 64      # Number of LED pixels.
LED_PIN = 18      # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA = 10       # DMA channel to use for generating signal (try 10)
LED_BRIGHTNESS = 255  # Set to 0 for darkest and 255 for brightest
# True to invert the signal (when using NPN transistor level shift)
LED_INVERT = False
 
def plasma (w, h, t):
    out = [ Color( 0, 0, 0 ) for x in range( w * h ) ]
    for x in range( w ):
        for y in range( h ):
            hue = 4.0 + math.sin( t + x ) + math.sin( t + y / 4.5 ) \
                + math.sin( x + y + t ) + math.sin( math.sqrt( ( x + t ) ** 2.0 + ( y + 1.5 * t ) ** 2.0 ) / 4.0 )
            hsv = colorsys.hsv_to_rgb( hue / 8.0, 1, 1 )
            out[ x + y * w ] = Color( *[ int( round( c * 10.0 ) ) for c in hsv ] )
    return out
 
# Main program logic follows:
if __name__ == '__main__':
    # Create NeoPixel object with appropriate configuration.
    strip = Adafruit_NeoPixel(
        LED_COUNT,
        LED_PIN,
        LED_FREQ_HZ,
        LED_DMA,
        LED_INVERT,
        LED_BRIGHTNESS
    )
    # Intialize the library (must be called once before other functions).
    strip.begin()
 
    t = 0.0                                                                       # time
    dt = 0.1                                                                      # speed of time
 
    for i in range( 0, strip.numPixels(), 1):                                     # iterate over all LEDs
        strip.setPixelColor( i, Color( 0, 0, 0 ) )                                # set LED to black (off)
 
    while True:
        t = t + dt                                                                # increment time
        pic = plasma( 8, 8, t )                                                   # render plasma of size 8x8 at time t
 
        for i in range( 0, strip.numPixels(), 1 ):                                # iterate over all LEDs
            strip.setPixelColor(                                                  # set pixel to color in picture
                i,
                pic[ i ]
            )
        strip.show()                                                              # update LEDs
        time.sleep(0.001)

