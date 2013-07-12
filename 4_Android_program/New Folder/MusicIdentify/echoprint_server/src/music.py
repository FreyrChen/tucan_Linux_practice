#!/usr/bin/python
# -*- coding=utf-8 -*-

import pygame
import sys
import os
import datetime
import socket
import threading
import time


def detectMp3Files( dir ):
    mp3_files = []
    for file in os.listdir(dir):
        if  file.split(".")[-1] == 'mp3':
            mp3_files.append( file )
    return mp3_files
 
class player( threading.Thread ):
    def __init__(self, dir, mp3_file, start_time, duration, ):
        threading.Thread.__init__(self)
        #initial for music player
        pygame.init()
        pygame.mixer.init()
        self.dir = dir
        self.mp3_file  = mp3_file
        self.start_time = start_time
        self.duration = duration
        self.thread_stop = False
        pygame.mixer.music.load( os.path.join(dir, file)  )
    
    def run(self ):
        while not self.thread_stop:
            #print 'thread play:%s, start: %s s, duration: %s s'%(self.mp3_file, self.start_time, self.duration)
            if not pygame.mixer.music.get_busy():
                pygame.mixer.music.play( 0, self.start_time )
                pygame.time.delay( self.duration * 1000)

            #time.sleep( self.time)        
    def stop( self):
        pygame.mixer.music.stop()
        self.thread_stop = True

           
################### main ################################################
 
if __name__ == '__main__':
      
    dir = r"/home/tusion/music_fp/test_files"
    txt = "/home/tusion/music_fp/test_files.txt"
    
    START_TIME = 10  # start at 10s
    PLAY_TIME = 30  #play 30 s
    id = 0
    SERVER_PORT = 6000
    
    success_num = 0;
    
    
    #record the test process in log file: result.txt
    log = open(str(datetime.datetime.now()) + 'result.txt','w')
    print "create a log file: ", log.name
    '''
    #initial for music player
    pygame.init()
    pygame.mixer.init()
    #wait for all init established
    pygame.time.delay(1000) 
    '''

    mp3_files = detectMp3Files( dir )
    #log.write( "get dir: %s,  total mp3 num: %d\n", dir, len(mp3_files) )
    print >> log, "get dir: %s,  total mp3 num: %d\n"%( dir, len(mp3_files) )
    print "get dir: %s,  total mp3 num: %d"%( dir, len(mp3_files) )
    
    
    print 'initial server'
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #if can not bind, prot already in use, use command
    # kill -9 `fuser -n tcp 6000`
    server.bind(('', SERVER_PORT) )
        
    #waitting queue as 1 connect at one time
    server.listen(1)
    print 'server start to listening....'
    
    #accept connection form android
    (client, addr) = server.accept()
    print 'accept connection from android'
    
    client.send("welcome to connect test server"+u"\r\n")
    
    for file in mp3_files:
        play_thread = player(dir, file, START_TIME, PLAY_TIME)
        #receive data; phone connect
        data = client.recv(1024) 
        print ('new cycle: %s ' %data)
        if 'android ready to next song' in data: 
            id += 1
            client.send( str(id) +",play song, "+ file + u"\r\n")
            print str(id) + ',send to android: play song:' + file 
            starttime = datetime.datetime.now()
            play_thread.start()
        else:
            client.send('wait for android ready.')
        
        #receive data: json string
        data = client.recv(1024) 
        print ('result from android: ' + str( data ))
 
               
        if 'songid' in data:
            success_num = success_num +1;
            print 'got one sucess!!!!'
        
        log.write(  'sucess num: ' +str(success_num) + '\n' );
        log.flush() 
            
        if 'retcode' in data: 
            #print"retcode in received json string"
            play_thread.stop()
            client.send( str(id) +",complete cycle,song, "+ file + u"\r\n")  
            endtime = datetime.datetime.now()
            interval=(endtime - starttime).seconds  
            
            log.write( str(id) +', ' + file + ",start at " + str( START_TIME)
                     + " s, last time, " + str(interval) + 's\n  ' + str(data) )  
            log.flush()
            print str(id) +': ' + file + ",start at " + str( START_TIME)+ " s, last time: " + str(interval) + 's'                    
        else:  
            print ('get wrong json string form android %s' %data)
            #client.send( str(id) +",complete cycle,song, "+ file + u"\r\n") 
        print ('sucess num: ' + str(success_num))
        
        if( id > 500 ):
            break
    #finished all test 
    log.write('finished test ' + str(id) + 'songs \n')
    log.flush();
    log.close()   
    
    client.close()                     