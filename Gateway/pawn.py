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
		elif "clue" in stringaNFC:
			print '[Debug] Clue received:'
			print stringaNFC
			scratch.broadcast(stringaNFC)
		else:
			print '[Debug] Text received from Pawn NFC: '
			print stringaNFC
		#	serPawn.flushInput()
	

#Opening serial connection with Pawn, Printer and Magnifier
try:
	serPawn = serial.Serial('/dev/tty.usbserial-A6XFZBHP', 9600)
	serPawn.flushInput()
	print "[Debug] Serial port opened"
except:
	print "[Error] No Serial cradle connected"

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
					print msg[1]
					serPawn.write(msg[1])
				if element[0] == 'text':
					print "[Debug] Sending Text to Printer:"
					print msg[1]
					serPawn.write(msg[1])
					
except KeyboardInterrupt:
	print "CLOSING..."
	thread.join(1) 
		