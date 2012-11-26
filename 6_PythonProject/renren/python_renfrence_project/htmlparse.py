import HTMLParser
import urllib

class parselinks(HTMLParser.HTMLParser):
	def handle_stattag(self,tag,attrs):
		if tag == 'a':
			for name,value in attrs:
				if name == 'href':
					print value
                                        print self.get_starttag_text()
     

myparser = parselinks()
myparser.feed(urllib.urlopen("http://www.python.org/index.html").read())
