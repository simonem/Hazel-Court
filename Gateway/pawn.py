#!/usr/bin/python

import serial
import scratch

def listen():
	try:
		yield s.receive()
	except scratch.ScratchError:
		raise StopIteration

#Opening serial connection with Pawn/NFC
try:
	serPawn = serial.Serial('/dev/tty.usbmodemfa131', 38400, timeout=1)
	serPawn.flushInput()
except:
	print "[Error] No Pawn connected"

stringaNFC=" "
stringaLCD=" "

#Opening socket connection with Scratch
s = scratch.Scratch()

while True:
	#Pocesses messages from scratch to pawn
	for msg in listen():
		print msg
		if msg[0] == 'broadcast':
			print "Broadcast message: "
			print msg[1]
			element = msg[1].split(":")
			if element[0] == 'image':
				print "[Debug] Sending Image to LCD:"
				print element[1]
				serPawn.write(element[1])
	
	#Processes messages from the pawn to scrach
	print serPawn.inWaiting()
	while serPawn.inWaiting() > 0:
		stringaNFC = serPawn.readline().strip()
		if "room" in stringaNFC:
			print '[Debug] Room received:'
			print stringaNFC
			s.broadcast(stringaNFC)
		elif "card" in stringaNFC:
			print '[Debug] Card received:'
			print stringaNFC
			s.broadcast(stringaNFC)
		else:
			print '[Debug] Text received from Pawn NFC: '
			print stringaNFC
			#	serPawn.flushInput()