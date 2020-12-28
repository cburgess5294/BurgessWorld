#!/usr/bin/python
import smbus
import time

# create instance of smbus on rpi I2C bus 1 
bus = smbus.SMBus(1)    # 0 = /dev/i2c-0 (port I2C0), 1 = /dev/i2c-1 (port I2C1)

# Give the I2C device time to settle
time.sleep(2)

# define sensor i2C address
DEVICE_ADDRESS = 0x48  #7 bit address (will be left shifted to add the read write bit)

# configure sensor
bus.write_word_data(DEVICE_ADDRESS, 0x1, 0x83C1)
# now read back the config
readSensor =  bus.read_i2c_block_data(DEVICE_ADDRESS,1,2) # read 2 bytes of data
print readSensor[0]
print readSensor[1]

time.sleep(.040) # give the sensor time to gather data
#now read the data values
readSensor =  bus.read_i2c_block_data(DEVICE_ADDRESS,0,2) # read 2 bytes of data
print readSensor[0]
print readSensor[1]

