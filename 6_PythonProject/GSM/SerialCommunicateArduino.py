#!/usr/bin/python
#encoding=utf-8

import serial
import time,datetime
import json
import MySQLdb


print("================================================================")
print ( "time: " + time.strftime("%Y-%m-%d\t") )
print 'Initial serial port'

'''
 serial prot data examples:

'''

#connect mysql database
try:
    db = MySQLdb.connect(               
            host='localhost',
            user='root',
            passwd='root',
            db='ds18b20_db')
    db.autocommit(True)
except Exception, e:
    print e

cursor = db.cursor()

'''
#test mysql connection
sql = "select * from tempratures"
cursor.execute( sql )
alldata = cursor.fetchall()
if alldata:
    for rec in alldata:
        print rec[0], rec[1], rec[2], rec[3], rec[4], rec[5]
'''

ser = serial.Serial()
#ser.port = "/dev/ttyACM0"
ser.port = "/dev/ttyUSB0"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS 
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
#ser.timeout = 0

try: 
    ser.open()
except Exception , e:
    print "error open serial port:" + str(e)
    exit()

if ser.isOpen():

    try:
        ser.flushInput()
        ser.flushOutput() 
    
        numOfLines = 0
        while True:
            #sep = int( time.strftime("%S") % 10 )
            #if sep == 0 :
                #ser.write("hello,PC write time is : " + time.strftime("%Y-%m-%d %X \n") )
            #print("hello,PC write time is : " + time.strftime("%Y-%m-%d %X \n") )
            json_string = ser.readline()
            millis = datetime.datetime.now()
            #millis = datetime.datetime.now().isoformat()
            #detect the message is monitor info.
            if json_string.startswith('{"name": "monitor"'):
                decode_json = json.loads( json_string )
                # decode_json is a dict type

                node  = decode_json['FromNode']
                temp1 = decode_json['TempC'][0]
                temp2 = decode_json['TempC'][1]
                temp3 = decode_json['TempC'][2]
                counter = decode_json['Counter']
                hum = decode_json['Humd']
                PIR = decode_json['PIR']
                #sql = "insert into tempratures(id, time, counter, temp1, temp2, temp3) \
                #      values( NULL, '%s', %d, %f, %f, %f)" %( millis, counter, temp1, temp2,temp3)
                sql = "insert into sensor_data(id, time, counter, node, temp1, temp2, temp3, humidty, PIR) \
                      values( NULL, '%s', %d, %d, %f, %f, %f, %f, %d)" \
                      %( millis, counter, node, temp1, temp2, temp3, hum, PIR)
                try:
                    #cursor.execute('START TRANSACTION')
                    cursor.execute( sql )
                    #cursor.execute('commit')
                except db.error, e:
                    print e

                print"Counter:[%s] | Time:%s | Node: %d | t1:%2.2f | t2:%2.2f | t3:%2.2f | hum:%2.2f " \
                        %(decode_json['Counter'], datetime.datetime.now(),node,temp1, temp2, temp3, hum )
            #else:
            #    print( '[Error] '+ json_string );

            #print( type( json_string )  )

        ser.close()
        cursor.close()
    except Exception, e1:
        print "error communicating ... " +  str(e1)

else:
    print"can: not open serial port"
    
    
             
