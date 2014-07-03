#!/usr/bin/python
# -*- coding=utf-8 -*-

'''
	this is a client to MQTT server
	reference: http://mosquitto.org/documentation/python/
	2014/07/03
'''
import sys
import mosquitto

SERVER_IP = "114.215.238.215"
CLIENT_ID = "x60s"
TOPIC = "52youche/tusion/mqtt"
QOS = 0

#################################################################

# mosquitto connect callback function defines 
def on_connect( mosq, obj, rc ):
	connect_dict ={
				'0': "Connect scucessfully",
				'1': "Refused, unacceptable protocol version",
				'2': "Refused, identifier rejectd",
				'3': "Refused, server unavailable",
				'4': "Refused, bad user name or password",
				'5': "Refused, not authorised" 
	}
	if str(rc) in connect_dict:
		print  connect_dict[ str(rc) ] 
	else:
		print "callback function on_connect() error"

def on_connect_test() :
	for i in range(0,5):
		on_connect( 0, 0, i )


# mosquitto disconnect callback functions define
def on_disconnect( mosq, obj, rc ):
	print("Disconnected successfully.")

# mseg callback
# msg.mid - the integer message id
# msg.topic 
# msg.payloadlen 
# msg.layload
# msg.qos
# msg.retain
def on_message( mosq, obj, msg ):
	print msg
	print( "Received: [mid]" + str(msg.mid) +", [topic]"+ msg.topic +\
	", [Qos]" + str(msg.qos) + ", [mesg]" + msg.payload )


#subcribe callback
def on_subscribe( mosq, obj, mid, qos_lis ):
	print("Subscribe: [mid]" + str(mid) )

#unsubscribe callback
def on_unsubscribe( mosq, obj, mid ):
	print("Unsubscribe: [mid]" + str(mid) )

######################################################################

if __name__=='__main__':
	
	if len(sys.argv)< 2: 	#not input any arttribute
		print "mqtt client default seting:\n [client id]: %s\n [topic]: %s,\n [server ip]:%s\n"\
		%(CLIENT_ID, TOPIC, SERVER_IP)
	elif sys.argv[1].startswith('-'):
		option = sys.argv[1][1:]
		if option == 'c': #config client
			CLIENT_ID = sys.argv[2]
		print "mqtt client default seting:\n [client id]: %s\n [topic]: %s,\n [server ip]:%s\n"\
		%(CLIENT_ID, TOPIC, SERVER_IP)
		#if option == 't'

	else:
		print "Usage: ./***.py -c [client id]  "
		sys.exit()

	################################################################################
	#create a mqtt client object
	#client = mosquitto.Mosquitto( client_id, clean_session=True, obj=None )
	client = mosquitto.Mosquitto( CLIENT_ID, False,None )


	#config mosquitto client callback funtions
	client.on_connect = on_connect
	client.on_disconnect = on_disconnect
	client.on_message = on_message
	client.on_subscribe = on_subscribe
	client.on_unsubscribe = on_unsubscribe

	#connect to server, if this method successful then it returns 0.
	#client.connect( hostname, port=1883, keepalive=60 )
	client.connect( SERVER_IP )
	
	
	
	
	#client.publish( topic, payload=None, qos=0, retain=false )
	#client.publish( "my/topic", "hello world", 1 )
	
	#client.subscribe( topic, qos )
	client.subscribe(TOPIC, QOS )
	
	while True:
		'''
		if( raw_input() == "exit" ):
			#disconnect to server broker.
			client.disconnect()
			exit()
		'''

		#loop method called freqently.
		#  0: to return immediately
		# -1: to return use default value of 1 second.
		# if successful, retrun 0.
		#client.loop( timeout = -1 )
		client.loop()
