import urllib2


def test_proxy_https():
    proxy_handler = urllib2.ProxyHandler({"http": "127.0.0.1:8087",
                                          "https":"127.0.0.1.:8087"})
    opener = urllib2.build_opener(proxy_handler)
    req = urllib2.Request("https://www.google.com/reader/view/")
    print req.get_host()
    opener.open(req)
    print req.get_host()

test_proxy_https()
