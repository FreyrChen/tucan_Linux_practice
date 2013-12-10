#!/usr/bin/python
#-*-coding: utf-8 -*-


import urllib2,time, re, sys
from bs4 import  BeautifulSoup #beautifulsoup4 change name to bs4


site = 'http://210.75.213.188/shh/portal/bjjs/index.aspx'

time_begin = time.time() 
html_src = urllib2.urlopen( site ).read()    #load web's HTML source code 
#print html_src
time_login=time.time()
time_cost=round( time_login-time_begin,4)
print 'Loading web cost time:',time_cost, ' s'

print'--------- use replex ----------------------'
#string = u"存量房“
#string = unicode( u"存量房", "utf8")
#string=eval('u"' + '存量房' + '"').encode('utf-8')
tag = r"class=\"tjInfo\""
result = re.findall(tag, html_src)
print len( result)
print result[0:4]
'''
match = re.search( tag, html_src )
print match
if match:
    print match.group()
'''    
print '--------- use BeautifulSoup --------------'
soup = BeautifulSoup( html_src )
print 'soup type: ', type(soup)
print 'html_src type: ', type(html_src)
#print( soup.prettify() )

print soup.html.head.title
print soup.html.head.title.string
print soup.html.contents[0].contents[0].next
print soup.name
print soup.html.name


print sys.getdefaultencoding()

#print soup.html.find('table')
#print soup('table', class="tjInfo01")
#for incident in soup.html('table', class="tjInfo01"):
#    print incident

