#!/usr/bin/python
# -*- coding=utf-8 -*-
'''
# this TCP connection from MCU+GSM to server.
# 2014/6
#
'''
import sys
import os
import datetime
import socket

###################################################
# Establish tcp connection to client,
# return client.
#
def listenServer( int port ):
	print '-'*40
	print 'Initial server to listen ... '	
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

	#bind orperatio may faild, this prot is in userd by other program.
	# kill -9 'fuser -n tcp 6000'
	sock.bind('', port)
	print"bind server's port:",SERVER_PROT

	sock.listen(1)		
	print'server is listening ...')
	return sock
		



###########################################
# create log file
#
def createLogFile( file_name )
	if os.path.isfile(file_name) :
		log_name = 'Gsm_log_' + str( datetime.datetime.now() )
		log_file = open( log_name , 'w' )
		print"Sorry,file %s is alredy exit, auto create a new file:%s"%(file_name, log_name )
	else
		log_file = open( file_name )
		print"create log file: ",log_file.name
	return log_file

##################################################################################################
if _name__=='__main__':
	print'-'*80
	print"This script is to listen tcp port, is connet to GSm"
	print"[Server Node]"
	print'-'*80


	TCP_PORT = 6000 #TCP connection port
	success_num = 0

	log = createLogFile("server_log.txt")
	sock = listenServer( TCP_PROT )



	#accept connection from GSM
	(connection, address) = sock.accept()
	line="accept connection form client address:%s\n" %address
	print line
	log.write( line )
	log.flush
	#now,connection is established, send welcom mesg to client.
	connection.send("Welcome to connet tusion's server"+u"\r\n")

	#endless cycle to recevie data.
	while True:
		try:
			#received msg from client
			recv_data = client.recv(1024)
			success_num += 1
			line = "[%d] Received data:%s\n"%(success_num,recv_data)
			print line
			log.write( line )
			log.flush
			print"Wait for next message."
		finally:
			#clean up connection
			connection.close()
			line = "close connection\n"
			print line
			log.write(line)
			log.flush()
			log.close()
	connection.close()
	log.flush()
	log.close()






