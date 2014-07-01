#!/usr/bin/python
# -*- coding=utf-8 -*-

import sys
import os
import datetime,time
import socket

import re,urllib2


########################################################

########################################################
def getExternalIP():
	#print'-'*40
	#print"Get server's IP ..."
	site_lsit = [ "http://www.whereismyip.com/",
					"http://whatismyipaddress.com/"]
	for i in site_lsit:
		#print"vist: %s"%i
		ip_site= urllib2.urlopen( i )
		if i == ip_site.geturl():
			html = ip_site.read()
			ExternalIP = re.search('\d+\.\d+\.\d+\.\d+', html).group(0)
			#print 'get IP: %s'%ExternalIP
			return ExternalIP
		else:
			print"site can not reach"
			continue







###########################################
# create log file
#
def createLogFile( file_name ):
	if os.path.isfile(file_name) :
		log_name = 'IPChangeLog__'+ str( datetime.datetime.now() ) + '_.txt'
		log_file = open( log_name , 'w' )
		print"Sorry,file %s is alredy exit, auto create a new file:%s"%(file_name, log_name )
	else:
		log_file = open( file_name,'w' )
		print"create log file: ",log_file.name
	return log_file

##################################################################################################
if __name__=='__main__':
	print'-'*80
	print' This is to supvior tusion.jios.org IP change '
	print'-'*80

	print"[run in back]: nohup command > myout.file 2>&1 &"
	print" nohup ./recordIPChange.py > IP_python_output.txt 2>&1 &"
	print" ps -e | grep recordIPChange"
	print" kill 7889"
	init_flag = 0
	chang_flag = 0
	success_num = 0

	while True:
		if init_flag == 0:
			log = createLogFile("IPChangeLog.txt")
	
			Last_IP = getExternalIP( )
			init_flag = 1
		else:
			try:
				New_ip = getExternalIP()
			except:
				New_ip = "Error,can not get ip"
			success_num += 1
			if New_ip != Last_IP:
				chang_flag = 1
			else:
				chang_flag = 0
			
			line = "[%4d]: "%success_num + str( datetime.datetime.now()) +\
				", IP: %s, chang_flag= %d\n"%(New_ip,chang_flag)
			print line
			log.write( line )
			log.flush()
			Last_ip = New_ip
		time.sleep(40)

	log.flush()
	log.close()






