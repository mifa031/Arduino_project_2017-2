from http import client
import time

headers={'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko'}
url1 = '/status.php?room_num='
url2 = '/status.php?room_num='
url2_1 = '&status=empty'
body=''

while(1):
    time.sleep(30)
    for i in range(1,21):
        if i!=1:
            conn = client.HTTPConnection('127.0.0.1',80)
            url = url1+str(i)
            conn.request('GET',url,body,headers)
            conn.close()
    for i in range(1,21):
        if i!=1:
            conn = client.HTTPConnection('127.0.0.1',80)
            url = url2 + str(i) + url2_1
            conn.request('GET',url,body,headers)
            res=conn.getresponse()
            conn.close()

 
"""
conn = client.HTTPConnection('121.128.151.144',80)
headers={'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko'}
url1 = '/'
body = ''
conn.request('GET',url,body,headers)
res=conn.getresponse()
resData=res.read()
strRes = str(resData) 
print(strRes)
conn.close()
"""
