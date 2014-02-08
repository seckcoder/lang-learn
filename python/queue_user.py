#/usr/bin/env python
import Queue
import threading
def test_queue():
    def worker():
        while not q.empty():
            item = q.get()
            print item
            q.task_done()
        print threading.current_thread().getName()
    q = Queue.Queue()
    for item in ['hello', 'world', 'haha', 'liwei', 'seckcoder']:
        q.put(item)
    for i in range(10):
        t = threading.Thread(target = worker, name=str(i))
        t.setDaemon(True)
        t.start()
        t.join()
        print 'yes'
    q.join()
    print 'finished'
def test_priority_queue():
    q = Queue.PriorityQueue()
    counter=0
    for item in ['hello', 'world', 'haha', 'liwei', 'seckcoder']:
        q.put((10-counter,item))
        if q.empty():
            print 'empty'
        else:
            print 'not empty'
        counter+=1
    q.put((1222, 'seckcoder'))
    while not q.empty():
        item = q.get()
        print item
        q.task_done()
test_priority_queue()
