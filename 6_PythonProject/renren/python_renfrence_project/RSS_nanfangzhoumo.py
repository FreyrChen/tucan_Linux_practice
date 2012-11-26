# down html from zm and save html to txt
#  -*- coding:utf-8 -*-
import htmllib, formatter, urllib, re

website = 'http://www.nanfangdaily.com.cn'
f = urllib.urlopen(website)
html = f.read ().lower()
i = html.find('url=')
j = html.find('/',i+4)
date = html[i+4:j]
website += date

f = urllib.urlopen(website)
p = htmllib.HTMLParser(formatter.NullFormatter())
p.feed(f.read())
p.close()
seen = set()
for url in p.anchorlist:
 if url[-3::] == 'asp':
  if url in seen: continue
  seen.add(url)
  
urls=list(seen)
k=len(urls)
doc=open(u'thetst'.encode('gb18030')+date+'.txt','a')
for l, url in enumerate(urls):
 f = urllib.urlopen(website+url[1:])
 html = f.read()
 i = html.find('#ff0000')
 i = html.find('>',i+7)
 j = html.find('<',i+1)
 doc.write(html[i+1:j])
 i = html.find('content01',j+1)
 i = html.find('>',i+9)
 j = html.find('</font',i+1)
 content = html[i+1:j]
 reobj = re.compile(r'</?[a-z][a-z0-9]*[^<>]*>',re.IGNORECASE)
 doc.write(reobj.sub('\n',content)+'\n------------\n')
 print l+1,'-->',k 
doc.close()
print u'jobdone!!'
