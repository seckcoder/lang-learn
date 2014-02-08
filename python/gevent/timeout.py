from gevent import Timeout
from gevent import sleep
try:
    with Timeout(2):
        sleep(4)
except Timeout:
    print "haha"
