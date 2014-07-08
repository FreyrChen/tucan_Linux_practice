#!/usr/bin/python
# -*- coding=utf-8 -*-

import socket
import threading
import SocketServer


HOST = ''
PORT = 6000
PACKET_SIZE = 2048
client_id = 0

class ThreadedTCPRequestHandler( SocketServer.StreamRequestHandler ):

	def handle( self ):
		print'Get connection from:', self.client_address[0]
		cur_thread = threading.current_thread()
		client_id += 1
		#print'get connection from:', self.request.getpeername()
		while True:
			self.data = self.request.recv( PACKET_SIZE )
			if not self.data:
				break
			else:
				print"%s NO.%d [%s]: %s"%( cur_thread.name, client_id, self.client_address[0], self.data )
				#self.request.sendall( self.data.upper() )

class ThreadedTCPServer( SocketServer.ThreadingMixIn, SocketServer.TCPServer ):
	pass

if __name__ == "__main__":
	
	print 'server established'
	server = ThreadedTCPServer( (HOST,PORT), ThreadedTCPRequestHandler )

	server_thread = threading.Thread( target=server.serve_forever)
	server_thread.daemon = True
	server_thread.start()
	print "Server loop running in thread: ", server_thread.name

	server.shutdown()	

