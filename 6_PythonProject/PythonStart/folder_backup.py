#!/usr/bin/python
#Filename: folder_backup.py

import os
import time

# the files and directionaries to be backed up are specified in  in  the list
#source = ['/home/tusion/SambaShare/PythonProject', '/home/tusion/SambaShare']
#source = ['/home/tusion/SambaShare/PythonProject']
source = ['/var/www/wordpress', '/var/www/sina_web']
# If you are using Windows, use source = [r'C:\Documents', r'D:\Work'] or something like that

target_dir = '/home/tusion/backup/'

today = time.strftime('%Y%m%d')
now = time.strftime('%H%M%S')

#add some comment at file name
comment = raw_input('enter comment--->')
target = comment.replace(' ', '_')
if len(comment) == 0:
	target = target_dir + today + os.sep + today + now +'.zip'
else:
	target = target_dir + today + os.sep + today + now + '_' +\
	target + '.zip'
	#replace blank characters in file name

#target = target_dir + time.strftime('%Y%m%d%H%M%S') + ".zip"
if not os.path.exists(target_dir + today):
	os.mkdir( target_dir + today )
	print ' success creat todya\'s directory', today
#os.sep is a system divider, in linux is'/', in wimdows is '\\'
zip_command = " zip -qr '%s' %s " % ( target, ' '.join(source))
print 'zip_command is:', zip_command


if os.system( zip_command ) == 0:
	print "Successful backup to",target
else:
	print 'failed to backup!'
