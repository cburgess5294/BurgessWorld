#!/usr/bin/python
import smbus
import time

# create instance of smbus on rpi I2C bus 1 
bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

# Give the I2C device time to settle
time.sleep(2)

# define sensor i2C address
DEVICE_ADDRESS = 0x32  #7 bit address (will be left shifted to add the read write bit)
#DEVICE_REG_MODE1 = 0x00
#DEVICE_REG_LEDOUT0 = 0x1d

# function to clear bits from returned data bytes
def clearBit(int_type, offset):
   mask = ~(1 << offset)
   return(int_type & mask)

ledout_values = [0xff, 0xff , 0xff , 0xff] 
# read sensor
bus.write_quick(DEVICE_ADDRESS) # wake sensor up and take a reading
time.sleep(.040) # give the sensor time to gather data
readSensor =  bus.read_i2c_block_data(DEVICE_ADDRESS,0,6) # read 4 bytes of data you could change the 4 to a 2 in order to only read humidity data

print readSensor[0]
print readSensor[1]
print readSensor[2]
print readSensor[3]
print readSensor[4]
print readSensor[5]
# process humidity data
#hum = readSensor[0] # put first byte of humidity data into a variable
#hum = clearBit( hum , 7 ) # clear bit 7 - this is a status bit
#hum = clearBit( hum, 6 ) # clear bit 6 - this is a status bit
#hum = hum * 256.0 + readSensor[1] # shift first byte left 8 bits and add second byte of humidity data
#hum = (hum / 16383) * 100 # convert raw data to humidity reading
#print "humidity" , int(hum) , "%" # print humidity reading at integer

# process temperature data
#temp = readSensor[2] * 256  # put first byte of temperature data into a variable and shift 8-bits to the left
#temp = temp + readSensor[3] # add first and second bytes of temperature data together
#temp = temp >> 2 # shift temperature data 2 bits to the left to mask undefined bits
#temp = ( temp / 16383.0) * 165 - 40 # convert raw temperature data to celsius 
#print "temperature" , int(temp) , "C" # print temperature as in in C
