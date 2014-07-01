#!/usr/bin/python
# -*- coding=utf-8 -*-
'''
# this is for sever node, received all data from client node.
# client node maybe a gsm device, network is not perfect
'''
import sys
import os
import time,datetime
import socket

import re,urllib2


########################################################

TCP_PORT = 6000 #TCP connection pord
RECEIVED_PACKET_SIZE = 2048  #define every tcp packet size, maybe large than 1024

today_str = time.strftime('%Y%m%d')
now_str = time.strftime('%H%M%S')

########################################################
def getExternalIP():
	print'-'*40
	print"Get server's IP ..."
	site_lsit = [ "http://www.whereismyip.com/",
					"http://whatismyipaddress.com/"]
	for i in site_lsit:
		print"vist: %s"%i
		ip_site= urllib2.urlopen( i )
		if i == ip_site.geturl():
			html = ip_site.read()
			ExternalIP = re.search('\d+\.\d+\.\d+\.\d+', html).group(0)
			print 'get IP: %s'%ExternalIP
			return ExternalIP
		else:
			print"site can not reach"
			continue





###################################################
# Establish tcp connection to client,
# return client.
#
def listenServer( port ):
	print '-'*40
	print 'Initial server to listen ... '	
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

	#bind orperatio may faild, this prot is in userd by other program.
	# lsof -i:6000
	# kill -9 PID
	# kill -9 'fuser -n tcp 6000'
	try:
		sock.bind( ('', port) )
		print"bind server's port:",port
	except socket.error , msg:
		print'Bind failed, Error code: ' + str(msg[0])+'Message:'+msg[1]
		sys.exit()

	sock.listen(10)		
	print'server is listening ...'
	return sock
		



###########################################
# create log file
#
def createLogFile( file_name ):
	if os.path.isfile(file_name) :
		log_file = open( file_name , 'w' )
		print"Sorry,file %s is alredy exit, auto create a new file:%s"%(file_name, file_name)
	else:
		log_file = open( file_name,'w' )
		print"create log file: ",log_file.name
	return log_file

##################################################################################################
if __name__=='__main__':
	print'-'*80
	print"This script is to listen tcp port, is connet to GSm"
	print"[Server Node]"
	print'-'*80


	success_num = 0

	log_name = 'GsmServerLog_' + today_str + '_' + now_str + '.txt'
	log = createLogFile(log_name)
	
#	LocalIP = getLocalIP()
	IP = getExternalIP( )
	line ="Server's external IP : %s"%IP
	print line
	log.write( line+'\n' )
	sock = listenServer( TCP_PORT)



	#endless cycle to recevie data.
	while True:
		#accept connection from GSM
		print
		print'-'*40
		print"Server IP:%s, port:%s"%(IP,TCP_PORT)
		print"Wait for new client to connect ... "
		(connection, address) = sock.accept()
		line="accept connection form client address:%s:%s"%address
		#line="accept connection form client "
		print line
		log.write( line+'\n' )
		log.flush

		#now,connection is established, send welcom mesg to client.
		#connection.send("Welcome to connet tusion  server")
		#connection.sendall("Welcome to connet tusion  server")

		while True:
			#received msg from client
			recv_data = connection.recv(RECEIVED_PACKET_SIZE)

			if not recv_data:
				break
			else:
				success_num += 1
				line = "[Reveived] %d (%s:%s):%s"%(\
				success_num,address[0],address[1],recv_data)
				print line
				log.write( line+"\n" )
				log.flush

				send_data = "Server got it, next ..."
				connection.sendall( send_data )
				line = "[Send]%d: %s"%(success_num, send_data )
				print line
				log.write( line + '\n')
				log.flush
		connection.close()
	sock.close()
	line = "close socket connection to client "
	print line
	log.write( line + '\n')
	log.flush()
	log.close()






