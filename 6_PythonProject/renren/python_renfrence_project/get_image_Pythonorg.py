import HTMLParser
import urllib

urlString ="http://www.python.org/index.html"

def getimage(addr):
    	u = urllib.urlopen(addr)
    	data = u.read()
	splitPath = addr.split("/")
	fName = splitPath.pop()
	print"saving %s"%fName
	f = open(fName,'wb')
	f.write(data)
	f.close()
	

class parseimages(HTMLParser.HTMLParser):
    def handle_starttag(self,tag,attrs):
        if tag == "img":
            for name,value in attrs:
                if name == "src":
                    getimage(urlString+"/"+value)
mypareser = parseimages()
u = urllib.urlopen(urlString)
print"opening url\n =========="
print u.info()

                    
