#!/usr/bin/python
#coding=utf-8

import sys, socket
import time, datetime
import MySQLdb

'''
# get host ip from web sites
'''
host_name = "tusion.jios.org"
ip_result = socket.getaddrinfo( host_name, None,0, socket.SOCK_STREAM )
host_ip=ip_result[0][4][0]

print"Host:%s ip: %s" %( host_name, host_ip)




def connectDB(DB_host=host_ip, DB_user='root', DB_passwd='qinghe@^)', DB='ds18b20_db'):
    #connect database 
    print "intial connect database ... "
    try:
        db = MySQLdb.connect(
                host = DB_host,
                user = DB_user,
                passwd = DB_passwd,
                db = DB )
        #python 与数据库的链接用的是事物模式，如果没有这一句，每次执行都要执行commit
        db.autocommit(True)
    except Exception,e:
		print e
		exit(0) #如果数据库连接出错，程序直接全部退出，不要再执行后面的内容
    cursor = db.cursor()
    return cursor,db

def executeDB( cursor,db,command ):
    print '-----------------------------------------------'
    print '[execute command]: ', command
    try:
        cursor.execute( command )
        result = cursor.fetchall()
        print result
    except db.error,e:
        print e


def processDB( cursor, db):
    #use datetime to get wall,  time.clock() is not correct
    print '-----------------------------------------------'
    start_time = datetime.datetime.now()
    print 'start to process database, start time is: ', start_time

    try:
        count = cursor.execute('select * from sensor_data')
        print 'table sensor_data has %s rows record' %count
    except Excepton,e:
        print e

    except Excepton,e:
        print e
    result = cursor.fetchall()
    print 'result has %d row.' %len(result)
    row = len(result)

    print '**********************************'
    print 'find sensor data\'s counter item is unconsist record.'
    unconsist_id_list = []
    for i in range(1, row):
        if result[i][2] != result[i-1][2] + 1 :
            unconsist_id_list.append( result[i][0] )
    print 'The number of unconsist item is: ',len(unconsist_id_list)
    if len(unconsist_id_list)>=1 :
        print 'for example: ',result[unconsist_id_list[0]-2],  result[unconsist_id_list[0]-1 ]
    time_stamp1 = datetime.datetime.now()
    interval1 = time_stamp1 - start_time
    print 'time cost: ', interval1



	
if __name__=='__main__':

    command_show_tables = "show tables"
    command_show_datastruct = "desc sensor_data"
    command_show_last_items = "select * from sensor_data order by id DESC limit 10"

    cursor,db = connectDB()
    executeDB( cursor, db, command_show_tables )
    executeDB( cursor, db, command_show_datastruct )
    executeDB( cursor, db, command_show_last_items )

    processDB( cursor, db )

    cursor.close()
    db.close











'''
mysql> select * from sensor_data order by id DESC limit 10;
+-------+----------------------------+---------+------+-------+-------+-------+---------+-----+
| id    | time                       | counter | node | temp1 | temp2 | temp3 | humidty | PIR |
+-------+----------------------------+---------+------+-------+-------+-------+---------+-----+
| 18968 | 2013-12-30 19:51:23.984292 |   12333 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18967 | 2013-12-30 19:51:22.792137 |   12332 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18966 | 2013-12-30 19:51:21.601219 |   12331 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18965 | 2013-12-30 19:51:20.407052 |   12330 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18964 | 2013-12-30 19:51:19.214127 |   12329 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18963 | 2013-12-30 19:51:18.022087 |   12328 |    1 | 25.06 |  0.00 | 25.00 |   33.00 |   0 |
| 18962 | 2013-12-30 19:51:16.831034 |   12327 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18961 | 2013-12-30 19:51:15.638994 |   12326 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18960 | 2013-12-30 19:51:14.445945 |   12325 |    1 | 25.12 |  0.00 | 25.00 |   33.00 |   0 |
| 18959 | 2013-12-30 19:51:13.252898 |   12324 |    1 | 25.06 |  0.00 | 25.00 |   33.00 |   0 |
+-------+----------------------------+---------+------+-------+-------+-------+---------+-----+

mysql> desc sensor_data;
+---------+------------------+------+-----+---------+----------------+
| Field   | Type             | Null | Key | Default | Extra          |
+---------+------------------+------+-----+---------+----------------+
| id      | int(10) unsigned | NO   | PRI | NULL    | auto_increment |
| time    | tinytext         | NO   |     | NULL    |                |
| counter | int(10) unsigned | NO   |     | NULL    |                |
| node    | tinyint(4)       | NO   |     | NULL    |                |
| temp1   | float(4,2)       | NO   |     | NULL    |                |
| temp2   | float(4,2)       | NO   |     | NULL    |                |
| temp3   | float(4,2)       | NO   |     | NULL    |                |
| humidty | float(4,2)       | NO   |     | NULL    |                |
| PIR     | tinyint(1)       | NO   |     | NULL    |                |
+---------+------------------+------+-----+---------+----------------+
9 rows in set (0.00 sec)

'''

