import socket
import urllib2
import httplib
from urllib import addinfourl
access_token = "2.001svOGDXBRcBEe533b988f8SIux1E"
def main():
    req = urllib2.Request("https://api.weibo.com/2/statuses/public_timeline.json")
    req.add_header('Authorization', 'OAuth2 %s' % access_token)
    sel_host = req.get_host()
    req.add_unredirected_header('Host', sel_host)
    req.add_unredirected_header('User-agent', 'Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0')
    #resp = urllib2.urlopen(req)
    h = httplib.HTTPSConnection(req.get_host())
    headers = dict(req.headers)
    headers.update(req.unredirected_hdrs)
    headers["Connection"] = "close"
    headers = dict(
        (name.title(), val) for name, val in headers.items())

    try:
        h.request(req.get_method(), req.get_selector(), req.data, headers)
        r = h.getresponse()
    except socket.error as err:
        print err
#    r.recv = r.read
    #fp = socket._fileobject(r, close=True)
    #resp = addinfourl(fp, r.msg, req.get_full_url())
    #resp.code = r.status
    #resp.msg = r.reason

def proxy():
    def demo():
        req = urllib2.Request("http://www.google.com")
        proxy = {
            "http": "http://10.1.2.17:8080"
        };
        proxy_handler = urllib2.ProxyHandler(proxy);
        #import pdb; pdb.set_trace()
        opener = urllib2.build_opener(proxy_handler)
        #opener = urllib2.build_opener()
        print "open"
        resp = opener.open(req)
        print "here"
    def add_handler():
        default_classes = [urllib2.ProxyHandler, urllib2.UnknownHandler, urllib2.HTTPHandler]
        opener = urllib2.OpenerDirector()
        for kclass in default_classes:
            opener.add_handler(kclass())
proxy()
