#!/usr/bin/python

import serial
import scratch

#Opening serial connection with Pawn/NFC
try:
	serPawnNFC = serial.Serial('/dev/tty.Pawn-XadowBLESlave', 38400)
	serPawnNFC.flushInput()
except:
	print "[Error] No Pawn/NFC connected"		
stringaNFCPawn=" "

#Opening serial connection with Magnifier
try:
	serMagNFC = serial.Serial('/dev/tty.Magnifier-XadowBLESlave', 38400)
	serMagNFC.flushInput()
except:
	print "[Error] No Magnifier connected"		
stringaNFCMag=" "

#Opening socket connection with Scratch
s = scratch.Scratch()

while True:
	
	stringaNFCPawn = serPawnNFC.readline().strip()
	#print 'Serial received from NFC:'
	#print stringaNFCPawn
	if "room" in stringaNFCPawn:
		print '[Debug] Room received:'
		print stringaNFCPawn
		s.broadcast(stringaNFCPawn)
	elif "card" in stringaNFCPawn:
		print '[Debug] Card received:'
		print stringaNFCPawn
		s.broadcast(stringaNFCPawn)
	else:
		print '[Debug] Text received from Pawn NFC: '
		print stringaNFCPawn

	stringaNFCMag = serMagNFC.readline().strip()
	if "clue" in stringaNFCMag:
		print '[Debug] Clue received:'
		print stringaNFCMag
		s.broadcast(stringaNFCMag)
	else:
		print '[Debug] Text received from Pawn NFC: '
		print stringaNFCMag
	
	
