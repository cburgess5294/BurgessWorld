import RPi.GPIO as GPIO
import time

all_pins = (7, 11, 12, 13, 15, 21, 18, 19)
GPIO.setmode(GPIO.BOARD)


for pin in all_pins:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.HIGH)

for pin in all_pins:
    GPIO.setmode(GPIO.BOARD)
    print("Testing pin %d as OUTPUT; CTRL-C to test next pin" % pin)
    try:
        while True:
            GPIO.setup(pin, GPIO.OUT)
            GPIO.output(pin, GPIO.LOW)
            time.sleep(0.25)
            GPIO.output(pin, GPIO.HIGH)
            time.sleep(0.25)
    except KeyboardInterrupt:
        pass
    finally:
        GPIO.cleanup()
