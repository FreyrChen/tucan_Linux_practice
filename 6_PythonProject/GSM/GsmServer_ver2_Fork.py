#!/usr/bin/python
# -*- coding=utf-8 -*-
'''
# this is for sever node, received all data from client node.
# used: fork subprocess for client connection
#	use lock for subprocess read and write same file
# client node maybe a gsm device, network is not perfect
'''
import sys
import os
import signal
import time,datetime
import socket
import fcntl 	# fork process read or write same file's lock
import traceback
import re,urllib2


########################################################
#netstat -an| grep '6000'|wc -l
TCP_PORT = 6000 #TCP connection pord
MAX_LISTEN_CLIENT = 1024 # the number is not actual client no.
RECEIVED_PACKET_SIZE = 2048  #define every tcp packet size, maybe large than 1024
SOCKET_TIME_OUT = None #60S time out

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
	sock.settimeout( SOCKET_TIME_OUT )

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

	sock.listen(MAX_LISTEN_CLIENT)		
	print'server is listening ...'
	return sock
		

######################################################################

def writeLogfile( log_fd,log_fo, data ):
	fcntl.flock( log_fd,fcntl.LOCK_EX)
	records = []

	try:
		log_fo.write( data+"\n")
		log_fo.flush()
	finally:
		#release the file lock
		fcntl.flock( log_fd, fcntl.LOCK_UN)	

###########################################
########################################################
def reap():
	''' collect any waitting child process, (zombie process)'''
	while True:
		try:
			result = os.waitpid( -1, os.WNOHANG )
			if not result[0]:
				break
		except:
			break
		#print"Reaped child process pid %d",resuld[0]
################################################################
#parent kill alll zombin child proccess
#signal.signal( signal.SIGCHLD, childHandler)

# use system signal to process zombin child process
def childHandler( signum, stackframe ):
	''' run in parent process, called whenever a child terminates.'''
	while True:
		try:
			result = os.waitpid( -1, os.WNOHANG)
			if not result[0]: 	#if pid=0, then do nothing.
				break
		except:
			break
		print"reaped child proccess, pid=%d"%result[0]
##################################################################################################
if __name__=='__main__':
	print'-'*80
	print"This script is to listen tcp port, is connet to GSm"
	print"[Server Node]"
	print'-'*80

	success_num = 0
	
	# create log file
	log_name = 'Log_' + today_str + '_' + now_str + '.txt'
	if os.path.isfile( log_name) :
		log_name = log_name + "_new"
	#Create or open the log file,get log file descripter 
	log_fd = os.open( log_name, os.O_RDWR|os.O_CREAT)
	#get log file object
	log_fo = os.fdopen( log_fd,'w+' )
	print"create log file: ",log_name
	#log.write( line+'\n' )
	#log.flush()

	IP = getExternalIP( )
	line ="Server's external IP : %s"%IP
	print line

	#socket -> bind -> listen
	sock = listenServer( TCP_PORT)

	#endless cycle to recevie data.
	while True:
		#accept connection from GSM
		print
		print'-'*40
		print"Server IP:%s, port:%s"%(IP,TCP_PORT)
		print"Wait for new client to connect ... "

		try:
			(connection, address) = sock.accept()
			line="accept connection form client address:%s:%s"%address
			#line="accept connection form client "
			print line
			writeLogfile( log_fd, log_fo, line)
		except KeyboardInterrupt:
			raise
		except:
			traceback.print_exc()
			continue	#paren exit, wait for new connction.
		
		#clean up old children, maybe a zobime process
		# once new clinet connect server, then clean up last in zombie child proccess.
		reap()
		#Fork new children process for this connection
		try:
			pid = os.fork()
		except:
			print"Fork new process failed"
			connection.close()
			continue
		
		if pid:
			#paren process
			connection.close()	#close the child used socket connection
			continue
		else:
			#child process
			sock.close()		#close paren's socket			
			child_pid = os.getpid()
			try:
				print"New process for client: %s, pid=%s"%(address, child_pid )
				while True:
					try:
						#received msg from client
						recv_data = connection.recv(RECEIVED_PACKET_SIZE)
					except timeout:
						break
					#when a recv returns 0 bytes, 
					#it means the client side has closed the connection.
					if not recv_data:
						break
					else:
						line = "[%s:%s], pid:%s, mesg:%s"%\
						(address[0], address[1], child_pid, recv_data)
						print line
						writeLogfile( log_fd, log_fo,line)
						#sever echo received data to client, just for test
						#connection.sendall( recv_data )

						command = "AT+SRGPS\r\n"
						line = "Send command: %s"%command
						writeLogfile( log_fd, log_fo, str(line))
						connection.sendall( command )
						

			except( KeyboardInterrupt, SystemExit ):
				raise
			except:
				traceback.print_exc()

			try:
				connection.close()
				#log_fo.close()
			except KeyboardInterrupt:
				raise
			except:
				traceback.print_exc()
		
			sys.exit(0)
'''
	sock.close()
	line = "close socket connection to client "
	print line
	log.write( line + '\n')
	log.flush()
	log.close()

'''



