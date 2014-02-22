#!/usr/bin/python

import serial
import scratch
from Adafruit_Thermal import *

def listen():
    while True:
        try:
           yield s.receive()
        except scratch.ScratchError:
           raise StopIteration

s = scratch.Scratch()
try:
	serLCD = serial.Serial('/dev/tty.usbmodemfa131', 38400)
except:
	print "[Error] No LCD connected"
try:
	printer = Adafruit_Thermal("/dev/tty.usbserial-A501E3BT", 19200, timeout=5)
except:
	print "[Error] No printer connected"
serLCD.flushInput()
stringa=" "

msg = s.receive()
print msg
for msg in listen():
	print msg
	if msg[0] == 'broadcast':
		print "Broadcast message: "
		print msg[1]
		element = msg[1].split(":")
		if element[0] == 'image':
			print "[Debug] Sending Image to LCD:"
			print element[1] 
			serLCD.write(element[1])
		if element[0] == 'text':
			print "[Debug] Text to printer:"
			print element[1] 
			printer.println(element[1])
			

