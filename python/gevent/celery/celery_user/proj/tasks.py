from __future__ import absolute_import
from celery.utils.log import get_task_logger
from celery.result import AsyncResult
from celery.contrib.methods import task_method
#from celery.contrib.methods import task
from celery.task import task

logger = get_task_logger(__name__)

from proj.celery import celery
@celery.task
def add(x, y):
    return x + y
@celery.task
def mul(x, y):
    return x * y
@celery.task
def xsum(numbers):
    return sum(numbers)
@celery.task
def minus(x, y):
    return x - y
@celery.task
def add_multi(x, y, n):
    return x

@celery.task
def add_callback(sum):
    logger.info('sum:%s' , sum)

@celery.task
def add_callback_noarg():
    logger.info('add_callback_noarg')

@celery.task
def add_exc_callback(task_id):
    result = AsyncResult(task_id)
    exc_value = result.get(propagate=False, timeout=10)
    print "*******"
    print "result:", result.result
    print "result type:", type(result.result)
    print "*******"
    print "traceback:", result.traceback
    print "*******"

@celery.task
def add_exc(x, y):
    raise RuntimeError('add_exc')


class StudyCase(object):
    #@celery.task(name='StudyCase.add_class', filter=task_method)
    @task(name='StudyCase.add_class')
    def add_class(self, x, y):
        print 'StudyCase.add_class'
        return x + y
    #@celery.task(name='StudyCase.add_class_callback', filter=task_method)
    @task(name='StudyCase.add_class_callback')
    def add_class_callback(self, task_ret):
        print 'task_ret:%s' % task_ret
    #@celery.task(name='StudyCase.add_class_exc_callback', filter=task_method)
    @task(name='StudyCase.add_class_exc_callback')
    def add_class_exc_callback(self, task_id):
        print 'task_id:%s' % task_id

class X(object):
    @task(name='X.add')
    def add(self, x, y):
            return x + y
