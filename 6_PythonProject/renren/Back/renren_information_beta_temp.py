#!/usr/bin/python
#encoding=utf-8
#һ��Ҫ�����б����ƶ����������ĵ�ע�ͻ����

##########################################################################
## ��������½�ͻ�ȡ������Ϣ
## ���ߣ�	Ϳ��
## Email��tusion@163.com
## ���༭ʱ�䣺 2011-04-30
##########################################################################

import sys,re,urllib2,urllib,cookielib,os,time
from BeautifulSoup import BeautifulSoup
import cPickle 
#cPickle���Զ�����һ�����͵�python����������л�����

############################################################################################
#ͨ��cookie�ķ�ʽ��½������
#��������д�����ܲ���ȫ������
time_begin = time.time()
mycookie = urllib2.HTTPCookieProcessor( cookielib.CookieJar())
opener = urllib2.build_opener( mycookie )

postdata = {
	'email':'tusion@163.com',
	'password':'584521',
	'origURL':'http://www.renren.com/Home.do',
	'domain':'renren.com'
}
# postdata = {
	# 'email':'x_wang08@163.com',
	# 'password':'416390012',
	# 'origURL':'http://www.renren.com/Home.do',
	# 'domain':'renren.com'
# }

req = urllib2.Request('http://www.renren.com/PLogin.do', urllib.urlencode(postdata))
print 'Login reenren.com,wait...'
html_src = opener.open(req).read()
time_login=time.time()
time_cost=round( time_login-time_begin,4)
print 'Login sucsess,time cost:',time_cost, '(s)'

############################################################################################
#��ȡ�Լ��ĺ����б�ֻ��Ҫ�ں���ҳ�����ҳ�����ҵ�ȫ����
URL_FRIENDLIST='http://friend.renren.com/myfriendlistx.do'
result=opener.open(URL_FRIENDLIST)
html=result.read()
#print html					#Դ���������Ϊ1x.html
print 'find the friends information,wait...' 
reg='friends=.*?];'			#����ƥ��
f=re.search(reg,html)
#����������һ��Ԫ�飬Ԫ���е�Ԫ�ؾ���������ʽ�ж������
x = f.group()		#f.group()������Ӧ����Ԫ��ģ�������ʵ��Ϊstr	
#print x				#ͨ��С���ɰ�����ƥ�䵽�ĺ����б���Ϣ��Ϊ�ı��ļ�
					#�������python renren_login_beta.py > group.txt 
					#������Կ��Ǵ������ݿ⴦��
x = x[8:-1] 		#ȥ�����ص�ͷ��־��friends=�������а˸��ַ�
#print"\n=====================================\n"
#print x
x = x.replace('true', 'True')	#���˵�bool���ʽ�е㲻һ��
x = x.replace('false', 'False')
x = x.replace('\/','/')
friends = eval(x) 	#������Ϊstr��xת��Ϊ����Ϊlist��friends
					#eval ������һ���ַ��� ��Ϊ Python ���ʽ��ֵ
					#eval�����������洢���ַ����е���ЧPython���ʽ
#print"\n=========================================\n"
#print friends		#Դ���������Ϊ2frends.txt
print 'get friendlist.dat, wait....'
for friend1 in friends:
	for key in friend1.keys():
		if key=='name':
			#print(friend1[key])
			#�����ֵı����Ϊ����
			friend1[key]=eval('u"' + friend1[key] + '"').encode('utf-8')
			#���뷽ʽ�����⻹��̫���ף�������
			#print(friend1[key])		#Դ���������Ϊ3frend1.txt
friendfile=file('friendlist.dat','w')
cPickle.dump(friends,friendfile)
friendfile.close()
time_getinfo=time.time()
time_cost=round( time_getinfo - time_login,4)
print 'get friendlist.dat,time cost :',time_cost, '(s).  success !!!!!'

