#!/usr/bin/python
#encoding=utf-8
#一定要有这行编码制定，否则中文的注释会出错

##########################################################################
## 人人网登陆和获取好友信息
## 作者：	涂灿
## Email：tusion@163.com
## 最后编辑时间： 2011-04-30
##########################################################################

import sys,re,urllib2,urllib,cookielib,os,time
from BeautifulSoup import BeautifulSoup
import cPickle 
#cPickle可以对任意一种类型的python对象进行序列化操作

############################################################################################
#通过cookie的方式登陆人人网
#这样明文写出来很不安全！！！
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
#获取自己的好友列表，只需要在好友页面的首页就能找到全部人
URL_FRIENDLIST='http://friend.renren.com/myfriendlistx.do'
result=opener.open(URL_FRIENDLIST)
html=result.read()
#print html					#源代码输出存为1x.html
print 'find the friends information,wait...' 
reg='friends=.*?];'			#正则匹配
f=re.search(reg,html)
#函数将返回一个元组，元组中的元素就是正则表达式中定义的组
x = f.group()		#f.group()的类型应该是元祖的，可这里实测为str	
#print x				#通过小技巧把正则匹配到的好友列表信息存为文本文件
					#运行命令：python renren_login_beta.py > group.txt 
					#这里可以考虑存入数据库处理
x = x[8:-1] 		#去掉返回的头标志”friends=“，共有八个字符
#print"\n=====================================\n"
#print x
x = x.replace('true', 'True')	#人人的bool表达式有点不一样
x = x.replace('false', 'False')
x = x.replace('\/','/')
friends = eval(x) 	#把类型为str的x转换为类型为list的friends
					#eval 函数将一个字符串 作为 Python 表达式求值
					#eval语句用来计算存储在字符串中的有效Python表达式
#print"\n=========================================\n"
#print friends		#源代码输出存为2frends.txt
print 'get friendlist.dat, wait....'
for friend1 in friends:
	for key in friend1.keys():
		if key=='name':
			#print(friend1[key])
			#把名字的编码变为汉字
			friend1[key]=eval('u"' + friend1[key] + '"').encode('utf-8')
			#编码方式的问题还不太明白！！！！
			#print(friend1[key])		#源代码输出存为3frend1.txt
friendfile=file('friendlist.dat','w')
cPickle.dump(friends,friendfile)
friendfile.close()
time_getinfo=time.time()
time_cost=round( time_getinfo - time_login,4)
print 'get friendlist.dat,time cost :',time_cost, '(s).  success !!!!!'

############################################################################################
#通过自己账户的好友页面得到所有好友，下载他们的小头像
print 'ready to down the headphoto,wait ...'
if os.path.isfile('friendlist.dat'):
	friendlist= file('friendlist.dat','r')
	friends=cPickle.load(friendlist)
	result={}
	
	NumFriends=len(friends)
	print"the number of friends is :",NumFriends
	
	#为小图像建立目录
	NowDir=os.getcwd()
	MiniPhotoDir=NowDir+os.sep+'mini_head_photo'
	if not os.path.exists(MiniPhotoDir):
			os.mkdir(MiniPhotoDir)
	os.chdir(MiniPhotoDir)
	
	#将要下载的文件地址存到TXT后，统一下载，速度提升很大
	if os.path.exists("downurllist.txt"):
		os.remove("downurllist.txt")		
	downurlfile=open( 'downurllist.txt','wr')
	for friend in friends:
		#print NumFriends,"-",i,":",friend['name'],"==",friend['head']
		DownPhotoUrl = friend['head']+'\n'
		# 在文件后面追加写的参数为“w+”
		downurlfile.write( DownPhotoUrl)
	
	#参数N为时间戳，可避免重复下载
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
#进入每个好友相册页面，先扫描他们有几页页面的相册，（大部分人只有一页）
#解析他们的头像相册

friendid=45542


URL_PHOTO1='http://photo.renren.com/photo/'
URL_PHOTO2='/album/relatives'

reg1=re.compile(URL_PHOTO1.replace('/','\/')+'.*'+URL_PHOTO2+'.*?(?=\")')
	#需要匹配的字符如下：
	#http://photo.renren.com/photo/45542/album/relatives?curpage=0
	#http://photo.renren.com/photo/45542/album/relatives?curpage=1
reg2=re.compile(URL_PHOTO1.replace('/','\/')+'.*m-.*?(?=\")')
	#需要匹配的字符如下：
	#http://photo.renren.com/photo/45542/album-441483466?albumpage=0#thumb
	#http://photo.renren.com/photo/45542/album-438524887?albumpage=0#thumb

reg3=re.compile('http://photo.renren.com/.*m-.*?curpage=.')
	#需要匹配的字符如下：
	
reg4=re.compile('http:\/\/photo.renren.com\/photo.*?t=')
urlreg=re.compile('(?<=largeurl":").*?.jpg')
namereg=re.compile('(?<=id = "albumname" value=").*?(?=" )')

#进入他们的相册首页
url=URL_PHOTO1+str(friendid)+URL_PHOTO2
albumhtml=opener.open(url).read()
#找到相册网页首页的页数
albumpages=reg1.findall(albumhtml)
if albumpages:
	#去除冗余
	albumpages=list(set(albumpages))
else:
	print friendid , "albumpages is not found..."
	


#######找到相册网页首页的页数
######albumpages=reg1.findall(albumhtml)
#去除冗余
#####albumpages=list(set(albumpages))


#将要下载的文件地址存到TXT后，统一下载，速度提升很大
# if os.path.exists("downurllist.txt"):
	# os.remove("downurllist.txt")
# txtname = friendid +"_downloadurl.txt"
txtname = "downloadurlall.txt"
downurlfile=open( txtname,'w+')


#头像相册只在第一页的最后一个出现
albumpage =URL_PHOTO1+str(friendid)+URL_PHOTO2+'/album/relatives'

albumhtml=opener.open(albumpage).read()
#找到每个小相册对应的地址albums
albums=reg2.findall(albumhtml)
if albums:
	albums=list(set(albums))
	#print "albums has num:",len(albums)
	#print "albums=",albums
				
	##############################################################
	#进入每个相册,得到相册每页对应的页面地址
	#这里有问题，只能找到第一页的小相册地址？？？
	
	for _album in albums:
		photohtml=opener.open(_album).read()
		photopages=reg3.findall(photohtml)
		if photopages:
			photopages=list( set(photopages))
		else:
			photopages=[_album,]
		#print _album ,"has num:",len(photopages)	
		print photopages
		
		#得到具体每张照片的地址
		# num=0
		# for _photopage in photopages:
			# photohtml=opener.open(_photopage).read()
			# if num==0:
				# if not os.path.isdir(NowDir+os.sep+"user"):
					# os.mkdir(NowDir+os.sep+"user")
				# name=namereg.search(photohtml)
				# print name.group()
				# if name ==“头像相册”:
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

			
			


