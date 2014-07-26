#!/usr/bin/python 
#encoding=utf-8
# -*- coding: utf-8 -*-

import re
import urllib
import urllib2
#from urllib2 import Request, urlopen, URLError, HTTPError

URL_KJGG = "http://www.zhcw.com/ssq/kjgg/"
#--------------------------------------------------------------
#在双色球福利彩票网站的开奖公告页面中轮询出每一期的公告地址
def getAllKjggURL( priods ):

	#公告的第一页地址是：http://www.zhcw.com/ssq/kjgg/
	html = openWeb(URL_KJGG)
	if html:
		getEveryKjggURL( html )
	else:
		print'Error, html is empty, URL:', URL_KJGG

	#公告的最后一页地址是：http://www.zhcw.com/ssq/kjgg/index_56.shtml
	last_num = 56
	for i in range( 2, last_num ):
		web_url = URL_KJGG + 'index_'+str(i)+'.shtml'
		html = openWeb(URL_KJGG)
		if html:
			getEveryKjggURL( html )
		else:
			print'Error, html is empty, URL:', web_url


#--------------------------------------------------------------
def getEveryKjggURL( html ):
	if not html:
		print'input html is empty, return'
		return
	


#--------------------------------------------------------------
#获取指定地址的网页HTML，对异常有处理
def openWeb( URL ):
	user_agent = "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:23.0) \
	Gecko/20100101 Firefox/23.0"
	#header = { 'User-Agent' : user_agent }
	#wait 10s
	urllib2.socket.setdefaulttimeout(10) 
	request = urllib2.Request( URL ) 
	request.add_header('User-Agent', user_agent )
	try:
		response = urllib2.urlopen(request)
		#real_url = response.geturl()
		#print response.info()
		#print 'URL: ' + real_url
		html = response.read()
		return html
	except urllib2.URLError,e:
		if hasattr( e, 'reason'):
			print 'Failed to fetch to server.'
			print 'Reason: ', e.reason
		elif hasattr( e, 'code' ):
			print 'Failed, server send the error code.'
			print 'Error code: ', e.code
		else:
			print 'Excption is unkonwn'
		return ''



html = openWeb( URL_KJGG )
print len(html)

log = open( 'parse.log', 'w' )
log.write( html )
log.close()
