#!/usr/bin/python
#-*-coding: utf-8 -*-

import re
import urllib2

URL="http://www.yahoo.org"

socket = urllib2.urlopen(URL)
html = socket.read()

print '------------html-----------'
#print html

print "open tags < **** >"
print re.findall(r"<[^/>][^>]*>", html)[0:3]

print "close tag </***>"
print re.findall(r"</[^/>][^>]*>", html )[0:3]

print "self-closing tags <***/>"
print re.findall(r"<[^>]+/>", html )[0:3]


print "--------- find head tag --------"
print "[eg]: "
head_reg = r"<head>([^>]+)</head>"
for link in re.findall( head_reg, html ):
    print link

print "-------- find href link -----------"
print '''[eg]: <a href="URL">TEXT</a> '''
href_reg = r"<a\s+href\s*=\s*['\"]?([^\"'\s]+)[\"\']?>([^<]+)</a>"
i=0
for link in re.findall(href_reg, html):
    i += 1
    print i,link[1], link[0]
print "------------ find all image --------------"
'''
<img width="635" height="250 class="fptoday-img" src="http://l3.yimg.com/nn/fp/rsz/101413/images/smush/MorningSuccess_635x250_1381788216.jpg">
'''
image_reg = r"<img\s+[^>]*?src\s*=\s*['\"]?([^\"'\s]+)[\"']?[^>]*>"
i=0
for link in re.findall( image_reg, html ):
    i += 1
    print i, link
    