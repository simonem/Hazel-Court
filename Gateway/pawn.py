#!/usr/bin/python

import serial
import scratch
import threading

def listen():
	try:
		yield s.receive()
	except scratch.ScratchError:
		raise StopIteration
		
def readserial(serial,scratch):
	print "[Debug] Thread started"
	while True:
		stringaNFC = serial.readline().strip()
		print "[Debug] Read from serial Started"
		if "room" in stringaNFC:
			print '[Debug] Room received:'
			print stringaNFC
			scratch.broadcast(stringaNFC)
		elif "card" in stringaNFC:
			print '[Debug] Card received:'
			print stringaNFC
			scratch.broadcast(stringaNFC)
		else:
			print '[Debug] Text received from Pawn NFC: '
			print stringaNFC
		#	serPawn.flushInput()
	

#Opening serial connection with Pawn/NFC
try:
	serPawn = serial.Serial('/dev/tty.usbmodemfa131', 38400)
	serPawn.flushInput()
	print "[Debug] Serial port opened"
except:
	print "[Error] No Pawn connected"

stringaNFC=" "
stringaLCD=" "

#Opening socket connection with Scratch
s = scratch.Scratch()

thread = threading.Thread(target=readserial, args=(serPawn,s))
thread.start()

try:
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
except KeyboardInterrupt:
	print "CLOSING..."
	thread.exit() 
		