#!/usr/bin/python
#Filename: cat.py

import sys
import os

def read_file( filename ):
	f = file( filename )
	while True:
		line = f.readline()
		if len(line) == 0:
			break
		print line
	f.close()


print 'os name:', os.name
#script starts with some attributes
if len( sys.argv ) < 2:
	print ' error, usage: cat.py file1 file2 ...'
	sys.exit()

if sys.argv[1].startswith( '--' ):
	option = sys.argv[1][2:]
	if option == 'version':
		print 'Inittial version: 0.1'
	elif option == 'help':
		print '''\
				this is a program to show file, like
				--version
				--help
			  '''
	else:
		print 'Unknown option.'
		sys.exit()
else:
	for filename in sys.argv[1:]:
		read_file( filename )
