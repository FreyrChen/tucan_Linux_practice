#!/usr/bin/python
# -*- coding=utf-8 -*-

import sys
import os
import time,datetime
import socket

import re,urllib2


#SERVER_IP ="123.116.98.89" 
SERVER_IP ="tusion.jios.org" 

########################################################

########################################################
def getExternalIP():
	print'-'*40
	print"Get host external IP ..."
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

#####################################################
def getIPFromDNS( url ):
	result = socket.getaddrinfo( url, 'http') 
	IP = result[0][4]
	print "Parse server IP:%s"%IP


###################################################
# Establish tcp connection to client,
# return client.
#
def listenServer( port ):
	print '-'*40
	print 'Initial server to listen ... '	
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

	#bind orperatio may faild, this prot is in userd by other program.
	# kill -9 'fuser -n tcp 6000'
	sock.bind( ('', port) )
	print"bind server's port:",port

	sock.listen(1)		
	print'server is listening ...'
	return sock

###################################################
# Establish tcp connection to client,
# return client.
#
def connectToServer( address, port):
	print '-'*40
	print 'Initial to connect  server. '	
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

	#bind orperatio may faild, this prot is in userd by other program.
	# kill -9 'fuser -n tcp 6000'
	print"Connect server: %s, port:%d"%(address,port)
	sock.connect( (address, port ) )

	return sock
		


		



###########################################
# create log file
#
def createLogFile( file_name ):
	if os.path.isfile(file_name) :
		log_name = 'Gsm_log_' + str( datetime.datetime.now() )
		log_file = open( log_name , 'w' )
		print"Sorry,file %s is alredy exit, auto create a new file:%s"%(file_name, log_name )
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


	TCP_PORT = 6000 #TCP connection port
	success_num = 0

	log = createLogFile("client_log.txt")
	
#	LocalIP = getLocalIP()
	IP = getExternalIP( )
	
	#getIPFromDNS("http://tusion.jios.org/")

	line ="Client's external IP : %s"%IP
	print line
	log.write( line )
	sock = connectToServer( SERVER_IP, 6000)

	'''
	welcome_mesg = sock.recv(1024)
	line = "[Server]:%s"%welcome_mesg
	print line
	log.write(line)
	log.flush()
	'''

	for i in range( 1,10 ): 
		success_num += 1
		send_mesg = "send mesg: client num %d"%success_num 
		print send_mesg
		log.write( send_mesg )
		log.flush()
		#sock.send(send_mesg )
		sock.sendall(send_mesg )

		time.sleep(1)

		receive_data = sock.recv(1024)
		line = "[Server %s:%s mesg:]%s"%(SERVER_IP, 6000, receive_data)
		print line
	
	log.flush()
	log.close()
	sock.close()






