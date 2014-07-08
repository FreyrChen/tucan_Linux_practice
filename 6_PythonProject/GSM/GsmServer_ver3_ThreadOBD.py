#!/usr/bin/python
# -*- coding=utf-8 -*-


import SocketServer


HOST = ''
PORT = 6000
PACKET_SIZE = 2048

class MyTCPHandler( SocketServer.StreamRequestHandler ):

	def handle( self ):
		print'get connection from:', self.client_adderss
		while True:
			self.data = self.request.recv( PACKE_SIZE )
			if not data:
				break
			else:
				print"{}wrote:".format( self.client_addresd )
				print self.data
				#self.request.sendall( self.data.upper() )

if __name__ == "__main__":
	
	print 'server established'
	server = SocketServer.ThreadingTCPServer( (HOST,PORT), MyTCPHandler )
	server.serve_forever()


