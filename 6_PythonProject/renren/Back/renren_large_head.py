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
	#��Ҫƥ����ַ����£�
	#http://photo.renren.com/photo/45542/album/relatives?curpage=0
	#http://photo.renren.com/photo/45542/album/relatives?curpage=1
reg2=re.compile(URL_PHOTO1.replace('/','\/')+'.*m-.*?(?=\")')
	#��Ҫƥ����ַ����£�
	#http://photo.renren.com/photo/45542/album-441483466?albumpage=0#thumb
	#http://photo.renren.com/photo/45542/album-438524887?albumpage=0#thumb

reg3=re.compile('http://photo.renren.com/.*m-.*?curpage=.')
	#��Ҫƥ����ַ����£�
	
reg4=re.compile('http:\/\/photo.renren.com\/photo.*?t=')
urlreg=re.compile('(?<=largeurl":").*?.jpg')
namereg=re.compile('(?<=id = "albumname" value=").*?(?=" )')

#�������ǵ������ҳ
url=URL_PHOTO1+str(friendid)+URL_PHOTO2
albumhtml=opener.open(url).read()
#�ҵ������ҳ��ҳ��ҳ��
albumpages=reg1.findall(albumhtml)
if albumpages:
	#ȥ������
	albumpages=list(set(albumpages))
else:
	print friendid , "albumpages is not found..."
	


#######�ҵ������ҳ��ҳ��ҳ��
######albumpages=reg1.findall(albumhtml)
#ȥ������
#####albumpages=list(set(albumpages))


#��Ҫ���ص��ļ���ַ�浽TXT��ͳһ���أ��ٶ������ܴ�
# if os.path.exists("downurllist.txt"):
	# os.remove("downurllist.txt")
# txtname = friendid +"_downloadurl.txt"
txtname = "downloadurlall.txt"
downurlfile=open( txtname,'w+')


#ͷ�����ֻ�ڵ�һҳ�����һ������
albumpage =URL_PHOTO1+str(friendid)+URL_PHOTO2+'/album/relatives'

albumhtml=opener.open(albumpage).read()
#�ҵ�ÿ��С����Ӧ�ĵ�ַalbums
albums=reg2.findall(albumhtml)
if albums:
	albums=list(set(albums))
	#print "albums has num:",len(albums)
	#print "albums=",albums
				
	##############################################################
	#����ÿ�����,�õ����ÿҳ��Ӧ��ҳ���ַ
	#���������⣬ֻ���ҵ���һҳ��С����ַ������
	
	for _album in albums:
		photohtml=opener.open(_album).read()
		photopages=reg3.findall(photohtml)
		if photopages:
			photopages=list( set(photopages))
		else:
			photopages=[_album,]
		#print _album ,"has num:",len(photopages)	
		print photopages
		
		#�õ�����ÿ����Ƭ�ĵ�ַ
		# num=0
		# for _photopage in photopages:
			# photohtml=opener.open(_photopage).read()
			# if num==0:
				# if not os.path.isdir(NowDir+os.sep+"user"):
					# os.mkdir(NowDir+os.sep+"user")
				# name=namereg.search(photohtml)
				# print name.group()
				# if name ==��ͷ����ᡱ:
					# nextdir=NowDir+os.sep+"user"+os.sep+name.group()
				# else:
					# nextdir=NowDir+os.sep+"user"+os.sep
			# num=num+1
			

downurlfile.close()	
					
								
						
					




		
		
	# num=0
	# for _photopage in photopages:
		# photohtml=open(_photopage).read()
		# if num==0:
			# name=namereg.search(photohtml)
			# if name:
				# nextdir=DIR_NOW+os.sep+name.group()
			# else:
				# nextdir=DIR_NOW

		# num=num+1
		# photos=reg2.findall(photohtml)
		# if photos:
			# photos=list(set(photos))

			
			