############################################################################################
#ͨ���Լ��˻��ĺ���ҳ��õ����к��ѣ��������ǵ�Сͷ��
print 'ready to down the headphoto,wait ...'
if os.path.isfile('friendlist.dat'):
	friendlist= file('friendlist.dat','r')
	friends=cPickle.load(friendlist)
	result={}
	
	NumFriends=len(friends)
	print"the number of friends is :",NumFriends
	
	#ΪСͼ����Ŀ¼
	NowDir=os.getcwd()
	MiniPhotoDir=NowDir+os.sep+'mini_head_photo'
	if not os.path.exists(MiniPhotoDir):
			os.mkdir(MiniPhotoDir)
	os.chdir(MiniPhotoDir)
	
	#��Ҫ���ص��ļ���ַ�浽TXT��ͳһ���أ��ٶ������ܴ�
	if os.path.exists("downurllist.txt"):
		os.remove("downurllist.txt")		
	downurlfile=open( 'downurllist.txt','wr')
	for friend in friends:
		#print NumFriends,"-",i,":",friend['name'],"==",friend['head']
		DownPhotoUrl = friend['head']+'\n'
		# ���ļ�����׷��д�Ĳ���Ϊ��w+��
		downurlfile.write( DownPhotoUrl)
	
	#����NΪʱ������ɱ����ظ�����
	#DownPhotocommand="wget -qN  -i %s" %("downurllist.txt")
	DownPhotocommand="wget -qN  -i downurllist.txt"
	print "		Downloading ... ....................................." 
	#################################################
#	os.system(DownPhotocommand)
	################################################
	#if os.system(DownPhotocommand)==0:
	#i=i+1
	downurlfile.close()	
else:
	print 'please get friendlist.dat first'

time_getmini=time.time()
time_cost=round( time_getmini - time_getinfo,4)
print 'get all mini photo,time cost :',time_cost, '(s).  success !!!!!'
	
############################################################################################
#����ÿ���������ҳ�棬��ɨ�������м�ҳҳ�����ᣬ���󲿷���ֻ��һҳ��
#�������ǵ�ͷ�����

friendid=45542
URL_PHOTO1='http://photo.renren.com/photo/'
URL_PHOTO2='/album/relatives'

reg1=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+URL_PHOTO2+'.*?(?=\")')
	#ƥ���м�Ϊ�����ַ�����'��β���ַ���������
	#http://photo.renren.com/photo/45542/album/relatives?curpage=0
	#http://photo.renren.com/photo/45542/album/relatives?curpage=1
	
	
#text = ("ͷ�����").decode("ascii").encode('utf-16')
#text=eval('u"' + "ͷ�����" + '"').encode('utf-16')
#text = u'\u5934\u50CF\u76F8\u518C' 

# text = "ͷ�����"
# text= unicode(text,'utf8')
#text = '\xe5\xa4\xb4\xe5\x83\x8f\xe7\x9b\xb8\xe5\x86\x8c'
reg_head_albumpages=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+'.*?(?=\"\>\xe5\xa4\xb4\xe5\x83\x8f\xe7\x9b\xb8\xe5\x86\x8c)')

#reg_head_albumpages=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+u'\u5934\u50CF\u76F8\u518C')
#reg_head_albumpages=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+'.*?(?=""\"\>"+"u"ͷ�����"")')
#reg_head_albumpages=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+'.*?(?=\"\>[\u4e00-\u9fa5])')

reg2=re.compile(URL_PHOTO1.replace('/','\/')+'.*m-.*?(?=\")')
	#��Ҫƥ����ַ����£�
	#http://photo.renren.com/photo/45542/album-441483466?albumpage=0#thumb
	#http://photo.renren.com/photo/45542/album-438524887?albumpage=0#thumb

reg3=re.compile('http://photo.renren.com/.*m-.*?curpage=.')
	#��Ҫƥ����ַ����£�
	


namereg=re.compile('(?<=id = "albumname" value=").*?(?=" )')




#�������ǵ������ҳ
url=URL_PHOTO1+str(friendid)+URL_PHOTO2
#url = http://photo.renren.com/photo/45542/album/relatives
#���û����
albumhtml=opener.open(url).read() 
#�ҵ������ҳ��ҳ��ҳ��
albumpages=reg1.findall(albumhtml)
if albumpages:
	#ȥ������
	albumpages=list(set(albumpages))
else:
	print friendid , "albumpages is not found..."

head_albumpages= reg_head_albumpages.findall(albumhtml)
if head_albumpages:
	#ȥ������
	head_albumpages=list(set(head_albumpages))
	print head_albumpages
else:
	print friendid , "head_albumpages is not found..."