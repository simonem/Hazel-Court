#!/usr/bin/python

import serial
import scratch

#Opening serial connection with Magnifier
try:
	serMagNFC = serial.Serial('/dev/tty.XadowBLESlave-XadowBLES', 38400)
	serMagNFC.flushInput()
except:
	print "[Error] No Magnifier connected"		
stringaNFCMag=" "

#Opening socket connection with Scratch
s = scratch.Scratch()

while True:
	stringaNFCMag = serMagNFC.readline().strip()
	if "clue" in stringaNFCMag:
		print '[Debug] Clue received:'
		print stringaNFCMag
		s.broadcast(stringaNFCMag)
	else:
		print '[Debug] Text received from Magnifier: '
		print stringaNFCMag
	
	
