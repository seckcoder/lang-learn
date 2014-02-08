#!/usr/bin/env python
import threading
import time
import logging
def config_log():
    numeric_level = getattr(logging, 'INFO', None) # TODO: Li Wei(cmd line support)
    if not isinstance(numeric_level, int):
        raise ValueError('Invalid log level')
    logging.basicConfig(filename='water_army.log', level=numeric_level,
                        filemode='w', format=('%(asctime)s: '
                                              '%(levelname)s: '
                                              '%(module)s: '
                                              '%(funcName)s(): '
                                              '%(lineno)d:\t '
                                              '%(message)s:'))
def test_Timer():
	def hello():
		print 'hello'
	def world():
		print 'world'
	t = threading.Timer(1, hello)
	t.start()
	t = threading.Timer(1, world)
	t.start()
def test_Thread_Object():
	class tobj(object):
		def __call__(self, msg, debug_info):
			print msg
			print debug_info
	def tfun(msg, debug_info):
		print threading.currentThread().name, 'Starting'
		print msg
		print debug_info
		print threading.currentThread().name, 'End'
	class MyThread(threading.Thread):
		def __init__(self, group=None, target=None, name=None,
				args=(), kwargs={}, verbose=None):
			#super(MyThread,self).__init__(name=name, group=group, target=target, name=name)
			super(MyThread,self).__init__()
			self.args = args
			self.kwargs = kwargs
			self.target= target
			self.args = args
			self.kwargs = kwargs
			self.name = name
		def run(self):
			self.target(self.args, self.kwargs)
			print 'runrun'
			return
	t = threading.Thread(target=tobj(), name='thread--1', args=('hello world',), kwargs={'debug_info':'hahaa',})
	t.setDaemon(True)
	t.start()
	t.join()
	t = threading.Thread(target=tfun, name='thread--2', args=('hello world',), kwargs={'debug_info':'hahaa',})
	t.setDaemon(True)
	t.start()
	t.join()
	t = MyThread(target=tfun, name='thread--3', args=('hello world',), kwargs={'debug_info':'hahaa',})
	t.setDaemon(True)
	t.start()
	t.join()
def tfun1():
    time.sleep(2)
    logging.info('%s' % threading.currentThread().name)
    print threading.currentThread().name
    logging.info('%s' % 'exit tfun1')
    print 'exit tfun1'
def tfun2():
    print threading.currentThread().name
    print 'Exiting tfun2'
def test_Daemon_Thread():
	t = threading.Thread(name='daemon thread 1', target=tfun1)
	t.setDaemon(True)
	print 'We will start daemon thread 1, but it may not finish executing before main thread finish,\
notice that daemon thread is still alive'
	t.start()
	t = threading.Thread(name='daemon thread 2', target=tfun2)
	t.setDaemon(True)
	print 'We will start daemon thread 2, main thread will be blocked to finish it'
	t.start()
	t.join()
def test_Event():
	def wait_for_event(e):
		print 'wait for event starting'
		event_is_set = e.wait()
		print 'event set: %s' % event_is_set
	def wait_for_event_timeout(e, t):
		while not e.isSet():
			print 'wait for event timeout starting'
			event_is_set = e.wait(t)
			print 'event set: %s' % event_is_set
			if event_is_set:
				print 'processing event'
			else:
				print 'doing other work'
	e = threading.Event()
	t1 = threading.Thread(name='block',
			target=wait_for_event, args=(e,))
	t1.start()
	t2 = threading.Thread(name='non-block',
			target=wait_for_event_timeout, args=(e,2))
	t2.setDaemon(True)
	t2.start()
	print 'waiting before calling event.set()'
	time.sleep(4)
	e.set()
	print 'Event is set'
	t2.join()
def test_Lock():
	print 'See: http://www.doughellmann.com/PyMOTW/threading/'
def test_RLock():
	lock = threading.Lock()
	try:
		print 'First try: ', lock.acquire()
		print 'Second try: ', lock.acquire(0)
	except Exception as inst:
		print inst
	lock = threading.RLock()
	try:
		print 'First try: ', lock.acquire()
		print 'Second try: ', lock.acquire(False)
		print 'Third try: ', lock.acquire(False)
	except Exception as inst:
		print inst

def loopfunc():
    while 1:
        pass
def test_Thread1():
    t = threading.Thread(name='thread', target=loopfunc)
    t.setDaemon(True)
    t.start()
    t.join()
    print 'haha'
def test_thread_exception():
    def call_exception_thread():
        def tfun1():
            a = 1
            assert a != 1, 'a equals 1'
        def tfun():
            print 'tfun'
            tfun1()
        t = threading.Thread(name='thread', target=tfun)
        t.start()
        t.join()
    try:
        print 'Note that one thread can\'t catch exception throwed by other thread'
        call_exception_thread()
    except AssertionError as inst:
        print inst
test_thread_exception()

#test_Thread1()
#test_Thread_Object()
config_log()
#test_Daemon_Thread()
#test_Event()
#test_RLock()
