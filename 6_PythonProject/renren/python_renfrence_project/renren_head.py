import urllib,urllib2,cookielib
from BeautifulSoup import BeautifulSoup
mycookie = urllib2.HTTPCookieProcessor( cookielib.CookieJar())
opener = urllib2.build_opener( mycookie )

postdata = {
	'email':'tusion@163.com',
	'password':'584521',
	'origURL':'http://www.renren.com/Home.do',
	'domain':'renren.com'
}
req = urllib2.Request('http://www.renren.com/PLogin.do', urllib.urlencode(postdata))
html_src = opener.open(req).read()
parser = BeautifulSoup(html_src)

# article_list = parser.find('div','feed-list').findAll('article')
# for my_article in article_list:
    # state = []
    # for my_tag in my_article.h3.contents:
        # factor = my_tag.string
        # if factor != None:
            # factor = factor.replace(u'\xa0','')
            # factor = factor.strip(u'\r\n')
            # factor = factor.strip(u'\n')
            # state.append(factor)
    # print ' '.join(state)
#raw_input()

figure_list = parser.findAll('figure','newsfeed-user')
# for my_article in article_list:
     #state = []
     # for my_tag in my_article.aside.newsfeed-user.a.contents:
        # fData = my_tag.img
		#fName =  my_tag.img.string
		# fName = 'qq'
        # print"saving %s"%fName
        # f = open(fName,'wb')
        # f.write(data)

print 	figure_list	




