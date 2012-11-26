#!/usr/bin/python
#Filename: folder_backup.py

import os
import time

# the files and directionaries to be backed up are specified in  in  the list
#source = ['/home/tusion/SambaShare/PythonProject', '/home/tusion/SambaShare']
source = ['/home/tusion/SambaShare/PythonProject']
# If you are using Windows, use source = [r'C:\Documents', r'D:\Work'] or something like that

target_dir = '/home/tusion/SambaShare/'

target = target_dir + time.strftime('%Y%m%d%H%M%S') + ".zip"

zip_command = " zip -qr '%s' %s " % ( target, ''.join(source))

if os.system( zip_command ) == 0:
	print "Successful backup to",target
else:
	print 'failed to backup!'
