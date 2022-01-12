The MCP3208 library used by the example python script was removed by the creator.  I have found the following workaround but the owner of the MCP3008 library listed below may remove it at some point in the future as well
Workaround:
- Make sure you have enabled the SPI bus in raspi-config
  Python2
  - pip install Adafruit_MCP3008
  - pip install Adafruit_GPIO

  Python3
  pip3 install Adafruit_MCP3008
  pip3 install Adafruit_GPIO

- git clone https://github.com/MomsFriendlyRobotCompany/mcp3208
- cd mcp3208
- python ./example.py
  -or-
- python3 ./example.py

You can also use the GPIOZero functionality, which has built-in support for MCP3xxx modules:
https://gpiozero.readthedocs.io/en/stable/

Finally, you can use the SPI interface directly to access the ADC module.  There are many examples of this available via google search.
