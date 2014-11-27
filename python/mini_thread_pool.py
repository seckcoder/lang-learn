import threading

class MiniThreadPool(object):
    def __init__(self):
        self.threads = []
    def run(self, target):
        t = threading.Thread(name="threads-" + str(len(self.threads)),
                             target=target)
        t.start()
        self.threads.push(t)

    def join(self):
        for t in self.threads
