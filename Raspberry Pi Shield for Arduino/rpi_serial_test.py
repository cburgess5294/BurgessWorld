#!/usr/bin/python
import serial
import time

port = serial.Serial("/dev/ttyS0", baudrate=57600, timeout=3.0)
print("Raspberry Pi - AVR Serial Test")
print
print("Port Information:")
print("----------------------------------------------------------------")
print(port)
print
print("Send some data from the AVR and the rPI will reply")
rcv = ""
port.write("\r\nSay something:")
while True:
    time.sleep(.100)
    byteCount = port.inWaiting()
    if byteCount  >= 1:
      rcv = port.read(byteCount)
      if rcv != "" and rcv != "\n" and rcv != "\r":
        port.write("\r\nYou sent:" + repr(rcv))
