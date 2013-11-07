_opener=None

class BaseHandler:
    handler_order = 500
    def add_parent(self, parent):
        self.parent = parent
    def close(self):
        pass
    def __lt__(self, other):
        if not hasattr(other, "handler_order"):
            return True
        return self.handler_order < other.handler_order
class AbstractHTTPHandler(BaseHandler):
    def __init__(self, debuglevel=0):
        self._debuglevel = debuglevel
    def set_http_debuglevel(self, level):
        self._debuglevel = level

    def do_open(self, http_class, req):


def build_opener():
    opener = OpenerDirector()
    for h in [HTTPHandler]:
        h = h()
        opener.add_handler(h)
    return opener
def urlopen(url):
    global _opener
    if _opener is None:
        _opener = build_opener()
    return _opener.open(url)
