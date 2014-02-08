import gevent.monkey
gevent.monkey.patch_socket()

import gevent
import urllib2
import json
import time

def fetch(pid):
    response = urllib2.urlopen('http://www.google.com.hk')
    result = response.read()
    print len(result)
#    json_result = json.loads(result)
    #datetime = json_result['datetime']

    #print 'Process ', pid, datetime
    #return json_result['datetime']

num = 50
def synchronous():
    cur = time.time()
    for i in range(1,num):
        fetch(i)
    print "time: ", time.time() - cur

def asynchronous():
    cur = time.time()
    threads = []
    for i in range(1,num):
        threads.append(gevent.spawn(fetch, i))
    gevent.joinall(threads)
    print "time: ", time.time() - cur

print 'Synchronous:'
synchronous()

print 'Asynchronous:'
asynchronous()
