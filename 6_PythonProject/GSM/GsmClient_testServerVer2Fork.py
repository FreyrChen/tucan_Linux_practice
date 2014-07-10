#!/usr/bin/python
# -*- coding=utf-8 -*-

import sys
import os
import time,datetime
import socket
import random

import re,urllib2
import threading


MAX_THREAD_NUM = 10
MAX_LOOP = 50
LOOP_DELAY = 0.001

#SERVER_IP ="tusion.jios.org" 
SERVER_IP   = "114.215.238.215" 
SERVER_PORT = 6000
today_str = time.strftime('%Y%m%d')
now_str = time.strftime('%H%M%S')

success_num = 0
error_num = 0
span_max = 0
span_min = 65536




########################################################
def getExternalIP():
	#print'-'*40
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
	# lsof -i:6000
	# netstat -an | wc -l
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
	#print '-'*40
	#print 'Initial to connect  server. '	
	sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

	#bind orperatio may faild, this prot is in userd by other program.
	# kill -9 'fuser -n tcp 6000'
	#print"Connect server: %s, port:%d"%(address,port)
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


########################################################
class testThread( threading.Thread ):
		
	
	#constructor function
	def __init__( self, thread_name, IP ):
		threading.Thread.__init__(self)
		self.test_count = 0
		self.IP = IP

	def run( self ):
		
		global success_num 
		global error_num
		global span_max
		global span_min

		TCP_PORT = 6000 #TCP connection port
		success_num = 0
	
		#log_name ='GsmClientLog_' + today_str + '_' + now_str + '.txt'
		#log = createLogFile( log_name )
		
		
		#getIPFromDNS("http://tusion.jios.org/")
	
		line ="Client's external IP : %s"%self.IP
		#print line
		#log.write( line + '\n')
		sock = connectToServer( SERVER_IP, SERVER_PORT)
	
	
		for i in range(  MAX_LOOP ): 
			send_int = random.randint(0,1000)
			send_mesg = "%d"%send_int
			start_time = time.time()
			sock.sendall(send_mesg )
	
			#log_mesg = '[Send to %s:%s]: %s' %(SERVER_IP, SERVER_PORT, send_mesg)
			#print log_mesg
	
			receive_data = sock.recv(1024)
			span_time = time.time() - start_time

			# lock varaibles shared in some threads.
			lock.acquire() 
			if   send_int == (int)(receive_data) :
				success_num += 1
			else:
				error_num += 1
			
			if (span_time > span_max) :
				span_max = span_time
			if (span_time < span_min) :
				span_min = span_time
			
			lock.release()

			time.sleep(LOOP_DELAY)
		
		sock.close()
	
##################################################################################################
if __name__=='__main__':
	print'*'*80
	print"This script is to listen tcp port, is connet to GSm"
	print"[Client Node]"
	print''
	
	IP = getExternalIP( )
	start_time = time.time()

	lock = threading.RLock()
	#store all thread object
	thread_list = []
	for x in xrange(0, MAX_THREAD_NUM ):
		thread_list.append( testThread( "Thread" + str(x), IP ) )
	
	print"Start thread number: %d, sending ... "%len(thread_list)
	for t in thread_list:
		t.start()
	
	for t in thread_list:
		t.join()


	print "-"*80
	print"response time min:%s, max:%s"%(span_min,span_max)
	print"Total success_num:%s, error_num : %s"%(success_num, error_num)
	print''
