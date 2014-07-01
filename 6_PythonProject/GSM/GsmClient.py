#!/usr/bin/python
# -*- coding=utf-8 -*-

import sys
import os
import time,datetime
import socket

import re,urllib2


#SERVER_IP ="tusion.jios.org" 
SERVER_IP   = "114.215.238.215" 
SERVER_PORT = 6000

today_str = time.strftime('%Y%m%d')
now_str = time.strftime('%H%M%S')


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
		#log_name = 'Gsm_log_' + str( datetime.datetime.now() )
		new_file_name ='GsmLog' + '_' + today_str + '_' + now_str + '.txt'
		log_file = open( new_file_name , 'w' )
		print"Sorry,file %s is alredy exit, auto create a new file:%s"%(file_name, new_file_name )
	else:
		log_file = open( file_name,'w' )
		print"create log file: ",file_name
	return log_file

##################################################################################################
if __name__=='__main__':
	print'-'*80
	print"This script is to listen tcp port, is connet to GSm"
	print"[Server Node]"
	print'-'*80


	TCP_PORT = 6000 #TCP connection port
	success_num = 0

	log_name ='GsmClientLog_' + today_str + '_' + now_str + '.txt'
	log = createLogFile( log_name )
	
#	LocalIP = getLocalIP()
	IP = getExternalIP( )
	
	#getIPFromDNS("http://tusion.jios.org/")

	line ="Client's external IP : %s"%IP
	print line
	log.write( line + '\n')
	sock = connectToServer( SERVER_IP, SERVER_PORT)


	for i in range( 1,100 ): 
		success_num += 1

		send_mesg = "client num %d"%success_num 
		#sock.send(send_mesg )
		sock.sendall(send_mesg )

		log_mesg = '[Send to %s:%s]: %s' %(SERVER_IP, SERVER_PORT, send_mesg)
		log.write( log_mesg + '\n' )
		log.flush()
		print log_mesg

		receive_data = sock.recv(1024)
		log_mesg = "[Received]: %s"%( receive_data)
		log.write( log_mesg + '\n' )
		log.flush()
		print log_mesg

		time.sleep(1)
	
	sock.close()
	log_mesg = "close socket connection to server."
	log.write( log_mesg + '\n' )
	log.flush()
	log.close()






