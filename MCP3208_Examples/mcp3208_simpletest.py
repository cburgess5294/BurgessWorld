#!/usr/bin/env python
from mcp3208 import MCP3208
import time

adc = MCP3208()
print("MCP3208 EXAMPLE - Read All 8 Ports Every 1/2 Second")
print()
print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*range(8)))
print('-' * 57)
while True:
        values = [0]*8
        for i in range(8):
           values[i] = (adc.read(i))
        print('| {0:>4} | {1:>4} | {2:>4} | {3:>4} | {4:>4} | {5:>4} | {6:>4} | {7:>4} |'.format(*values))
        time.sleep(0.5)
