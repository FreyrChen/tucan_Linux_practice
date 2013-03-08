#!/usr/bin/python
#Filename: practice1.py

number = 23
x = 9
y = 10


condition = True

def say_hello():
	print 'hello world!'


def max( a, b):
	if a>b :
		print a, 'is maximum'
	else:
		print b, 'is maximum'


say_hello() #call the function
max( x, y)

print '==================================================================='
#list
shop_list = ['apple', 'milk', 'paper', 'beaf']
print 'I have', len(shop_list), 'items to shop'
print 'They are:'
for item in shop_list:
	print item

print'\nadd some items in the list'
shop_list.append('bread')
print'shop list now is', shop_list;

shop_list.sort()
print'shop list is sort, now is :',shop_list

print'the first thing in list is:', shop_list[0]

del shop_list[0]
print 'delet the item0, now list is:', shop_list


print '==================================================================='
#yuan zu

s = ('a', 'b', 'f')
age = 27
name = 'tusion'
print '%s is %s years old' % (name, age)
print '%s use python today'% name


print '==================================================================='
#diaray
dic = { 'tusion' : '27',
		'alan'   : '23',
		'alivan' : '26'
	 }
print 'tusion\'s age is %s' % dic['tusion']

print 'add item in the dic'
dic['bob'] = '18'
print 'there are %s items' % len(dic),dic,

print '\ndel item in dic '
del dic['tusion']
print 'now, there are %s items' % len(dic), dic

print 'print all items in the dic'
for name, age in dic.items():
	print 'name: %s, age:%s' %(name,age)

if 'bob' in dic:
	print 'bob is sure in dic, bob age is %s' % dic['bob']


print '==================================================================='


print '==================================================================='


print '==================================================================='
while condition:
	guess= int( raw_input( "please guess number, enter a number:") )
	
	if guess == number:
		print 'Congratulations, you got it!'
		condition = False
	elif guess < number:   #if ... elif ... else
		print 'No, it is larger than ' , guess
	else:
		print 'No, it is lower than ', guess
else:
	print 'The while loop is over'

print 'Done'

print '====================================================================='
print 'scan the local host'
import os

result = os.system('ping www.baidu.com -c 1')
print result
if result==0:
	print 'ping sucess!'
else:
	print 'ping fail'

#from scapy import *
#conf.verb=0
#arping("192.168.1.*")

import sys

print 'The command line arguments are:'
for i in sys.argv:
	print i
print '\n\nThe python path is',  sys.path



