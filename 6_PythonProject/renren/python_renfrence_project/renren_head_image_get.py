import HTMLParser
import urllib

#urlString ="http://www.renren.com/home"
urlString ="http://friend.renren.com/myfriendlistx.do#item_0"
def getimage(addr):
        u = urllib.urlopen(addr)
        data = u.read()
        print"\nURL=%s"%addr
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
print("Openign<<< %s>>>>\n\
======================================")%urlString
print u.info()

mypareser.feed(u.read())
mypareser.close()





